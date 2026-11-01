#pragma once

#include <string>

#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum::md {

// comum::md::IRegraIdentidade: the rule that checks a voter's identity number of one type (RTTI: a class with no base,
// ledger/classes.json typeinfo @1574684). Its record, md/iregraidentidade.cpp:23 (Valida, inlined into fn 566), names
// this directory; the header's path is chosen beside it. The target has no vtable of its own for the class, and its
// typeinfo lies right after the first derived class's (CRegraIdentidadeLivre's @1574672), where a base whose virtual
// members are all inline or pure has it: so no virtual member is out of line, and whether slots 2 to 4 are pure or
// inline defaults is not recovered (they are declared pure here). The derived vtables are [174, 144, slot 2, slot 3,
// slot 4]: the destructors destroy nothing (fn 174 returns `this`, fn 144 frees it), slot 2 returns the identifier type
// that CValidadorIdentidade::Valida (fn 566) compares with its argument, slot 3 formats a number (PreencheAEsquerda to
// the type's length), slot 4 tests its check digits, and Valida calls it after checking that the number holds only
// digits. No record, symbol or caller names slots 2 to 4: GetTipo, Formata and ValidaDigitoVerificador are chosen from
// those roles. Valida (record iregraidentidade.cpp:23) is inlined into fn 566. EhValida (fn 3723, callers 2803 and 10627)
// holds Valida's test with a bool result, and Valida's body holds it inlined; its name is chosen.
class IRegraIdentidade {
public:
    virtual ~IRegraIdentidade() = default;

    virtual ecourna::app::dados::ETipoIdentificadorEleitor GetTipo() const = 0;
    virtual std::string Formata(const std::string& numero) const = 0;
    virtual bool ValidaDigitoVerificador(const std::string& numero) const = 0;

    bool EhValida(const std::string& numero) const;
    void Valida(const std::string& numero) const;
};

} // namespace comum::md
