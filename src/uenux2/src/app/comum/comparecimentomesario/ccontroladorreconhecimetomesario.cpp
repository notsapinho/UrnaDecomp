// comum (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp): the list of
// the files of the WSQ directory "nao-registrado/" in reverse name order, target fn 5374, and with it the libc++ code
// of its std::sort the target keeps: __introsort (fn 5373), __insertion_sort_incomplete (fn 5370), __sort4 (fn 2726)
// and the comparator (fn 310). No record names fn 5374: its name, its being a free function and its line are chosen,
// and its file is its band's. The records of CControladorReconhecimentoMesario::ComparaDigitais (fn 5372, lines 65
// and 76) are not written. src/units/214-uenux2-app-comum-comparecimentomesario.mk says what each part rests on.

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

#include "app/comum/gravadores/pathwsq.h"

namespace comum {

std::vector<std::filesystem::path> ListaArquivosNaoRegistrados()
{
    const std::filesystem::path diretorio = GetPathWsqNaoRegistrado();
    std::vector<std::filesystem::path> arquivos;
    for (const auto& entrada : std::filesystem::directory_iterator(diretorio)) {
        if (entrada.is_directory()) {
            continue;
        }
        arquivos.push_back(entrada.path().filename());
    }
    std::sort(arquivos.begin(), arquivos.end(),
              [](const std::filesystem::path& a, const std::filesystem::path& b) { return a.string() > b.string(); });
    return arquivos;
}

} // namespace comum

// <stubs>
// f5372 · 720 B · unmatched · name unknown
// ? f5372(i32) { ... }
// </stubs>
