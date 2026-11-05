// comum::md::CResultadoVotacaoPorEleicao's constructor (no record, no target index of its own). Fn 11629
// (comum::CGravadorBU::GravaResultado), its one caller, holds it as a block whose result is `this`, after its stores,
// and its copy of the vector calls fn 1556 per element: read as an out-of-line function binaryen inlines
// (docs/how-to-decompile.md step 3). Defined in the class instead, fn 11629 differs (src/units/200-uenux2-cgravadorbu.mk
// has both scores). This file's name and path, beside its header, are chosen: no record names them.

#include "app/comum/gravadores/md/cresultadovotacaoporeleicao.h"

namespace comum::md {

CResultadoVotacaoPorEleicao::CResultadoVotacaoPorEleicao(uedword idEleicao, const SQtdeAptos& qtdEleitoresAptos,
    const std::vector<CResultadoVotacao>& resultadosVotacao)
    : m_idEleicao(idEleicao),
      m_qtdEleitoresAptos(qtdEleitoresAptos),
      m_resultadosVotacao(resultadosVotacao)
{
}

} // namespace comum::md
