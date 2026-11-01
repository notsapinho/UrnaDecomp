#pragma once

#include <vector>

#include "app/comum/gravadores/md/cresultadovotacao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaResultadoVotacaoPorEleicao
// (cconversorentidadebu.cpp:164, inlined into target fn 10273), its function-name text at 420752 (ledger/strings.tsv)
// and the record of comum::CGravadorBU::MontaEntidadeBU (cgravadorbu.cpp:636), which takes a const
// std::vector<md::CResultadoVotacaoPorEleicao> &. Recovered: the layout only, 20 bytes: fn 2853 copies the 8 bytes at
// +0 as one 64-bit word and then the vector at +8, so the bytes before the vector are not told apart. The constructors
// are not reconstructed. Chosen: the path, beside cvotosvotavel.h; the 8 bytes as two 32-bit words; every member name,
// the first after ModuloBoletimUrna's ResultadoVotacaoPorEleicao field idEleicao, the vector after its
// resultadosVotacao.
class CResultadoVotacaoPorEleicao {
private:
    uedword m_idEleicao;
    uedword m_naoRecuperado;
    std::vector<CResultadoVotacao> m_resultadosVotacao;
};

} // namespace comum::md
