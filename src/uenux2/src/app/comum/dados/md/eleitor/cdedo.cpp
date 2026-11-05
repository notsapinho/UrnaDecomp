// Reconstruction: comum::md::CDedo's constructor, which comum::asn::CConversorDedo's slot 3 (target fn 11416) holds
// inlined by binaryen behind a frame of its own; its records lie in this file's run of the data (@1572412, @1572428),
// and place the throws, line 28 and line 33, column 15. Every other line of this file, and the literal 200, are chosen.
#include "app/comum/dados/md/eleitor/cdedo.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 12-23: content not recovered)
#line 24
CDedo::CDedo(TipoDedo tipo, uedword quantidadeMinucias, const std::vector<api::SXYT>& minucias)
    : m_tipo(tipo), m_quantidadeMinucias(quantidadeMinucias), m_minucias(minucias)
{
    if (quantidadeMinucias > 200) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8061, std::format("Quantidade de minúcias menor que 0 ou maior que o maior valor aceito: {}", quantidadeMinucias));
    }


    if (minucias.empty() || minucias.size() > 200) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8062, std::format("Conjunto de minúcias vazia ou maior que o maior valor aceito: {}", minucias.size()));
    }
}

} // namespace comum::md
