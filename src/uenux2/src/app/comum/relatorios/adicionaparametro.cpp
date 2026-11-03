#include "app/comum/relatorios/adicionaparametro.h"

#include "ecourna/api/util/cstringutils.hpp"

using ecourna::api::util::CStringUtils;

namespace comum {

void AdicionaParametro(api::CPaperFormBuilder& builder, const std::string& nome, const std::string& valor)
{
    std::string linha = nome;
    linha += CStringUtils::PreencheAEsquerda(valor, ' ', 38 - nome.size());
    builder.AddTextField(linha, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
}

} // namespace comum
