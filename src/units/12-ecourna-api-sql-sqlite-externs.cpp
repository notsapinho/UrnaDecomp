// Definitions the api/sql/sqlite units call that belong to api/util/cstringutils.cpp (CStringUtils), until that file
// is reconstructed around them: target fns 5158 (ToLower in place), 1879 (ToLower copy) and 9398 (Replace), compiled
// with the ecourna flags through src/units/12-ecourna-api-sql-sqlite.mk.
// Replace matches. It reads the replacement's size once, before the loop, as the target does; a loop that adds
// para.size() each time gives other code, a while loop over the same hoisted size the same object code.
// ToLower in place maps each character through std::transform: a range-for over the string gives other code (39 rows
// against the target, 8 inserted and 12 deleted), this form 8 rows, all operand-only. It does not match yet: its
// `content-anchor` pair votes the guard (.bss, 1911848), no other body reads a guard, and the self-vote rule asks for one.
// A rule could release it later: 18 of 18 guards sit at one distance from their objects on both sides.
// The copying ToLower does not match either: CSqlResultSet::IndexForColumnName (unit 12's fragment) says why.
#include "ecourna/api/util/cstringutils.hpp"

#include <algorithm>
#include <cctype>
#include <set>

namespace ecourna::api::util {

void CStringUtils::ToLower(std::string& valor)
{
    std::transform(valor.begin(), valor.end(), valor.begin(), [](char caractere) -> char {
        static const std::set<int> acentuadas = {'Ç', 'Á', 'É', 'Í', 'Ó', 'Ú', 'À', 'È', 'Ì', 'Ò', 'Ù', 'Â', 'Ê', 'Î',
                                                 'Ô', 'Û', 'Ã', 'Õ', 'Ñ'};
        if (acentuadas.find(caractere) != acentuadas.end()) {
            return caractere | 32;
        }
        if (isalpha(caractere)) {
            return tolower(caractere);
        }
        return caractere;
    });
}

std::string CStringUtils::ToLower(const std::string& valor)
{
    std::string resultado = valor;
    ToLower(resultado);
    return resultado;
}

void CStringUtils::Replace(std::string& valor, char de, const std::string& para)
{
    const size_t tamanho = para.size();
    for (size_t posicao = valor.find(de); posicao != std::string::npos; posicao = valor.find(de, posicao + tamanho)) {
        valor.replace(posicao, 1, para);
    }
}

} // namespace ecourna::api::util
