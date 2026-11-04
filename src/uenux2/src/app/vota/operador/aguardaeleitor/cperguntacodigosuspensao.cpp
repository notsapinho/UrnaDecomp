// vota::CPerguntaCodigoSuspensao
// (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.cpp; no record names the file:
// the path is chosen, its directory from the data). The reconstruction's note, not TSE's text: no record names a line
// of this file either, so every line is a choice; src/units/142-uenux2-app-vota-estados-448.mk says what the bytes
// decide.
#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"

#include <string>
#include <utility>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/util/csystem.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/csincronismooperador.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CPerguntaCodigoSuspensao::~CPerguntaCodigoSuspensao() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Informe seu título para", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("suspender a votação", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: suspender", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    AdicionaCampoNumerico(builder, 12, true, api::SPoint{1, 3});
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaTituloInvalido()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Título inválido para", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("suspender a votação", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPerguntaCodigoSuspensao::CPerguntaCodigoSuspensao()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA)
    , m_form(MontaTela())
    , m_formConfirmacao(MontaTelaTituloInvalido())
    , m_bLido(false)
{
}

CPerguntaCodigoSuspensao& CPerguntaCodigoSuspensao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPerguntaCodigoSuspensao());
    }
    return *s_inst;
}

std::unique_ptr<CPerguntaCodigoSuspensao> CPerguntaCodigoSuspensao::s_inst;
std::mutex CPerguntaCodigoSuspensao::s_mutex;

void CPerguntaCodigoSuspensao::StartState()
{
    m_pNextState = this;
    CLogVota::GetInst().LogaPedidoTituloSuspensao();
    m_form->Slot2();
    m_bLido = false;
}

void CPerguntaCodigoSuspensao::ProcessInput()
{
    const api::EInputResult resultado = m_form->Read();
    if (m_bLido) {
        return;
    }
    switch (resultado) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaSuspensaoAbortada();
        CThreadEleitor::GetInst().GetMensagens().Post(4);
        m_pNextState = &CMostraEleitorVotando::GetInst();
        break;
    case api::INPUT_CONFIRMA: {
        const std::string texto = m_form->GetEntradas().at(0)->GetTexto();
        if (!texto.empty()) {
            CLogVota::GetInst().LogaTituloSuspensaoDigitado();
            const std::pair<bool, std::string> validacao = ValidaTituloSuspensao(texto);
            if (!validacao.first) {
                CLogVota::GetInst().LogaTituloSuspensaoInvalido(validacao.second);
                m_formConfirmacao->Slot2();
                api::CSystem::Dorme(3000);
                m_form->Slot2();
            } else {
                CLogVota::GetInst().LogaTituloSuspensaoValido(validacao.second);
                CThreadEleitor::GetInst().GetMensagens().Post(2);
                m_bLido = true;
            }
        }
        break;
    }
    default:
        break;
    }
}

void CPerguntaCodigoSuspensao::ProcessKey(uebyte tecla)
{
    switch (tecla) {
    case 5:
        m_pNextState = &CMostraEleitorVotando::GetInst();
        break;
    case 2:
        m_bLido = false;
        CEleitorVotouNaoVotou::GetInst().SetVotou(false);
        m_pNextState = &CEleitorVotouNaoVotou::GetInst();
        break;
    case 13:
        m_bLido = false;
        CSincronismoOperador::GetInst().SetSincronizado(true);
        m_pNextState = &CSincronismoOperador::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
