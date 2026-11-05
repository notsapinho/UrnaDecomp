#include "app/vota/operador/caguardainicio.h"

#include <format>
#include <string>

#include "api/gui/capplication.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/iscreenmt.h"
#include "api/util/cdatetime.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/outrasopcoes/cfimaquisicaovotos.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

namespace {

std::shared_ptr<api::IForm<api::IScreenMT>> MontaTelaAguardaInicio()
{
    api::CMTFormBuilderBase builder;
    const std::string aplicacao = std::format("{}: {}", api::CApplication::s_aplicacao, api::CApplication::s_versao);
    const size_t traco = aplicacao.find('-');
    if (traco != std::string::npos) {
        const std::string primeira = ecourna::api::util::CStringUtils::Trim(aplicacao.substr(0, traco));
        const std::string segunda = ecourna::api::util::CStringUtils::Trim(aplicacao.substr(traco + 1));
        if (!primeira.empty()) {
            builder.AddTextField(primeira, api::SPoint{1, 1}, api::ALINHAMENTO_CENTRO);
        }
        if (!segunda.empty()) {
            builder.AddTextField(segunda, api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
        }
    } else {
        builder.AddTextField(aplicacao, api::SPoint{1, 1}, api::ALINHAMENTO_CENTRO);
    }
    builder.AddTextField("Siga as instruções na tela do eleitor", api::SPoint{1, 3}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(&api::CDateTime::FormatCurrentDate, api::SPoint{11, 4}, "DD/MM/YYYY", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&api::CDateTime::FormatCurrentTime, api::SPoint{22, 4}, "hh:mm:ss", api::ALINHAMENTO_ESQUERDA);
    return builder.GetForm("");
}

} // namespace

CAguardaInicio::CAguardaInicio()
    : comum::CAppState(EVENTO_TECLA | EVENTO_TICK)
    , m_form(MontaTelaAguardaInicio())
    , m_tick(CThreadOperador::GetInst().AddStoppedTick(500))
{
}

CAguardaInicio& CAguardaInicio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAguardaInicio());
    }
    return *s_inst;
}

std::unique_ptr<CAguardaInicio> CAguardaInicio::s_inst;
std::mutex CAguardaInicio::s_mutex;

CAguardaInicio::~CAguardaInicio() = default;

void CAguardaInicio::StartState()
{
    m_pNextState = this;
    CThreadOperador::GetInst().StartTick(m_tick);
    m_form->Slot2();
}

void CAguardaInicio::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tick);
}

void CAguardaInicio::ProcessTick(uebyte id)
{
    if (id == m_tick) {
        m_form->Slot2();
    }
}

void CAguardaInicio::ProcessKey(uebyte tecla)
{
    switch (tecla) {
    case 8:
        CLogVota::GetInst().loga("Urna pronta para receber votos");
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    case 7:
        m_pNextState = &comum::CRegistrarMesarios::GetInst();
        break;
    case 10:
        m_pNextState = &CFimAquisicaoVotos::GetInst();
        break;
    default:
        CAppState::ProcessKey(tecla);
        break;
    }
}

} // namespace vota
