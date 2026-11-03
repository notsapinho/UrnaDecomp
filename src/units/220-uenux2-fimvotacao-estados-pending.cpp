// Pending of unit 220: the slots of its states not reconstructed, with trapping bodies so that the vtables link.
// - vota::CGeraBU::StartState (slot 2, target fn 12110, 17349 B, record cgerabu.cpp:54).
// - vota::CGeraRelatorios::StartState (slot 2, fn 12105, 18808 B, record cgerarelatorios.cpp:51).
// - vota::CCopiaResultadoParaMR::StartState (slot 2, fn 12134, 5966 B, records ccopiaresultadoparamr.cpp:59 and, for
//   CopiaResultado, which it holds inlined, :85, :94, :112, :126 and :174).
// Each calls functions with no name (no line in splat/matched.txt or splat/symbol_addrs.txt; imports aside): 12110 and
// 12105 fns 1047, 1541 and 1543 among them (1156 has a name now: unit 296; 12105 also
// builds the std::function of comum::(anonymous)::MontaCabecalho's lambda, whose __func members 11236 to 11239
// wait for it); 12134 none now (3978, 5575, 5896 and 2762 have names: units 116, 179, 35 and 32). Each of the
// three calls fn 491 too, named now (unit 205). 12134 stays a trap whatever its source: it reads three statics no other
// target function reads (/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])' build/out/splat/pieces/asm prints its
// piece alone): api::CSystem::AreFilesEqual's two 32768-byte buffers at 1839328 and 1872096 (zero-filled: the target's
// initialized data ends at 1811674), whose names only its own vote could give, which docs/reference/splat.md section
// 3, "No circular evidence", refuses for a .bss object; and its file's DepuraInfo word at 1540224 (.data, -1), which
// content cannot place (fn 5574's row reads so for cvalidamidia.cpp's word) and only a seed pair's vote would name.
// Their record lines in those files stay blank, past each file's end. The stubs of two went with these traps (a pending
// member has no stub): 12110's in the gap of app/comum/relatorios/ccalculacv.cpp at line 55 (a record of an inlined
// callee, ccalculacv.cpp:58), and 12105's in app/comum/relatorios/cgeradorbuj.cpp, a stub-only file that went with it
// (its record cgeradorbuj.cpp:189, comum::CGeradorBUJ::GeraBUJ, inlined); writing 12105 writes that file again. Move
// each into its file when it is reconstructed, and delete this file with the last.
#include "app/vota/eleitor/fimvotacao/ccopiaresultadoparamr.h"
#include "app/vota/eleitor/fimvotacao/cgerabu.h"
#include "app/vota/eleitor/fimvotacao/cgerarelatorios.h"

namespace vota {

void CGeraBU::StartState()
{
    __builtin_trap();
}

void CGeraRelatorios::StartState()
{
    __builtin_trap();
}

void CCopiaResultadoParaMR::StartState()
{
    __builtin_trap();
}

} // namespace vota
