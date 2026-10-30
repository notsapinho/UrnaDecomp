// comum::md::CTradutorFrase: RecuperaLabel, the record at line 95 col 15. The reconstruction's own note; the blank lines
// stand for text not recovered, and which functions the original held above and below the throw is not known.
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

std::map<char, ecourna::app::dados::CLabelParametrizado> CTradutorFrase::s_labels;

// (original lines 11-89: content not recovered)
#line 90
const ecourna::app::dados::CLabelParametrizado& CTradutorFrase::RecuperaLabel(const std::string& label)
{
    const char token = label.at(0);
    const auto it = s_labels.find(token);
    if (it == s_labels.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8128, "Token inválido: " + label);
    }
    return it->second;
}

} // namespace comum::md

// <stubs>
// f654 · 4752 B · unmatched · name unknown
// void f654(i32, i32) { ... }
// </stubs>
