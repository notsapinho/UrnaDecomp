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
// trivially copyable). The constructor from the three members is held by fn 3819 (comum::MontaVotosCargos), which
// binaryen inlines, its `this` returned through a block result there (docs/how-to-decompile.md step 3): written out of
// line, in md/cvotoscargo.cpp, whose path is chosen beside this header; the vector is copied, so a const reference, and
// the parameters' types follow the members'. Chosen: the path, beside cvotosvotavel.h; the two bytes'
// types beyond their width and every member name, after ModuloBoletimUrna::TotalVotosCargo's fields codigoCargo,
// ordemImpressao and votosVotaveis, in their order. The getters are what fn 10273 (CConversorEntidadeBU::DoConverte)
// reads, the code and the order by value (it copies the code to pass it by reference); their names are chosen.
class CVotosCargo {
public:
    CVotosCargo(TCargoID codigoCargo, uebyte ordemImpressao, const std::vector<CVotosVotavel>& votosVotaveis);

    TCargoID GetCodigoCargo() const { return m_codigoCargo; }
    uebyte GetOrdemImpressao() const { return m_ordemImpressao; }
    const std::vector<CVotosVotavel>& GetVotosVotaveis() const { return m_votosVotaveis; }

private:
    TCargoID m_codigoCargo;
    uebyte m_ordemImpressao;
    std::vector<CVotosVotavel> m_votosVotaveis;
};

} // namespace comum::md
