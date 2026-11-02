# uenux2 vota::CLogVota (src/app/vota/log/clogvota.cpp, the file its std::source_location records name) and
# vota::CControladorRegistraMesariosVota (src/app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.cpp), with the
# slots of their interface comum::IControladorRegistraMesarios (unit 100's head), and the state its slot 11 returns,
# vota::CRegistroMesarioEncerrado (src/app/vota/eleitor/fimvotacao/cregistromesarioencerrado.cpp). Target fns:
# - 184, CLogVota::GetInst: CPolySingletonList::has<comum::IEventosLog>, then CPolySingleton<comum::IEventosLog>::set with
#   push, both inlined by binaryen (two more stack prologues), then the instance through dynamic_cast to CLogVota&;
# - the controller's 37 slots (10800 down to 10766, with 434 in slot 8), and the bodies binaryen merged some of them into:
#   3887 (slots 31 to 33 in the target, 32 and 33 here: below), 3888 (slots 29, 34 and 36), 6017 (slots 19 and 27);
# - CRegistroMesarioEncerrado's two exit-time destructors, 10765 (the pointer's) and 10764 (the mutex's).
# Matched: 184, 3887, 3888, 6017, 10763 to 10779, 10781 to 10785, 10788, 10791, 10793, 10795, 10796 and 10798 to 10800.
# Slot 8 is the shared 434 (`return true`), matched before. Unit 02 matches 422 and 5451, which
# slot 3 reaches, and names CTickManager::AddTick (3644), which slot 2 (10800) calls, by a `callers+content` hand line.
#
# clogvota.cpp:
# - GetInst's one record, line 37 column 37, is instance()'s default std::source_location: four spaces of indent and
#   `return dynamic_cast<CLogVota &>(` put the call there. That spelling is a choice; any of the same length gives it.
# - The constructor is out of line above GetInst. Measured in the object (wasm-objdump -x): so, its .data.rel.ro has the
#   vtable before GetInst's record and the two typeinfos, the target's order (@1532784, @1532800, @1532816, @1532824);
#   defined in the class, the vtable comes after them.
# - The four Loga members: slots 19, 23, 26 and 27 call GetInst and then run the member in a stack frame of their own (a
#   second prologue), so each is an out-of-line member that binaryen inlined into its one caller. They read +4 and call
#   api::CLoga::loga, so comum::IEventosLog's m_aplicativo is protected (ieventoslog.h). Each names its message before the
#   call: passing the temporary to api::CLoga::loga reads +4 before the message is built, one row out of place (10779
#   `score 13 over 70 rows (same 57, replaced 11 [11 operand-only], inserted 1, deleted 1)`, 6017 `13 over 211`). Their
#   names, lines and order are chosen.
# - LogaMesarioRegistrado and LogaMesarioJaRegistrado are above GetInst, measured: a std::format body emitted before push's
#   moves push's frame slots (unit 100's fragment has the effect on 4879). With no such body above GetInst the link gave
#   184 `score 158 over 947 rows (same 789, replaced 158 [153 operand-only], inserted 0, deleted 0)`, its first slot at
#   +120 of push's frame where the target has +172; with them above it, every row but operands is the target's.
# - Three more members, after LogaTituloInvalidoRegistroMesario and so below GetInst, belong to unit 142's states, which
#   hold them inlined (10594 two, 10421 one); src/units/142-uenux2-app-vota-estados-448.mk has their evidence. They have
#   no target function of their own, and 184 matches with them in the file.
# - Five more members, right after GetInst, belong to unit 161's states: three are held inlined by 10642, 10669 and
#   10444, and two are out of line, 2097 and 4522, matched; src/units/161-uenux2-app-vota-operador-identidade.mk has
#   their evidence, and 184 still matches with them in the file.
# - Seven more, after LogaTituloInvalidoRegistroMesario and before unit 142's three, belong to unit 152's states: five
#   are held inlined by 10416, 10436, 10524, 10758 and 11798, and two are out of line, 4529 and 4535, matched; an eighth,
#   LogaAudioAtivadoConformeCadastro, right after LogaAudioDesativadoFimVotacao, is held inlined by unit 152's 10523,
#   with a second prologue of its own (its name and line are chosen). Last come
#   unit 138's LogaVotacaoEncerrada, which 12058 holds inlined, and unit 169's LogaAguardandoConfirmacaoZeresima, which
#   5958 holds inlined. Fragments 152, 138 and 169 have their evidence, and 184 still matches with them in the file.
# - Four more, after LogaPedidoTituloSuspensao, belong to unit 156's states: LogaImprimindoRelatorio (1127),
#   LogaMesarioIndagadoQualidadeBU (4551), and the two logaAlerta texts binaryen merges into fn 6115,
#   LogaQtdViasAdicionaisExcedeMaximo (4556) and LogaHabilitacaoCanceladaReconhecimentoBiometrico (2495), all out of
#   line; src/units/156-uenux2-fimvotacao-bu.mk has their evidence, and its roots their callers' stand-ins.
# - Four more, after LogaAguardandoConfirmacaoZeresima: unit 138's LogaAguardandoHorarioZeresima and unit 199's
#   LogaDataEleicaoInvalida, held inlined by fns 11871 and 11914 (their fragments have the evidence), and two out of
#   line that this unit matches: LogaErroEstadoAplicativoDesconhecido (fn 3279, logaErro of "Erro estado do aplicativo
#   nao conhecido") and LogaFimTesteTecladoSucesso (fn 4511, loga of "Fim do teste de Teclado do TE - Sucesso"),
#   each 8 over 59 rows, operand-only (pnpm wasm score, whole link), matched by content at step 9. Their target
#   callers are not written (3279: fn 7160 twice and vota::CDefineRotaPosReinicio::NeedChangeState, fn 11858; 4511:
#   fn 11804 twice), so the roots stand in for them. They call fns 2282 and 233 out of line, as unit 156's 1127 and
#   4551 do; their names and their place are chosen.
#
# ccontroladorregistramesariosvota.cpp and the interface:
# - No record names a file of the class. The path is chosen: ledger/tu-clusters.tsv's stretch 346, the slots' run, guesses
#   it by class convention only. The class has a key function in its own .cpp: fn 7160 builds the object (4 bytes, the
#   vptr alone), and the vtable (@1586600) is not among fn 7160's records (@1534296 to @1534560), where a class with no key
#   function would have it (docs/reference/facts/reading.md R6). Which member is first is chosen (AddTick).
# - comum::IControladorRegistraMesarios declares the 35 slots pure: the target has no vtable of the interface, and its one
#   implementer gives the order and the wasm types. Every name is chosen (the interface header says from what); a slot
#   with nothing to name it is SlotN. Every slot but SetTituloMesario is const, here as in the interface, whose header
#   gives the evidence (comum's mesario states call 28 of them through a const reference, unit 135); the const changes
#   the members' symbols and no byte: step 9 renamed the match lines of the 20 const slots matched here and of fns
#   3887, 3888 and 6017 to their _ZNK names.
# - Slots 2 to 4 call the ticks of vota::CThreadOperador (fn 270). CThreadVota::AddTick is out of line in cthreadvota.cpp
#   beside StopTick and StartTick (a choice); binaryen inlines it into slot 2, its one caller. Slots 17 and 18 return and
#   assign +96 of CThreadOperador, unit 116's second string, now m_tituloMesario with an inline getter and setter (chosen:
#   an out-of-line pair was not measured); slots 31 to 33 format it.
# - Slot 30 takes the four scores as a const std::vector<int>& (chosen: it loads a data pointer and four ints, each of
#   type code 3). Slot 12 returns CFinalizaOperador::GetInst() (fn 5342) as comum::CAppState&, a chosen type.
# - Slot 6 (10796) reads the first word of comum::CAppInfo::GetInst().GetVota() (fns 185, 261 with 51), the vote state,
#   and returns 1, 2, 0 and 3 for 55, 56, 57 and 58 (a table at 534720), else 0. The getter's name, GetEstadoVota, is the
#   target's Assert texts' (cestadogeralvota.h says which). No text or record names EEstadoVota's 52 to 58 (the Assert
#   holders compare with 49 to 51 and 59 to 64), so the cases are bare numbers, and the switch is a choice. Same rows,
#   measured on objects at this tree's flags with the call, global and __memory_base numbers masked: the switch with or
#   without `case 57: return 0;`, an if chain over a local, a local set in the switch and returned, and a static table
#   of the four values indexed by the state less 55. The target's dead `local.set 0` of 0 at the entry is the switch's
#   default held in a local, which each of those objects has too (a reading). A --single try returns that local where the
#   target has `i32.const 0` (`score 4 over 23 rows`, 3 of them operand-only); the link gives the target's bytes.
# - Slot 7 (10795) calls comum::CRegistradorMesario::GetInst (fn 815) first, then reads the same state: for 55 and 56
#   it tests the count of period 1 (fn 3606), for 58 the count of period 2 (fn 2727), each `> 5` unsigned, and returns
#   true for every other state. Unit 113 writes those three. GetInst's call comes before the state's read in the target,
#   so the registrador is held in a local first; the switch and its cases as bare numbers are a choice, as in slot 6,
#   and no other spelling was measured.
# - Slot 11 (10793) returns CRegistroMesarioEncerrado::GetInst(), which binaryen inlined into its one caller: the 12-byte
#   new, comum::CAppState's constructor (fn 224) with 1 and the vptr store, the old object freed with no call through
#   the vtable, the mutex's unlock (fn 150). The class is written as unit 104's states with no member are (unit 104's
#   fragment has the measurements behind that shape): final, a private constructor out of line, GetInst with a
#   std::lock_guard in the .cpp, and the statics defined below it, pointer first. The target fits it: the mutex
#   (@1904864) 24 bytes below the pointer (@1904888), the pointer's destructor (10765) ahead of the mutex's (10764) in
#   link order. Evidence: the class, its base and its vtable (RTTI, @1586768); its slots 2 and 6 (10763, 10762), its
#   own, and the base's slots 3 to 5, 7 and 8; the base constructor's argument 1, bit 0, the flag the context reads
#   before it calls slot 6 (cappstate.h), spelled EVENTO_TECLA, that header's chosen name. Each static's other user is
#   its destructor, so the two destructors and 10793 hold each other (docs/reference/splat.md "No circular evidence").
#   Chosen: the path, the guess
#   of ledger/tu-clusters.tsv's stretch 345 (`class-convention`), which lies between this class's stretch 346 and
#   CHorarioVotacaoTerminou's 344, and beside this .cpp, whose own path is chosen; GetInst's name, the statics' names, the
#   local, and ProcessKey's name (cappstate.h's).
# - Slot 28 (10774), LogaLimiteMesariosAtingido, calls comum::IEventosLog::logaAlerta (fn 1398, unit 111's file) on
#   CLogVota::GetInst() with std::format of the target's literal (ledger/strings.tsv 4576, 58 bytes, with its accents)
#   and one argument of type code 6, libc++'s __arg_t::__unsigned: an unsigned type of 32 bits or less, so `6u` is a
#   choice among those.
# - The members are defined in slot order, a choice, but slots 10 and 15: the band puts 10793 (slot 11) above 10792
#   (slot 10) and 10788 (slot 17) above 10787 (slot 15), so slot 10 follows slot 11 and slot 15 follows GetTituloMesario.
# - Slots 10 and 15 (10792, 10787) post 11 and 7 to vota::CThreadEleitor's queue through fn 6018, which the target keeps
#   out of line under them and which reads nothing of the object it is passed: a const member, EnviaMensagemEleitor
#   (name chosen), with api::CPriorityMessageQueue's Post (unit 174's fragment). In this .cpp clang inlines it into both
#   slots (measured on a scratch TU of the same shape, a class with the const helper and two const callers at this
#   tree's flags: both callers hold the post inlined and no call), so it is in a TU of its own, ccontroladorregistramesariosvotamensagem.cpp (fragment 174's source; the file
#   name is chosen). Written, not matched: the target's 6018 is (i32 i32)->() and keeps the unused first parameter,
#   where our link's binaryen drops it, so the slots pass one argument less (`pnpm wasm score` against the link: 6018
#   `score 9 over 27 rows (same 18, replaced 7 [7 operand-only], inserted 1, deleted 1)`, 10792 `score 2 over 5 rows`,
#   one row deleted, the slot's `local.get 0`). No form found keeps the parameter; the slots read `unresolved`, their
#   callee 6018 having no name.
# - CRegistroMesarioEncerrado::StartState (10763) is written after the statics: the band puts their destructors (10765,
#   10764) above it. It stores `this` as the next state and posts 14 to vota::CThreadEleitor's queue with Post.
#
# Written, and what each waited for (all three match now):
# - 10771, slot 31: its literal is 44 bytes, and at -O2 its std::format kept the search of the literal for a brace
#   (`score 253 over 255 rows (same 2, replaced 4 [1 operand-only], inserted 249, deleted 0)`); the target has none, which
#   is -O3's limit (docs/reference/facts/reading.md R13). At the tree's -O3 it matches, a thunk into 3887 with slots 32
#   and 33, and binaryen names 3887 after it (the rename of 3887's line in splat/matched.txt).
# - 10800, slot 2: it was `unresolved` while its call named no target function, and matches since CTickManager::AddTick
#   (3644) is named (unit 02's fragment); 3644 itself matches since src/api/ builds with strict aliasing.
# - 10774, slot 28: the same limit. At -O2 its std::format keeps the search of the 58-byte literal for a brace (a loop
#   and two br_table over `i32.const 123`; the target has none): `pnpm wasm score` against our link reads `52 over 216
#   rows (same 164, replaced 11 [11 operand-only], inserted 35, deleted 6)`. With this unit's four files at -O3 in a
#   whole-link try (`tools/round/try-tu.sh --flags -O3 --skip-units 119-uenux2-ccontroladorregistramesariosvota.mk
#   --component uenux2/src/app/vota/eleitor/fimvotacao --roots <this unit's -roots.cpp>` over clogvota.cpp,
#   ccontroladorregistramesariosvota.cpp, cregistromesarioencerrado.cpp and the -pending.cpp), the
#   score is `11 over 181 rows (same 170, replaced 11 [11 operand-only], inserted 0, deleted 0)`, and `pnpm wasm
#   splat-remap --against 10774` prints IDENTICAL, operand kinds verified, with logaAlerta's name for 1398 added to a
#   copy of the symbol file (splat-remap reads no match list). At the tree's -O3 it matches.
#
# Pending (119-uenux2-ccontroladorregistramesariosvota-pending.cpp names each and what it waits for): the controller's
# slots 5, 9, 13, 14 and 16 (fns 10797, 10794, 10790, 10789, 10786), and behind them fns 4662 and 5343;
# CRegistroMesarioEncerrado's ProcessKey (fn 10762).
#
# Roots: the controller's vtable in a sink (fn 7160, its builder, is not written). CLogVota::GetInst's callers are the
# slots, and CRegistroMesarioEncerrado::GetInst's is slot 11, so neither has a stand-in.
CCONTROLADORREGISTRAMESARIOSVOTA_SRCS := src/app/vota/log/clogvota.cpp src/app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.cpp src/app/vota/eleitor/fimvotacao/cregistromesarioencerrado.cpp
UENUX2_SRCS += $(CCONTROLADORREGISTRAMESARIOSVOTA_SRCS)
CCONTROLADORREGISTRAMESARIOSVOTA_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/119-uenux2-ccontroladorregistramesariosvota-pending.o: $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota.mk $(CCONTROLADORREGISTRAMESARIOSVOTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/119-uenux2-ccontroladorregistramesariosvota-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/119-uenux2-ccontroladorregistramesariosvota-pending.o
$(ROOT)/$(APP)/119-uenux2-ccontroladorregistramesariosvota-roots.o: $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/119-uenux2-ccontroladorregistramesariosvota.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/119-uenux2-ccontroladorregistramesariosvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/119-uenux2-ccontroladorregistramesariosvota-roots.o
