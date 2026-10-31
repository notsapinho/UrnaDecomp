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
// compared with 1 gives the same rows: docs/reference/facts/reading.md R14).
//
// CPadDS<CToUpperDS<CCargoDSNome>> is 16 bytes: fn 3699 builds one ({38, '-', 0, table slot 2920}) and passes its address
// to fn 5613, which copies it as two i64 into its CDataText at +8. fn 11247, that CDataText's GetText, holds the call
// operators inlined: it gets CCargoDSNome's text with the ESexo at +16 of the CDataText (+8 of the CPadDS), calls the
// function pointer at +20 on it (slot 2920 is fn 3509, an in-place upper-casing of ecourna's with a table of accented
// letters), and when the text is shorter than the size_t at +8 returns it with the char at +12 repeated before it
// (half the difference, rounded down) and after it (the rest). So CPadDS holds a width, a fill char and its source, and
// CToUpperDS its source and that pointer. Recovered: the layout and the bodies; the member names, the width's type
// beyond its 32 bits and the pointer's type beyond the call 11247 makes are chosen. The operators are inline here
// because 11247 holds them; 11247 differs in our link (src/units/129-uenux2-ccargods.mk says how).
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
    std::string operator()() const
    {
        std::string texto = m_fonte();
        m_converte(texto);
        return texto;
    }

private:
    TFonte m_fonte;
    void (*m_converte)(std::string&);
};

template <typename TFonte>
class CPadDS {
public:
    std::string operator()() const
    {
        std::string texto = m_fonte();
        if (m_tamanho <= texto.size()) {
            return texto;
        }
        const size_t falta = m_tamanho - texto.size();
        const size_t metade = falta / 2;
        const std::string esquerda(metade, m_preenchimento);
        const std::string direita(falta - metade, m_preenchimento);
        return esquerda + texto + direita;
    }

private:
    size_t m_tamanho;
    char m_preenchimento;
    TFonte m_fonte;
};

} // namespace comum
