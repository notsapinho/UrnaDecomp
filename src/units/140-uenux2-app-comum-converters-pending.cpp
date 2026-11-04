// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet. Their
// bodies are NOT the target's; they trap.
// - CConversorEleicoesVota::DoDesconverte (slot 3, fn 11349, records cconversoreleicoesvota.cpp:69, :74, :94 and :104),
//   not written: it builds md::CVotosEleicoesVota's maps from the entity (5054 B); of its direct callees, 3869 matches
//   (unit 110's object, kept out of line by unit 280's roots), 5681 is written and differs (15 over 167 rows by pnpm
//   wasm score, fragment 13), and md::CVotosCargos' and md::CVotosEleicoesVota's constructors (5643, 5640) match.
//   5681 and unit 197's 4454 wait for it (docs/reference/facts/app-flags.md F6); our link takes its copy of 5681 from
//   md/rdv/cvotoscargos.cpp.o, which build/out/wasm/vota_web/link.cmd lists ahead of cconversoreleicoesvota.cpp.o, so
//   writing 11349 here brings this object's copy only with the object moved ahead of md/rdv/ (a reading: the link
//   keeps the first object's copy; the target's data hold this file's records before md/rdv/'s).
#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"

namespace comum::asn {

CConversorEleicoesVota::TDado CConversorEleicoesVota::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
