# uenux2 comum: comum::NomeArquivoEleitores and NomeArquivoEleitoresTTE
# (app/comum/nomearquivo/cnomearquivoeleitores.cpp) and comum::CMesarioRegistrado
# (app/comum/comparecimentomesario/estados/cmesarioregistrado.{h,cpp}). Paths relative to src/uenux2.
#
# Target fns matched: 3745 and 5727 (comum::NomeArquivoEleitores, NomeArquivoEleitoresTTE) and 10338
# (CMesarioRegistrado::ProcessInput, a thunk; unit 247's fragment has its evidence and the hand line it rests on).
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
# - Their band neighbours with records do not place the file: 3744 (cnomearquivo.cpp:208) and 3747
#   (dados/md/rdv/cvotoseleicoesvota.cpp:184) for 3745 in band 3, 5725 (api/io/cdatamap.h:143, a header) and 5732
#   (cvotoseleicoesvota.cpp:172) for 5727 in band 2. The file's name and its directory, beside the header that declares
#   them, are chosen.
# - comum::CMesarioRegistrado (cmesarioregistrado.h has the class's evidence): vtable @1594872, [448, 765, 10339, 7480,
#   1661, 218, 425, 10338, 425], and the record cmesarioregistrado.cpp:72, GetControlador's return, which 10339 and 6011
#   (through 10338) load. ProcessInput (10338) is the thunk `f6011(p0, 1594916, 1594944)` of unit 247's paragraph.
# - StartState (10339) is written and differs: `24 over 100 rows (same 76, replaced 20 [16 operand-only], inserted 2,
#   deleted 2)`, the target's calls and slots in the target's order, binaryen's local numbers apart (the scan: `+0x2e
#   target +0x2d local.tee 1 | ours +0x2d local.tee 4`; the record's address and the controllers sit in other locals).
#   Not explained, as unit 135's 10318 and 10383; its vtable slot needs it, so it stays written.
# - GetInst, the constructor and the operator's form (TelaMesarioRegistrado) are written from IGestorDadoMesario::
#   StartState (10337, unit 135's trap), which holds them inlined: the 28-byte object, CAppState's constructor with 2
#   (EVENTO_ENTRADA), the vptr, both forms assigned (fn 1255's at +20, then the builder's at +12, a frame of its own),
#   the builder's buzz (51, 10), the texts @364807, @335481 and @86376 at {1, 1}, {1, 2} and {1, 4}, AddInputControl
#   and GetInteractiveForm("", true). Nothing in the link calls GetInst, so wasm-ld drops the three: they are compared
#   with nothing until 10337 is written (docs/how-to-decompile.md step 5).
# - The statics, @1909736 (s_inst, which 10337 loads and stores) and @1909712 (s_mutex, whose address 10337 passes to
#   the mutex's call): their exit destructors are 10341 and 10340. 10341 reads `unresolved`
#   (`_ZN5comum18CMesarioRegistrado6s_instE (.bss) has no target symbol`) and 10340 `differs` (the census pairs it with
#   vota::CEleitorVotouNaoVotou's s_mutex destructor): no target function that is written uses either address, so no
#   vote names them; they wait for 10337. Their object adds a second local
#   __cxx_global_array_dtor.5 to the link, so step 9 renamed 10760's match line to the one qualified by its object.
# Chosen: the files' paths and names, the order of the definitions in each (cmesarioregistrado.cpp as unit 247's
# cregistrarmesarios.cpp), the class's `final` and its destructor declared first and out of line (as
# CRegistrarMesarios, over the same slots 0 and 1), the members' names, TelaMesarioRegistrado's name, and the
# controller's slot names (its header's). TelaMesarioRegistrado's external linkage is evidence, not a choice: 10337
# holds it behind a frame of its own, the sign unit 247's fragment measured for CRegistrarMesarios's form.
#
# Not written here: 1937 (unit 98's fragment has the measurement), and the rest of the class's file:
# IGestorDadoMesario::StartState (10337) is a trap in unit 135's pending file.
NOMEARQUIVOELEITORES_MESARIOREGISTRADO_SRCS := src/app/comum/nomearquivo/cnomearquivoeleitores.cpp \
    src/app/comum/comparecimentomesario/estados/cmesarioregistrado.cpp
UENUX2_SRCS += $(NOMEARQUIVOELEITORES_MESARIOREGISTRADO_SRCS)
# the unit's callers are not written: 279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp keeps the vtable's
# address and the two name builders the way the target does
$(ROOT)/$(APP)/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.o: $(ROOT)/src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado.mk $(ROOT)/src/uenux2/src/app/comum/nomearquivo/cnomearquivo.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/279-uenux2-nomearquivoeleitores-cmesarioregistrado-roots.o
