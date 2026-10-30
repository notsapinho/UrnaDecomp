# uenux2 comum::md's identity-number rules, the three classes derived from comum::md::IRegraIdentidade:
# CRegraIdentidadeLivre's Formata (target fn 11274, slot 3 of its vtable @1574644), CRegraTitulo's Formata and
# ValidaDigitoVerificador (fns 11271 and 11272, slots 3 and 4 of its vtable @1574692) and CRegraCPF's (fns 11269 and
# 11270, vtable @1574732), in src/app/comum/dados/md/cregraidentidadelivre.cpp, cregratitulo.cpp and cregracpf.cpp,
# with their headers and the base's, iregraidentidade.h. The vtables' other slots hold bodies binaryen merges with
# other classes' and that match already: the implicit destructors, which destroy nothing (fns 174 and 144), GetTipo
# (fns 11273, 434 and 2254: return 3, 1 and 2) and CRegraIdentidadeLivre's ValidaDigitoVerificador (fn 371: return
# true). No record names these classes, files or members (docs/how-to-decompile.md step 3, "When no record names the
# file"):
# - the directory is the one where the family has its record, md/iregraidentidade.cpp:23 (the base's Valida, inlined
#   into fn 566; rule 3). The link-order clusters 426 to 428 of src/uenux2/unplaced.cpp say md/processoeleitoral/ by
#   class convention only, and their recorded neighbours (cluster 425 in relatorios/, 429 to 432 in dados/asn/) are
#   not the family's. The data order names no directory either: the three vtables (@1574644 to @1574760) lie after
#   md/rdv/cvotoseleicoesvota.cpp's records and before md/estadoaplicacao/cestadogeral.cpp's;
# - the file names are the classes' in lower case (rule 4), one class per file: the three classes' functions and
#   vtables follow each other in the target in the order Livre, Titulo, CPF, which this fragment keeps;
# - the member names are chosen (iregraidentidade.h says from what), and so are the base's slots being pure and the
#   file-static helpers Digitos and CalculaDV of cregratitulo.cpp and cregracpf.cpp (names and linkage).
# Measured in a whole link (tools/round/try-tu.sh, then pnpm wasm splat-remap): the padded string has to be a local of
# an inlined helper; written as a scoped local of ValidaDigitoVerificador itself, the frame puts it below the digits and
# 11272 differs. In 11272 the first sum gives the same bytes written as one expression assigned to a ueword (here), as a
# ueword accumulated in a loop, or as CalculaDV's argument; in 11270 a loop puts the first two digits' terms the other
# way round (measured alone, try-tu.sh --single), so the sums are expressions in both files. 11270's check digit is a
# uebyte (its compare masks it with 255), 11272's an int. Each class's Formata is its first virtual member defined out
# of line, so its key function: each object emits its class's vtable, with the implicit destructors and the base's
# typeinfo. The constructors (inlined into fn 7787) are not written, nor IRegraIdentidade::Valida.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CREGRA_SRCS := src/app/comum/dados/md/cregraidentidadelivre.cpp src/app/comum/dados/md/cregratitulo.cpp \
  src/app/comum/dados/md/cregracpf.cpp
UENUX2_SRCS += $(CREGRA_SRCS)
# the rules' user is not reconstructed yet: 63-uenux2-app-comum-dados-md-roots.cpp keeps the three vtables the way the
# target reaches them
$(ROOT)/$(APP)/63-uenux2-app-comum-dados-md-roots.o: $(ROOT)/src/units/63-uenux2-app-comum-dados-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/63-uenux2-app-comum-dados-md.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/63-uenux2-app-comum-dados-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/63-uenux2-app-comum-dados-md-roots.o
