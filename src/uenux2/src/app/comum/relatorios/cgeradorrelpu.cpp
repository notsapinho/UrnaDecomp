// comum::CGeradorRelPU: AdicionaParametro (target fn 677), a line of a parameter's name with its value right-aligned to
// 38 columns. Reconstruction's note: no record names this file or the function; cgeradorrelpu.h says what is chosen.
#include "app/comum/relatorios/cgeradorrelpu.h"

#include "ecourna/api/util/cstringutils.hpp"

using ecourna::api::util::CStringUtils;

namespace comum {

void CGeradorRelPU::AdicionaParametro(const std::string& nome, const std::string& valor)
{
    std::string linha = nome;
    linha += CStringUtils::PreencheAEsquerda(valor, ' ', 38 - nome.size());
    m_builder.AddTextField(linha, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

} // namespace comum
