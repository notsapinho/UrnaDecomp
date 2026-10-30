#pragma once

#include <map>
#include <string>

#include "ecourna/app/dados/parametrizacaourna/clabelparametrizado.hpp"

namespace comum::md {

// Only RecuperaLabel (target fn 5658) is declared; TraduzLabel and TraduzTexto (the file's other records) are not
// reconstructed. The target shows a std::map<char, CLabelParametrizado> in .bss (1839056), with a dynamic initializer
// and a global destructor (fn 11341). Its name, and that it is a private static member, are chosen.
class CTradutorFrase {
public:
    static const ecourna::app::dados::CLabelParametrizado& RecuperaLabel(const std::string& label);

private:
    static std::map<char, ecourna::app::dados::CLabelParametrizado> s_labels;
};

} // namespace comum::md
