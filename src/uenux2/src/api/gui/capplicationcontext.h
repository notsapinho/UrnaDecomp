#pragma once

// Reconstruction's note, not TSE's text. api::CApplicationContext: the name is the record's, capplicationcontextstack.cpp
// 45:15, `api::CApplicationContextGuard::CApplicationContextGuard(CApplicationContextStack &, CApplicationContext)`,
// which prints it unqualified, so its namespace is chosen, and so are this header's path and every member's,
// function's and parameter's name. That CriaContextoAplicacao, CriaContextoPadrao and Actions are free functions, not
// members, is chosen too (they read no state of the class). src/units/193-uenux2-capplicationcontextstack.mk has the
// rest.

#include <string>
#include <vector>

namespace api {

// A context of the application, read as what an error screen shows of it (a reading: its strings are titles and
// messages, and Actions' lines say what to do): 52 bytes, three strings at +0, +12 and +24, a vector of strings at +36
// and a 32-bit word at +48 (the constructor, target fn 5557, moves its five arguments there in that order; the copy
// constructor, fn 1841, and operator==, fn 5556, read them in that order). The word is 1 in the context
// CriaContextoPadrao builds (fn 5558), 0 in the one CriaContextoAplicacao builds (fn 3682), and Push tests it for
// non-zero: its int type is chosen for that width.
class CApplicationContext {
public:
    CApplicationContext(std::string titulo, std::string descricao, std::string detalhe, std::vector<std::string> acoes,
                        int padrao);

    // Defaulted where capplicationcontext.cpp defines it, beside the constructor.
    bool operator==(const CApplicationContext&) const;

    std::string m_titulo;
    std::string m_descricao;
    std::string m_detalhe;
    std::vector<std::string> m_acoes;
    int m_padrao;
};

// The context of an error of a kind: the three strings, Actions(tipo) and the word 0 (fn 3682).
CApplicationContext CriaContextoAplicacao(int tipo, std::string titulo, std::string descricao, std::string detalhe);

// The context InitApplication pushes first, and the one fn 1695 builds when the stack is empty: the two strings, the
// line to photograph the screen, Actions(1) and the word 1 (fn 5558).
CApplicationContext CriaContextoPadrao(std::string titulo, std::string descricao);

// The lines the error screen shows for each kind of error (fn 5555, 17 cases); for any other value it returns the
// one line "Actions({}) - não reconhecida", which gives the name.
std::vector<std::string> Actions(int tipo);

} // namespace api
