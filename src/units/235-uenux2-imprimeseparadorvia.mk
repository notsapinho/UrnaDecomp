# uenux2 comum::CRelUtil::ImprimeSeparadorVia (target fn 5581, matched), written on lines 403 to 408 of
# src/uenux2/src/app/comum/relatorios/crelutil.cpp, unit 123's source, which compiles it (src/units/README.md "Landing a
# unit" item 2), and declared in crelutil.h. This fragment holds its stand-in only, as unit 178's roots keep a member
# written in unit 110's file (fn 2803); unit 123's fragment points here.
#
# What the target shows.
# - 5581 (427 B, `pnpm wasm fn ../target/vota_web_wasm.wasm 5581`) builds std::format's result for
#   "-------------- {:02} / {:02} ---------------" (the 44-byte literal at 378206, which no other target function loads:
#   `/usr/bin/grep -rlE 'i32\.const 378206($|[^0-9])' build/out/splat/pieces/asm`) over its second and third arguments,
#   both of argument code 6, unsigned (the i64 198 it stores: docs/reference/facts/reading.md R13), adds it to the
#   api::CPaperFormBuilder its first argument is with AddTextField (fn 193), style 1 and alignment 0, then calls
#   AddNewLine(1) (fn 198).
# - Its one caller is fn 12110, vota::CGeraBU's slot 2 (ledger/vtables.json), which calls it twice (+0xdbe and +0x1086),
#   each time with the builder at +36 of its frame, a counter plus one and a total. 12110 also calls
#   CRelUtil::GetIDCargaFormatado (fn 2786, record crelutil.cpp:69).
#
# Chosen.
# - The file. No record names it, and in the uses-2 band of ledger/ordinals.tsv no function between the matched
#   cparte*.cpp rows (5590 to 5587) and cvalidamidia.cpp's GetInst (5575, record line 182) holds a record. In link
#   order 5581 follows fn 5583, which unit 123 put in crelutil.cpp by choice, and fn 5582 (no record), and precedes fns
#   5580 to 5576 (no record; 5576's callers are fn 3689, which holds csubstituidortitulo.cpp's records, and fn 11175).
#   crelutil.cpp is taken for that neighbour and for the caller's other CRelUtil call (above); the other relatorios
#   files whose names sort in that stretch, csigverifier.cpp (unit 26) and csubstituidortitulo.cpp, were not linked
#   with it (docs/reference/facts/placing.md P5).
# - Its name, its being a static member of CRelUtil (the class's records name only static members: how-to step 3,
#   "Names no evidence gives"), its parameters' unsigned int (the argument code gives the signedness, not the width),
#   its line (in the blank run between IncluiCabecalhoEleicoesMZS's record, line 307, and DSCodigoVerificador, line
#   410), and the style's spelling as a cast of 1 and the alignment's as api::ALINHAMENTO_ESQUERDA, as
#   IncluiAvisoModoDemonstracao spells its style.
#
# The match: `pnpm wasm score ../target/vota_web_wasm.wasm 5581 ../build/out/wasm/vota_web/vota_web_wasm.wasm <ours>`
# gave 11 over 187 rows before step 9, all operand-only, the one operand that is no call and no data address being the
# format buffer's table slot (148 in the target). No symbol-file line names it: the scan's content pass pairs it (its
# `source` read `content` in the first scan), and no other target function loads its literal.
#
# Roots (235-uenux2-imprimeseparadorvia-roots.cpp): w235_vias stands for 12110 with two calls; it goes when 12110 is in
# the link.
$(ROOT)/$(APP)/235-uenux2-imprimeseparadorvia-roots.o: $(ROOT)/src/units/235-uenux2-imprimeseparadorvia-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/235-uenux2-imprimeseparadorvia.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/235-uenux2-imprimeseparadorvia-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/235-uenux2-imprimeseparadorvia-roots.o
