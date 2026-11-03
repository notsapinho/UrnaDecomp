// vota::CRegistraDigitalOperador's file, the path its records give:
// /home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp. The reconstruction's
// note, not TSE's text: the records fix StartState's lines (95 and 98) and FinishState's (104 and 105); ProcessTick's
// (143 to 145) and BiometriaMesarioPresenteNosEleitores's (328 and 371) hold no code of ours, those members not written.
// Every other line is a choice. comum::md::CComparecimentoMesarioPK's constructor (target fn 2738) is at chosen lines
// after the records. src/units/221-uenux2-app-comum-constructors.mk has the notes on both classes.
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/hwil/ifingerscanner.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CRegistraDigitalOperador::~CRegistraDigitalOperador() = default;

std::unique_ptr<CRegistraDigitalOperador> CRegistraDigitalOperador::s_inst;
std::mutex CRegistraDigitalOperador::s_mutex;

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaRegistraDigitalOperador()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("MESÁRIO:", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Posicione seu dedo POLEGAR ou INDICADOR", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("sobre o sensor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: não habilitar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaDigitalCapturadaOperador()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField("Digital capturada", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Por favor aguarde", api::SPoint{20, 3}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

CRegistraDigitalOperador::CRegistraDigitalOperador()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickCaptura(CThreadOperador::GetInst().AddStoppedTick(15000))
    , m_tickEspera(CThreadOperador::GetInst().AddStoppedTick(50))
    , m_form(TelaRegistraDigitalOperador())
    , m_formCapturada(TelaDigitalCapturadaOperador())
    , m_tentativasRestantes(3)
{
}

CRegistraDigitalOperador& CRegistraDigitalOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegistraDigitalOperador());
    }
    return *s_inst;
}

// (original lines 66-90: content not recovered)
#line 91
void CRegistraDigitalOperador::StartState()
{
    CLogVota::GetInst().LogaSolicitaDigitalMesario();
    m_form->Slot2();
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(2);
    CThreadOperador::GetInst().StartTick(m_tickCaptura);
    CThreadOperador::GetInst().StartTick(m_tickEspera);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot3();
    m_pNextState = this;
}

void CRegistraDigitalOperador::FinishState()
{
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
}

void CRegistraDigitalOperador::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        CThreadOperador::GetInst().StopTick(m_tickCaptura);
        CThreadOperador::GetInst().StopTick(m_tickEspera);
        CLogVota::GetInst().LogaHabilitacaoCanceladaCapturaDigitalMesario();
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota

// (original lines 120-324: content not recovered)
#line 325
// <stubs>
// f3614 · 4765 B · unmatched · name unknown
// ? f3614(i32, i32) { ... }
// </stubs>












































namespace comum::md {

CComparecimentoMesarioPK::CComparecimentoMesarioPK(const CEleitorIdentidade& mesario, int periodoPresente)
    : m_mesario(mesario)
    , m_periodoPresente(periodoPresente)
{
}

} // namespace comum::md
