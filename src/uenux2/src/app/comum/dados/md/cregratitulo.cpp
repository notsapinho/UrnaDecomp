// Reconstruction notes: comum::md::CRegraTitulo's ValidaDigitoVerificador (target fn 11272) and Formata (fn 11271),
// slots 4 and 3 of its vtable, defined in the target's link order. No record names this file or these members: the path
// and the names are chosen (the fragment's header comment says why). Digitos, Soma and CalculaDV are file-static
// helpers that clang inlines; their names are chosen. That the padded string is a local of an inlined function is
// measured: written as a scoped local of ValidaDigitoVerificador, the frame puts it below the digits instead of above
// them and 11272 differs. Soma's loop is a choice among forms that give the same bytes, which the fragment lists.
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

ueword Soma(const std::array<uebyte, 12>& digitos, int n, int peso)
{
    ueword soma = 0;
    for (int i = 0; i < n; ++i)
        soma += digitos[i] * (peso - i);
    return soma;
}

int CalculaDV(ueword soma, int uf)
{
    const int resto = soma % 11;
    if (resto < 2)
        return (uf == 1 || uf == 2) ? 1 - resto : 0;
    return 11 - resto;
}

} // namespace

bool CRegraTitulo::ValidaDigitoVerificador(const std::string& numero) const
{
    if (numero.size() > 12)
        return false;

    const std::array<uebyte, 12> digitos = Digitos(numero);

    const int uf = digitos[8] * 10 + digitos[9];
    if (uf < 1 || uf > 28)
        return false;

    ueword soma = Soma(digitos, 8, 9);
    if (digitos[10] != CalculaDV(soma, uf))
        return false;

    soma = digitos[8] * 4 + digitos[9] * 3 + digitos[10] * 2;
    return digitos[11] == CalculaDV(soma, uf);
}

std::string CRegraTitulo::Formata(const std::string& numero) const
{
    return CStringUtils::PreencheAEsquerda(numero, '0', 12);
}

} // namespace comum::md
