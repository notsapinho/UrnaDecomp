// Pending member: the virtual member of comum::CRelatorioTesteImpressora that
// src/uenux2/src/app/comum/relatorios/crelatoriotesteimpressora.cpp does not hold yet. The class's vtable (emitted with
// EhTreinamento, its key function, in that TU) needs it defined; its body is NOT the target's, it traps. It moves into
// the class's .cpp when it is reconstructed; delete this file then.
// - GetConteudoQRCode, slot 5, fn 11200 (330 B): builds a vector of string pairs from the general state (fn 5636, 3903 B),
//   copies it (fn 1300), adds one tag of two by a switch on 1 (fn 5783) and turns it into the string (fn 5782, 2390 B).
//   It waits for 5636, 5782 and 5783, none named or written.
#include "app/comum/relatorios/crelatoriotesteimpressora.h"

namespace comum {

std::string CRelatorioTesteImpressora::GetConteudoQRCode() const
{
    __builtin_trap();
}

} // namespace comum
