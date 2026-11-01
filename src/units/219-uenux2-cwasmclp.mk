# uenux2 api::CLp, the printer the reports print through: its destructor (target fn 5978), out of line in
# mock/app/simulador/wasm/cwasmclp.cpp, and the class head with the layout of the object its std::unique_ptr holds
# (api/hwil/clp.h). Nothing else of the class is written: the singleton's accessor (fn 3876, which holds the
# constructor inlined), the member fn 3875 and the statics' exit-time destructors (fns 12016, 12015) wait, and
# cwasmclp.cpp keeps 3876's stub over the constructor's record line.
#
# Evidence:
# - The name. Fn 12016 is the exit-time destructor of the static pointer at @1834044: it clears it and, when it held an
#   object, calls fn 5978 on it and frees it. Fn 3876, which builds a 12-byte object through the constructor whose
#   record is api::CLp::CLp() (1543108, cwasmclp.cpp 10:68), stores it in that pointer and calls fn 5978 on the object
#   the pointer held before, then frees it: the shape of std::unique_ptr<CLp>::reset with a destructor called as a
#   function. So fn 5978 is CLp's destructor (the D2, its two callers adding the free).
# - Out of line. Measured on two scratch TUs at the tree's flags (try-tu.sh --symbols --component
#   uenux2/mock/app/simulador/wasm, then wasm-objdump -d of the object) holding this head, a GetInst of unit 104's
#   shape and the static pointer: with the destructor defined in the .cpp, GetInst and the pointer's exit-time
#   destructor each call the D2 and then operator delete, the target's shape; with the destructor implicit, clang emits
#   std::default_delete<api::CLp>::operator() out of line, the destructor and the free inside it, and both call that.
# - The body: +8 is released as std::unique_ptr releases (the member cleared before the delete); the pointee's
#   destructor, inlined, destroys an ecourna::api::io::CFile at +20 (its inline destructor calls fn 336, CFile::Close,
#   when the FILE* is set, then frees the name at +24) and then frees a std::vector at +8 whose elements need no
#   destruction (no loop between the end and the free). Nothing else of the pointee is destroyed.
# Measured on the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before steps 7 to 9:
# 4 over 46 rows, operand-only. Steps 8 and 9 give it no symbol line: the census pairs nothing with it (its tier is
# none), and the scan's content pass matched it (the first scan's source column read content; a rescan writes symbol
# there, as the committed splat/scan.tsv reads), the body being the only unmatched one of ours equal to the target's.
#
# Chosen, no evidence names them: the pointee's name, SSaidaLp, and its being a struct; its two first words and their
# types, the vector's element type (uebyte), every data member's name; the types of CLp's +0 and +4 (fn 3876 stores the
# same word, CPolySingleton<IImpressoraRelatorios>::instance()'s, in both, and fn 3875 calls slot 9 of +4's object, an
# IImpressora's per api/hwil/iimpressora.h); the header's path, api/hwil/clp.h, beside the printer interfaces (no record
# names a header; the record's file is the simulator's implementation); the destructor's file, the constructor's;
# `= default` for its body (`{}` gives the same D2: wasm-objdump -d of the two objects, call indices masked) and its
# line, below line 10, the constructor's record line.
#
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2
# header.
CWASMCLP_SRCS := mock/app/simulador/wasm/cwasmclp.cpp
UENUX2_SRCS += $(CWASMCLP_SRCS)
# nothing reconstructed calls the destructor yet: 219-uenux2-cwasmclp-roots.cpp stands for its two target callers
$(ROOT)/$(APP)/219-uenux2-cwasmclp-roots.o: $(ROOT)/src/units/219-uenux2-cwasmclp-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/219-uenux2-cwasmclp.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/219-uenux2-cwasmclp-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/219-uenux2-cwasmclp-roots.o
