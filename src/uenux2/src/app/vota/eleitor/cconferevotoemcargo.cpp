#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/cthreadeleitor.h"

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
    : CVotacaoStateAudio(EVENTO_ENTRADA | EVENTO_TICK),
      m_tickConfere(CriaTickConfere()),
      m_tela(tela)
{
}

IConfereVotoEmCargo::~IConfereVotoEmCargo()
{
    CancelaEsperaConfere();
}

// (original lines 32-59: content not recovered)
#line 60
void IConfereVotoEmCargo::FinishStateAudio()
{
    CancelaEsperaConfere();
}
























































std::string IConfereVotoEmCargo::GetMensagem() const
{
    return "Confira o seu voto.";
}

} // namespace vota
