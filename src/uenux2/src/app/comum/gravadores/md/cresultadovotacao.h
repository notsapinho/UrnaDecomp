#pragma once

#include <vector>

#include "app/comum/gravadores/md/cvotoscargo.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaResultadoVotacao (cconversorentidadebu.cpp:132,
// inlined into target fn 10273) and its function-name text at 420905 (ledger/strings.tsv), which take a const
// md::CResultadoVotacao &. Recovered: the layout, 20 bytes: comum::CGravadorBU::GravaResultado (fn 11629) copies a
// 32-bit word at +0 and a 16-bit word at +4 and the vector at +8 (fn 1556), and fn 2853 copies the same; and the
// constructor (fn 3824, out of line in cresultadovotacao.cpp), which stores its first argument at +0 (i32.store), its
// second at +4 (i32.store16) and copies the vector it is given by reference to +8 (fn 1556, the vector's copy). The
// implicit copy and move constructors are the ones std::vector<CResultadoVotacao>'s push_back of a copy holds in its
// __emplace_back_slow_path (fn 3817): it copies the new element's vector (fn 1556) and moves the old ones' (their three
// words taken, the source's zeroed). Chosen: the path, beside cvotosvotavel.h; the words' types beyond their widths, the constructor's parameter
// types beyond what it stores, and every member and parameter name, after ModuloBoletimUrna::ResultadoVotacao's fields
// tipoCargo, qtdComparecimento and totaisVotosCargo, in their order.
class CResultadoVotacao {
public:
    CResultadoVotacao(uedword tipoCargo, ueword qtdComparecimento, const std::vector<CVotosCargo>& totaisVotosCargo);

private:
    uedword m_tipoCargo;
    ueword m_qtdComparecimento;
    std::vector<CVotosCargo> m_totaisVotosCargo;
};

} // namespace comum::md
