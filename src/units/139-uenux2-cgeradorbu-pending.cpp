// Pending members: the virtual members of comum::CGeradorBU and comum::CGeradorBUBase<comum::CRdvVota, comum::CEleitores>
// that src/uenux2/src/app/comum/relatorios/cgeradorbu.cpp and cgeradorbubase.h do not hold yet. CGeradorBU's vtable
// (emitted with its destructor, the key function, in cgeradorbu.cpp's TU) and the base's (emitted there too, with the
// base's destructor) need them defined; their bodies are NOT the target's, they trap. Each moves into its class when it
// is reconstructed; delete this file with the last one. The three base members are explicit specializations of the one
// instance the vtables need (src/units/README.md "Pending members", the template default's case): delete each when the
// template's member is written in cgeradorbubase.h.
// - CGeradorBU::ImprimePreTexto, slot 2, target fn 11256 (1733 B, record cgeradorbu.cpp:257): it walks the vector at
//   +116 after loading the load-code history's title, and it calls fn 160, std::string::append, which this tree's code
//   calls at its -O3 (units 31 and 93 measure it on AddField and DefineHistoricoCarga), and fn 942,
//   CCalculaCV::IncluiString (unit 121). Its callees 2786 (CRelUtil::GetIDCargaFormatado, unit 123) and 357
//   (api::CPaperFormBuilder::Build, unit 31) match; it passes table slot 3048, fn 11182, to AddTextField (fn 604), and
//   waits for it: CRelUtil::DSCodigoVerificador (record crelutil.cpp:412), not written, which calls fn 3700, a
//   CCalculaCV member of 1946 B over ecourna's CSiphashMac with no body or name of ours.
// - CGeradorBUBase<...>::ImprimeProporcionalPartido, slot 3, fn 11255 (1749 B, records cgeradorbubase.h:187 and
//   ImprimeVotosCandidatos' 222), and ImprimeMajoritario, slot 4, fn 11254 (1443 B, record :246). Both call fn 942,
//   CCandidaturas::ExisteCandidato (2271) and fn 1930, CRdvVota's slot 10 (CRdvVota::Cargo), which our sources declare
//   and do not define: our match line for 1930 names CVotosEleicoesVota::Cargo, a body of the same bytes, so a call of
//   CRdvVota::Cargo has no symbol to link to. 11255 calls GetCandidatosPartido (2272) and Busca (1273) as well. Both
//   wait for CRdvVota::Cargo.
// - CGeradorBUBase<...>::ImprimeConsulta, slot 5, fn 11253 (2730 B, record :286): it calls fn 160 too, and fn 942
//   twice, and waits for fns 1923 and 5610, which have no body or name of ours (357, Build, and 1881 match).
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
