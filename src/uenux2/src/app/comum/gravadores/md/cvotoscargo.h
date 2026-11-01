#pragma once

#include <vector>

#include "app/comum/dados/md/rdv/cvotoscargos.h"
#include "app/comum/gravadores/md/cvotosvotavel.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaVotosCargo (cconversorentidadebu.cpp:110, inlined into
// target fn 10273) and its function-name text at 418762 (ledger/strings.tsv), which take a const md::CVotosCargo &.
// Recovered: the layout only, 16 bytes: fn 3819 stores a byte at +0 and one at +1 and builds the vector at +4, and fn
// 2853 copies the two bytes as one 16-bit word and the vector, whose 24-byte elements it copies whole (CVotosVotavel is
// trivially copyable). The constructors are not reconstructed. Chosen: the path, beside cvotosvotavel.h; the two bytes'
// types beyond their width and every member name, after ModuloBoletimUrna::TotalVotosCargo's fields codigoCargo,
// ordemImpressao and votosVotaveis, in their order.
class CVotosCargo {
private:
    TCargoID m_codigoCargo;
    uebyte m_ordemImpressao;
    std::vector<CVotosVotavel> m_votosVotaveis;
};

} // namespace comum::md
