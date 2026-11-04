#pragma once

#include <vector>

#include "app/comum/gravadores/md/cresultadovotacao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaResultadoVotacaoPorEleicao
// (cconversorentidadebu.cpp:164, inlined into target fn 10273), its function-name text at 420752 (ledger/strings.tsv)
// and the record of comum::CGravadorBU::MontaEntidadeBU (cgravadorbu.cpp:636), which takes a const
// std::vector<md::CResultadoVotacaoPorEleicao> &. Recovered: the layout only, 20 bytes: fn 2853 copies the 8 bytes at
// +0 as one 64-bit word and then the vector at +8, and fn 10273 (CConversorEntidadeBU::DoConverte) reads a 32-bit word
// at +0 (the election) and 16-bit words at +4 and +6, which it stores as qtdEleitoresAptosSecao and
// qtdEleitoresAptosTTE, and their 16-bit sum as qtdEleitoresAptos; the getters are what it reads. The constructors are
// not reconstructed. Chosen: the path, beside cvotosvotavel.h; every member and getter name, after ModuloBoletimUrna's
// ResultadoVotacaoPorEleicao fields; that the sum is a getter's (the converter could add the two).
class CResultadoVotacaoPorEleicao {
public:
    uedword GetIdEleicao() const { return m_idEleicao; }
    ueword GetQtdEleitoresAptos() const { return m_qtdEleitoresAptosSecao + m_qtdEleitoresAptosTTE; }
    ueword GetQtdEleitoresAptosSecao() const { return m_qtdEleitoresAptosSecao; }
    ueword GetQtdEleitoresAptosTTE() const { return m_qtdEleitoresAptosTTE; }
    const std::vector<CResultadoVotacao>& GetResultadosVotacao() const { return m_resultadosVotacao; }

private:
    uedword m_idEleicao;
    ueword m_qtdEleitoresAptosSecao;
    ueword m_qtdEleitoresAptosTTE;
    std::vector<CResultadoVotacao> m_resultadosVotacao;
};

} // namespace comum::md
