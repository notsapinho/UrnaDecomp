// vota::CEscolheOpcao (/home/rubio/tse/uenux2/src/app/vota/operador/outrasopcoes/cescolheopcao.cpp). This comment is
// the reconstruction's. The file's records are StartState's (fn 10690, not reconstructed), lines 150 to 152; they stay
// blank. Written here: the destructor (fns 2752 and 10691), whose line is a choice before the records, in its use band's
// order, and COpcaoDS's call operator, which has no record and no target function of its own: binaryen inlined it into
// fn 10685, CDataText<COpcaoDS>::GetText. Its line is a choice, after the records.
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

#include <format>

namespace vota {

// (original lines 12-139: content not recovered)
#line 140
CEscolheOpcao::~CEscolheOpcao() = default;



















std::string CEscolheOpcao::COpcaoDS::operator()() const
{
    return std::format("{}-{}", m_numero, m_texto());
}

} // namespace vota
