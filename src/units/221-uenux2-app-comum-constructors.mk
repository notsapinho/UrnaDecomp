# uenux2 comum constructors that no record names, each defined out of line: comum::md::CComparecimentoMesario's two
# (target fns 2731 without an id_arquivo and 2730 with one, defined in that order) in
# app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp, and comum::md::CComparecimentoMesarioPK's (2738) in
# app/vota/operador/confirmaidentidade/ccomparecimentomesariopk.cpp, a file of its own beside
# vota::CRegistraDigitalOperador's (below says why; that class's members extend this unit: below). All three match. The
# fourth constructor of the kind, comum::CEleitorDadosHabilitacao's (2733), is in unit 142's
# aguardaeleitor/celeitordadoshabilitacao.cpp, a TU of its own, and unit 142's fragment has its evidence.
#
# Evidence, read in the target:
# - The layout is unit 91's ccomparecimentomesario.h: each constructor stores its arguments at those offsets, copying
#   the identity's std::string inline or through __init_copy_ctor_external (fn 138). CComparecimentoMesario's copies its
#   date as 12 bytes from an address; 2730 stores id_arquivo's value and 1 in the std::optional's flag, 2731 clears the
#   optional's null byte and flag: std::optional<int>'s two constructors. The parameters' order is each wasm
#   signature's.
# - Out of line, and 2738 in another TU than 2730 and 2731. The target keeps their calls: 2730 and 2731 from 10401 and
#   10402 (unit 91's DAO), and 10337 (unit 135, written), 2738 from 2730, 2731, 3614 and 10313. Defined in its class, each is
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
#   app/vota/operador/confirmaidentidade/, against the class's namespace (rule 2 wins over it). The file is not the
#   recorded cregistradigitaloperador.cpp, though 3614, one of 2738's callers, is there: the target's 3614 uses the
#   constructor's returned `this` as the map key it builds (`call 2738; local.tee`), as 2730, 2731 and 10313 do, and
#   with the constructor defined in cregistradigitaloperador.cpp the object drops that result at 3614's call, where with
#   the constructor only declared there it keeps it (llvm-objdump -d of the object compiled each way; in the whole link,
#   3614 is 346 over 2200 rows so, against 132 over 2174 with the file of its own).
#   So the file is the other reading, one named after the class there (rule 4), which no data contradict; its name,
#   its lines and its place in this unit's list are chosen.
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
# parameter gets too); the member-initializer lists. ccomparecimentomesariopk.cpp builds with strict aliasing
# (UENUX2_TBAA_DIRS) where md/ does not: compiled with -fno-strict-aliasing too, its object is byte-identical (cmp). No
# roots file: the DAO's RecuperarID and RecuperarTodos (unit 91) call the three, as the target's 10402 and 10401 do.
#
# vota::CRegistraDigitalOperador's members, written in cregistradigitaloperador.cpp, extend this unit
# (src/units/README.md "Landing a unit" item 2); unit 278's list compiles that file and unit 214's
# ccontroladorreconhecimetomesario.cpp, after the two states (the order of the objects, below). Target fns matched:
# GetInst 5396, with the constructor and its two form builders inlined; StartState 10454; ProcessInput 10452; the
# statics' exit destructors 10457 and 10456; and 3886, the body binaryen forms from three statics' exit destructors,
# with 10321 (unit 135's) and 10682 (unit 161's), which match through it. Evidence (cregistradigitaloperador.h has the
# class's RTTI, vtable and layout):
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
# Chosen: every member's and data member's name but the overrides' (StartState, FinishState, ProcessInput,
# ProcessTick and the destructors are comum::CAppState's slots, app/comum/cappstate.h); the builders' names and their
# linkage; the CLogVota member's name and
# its place in clogvota.cpp; the `if` spellings; the lines but the records' (the destructor, the statics, the builders,
# the constructor and GetInst above StartState, ProcessInput between FinishState's records and ProcessTick's, the band's
# order).
# FinishState (10453) is written at its records' lines (104 and 105, column 5: instance<api::IFingerScanner>() with slot 7
# given 0, then slot 6); with comum::CPedeDigitalMesario::FinishState (10315, unit 135) it forms binaryen's 6012, as in
# the target, and the three match.
# GetInst (5396) needs no stand-in: its two target callers, 10458 (unit 278) and 10443 (unit 161), are in the link.
#
# ProcessTick (10451, slot 8, 6996 B, records :143 to :145) matches, with its callee BiometriaMesarioPresente (3614,
# 4765 B), named by the srcloc-anchor of the records it holds, comum::CControladorReconhecimentoMesario::ComparaDigitais
# (5372, unit 214's file), the hinted emplace of std::map<md::CEleitorIdentidade, md::CComparecimentoMesario> (5376,
# from cregistradormesario.cpp's object) and the five __func members of SalvarBiometriaMesarioNaoRegistrado's lambda
# (10294 to 10298). What the target holds, read with pnpm wasm fn and lift (the headers name each piece):
# - On the capture tick (+11): both ticks stopped, +32 decremented; at 0 it is set back to 3, the next state is
#   vota::CTentativaCapturaDigitalEsgotada and LogaHabilitacaoCanceladaCapturaDigitalMesario (fn 4522) logs it,
#   otherwise the next state is vota::CDigitalNaoCapturada; each GetInst and constructor inlined (their headers).
# - On the wait tick (+12): the detection, scanner and urna singletons (records :143 to :145; fns 3615, 816, 923); up
#   to three captures (slot 4), each checked against slot 0's size, its entropy computed (a std::map<uebyte, int> of
#   its bytes in ProcessTick's own frame, then the sum of p * log2(p) in doubles: fn 2972, musl's log2, and the
#   `f64.lt` against -4.0) before the urna's model is tested (2009, 2010, 2020 and 2022 keep the capture at once), the
#   one of highest entropy above 4 kept; then, when the detection's slot 2 accepts it: the second form, the scanner's
#   slot 7 with 1, InvertColors up to model 2019 and VerticalFlip, CConversorWsq's WSQ and its std::make_shared copy,
#   assigned to CControlaReconhecimento's s_digitalRegistrada (@1908684); IdentificaMesario's frame; the two ticks
#   stopped; vota::impl::IInformacaoThreadOperador::GetInst()'s slot 12 (SetBiometriaOperador) and
#   CInformaEleitorPodeVotar::GetInst() as the next state.
# - IdentificaMesario: the three searches, each over a map comum::CRegistradorMesario builds (its three Get* members),
#   calling 3614 for each node with the comparecimento's id_arquivo or 999999 and logging LogaMesarioHabilitouEleitor
#   (fn 3258) for the one found; when none is, the digital is compared (5372) with the first six files of
#   comum::ListaArquivosNaoRegistrados (fn 5374), and either a match is logged, or LogaCapturadaDigitalMesario and the
#   message that none matched are, and SalvarBiometriaMesarioNaoRegistrado stores it through GravaWsq (fn 5371).
# - 3614: BiometriaMesarioPresenteNosEleitores inlined first (the registered digital's template; the mesario's
#   comparecimento of period 1 through CRegistradorMesario's Find and CComparecimentoMesarioPK, fn 2738; the fingers to
#   try, its dedo_habilitacao, or 1, 6, 2 and 7 when it has none, false at once for a finger 0; a copy of
#   comum::CEleitores's records, the mesario found in it, and for each finger it has its minutiae against the template,
#   IFingerMatcher's slot 2 with the controller's limit, record :371); then CControlaReconhecimento's s_dedoRegistrado
#   emptied and, when the mesario is found, set to the identifier, the logs of the outcome, and the registered file
#   "me{:06}.wsq" of the id_arquivo compared (5372) when the voters' biometry did not match.
# The forms the bytes asked for, each measured on the whole link (pnpm wasm score at the default depth, the variant's
# object or link line swapped into a copy of link.cmd: docs/reference/facts/workflow.md W13):
# - the entropy's counts as a std::map<uebyte, int> that a function returns by value (ContaOcorrencias, over the
#   image's begin and end, called by CalculaEntropia; both functions, their names and linkage are chosen): the map's
#   construction then stores its root and size first and its begin node after, the target's order. Built in
#   CalculaEntropia's own body, clang stores the begin node first in every form tried (the iterators read before the
#   map or after it, a range-for, a span, a reference, the helper inlined or not, `{}` or a comparator or an
#   allocator given to the constructor: the object, wasm-objdump of each variant compiled at the file's flags), and in
#   the landed order 10451 is 204 over 3257 so (3 rows inserted, 3 deleted). The helper over a const
#   std::vector<uebyte>& with a range-for, or an immediately invoked lambda in CalculaEntropia, give 10451 byte for
#   byte (wasm-objdump -d of 10451 in each link);
# - the first six files (in unit 214's ccontroladorreconhecimetomesario.cpp) as std::vector<std::filesystem::path>
#   (std::from_range, std::span(arquivos).first(quantidade)), quantidade the conditional
#   `arquivos.size() >= 6 ? 6 : arquivos.size()`: the target sizes the copy `count >= 6 ? 72 : bytes` and tests the
#   bytes for zero in the second arm only. std::min<std::size_t>(arquivos.size(), 6), with the span or with the
#   iterator constructor (the base's form), and the conditional with the iterator constructor give a select and test
#   begin against end first: 284 over 3266 in the landed order (12 rows inserted, 12 deleted). Same function in the
#   object (wasm-objdump): the count spelled `arquivos.size() < 6 ? arquivos.size() : 6` or written inside first(),
#   std::views::counted(arquivos.begin(), quantidade) for the span, std::ranges::to<std::vector> for the from_range
#   constructor; `> 6` compares with 7, the target with 6. The conditional over std::min and the span are chosen for
#   these bytes; both are the file's own expressions, no library body copied (how-to step 3);
# - the order of the objects (docs/reference/facts/codegen.md C4): the two states' files (unit 278's), this file,
#   ccomparecimentomesarioservico.cpp and cregistradormesario.cpp (unit 113's) and ccontroladorreconhecimetomesario.cpp
#   (unit 214's), in that order, compiled from unit 278's list after the states. 10451 holds the states' GetInst,
#   IdentificaMesario with its three searches, cregistradormesario.cpp's three Get* members and
#   BiometriaPresenteNosNaoRegistrados inlined by binaryen, and the objects' order decides its locals: with the two
#   forms above in the base's order (this file and the comum file in this unit's list, the states after them in unit
#   278's, cregistradormesario.cpp ahead of all in unit 113's) 10451 was 727 over 3278 (24 rows inserted, 20 deleted:
#   the inlined state constructors' locals and a permutation of locals through the capture loop, the searches and the
#   copy of the six files); the states ahead of this file, 267 over 3258 (locals 1, 2 and 9 to 14 permuted); and
#   cregistradormesario.cpp after this file too, 198 over 3254, every row an operand (the four statics' addresses and
#   CControlaReconhecimento's s_digitalRegistrada, before step 8 named them). The comum file ahead of this one gives 348
#   over 3271; ccontrolareconhecimento.cpp or cinformaeleitorpodevotar.cpp moved beside the group, 267 over 3258 both;
#   the servico's object moves with cregistradormesario.cpp, right before it, a choice of the data's order and not a
#   byte need: 815 needs it ahead of cregistradormesario.cpp (unit 113's fragment), and with the servico left in unit
#   113's list 10451 is still 198 over 3254 and 815 still 55 over 519, both operand-only (that order puts 232 fewer
#   pairs in the data's order and inverts 18 fewer); this unit's ccomparecimentomesariopk.cpp stays in its list (198
#   over 3254 moved with them too). Against the target's data (each object's lowest record address, or the address of
#   the vtable of its own class), the move puts 537 object pairs into the data's order and inverts 39:
#   ccomparecimentomesarioservico.cpp and cregistradormesario.cpp now follow 18 objects whose data the target holds
#   after theirs (comum/util/cmonitoraalimentacao.cpp, vota/monitor/cthreadmonitor.cpp, api/ipc/cthread.cpp,
#   api/hwil/euedesligandoerror.cpp, api/hash/chasharquivo.cpp, chashdiretorio.cpp and cmontadorhash.cpp,
#   vota/operador/cthreadoperador.cpp and caguardainicio.cpp, vota/iexecucaovota.cpp, and comum/gravadores/asn/util.cpp,
#   cconversorcorrespresultado.cpp, cconversorurna.cpp, cconversorenvelopegenerico.cpp,
#   cconversorhistoricovotoimpresso.cpp, cconversortipoapuracaosa.cpp, cconversorversoesarquivos.cpp and
#   md/ctipoapuracaosa.cpp, which link in units between unit 113's and unit 278's); ccontroladorreconhecimetomesario.cpp
#   follows cmontadorhash.cpp; and cregistradigitaloperador.cpp follows api/hash/cmontadorhash.cpp and
#   comum/comparecimentomesario/estados/cregistrarmesarios.cpp; 50 pairs hold an object with no such address (counted on
#   the merged link with the pair count of the move's measurement). Placed with this unit instead (the states moved up
#   into this list), the group gives 10451 the same 198 rows and the move 384 pairs in the data's order against 94
#   inverted (counted at b3b6d4bb, where the landed order gave 515 against 33);
# - 2738 in a file of its own (above);
# - the fingers built by reserve(2) and four push_back, where a vector of {1, 6} move-assigned lets clang fold away the
#   8-byte buffer the target keeps (3614 is 144 over 2174 so, 11 rows deleted), and `dedos = {1, 6}` calls
#   __assign_with_size out of line and keeps the vector in the frame (112 bytes against the target's 96: the object);
# - the loop over the fingers by reference, each finger loaded at each use as in the target;
# - the searches as a loop that keeps the identity found and logs after it: with the log inside the loop 10451 was 329
#   over 3290, with std::ranges::find_if 371 over 3292 (the base's order and forms);
# - the file checks as nested ifs that return true from inside, the target's `block (result i32)`.
# ProcessTick's two states' statics (@1909068 and @1909092 CTentativaCapturaDigitalEsgotada's s_mutex and s_inst,
# @1909096 and @1909120 CDigitalNaoCapturada's) are read by 10451, through the GetInsts it holds inlined (each s_inst
# tested for null, set to the 20-byte object whose vptr is the class's, 1592288 or 1592360, the object it held deleted
# through 244; each mutex unlocked through 150), and each by its exit destructor alone (the grep of i32.const <address>
# in build/out/splat/pieces/asm): 10463 and 10460 pass s_inst to 389 (binaryen's body of several statics' exit
# destructors, its match line named after cmaisinformacoes.cpp's), 10462 and 10459 pass s_mutex to 150. Their names are
# step 8's, `vote:8` and `vote:2` by:10451, the srcloc-anchor ProcessTick's records give it; they hold through the four
# destructors' matches, which step 9 added and no symbol line names (docs/reference/splat.md section 3, "No circular
# evidence": the object's static destructor is the second match), so no hand line names them.
# Four rows match besides, from objects this unit does not compile: 10516, the exit destructor of
# CControlaReconhecimento::s_dedoRegistrado (unit 161's ccontrolareconhecimento.cpp), named by 3614's vote now that
# 3614 assigns that static; 2972 (musl's log2) and 12450 (SQLite's logFunc, log2's one other caller in this link),
# `no-candidate` at the base with no log2 in its names, and matches here, where 10451 calls log2 too; and 4689
# (libc++'s ~__split_buffer of locale.o), `differs` on its locals at the base (splat/scan.tsv) and a match here, a
# whole-link match no source of ours holds (docs/reference/facts/splat.md §S10 item 27).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# cregistradigitaloperador.cpp and ccontroladorreconhecimetomesario.cpp compile from unit 278's list (above).
APP_COMUM_CONSTRUCTORS_SRCS := src/app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp \
    src/app/vota/operador/confirmaidentidade/ccomparecimentomesariopk.cpp
UENUX2_SRCS += $(APP_COMUM_CONSTRUCTORS_SRCS)
