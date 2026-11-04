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
# (`()->(i32)`). Fns 1256 (CControlaReconhecimento::GetInst, unit 161) and 10465 (unit 282) are in the link;
# 307-uenux2-cparametrosimagemdigital-roots.cpp stands in for the other three and reads the result, so that binaryen
# keeps both the function and its result.
#
# Also in this file, each matched (step 9): vota::CParametrosImagemDigital::ExtraiTemplate (fn 2224) and
# vota::CConversorWsq, the 1-byte singleton of fn 2742 (its GetInst, a thunk into binaryen's shared body 2900, as our
# link forms it too), with its statics' exit destructors (10521, s_mutex's; 10522, s_inst's) and its ConverteParaWsq,
# whose body after binaryen's dead-argument elimination is 7-Zip's Xzs_Construct's (fn 1379, one body in our link too,
# whose match line step 9 renamed to ours: our object links first). cparametrosimagemdigital.h says what each rests on
# and what is chosen. CConversorWsq's GetInst and statics come first in the file: the target's .bss holds its mutex and
# pointer right below CParametrosImagemDigital's, and band 1 links their exit destructors first (10522 and 10521 above
# 10520 and 10519); the file's local destructor names moved with them (CParametrosImagemDigital's are now
# __cxx_global_array_dtor.4 and .6, the match lines of 10520 and 10519 edited to them). Their callers that are not
# written (2224's 3614 and 5372; 2742's and ConverteParaWsq's 10451: 10316 and 2725, units 135 and 293, are written
# now) have stand-ins in the roots, since binaryen inlines a function its link calls once; they go when those callers
# are in the link. The header's vota::CConversorWsq::PreparaWsq, inline, is unit 293's: 2725 holds it.
CPARAMETROSIMAGEMDIGITAL_SRCS := src/app/vota/operador/confirmaidentidade/cparametrosimagemdigital.cpp
UENUX2_SRCS += $(CPARAMETROSIMAGEMDIGITAL_SRCS)
# The roots declare what they call through an asm label, so they include no header; compiled with APP_CXXFLAGS.
$(ROOT)/$(APP)/307-uenux2-cparametrosimagemdigital-roots.o: $(ROOT)/src/units/307-uenux2-cparametrosimagemdigital-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/307-uenux2-cparametrosimagemdigital.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/307-uenux2-cparametrosimagemdigital-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/307-uenux2-cparametrosimagemdigital-roots.o
