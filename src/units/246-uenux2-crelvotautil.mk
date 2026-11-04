# uenux2 vota::CRelVotaUtil::CortaPapel (target fn 2882) in app/vota/eleitor/iniciovotacao/crelvotautil.cpp, with the
# std::function slots of its lambda that match: target_type (fn 12003), target (12004) and the call (12005).
#
# Evidence:
# - The name: the RTTI of its lambda, vota::CRelVotaUtil::CortaPapel()::$_0 (typeinfo 1543288), whose std::function's
#   vtable (@1543232) fn 2882 stores (1543240, its address point). CortaPapel takes nothing (fn 2882 is ()->()). The
#   lambda RTTI of the second member, CriaCabecalho (fn 5977, which stores @1543304), names that class too.
# - The body, read from fn 2882: an api::CPaperFormBuilder on the stack (its vector zeroed in place), AddNewLine(2) (fn
#   198) and AddCut (fn 1264); then api::CLp::GetInst (fn 3876, unit 219), called before the sub-report is built, as a
#   member call's object expression is evaluated before its arguments; an api::CSubReport of two empty strings and false
#   (fn 3660 with 0); the lambda, which captures the builder by reference (the pointer the __func holds at +4) and calls
#   Build (fn 357) and slot 2 of the form it returns (fn 12005's body); CLp::Imprime (fn 3875) with the three; then the
#   std::function's, the CSubReport's (inlined: the vptr store and the member frees) and the builder's destruction.
#   pnpm wasm score against the link: 12 over 220 rows, operand-only.
# - Its target callers are fns 11842 (unit 169), 11848 twice (unit 104) and 11991 (pending in unit 104), so the link
#   gives it three call sites and it needs no stand-in.
# - CSubReport's linkonce copies (its vtable, D2 12014, D0 12013, slots 2 to 7) come from this object now, which links
#   before csubreport.cpp's (fragment 246 sorts before 57; the object column of build/out/wasm-map/vota_web/names.tsv),
#   as the target keeps the copies of CRelVotaUtil's object (src/uenux2/src/api/gui/csubreport.h).
#
# The lambda's __clone(__base*) (fn 12006) and __clone() (fn 12007), which step 8 names by their vtable, match since
# this file builds without strict aliasing (src/Makefile's UENUX2_NOTBAA_FILES). The target's 12006 stores the vptr
# before it copies the captured pointer, the order this object gives without TBAA; at src/app/vota/'s strict aliasing
# ours copied first (`differs +0x3 target i32.const 1543240 | ours local.get 0`, 6 over 12 rows; 1 over 9, operand-only,
# without it), and 12007, a thunk into binaryen's merge of clone bodies, called another merge (`target call 786 | ours
# call 1083`). The closure's `$_0` in its RTTI name is clang's name for a type with internal linkage, so the target's
# copies are code of the TU that defines CortaPapel. On the whole link this object without strict aliasing turns 12006
# and 12007 to match and moves no other row in or out of match (docs/reference/facts/app-flags.md F6). The lambda of
# api::CPaperFormBuilder::Show, of the same shape in an src/api object, which builds with strict aliasing, has the load
# first in the target (fn 10999, matched). A path outside UENUX2_TBAA_DIRS would have given the flag too
# (docs/reference/facts/reading.md R10's last paragraph puts a helper in the tree whose flags its rows match at), against
# the use band below; the file is listed by its own path instead, so the directory stays the band's choice.
#
# Chosen, no evidence names them: the file's path and the header's beside it; CRelVotaUtil as a class of static members,
# as comum::CRelUtil is (its records read `static`), where the mangled name does not tell a class from a namespace; the
# two empty strings' spelling `""`; the local's name; the lambda's capture spelled `[&builder]` (`[&]` captures the
# same by the language's rules, not compiled here). No record names the file. The data put this object right after
# cwasmclp.cpp's records (@1543108 to @1543156: CSubReport's vtable @1543172 and the lambda's @1543232 follow), and
# then CDefineRotaPreVotacao's vtable (@1543448, unrecorded) and app/vota/eleitor/iniciovotacao/cimprimindozeresima.cpp's
# records (@1543548). In use band 4, fn 2882 follows vota::CExibeAlertaDesligamento's 2883
# (iniciovotacao/cexibealertadesligamento.cpp) and precedes CriaCabecalho's lambda body 2881 and
# vota::CInicioVotacao::GetInst 2880; in bands 1 and 2 cwasmclp.cpp's 12015 and 5978 come right before this object's
# 12014 and 5977. So the adjacent recorded object in the data is cwasmclp.cpp, in mock/app/simulador/wasm/, the side
# docs/reference/facts/placing.md P5 takes, and the band-4 neighbours and the callers' files are in
# app/vota/eleitor/iniciovotacao/, the band neighbours' directory (ledger/tu-clusters.tsv labels stretch 1118, 2881 to
# 2883, iniciovotacao/cexibealertadesligamento.cpp), which docs/reference/facts/placing.md P4 lets a fragment take
# when it names both neighbours, as here. The directory is a choice, the band's and the class's namespace's; both
# candidates build with strict aliasing, which 12006 and 12007 say this TU did not have, so the file is listed in
# UENUX2_NOTBAA_FILES whichever directory holds it.
#
# Not written: CriaCabecalho (fn 5977) and its lambda's slots (2881, 12000 to 12002).
#
# Roots: none. 246-uenux2-crelvotautil-roots.cpp held the caller stand-in of unit 31's api::CPaperFormBuilder::Show
# (fn 3671) for its target caller 11902, and went with it once 11902 (unit 176's cimpressaopu.cpp) was in the link
# beside 5592 (unit 287's) and 5591 (unit 123's); unit 31's fragment has Show's paragraph.
#
# Paths relative to src/uenux2; the generic uenux2 rule compiles it and depends on the source and every uenux2 header.
CRELVOTAUTIL_SRCS := src/app/vota/eleitor/iniciovotacao/crelvotautil.cpp
UENUX2_SRCS += $(CRELVOTAUTIL_SRCS)
