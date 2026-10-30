// Reconstruction notes: comum::md::CRegraCPF's ValidaDigitoVerificador (target fn 11270) and Formata (fn 11269), slots
// 4 and 3 of its vtable, defined in the target's link order. No record names this file or these members: the path and
// the names are chosen (the fragment's header comment says why). Digitos, Soma and CalculaDV are file-static helpers
// that clang inlines, as in cregratitulo.cpp; their names are chosen. Soma's loop is a choice among forms that give the
// same bytes, which the fragment lists; written in ValidaDigitoVerificador itself, the same loop differs.
#include "app/comum/dados/md/cregracpf.h"

#include <algorithm>
#include <array>
#include <string>

#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

using ecourna::api::util::CStringUtils;

namespace {

std::array<uebyte, 11> Digitos(const std::string& numero)
{
    const std::string cpf = CStringUtils::PreencheAEsquerda(numero, '0', 11);
    std::array<uebyte, 11> digitos;
    std::transform(cpf.begin(), cpf.end(), digitos.begin(), [](char c) { return c - '0'; });
    return digitos;
}

ueword Soma(const std::array<uebyte, 11>& digitos, int n, int peso)
{
    ueword soma = 0;
    for (int i = 0; i < n; ++i)
        soma += digitos[i] * (peso - i);
    return soma;
}

uebyte CalculaDV(ueword soma)
{
    const int resto = soma % 11;
    return resto < 2 ? 0 : 11 - resto;
}

} // namespace

bool CRegraCPF::ValidaDigitoVerificador(const std::string& numero) const
{
    if (numero.size() > 11)
        return false;

    const std::array<uebyte, 11> digitos = Digitos(numero);

    ueword soma = Soma(digitos, 9, 10);
    const uebyte dv1 = CalculaDV(soma);
    if (digitos[9] != dv1)
        return false;

    soma = Soma(digitos, 9, 11) + dv1 * 2;
    return digitos[10] == CalculaDV(soma);
}

std::string CRegraCPF::Formata(const std::string& numero) const
{
    return CStringUtils::PreencheAEsquerda(numero, '0', 11);
}

} // namespace comum::md
