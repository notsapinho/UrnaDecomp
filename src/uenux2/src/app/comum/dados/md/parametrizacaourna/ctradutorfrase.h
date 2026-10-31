#pragma once

#include <map>
#include <string>

#include "ecourna/app/dados/parametrizacaourna/clabelparametrizado.hpp"

namespace comum::md {

// Only RecuperaLabel (target fn 5658) is declared; TraduzLabel and TraduzTexto (the file's other records) are not
// reconstructed. The target shows a std::map<char, CLabelParametrizado> in .bss (1839056), with a dynamic initializer
// and a global destructor (fn 11341). Its name, and that it is a private static member, are chosen. SetLabels has no
// target function: fns 11196 (comum::CRelatorioTesteImpressora::InicializaTradutorFrase) and 7787 assign a map to it
// in their own code, a call of the tree's __assign_multi (fn 5794, the map's address folded in). That this is an
// inline setter of the class, and its name, are chosen.
class CTradutorFrase {
public:
    static const ecourna::app::dados::CLabelParametrizado& RecuperaLabel(const std::string& label);
    static void SetLabels(const std::map<char, ecourna::app::dados::CLabelParametrizado>& labels) { s_labels = labels; }

private:
    static std::map<char, ecourna::app::dados::CLabelParametrizado> s_labels;
};

} // namespace comum::md
