#pragma once

#include "api/util/cdate.h"

namespace comum::md {

// Recovered: the layout only, 20 bytes, and the constructor's parameters, from its record (chorarioverao.cpp:29):
// fn 11384 holds the constructor, inlined by binaryen (a second stack-pointer prologue), which stores the two dates at
// +0 and +8 and the int at +16. The class is trivially
// copyable: the constructors that keep one in a std::optional copy it with two i64.store and one i32.store (fn 5674).
// The constructor stays declared only: chorarioverao.cpp is not written. The member names are not in the target.
class CHorarioVerao {
public:
    CHorarioVerao(const api::CDate& inicio, const api::CDate& fim, int diferenca);

private:
    api::CDate m_inicio;
    api::CDate m_fim;
    int m_diferenca;
};

} // namespace comum::md
