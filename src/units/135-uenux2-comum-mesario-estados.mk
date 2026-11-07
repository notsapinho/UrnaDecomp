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
#   matched with them: it holds the three GetInst inlined); IGestorDadoMesario::StartState 10337, the three states'
#   slot 2, whose file unit 279's list compiles (below);
# - CConfirmaFimRegistroMesarios::GetInst 5389, with its constructor and form builder inlined, and its statics'
#   destructors 10387 and 10386; the statics' destructors of CTituloMesarioVazio (10355, 10354), CTituloMesarioInvalido
#   (10351, 10350) and CTituloMesarioJaRegistrado (10346, 10345), whose reader is unit 71's
#   IPedeTituloMesario::ProcessInput (10313: it holds those three GetInst inlined, and CPedeDigitalMesario's);
#   CTituloMesarioInvalidoDS::Text 10349 and CTituloMesarioJaRegistradoDS::Text 10344, thunks into 6009, the body
#   binaryen forms from the two;
# - CPedeDigitalMesario's s_mutex destructor 10320; api::CPolySingleton<api::IFingerScanner>::instance 816 (the copy of
#   cpededigitalmesario.cpp.o, whose StartState calls it) and <api::IFingerMatcher>::instance 1686
#   (cpededigitalmesario.cpp.o's copy now, which ProcessTick calls), thunks into 6013, the body binaryen forms from the
#   two;
# - CPedeDigitalMesario::FinishState (10315), at its records' lines (cpededigitalmesario.cpp:298 and :299, column 5:
#   instance<api::IFingerScanner>() with slot 7 given 0, then slot 6), which with vota::CRegistraDigitalOperador's
#   (10453, unit 221, records cregistradigitaloperador.cpp:104 and :105) forms binaryen's 6012, as in the target: the
#   three match (step 8 names both thunks by srcloc-anchor and 6012 by their calls).
# - CPedeDigitalMesario::ProcessTick (10316), at its records' lines (cpededigitalmesario.cpp:141, 142, 143 and 182, the
#   instance() calls, and 262, ExecutaBatimentoDigitalMesario's), with what it holds inlined:
#   ExecutaBatimentoDigitalMesario (record 262), PararTicks, comum::CalculaEntropia, GetControlador (record 304) and
#   CDigitalMesarioNaoReconhecida's GetInst with its constructor and form; SalvaDigitalMesario (5382), which it calls
#   twice; CDigitalMesarioNaoReconhecida's statics' destructors 10324 and 10326; the CNomeMesariosUrnaDS::Text of
#   cdigitalmesarionaoreconhecida.cpp (10323) and of cpededigitalmesario.cpp (10319), thunks into 6008, the body
#   binaryen forms from the two.
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
#   (std::__format::__allocating_buffer<char>::__prepare_write, matched), where ours has 43; the literal was a string of
#   its own then. With 5389 in the link it is the tail of 5389's string, one copy as in the target, and 5386 matches
#   (splat-review passes both ways). Its other target caller, comum::CMesarioRegistrado's
#   slot 2 (10339), is written in unit 279, and the roots' stand-in for it went. Band: 10360, 10359,
#   10358 and 10357 run 4165 to 4168 in ld_index at 9f0245ef. Chosen: TelaLimiteMesariosRegistrados, its being a free function of
#   comum declared in the class's header, its parameter, and its place at the file's end; the constructor and GetInst
#   above the statics.
#
# GetInst, the constructors and the forms' builders (5389, and the four 10313 holds inlined). Each GetInst is the project's
# singleton, CEncerraRegistroMesarios's form. Each constructor of the 28-byte states stores CAppState's vptr and two empty
# std::shared_ptr, then assigns +20 from TelaRegistroMesarios (fn 1255) and +12 from its builder, each through a
# temporary in a 16-byte frame of the constructor's own, releasing the old pointer after the move: assignments in its
# body. CPedeDigitalMesario's builds its two forms in place in its member list, and its two ticks from the controller's
# slot 2 (AddTick, with 15000 and 50). In the target the constructor and the builder each have a frame of their own, so
# each is a function binaryen inlined: on cconfirmafimregistromesarios.cpp's object (try-tu --symbols, wasm-objdump -d) a
# builder in the anonymous namespace is inlined by clang into the constructor, and one with external linkage stays a
# call. The texts, positions, alignments, the LED and the buzzes are the target's constants. Orders measured in the whole
# link (`pnpm wasm score`; docs/reference/facts/codegen.md C4): in cconfirmafimregistromesarios.cpp the constructor above
# its builder gives 5389 at 33 over 429 rows, all operand-only (a match), and the builder above it 59 over 432 (3
# inserted, 3 deleted: the result's address kept in a local where the target computes it at the call); in
# ctitulomesariovazio.cpp and ctitulomesarioinvalido.cpp the builder is above the constructor, since the other order takes
# 10313 from 202 over 2650 (a match) to 710 over 2672 (22 inserted, 20 deleted). In ctitulomesariojaregistrado.cpp the
# builder has to precede StartState, whose record is line 53, because its data source's Text (10344, first mentioned by
# the builder) precedes StartState (10343) in the band; the constructor is after them. In each file the statics are
# defined above the builder, so their exit destructors precede Text in the object, as the band has them.
# The data sources: each file's anonymous class with a static Text, named and placed by its record (28:36, 29:36 and
# cpededigitalmesario.cpp 47:36); the column falls at the call after `auto& controladorMesario = `, the spelling of
# CTituloMesarioJaRegistrado::StartState's record (53:32), a choice of that length. Text copies the controller's titulo
# (slot 17) into a local and formats it with std::vformat. 6009 forms from the two CTitulo* copies: 10 over 280 rows
# before step 9, all operand-only, and a match after it.
# The roots: the vtable sinks of CConfirmaFimRegistroMesarios, CTituloMesarioVazio, CTituloMesarioInvalido,
# CTituloMesarioJaRegistrado and CPedeDigitalMesario went, since their constructors are in the link (inlined through
# GetInst into 5389 and 10313). ConfirmaFimRegistro, which called 5389 for fn 6011, went: 6011's two callers, the
# ProcessInput of comum::CRegistrarMesarios and CMesarioRegistrado (10391, 10338), are written (units 247 and 279).
# ReconheceDigital, which called CPolySingleton<api::IFingerMatcher>::instance twice for 3614 and 5372, went with the
# roots file: both are in the link (unit 221's and unit 214's files), with 10316, 10465, 10474 and 10482.
# api/hwil/ifingerscanner.h and ifingermatcher.h are new heads, and say what their slots rest on.
#
# Measured, by function (10380 alone does not match):
# - 10337, IGestorDadoMesario::StartState, in igestordadomesario.cpp, which unit 279's list compiles, right after
#   cmesarioregistrado.cpp (unit 279's fragment, "The orders", has the measurement and the count; this list held it
#   before the Gestor states, whose vtables follow its typeinfo in the target's data): GetControlador's record is line
#   65 column 12, `return` and instance() as in the other files. Evidence (pnpm wasm fn): StartState has no frame of its
#   own; it opens with the 96-byte frame of a member binaryen inlined (RegistraMesario, a chosen name; it calls slot 9
#   on `this`) and, after that frame closes, stores CMesarioRegistrado::GetInst()'s result (inlined: unit 279's
#   constructor and form) in m_pNextState. RegistraMesario: CRegistradorMesario::GetInst (fn 815),
#   CControladorReconhecimentoMesario::GetInst (fn 1149, unit 214), the controller's slot 13 (passed as the
#   constructors' bool, pertence_secao's column), the reads of +0, +8 and the 8 bytes at +12 of 1149's object, the
#   controller's slot 17 (GetTituloMesario) copied into the by-value string of md::CEleitorIdentidade's constructor (fn
#   566, TipoIDInscricaoEleitoral); then, by the optional's flag (+16), fn 2730 with its value or fn 2731 without, each
#   after Slot9() and api::CDateTime::Now() (fn 479) and followed by CRegistradorMesario::Registra (fn 5378); then
#   CRegistradorMesario::SaveCurrentInternal behind a 16-byte frame of its own (binaryen inlined it: record
#   cregistradormesario.cpp:85 column 15, written in unit 113's file, its throw code 7754 in
#   euecomumcomparecimentomesarioerror.h, its call the DAO's slot 3 through the servico's new inline Inserir) and the
#   controller's slot 16. It matches (step 9, evidence:srcloc-anchor) with CMesarioRegistrado::GetInst defined above the
#   class's constructor and this file linked after cmesarioregistrado.cpp, both: in the whole link at 9f0245ef (pnpm
#   wasm score, 10337 against ours), `69 over 750 rows (same 681, replaced 69 [69 operand-only], inserted 0, deleted 0)`
#   before step 8, and with either alone `289 over 761 rows (same 472, replaced 268 [264 operand-only], inserted 11,
#   deleted 10)`, as before both: binaryen's local numbers, not renamed one for one (the target's local 0 was ours 1 at
#   70 rows and 0 at 2, its 1 ours 2, 3 or 1). Measured on that link, the object swapped on a copy of the plain link.cmd
#   (docs/reference/facts/workflow.md W13): the estado read before the dedo gives the target's order of the two loads
#   (+0, then +8), the other order `75 over 752 rows (same 677, replaced 71 [71 operand-only], inserted 2, deleted 2)`
#   (298 over 766 at the old order); RegistraMesario defined above StartState, and the next-state store through
#   comum::CAppState::SetNextState, each give the module of the source as written (sha256 4da35798fc27afe9...), so they
#   are same-bytes forms. The statics it reads, through the inlined GetInst, are CMesarioRegistrado's: step 8 names them
#   by its votes, and their exit destructors' matches hold the names (unit 279's fragment, which weighs their hand
#   lines). Chosen: RegistraMesario's name, its being private and non-const, the locals and their const, the
#   std::optional<int> copy, `has_value()`, the temporaries passed to Registra, the assignment of m_pNextState and the
#   order of the two definitions (each against its same-bytes form above), and the lines of igestordadomesario.cpp but
#   the record's.
# - 10380, CEncerraRegistroMesarios::StartState: the scan says `the locals`. The target stores m_pNextState before its
#   stack prologue. It is read as a frameless StartState with an out-of-line member binaryen inlined, a reading: how-to
#   step 3 does not list a store before the only prologue among binaryen's tells. So the switch is in
#   DefineProximoEstado (chosen name), its cases in the target's block order (2, 3, then 0 and 1). Measured
#   with `pnpm wasm score`: the switch in StartState in case order, `117 over 203 rows (same 86 ... inserted 35, deleted
#   36)`; as written, `42 over 174 rows (same 132, replaced 27 [27 operand-only], inserted 6, deleted 9)`, the target's
#   blocks. Left: the object (wasm-objdump -d of cencerraregistromesarios.cpp.o) keeps each case's last instance() call
#   in the case, and our link folds the three into the shared tail where the target keeps one in each case. Not
#   explained.
# - 10383, CConfirmaFimRegistroMesarios::ProcessInput: a match with its two next-state stores through
#   comum::CAppState::SetNextState (unit 61's fragment has why: the target ran binaryen's passes on the body again after
#   inlining a call). With the assignments it read local numbers only (`25 over 85 rows (... [25 operand-only] ...)`,
#   scan `+0x9 target +0x8 local.tee 1 | ours +0x8 local.tee 2`: the target gives the input field `this`'s local once
#   `this` is pushed for the final store, ours another), the same with an if/else-if chain for the switch, with
#   GetControlador defined above the slots, and with cencerraregistromesarios.cpp first in this fragment. The case order
#   is measured: CORRIGE first (with a `default: break;`) moves the blocks, `31 over 88 rows (... inserted 3, deleted
#   3)`. Its StartState (10385) stays an assignment, matched as written: the replay of unit 61's fragment with an empty
#   call binaryen inlines leaves 10385's bytes as they are, so they do not tell the two forms apart.
# - 10318, CPedeDigitalMesario::StartState, matched since its next-state store calls comum::CAppState::SetNextState
#   (cappstate.h): with the store, the target's 257 bytes row for row but for binaryen's local numbers (`42 over 106
#   rows (... [13 operand-only], inserted 12, deleted 12)`: the frame and the record's address are locals 3 and 2 in the
#   target, 2 and 3 here); with the call, 15 over 94, names only (pnpm wasm score on the whole link), and step 9 matches
#   it (`evidence:srcloc-anchor`).
# - 10316, CPedeDigitalMesario::ProcessTick: vota::CPedeDigital::ProcessTick's twin (10465, unit 282: the same three
#   instance() calls at the same columns, the entropy loop over musl's log2f and the map destroy 2223, the model checks
#   2009, 2010, 2020 and 2022, then 2019 before InvertColors), so it takes 10465's measured forms, unit 282's fragment
#   has them: the best image kept through a temporary api::TSharedImageVector, IFingerMatcher's slot 2 returning an int,
#   the minutiae copied through std::vector<api::SXYT>'s copy constructor. It adds the controller's slots 13 and 14,
#   CControladorReconhecimentoMesario's accessors at +0, +4 and +8 (inline in its header, names chosen) and
#   SalvaDigitalMesario. Measured in the whole link (pnpm wasm score against the target, before step 8): `127 over 1684
#   rows (same 1557, replaced 127 [127 operand-only], inserted 0, deleted 0)`, the calls, data addresses and the two
#   .bss words of CDigitalMesarioNaoReconhecida; `splat-remap --no-kinds` stops only on 1149 (a name the match list
#   alone holds) and 5382. Step 9 matches it (evidence:srcloc-anchor).
# - 5382, CPedeDigitalMesario::SalvaDigitalMesario (a chosen name; a member, as it stops this's two ticks, +11 and +12):
#   it holds GetControlador and PararTicks, then, behind frames of their own (64, 80 and 32 bytes, binaryen's inlining
#   of a function with one caller), CControladorReconhecimentoMesario::SalvarBiometriaMesarioRegistrado, named by its
#   lambda's typeinfo (std::__function::__func<...SalvarBiometriaMesarioRegistrado(...)::$_0, unsigned int ()>, whose
#   vtable 5382 stores), comum::ArmazenaImagemMesario and GetPathWsqRegistradoExterno (units 214 and 122). Measured as
#   10316: `43 over 453 rows (same 410, replaced 43 [43 operand-only], ...)`. It matches with its callees 5371 (unit
#   214's, a match) and 2725 (unit 293's), which differs and is named by a hand line, since 5382 is its one caller in
#   our link: weighed by removal (copies of the symbol file and the match list, two scans beside a control keeping the
#   names), the line alone out drops 5382 to `unresolved` and splat-build then refuses 10316 (`UNCONFIRMED:
#   self-voted` on 5382's name).
# - 10319 and 10323, CNomeMesariosUrnaDS::Text of each file, and 6008: the target's 10319 and 10323 are `f6008(p0, p1,
#   <the record>)`, binaryen's shared body of the two. With both in the link ours forms it too. The voter's name is
#   copied in an if over GetNomeUrna's emptiness, each branch with its own substr, as unit 214's GetNomeMesario: with
#   one ternary over the two names `pnpm wasm score` gives 6008 `114 over 494 rows (same 380, replaced 34 [28
#   operand-only], inserted 16, deleted 64)`; with the if `15 over 478`, operand-only, and `splat-remap --no-kinds`
#   prints IDENTICAL. Step 9 matches the three. The hand line that named 10319 for 10313 went: the generated lines name
#   both copies by object now, and without it the scan on copies moves nothing and splat-build gives 12475.
# - The static pointer and mutex of CDigitalMesarioNaoReconhecida (10326 through fn 389, 10324): their reader, 10316's
#   inlined GetInst, matches, and they match through its votes. They are defined below GetInst, which names s_mutex
#   first, so the object puts the mutex 24 bytes below the pointer (llvm-nm of the object), the target's .bss order
#   (@1909852 and @1909876); defined above it, as before, the pointer came first. CPedeDigitalMesario's pointer's
#   destructor (10321) is a thunk into fn 3886, the reset binaryen keeps once for three classes' statics (10321, 10457,
#   10682) over the D2 1537: with the three in the link (vota::CRegistraDigitalOperador's static came last:
#   src/units/221-uenux2-app-comum-constructors.mk) ours is that thunk too, and it matches. It holds the pointer's name
#   for 10313, and the hand line that named it went.
#
# Not reconstructed, and what each waits for:
# - comum::CMesarioRegistrado (10339, 10338) is written in unit 279, whose fragment says what of it matches.
# The pending object went with its last trap, ProcessTick.
#
# Chosen, no evidence names them: DefineProximoEstado; SalvaDigitalMesario and PararTicks, their being members and their
# lines (between ProcessTick's records and FinishState's); comum::CalculaEntropia's name, its being a free function of
# comum declared in cpededigitalmesario.h and its line (vota::CalculaEntropia's form, unit 282: binaryen keeps neither
# out of line); CControladorReconhecimentoMesario's accessors' names; every data member's name; the forms' builders'
# names
# (TelaConfirmaFimRegistroMesarios, TelaTituloMesarioVazio, TelaTituloMesarioInvalido, TelaTituloMesarioJaRegistrado,
# TelaPedeDigitalMesario, TelaAguardeDigitalMesario) and their being free functions of comum declared in the class's
# header (on the object, a static member of the class stays a call too, not measured further); the locals; the lines of what each .cpp defines, around the records' lines, which stay where the records put them;
# the headers' paths, beside their .cpp; the three Gestor states' .cpp paths (how-to step 3, rule 4: no record names
# them) and their order here, which follows the band (10336 above 10333 above 10331); the out-of-line destructors as key
# functions, declared first.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# igestordadomesario.cpp, this unit's, is compiled by unit 279's list, after cmesarioregistrado.cpp (10337, above).
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
# no roots: the last stand-in went (above)
