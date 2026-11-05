# uenux2 api::hash::CHashDiretorio (the header src/uenux2/src/api/hash/chashdiretorio.h, beside unit 46's
# chasharquivo.h: CHashArquivo is the element type of its files' vector) and its file api/hash/chashdiretorio.cpp, the
# records' (line 41): the implicit destructor (target fn 2220), which gives the class's layout (the header says how),
# and the constructor with ValidaObjeto, which binaryen inlines into CMontadorHash::CriaHashesDiretorio (fn 5360, unit
# 227's, written and not matched), their one caller, behind a frame of 16 bytes: the name copied, the files' vector (fn
# 1300) and the subdirectories' (fn 5363) copied, then the name tested (5102 "CHashDiretorio: nome inválido.", record
# :41). ValidaObjeto is inlined into the constructor by clang, one frame; the constructor's lines and parameters' forms
# are a choice (the copies say references). 2220 calls itself through the vector of subdirectories; 5359 and 5360 call
# it.
#
# 2220 matches from cmontadorhash.cpp's object now, the first on the link line to emit it (5359 and 5360 destroy a
# CHashDiretorio there): the roots file that emitted it for those two callers, at UENUX2_CXXFLAGS, went with them.
# Before, the census paired it at the addr tier, its fingerprint differing from the target's (pnpm wasm fn:
# e60261f09a2851ed for 2220, ba4e628066e18001 for ours, the same shape), and the score read `5 over 118 rows (same 113,
# replaced 5 [5 operand-only], inserted 0, deleted 0)`, the five calls of free; step 8 named it by pair-addr. src/api/'s
# objects build without -fno-strict-aliasing, and the roots object was the same both ways (cmp of the object compiled
# with and without it). That the destructor is implicit is a choice: compiled at the tree's flags, a function shaped
# like 5359 (CriaHashesDiretorio into a local, a call with it, then its destruction) keeps the call to the implicit
# destructor (a probe compile, wasm-objdump -d), as it would keep a call to one defined in chashdiretorio.cpp, so the
# target's call does not tell the two apart. 5363, the vector of subdirectories' copy constructor, comes from this
# file's object: 4 over 98 rows, every row a call (pnpm wasm score), and no-candidate, since its recursive call waits
# for its own name, which its other caller, 5360, would give once named itself. The header's inline getters are fragment
# 227's (api::hash::ListaHashesArquivos, fn 5358, reads the three members in place). The file's object links in this
# unit's list, between unit 186's chasharquivo.cpp.o and unit 227's cmontadorhash.cpp.o, the data's order of their
# records (@1599676, @1599740, @1599756).
W198_SRCS := src/api/hash/chashdiretorio.cpp
UENUX2_SRCS += $(W198_SRCS)
