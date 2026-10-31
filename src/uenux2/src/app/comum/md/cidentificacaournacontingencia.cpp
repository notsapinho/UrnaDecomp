// Reconstruction: comum::md::CIdentificacaoUrnaContingencia's constructor (target fn 5888). Its one record (line 32,
// column 19) is loaded by no function of the target: both callers (fns 11452 and 12098) pass the type 50, binaryen
// folds the argument into the body, and the throw that tests it goes with it; its 480-byte frame stays, which this
// file's std::format throw gives. The test written there is chosen (a switch that takes only eUrnaContingencia), and so
// are its code, 8914, the other of the two codes of 8900 to 8927 that no call of fn 591 passes. Its message is the
// target's: the one unread format string of the data that names this urn's type (at 6328).
#include "app/comum/md/cidentificacaournacontingencia.h"

#include <format>

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 15-23: content not recovered)
#line 24
CIdentificacaoUrnaContingencia::CIdentificacaoUrnaContingencia(const EUrnaTipo tipo, const TMunicipioID municipio,
    const TZonaID zona)
    : CIdentificacaoUrna(tipo, municipio, zona)
{
    switch (tipo) {
        case eUrnaContingencia:
            break;
        default:
            throw CUeComumMdError(EUE_COMUM_MD_8914, std::format("Tipo inválido para urna de contingência: {}", static_cast<int>(tipo)));
    }
}

} // namespace comum::md
