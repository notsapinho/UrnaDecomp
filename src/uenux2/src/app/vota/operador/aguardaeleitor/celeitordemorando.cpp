// vota::CEleitorDemorando (app/vota/operador/aguardaeleitor/celeitordemorando.cpp, the class name in lower case; the
// directory from the data). This comment is the reconstruction's: no record names this file or its functions, so
// every line is a choice, in the order of the use bands where they give one
// (src/units/152-uenux2-app-vota-operador-estados.mk).
#include "app/vota/operador/aguardaeleitor/celeitordemorando.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.h"
#include "app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CEleitorDemorando::~CEleitorDemorando() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> situacao,
                                                                                std::shared_ptr<std::string> texto)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_1);
    builder.AddBuzz(51, 10);
    builder.AddTextField("O eleitor está demorando", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(situacao), api::SPoint{1, 2}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(texto), api::SPoint{1, 3});
    builder.AddTextField("CONFIRMA", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEleitorDemorando::CEleitorDemorando()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA)
    , m_bVotou(false)
    , m_situacao(std::make_shared<std::string>("votou/não votou"))
    , m_texto(std::make_shared<std::string>("nome abreviado"))
    , m_form(MontaTela(m_situacao, m_texto))
{
}

CEleitorDemorando& CEleitorDemorando::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorDemorando());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorDemorando> CEleitorDemorando::s_inst;
std::mutex CEleitorDemorando::s_mutex;

void CEleitorDemorando::StartState()
{
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        CSuspensaoAutomaticaEleitor& suspensao = CSuspensaoAutomaticaEleitor::GetInst();
        suspensao.SetVotou(m_bVotou);
        m_pNextState = &suspensao;
        return;
    }
    if (m_bVotou) {
        *m_situacao = "Votou parcialmente";
    } else {
        *m_situacao = "Não votou";
    }
    CLogVota::GetInst().LogaEleitorSemAtividade(
        comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoDispararSuspensao());
    m_pNextState = this;
    *m_texto = CThreadOperador::GetInst().GetTextoEleitor();
    m_form->Slot2();
}

void CEleitorDemorando::ProcessKey(uebyte tecla)
{
    if (tecla == 5) {
        m_pNextState = &CMostraEleitorVotando::GetInst();
    }
}

void CEleitorDemorando::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPerguntaEleitorVotando::GetInst();
    }
}

} // namespace vota
