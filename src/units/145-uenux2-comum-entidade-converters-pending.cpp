// Pending members: comum::asn::CConversorCabecalhoEntidade's two slots, DoConverte and DoDesconverte, target fns 11589
// and 11588 (vtable @1556732, slots 2 and 3; records app/comum/asn/cconversorcabecalhoentidade.cpp:35 and :56). Their
// stubs were the last of that stub-only file, which goes with them while these traps fill the slots: writing the
// members writes the file again, laid out on those two lines. DoConverte builds the entity's DataHoraJE through fn
// 1080, which calls fns 706 and 779; DoDesconverte calls fn 1713 and md::CCabecalhoEntidade's constructor, fn 1945.
// Unit 145's converter of the parties' entity builds this converter (fns 11458 and 11457), so its vtable must link; its
// key function is pending, so the vtable is emitted here. The bodies are NOT the target's, they trap. Move both into
// cconversorcabecalhoentidade.cpp when they are reconstructed; delete this file with them.
#include "app/comum/asn/cconversorcabecalhoentidade.h"

namespace comum::asn {

CConversorCabecalhoEntidade::TEntidade CConversorCabecalhoEntidade::DoConverte(const TDado&) const
{
    __builtin_trap();
}

md::CCabecalhoEntidade CConversorCabecalhoEntidade::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
