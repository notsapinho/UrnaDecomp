#pragma once

#include <vector>

#include "app/comum/gravadores/md/cvotoscargo.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaResultadoVotacao (cconversorentidadebu.cpp:132,
// inlined into target fn 10273) and its function-name text at 420905 (ledger/strings.tsv), which take a const
// md::CResultadoVotacao &. Recovered: the layout only, 20 bytes: comum::CGravadorBU::GravaResultado (fn 11629) copies a
// 32-bit word at +0 and a 16-bit word at +4 and the vector at +8 (fn 1556), and fn 2853 copies the same. The
// constructors are not reconstructed. Chosen: the path, beside cvotosvotavel.h; the words' types beyond their widths
// and every member name, after ModuloBoletimUrna::ResultadoVotacao's fields tipoCargo, qtdComparecimento and
// totaisVotosCargo, in their order.
class CResultadoVotacao {
private:
    uedword m_tipoCargo;
    ueword m_qtdComparecimento;
    std::vector<CVotosCargo> m_totaisVotosCargo;
};

} // namespace comum::md
