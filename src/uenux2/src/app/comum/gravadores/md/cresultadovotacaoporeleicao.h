#pragma once

#include <vector>

#include "app/comum/gravadores/md/cresultadovotacao.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Named by the records of comum::asn::CConversorEntidadeBU's CriaResultadoVotacaoPorEleicao
// (cconversorentidadebu.cpp:164, inlined into target fn 10273), its function-name text at 420752 (ledger/strings.tsv)
// and the record of comum::CGravadorBU::MontaEntidadeBU (cgravadorbu.cpp:636), which takes a const
// std::vector<md::CResultadoVotacaoPorEleicao> &. Recovered: the layout, 20 bytes: fn 2853 copies the 8 bytes at +0 as
// one 64-bit word and then the vector at +8, and fn 10273 (CConversorEntidadeBU::DoConverte) reads a 32-bit word at +0
// (the election) and 16-bit words at +4 and +6, which it stores as qtdEleitoresAptosSecao and qtdEleitoresAptosTTE,
// and their 16-bit sum as qtdEleitoresAptos; the getters are what it reads. The constructor (md/cresultadovotacaoporeleicao.cpp)
// is what comum::CGravadorBU::GravaResultado (fn 11629) builds each election's result with: the election's id, the
// comum::SQtdeAptos that its map::at finds for the election's abrangencia, which it copies to +4 as one 32-bit word
// (2-aligned), and the election's std::vector<md::CResultadoVotacao>, copied. +4 is that SQtdeAptos: two 16-bit members
// (src/units/200-uenux2-cgravadorbu.mk has the measurement). Chosen: the path, beside cvotosvotavel.h; every member and
// getter name, after ModuloBoletimUrna's ResultadoVotacaoPorEleicao fields; that the sum is a getter's (the converter
// could add the two); the constructor's parameters beyond what fn 11629 passes.
class CResultadoVotacaoPorEleicao {
public:
    CResultadoVotacaoPorEleicao(uedword idEleicao, const SQtdeAptos& qtdEleitoresAptos,
        const std::vector<CResultadoVotacao>& resultadosVotacao);

    uedword GetIdEleicao() const { return m_idEleicao; }
    ueword GetQtdEleitoresAptos() const
    {
        return m_qtdEleitoresAptos.m_qtdeAptosDaSecao + m_qtdEleitoresAptos.m_qtdeAptosTTE;
    }
    ueword GetQtdEleitoresAptosSecao() const { return m_qtdEleitoresAptos.m_qtdeAptosDaSecao; }
    ueword GetQtdEleitoresAptosTTE() const { return m_qtdEleitoresAptos.m_qtdeAptosTTE; }
    const std::vector<CResultadoVotacao>& GetResultadosVotacao() const { return m_resultadosVotacao; }

private:
    uedword m_idEleicao;
    SQtdeAptos m_qtdEleitoresAptos;
    std::vector<CResultadoVotacao> m_resultadosVotacao;
};

} // namespace comum::md
