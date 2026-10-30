// Reconstruction notes: comum::md::CRegraCPF's Formata (target fn 11269) and ValidaDigitoVerificador (fn 11270), slots
// 3 and 4 of its vtable. No record names this file or these members: the path and the names are chosen (the fragment's
// header comment says why). Digitos and CalculaDV are file-static helpers that clang inlines, as in cregratitulo.cpp;
// their names are chosen.
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

uebyte CalculaDV(ueword soma)
{
    const int resto = soma % 11;
    return resto < 2 ? 0 : 11 - resto;
}

} // namespace

std::string CRegraCPF::Formata(const std::string& numero) const
{
    return CStringUtils::PreencheAEsquerda(numero, '0', 11);
}

bool CRegraCPF::ValidaDigitoVerificador(const std::string& numero) const
{
    if (numero.size() > 11)
        return false;

    const std::array<uebyte, 11> digitos = Digitos(numero);

    ueword soma = digitos[0] * 10 + digitos[1] * 9 + digitos[2] * 8 + digitos[3] * 7 + digitos[4] * 6 + digitos[5] * 5 +
                  digitos[6] * 4 + digitos[7] * 3 + digitos[8] * 2;
    const uebyte dv1 = CalculaDV(soma);
    if (digitos[9] != dv1)
        return false;

    soma = digitos[0] * 11 + digitos[1] * 10 + digitos[2] * 9 + digitos[3] * 8 + digitos[4] * 7 + digitos[5] * 6 +
           digitos[6] * 5 + digitos[7] * 4 + digitos[8] * 3 + dv1 * 2;
    return digitos[10] == CalculaDV(soma);
}

} // namespace comum::md
