# uenux2 comum: comum::NomeArquivoEleitores and NomeArquivoEleitoresTTE
# (app/comum/nomearquivo/cnomearquivoeleitores.cpp) and comum::CMesarioRegistrado
# (app/comum/comparecimentomesario/estados/cmesarioregistrado.{h,cpp}). Paths relative to src/uenux2. The list also
# compiles unit 135's igestordadomesario.cpp, last, for 10337 (below, "The orders").
#
# Target fns matched: 3745 and 5727 (comum::NomeArquivoEleitores, NomeArquivoEleitoresTTE) and 10338
# (CMesarioRegistrado::ProcessInput, a thunk into binaryen's 6011, which matches; unit 247's fragment has its evidence).
#
# - 3745 and 5727: each builds two short strings in its frame, "el" or "tte" and "dat", calls
#   comum::CNomeArquivo::NomeArquivoSecao (3772, unit 131) with the words at +0 and +4 and the string at +8 of the
#   address it takes, then its three numbers and the two strings, and frees each string when long. Their callers, 1937
#   (comum::CEleitorDetalhe::GetBiometria, by its records) and 7787, pass CConfiguracaoEleicao::GetInst()'s +620 and the
#   words at +644 and +648 (cnomearquivo.h says what of this is chosen). No record names them or their file.
# - Not cnomearquivo.cpp: there clang sees NomeArquivoSecao's body, and each of ours tests the long bit of one string
#   only (wasm-objdump -d of cnomearquivo.cpp.o: one i32.load8_s per function); 3745 scored `17 over 80 rows (same 63,
#   replaced 5 [5 operand-only], inserted 0, deleted 12)` in that link, the twelve rows of the target's second test. The
#   same body in a TU with cnomearquivo.h only tests both. Not celeitordetalhe.cpp either: there clang inlines both into
#   GetBiometria's file name (that object calls NomeArquivoSecao itself), where the target's 1937 calls them. In this
#   file, before steps 7 to 9 (pnpm wasm score at the default depth): 3745 `6 over 80 rows (same 74, replaced 6 [6
#   operand-only], inserted 0, deleted 0)`, 5727 `7 over 85 rows (same 78, replaced 7 [7 operand-only], inserted 0,
#   deleted 0)`, calls and data addresses only; step 9 matched both (scan source `ledger`, the census's pairs).
# - Their band neighbours with records do not place the file: 3744 for 3745 in band 3, whose record
#   (cnomearquivo.cpp:208) is a builder's binaryen inlined into it, and 3747 (dados/md/rdv/cvotoseleicoesvota.cpp:184),
#   5725 (api/io/cdatamap.h:143, a header) and 5732 (cvotoseleicoesvota.cpp:172) for 5727 in band 2. The file's name and
#   its directory, beside the header that declares them, are chosen.
# - comum::NomesArquivosEleicao (fn 3744) follows them in this file, its object's by band 3 and the table's slots
#   (fragment 388, src/units/388-uenux2-nomesarquivos.mk, has its evidence, forms and stand-ins).
# - comum::CMesarioRegistrado (cmesarioregistrado.h has the class's evidence): vtable @1594872, [448, 765, 10339, 7480,
#   1661, 218, 425, 10338, 425], and the record cmesarioregistrado.cpp:72, GetControlador's return, which 10339 and 6011
#   (through 10338) load. ProcessInput (10338) is the thunk `f6011(p0, 1594916, 1594944)` of unit 247's paragraph.
# - StartState (10339) matches with its two next-state stores through comum::CAppState::SetNextState (unit 61's fragment
#   has why: the target ran binaryen's passes on the body again after inlining a call). With the assignments it read
#   `24 over 100 rows (same 76, replaced 20 [16 operand-only], inserted 2, deleted 2)`, the target's calls and slots in
#   the target's order, binaryen's local numbers apart (the scan:
#   `+0x2e target +0x2d local.tee 1 | ours +0x2d local.tee 4`; the record's address and the controllers sit in other
#   locals). ProcessInput's two stores go through the setter as well, as CRegistrarMesarios::ProcessInput's do: the two
#   bodies are what binaryen merges into 6011, which matches so (unit 247's paragraph has the measurement); 10338, the
#   thunk into it, matches either way.
# - GetInst, the constructor and the operator's form (TelaMesarioRegistrado) are written from IGestorDadoMesario::
#   StartState (10337, unit 135), which holds them inlined: the 28-byte object, CAppState's constructor with 2
#   (EVENTO_ENTRADA), the vptr, both forms assigned (fn 1255's at +20, then the builder's at +12, a frame of its own),
#   the builder's buzz (51, 10), the texts @364807, @335481 and @86376 at {1, 1}, {1, 2} and {1, 4}, AddInputControl
#   and GetInteractiveForm("", true). 10337, which calls GetInst, matches with the two orders below (step 9,
#   evidence:srcloc-anchor); its body is unit 135's.
# - The orders, measured for 10337 on whole links of the plain link.cmd at 9f0245ef, each a copy with the variant object
#   swapped in, igestordadomesario.cpp.o moved, or both (docs/reference/facts/workflow.md W13; pnpm wasm score at the
#   default depth; docs/reference/facts/codegen.md C4): GetInst defined above CMesarioRegistrado's constructor in
#   cmesarioregistrado.cpp, and igestordadomesario.cpp.o linked after cmesarioregistrado.cpp.o, so this list compiles
#   it, last. With both, `69 over 750 rows (same 681, replaced 69 [69 operand-only], inserted 0, deleted 0)`, the six
#   rows that are no call and no data being the thrown error's destructor slot (__cxa_throw's third argument) and the
#   statics' addresses; then a match at step 9. With either alone, the base's `289 over 761 rows (same 472, replaced 268
#   [264 operand-only], inserted 11, deleted 10)`: GetInst above the destructor with the object in place gives the
#   base's module byte for byte. GetInst first in the file or right after the destructor, as written, are two objects
#   (wasm-objdump -x: GetInst, D2, D0, C2, TelaMesarioRegistrado against D2, D0, GetInst, C2, TelaMesarioRegistrado) and
#   one module (sha256 4da35798fc27afe9...): GetInst's place among the definitions above the constructor is a choice. In
#   the target's data cmesarioregistrado.cpp.o's vtable (0x1855f8) is the rank right before igestordadomesario.cpp.o's
#   typeinfo (0x185660), and the three Gestor states' vtables (unit 135's list) follow it. codegen.md C4's record-aware
#   count (the section's script, on the plain link.cmd at 9f0245ef): igestordadomesario.cpp.o at its place in unit 135's
#   list 454 objects out of the data's order; after cmesarioregistrado.cpp.o 280, of which 19 the move inverts (the
#   three Gestor states, cpededigitalmesario.cpp and ccontroladorreconhecimetomesario.cpp of comparecimentomesario/, six
#   gravadores/asn converters and gravadores/md/ctipoapuracaosa.cpp, api/hash's three files, api/ipc/cthread.cpp, vota's
#   iexecucaovota.cpp, operador/caguardainicio.cpp and operador/cthreadoperador.cpp) and 193 it restores; the list's
#   other places, before cnomearquivoeleitores.cpp.o or before cmesarioregistrado.cpp.o, 281 each, and give the other
#   order. The other move, cmesarioregistrado.cpp into unit 135's list ahead of igestordadomesario.cpp, counts 281 here
#   and 453 or 454 at each place there. So igestordadomesario.cpp moves, and unit 135 keeps its note and row
#   (src/units/README.md "Names").
# - The statics, @1909736 (s_inst, which 10337 loads and stores) and @1909712 (s_mutex, whose address 10337 passes to
#   the mutex's call): their exit destructors are 10341 and 10340. Until it matched, 10337 was named by vtable, which
#   casts no vote, and each object took a hand line in splat/symbol_addrs.txt led by its two readers (10337, whose
#   inlined GetInst tests and stores the pointer and unlocks the mutex, and the exit destructor). Since 10337 matches,
#   step 8 names both objects by its votes (`vote:8 by:10337` and `vote:2 by:10337` at c1ffbbae), and the matches of
#   10340 and 10341, which use them, hold the names (docs/reference/splat.md "No circular evidence"): 10337, 10340 and
#   10341 land or leave together. The hand lines went, idle: weighed by removal on copies (the symbol file without a
#   line, the match list without 10337, 10340 and 10341, two scan passes beside a control that keeps every name, then
#   splat-build on the copies), each hand line out, and both, every row came back and the build gave the target's sha256
#   with 12986 matches; both names out on both sides of the marker, 10337 reads unresolved and 10340 and 10341 differ.
#   They went in a commit of their own with docs/how-to-decompile.md step 1's example, which cited them (step 9, "Hand
#   edits"). Their object adds a second local __cxx_global_array_dtor.5 to the link, so step 9 renamed 10760's match
#   line to the one qualified by its object.
# Chosen: the files' paths and names, the order of the definitions in each but GetInst above the constructor, measured
# (above; cmesarioregistrado.cpp otherwise as unit 247's cregistrarmesarios.cpp), the class's `final` and its
# destructor declared first and out of line (as CRegistrarMesarios, over the same slots 0 and 1), the members' names,
# TelaMesarioRegistrado's name, and the controller's slot names (its header's). TelaMesarioRegistrado's external
# linkage is evidence, not a choice: 10337 holds it behind a frame of its own, the sign unit 247's fragment measured for
# CRegistrarMesarios's form.
#
# Not written here: 1937, in celeitordetalhe.cpp (unit 110's list; unit 98's fragment has the measurement).
# IGestorDadoMesario::StartState (10337) is unit 135's, matched; igestordadomesario.cpp is compiled here (above).
NOMEARQUIVOELEITORES_MESARIOREGISTRADO_SRCS := src/app/comum/nomearquivo/cnomearquivoeleitores.cpp \
    src/app/comum/comparecimentomesario/estados/cmesarioregistrado.cpp \
    src/app/comum/comparecimentomesario/estados/igestordadomesario.cpp
UENUX2_SRCS += $(NOMEARQUIVOELEITORES_MESARIOREGISTRADO_SRCS)
# the unit's callers are not written: 279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp keeps the vtable's
# address and the two name builders the way the target does
$(ROOT)/$(APP)/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.o: $(ROOT)/src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado.mk $(ROOT)/src/uenux2/src/app/comum/nomearquivo/cnomearquivo.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.o
