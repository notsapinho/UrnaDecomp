// Pending member: the virtual member of comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores> that
// src/uenux2/src/app/comum/relatorios/cgeradorbubase.h does not hold yet. The base's vtable (emitted in cgeradorbu.cpp's
// TU, with the base's destructor) needs it defined; its body is NOT the target's, it traps. It moves into the class when
// it is reconstructed; delete this file with it. It is an explicit specialization of the one
// instance the vtables need (src/units/README.md "Pending members", the template default's case): delete it when the
// template's member is written in cgeradorbubase.h, as ImprimeProporcionalPartido's and ImprimeMajoritario's are.
// - CGeradorBUBase<...>::ImprimeConsulta, slot 5, fn 11253 (2730 B, record :286): it calls fn 160,
//   std::string::append, which this tree's code calls at its -O3 (units 31 and 93 measure it on AddField and
//   DefineHistoricoCarga), and fn 942 (CCalculaCV::IncluiString, unit 121) twice, and waits for fn 5610, which has no
//   body or name of ours (357, Build, 1881 and 1923, CCargo::GetDetalheConsulta, match).
#include "app/comum/relatorios/cgeradorbu.h"

namespace comum {

template <>
void CGeradorBUBase<CRdvVota, CEleitores>::ImprimeConsulta() const
{
    __builtin_trap();
}

} // namespace comum
