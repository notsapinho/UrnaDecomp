// vota::CEscolheOpcao (/home/rubio/tse/uenux2/src/app/vota/operador/outrasopcoes/cescolheopcao.cpp). This comment is
// the reconstruction's. The file's records are StartState's (fn 10690, not reconstructed), lines 150 to 152; they stay
// blank. The one function written here is COpcaoDS's call operator, which has no record and no target function of its
// own: binaryen inlined it into fn 10685, CDataText<COpcaoDS>::GetText. Its line is a choice, after the records.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

#include <format>

namespace vota {

// (original lines 11-146: content not recovered)
#line 147
// <stubs>
// f10690 · 240 B · unmatched · name unknown
// void f10690(i32) { ... }
// </stubs>









std::string CEscolheOpcao::COpcaoDS::operator()() const
{
    return std::format("{}-{}", m_numero, m_texto());
}

} // namespace vota

// <stubs>
// f10691 · 13 B · unmatched · placement: link order · name unknown
// void f10691(i32) { ... }

// f2752 · 69 B · unmatched · placement: link order · name unknown
// ? f2752(i32) { ... }
// </stubs>
