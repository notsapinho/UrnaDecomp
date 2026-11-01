# uenux2 comum::md::CEleitorIdentidade's constructor (target fn 566) and FormataIdentidade (fn 2798) in
# src/app/comum/dados/md/eleitor/celeitoridentidade.cpp, and IRegraIdentidade's EhValida (fn 3723) and Valida in
# src/app/comum/dados/md/iregraidentidade.cpp. CValidadorIdentidade's Valida and EhValida (fn 2803), which 566 and the
# roots call, are unit 110's (cvalidadoridentidade.cpp); the CStringUtils zero helpers they call (fns 3510, 3512, 5159)
# are unit 00's.
#
# Evidence:
# - 566 holds two records, cvalidadoridentidade.cpp:61 (CValidadorIdentidade::Valida) and iregraidentidade.cpp:23
#   (IRegraIdentidade::Valida), each behind a stack-pointer prologue of its own (`pnpm wasm fn ... 566`: g0-480, then
#   g0-32 after the outer g0-16; docs/reference/facts/reading.md R10): both are out-of-line functions binaryen inlined
#   into their one caller, and 566 is neither. 566 takes a string by value (it moves from p1) and a type, stores them at
#   +0 and +12, CEleitorIdentidade's layout (celeitoridentidade.h), and returns p0: a constructor (R2). Its callers build
#   the class with it: 2264 makes the key of a find over CEleitorIdentidade (fn 1703), and 11410 holds the record of
#   CConversorImpedido::MontaEleitorIdentidade, which returns md::CEleitorIdentidade.
# - Before the validation 566 holds 2798's body (callers 3616, 10420, 10631): a by-value string formatted to the type's
#   length (11 for type 2, else 12: leading '0's erased when longer, then padded) and moved out. 2798 has three callers
#   and no call of it is in 566, read as clang inlining it, so the two share a TU (a reading: 566 could repeat the
#   code). After the validation 566 formats its member
#   again in place, reading the type back from +12.
# - 3723 is the test Valida throws on, with a bool result (callers 2803 and 10627): empty is false at once, a character
#   outside '0'-'9' is false, else slot 4 of the rule on the number with its leading '0's erased (fn 5159). 566's inlined
#   Valida holds the same code, with no call of 3723: clang inlined it there, so both are in the record's file. The
#   target's test of each character against a 64-bit mask is what `numero.find_first_not_of("0123456789")` compiles to
#   here (3723 scores operand rows only, below); why it does (LLVM folding the memchr of a short literal) is a reading.
#
# Where the files are (docs/how-to-decompile.md step 3, "When no record names the file"):
# - iregraidentidade.cpp is the record's file. In ledger/ordinals.tsv's uses-3 band, read in link order, 3723 lies
#   after md/clocal.cpp's 3724 and before md/eleitor/cbiometriaeleitor.cpp's 3720, and md/'s own files sort clocal.cpp,
#   ..., cvalidadoridentidade.cpp, iregraidentidade.cpp; the records' data order agrees (cvalidadoridentidade.cpp's at
#   @1571932, iregraidentidade.cpp's at @1571948). A reading, consistent with the path.
# - celeitoridentidade.cpp is chosen by rule 4 (the class's name in lower case) in md/eleitor/, the voter classes'
#   directory. In the uses-4 band 2798 lies after md/eleitor/cbiometriaeleitor.cpp's 2799 and before
#   md/processoeleitoral/ccargo.cpp's 2797, where a file of md/eleitor/ sorting after cbiometriaeleitor.cpp falls: a
#   reading that fits the choice, not evidence for it.
#
# Measured: our link inlines both Valida into 566 as the target's does (neither is in build/out/wasm-map/vota_web/
# names.tsv after `make -C src link-map`), and 566, 2798 and 3723 score operand rows only against the target before step
# 8 (`pnpm wasm score`: 26 over 448, 0 over 40, 2 over 97). No other form of these bodies was tried.
#
# Chosen, no evidence names them: EhValida (here and in CValidadorIdentidade), FormataIdentidade and its being a free
# function of comum::md, the file-static Normaliza that both formattings call, celeitoridentidade.cpp's path and every
# line in both files but the throw's (iregraidentidade.cpp:23, column 15), and the order of the two functions in each
# file. The constructor's second formatting is written as Normaliza on the member, since 566 calls 3510 and 3512 on p0
# itself; no other spelling of it was tried.
#
# Roots (178-uenux2-celeitoridentidade-roots.cpp): none of the four functions' target callers is reconstructed, so the
# file gives each two call sites; the two Valida get none, since the target inlines each into its one caller and ours
# has that one call too.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CELEITORIDENTIDADE_SRCS := src/app/comum/dados/md/iregraidentidade.cpp src/app/comum/dados/md/eleitor/celeitoridentidade.cpp
UENUX2_SRCS += $(CELEITORIDENTIDADE_SRCS)
# the unit's target callers are not reconstructed: 178-uenux2-celeitoridentidade-roots.cpp stands in for them
$(ROOT)/$(APP)/178-uenux2-celeitoridentidade-roots.o: $(ROOT)/src/units/178-uenux2-celeitoridentidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/178-uenux2-celeitoridentidade.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/178-uenux2-celeitoridentidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/178-uenux2-celeitoridentidade-roots.o
