# uenux2: std::map<char, ecourna::app::dados::CLabelParametrizado>'s initializer-list constructor (target fn 5795), the
# label map comum::md::CTradutorFrase::SetLabels takes. The unit has no source of its own (src/units/README.md "What a
# fragment holds" item 2): the body is libc++'s, from unit 123's crelatoriotesteimpressora.cpp.o, which instantiates it
# for CRelatorioTesteImpressora::InicializaTradutorFrase (fn 11196), and this unit holds only the caller stand-in that
# keeps it out of line.
#
# Evidence. Unit 123's fragment reads 5795 as that constructor: 11196 builds the map from a list of four labels and the
# target calls 5795 there, which holds the insertion (__emplace_hint_unique_extract_key) that our 11196 called at -O2,
# where clang inlined the constructor. Its target callers are 11196 and 7787 (ledger/callgraph.tsv); with 11196 the
# only one in our link binaryen inlines it there (unit 123's fragment: 11196 at 212 over 453 rows so, at the tree's
# -O3). The target's wasm type, (i32 i32)->(i32), keeps the result, so the stand-in reads it; the object's third
# parameter, the comparator, is in neither link's type (pnpm wasm fn on both).
#
# Measured, pnpm wasm score against our plain link with the stand-in in it: 5795 1 over 172 rows, and 11196 20 over 289,
# all operand-only; splat-match then matched both (5795 by content, 11196 under the symbol file's name). 11196's body is
# unit 123's, unchanged: the stand-in only gives 5795 its second call site.
#
# The roots compile at APP_CXXFLAGS: they declare the constructor through an __asm__ label with the object's signature
# ((i32, i32, i32) -> i32 in crelatoriotesteimpressora.cpp.o, wasm-objdump -x), include no header and instantiate
# nothing, so the flags decide no body here. The stand-in goes when 7787 lands.
$(ROOT)/$(APP)/208-uenux2-clabelparametrizado-map-roots.o: $(ROOT)/src/units/208-uenux2-clabelparametrizado-map-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/208-uenux2-clabelparametrizado-map.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/208-uenux2-clabelparametrizado-map-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/208-uenux2-clabelparametrizado-map-roots.o
