# uenux2 vota::CVotacaoStateAudio's slot-15 family, two state leftovers and api::CPosixRWMutex.
#
# Slot 15 (a chosen name, GetMensagem: fn 7010 calls it and fills the result's {cargo-atual}-style tags through slot 14)
# of vota::CCandidatoInapto, CConfirmaVotoLegenda, CCandidatoInexistente, CProporcionalBranco and CProporcionalNulo
# (target fns 11748, 11735, 11731, 11704, 11701), each `return "<literal>";`, with their destructors, fns 884 and 883;
# vota::CVotacaoStateAudio's destructor (1035) and the heads of its derived classes CConfirmaVotoEmCargo and
# CConfirmaProporcional, all abstract. comum::CPedeTituloMesarioInicial, Final and Votacao: their D0 (3609), slot 9 and
# the D2 they share with comum::IPedeTituloMesario (1378, unit 71's), and since their GetInst, constructors, forms and
# statics (below, "Written since"). vota::testeteclado::CErroTesteTecladoFim:
# StartState and destructors (3857, one body with CEnviarManutencao's and CTesteFalhou's, 785 and 1560, bodies of eight
# states), over the head of vota::CEstadoComDesligamentoAutomatico; its file, cerrotestetecladofim.cpp, links in unit
# 217's list since that unit wrote its GetInst (unit 217's fragment has why). api::CPosixRWMutex: constructor and destructors
# (10245, 5353, 10244) and slots 2 to 4, which binaryen merges into 2219, api::IRWSyncCtl and six enumerators of
# EUeIpcError. The class headers say what each layout and name rests on. Every member the vtables need is written
# (below), and the unit has no -pending.cpp.
#
# The constructors and two slots, over unit 02's tick names: CVotacaoStateAudio's constructor (1785), StartState (7028)
# and FinishState (7022); CConfirmaVotoEmCargo's constructor (5929) with its two data members; CConfirmaProporcional's
# (11752); CEstadoComDesligamentoAutomatico's (1285). The roots' header says which of their callers are in the link
# (1285's ten are, so its stand-in went). Out of line, by the target: each constructor is a function of its own with two
# callers or more (11752 has one, fn 1961, the body binaryen shares for six builders that each called it). Lines and
# files: StartState and FinishState sit after ProcessInput's record (:69) and before ProcessTick's (:120), as the band
# orders them (7029, 7028, 7022, 7010 in use band 1, the higher index linked first); their exact lines are a choice, and
# so are the constructors' (above the destructor, and in cconfirmavotoemcargo.cpp above GetTelaCargoAtual's record :71,
# and in cestadocomdesligamentoautomatico.cpp above ProcessTick's lambda record :44). CConfirmaProporcional's file,
# votaproporcional/cconfirmaproporcional.cpp, is chosen, beside its header. Measured: CVotacaoStateAudio's tick ids are
# assigned in the constructor's body, after the members' initialisation, as the target stores +24, +16, +11 and the vptr
# before both calls; with the two ids as mem-initializers the object stores +11 and the vptr, makes the first call, and
# stores +24 and +16 only after the second (compiled, wasm-objdump -d). StartState reads the tick id into a local before
# CThreadEleitor::GetInst(), as the target loads +13 before that call: with m_tickMensagem as StartTick's argument the
# link's row read `differs`, `+0x26 target local.get 0 | ours call 316`, the call first. Chosen: the 1000 ms as
# std::chrono::milliseconds(1000), whose rows std::chrono::seconds(1) gives as well (compiled); the event bits with CAppState's
# chosen enumerators (EVENTO_TICK, and EVENTO_ENTRADA | EVENTO_TICK for the 6 fn 11752 passes); that 6 written in
# CConfirmaProporcional's constructor, not passed to it.
#
# The voting states over them. vota::CPedeProporcional and vota::CPedeMajoritario: slot 15 (11710, 11682), out-of-line
# destructors (884, 883), and the singletons' GetInst (3849, 5921), constructors and statics, in unit 104's form; final,
# as fn 6051 deletes through CVotacaoStateAudio's D2. Our link merges the two GetInst into one shared body as the target
# does, and 6051 matches; so do the two mutexes' exit-time destructors (11713, 11685). 3849 and 5921 read `unresolved
# self-voted` on their s_inst until the other reader of each, the std::unique_ptr's exit-time destructor (11714, 11686),
# matches: a thunk into fn 906, a body of docs/reference/facts/codegen.md C8's `m` shape, which forms from three copies
# there; with these two alone it did not form, and the next paragraph's singletons give it the copies.
# vota::CCompletaProporcional: its head and constructor (5932). vota::CPedeNulo and CPedeNominal
# (11745, 11725), vota::CMajoritarioValido, Repetido, Nulo and Branco (11687, 11690, 11693, 11696) and
# vota::CConfirmaVotoNominal (11728): slot 15 and out-of-line destructors. vota::CConfirmaMajoritario: its head,
# constructor (11700) and slot 16 (11699), and CConfirmaProporcional's slot 16 (11751), each `return &X::GetInst();`.
# The four majority states' slot 15 and CPedeMajoritario's test comum::CCargos::GetInst().GetCurrent().IsConsulta(),
# the byte +136 of the current cargo (ccargo.h), compared with 1, and return one literal or the other: the if and its
# two returns are a choice. Files: cpedeproporcional.cpp, cpedenulo.cpp, ccompletaproporcional.cpp and
# cpedemajoritario.cpp are named by records; cpedenominal.cpp and cconfirmavotonominal.cpp (votaproporcional/) and
# cconfirmamajoritario.cpp and cmajoritario*.cpp (votamajoritario/) are chosen, the class-name convention in the family's
# directory, as for the leaf states above (and for CConfirmaMajoritario: its vtable lies between CProporcionalNulo's
# and the majority states', before cpedemajoritario.cpp's records). Lines: in use band 1 the higher index is linked
# first, so GetMensagem comes after ProcessInputAudio in cpedeproporcional.cpp (11712, 11711, 11710; record :84) and
# cpedemajoritario.cpp (11684, 11683, 11682; record :64), before GetProximoEstado in cpedenulo.cpp (11745, 11744; record
# :44), and each constructor above the slot it is linked before (11700 above 11699, 11752 above 11751, 5932 above
# 5931); the exact lines, the singletons' code at the head of their files and the destructors' places are chosen. The
# twins 883 and 884 are now CPedeProporcional's D0 and D2, the first of the fifteen bodies in link order.
#
# The ten confirmation states' singletons: GetInst, a private constructor and the two statics of
# CProporcionalBranco, CProporcionalNulo, CCandidatoInapto, CCandidatoInexistente, CConfirmaVotoLegenda,
# CConfirmaVotoNominal and the four CMajoritario* states, each in its class's .cpp, final, in unit 104's form. The target
# holds each GetInst inlined in slot 16 of the CConfereVotoEmCargo instance over its class, and binaryen shares those
# slots as fns 1961 (six) and 2901 (four); the thunks pass the statics' addresses, the vptr and the constructor's
# arguments, which the constructors here write (fns 11670 to 11673, 11707, 11715 to 11717, 11738, 11739). The GetInst
# match nothing of their own: slot 16 is their one caller, and binaryen inlines them there as in the target. Their
# std::unique_ptr's exit-time destructors give fn 906 the copies it forms from: 906 matches, and with it
# CPedeProporcional's and CPedeMajoritario's (11714, 11686), whose second reader of s_inst lets 3849 and 5921 hold. The
# ten states' own, the mutex's and the pointer's (11688 and 11689 for CMajoritarioValido, 11691, 11692, 11694, 11695,
# 11697, 11698, 11702, 11703, 11705, 11706, 11729, 11730, 11732, 11734, 11736, 11737, 11749, 11750), match since the
# slot-16 thunks match: those read the statics too, so the names are no longer voted by the destructors alone.
# Placement: each state's statics come before its slot 15 (11750, 11749 and 11748 for CCandidatoInapto, in the band
# order), so they are defined above it; the constructor, destructor and GetInst above them are a choice.
#
# The class template vota::CConfereVotoEmCargo<ESTADO, TELA> (cconferevotoemcargo.h; its RTTI names ten instances, the
# header's comment gives what each part rests on): final, a singleton whose GetInst the target inlines into the four
# functions that build the instances (fns 11683, 11711, 11724, 11744), slot 16 returning &ESTADO::GetInst(), the
# destructor not out of line (implicit, a choice). The four are written, and their objects (cpedeproporcional.o,
# cpedenulo.o, cpedenominal.o and cpedemajoritario.o) instantiate the ten instances: from the first of them match the D0
# every instance shares (1278), slot 16 (the thunks above, and 1961 and 2901, which our link forms from the same six and
# four bodies) and 1286, the body binaryen shares for the ten std::unique_ptr statics' exit-time destructors. The
# statics' exit destructors of the instances 11711, 11724 and 11744 build (11708, 11709, 11718 to 11723, 11740 to 11743)
# match, voted by their builders, and so do those of the four 11683 builds (11674 to 11681, below).
#
# vota::IConfereVotoEmCargo (cconferevotoemcargo.h, new, and cconferevotoemcargo.cpp, named by its records): the head,
# the constructor (fn 1165), the destructor (fn 1717), FinishStateAudio (11792) and GetMensagem (11789); its other slots
# are below. The destructor
# is out of line, the key function, and cconferevotoemcargo.o emits the vtable: with the destructor in the class, as
# this unit first had it, the instances' D0 inlines it at the tree's -O3 (63 rows inserted against 1278, whole link),
# where the target's 1278 calls 1717; out of line, 1278 and 1717 give operand rows only, and 1717 matches from
# cconferevotoemcargo.o. The constructor reads the confirmation time through
# CConfiguracaoEleicao::GetParametrosUrna().GetTempoConfirmacaoVoto() and creates the tick only when it is positive, in a
# std::optional<uebyte> (+28, +29) a helper of the file's anonymous namespace returns; that helper, its name and the
# optional are chosen, and give the target's rows. cconferevotoemcargo.cpp includes cconfiguracaoeleicao.h, whose
# ecourna headers include Boost: an include path, not a flag of the code (the rule below). Lines: in use band 1 the
# slots are linked 11793, 11792, 11791, 11790, 11789, so FinishStateAudio sits between StartStateAudio (record :41 of
# its inlined helper) and ProcessInputAudio (record :80), and GetMensagem after ProcessTickAudio, past
# ExecutarAposAudioAtual's record :95; lines 60 and 120 are a choice, and so are the constructor's and the destructor's
# above line 41 (FinishStateAudio is at line 65 now, between StartStateAudio and ProcessInputAudio, a choice).
#
# GetTelaCargoAtual and StartStateAudio of vota::CPedeMajoritario, CPedeProporcional, CConfirmaVotoEmCargo and
# CCompletaProporcional (target fns 5920, 5923, 5928, 5931 and 11684, 11712, 11755, 11757), each throw on its record's
# line (cpedemajoritario.cpp:44, cpedeproporcional.cpp:42, cconfirmavotoemcargo.cpp:71, ccompletaproporcional.cpp:83).
# GetTelaCargoAtual throws when comum::CCargos is past its last post, else asks vota::CTelasVota::GetTelaCargo (fn
# 4135, unit 110) for the current post's form: the screen 0 for the two Pede states, the byte at +28 for the others,
# whose parameter is the caller's signature, "<caller> - o cargo atual nao esta posicionado" being the message. The
# target holds GetCurrent's call before CTelasVota::GetInst's and the post's id read after it (pnpm wasm fn 6050, at
# +0x3c, +0x43 and +0x48), the order a reference local gives; the call in the argument place would come after GetInst
# in C++17's order (a reading, not compiled). binaryen shares the bodies as the target does: the two Pede members form
# fn 6050 and the three others, with unit 150's CConfirmaVotoSemCandidato's, fn 3921 (each thunk passes its record and
# its code). StartStateAudio shows the form (slot 2, Slot2 in api/gui/cinteractiveform.h) and sets the next state to
# this one; the three with a parameter pass __PRETTY_FUNCTION__, whose text the target holds and no record does. The
# target's second caller of each GetTelaCargoAtual is the class's ProcessInputAudio, written since (below): with
# StartStateAudio its only caller binaryen inlined GetTelaCargoAtual into it and merged the two Pede StartStateAudio into
# one shared body, which the roots' stand-ins for the four ProcessInputAudio prevented until they were written. Measured before
# step 8 (pnpm wasm score, whole link): every one of these rows and 6050 and 3921 operand-only (3 of 6 to 11 of 107
# rows), matched at step 9. EUeVotaError's 9306, 9380, 9384 and 9386 are their codes (euevotaerror.h). Chosen: the
# parameter's name, GetTelaCargoAtual's being private, the reference locals' form, the cast of +28's uebyte to
# ETelaVotacao, and the lines: StartStateAudio after GetTelaCargoAtual, except in ccompletaproporcional.cpp, where it is
# above EmiteEcoComInputField's record (:60), as fn 5931 is linked before fn 5930 in use band 2 and so is first
# mentioned above :60 (a reading of the band). Other forms are not measured.
#
# Destructor forms, read from the bytes and measured. Fn 884 is one call of fn 1035, so each of the fifteen states over
# fn 1035 defines its destructor out of line: an implicit one leaves the base's D2 itself in the slot, as
# CConfirmaVotoEmCargo's and CConfirmaProporcional's slot 0 do, so those two are implicit. Fn 1035 is not inline with the
# hint, which would have put its body in fn 884 (compiled). Out of line or in the class without `inline` both leave the
# one call, the second through a weak copy in each user's object: out of line is chosen, since the vtable's place says
# that a member of the class is. The object's D0 calls its D1, and binaryen inlines that one-call body into the D0, which
# gives fn 883. Fn 3609 has that shape, a call, a drop and a free, while slot 0 holds fn 1378: clang inlines
# comum::IPedeTituloMesario's destructor into each derived class's out-of-line D2, and binaryen's duplicate-function
# elimination merges those bodies with the base's own. So that destructor is inline. Unit 71 had chosen it out of line,
# as the key function. Over that form an implicit derived destructor gives a 10-B D0, where 3609 differs at byte 6 in
# the whole link, and an out-of-line one in another object gives a D2 of one call, which is not slot 0's body (compiled). Fn 785 stores no
# vptr and CErroTesteTecladoFim is final: without final the D2 gains the store (compiled).
#
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3).
# CConfereVotoEmCargo<ESTADO, TELA>'s destructor: implicit, `= default` in the class, or `{}` in the class (object cmp-identical). Slot 15:
# `return std::string("...");`, a local std::string returned, and the body in the class. The leaf states: `{}` for
# `= default`, final, and slot 15 declared before the destructor. Fn 1035: `= nullptr` for reset(), the helper declared
# inline, its statements written in the destructor, and another pointee type for the +16 member. CErroTesteTecladoFim:
# `{}`, StartState in the class, and final on the destructor instead of the class. StartState with the call before the
# store differs. The CPedeTituloMesario* states: `{}` and final; comum::IPedeTituloMesario's destructor implicit, `=
# default` in the class with or without inline, and `{}` in the class. CPosixRWMutex: the throw tests on the call with
# strerror(errno), a const int per call, and any assignment of the literals to the throws give the constructor's frame
# of 592 B with the attributes at +152 and the slots' frame of 480 B, the only code the link leaves; their objects differ
# in the throw paths, which the link removes.
#
# Files. No record names the five leaf states, and their clusters' comments, fimvotacao/, are class-convention guesses
# (labels of stretches 541, 542, 548, 549, 552) that the data contradict: fimvotacao/'s records lie at
# @1540116-1542976 and these vtables at @1548432-1549728, between records of votaproporcional/ccompletaproporcional.cpp,
# cpedenulo.cpp and cpedeproporcional.cpp, and votamajoritario/cpedemajoritario.cpp's @1550352. votaproporcional/ is
# chosen, as the family's directory (how-to step 3, rule 3), and so it is for CConfirmaProporcional. The data do not
# settle it: cconfirmavotoemcargo.cpp of eleitor/ lies among those records. The file names are the class-name
# convention. Headers beside their sources are chosen. cerrotestetecladofim.cpp is the same rule in testeteclado/, where
# the records of ctesteteclado.cpp and cprezeresima.cpp lie. The destructors' lines in
# cvotacaostateaudio.cpp and the states' files are a choice, since no record gives one; the constructors' records (:44
# and :45 of the three cpedetitulomesario*.cpp) hold their lines (below). CPosixRWMutex's six throws sit on their
# records' lines.
# Which throw holds which literal is chosen from the messages: the code that loaded them is gone, and they stay in the
# target's data. The six enumerators' values are chosen too (eueipcerror.h).
#
# Written since:
# - comum::CPedeTituloMesarioInicial, CPedeTituloMesarioVotacao and CPedeTituloMesarioFinal: GetInst, the constructor
#   and the operator's form of each, which unit 104's CPedeTituloMesario::StartState (fn 10388) holds inlined, one case
#   of its switch each. Evidence, from 10388 (pnpm wasm fn): the test of s_inst (@1909540, @1909596, @1909568), new of
#   28 bytes, a 96-byte frame of the constructor's own after it (binaryen inlined it), the old object deleted by a
#   direct call of the D2 1378 and free (final, as unit 104's singletons), the unlock of s_mutex (@1909516, @1909572,
#   @1909544) through fn 150. In that frame: the form's builder (fn 203 at +84), "Informe o título do mesário: " at {1,
#   1}, AddClock (fn 728) at {33, 1}, "Quantidade de mesários registrados:" at {1, 3}, then a 24-byte api::CDataTextFmt
#   over the file's anonymous CComparecimentoMesariosDS (RTTI: three typeinfo names of that text, one per file; vptrs
#   1594036, 1594340, 1594188) with the format "{:02}" stored in place, a CTextFieldMT over it at {39, 3} (fn 1262)
#   pushed with vector::push_back in place, vota::AdicionaCampoNumerico (fn 1151) with 12, 1 and {1, 2}, "CORRIGE:
#   Encerrar  CONFIRMA: Prosseguir" at {1, 4} and GetInteractiveForm("", true) (fn 301); then fn 1255 (the voter's
#   screen), comum::IPedeTituloMesario's constructor (fn 3608) with both, the vptr store, and the controller's slot 20,
#   21 or 22 (LogaRegistrandoMesariosAntesVotacao, DuranteVotacao, AposVotacao, the header's names) through instance()
#   at the record's line, column 5. The builder's code is in the constructor's frame, so clang inlined it:
#   TelaPedeTituloMesario is in each file's anonymous namespace (a name of that file each). The data source's slot 2,
#   GetText, holds its operator() inlined: CRegistradorMesario::GetInst (fn 815) and QuantidadeMesariosInicio (fn 3606,
#   Inicial and Votacao: one body, fn 5387) or QuantidadeMesariosFim (fn 2727, Final: fn 10368), formatted as an
#   unsigned argument (type code 6) with std::vformat. The adder over CDataTextFmt is a member template of
#   api::CMTFormBuilderBase (cmtformbuilder.h says what is chosen). The voter's screen is
#   comum::TelaEleitorRegistroMesarios, the second copy of fn 1255, with a parameter its body does not read:
#   ipedetitulomesario.h has the three forms measured against it. Measured in the whole link (pnpm wasm score of 10388):
#   186 over 2061 rows, all operand-only (the six statics' addresses), then a match at step 9; the statics are named by
#   10388's votes, and their exit destructors match with them: 10379, 10378 (Inicial), 10372, 10371 (Final), 10366,
#   10364 (Votacao), the pointers' through fn 3881, binaryen's shared body of the three, which our link forms too. The
#   data sources' slot 2 (5387, 10368) and D2/D0 (10377, 10374; 10370, 10369; 10363, 10362: thunks into fns 1566 and
#   1565) match; their control blocks' __get_deleter (10373, 10367, 10361) do not: the census pairs them with
#   comum::CGravador*'s blocks (scan detail), and each compares the deleter's typeinfo name, whose text the three files
#   share, which reads as why no name singles ours out (a reading, not traced). Band (ld_index in names.tsv): in each
#   object the statics' destructors, then the D2, the D0 and slot 2, as the target's indices run. Chosen: the builder's
#   and the data source's names and their being in the anonymous namespace, the data source being a class with a const
#   operator() (CDataTextFmt's T is the class itself, by RTTI, and nothing of it is stored), std::size_t for the count,
#   the destructor and slot 9 after GetInst, and every line but the records' (Final's record is one line lower: its gap
#   above the constructor is a line longer). Not chosen: the statics are defined below GetInst, which names s_mutex
#   first, so each object puts the mutex 24 bytes below the pointer, the target's .bss order (@1909516 and @1909540 for
#   Inicial); defined above the constructor, the pointer came first. Measured on the whole link: no scan row moves
#   either way, the statics' exit destructors keep their place in each object's function order, and step 9 renamed
#   their `.2` lines to `.3`. The constructor keeps its record's line behind a gap. The three content-found D2/D0 match
#   lines were first written crosswise (bodies alike but for the vtable constant) and are corrected by the vtables that
#   hold their slots (@1594028, @1594180, @1594332).
# - vota::CEstadoComDesligamentoAutomatico::ProcessTick (fn 12061, slot 8), in cestadocomdesligamentoautomatico.cpp, its
#   lambda's record at :44:45 the CPolySingleton<api::IPower>::instance() call of api::IPower::UsandoBateriaInterna
#   (api/hwil/ipower.h). For another tick's id it calls slot 9, ProcessTickNaoDesligamento. With a time limit set and
#   past (api::CDateTime's operator==, inline, and fn 759), it adds CParametrosUrna's tempoAvisoDesligamentoAutomatico
#   (+96, through fn 5474, unit 125's), copies the limit into vota::g_dataHoraDesligamento
#   (app/vota/eleitor/comum/cinformacaoeleitor.h), sets vota::CExibeAlertaDesligamento's +36 to this state and goes to
#   it (GetInst, fn 5979, unit 61); else, on the internal battery, it sets an unset limit to now plus
#   tempoDesligamentoAutomatico (+92) less the warning time; off it, it unsets the limit (CDateTime(-1)). Measured with
#   pnpm wasm score, whole link: the limit's test as a statement of its own (a bool local) gives operand rows only;
#   `m_limite != api::CDateTime(-1) && api::CDateTime::Now() > m_limite` as one condition gives 41 over 206 rows (12
#   inserted), a 32-byte frame for the target's 16, as the two temporaries share no slot. The target sign-extends both
#   times to the 64-bit count (i64.load32_s, i64.extend_i32_s), as cparametrosurna.hpp's getters of the two, which
#   return int, give; the int locals are a choice. The target calls comum::CConfiguracaoEleicao::GetInst (fn 187)
#   once in the first branch and twice in the second, as written. Chosen too: the locals' and the lambda's names, the
#   lambda's spelling (the record fixes the 44 characters before the call) and ProcessTick's first line.
# - vota::CPedeNulo::GetProximoEstado and vota::CPedeNominal::GetProximoEstado (fns 11744 and 11724, slot 16), in
#   cpedenulo.cpp (EUeVotaError 9385, "O cargo atual nao esta posicionado", at record :44:15, past the last post) and
#   cpedenominal.cpp (no record: its line, after GetMensagem, is a choice). Both store the number typed through
#   vota::SetNumeroDigitado (cinformacaoeleitor.h), compare its size with the post's +12 and look the candidate up
#   with comum::CCandidaturas::Busca (fn 1273); the target reads the post's id and calls ToDWord (fn 1523) before
#   CCandidaturas::GetInst (fn 521), so both are read into locals first. The states they return are the
#   CConfereVotoEmCargo instances of the RTTI over the screens 14 and 7 (11744) and 10, 12, 14 and 2 (11724), with a
#   candidate's +52 (its holder's ESituacao) not 0 for CCandidatoInapto. Measured for 11744: the null state returned in
#   the size test's block and again after it gives operand rows only; one return after the block, with `&&`, nested
#   ifs or a bool local, 43 over 181 rows (1 inserted, 2 deleted); early returns, the size mismatch first, 77 over 200.
#   The roots' ConfereNulo and ConfereNominal went with them, and EstadoAudio and PedeMajoritario, which stood for fn
#   4459, now written (src/units/197-uenux2-celeitorvotando.mk).
#
# FormatPartyName (target fn 6954, record :297, code 9321) is written: it converts the number with atoi, finds it in
# comum::CPartidos' map (CDataMap::Find, inlined: the cursor at +12 set on a hit) and returns a copy of the party's
# m_nome (+16 of md::CPartido); on a miss it calls vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550, unit 119's
# source) on GetInst's result and throws code 9321, "Nao foi encontrado o partido". Its record shows it neither static
# nor const; its wasm type has no `this`, which binaryen's dead-argument elimination drops when the body does not read
# it (a reading). The number is read into a local first, since the target calls atoi before CPartidos::GetInst; the
# form with the conversion in Find's argument is not compiled. Chosen: the parameter's and locals' names, the test of the
# null result before the return, its access (private) and the enumerator's name. Its one target caller is fn 6999
# (slot 14), which calls it twice, from SubstituiMarcador (below). The four include lines it needed, with a blank line,
# took five of the blank lines above line 69 (ProcessInput's record, not written). Scored 13 over 112 rows, all
# operand-only, before step 8; matched at step 9.
#
# Slot 14, FormataMensagem (fn 6999, written, `unresolved`: what it waits for is below), in cvotacaostateaudio.cpp after
# FormatPartyName, a choice (in use band 1 it is linked after ProcessTick, fn 7010, whose record is :120). It returns ""
# for an empty message, else the message with each {...} tag replaced: a std::regex("\\{.+?\\}") built in its frame
# (the constructor inlined, its __parse called, fn 2062), a std::sregex_token_iterator over it with the submatches
# {-1, 0}, and std::for_each over named iterators whose lambda appends SubstituiMarcador's text for each part, the shape
# of unit 84's CMenuItem::GetTextoFormatado (5492). The target holds these functions of the file each behind a stack
# frame of its own, binaryen's inlining (docs/reference/facts/reading.md R10), so they are out of line here, external,
# and binaryen inlines them into their one caller: SubstituiMarcador (a 48-byte frame), GetNomeCargoAtual (432),
# GetCandidatoComSuplentes (80), GetQuantidadeDigitos (400) and FormataProgresso (400). GetProgresso, over
# FormataProgresso, has no frame, so no evidence makes it a function: it is one as a measured form ({progresso}, below).
# Chosen: the helpers' names (SoletraNumero and TextoConsulta, which picks the consulta's string, in an anonymous
# namespace; GetNomeCargoAtual, GetCandidatoComSuplentes, GetQuantidadeDigitos, FormataProgresso and GetProgresso, in
# vota), their being free functions, their locals' names, and their place, lines 231 to 288 of cvotacaostateaudio.cpp.
# Each tag's text, read from 6999's code:
# - {cargo-atual}: the current post's GetNomeNeutro (fn 1547), or for a consulta the detail's string at +36, else the
#   one at +12 (GetDetalheConsulta, fn 1923), then, when the post has more than one choice, " {}ª {}" of
#   vota::g_escolhaAtual and "escolha" or "vaga";
# - {voto} and {legenda}: the number typed, whole or its first two characters, with ", " before every digit but the
#   first: std::regex_replace with a static std::regex("\\B\\d") and ", $&" (SoletraNumero; the static's guard test
#   is in the target twice, so clang inlined it at both);
# - {nome-partido}: FormatPartyName of the number's first two characters;
# - {escolha-referendo}: the current answer's string at +16, else the one at +4 (comum::CRespostas, fns 2812, 3125);
# - {o/a}: 'a' when the current candidacy's holder is a woman, else 'o' (vota::ArtigoCandidato, below);
# - {candidato}: the holder's optional name at +24 when it is engaged, else its name at +12;
# - {candidato-com-suplentes}: that, then for each substitute ", " + comum::CCargoDSNomeSexoCandidato(n, true)() + " "
#   + the substitute's name (fn 2268);
# - {quantidade-digitos}: "{} {}" of the post's digit count and "dígitos" or "dígito";
# - {progresso}: "{} de {}" of the votes cast plus one and the sum of the posts' choice counts (fn 861).
# Measured, on the object (wasm-objdump -d at the file's flags) and in the whole link (pnpm wasm score):
# - {o/a} written in this file, as a bool or a char local or a conditional, gives a select the target does not have; a
#   function of another TU gives the target's branches. ArtigoCandidato, in comum/cinformacaoeleitor.cpp beside the
#   voter's statics (src/units/197-uenux2-celeitorvotando.mk), its name and its being a free function are chosen.
# - The first argument of " {}ª {}" as `g_escolhaAtual` is loaded after the store of the arguments' types, where the
#   target loads it before; `static_cast<unsigned>(g_escolhaAtual)`, written, and the value or the second argument in a
#   local first give the same object code (the function's disassembly, masked).
# - {progresso} with the count computed in GetProgresso puts its arithmetic after the loop (clang sinks it), and with
#   the format in the same function as the loop, the frame comes before the loop; the count as GetProgresso's argument
#   gives the target's order.
# - GetDetalheConsulta (fn 1923) has six direct callers in the target and one here: with 6999 alone binaryen inlines
#   it. Unit 232's roots stand for the other five (two calls), and our link then forms the target's merge 6029 of it and
#   comum::md::CLocal::GetContingencia (3724): 1923, 3724 and 6029 match. The static std::regex's exit destructor
#   (14464) merges with 5492's static's (10901) into 6096, which matches, and 10901 with it; 14464 waits for the
#   static's name.
# What 6999 waits for (pnpm wasm score at this commit's link: 523 over 2253 rows, 440 of the 447 replaced operand-only,
# 35 inserted, 41 deleted): std::regex_replace (fn 6958) keeps the regex and the format
# as parameters in the target, (i32 i32 i32 i32 i32)->(), and loses them to dead-argument elimination here, (i32 i32
# i32)->(), as both its call sites pass the same constants; that is not explained: SoletraNumero declared inline (its
# static then reached through the GOT) gives the same fold, and a live caller passing another regex keeps the regex here and
# moves no other row of 6999. So 6958 is `no-candidate`. In {progresso} the target leaves FormataProgresso's code with
# one branch out of the tag's chain, and ours keeps one more block (FormataProgresso defined after GetProgresso gives
# the same). The rest are local numbers. 6999 also reads its static std::regex and guard (1833216, 1833256), which no
# other target function reads but 14464, which reads the object. 6999 scores the same with cvotacaostateaudio.cpp
# compiled with strict aliasing and without it, as the file builds now. It stays written, as slot 14
# (a trap would hide it), and the matches above rest on its code.
#
# std::regex's copies, src/app/roots_cbasetype.cpp (its comment says what it holds) and src/app/roots_regex.cpp (the
# std::string constructor's chain, gone since 5821, unit 122, brings ecourna's icompressor.cpp.o, which gives it),
# measured by whole links of this unit with roots_regex.o compiled at each set by hand (census, splat-symbols,
# splat-match; rows against a081739b's splat/scan.tsv, 5 of whose new matches are the ones above):
# - roots_regex.cpp as it was (the constructor from a C string at ECOURNA_CXXFLAGS): 5 rows turn `match`, none stops;
# - the same at UENUX2_CXXFLAGS (no -fexceptions, no strict aliasing): 31 turn `match`, 5 stop (3329, 3524, 5186, 5188,
#   6770; 3524, 5186 and 5188 are the std::string constructor's copies of three parser members whose const char*
#   copies are 4242, 4203 and 6862);
# - at UENUX2_CXXFLAGS with strict aliasing: 19 turn `match`, 8 stop;
# - the C-string constructor in roots_cbasetype.o and a std::string one in roots_regex.o: 60, none stops; with the token
#   iterator and std::regex_replace in roots_cbasetype.cpp too, as written: 65, none stops (2054, 4276, 4279, 4307 and
#   5492 besides).
# So the target's copies over const char* and of the token iterator are uenux2's without strict aliasing and without
# landing pads, though cinputmenufield.cpp, one of their users here, builds with strict aliasing, and the other,
# cvotacaostateaudio.cpp, which builds without it (below), links after it; that flag is not changed here, and listing
# cvotacaostateaudio.cpp in UENUX2_NOTBAA_FILES moved none of these rows. Since fragment 299's cqrcodeds.cpp, built
# without strict aliasing, links ahead of cinputmenufield.cpp and gives the const char* parser's copies, the tree root
# holds the token iterator's and std::regex_replace's alone (its comment).
#
# CVotacaoStateAudio's slots 7, 8 and 13 and its static helpers, written since (target fns 7029, 7010, 3139, 1455, 3143
# and 1204), with the copies of api::CPolySingleton<T>::instance they call (1091, 2079) and has<ITextToSpeech> (3281).
# Each instance() call sits at its record's line and column (cvotacaostateaudio.cpp :69, :120, :136, :172, :173, :178,
# :179, :226 and :388), and 3139's throw (code 9318) at :188; where a local takes the call's result, the length of its
# name puts the call at its column, and the names are chosen.
# - ProcessInput (7029) and ProcessTick (7010): when audio is on, each ends the wait for the audio
#   (CancelaEsperaFimAudio) and stops both ticks (PararTicks, inline in the .cpp: the test and the two StopTick calls
#   FinishState, 7029 and 7010 hold with no frame of their own); ProcessInput then calls ISound's slot 5 and PararTicks
#   again, then slot 9, and restarts the echo tick (+12) when slot 4 returns this state; ProcessTick, on one of its two
#   ticks and unless ISound's slot 7 returns 1, speaks slot 15's message through slot 14 (FalaMensagem, which clang
#   inlines here) and starts the wait (IniciarEsperaFimAudio, record :388, held by 7010 in a stack frame of its own:
#   out of line, inlined by binaryen into its one caller here too), else it calls slot 12. IniciarEsperaFimAudio stores
#   ISound::WaitAsync's result over `[] { return false; }` and a lambda that restarts the echo tick when the audio
#   ended: the lambdas' __func typeinfos name them $_0 and $_1 of that function, and their slots 13703, 13712, 13721,
#   13750, 13761, 13769 and 13778 match from this object.
# - PlayMessage (1204) and PlayInterruptibleMessage (3143), static by their records: ITextToSpeech's slot 0 of the text,
#   played through ISound's slot 4, queued (mode 1) and waited for with ISound::Wait() (its lambda's __func @1530436),
#   or interrupting (mode 0). PlayKey (1455): a zero key beeps (IBeep's slot 6) and is logged
#   (CLogVota::LogaTeclaIndevida, clogvota.cpp); with audio on, a digit, 'B' and 'D' speak api::KeyName's text
#   interrupting, 'C' queued, and a zero key plays ":/resource/sounds/tecE.wav" through PlayFile (static by its record
#   :226; clang inlines it), which, when CEstadoAudio is active, copies the path and passes it to ISound's slot 1.
#   EmiteEcoComInputField (3139): the form's one input field (else the throw), its text before and after Read, the
#   field's last key echoed through PlayKey unless Read returns 5 or 13 with the text unchanged (0 then), and the pair
#   of Read's result and the text after it. The access of PlayKey, PlayFile, IniciarEsperaFimAudio, PararTicks and
#   FalaMensagem is chosen (the header says so).
# - The instances: 1091 (instance<ISound>, with landing pads) is the executable TU's copy (its record @1526584 in that
#   TU's data) and matches from vota_web_wasm.cpp.o, now that its target callers here keep it out of line; so does unit
#   170's votaSetAudioEnabled (10240), whose body held it inlined in our link. 2079 (instance<ITextToSpeech>) is
#   cinstrucaovotacaoacessibilidade.cpp's copy (its record @1533836 follows that file's) and matches from unit 150's
#   object. 3281 matches from src/app/roots_texttospeech.cpp, whose comment says why, with unit 150's roots standing for
#   its unwritten callers.
# Measured, pnpm wasm score in the whole link before step 8 (each matched at step 9):
# - the tick read into a local before CThreadEleitor::GetInst() in ProcessInput and in the lambda, as StartState has it:
#   with m_tickEco as StartTick's argument 7029 scored 16 over 125 rows (1 inserted, 3 deleted), the call first;
# - ProcessTick as an if/else on the tick, and IniciarEsperaFimAudio's instance() bound to a reference before WaitAsync:
#   an early return for the other ticks, written first, put slot 12's call at the head, and instance() in WaitAsync's
#   expression kept its std::source_location live into that call in a slot of its own (+52, where the target's result
#   reuses +56): 7010 scored 66 over 327 rows (13 inserted, 18 deleted); as written, operand rows only;
# - LogaTeclaIndevida a member PlayKey calls on GetInst's result: a free function that built its message and then
#   called GetInst gave 1455 31 over 211 rows (1 inserted, 1 deleted), GetInst inside the member's frame;
# - 3281: the copy simulador.cpp.o gives at the tree's flags is a thunk into a body of three constants, 4 over 7 rows (2
#   inserted); from roots_texttospeech.o, operand rows only.
# Readings, not measured as forms: PlayFile's copy of the path before instance() is called (a by-value argument would be
# built after instance(): a test TU at -O3 calls the object first, wasm-objdump -d), and FalaMensagem's local (the
# target frees slot 15's string before PlayInterruptibleMessage, where the temporaries of one full expression live until
# its end). That PararTicks is a function is a choice: the lines of ProcessTick's record (:120) and PlayKey's (:136)
# leave its statements no room in ProcessTick; FinishState uses it too, and 7022 still matches. That FalaMensagem is
# one is evidence (11786, below). Other forms of PlayKey's switch and of the echo's test are not measured.
# $_1's two __clone slots (13732 and 13740) store the vptr before they copy the capture, as only code without strict
# aliasing does (fn 786, the merge 13740 calls, has that order; with strict aliasing ours joins the merge with the other
# order, the target's 1083, and 13732 scores 6 over 12 rows, 3 inserted and 3 deleted). They match since
# cvotacaostateaudio.cpp builds without strict aliasing (src/Makefile's UENUX2_NOTBAA_FILES, the user's decision;
# docs/reference/facts/app-flags.md F6 has the measurement on the whole link). In a variant link with only that object
# so (docs/reference/facts/workflow.md W13), every other function of the object with a target row scored as it does with
# strict aliasing.
#
# The input slots of the vote states and IConfereVotoEmCargo's audio slots, written since (target fns 11791, 11793,
# 11790, 3851, 11754, 11711, 11683, 11756, 5930 and 5925, with 5922), so every member the unit's vtables need is written
# and the -pending.cpp is gone:
# - IConfereVotoEmCargo (cconferevotoemcargo.cpp): ProcessInputAudio (11791, record :80) echoes the key (PlayKey(0)) and
#   clears the keyboard (api::IInputKbd's slot 4, the instance at its record's column); StartStateAudio (11793) sets
#   this state as the next one and, with the tick, starts it, shows the form CTelasVota::GetTelaCargo (fn 4135) gives for
#   the post GetCargoID returns (an anonymous-namespace function by its record :41, code 9305, which StartStateAudio
#   holds inlined) and the screen at +30, and speaks the message once the audio ends, else goes to slot 16's state once
#   it ends; ProcessTickAudio (11790) stops the tick when it fires and goes to slot 16's state once the audio ends;
#   ExecutarAposAudioAtual (3851, record :95, its signature the record's) cancels the wait at +32 and runs its function at
#   once when ISound::Wait over `[] { return false; }` returns true, else keeps at +32 the wait ISound::WaitAsync returns
#   over a lambda that cancels it once the state changes and one that resets +32 and runs the function when the audio
#   ended and the state stayed. The six lambdas' __func members are libc++'s (fns 11758 to 11788 but 11769, with 5934,
#   the operator() binaryen keeps once for the two that set the next state, and 340, the shared `return 0`); the typeinfos
#   name them $_0 and $_1 of StartStateAudio(), $_0 of ProcessTickAudio(unsigned char) and $_0 to $_2 of
#   ExecutarAposAudioAtual, so they are written in that order, each in place in its call. Measured, pnpm wasm score in the
#   whole link before step 8: 3851 8 over 367 rows, 11790 4 over 63, 11791 4 over 30, 11793 17 over 150, all
#   operand-only; matched at step 9, with 23 of the 31 __func members the lambdas have of their own (11786 below); the
#   other eight, the __clone slots below, match since cconferevotoemcargo.cpp builds without strict aliasing.
#   Chosen: the locals' names (their lengths put the instance() calls at their records' columns, :80:20 and :95:18),
#   ExecutarAposAudioAtual's access and parameter name, the early return after the function runs at once, and
#   `reset()` for clearing +32 in the lambda. The two __func destructors of $_2 (11765, 11764) are thunks into
#   binaryen's merges 6053 and 6052 with api::CDataText<COpcaoDS>'s (10688, 10686, unit 121), which our link now
#   forms: all six match.
# - The eight __clone slots of the four lambdas that capture `this` alone (11770, 11771, 11778, 11779, 11782, 11783,
#   11787, 11788) store the vptr before they copy the capture, as only code without strict aliasing does (as
#   CVotacaoStateAudio's $_1, 13732 and 13740, above): with strict aliasing 11782 and 11787 scored 6 over 12 rows (3
#   inserted, 3 deleted) and the four __clone() slots 2 over 5, operand-only. They match since cconferevotoemcargo.cpp
#   builds without strict aliasing (src/Makefile's UENUX2_NOTBAA_FILES, the user's decision;
#   docs/reference/facts/app-flags.md F6 has the measurement on the whole link). Measured first in a variant link with
#   cconferevotoemcargo.cpp.o compiled with -fno-strict-aliasing (one object swapped in a copy of link.cmd,
#   docs/reference/facts/workflow.md W13, scanned with the committed symbol file and match list): the eight turned
#   `match` and no other row entered or left `match`; its control, the object compiled from the same line, gave the
#   plain link's sha256.
# - The operator() of StartStateAudio's $_0 (11786) calls CVotacaoStateAudio::FalaMensagem, out of line (protected,
#   not `inline`, in cvotacaostateaudio.cpp). That the target keeps FalaMensagem as a function of its own is
#   evidence: its 11786 reads the capture first (+0x3 local.get 0, +0x5 i32.load offset=4, +0x8 local.set 1) and
#   opens its one stack frame after that (+0xa global.get 0, i32.const 32, i32.sub), a frameless caller's statements
#   ahead of the only prologue, the sign of a callee binaryen inlined (how-to step 3); the frame holds that callee's
#   two strings, slot 15's result at +8 and slot 14's at +20. With the statements written in the lambda (the audio
#   flag made protected for it), ours opened the frame first: `differs` at +0x3, 24 over 68 rows (2 inserted, 3
#   deleted). Out of line, clang still inlines FalaMensagem into ProcessTick, and 7010 keeps its match. Measured
#   first in a variant link with both objects swapped (docs/reference/facts/workflow.md W13): 11786 the one row to
#   enter or leave `match`; then in this tree's whole link, matched at step 9.
# - CConfirmaVotoEmCargo::ProcessInputAudio (11754, cconfirmavotoemcargo.cpp, inherited by twelve derived classes'
#   slot 9) over CVotacaoStateAudio::EmiteEcoCorrigeConfirma, written in cvotacaostateaudio.cpp at its record :209 (code
#   9319) and held inlined by binaryen: Read, then the field count's test, then the field's last key echoed when it is
#   'C' or 'D'. On INPUT_CONFIRMA it reads the post's id, copies vota::g_numeroDigitado (the target copies it before
#   CEleitorVotando::GetInst) and registers the vote with +32 as its type. 34 over 273 rows, operand-only; matched.
#   Chosen: the conditional's form for the key, the locals and the switch.
# - CPedeProporcional::ProcessInputAudio (11711, record :84, code 9387) and LegendaValida (5922, a free function in
#   cpedeproporcional.cpp, declared in its header for its second target caller, fn 5500, the executable TU's state
#   reader; the roots take its address for that caller's invoke). The INPUT_CONFIRMA branch tests the party's lookup
#   (comum::CPartidos' Find, cursor set) and LegendaValida negated, CPedeNulo first: written as `Find(...) != nullptr &&
#   LegendaValida(...)` with CPedeNominal first, the two GetInst blocks came out the other way round (63 over 342 rows, 1
#   deleted); as written, 58 over 342, operand-only. LegendaValida looks the party up with CDataMap::Existe (a const
#   find, api/io/cdatamap.h), walks the candidacies through CCandidaturas::ExisteCandidatoPartido and else asks the
#   party's federation: with ExisteCandidatoPartido inline in ccandidaturas.h, clang's early return replaced the
#   target's block result tested again (34 over 128 rows, 10 deleted); out of line in ccandidaturas.cpp, which binaryen
#   inlines into its one caller, 4 over 128, operand-only. vota::CPedeNulo and CPedeNominal get their singletons
#   (GetInst, a private constructor passing 5 and 8 to CCompletaProporcional's, the statics), which 11711 holds
#   inlined; their statics' exit destructors (11746, 11747, 11726, 11727) and those of the CConfereVotoEmCargo instance
#   over CProporcionalBranco (11708, 11709) match with 11711. Chosen: LegendaValida's name, membership, parameters'
#   types beyond their widths and file; the singletons' form is unit 104's.
# - CPedeMajoritario::ProcessInputAudio (11683, record :64, code 9381) and ExisteCandidatoValidoResposta (record :125,
#   code 9382, held inlined by binaryen), matched. The repeated-vote test (ExisteVotoRepetido, a chosen member clang
#   leaves out of line and binaryen inlines, with comum::md::CCargo::PodeRepetir, +14) tests the choice being voted
#   (`g_escolhaAtual == 1`) in an `if` of its own, after the reference to g_votosEleitor.GetVotos() and before the vote
#   count, and its loop's guard on the choice is then the target's `i32.eqz`. Measured on the object at the file's
#   flags (em++ -S -emit-llvm -mllvm -print-after-all, ExisteVotoRepetido's dumps): with the test in the `||` of the
#   post's two tests, the form before, the first SimplifyCFG (before inlining) joins it and PodeRepetir's into one
#   `select` branch, and the InstCombine after LoopRotate leaves the rotated guard `icmp ugt i8 n, 1` (`i32.const 2;
#   i32.lt_u`: 77 over 532 rows in the whole link, 1 inserted); with GetVotos' call between the two `if`s (inline: a
#   call in that first pass, no code once inlined), the `== 1` test keeps a branch of its own, and that InstCombine
#   rewrites the guard `icmp ult i8 1, n` as `icmp eq i8 n, 0`. Whole link: 75 over 531 rows, all operand-only; matched
#   at step 9. Measured on the object and not the target's guard: the `== 1` test in its own `if` with no call before
#   it, and an external function in PodeRepetir's place, keep the `== 1` test and guard with `i32.const 2; i32.lt_u`;
#   the vote count computed before the `== 1` test, or above the post's two tests, leaves no `== 1` test (the two join
#   into `i32.const 2; i32.lt_u`). The forms measured at the earlier commit give `i32.const 2; i32.lt_u` or other code
#   too (the early tests nested in one if, `<= 1`, no `== 1` test; the counter as int, unsigned or size_t, or compared
#   with `!=` as int, size_t or uebyte, or with `<= g_escolhaAtual - 1`; a while loop; a descending index; the tests
#   split by a continue), and the count in the loop's at() came after the guard (116 over 541 rows, 10 inserted, 14
#   deleted). The reference's place between the two tests is chosen, the one form found that gives the guard; no record
#   fixes it, and the three lines the function gained took three of the blank lines above line 111.
#   The statics of the four CConfereVotoEmCargo instances it builds, each one's s_mutex and s_inst, are named by
#   11683's votes alone (`vote:2 by:11683` and `vote:6 by:11683` in splat/symbol_addrs.txt), and each of their eight
#   addresses has one other target reader, its exit destructor (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
#   build/out/splat/pieces/asm` lists 11683 and one of 11674 to 11681 for each of 1838344 to 1838480): the second match
#   docs/reference/splat.md section 3 asks of a .bss name. The eight match with 11683, 11675, 11677, 11679 and 11681 by
#   the scan's content pass: the census pairs those four with other objects' mutex destructors of the same shape, and
#   two other target rows, 8378 and 9267, with two of ours (`__cxx_global_array_dtor.30` and `.22`): those two rows read
#   `differs` now, where they read `unresolved` before the statics had names.
# - CCompletaProporcional (ccompletaproporcional.cpp): ProcessInputAudio (11756) and EmiteEcoComInputField (5930, record
#   :60, code 9383), final, as 11756 calls it directly; 29 over 342 and 17 over 245 rows, operand-only; matched. The
#   INPUT_CONFIRMA branch copies vota::g_numeroDigitado before it appends the field's text (the target copies it first).
#   Chosen: final (a qualified call is not measured), ProcessInputAudio's line above EmiteEcoComInputField's record.
# - Slot 17 of vota::CConfirmaVotoNominal and CMajoritarioValido (5925), the same body in both files, which binaryen keeps
#   once: on INPUT_CORRIGE it logs through a new CLogVota member (LogaEleitorCorrigiuConfirmacaoCandidato, clogvota.cpp)
#   and clears the keyboard through vota::impl::IPoliticaExecucaoEleitor's GetInst (unit 165), both held inlined. The
#   target calls GetInst before the logger's frame opens, a member called on its result: a free function that built the
#   message and then called GetInst gave 150 over 889 rows (5 inserted, 5 deleted); as written, 96 over 884,
#   operand-only; matched. Unit 165's stand-in for 5925 went, and 13574, the exit destructor of that GetInst's mutex,
#   matches since 5925, its other reader, does.
# Every throw sits on its record's line; the files' other lines are chosen. Unit 212's, 197's and 165's stand-ins for
# 11683, 11754 and 5925 went with them, and this unit's roots for 11711, 11683, 11756 and the four ProcessInputAudio.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CVOTACAOSTATEAUDIO_SRCS := src/app/vota/eleitor/cvotacaostateaudio.cpp \
    src/app/vota/eleitor/cconfirmavotoemcargo.cpp \
    src/app/vota/eleitor/cconferevotoemcargo.cpp \
    src/app/vota/eleitor/votaproporcional/cconfirmaproporcional.cpp \
    src/app/vota/eleitor/cestadocomdesligamentoautomatico.cpp \
    src/app/vota/eleitor/votaproporcional/cpedeproporcional.cpp \
    src/app/vota/eleitor/votaproporcional/ccompletaproporcional.cpp \
    src/app/vota/eleitor/votaproporcional/cpedenulo.cpp \
    src/app/vota/eleitor/votaproporcional/cpedenominal.cpp \
    src/app/vota/eleitor/votaproporcional/cconfirmavotonominal.cpp \
    src/app/vota/eleitor/votamajoritario/cpedemajoritario.cpp \
    src/app/vota/eleitor/votamajoritario/cconfirmamajoritario.cpp \
    src/app/vota/eleitor/votamajoritario/cmajoritariovalido.cpp \
    src/app/vota/eleitor/votamajoritario/cmajoritariorepetido.cpp \
    src/app/vota/eleitor/votamajoritario/cmajoritarionulo.cpp \
    src/app/vota/eleitor/votamajoritario/cmajoritariobranco.cpp \
    src/app/vota/eleitor/votaproporcional/ccandidatoinapto.cpp \
    src/app/vota/eleitor/votaproporcional/cconfirmavotolegenda.cpp \
    src/app/vota/eleitor/votaproporcional/ccandidatoinexistente.cpp \
    src/app/vota/eleitor/votaproporcional/cproporcionalbranco.cpp \
    src/app/vota/eleitor/votaproporcional/cproporcionalnulo.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesarioinicial.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesariofinal.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesariovotacao.cpp \
    src/api/ipc/posix/cposixrwmutex.cpp
UENUX2_SRCS += $(CVOTACAOSTATEAUDIO_SRCS)
# cconferevotoemcargo.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit
# 122's cgravadorutil.cpp does)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/cconferevotoemcargo.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# cestadocomdesligamentoautomatico.cpp includes cconfiguracaoeleicao.h too
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/cestadocomdesligamentoautomatico.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# cvotacaostateaudio.cpp includes cconfiguracaoeleicao.h too
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# what nothing reconstructed references yet: 97-uenux2-cvotacaostateaudio-roots.cpp takes the address of fn 5922; it
# declares through asm labels and instantiates nothing
$(ROOT)/$(APP)/97-uenux2-cvotacaostateaudio-roots.o: $(ROOT)/src/units/97-uenux2-cvotacaostateaudio-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/97-uenux2-cvotacaostateaudio.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/comum/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votaproporcional/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votamajoritario/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/dados/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/97-uenux2-cvotacaostateaudio-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/97-uenux2-cvotacaostateaudio-roots.o
