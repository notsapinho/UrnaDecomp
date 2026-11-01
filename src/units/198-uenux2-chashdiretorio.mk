# uenux2 api::hash::CHashDiretorio's destructor (target fn 2220), the implicit destructor of the class in the new
# header src/uenux2/src/api/hash/chashdiretorio.h, beside unit 46's chasharquivo.h (CHashArquivo, the element type of
# its files' vector). The destructor gives the class's layout (the header says how). The class's records
# (chashdiretorio.cpp line 41, cmontadorhash.cpp line 121) are in fn 5360, not written, and so is 5359; both call
# 2220, which calls itself through the vector of subdirectories.
#
# No source of its own: 198-uenux2-chashdiretorio-roots.cpp stands for 5359 and 5360 and calls the destructor twice by
# its qualified name in an optnone function, which emits the implicit destructor in the roots object
# (src/units/README.md "Companion files"). The rule compiles it at UENUX2_CXXFLAGS, the tree's flags; src/api/'s
# objects build without -fno-strict-aliasing, and the roots object is the same both ways (cmp of the object compiled
# with and without it). 2220 matches from it: the census pairs it at the addr tier (ledger/functions.tsv), its
# fingerprint differs from the target's (pnpm wasm fn: e60261f09a2851ed for 2220, ba4e628066e18001 for ours, the same
# shape), and the score before the match reads `5 over 118 rows (same 113, replaced 5 [5 operand-only], inserted
# 0, deleted 0)`, the five calls of free; step 8 names it by pair-addr. That the destructor is implicit is a choice:
# compiled at the tree's flags, a function shaped like 5359 (CriaHashesDiretorio into a local, a call with it, then
# its destruction) keeps the call to the implicit destructor (a probe compile, wasm-objdump -d), as it would keep a
# call to one defined in chashdiretorio.cpp, so the target's call does not tell the two apart.
$(ROOT)/$(APP)/198-uenux2-chashdiretorio-roots.o: $(ROOT)/src/units/198-uenux2-chashdiretorio-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/198-uenux2-chashdiretorio.mk $(ROOT)/src/uenux2/src/api/hash/chashdiretorio.h $(ROOT)/src/uenux2/src/api/hash/chasharquivo.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/198-uenux2-chashdiretorio-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/198-uenux2-chashdiretorio-roots.o
