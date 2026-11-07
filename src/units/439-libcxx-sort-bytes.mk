# Unit 439: libc++'s std::sort over unsigned char, libc++.a's algorithm.o, brought into the link by a stand-in for its
# one unwritten target caller, fn 7787. No source of its own: one roots rule (439-libcxx-sort-bytes-roots.cpp), unit
# 216's shape. These are library functions, built from libc++'s source at the pinned emsdk (docs/how-to-decompile.md
# "Library functions"); no code of theirs is written here.
#
# Matched from sysroot:libc++.a(algorithm.o), each over unsigned char* (the names step 8 gives them,
# evidence:pair-fingerprint): 4820 std::__introsort<_ClassicAlgPolicy, ranges::less, unsigned char*, true>, 4817
# __insertion_sort_incomplete, 4818 __sort5, 4819 __sort4, 4811 __sift_down, 4812 __swap_bitmap_pos, 1507 __sort3 and
# 2579 __partially_sorted_swap. Before step 8, `pnpm wasm score` against our plain link: 4820 `0 over 1286 rows`, 4817
# `0 over 154`, 4818 `0 over 74`, 4819 `0 over 100`, 4811 `0 over 148`, 4812 `0 over 52`, 1507 `0 over 26` and 2579
# `0 over 39`.
#
# Evidence. The target's 4809, 4810, 4813 to 4816, 1506 and 2578 are the same functions over unsigned int, matched from
# algorithm.o since unit 77's 11212 sorts a std::vector of them; these eight sit among them in the target's index order
# and read their elements with load8_u where those use i32.load (`pnpm wasm fn`). 4820's target callers are 4820 and
# 7787, and the other seven's are members of the family (ledger/callgraph.tsv). 7787 calls
# CConfiguracaoEleicao::GetInst (fn 187) and GetTodosCargos (fn 5790), copies the byte at +0 of each 140-byte element of
# the result into a vector (its growth inlined), and when the vector is not empty calls 4820 at +0x11bab with
# 2 * log2(n) and true (build/out/splat/pieces/asm/comum/7787.wat): libc++'s __sort<__less<unsigned char>&, unsigned
# char*> (system/lib/libcxx/src/algorithm.cpp), which binaryen inlined into 7787. libc++'s __algorithm/sort.h declares
# that instance extern template, so a std::sort over unsigned char with the default order calls algorithm.o's copy,
# which reaches the eight.
#
# The stand-in stands for 7787's one call of the family: one std::sort over a std::vector<unsigned char>, which reaches
# the extern template as 7787's code does; binaryen inlines __sort into the stand-in, which then calls 4820's copy once
# with the depth limit and true, as 7787 does (`pnpm wasm fn` on both). Without it, as at 911c8d03, none of the eight is
# in our link: their rows read no-candidate. It goes when 7787 is in the link (src/units/README.md "When it goes",
# whose exception is this case: the target inlines __sort into 7787). That the vector holds the cargos' TCargoID (a
# uebyte) is a reading of our CCargo header (app/comum/dados/md/processoeleitoral/ccargo.h: m_id first, 140 bytes).
# Chosen: the stand-in's name and its result (the size plus 439, so that its body is no target function's).
# std::ranges::sort(cargos) and std::sort(cargos.data(), cargos.data() + cargos.size()) give an object cmp-equal to this
# one, each compiled at this rule's line.
#
# The roots compile at APP_CXXFLAGS and include only <algorithm> and <vector>: the object defines the stand-in, its sink
# and its static constructor and leaves __sort<__less<unsigned char>&, unsigned char*> undefined (llvm-nm), so it emits
# no TSE code and no library instance, and no match rests on its flags. The census pairs no target function with it
# (how-to step 7's command lists the same 31 roots-object pairs as at 911c8d03). Steps 6 to 9 against 911c8d03: the
# eight go from no-candidate to match and no other row's verdict moves (how-to step 9's join); 4809, 4810, 4813 to 4816,
# 1506 and 2578 stay matched, and 11212 scores `23 over 378 rows`, operand-only, as unit 77's fragment gives.
$(ROOT)/$(APP)/439-libcxx-sort-bytes-roots.o: $(ROOT)/src/units/439-libcxx-sort-bytes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/439-libcxx-sort-bytes.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/439-libcxx-sort-bytes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/439-libcxx-sort-bytes-roots.o
