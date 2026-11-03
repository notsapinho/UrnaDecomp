# uenux2 comum constructors that no record names, each defined out of line: comum::md::CComparecimentoMesario's two
# (target fns 2731 without an id_arquivo and 2730 with one, defined in that order) in
# app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp, and comum::md::CComparecimentoMesarioPK's (2738) in
# app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp, vota::CRegistraDigitalOperador's file (its records'
# path), which no unit compiled before (the class's members came later: below). All three match. The fourth
# constructor of the kind, comum::CEleitorDadosHabilitacao's (2733), is in unit 142's cmostraeleitorvotando.cpp, which
# has its evidence.
#
# Evidence, read in the target:
# - The layout is unit 91's ccomparecimentomesario.h: each constructor stores its arguments at those offsets, copying
#   the identity's std::string inline or through __init_copy_ctor_external (fn 138). CComparecimentoMesario's copies its
#   date as 12 bytes from an address; 2730 stores id_arquivo's value and 1 in the std::optional's flag, 2731 clears the
#   optional's null byte and flag: std::optional<int>'s two constructors. The parameters' order is each wasm
#   signature's.
# - Out of line, and 2738 in another TU than 2730 and 2731. The target keeps their calls: 2730 and 2731 from 10401 and
#   10402 (unit 91's DAO), and 10337 (not written), 2738 from 2730, 2731, 3614 and 10313. Defined in its class, each is
#   inlined where the target calls it: compiled alone at the tree's flags, the DAO's TU against a header that defines
#   all three in their classes calls none of them, and ccomparecimentomesario.cpp against one that defines only the
#   key's constructor there calls __init_copy_ctor_external twice where the target's 2730 and 2731 call 2738. Out of
#   line, a call of the complete constructor (C1) stays a call even in the constructor's own TU at -fPIC
#   (docs/reference/facts/codegen.md C6; a caller compiled in one TU with the key's constructor keeps its call), but
#   2730 and 2731 call the base's constructor (C2, no alias), which clang inlines in their TU: so 2738's TU is another.
# - The calls name them: splat/symbol_addrs.txt gives 2730 and 2731 `pair-fingerprint` and 2738 `pair-addr` evidence.
#   Before steps 7 to 9, pnpm wasm score gave 2738 1 over 35 rows (then in a file of its own) and 2730 and 2731 0
#   over 30, all operand-only.
#
# Placement. No record names a file, so step 3's rule 2 places each by its neighbours in its use band (uses 4,
# ledger/ordinals.tsv; inside a band a higher index links earlier) and by the data:
# - 2738 links after confirmaidentidade/cpededigital.cpp's 2739 and before 2735, CVerificaDadoEleitor::GetInst
#   (cverificadadoeleitor.h; stretch 1081 of ledger/tu-clusters.tsv, labelled cpededigital.cpp). In the data, between
#   cpededigital.cpp's record (@1591932) and CVerificaDadoEleitor's vtable (@1592712), lie the vtables of
#   CTentativaCapturaDigitalEsgotada and CDigitalNaoCapturada (no .cpp record), cregistradigitaloperador.cpp's object
#   (CRegistraDigitalOperador's vtable @1592424, records @1592468 to @1592596) and CDadoEleitorNaoConfere's vtable: the
#   one recorded file between is confirmaidentidade's, and so is the upper end's (cpededigital.cpp); the lower end's
#   file, cverificadadoeleitor.cpp, is unit 161's choice in that directory. So the directory is
#   app/vota/operador/confirmaidentidade/, against the class's namespace (rule 2 wins over it). The file is a choice
#   among those objects: cregistradigitaloperador.cpp, the recorded one, holds 3614, one of 2738's callers (records :328
#   and :371), and a small class one file constructs can be defined there (docs/reference/facts/placing.md P2). A file
#   named after the class there (rule 4) is the other reading; no data place it. The constructor's lines, after the
#   records of the class's own members (95 to 371; StartState's are written now: below), are chosen (src/README.md
#   "Gaps").
# - 2731 and 2730 link after aguardaeleitor/csuspensaoautomaticaeleitor.cpp's 2732 and before
#   comparecimentomesario/estados/cpedetitulomesario.cpp's 2729 (stretch 1080, labelled
#   csuspensaoautomaticaeleitor.cpp). In the data CSuspensaoAutomaticaEleitor's vtable (@1593264) and record are
#   followed by comum::dao::CComparecimentoMesarioDAO's vtable (@1593352) and dao/ccomparecimentomesariodao.cpp's record
#   (@1593396), the object of their callers 10401 and 10402: the data support that file. md/, the directory of the
#   class's header, in the comparecimentomesario/ tree whose estados/cpedetitulomesario.cpp (2729's) the band reaches
#   next, is kept instead, a choice (docs/reference/facts/placing.md P5), and the file is named after the class (rule
#   4). 2731 is defined first, as it links first (docs/how-to-decompile.md step 3, "The order of two members").
# Chosen too: the header's path, unit 91's (rule 1: such a path names nothing; 2730, 2731 and the DAO include it, and it
# stays); the parameters' names; the date taken by reference (the callers pass an address, which a by-value class
# parameter gets too); the member-initializer lists. cregistradigitaloperador.cpp builds with strict aliasing
# (UENUX2_TBAA_DIRS) where md/ does not: compiled with -fno-strict-aliasing too, its object is byte-identical. No roots
# file: the DAO's RecuperarID and RecuperarTodos (unit 91) call the three, as the target's 10402 and 10401 do.
#
# vota::CRegistraDigitalOperador's members, written in cregistradigitaloperador.cpp before 2738's constructor, extend
# this unit (src/units/README.md "Landing a unit" item 2). Target fns matched: GetInst 5396, with the constructor and
# its two form builders inlined; StartState 10454; ProcessInput 10452; the statics' exit destructors 10457 and 10456;
# and 3886, the body binaryen forms from three statics' exit destructors, with 10321 (unit 135's) and 10682 (unit
# 161's), which match through it. Evidence (cregistradigitaloperador.h has the class's RTTI, vtable and layout):
# - The class: its vtable @1592424 [1537, 3629, 10454, 7480, 1661, 10453, 425, 10452, 10451] is stored by 5396 alone
#   (its vptr 1592432: /usr/bin/grep -rlE 'i32\.const 1592432($|[^0-9])' build/out/splat/pieces/asm). Slots 0 and 1 are
#   the bodies comum::CPedeDigitalMesario and vota::CPedeIdentidade share (1537 and 3629, matched as
#   CPedeDigitalMesario's): a final class with its destructor out of line, releasing +24 then +16.
# - GetInst (5396, 1586 B, no record), the project's singleton (unit 135's CPedeDigitalMesario::GetInst, unit 161's
#   CPedeIdentidade::GetInst): s_inst @1909148 and s_mutex @1909124 (its unlock, fn 150, at the end), a new of 36 bytes
#   and the constructor inlined: CAppState's with 6 (EVENTO_ENTRADA | EVENTO_TICK), the vptr, the bytes
#   CThreadOperador::GetInst().AddStoppedTick (fns 270, 807) returns for 15000 and 50 at +11 and +12, the form at +16
#   and the second at +24 (fn 301 writes each in place), then 3 at +32. Each form is built behind a stack frame of its
#   own (64 and 48 bytes) inside the constructor's code, so each is a function binaryen inlined:
#   TelaRegistraDigitalOperador (AddLed(LED_OPERACAO_0); "MESÁRIO:", "Posicione seu dedo POLEGAR ou INDICADOR", "sobre o
#   sensor" and "CORRIGE: não habilitar" at {1, 1} to {1, 4}, on the left; AddInputControl; GetInteractiveForm("",
#   true)) and TelaDigitalCapturadaOperador (AddLed(LED_OPERACAO_0); AddBeep(1); "Digital capturada" at {20, 1} and "Por
#   favor aguarde" at {20, 3}, centred; GetInteractiveForm("", true)). Both have external linkage, and clang keeps both
#   out of line (wasm-objdump -x of cregistradigitaloperador.cpp.o lists them), as unit 135's builder of the same shape,
#   whose fragment measured that clang inlines one of the anonymous namespace into the constructor.
# - StartState (10454, records :95 and :98, column 5): CLogVota::GetInst (`call 184` at +0xc, after StartState's own
#   frame opens) and then a 16-byte frame that builds "Solicita digital do mesário" and calls IEventosLog::loga (fn
#   233), the shape of the CLogVota members unit 161 reads as held inlined (vota::CLogVota::LogaSolicitaDigitalMesario,
#   added to clogvota.cpp, unit 119's file); the form at +16 shown (slot 2); CPolySingleton<IFingerScanner>::instance()
#   (fn 816, record :95) slot 7 with 2; the ticks at +11 and +12 started (fn 700); instance() (record :98) slot 3; and
#   this as the next state.
# - ProcessInput (10452): Read() of the form at +16; on CORRIGE (5) it stops the two ticks (fn 422), logs through
#   CLogVota::LogaHabilitacaoCanceladaCapturaDigitalMesario (fn 4522) and goes to CPedeIdentidade::GetInst's (fn 652).
# - The statics' exit destructors: 10457 is `f3886(p0, 1909148)`, s_inst's, and 10456 s_mutex's (`f150(1909124)`); both
#   link above StartState (10454) in use band 1 (ledger/ordinals.tsv; a higher index links earlier), so the statics are
#   defined above it.
# - 3886 (32 B) is the body of three statics' std::unique_ptr destructors over the shared D2 1537: CPedeDigitalMesario's
#   (10321), this class's (10457) and CPedeIdentidade's (10682), its three callers (ledger/callgraph.tsv). With this
#   class's static in the link, ours holds the three, binaryen forms the body as the target did (it matches under
#   byn$mgfn-shared$__cxx_global_array_dtor@app/uenux2/src/app/comum/comparecimentomesario/estados/cpededigitalmesario.cpp.o),
#   and 10321 and 10682 match as its thunks, each re-pointing through its own s_inst's name: 10682's is what unit 161's
#   652 waited for (unit 161's fragment). With 10321 matched, the hand line that named
#   comum::CPedeDigitalMesario::s_inst for unit 71's 10313 carried nothing and went: weighed alone
#   (splat/symbol_addrs.txt without it, the match list without 10313 and 10321, the scan run twice beside a control with
#   every line, then splat-build on both copies), both sides kept 11905 match rows, 10313 and 10321 among them, and
#   built the target's sha256.
# Chosen: every member's and data member's name; the builders' names and their linkage; the CLogVota member's name and
# its place in clogvota.cpp; the `if` spellings; the lines but the records' (the destructor, the statics, the builders,
# the constructor and GetInst above StartState, ProcessInput between FinishState's records and ProcessTick's, the band's
# order).
# Pending (221-uenux2-app-comum-constructors-pending.cpp says what each waits for): FinishState (10453: written with
# comum::CPedeDigitalMesario::FinishState, 10315, it forms 6012) and ProcessTick (10451);
# BiometriaMesarioPresenteNosEleitores (3614) is declared and not written. The stand-in for 5396's other caller (10443)
# and the vtable sinks of the two states 10451 holds inlined are in unit 278's roots, beside those states' classes.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_CONSTRUCTORS_SRCS := src/app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp \
    src/app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp
UENUX2_SRCS += $(APP_COMUM_CONSTRUCTORS_SRCS)
# vota::CRegistraDigitalOperador's members not reconstructed: 221-uenux2-app-comum-constructors-pending.cpp gives its
# vtable trapping bodies, compiled with UENUX2_CXXFLAGS, as unit 161's pending file is
$(ROOT)/$(APP)/221-uenux2-app-comum-constructors-pending.o: $(ROOT)/src/units/221-uenux2-app-comum-constructors-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/221-uenux2-app-comum-constructors.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/221-uenux2-app-comum-constructors-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/221-uenux2-app-comum-constructors-pending.o
