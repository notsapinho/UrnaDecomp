// Roots: api::CDataMap<KeyType, RecordType> (api/io/cdatamap.h), a class template, and the std::map members its users
// reach, the way the target reaches them. The list below names each function's target callers; the stand-ins over the
// maps' GetCurrent and Next went as those callers came into the link, and only ContaEleitor is left. This object
// compiles at the tree's flags, so no match rests on a flag its tree lacks; fragment 113 says what that decides.
// src/api/'s own objects drop -fno-strict-aliasing (src/Makefile UENUX2_TBAA_DIRS); the four bodies this object
// supplied, 1283, 3697, 3741 and 5611, are the same without it (wasm-objdump -d of the object compiled both ways). It
// supplies none of them now: 1283, 3697 and 5611 come from the first objects on the link line to instantiate them: 1283
// from cpartidos.cpp's (for comum::SiglaPartidoCorrente, 11501), 3697 and 5611 from cgeradorbu.cpp's (for unit 139's
// 11254 and 11255). 3741 comes from cjustificador.cpp's object, whose Justifica (held by unit 283's 10590) is its first
// user on the link line. Each function here has two call sites or more, as each has in the target, so binaryen keeps it
// out of line:
// - GetCurrent, four instantiations: 656 (19 callers), 1200 (7, all in the link: 2268, 2838, 5604, 6999, 11254, 11972
//   and 11973), 1283 (9, all in the link: 5604, 11181, 11213, 11255, 11260, 11261, 11499, 11501 and 11976), 3125 (4,
//   all in the link). All four in the link are what makes binaryen form 2919: the second parameter of that body is the
//   pair's second member's offset, 32 or 20.
// - Next, three: 3697 (5604, 11213 and 11255, all in the link), 5601 (12105 and 11206, both in the link), 5611 (5604
//   and 11254, both in the link), which form 3892. The stand-ins over the candidaturas' map went with 5604 (unit 155's
//   written Gera) in the link, those over the voters' map with 12105 (fragment 372's), and those over the parties' map
//   (AvancaUm and AvancaDois) with 11499 (unit 109's comum::NumeroPartidoCorrente), the last of 1283's callers.
//   The fourth record's instance is inlined into 12105, not instantiated here; nor is CRespostaConsulta's (no record).
// - find<CNumeroInscricaoEleitoral>, 3741, needs no stand-in: its target callers 5725, 10587 and 10590 are in the link.
//   Add over this key, 5725 (6734, 10590), and the copy of the pair's second member, 3743 (5725, 6734, 10590): 10590
//   (unit 283, through comum::CJustificador::Justifica), 5725 and 6734 (fragment 386) are in the link: no stand-in.
//   cjustificador.cpp's object is ahead of this one on the link line, so 5725 is its copy, as in the target (its
//   record lies in that object's data); fragment 113 says why it matches only with strict aliasing there.
// - CRegistradorMesario::Registra, 5378, has its two call sites in 10337 (unit 135, in the link). Add(KeyType,
//   RecordType), 5377 (5378, 6734), and the insert of the second map, 5379 (5378, 6734): both callers are in the link
//   (6734, fragment 386's, holds CRegistradorMesario::Carrega), and the stand-in for 6734 went.
// - find<CEleitorIdentidade> and __find_equal<CEleitorIdentidade>, 1703 (2225, 2264, 3614, 5378, 10842) and 860 (2805,
//   3728, 5379, 6734, 7787, 10842): these bodies do not depend on the mapped type, so a std::map<CEleitorIdentidade,
//   int> stands for the callers not written (2225 and 2264 are, units 50 and 110, 3614, unit 221, 3728, fragment
//   225, 2805, fragment 310, and 6734, fragment 386), and binaryen merges the copies.
// - comum::CJustificador's constructor, 3742 (1391 and 11474, both in the link, 11474 through fragment 372): its two
//   call sites keep it out of line; it stores CJustificadorServico's vptr, the reference the target has to that vtable.
//   Its stand-in went with 11474.
// - CRegistradorMesario::GetInst, 815 (ten callers; 10795, 10313, 10337, 5387, 10368, 3614 and 10451 are in the
//   link), its counts
//   3606 and 2727 (called by 10795 and by 5387 and 10368, the data sources' slot 2, in the link with unit 104's 10388,
//   and both by 12105), and HasInst, 2221 (11616, 12105): both callers are in the link (unit 122's 11616 calls it
//   three times, fragment 372's 12105 twice), and the stand-in for 12105 went.
// A stand-in goes once our link holds the calls of the target callers it names, matched or not (src/units/README.md).
#include <map>

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace {

// Stands for 10842 (2225, 2264 and 3614 are in the link), which searches and inserts in another tree of this key.
__attribute__((noinline)) int ContaEleitor(std::map<comum::md::CEleitorIdentidade, int>& mapa,
                                           const comum::md::CEleitorIdentidade& eleitor)
{
    if (mapa.find(eleitor) != mapa.end()) {
        return 17;
    }
    mapa[eleitor] = 19;
    return 23;
}

const void* volatile w113_sink;

struct SW113Roots {
    SW113Roots()
    {
        w113_sink = reinterpret_cast<const void*>(&ContaEleitor);
    }
} w113_roots;

} // namespace
