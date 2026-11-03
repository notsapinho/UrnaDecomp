// vota::CPedeTituloEncerramento (app/vota/operador/outrasopcoes/cpedetituloencerramento.cpp, the class name in lower
// case). This comment is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/cpedetituloencerramento.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/outrasopcoes/cconfirmaencerramento.h"
#include "app/vota/operador/outrasopcoes/cencerramentoantecipado.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"
#include "app/vota/operador/outrasopcoes/ctituloencerramentoinvalido.h"

namespace vota {

CPedeTituloEncerramento::~CPedeTituloEncerramento() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Informe seu título para", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("encerrar a votação", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    AdicionaCampoNumerico(builder, 12, true, api::SPoint{1, 3});
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPedeTituloEncerramento::CPedeTituloEncerramento()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
    , m_dataHoraEncerramento(comum::CConfiguracaoEleicao::GetInst().GetDataHoraEncerramento())
{
}

CPedeTituloEncerramento& CPedeTituloEncerramento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeTituloEncerramento());
    }
    return *s_inst;
}

std::unique_ptr<CPedeTituloEncerramento> CPedeTituloEncerramento::s_inst;
std::mutex CPedeTituloEncerramento::s_mutex;

void CPedeTituloEncerramento::StartState()
{
    m_pNextState = this;
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        if (m_dataHoraEncerramento > api::CDateTime::Now()) {
            m_pNextState = &CEncerramentoAntecipado::GetInst();
        } else {
            m_pNextState = &CConfirmaEncerramento::GetInst();
        }
    } else {
        m_form->Slot2();
    }
}

void CPedeTituloEncerramento::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (comum::CAppState* proximo = ConfirmaTitulo()) {
            m_pNextState = proximo;
        }
        break;
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaEncerramentoCancelado();
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    default:
        break;
    }
}

comum::CAppState* CPedeTituloEncerramento::ConfirmaTitulo()
{
    const std::string titulo = m_form->GetEntradas().at(0)->GetTexto();
    if (titulo.empty()) {
        return nullptr;
    }
    CThreadOperador::GetInst().SetTituloEncerramento(titulo);
    if (!TituloValido(titulo)) {
        return &CTituloEncerramentoInvalido::GetInst();
    }
    CLogVota::GetInst().LogaTituloDigitadoEncerramento(titulo);
    return &CConfirmaEncerramento::GetInst();
}

bool CPedeTituloEncerramento::TituloValido(const std::string& titulo)
{
    if (titulo.empty() || !std::all_of(titulo.begin(), titulo.end(), ::isdigit)) {
        return false;
    }
    const std::string numero = std::format("{:0>{}}", titulo, 12);
    return comum::md::CValidadorIdentidade::GetInst().EhValida(ecourna::app::dados::TipoIDInscricaoEleitoral, numero);
}

} // namespace vota
