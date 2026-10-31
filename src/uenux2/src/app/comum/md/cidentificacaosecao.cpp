// Reconstruction: comum::md::CIdentificacaoSecao's constructor (target fn 5887); its records (lines 38 and 41, column 15)
// place the throws. The record at line 33, column 19, is loaded by no function of the target: both callers (fns 11453
// and 12098) pass the type 49, binaryen folds the argument into the body, and the throw that tests it goes with it. The
// test written there is chosen (a switch that takes only eUrnaVota), and so are its code, 8915, next to this file's 8916
// and 8917 and one of the two codes of 8900 to 8927 that no call of fn 591 passes. Its message is the target's: the
// one unread string of the data that names this urn's type (at 361994), plain, as the 48-byte frame wants.
#include "app/comum/md/cidentificacaosecao.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 13-24: content not recovered)
#line 25
CIdentificacaoSecao::CIdentificacaoSecao(const EUrnaTipo tipo, const TMunicipioID municipio, const TZonaID zona,
    const TLocalID local, const TSecaoID secao)
    : CIdentificacaoUrna(tipo, municipio, zona), m_local(local), m_secao(secao)
{
    switch (tipo) {
        case eUrnaVota:
            break;
        default:
            throw CUeComumMdError(EUE_COMUM_MD_8915, "Tipo inválido para urna de seção.");
    }


    if (local > 9999) {
        throw CUeComumMdError(EUE_COMUM_MD_8916, "Local inválido.");
    }
    if (secao < 1 || secao > 9999) {
        throw CUeComumMdError(EUE_COMUM_MD_8917, "Seção inválida.");
    }
}

} // namespace comum::md
