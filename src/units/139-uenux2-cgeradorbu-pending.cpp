// Pending members: the virtual members of comum::CGeradorBU and comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores>
// that src/uenux2/src/app/comum/relatorios/cgeradorbu.cpp and cgeradorbubase.h do not hold yet. CGeradorBU's vtable
// (emitted with its destructor, the key function, in cgeradorbu.cpp's TU) and the base's (emitted there too, with the
// base's destructor) need them defined; their bodies are NOT the target's, they trap. Each moves into its class when it
// is reconstructed; delete this file with the last one. The three base members are explicit specializations of the one
// instance the vtables need (src/units/README.md "Pending members", the template default's case): delete each when the
// template's member is written in cgeradorbubase.h.
// - CGeradorBU::ImprimePreTexto, slot 2, target fn 11256 (1733 B, record cgeradorbu.cpp:257): it walks the vector at
//   +116 after loading the load-code history's title, and it calls fn 160, std::string::append, which this tree's code
//   calls at its -O3 (units 31 and 93 measure it on AddField and DefineHistoricoCarga), and fn 942, which has no body
//   or name of ours (below), so it waits for 942.
// - CGeradorBUBase<...>::ImprimeProporcionalPartido, slot 3, fn 11255 (1749 B, records cgeradorbubase.h:187 and
//   ImprimeVotosCandidatos' 222), and ImprimeMajoritario, slot 4, fn 11254 (1443 B, record :246). Both call fn 942, which
//   holds CCalculaCV::IncluiString's record and calls fn 160, and fn 2271; 11255 calls fns 2272 and 1273 as well. None
//   of the four has a body or a name of ours (`no-candidate` in splat/scan.tsv), so both wait for them.
// - CGeradorBUBase<...>::ImprimeConsulta, slot 5, fn 11253 (2730 B, record :286): it calls fn 160 too, and fn 942
//   twice, and waits for 942.
#include "app/comum/relatorios/cgeradorbu.h"

namespace comum {

template <>
void CGeradorBUBase<CRdvVota, CEleitores>::ImprimeProporcionalPartido() const
{
    __builtin_trap();
}

template <>
void CGeradorBUBase<CRdvVota, CEleitores>::ImprimeMajoritario() const
{
    __builtin_trap();
}

template <>
void CGeradorBUBase<CRdvVota, CEleitores>::ImprimeConsulta() const
{
    __builtin_trap();
}

void CGeradorBU::ImprimePreTexto() const
{
    __builtin_trap();
}

} // namespace comum
