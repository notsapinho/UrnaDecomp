#include "app/vota/eleitor/cinstrucaovotacaoacessibilidade.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"

namespace vota {

CInstrucaoVotacaoAcessibilidade::~CInstrucaoVotacaoAcessibilidade() = default;

// <stubs>
// f4420 · 141 B · unmatched · placement: link order · name unknown
// ? f4420() { ... }
// </stubs>

// (original lines 14-172: content not recovered)
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
