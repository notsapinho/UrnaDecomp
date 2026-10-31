#include "app/vota/eleitor/comum/ctelascargo.h"

#include <format>

#include "app/vota/euevotaerror.h"

namespace vota {

// (original lines 9-19: content not recovered)
#line 20
std::string NomeTela(const ETelaVotacao tela)
{
    switch (tela) {
    case ETelaVotacao::TELA_INICIAL:
        return "Tela Inicial";
    case ETelaVotacao::TELA_COMPLETA:
        return "Tela Completa";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_NOMINAL:
        return "Tela de Conferência de Voto Nominal";
    case ETelaVotacao::TELA_VOTO_BRANCO:
        return "Tela de Voto Branco";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_BRANCO:
        return "Tela de Conferência de Voto Branco";
    case ETelaVotacao::TELA_VOTO_PROPORCIONAL_NULO_INCOMPLETO:
        return "Tela de Voto Proporcional Nulo Incompleto";
    case ETelaVotacao::TELA_VOTO_NULO:
        return "Tela de Voto Nulo";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_NULO:
        return "Tela de Conferência de Voto Nulo";
    case ETelaVotacao::TELA_PARTIDO:
        return "Tela de Partido";
    case ETelaVotacao::TELA_VOTO_LEGENDA_INCOMPLETO:
        return "Tela de Voto Legenda Incompleto";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_LEGENDA:
        return "Tela de Conferência de Voto Legenda";
    case ETelaVotacao::TELA_CANDIDATO_INEXISTENTE:
        return "Tela de Candidato Inexistente";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INEXISTENTE:
        return "Tela de Conferência de Candidato Inexistente";
    case ETelaVotacao::TELA_CANDIDATO_INAPTO:
        return "Tela de Candidato Inapto";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INAPTO:
        return "Tela de Conferência de Candidato Inapto";
    case ETelaVotacao::TELA_CANDIDATO_REPETIDO:
        return "Tela de Candidato Repetido";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_REPETIDO:
        return "Tela de Conferência de Candidato Repetido";
    case ETelaVotacao::TELA_CARGO_SEM_CANDIDATO:
        return "Tela de Cargo sem Candidato";
    }
    throw CUeVotaError(EUE_VOTA_TELA_INVALIDA, std::format("Tela inválida {}", static_cast<int>(tela)));
}


// <stubs>
// f2386 · 941 B · unmatched · name unknown
// void f2386(i32, i32, i32) { ... }
// </stubs>

// (original lines 69-76: content not recovered)
#line 77
// <stubs>
// f4135 · 1190 B · unmatched · name unknown
// void f4135(i32, i32, i32, i32) { ... }
// </stubs>









} // namespace vota
