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
# (`()->(i32)`). Fn 1256 (CControlaReconhecimento::GetInst, unit 161) is in the link; 307-uenux2-cparametrosimagemdigital-roots.cpp
# stands in for the other four and reads the result, so that binaryen keeps both the function and its result.
CPARAMETROSIMAGEMDIGITAL_SRCS := src/app/vota/operador/confirmaidentidade/cparametrosimagemdigital.cpp
UENUX2_SRCS += $(CPARAMETROSIMAGEMDIGITAL_SRCS)
# The roots declare what they call through an asm label, so they include no header; compiled with APP_CXXFLAGS.
$(ROOT)/$(APP)/307-uenux2-cparametrosimagemdigital-roots.o: $(ROOT)/src/units/307-uenux2-cparametrosimagemdigital-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/307-uenux2-cparametrosimagemdigital.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/307-uenux2-cparametrosimagemdigital-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/307-uenux2-cparametrosimagemdigital-roots.o
