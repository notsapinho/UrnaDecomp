#pragma once

#include <map>
#include <string>

#include "api/util/cdate.h"
#include "ecourna/app/dados/parametrizacaourna/clabelparametrizado.hpp"

namespace comum::md {

// The records name RecuperaLabel (target fn 5658), TraduzLabel and TraduzTexto; Traduz (fn 654) holds the last two and
// TraduzData inlined by binaryen. No record names Traduz or TraduzData: their names, and which members are public, are
// chosen. The target shows a std::map<char, CLabelParametrizado> in .bss (1839056), with a dynamic initializer and a
// global destructor (fn 11341), and right after it the api::CDate at 1839068, which the same initializer builds with
// CDate's constructor (fn 1382) and TraduzData reads. Their names, and that they are private static members, are chosen.
// SetLabels and SetDataReferencia have no target function: fns 11196 (comum::CRelatorioTesteImpressora::
// InicializaTradutorFrase) and 7787 assign a map to s_labels in their own code, a call of the tree's __assign_multi (fn
// 5794, the map's address folded in), and 7787 stores 8 bytes to s_dataReferencia after it. That these are inline
// setters of the class, and their names, are chosen.
class CTradutorFrase {
public:
    static std::string Traduz(const std::string& frase);
    static const ecourna::app::dados::CLabelParametrizado& RecuperaLabel(const std::string& label);
    static std::string TraduzLabel(const std::string& label);
    static std::string TraduzTexto(const std::string& texto);
    static std::string TraduzData(const std::string& data);
    static void SetLabels(const std::map<char, ecourna::app::dados::CLabelParametrizado>& labels) { s_labels = labels; }
    static void SetDataReferencia(const api::CDate& data) { s_dataReferencia = data; }

private:
    static std::map<char, ecourna::app::dados::CLabelParametrizado> s_labels;
    static api::CDate s_dataReferencia;
};

} // namespace comum::md
