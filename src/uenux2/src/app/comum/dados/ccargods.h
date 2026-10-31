#pragma once

#include <string>

#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// Data sources of a position's texts (RTTI, in the arguments of api::CDataText). A source is callable, as api::CDataText
// calls it. The records name CCargoDSNomeSexoCandidato's call operator and the file, ccargods.cpp; CCargoDSNome's call
// operator has no target function of its own: fn 11247 holds it inlined, with a second frame (binaryen's inlining of a
// function of its own, docs/reference/facts/reading.md R10) and its own function name's literal, so it is written out of
// line in ccargods.cpp. Its member is the ESexo 11247 passes to GetNomeCargoComGenero (the word at +16 of the CDataText). CCargoDSNomeSexoCandidato's two bytes are fn 2268's: +0 the substitute's order it passes
// on, +1 the flag that asks for the short name of a long one. The members' names and the flag's type are chosen (a byte
// compared with 1 gives the same rows: docs/reference/facts/reading.md R14). fn 5613 copies a
// CPadDS<CToUpperDS<CCargoDSNome>> as 16 bytes, whose fields are not recovered. So m_fonte in the two wrappers is chosen,
// the member and its name, a reading of what a wrapper holds: no body read shows it, and it does not give those 16 bytes.
class CCargoDSNome {
public:
    std::string operator()() const;

private:
    md::CSexo::ESexo m_sexo;
};

class CCargoDSNomeSexoCandidato {
public:
    std::string operator()() const;

private:
    uebyte m_suplente;
    bool m_abreviaNomeLongo;
};

// The report labels of the current position: the records name the class and its three static members (ccargods.cpp
// lines 98, 113 and 128). The bodies read the position's CCargos and pick one of two texts by whether it is a consulta.
class CCargoDSLabelRelatorio {
public:
    static std::string HeaderDetalhe();
    static std::string HeaderDetalheZE();
    static std::string TotalVotoNominal();
};

template <typename TFonte>
class CToUpperDS {
public:
    std::string operator()() const;

private:
    TFonte m_fonte;
};

template <typename TFonte>
class CPadDS {
public:
    std::string operator()() const;

private:
    TFonte m_fonte;
};

} // namespace comum
