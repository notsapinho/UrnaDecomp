#include "app/vota/eleitor/cinstrucaovotacaoacessibilidade.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CInstrucaoVotacaoAcessibilidade::CInstrucaoVotacaoAcessibilidade()
    : CVotacaoStateAudio(EVENTO_ENTRADA), m_tela(CTelasVota::GetInst().GetTelaInstrucaoVotacaoAcessibilidade())
{
}

CInstrucaoVotacaoAcessibilidade& CInstrucaoVotacaoAcessibilidade::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInstrucaoVotacaoAcessibilidade());
    }
    return *s_inst;
}

std::unique_ptr<CInstrucaoVotacaoAcessibilidade> CInstrucaoVotacaoAcessibilidade::s_inst;
std::mutex CInstrucaoVotacaoAcessibilidade::s_mutex;

CInstrucaoVotacaoAcessibilidade::~CInstrucaoVotacaoAcessibilidade() = default;

// (original lines 27-172: content not recovered)
#line 173
std::string CInstrucaoVotacaoAcessibilidade::GetKeyboardPosition() const
{
    auto& iurna = api::CPolySingleton<api::IUrna>::instance();
    return iurna.Modelo() > 2019 ? "abaixo" : "à direita";
}

std::string CInstrucaoVotacaoAcessibilidade::GetMensagem() const
{
    const std::string posicao = GetKeyboardPosition();
    return "A urna está pronta para receber o seu voto. Use o teclado numérico " + posicao
        + " da urna para digitar o seu voto. Aperte a tecla 4 para fala mais lenta. Aperte a tecla 6 para fala mais rápida. Aperte a tecla 3 para aumentar o volume. Aperte a tecla 9 para diminuir o volume. Aperte confirma para iniciar o seu voto";
}

} // namespace vota
