# uenux2 comum's mesario states over comum::CAppState, in app/comum/comparecimentomesario/estados/, the directory their
# records name. Target fns matched, by class:
# - the 19 states whose destructors are fns 448 and 765 (six here, CConfirmaFimRegistroMesarios,
#   CEncerraRegistroMesarios, CLimiteMesariosRegistradosAtingido, CTituloMesarioVazio, CTituloMesarioInvalido,
#   CTituloMesarioJaRegistrado): 448, 765 and 763, the shared body of their static pointers' exit-time destructors;
# - CConfirmaFimRegistroMesarios::StartState 10385; CEncerraRegistroMesarios::GetInst 5388 and its statics' destructors
#   10382 and 10381; CLimiteMesariosRegistradosAtingido::StartState 10358 and ProcessInput 10357, and its GetInst 5386
#   (with the constructor and the operator's form) and statics' destructors 10360 and 10359;
#   CTituloMesarioVazio's and CTituloMesarioInvalido's StartState 10353 and 10348, thunks into binaryen's 6010, and
#   ProcessInput 10352 and 10347; CTituloMesarioJaRegistrado::StartState 10343 and ProcessInput 10342;
#   CDigitalMesarioNaoReconhecida::StartState 1070 (one body in twelve states' slot 2) and ProcessInput 10322; 2895, the
#   shared body of the four ProcessInput 10322, 10342, 10347 and 10352;
# - CPedeDigitalMesario's destructors 1537 and 3629 (vota::CPedeIdentidade and CRegistraDigitalOperador share both) and
#   ProcessInput 10317;
# - CGestorDadoMesarioInicial, Votacao and Final, over the new head comum::IGestorDadoMesario: their statics' destructors
#   10336 and 10334, 10333 and 10332, 10331 and 10330, whose reader is unit 104's CGestorDadoMesario::StartState (10327,
#   matched with them: it holds the three GetInst inlined).
# The states read their controller through comum::IControladorRegistraMesarios, now const (its header says why), and
# slot 7 through api::CInteractiveForm<MEDIA, INPUT>::Read(), now written in api/gui/cinteractiveform.h at its record's
# line 57. Both 448 and 765 are named after CConfirmaFimRegistroMesarios, the first object of ours that defines them.
#
# Evidence, each class's head says the rest:
# - 448 stores no vptr (final, docs/reference/facts/reading.md R4) and releases two std::shared_ptr, +20's control block
#   at +24 first, then +12's at +16; 765 is `f448(p0); f136(p0)`, an out-of-line destructor (R5). +12 is the operator's
#   form: slot 7 reads it through Read(), whose record (cinteractiveform.h:57) each file holds a copy of; +20's pointee
#   is chosen as comum::IPedeTituloMesario's +20, the voter's form: fns 5389 and 5386 store into +20 what fn 1255
#   builds, as fn 10388 does for that class (ipedetitulomesario.h). Names: m_form and m_formEleitor are
#   IPedeTituloMesario's, chosen.
# - GetControlador's records give its line and column in each file and its text: a non-static, non-const member
#   returning `const IControladorRegistraMesarios &`. Its body is instance()'s call at column 12, its default
#   source_location. CTituloMesarioJaRegistrado::StartState's own record (line 53, column 32) and unit 104's 10327's
#   (line 35, column 32) are instance() bound to a reference before its first use: `auto& controladorMesario = ` is a
#   chosen spelling of that length.
# - Slot 7 compares Read()'s result with INPUT_CONFIRMA (9) or INPUT_CORRIGE (5), the values iinputfield.h names.
# - The band orders hold in each object (docs/how-to-decompile.md step 3, "The order of two members", checked on
#   build/out/wasm-map/vota_web/names.tsv): the static pointer's destructor, the mutex's, StartState, ProcessInput, so
#   the statics are defined above the slots; the mutex is lower in .bss (fn 5388: @1909488, @1909512), as unit 104's.
# - CEncerraRegistroMesarios's constructor, inlined into 5388, passes 0 to the base's and leaves both forms empty
#   (`i64.store` of 0 at +12 and +20); GetInst deletes the old object with a direct call of 448, as a final class does.
# - CGestorDadoMesarioInicial, Votacao and Final: 10327 clears 11 bytes of each object at alignment 4 (`i32.store align=0
#   offset=7`, `i64.store align=2 offset=0`) before calling fn 224 with 0. Measured on a probe TU at UENUX2_CXXFLAGS (a
#   base `A` of a vptr, a pointer and three bools with `explicit A(int)`, `B : A`, `D final : B`, `new D()`, in eight
#   variants of the constructors, read with wasm-objdump -d): only a derived constructor that
#   value-initializes a base whose default constructor is not user-provided gives those two stores: a value-initialized
#   complete object (the derived constructor not user-provided) gives `i32.store offset=8` and `i64.store align=3`, and a
#   derived constructor that default-initializes the base no clearing at all. That base constructor calls CAppState's with no argument, hence cappstate.h's default argument. Same bytes:
#   the base's constructor implicit or `= default`; `: IGestorDadoMesario{}` for `()`; an inline delegating `CAppState()`
#   for the default argument. The derived constructor is out of line in its .cpp, as unit 104's are: in the class, 10327
#   scored `36 over 159 rows (... replaced 33 [30 operand-only], inserted 3 ...)`, the static pointer stored from the
#   base constructor's result; out of line, `33 over 156 rows (... [33 operand-only] ...)` and a match after step 9.
# - The statics' destructors match where a matched function reads the object (docs/reference/splat.md "No circular
#   evidence"): 5388 for CEncerraRegistroMesarios's, 5386 for CLimiteMesariosRegistradosAtingido's, 10327 for the three
#   Gestor states'.
# - CLimiteMesariosRegistradosAtingido::GetInst (5386), the singleton of 5388's shape (s_inst @1909624, s_mutex @1909600:
#   /usr/bin/grep -rlE 'i32\.const (1909624|1909600)($|[^0-9])' build/out/splat/pieces/asm lists 5386 and their
#   destructors 10360, `f763(p0, 1909624)`, and 10359, `f150(1909600)`). Its constructor is a function of its own that
#   binaryen inlined, its 16-byte frame opening after the new of 28 bytes: fn 224 with 2 (EVENTO_ENTRADA), 0 at +12, the
#   vptr 1594416, 0 at +20, TelaRegistroMesarios()'s result (fn 1255) moved into +20, then instance() with the record
#   climitemesariosregistradosatingido.cpp:53:12 (GetControlador, inlined) and its result unread, then the operator's
#   form moved into +12. The form is built behind a 432-byte frame of its own: the builder (fn 203), "Limite de
#   mesários registrados atingido" (39 bytes @137182) at {1, 1}, std::format("Quantidade máxima permitida: {}" (31
#   bytes @6372), 6) at {1, 2}, its one argument of type code 6 (unsigned: docs/reference/facts/reading.md R13), both
#   aligned left, and "CONFIRMA: Finalizar" at {40, 4} aligned right (1): 19 bytes copied from +17 of "CORRIGE: Voltar
#   CONFIRMA: Finalizar" (@90918, whose whole only fn 5389 loads), the tail of that literal; then AddInputControl (fn
#   395) and GetInteractiveForm("", true) (fn 301). The form's builder, TelaLimiteMesariosRegistrados, has external
#   linkage: in an anonymous namespace clang inlines it into the constructor (wasm-objdump -d of a scratch copy at this
#   directory's flags), where the target keeps its frame apart (docs/reference/facts/reading.md R10; unit 247's
#   fragment measured CRegistrarMesarios's form the same way). The 6, after a GetControlador() whose reference nothing
#   reads: a constant reached through the controller, written as IControladorRegistraMesarios::QUANTIDADE_MAXIMA_MESARIOS
#   (its name, its being a static constant of that class, and std::size_t are chosen; the controller's slot 7, unit 119,
#   compares the counts of mesarios with `> 5`). Measured in the link before steps 7 to 9 (pnpm wasm score at the
#   default depth): `45 over 637 rows (same 592, replaced 45 [45 operand-only], inserted 0, deleted 0)`, the rows that
#   are no call and no data address being the statics' addresses and the table slot 148, fn 7324's
#   (std::__format::__allocating_buffer<char>::__prepare_write, matched), where ours has 43. In this link the literal is
#   a string of its own (5389 is not written), and 5386 matches. Its other target caller, comum::CMesarioRegistrado's
#   slot 2 (10339), is not written: 135-uenux2-comum-mesario-estados-roots.cpp stands for it. Band: 10360, 10359,
#   10358 and 10357 run 3727 to 3730 in ld_index. Chosen: TelaLimiteMesariosRegistrados, its being a free function of
#   comum declared in the class's header, its parameter, and its place at the file's end; the constructor and GetInst
#   above the statics.
#
# Written, not matching:
# - 10380, CEncerraRegistroMesarios::StartState: the scan says `the locals`. The target stores m_pNextState before its
#   stack prologue. It is read as a frameless StartState with an out-of-line member binaryen inlined, a reading: how-to
#   step 3 does not list a store before the only prologue among binaryen's tells. So the switch is in
#   DefineProximoEstado (chosen name), its cases in the target's block order (2, 3, then 0 and 1). Measured
#   with `pnpm wasm score`: the switch in StartState in case order, `117 over 203 rows (same 86 ... inserted 35, deleted
#   36)`; as written, `42 over 174 rows (same 132, replaced 27 [27 operand-only], inserted 6, deleted 9)`, the target's
#   blocks. Left: the object (wasm-objdump -d of cencerraregistromesarios.cpp.o) keeps each case's last instance() call
#   in the case, and our link folds the three into the shared tail where the target keeps one in each case. Not
#   explained.
# - 10383, CConfirmaFimRegistroMesarios::ProcessInput: local numbers only (`25 over 85 rows (... [25 operand-only] ...)`,
#   scan `+0x9 target +0x8 local.tee 1 | ours +0x8 local.tee 2`): the target gives the input field `this`'s local once
#   `this` is pushed for the final store, ours another. The same score with an if/else-if chain for the switch, with
#   GetControlador defined above the slots, and with cencerraregistromesarios.cpp first in this fragment. The case order
#   is measured: CORRIGE first (with a `default: break;`) moves the blocks, `31 over 88 rows (... inserted 3, deleted
#   3)`.
# - The static pointers and mutexes of CConfirmaFimRegistroMesarios (10387, 10386), CTituloMesarioVazio (10355, 10354),
#   CTituloMesarioInvalido (10351, 10350), CTituloMesarioJaRegistrado
#   (10346, 10345), CDigitalMesarioNaoReconhecida (10326 through fn 389, 10324) and CPedeDigitalMesario (10321 through
#   fn 3886, 10320): no reader is written (their GetInst are below), so their destructors' `.bss` names have no voter
#   but themselves. With CEncerraRegistroMesarios's and CLimiteMesariosRegistradosAtingido's, the four static pointers of
#   these over fn 448 are the six members fn 763 forms from here (three form that shape: docs/reference/facts/codegen.md
#   C8); with no GetInst to mention them first, the .bss order of these six classes' statics is a choice, as unit 104
#   says of CQuerReimprimirZeresima's.
#
# Not reconstructed, and what each waits for:
# - GetInst and the constructor of CConfirmaFimRegistroMesarios (5389), which builds both forms with fns 395 (matched,
#   unit 31) and 1255 (matched, unit 247), so no callee holds it back;
#   the other states' GetInst, inlined into callers not written (each vptr is stored in fn 10313,
#   IPedeTituloMesario::ProcessInput, or for CDigitalMesarioNaoReconhecida in fn 10316), and the files' anonymous data
#   sources (10349, 10344, 10323, 10319).
# - comum::CMesarioRegistrado (10339, 10338): 10339 calls 5386, matched, and fn 6011, the shared body of its
#   ProcessInput and comum::CRegistrarMesarios's (10391, pending in unit 247, whose StartState 10392 matches), calls
#   5389. Its stub file stays as it is.
# - The pending traps (135-uenux2-comum-mesario-estados-pending.cpp names each): IGestorDadoMesario::StartState
#   (10337), CPedeDigitalMesario's StartState (10318), FinishState (10315) and ProcessTick (10316). 10318 and 10315 call
#   fn 816, api::CPolySingleton<api::IFingerScanner>::instance by its records, a thunk into binaryen's fn 6013, whose
#   other member is fn 1686, IFingerMatcher's instance; this tree declares neither class.
#
# Chosen, no evidence names them: DefineProximoEstado; every data member's name and CPedeDigitalMesario's +24 pointee;
# the locals; the lines of what each .cpp defines, around the records' lines, which stay where the records put them;
# the headers' paths, beside their .cpp; the three Gestor states' .cpp paths (how-to step 3, rule 4: no record names
# them) and their order here, which follows the band (10336 above 10333 above 10331); the out-of-line destructors as key
# functions, declared first.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
COMUM_MESARIO_ESTADOS_SRCS := src/app/comum/comparecimentomesario/estados/cconfirmafimregistromesarios.cpp \
    src/app/comum/comparecimentomesario/estados/cdigitalmesarionaoreconhecida.cpp \
    src/app/comum/comparecimentomesario/estados/cencerraregistromesarios.cpp \
    src/app/comum/comparecimentomesario/estados/cgestordadomesarioinicial.cpp \
    src/app/comum/comparecimentomesario/estados/cgestordadomesariovotacao.cpp \
    src/app/comum/comparecimentomesario/estados/cgestordadomesariofinal.cpp \
    src/app/comum/comparecimentomesario/estados/climitemesariosregistradosatingido.cpp \
    src/app/comum/comparecimentomesario/estados/cpededigitalmesario.cpp \
    src/app/comum/comparecimentomesario/estados/ctitulomesarioinvalido.cpp \
    src/app/comum/comparecimentomesario/estados/ctitulomesariojaregistrado.cpp \
    src/app/comum/comparecimentomesario/estados/ctitulomesariovazio.cpp
UENUX2_SRCS += $(COMUM_MESARIO_ESTADOS_SRCS)
# IGestorDadoMesario::StartState and three slots of CPedeDigitalMesario are not reconstructed:
# 135-uenux2-comum-mesario-estados-pending.cpp gives the vtables trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/135-uenux2-comum-mesario-estados-pending.o: $(ROOT)/src/units/135-uenux2-comum-mesario-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/135-uenux2-comum-mesario-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/135-uenux2-comum-mesario-estados-pending.cpp -o $(R)
# nothing reconstructed references six of the states' vtables, nor calls CLimiteMesariosRegistradosAtingido::GetInst a
# second time: 135-uenux2-comum-mesario-estados-roots.cpp takes their addresses and stands for that caller
$(ROOT)/$(APP)/135-uenux2-comum-mesario-estados-roots.o: $(ROOT)/src/units/135-uenux2-comum-mesario-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/135-uenux2-comum-mesario-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/135-uenux2-comum-mesario-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/135-uenux2-comum-mesario-estados-pending.o $(APP)/135-uenux2-comum-mesario-estados-roots.o
