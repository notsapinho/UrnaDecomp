#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "api/audio/isound.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/iinput.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/euevotaerror.h"

namespace vota {

namespace {

std::optional<uebyte> CriaTickConfere()
{
    const int tempo = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoConfirmacaoVoto();
    if (tempo <= 0) {
        return std::nullopt;
    }
    return CThreadEleitor::GetInst().AddStoppedTick(tempo);
}

} // namespace

IConfereVotoEmCargo::IConfereVotoEmCargo(ETelaVotacao tela)
    : CVotacaoStateAudio(EVENTO_ENTRADA | EVENTO_TICK), m_tickConfere(CriaTickConfere()), m_tela(tela)
{
}

IConfereVotoEmCargo::~IConfereVotoEmCargo()
{
    CancelaEsperaConfere();
}

namespace {

comum::TCargoID GetCargoID()
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_CONFERE_VOTO_EM_CARGO_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    return cargos.GetCurrentCargoID();
}

} // namespace

void IConfereVotoEmCargo::StartStateAudio()
{
    m_pNextState = this;
    if (m_tickConfere) {
        CThreadEleitor::GetInst().StartTick(*m_tickConfere);
        CTelasVota::GetInst().GetTelaCargo(GetCargoID(), m_tela)->Slot2();
        ExecutarAposAudioAtual([this] { FalaMensagem(); });
    } else {
        ExecutarAposAudioAtual([this] { m_pNextState = GetProximoEstado(); });
    }
}

void IConfereVotoEmCargo::FinishStateAudio()
{
    CancelaEsperaConfere();
}

// (original lines 65-77: content not recovered)
#line 78
void IConfereVotoEmCargo::ProcessInputAudio()
{
    auto& teclas = api::CPolySingleton<api::IInputKbd>::instance();
    PlayKey(0);
    teclas.Clear();
}

void IConfereVotoEmCargo::ProcessTickAudio(uebyte tick)
{
    if (m_tickConfere && tick == *m_tickConfere) {
        CThreadEleitor::GetInst().StopTick(*m_tickConfere);
        ExecutarAposAudioAtual([this] { m_pNextState = GetProximoEstado(); });
    }
}

void IConfereVotoEmCargo::ExecutarAposAudioAtual(std::function<void()> acao)
{
    auto& sons = api::CPolySingleton<api::ISound>::instance();
    CancelaEsperaConfere();
    if (sons.Wait([] { return false; })) {
        acao();
        return;
    }
    m_esperaConfere = sons.WaitAsync([this] { return GetNextState() != this; },
                                     [this, acao = std::move(acao)](bool terminou) {
                                         m_esperaConfere.reset();
                                         if (terminou && GetNextState() == this) {
                                             acao();
                                         }
                                     });
}











std::string IConfereVotoEmCargo::GetMensagem() const
{
    return "Confira o seu voto.";
}

} // namespace vota
