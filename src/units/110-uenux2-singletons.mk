# uenux2 singletons over binaryen's body 1406: the nine GetInst (target fns 187, 273, 326, 407, 555, 1073, 1926, 2812,
# 2817), their mutexes' and pointers' exit destructors, and the classes' own destructors. Sources here are the files of
# CEleitores, CHV, CPE, CRespostas, CValidadorIdentidade and CTelasVota; ccargos.cpp and cconfiguracaoeleicao.cpp are unit
# 88's and crdvvota.cpp unit 13's, and their GetInst are described here. The macro is
# src/ecourna/api/pattern/singleton.hpp.
#
# What the target shows:
# - 1406 is formed, it has no source: every thunk is f1406(mutex, record, message, pointer). With the nine in the link
#   binaryen forms the same body, with the same four parameters in the same order, under the first GetInst in link order.
#   Its throw is CPatternError's 1303 through 331, and its 150 unlocks: `mutex::lock` leaves no call (R15) and uenux2's
#   flags leave no landing pad, so the throw path has no unlock.
# - The record's column is 46 or 47 plus the class name's length. In CHV, CPE, CRespostas and CRdvVota the next record is
#   CreateInst's throw five lines down, room for a blank line, its head, `{` and `if`, so GetInst's line is the whole
#   member; in CCargos and CTelasVota the next line is a second such record, CreateInst's. The +46 classes' next records
#   are further down and say nothing. __builtin_COLUMN reports the end of a macro's expansion, and each record here is the
#   target's with the column at the `)` of the invocation. Compiled over three classes, a definition spelled out gives a
#   fixed column (15 with the throw on its own line, 31 with its `if`), all on one line it grows by two per character of
#   the name, and only macro forms grow by one. The formula holds on two classes not written here (CSubstituidorTitulo,
#   CMonitoraAlimentacao).
#   Records on consecutive lines in two members (CCargos's 24 and 25, CTelasVota's 3434 and 3435) make each member one
#   line, so the macro holds the member and not the throw alone. No bytes hold the macro: that is the reading.
# - The two forms of the column are the two orders of the statics: `.bss` holds the mutex 24 bytes below the pointer for
#   the +47 classes (CCargos, CHV, CPE, CRdvVota, CRespostas, CTelasVota) and the pointer 4 bytes below the mutex for the
#   +46 classes (CConfiguracaoEleicao, CEleitores, CValidadorIdentidade), and in all nine the pointer's exit destructor
#   comes first in link order (its index is the higher of each pair, 11561 over 11560). Measured in the object: GetInst above the
#   definitions `pointer; mutex;` gives mutex, pointer in `.bss` and the pointer's destructor first; the same definitions
#   above GetInst give pointer, mutex and the same destructor order (the object's segment list and the order of its
#   `__cxx_global_array_dtor`s).
# - The pointer is a std::unique_ptr: each exit destructor nulls it, then destroys and frees the old value.
# - Every destructor but CHV's is out of line in its class's .cpp: the exit destructor keeps a call of 37 bytes around
#   5805, 5792, 5773, 5730, 5671, 5598 or 6548, and a non-virtual class shows no D0 to read. Measured on CCargos: implicit,
#   clang inlines the D2 and the object's exit destructor is 114 B; defined in the .cpp the call goes through the D1 alias,
#   which clang does not inline, and it is 51 B there and 37 B in the link, the target's. CHV's calls no destructor:
#   f349(p0, 1838872) only frees.
# - CEleitores is final: fn 5773 opens with no vptr store (R4), though its vtable has one slot. Its tree at +52 is fn
#   1594, the function CConfiguracaoEleicao's tree at +604 calls, so the two share an element type.
# - The caller's object first: cconfiguracaoeleicao.cpp links after ccargos.cpp, as the records' addresses have it, with
#   ccargods.cpp and cfederacoes.cpp between them in the target. The rule is "after": unit 88's list puts it next, and 2836
#   holds at the end of that unit or further on. In this fragment, which sorts ahead of 88, 2836 scores 100 over 283 rows,
#   inserted 4 and deleted 4, its locals swapped (docs/reference/facts/codegen.md C4).
# - 5745's order is measured: with GetHorarioVerao above VerificaEntraEmHorarioVerao in chv.cpp it scores 29 over 293
#   rows, all operand-only, and below it 47 over 298, inserted 5 and deleted 4 (docs/reference/facts/codegen.md C4).
#   binaryen inlines VerificaEntraEmHorarioVerao and CHorarioVeraoMunicipio::GetHorarioVerao into it: its object calls both. binaryen inlines CConfiguracaoEleicao::GetEleicao into
#   2836, from another object. clang inlines the implicit ~CEleicaoPE into __destroy_at<CEleicaoPE> (730) and the in-class
#   predicates and accessors.
# - In CParteRdv::Imprime the predicates read the flag before the type: `has_value() && m_tipo == X` gives the target's
#   `!= 1` and `eqz`, the other order leaves `& 1` on the flag.
# - GetCurrent and GetCurrentEleicao read the cargo before calling GetInst: the target's order, which a local gives. In
#   the argument place the call comes first and the object has 60 rows against 62.
#
# Forms measured, function by function with object-local numbers masked, that give the same rows, so each spelling is a
# choice: for lock_guard, std::unique_lock, std::scoped_lock and the deduced lock_guard; for `!p`, `p == nullptr`, `!p.get()`;
# `= default` or `{}` on the destructor, compared on the D2; a copy of the whole pair for the local in GetCurrent;
# `!(a < b)` for IsFim's `a >= b`; a reference to the element in GetEleicao's loop, or the vector read through the accessor
# each time; in CParteCargos::Imprime a while loop for the for, and the two tests nested. Forms measured that give other
# rows: a reference for the local in GetCurrent, range-for in GetEleicao or in either loop of GetCargo, the two tests
# of Imprime swapped, and in CParteRdv::Imprime a pointer to the chosen part, or three separate ifs.
#
# Chosen, no evidence names them: the macro's name and path, its parameters, `s_instancia` and `s_mutex`, and the one
# character `s_instance` is shorter by for the +46 classes (a shorter mutex or a missing space give the same column). The
# record fixes the invocation's whole length; how the name and the parameters share it is free, so the macro's name is
# fitted to the record and not evidence. Enumerator EPE_SINGLETON_NAO_CRIADO, CCargos's Reset, IsFim and
# GetUltimaEleicaoID (fns 2269 and 602 have no record), CCargo's GetID and three predicates, CPleito's GetEleicoes,
# CHorarioVeraoMunicipio's TemHorarioVerao, the headers' paths beside the records' files, the map keys and element types
# the class heads say are chosen, ETelaVotacao's definition, ctelascargo.h's path, and the lines of the statics, of each
# destructor and of Reset and IsFim. The statics sit below CreateInst's lines in the +47 files.
#
# Records give what a head could otherwise only choose: 1536124 CRespostas's key and element; 1536832 with fn 4135
# CTelasVota's keys and inner element; 1536624 and 1536592 the outer element, vota::CTelasCargo, a TCargoID and a map (2386
# stores the byte, 4135 reads it). Both CEleitores and CRespostas are CDataMaps by record or RTTI: the base's 28 bytes hold
# the map, the cursor and the name, and with the map alone as a member 5773 and 11535 stop matching.
#
# Names: 407, 555, 187, 1073, 1926 and 2817 are srcloc-anchors. Their mutexes hold through their exit destructors, which
# the content pass pairs once the name is voted, and through the thunk. A record held by a function that inlines GetInst
# anchors nothing, so 273, 326 and 2812 have hand edits of `s_mutex`, and CRespostas's pointer one too, with 1929, whose
# twin 1932 stops the census; the content pass then pairs 5730. 555's pointer has one voter, so it has a hand edit too: 555's
# destructor cannot land, and the build refuses the name without its line. 2817's has one voter as well and needs no line:
# its destructor, 11510, holds the address. Each line in splat/symbol_addrs.txt cites what the thunk's own body holds and the
# other holders.
#
# 5805, ~CCargos, has two target callers: 11561, written here, and 7787, which is not. The roots' d5805 stands for 7787 and
# goes when 7787 lands: with 11561 alone binaryen inlines the destructor, 11561 changes shape, CCargos's pointer loses its
# voter, and 273, 11203 and 11209 go with it. 5805's line in splat/matched.txt is no hand edit: step 9 writes it from the
# census's pair.
#
# 5734 and 11495, CRdvVota's destructor and its pointer's exit destructor, match from unit 13's crdvvota.cpp.o: CRdvVota
# holds comum::asn::CConversorRegistroDigitalVoto<CConversorEleicoesVota> at +44 (vptr 1560304), which unit 140 writes;
# its slots 2 and 3 (11483 and 11482) are traps there. The roots' d5734 stands for 7787, which is not written.
#
# comum::RespostaCorrente (fn 11479), the current answer's text, is in crespostas.cpp: it holds GetInst's code (record 28),
# which only that TU can inline, then calls CDataMap<unsigned int, CRespostaConsulta>::GetCurrent (3125) and copies the
# string at +4 of the answer (md/processoeleitoral/crespostaconsulta.h's GetResposta). The target reaches it only through
# table slot 1096, which fn 6652 passes to api::CFormBuilder::AddTextField (1191): the roots take its address. In band 1
# (ledger/ordinals.tsv) it follows the file's exit destructors (11481, 11480), so it is defined after the statics, here
# after CRespostasDSNumero's call operator, a choice. Chosen: its name and GetResposta's, its being a free function,
# crespostasds.h as its header, GetResposta's being inline in the class. fn 11478, the file's other function passed by a
# table slot (3051, by fn 11946), waits for fn 1881, which nothing names.
# Not reconstructed:
# - 11206, CParteEleitores::Imprime, and 11215, CParteCandidatos::Imprime, which waited for 2271: unit 77 matches both
#   since.
# - 242, ~CDetalheCandidato, is written (implicit) and differs: __destroy_at<CSuplencia> costs 245, over -O2's threshold
#   of 225 and under -O3's 250 (-Rpass-missed=inline on cpe.cpp). At -O2 it stays out of line and the small loop goes into
#   the D2; at -O3 it goes into the loop, fn 1135, which is then too costly for the D2. At the tree's -O3 242 scores 96
#   over 152 rows (86 inserted; 79 over 134 at -O2), so the level does not close it, and no source form here does.
# - CEleitores's one slot, 2824, has no body and no vtable of ours: the stub went with the class (src/units/README.md
#   "Pending members"). CreateInst of each class is inlined into 7787 or 2787 and is not written.
# - crespostas.cpp also holds comum::CRespostasDSNumero's call operator, which inlines GetInst in the target (fn 12621,
#   CDataText<CRespostasDSNumero>::GetText, holds this file's record 28): it matches since fn 11973's literal is in the
#   link, and src/units/121-uenux2-datasources.mk, whose roots keep that text's vtable, says what it waited for. Its line
#   is a choice, after the destructor.
#
# CEleitores's members in celeitores.cpp, each throw on its record's line; every other line is blank, and where each member
# starts is chosen:
# - ValidaIdentidadesEleitor (target fn 5765, line 738), matched. It looks for the type at +100 of CEleitores among the
#   voter's identities and throws code 7852 with std::format when none has it. The member at +100 is compared with the
#   identities' type, so it is written with that type (unit 50's header chose it); its name is chosen. Its formatted
#   enum's handle is binaryen's 536 (the formatter<unsigned int> body), which the formatter template in
#   app/comum/asn/util.h gives: the file includes that header for it. std::none_of is written; !std::any_of and
#   std::ranges::none_of print IDENTICAL too (splat-remap on a link with only this object rebuilt), and
#   std::find_if(...) == end() differs, 32 over 262 rows.
# - MarcaEleitorFoiHabilitado (2825, lines 435, 439 and 447) and the Text of four data sources, CEleitorDadoNomeParaUrna,
#   CEleitorDadoSequencial, CEleitorDadoSecao and CEleitorDadoTTE (11529, 11528, 11527, 11526, lines 756, 772, 784, 796;
#   reached only by table slots 3906, 4055, 4056 and 4113, which fn 5401 passes), match at the tree's -O3 and did not at -O2:
#   - the four Text hold GetInst inlined (record 44 lists them), which -O2 keeps out of line: `try-tu.sh --symbols --flags
#     '-Rpass-missed=inline'` on this file prints `cost=230, threshold=225` at each call. In the -O2 link they scored 41
#     over 93, 41 over 251 (twice) and 43 over 371, each with GetInst's 23 rows deleted.
#   - 2825 holds CEleitorDetalhe::MarcaHabilitado (unit 98) inlined by binaryen, and that holds the mesario's member of
#     CEleitorDinamico as a call binaryen inlined. At -O2 clang inlines that member and keeps
#     std::optional<CEleitorIdentidade>::operator= out of line inside it (`cost=235, threshold=225`); at -O3 it inlines
#     operator= (threshold 250) and keeps the member (`cost=250, threshold=250`), the target's shape. 2825 scored 101 over
#     446 rows in the -O2 link.
#   With this object and celeitordetalhe.cpp.o compiled at -O3 in a copy of the link (each make compile line with -O2
#   turned to -O3), the four Text score 24 over 93, 26 over 251 (twice) and 28 over 371, and 2825 41 over 440, all
#   operand-only; splat-remap prints IDENTICAL for the four Text and stops on 2825 only at the call of 1271, which has no
#   name before this unit lands. ValidaIdentidadesEleitor scores 19 over 255, operand-only, at both levels.
#   Forms measured on them: TTE tests !IsTTE() first and returns "" there (the other order: 41 over 101 rows at -O3, 8
#   inserted, 9 deleted); its literal is the tail of the target's "TTE: Transferência Temporária". 2825's third test is
#   an if/else with the call in the if, which lays the three throws out ahead of the call as the target does; with an early
#   throw the object has the call first (compared in the object). The voter's data come from accessors of
#   md::CEleitorDecorator (unit 91's header, which says what each reads); NomeParaUrna's argument is a local string, as
#   std::make_format_args takes lvalues.
# - Not written. LoadEleitorDetalhe (5764, line 719): a body written over a 104-byte md::CEleitor base (fn 946 is its
#   copy: it copies 104 bytes and 5764 copies CEleitorDecorator's +104 after it), CImpedido::GetImpedimentoP2
#   (cimpedido.cpp:46) and CEleitorDetalhe's two constructors (celeitordetalhe.cpp:49) scored 96 over 834 rows, its 6
#   inserted and 6 deleted rows all local numbers. Moving cimpedido.cpp.o, celeitordetalhe.cpp.o or both after this
#   object, -O3 on this object and celeitordetalhe.cpp.o, and twelve source forms (of the impediments, the returns, the
#   constructors and CEleitorDinamico's copy) left them or made more, so it stays unwritten (docs/how-to-decompile.md
#   step 5); it has no stub, since the scan groups it under libc++, and stubs.py writes none there. MarcaVotou (lines
#   456, 460) is held inlined by fn 10210, vota::CSincronismoOperador::StartState (unit 104's pending member), which
#   also calls fn 501, api::CPriorityMessageQueue<api::SMessage>::Insert (unit 174). CompleteLoad (6734), DynamicCreate
#   (5761) and GetCurrentAbrangenciaEleitor (7377, which holds GetInst inlined and calls 501) are not written.
#
# ctelasvota.cpp also holds vota::CTelasVota::GetTelaCargo (target fn 4135, record :3534, code 9358): it looks the post
# up in the outer map and throws with std::format when it is missing, else returns CTelasCargo::GetTela's form. GetTela
# (record ctelascargo.cpp:80) sits in 4135 behind a second stack prologue, so binaryen inlined an out-of-line member
# with one caller: unit 150's ctelascargo.cpp defines it, unrooted. 4135's target callers are the shared
# GetTelaCargoAtual bodies 6050 and 3921 (units 97 and 150, written) and fn 11793 (IConfereVotoEmCargo::StartStateAudio,
# pending). Measured before step 8: 31 over 514 rows, all operand-only (pnpm wasm score, whole link); matched at step 9.
# ctelasvota.h gains four accessors, of the forms at +36, +44, +52 and +124, which fns 3877, 5979, 5959 and 4420 copy
# after CTelasVota::GetInst() (the header says which); their names are chosen. Chosen too: GetTelaCargo's parameter
# names, its local, the find form, and its place above the record (lines 3530 to 3538; the constructor's record :3502
# stays blank). Other forms are not measured. This file's screen builders (13101, 4181, 4184, 6660, 6671, 6678 and the
# rest of its anonymous namespace) are internal, and their only target callers are each other and the constructor, fn
# 7787, which is not written: a reading, not compiled, is that this TU would emit none of them before 7787 is written.
SINGLETONS_SRCS := src/app/comum/dados/celeitores.cpp \
  src/app/comum/dados/chv.cpp src/app/comum/dados/cpe.cpp src/app/comum/dados/crespostas.cpp \
  src/app/comum/dados/md/cvalidadoridentidade.cpp src/app/vota/eleitor/comum/ctelasvota.cpp
UENUX2_SRCS += $(SINGLETONS_SRCS)
# the callers are not reconstructed yet: 110-uenux2-singletons-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/110-uenux2-singletons-roots.o: $(ROOT)/src/units/110-uenux2-singletons-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/110-uenux2-singletons.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/110-uenux2-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/110-uenux2-singletons-roots.o
