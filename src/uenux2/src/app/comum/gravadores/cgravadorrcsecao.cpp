// comum::CGravadorRCSecao (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorrcsecao.cpp): CriaIdentidadeEleitor,
// target fn 5845, whose throw is a record of the target (line 230, column 11). The records of LeChavePublica (lines 65,
// 75 and 83, inlined into fn 11616) and GravaResultado (line 110, fn 11616) belong to functions not written; their lines
// stay blank.

#include "app/comum/gravadores/cgravadorrcsecao.h"

#include <format>
#include <memory>

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "ecourna/app/dados/cnumerocpf.hpp"
#include "ecourna/app/dados/cnumeroidentificacaolivre.hpp"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace comum {

// (original lines 19-61: content not recovered)
#line 62
// <stubs>
// f11616 · 15849 B · unmatched · name unknown
// void f11616(i32, i32) { ... }
// </stubs>

// (original lines 67-209: content not recovered)
#line 210
ecourna::app::dados::TSharedIdentificadorEleitor CGravadorRCSecao::CriaIdentidadeEleitor(
    const comum::md::CEleitorIdentidade& identidade) const
{
    switch (identidade.GetTipo()) {
        case ecourna::app::dados::TipoIDInscricaoEleitoral: {
            const ecourna::app::dados::CNumeroInscricaoEleitoral numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(numero);
        }
        case ecourna::app::dados::TipoIDCPF: {
            const ecourna::app::dados::CNumeroCPF numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroCPF>(numero);
        }
        case ecourna::app::dados::TipoIDNumeroLivre: {
            const ecourna::app::dados::CNumeroIdentificacaoLivre numero(identidade.GetIdentificador());
            return std::make_shared<ecourna::app::dados::CNumeroIdentificacaoLivre>(numero);
        }
        default:
            break;
    }

    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8654,
        std::format("Tipo de identidade invalida: {}", static_cast<int>(identidade.GetTipo())));
}

} // namespace comum
