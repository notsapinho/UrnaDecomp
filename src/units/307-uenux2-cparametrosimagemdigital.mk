# uenux2 vota::CParametrosImagemDigital::GetInst (target fn 1903) in
# app/vota/operador/confirmaidentidade/cparametrosimagemdigital.cpp, paths relative to src/uenux2. The class header says
# what the object holds; nothing names the class, its file or its members, so all of those are chosen.
#
# Where the evidence places it (a reading): no record, slot or RTTI names fn 1903. Its statics' exit destructors, 10520
# (the std::unique_ptr's, `f349(p0, 1908664)`) and 10519 (the std::mutex's, `f150(1908640)`), sit in use band 1 between
# 2742's (10522, 10521) and the file statics of ccontrolareconhecimento.cpp (10518 to 10516, then
# CControlaReconhecimento's 10515 and 10514), after chabilitaaudioeleitor.cpp's (10526, 10525): an index runs in
# reverse link order inside a band (`awk -F'\t' '$1>=10514 && $1<=10526' ledger/ordinals.tsv`, uses 1), and in .bss
# the two objects lie right below CControlaReconhecimento::s_indiceDedo (@1908668). So its TU lies among
# confirmaidentidade/'s objects, just before ccontrolareconhecimento.cpp's or in it. Not in it, measured: written in
# ccontrolareconhecimento.cpp, clang inlines GetInst into CControlaReconhecimento's constructor (the try-tu --symbols
# object's C1 calls mutex lock, operator new and unlock and no GetInst), where the target's fn 1256 keeps `call 1903`.
# So it has a file of its own here, named after the class.
#
# Its five target callers (fns 1256, 3614, 5372, 10316, 10465) drop its result, and the target keeps it all the same
# (`()->(i32)`). All five are in the link (units 161, 221, 214, 135 and 282), and the roots went: with the roots'
# object emptied, the link keeps 1903 and 2742 as `()->(i32)` and pnpm wasm score gives them the rows it gives them
# with it (8 over 33 and 3 over 5, operand-only; 2224 byte-exact), measured on a copy of link.cmd
# (docs/reference/facts/workflow.md W13).
#
# 2742 and unit 282's 10465, with 10465's callee 2223, hold each other: 2742's and 2223's names are `call by:10465`
# only, and splat-build without either match line refuses 10465 as self-voted, so the three land or leave together.
# Also in this file, each matched (step 9): vota::CParametrosImagemDigital::ExtraiTemplate (fn 2224) and
# vota::CConversorWsq, the 1-byte singleton of fn 2742 (its GetInst, a thunk into binaryen's shared body 2900, as our
# link forms it too), with its statics' exit destructors (10521, s_mutex's; 10522, s_inst's) and its ConverteParaWsq,
# whose body after binaryen's dead-argument elimination is 7-Zip's Xzs_Construct's (fn 1379, one body in our link too,
# whose match line step 9 renamed to ours: our object links first). cparametrosimagemdigital.h says what each rests on
# and what is chosen. CConversorWsq's GetInst and statics come first in the file: the target's .bss holds its mutex and
# pointer right below CParametrosImagemDigital's, and band 1 links their exit destructors first (10522 and 10521 above
# 10520 and 10519); the file's local destructor names moved with them (CParametrosImagemDigital's are now
# __cxx_global_array_dtor.4 and .6, the match lines of 10520 and 10519 edited to them). Their callers are all in the
# link (2224's 3614 and 5372, units 221 and 214; 2742's and ConverteParaWsq's 10451, unit 221, with 10316 and 2725,
# units 135 and 293), so the stand-ins the roots gave them went (above). The header's vota::CConversorWsq::PreparaWsq,
# inline, is unit 293's: 2725 holds it.
CPARAMETROSIMAGEMDIGITAL_SRCS := src/app/vota/operador/confirmaidentidade/cparametrosimagemdigital.cpp
UENUX2_SRCS += $(CPARAMETROSIMAGEMDIGITAL_SRCS)
