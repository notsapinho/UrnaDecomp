// Reconstruction notes: comum::md::CRegraTitulo's Formata (target fn 11271) and ValidaDigitoVerificador (fn 11272),
// slots 3 and 4 of its vtable. No record names this file or these members: the path and the names are chosen (the
// fragment's header comment says why). Digitos and CalculaDV are file-static helpers that clang inlines; their names
// are chosen. That the padded string is a helper's local is measured: written as a scoped local of
// ValidaDigitoVerificador, the frame puts it below the digits instead of above them and 11272 differs.
#include "app/comum/dados/md/cregratitulo.h"

#include <algorithm>
#include <array>
#include <string>

#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

using ecourna::api::util::CStringUtils;

namespace {

std::array<uebyte, 12> Digitos(const std::string& numero)
{
    const std::string titulo = CStringUtils::PreencheAEsquerda(numero, '0', 12);
    std::array<uebyte, 12> digitos;
    std::transform(titulo.begin(), titulo.end(), digitos.begin(), [](char c) { return c - '0'; });
    return digitos;
}

int CalculaDV(ueword soma, int uf)
{
    const int resto = soma % 11;
    if (resto < 2)
        return (uf == 1 || uf == 2) ? 1 - resto : 0;
    return 11 - resto;
}

} // namespace

std::string CRegraTitulo::Formata(const std::string& numero) const
{
    return CStringUtils::PreencheAEsquerda(numero, '0', 12);
}

bool CRegraTitulo::ValidaDigitoVerificador(const std::string& numero) const
{
    if (numero.size() > 12)
        return false;

    const std::array<uebyte, 12> digitos = Digitos(numero);

    const int uf = digitos[8] * 10 + digitos[9];
    if (uf < 1 || uf > 28)
        return false;

    ueword soma = digitos[0] * 9 + digitos[1] * 8 + digitos[2] * 7 + digitos[3] * 6 + digitos[4] * 5 + digitos[5] * 4 +
                  digitos[6] * 3 + digitos[7] * 2;
    if (digitos[10] != CalculaDV(soma, uf))
        return false;

    soma = digitos[8] * 4 + digitos[9] * 3 + digitos[10] * 2;
    return digitos[11] == CalculaDV(soma, uf);
}

} // namespace comum::md
