# uenux2 vota::CVotacaoStateAudio's slot-15 family, two state leftovers and api::CPosixRWMutex.
#
# Slot 15 (a chosen name, GetMensagem: fn 7010 calls it and fills the result's {cargo-atual}-style tags through slot 14)
# of vota::CCandidatoInapto, CConfirmaVotoLegenda, CCandidatoInexistente, CProporcionalBranco and CProporcionalNulo
# (target fns 11748, 11735, 11731, 11704, 11701), each `return "<literal>";`, with their destructors, fns 884 and 883;
# vota::CVotacaoStateAudio's destructor (1035) and the heads of its derived classes CConfirmaVotoEmCargo and
# CConfirmaProporcional, all abstract. comum::CPedeTituloMesarioInicial, Final and Votacao: their D0 (3609), slot 9 and
# the D2 they share with comum::IPedeTituloMesario (1378, unit 71's). vota::testeteclado::CErroTesteTecladoFim:
# StartState and destructors (3857, one body with CEnviarManutencao's and CTesteFalhou's, 785 and 1560, bodies of eight
# states), over the head of vota::CEstadoComDesligamentoAutomatico. api::CPosixRWMutex: constructor and destructors
# (10245, 5353, 10244) and slots 2 to 4, which binaryen merges into 2219, api::IRWSyncCtl and six enumerators of
# EUeIpcError. The class headers say what each layout and name rests on. The seventeen members not written are in
# 97-uenux2-cvotacaostateaudio-pending.cpp, with what each waits for.
#
# The constructors and two slots, over unit 02's tick names: CVotacaoStateAudio's constructor (1785), StartState (7028)
# and FinishState (7022); CConfirmaVotoEmCargo's constructor (5929) with its two data members; CConfirmaProporcional's
# (11752); CEstadoComDesligamentoAutomatico's (1285). Their callers in the target are not written, and the roots stand
# in for them (its header names each). Out of line, by the target: each constructor is a function of its own with two
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
# functions that build the instances (fns 11683, 11711, 11724, 11744, not reconstructed), slot 16 returning
# &ESTADO::GetInst(), the destructor not out of line (implicit, a choice). The roots stand in for those four builders and call the instances'
# GetInst as they do, so the roots object instantiates the template, as unit 79's roots instantiate theirs, and is
# compiled with UENUX2_CXXFLAGS. From it match the D0 every instance shares (1278), slot 16 (the thunks above, and 1961
# and 2901, which our link forms from the same six and four bodies) and 1286, the body binaryen shares for the ten
# std::unique_ptr statics' exit-time destructors. Those destructors (11674, 11676, 11678, 11680, 11708, 11718, 11720,
# 11722, 11740, 11742) read `unresolved`, the static's address having no target symbol, and the mutexes' (11743 for
# CCandidatoInapto's, 11675 and the other odd neighbours) `no-candidate`: the statics' readers in the target are the
# four builders, not written, and the roots' stand-ins cast no vote.
#
# vota::IConfereVotoEmCargo (cconferevotoemcargo.h, new, and cconferevotoemcargo.cpp, named by its records): the head,
# the constructor (fn 1165), the destructor (fn 1717), FinishStateAudio (11792) and GetMensagem (11789). The destructor
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
# above line 41.
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
# target's second caller of each GetTelaCargoAtual is the class's ProcessInputAudio, pending: with StartStateAudio its
# only caller binaryen inlined GetTelaCargoAtual into it and merged the two Pede StartStateAudio into one shared body
# (the first link of this change, names.tsv), so the roots stand in for the four ProcessInputAudio. Measured before
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
# cvotacaostateaudio.cpp and the states' files are a choice, since no record gives one; the constructors' record lines
# stay blank (:44 and :45 of the three cpedetitulomesario*.cpp). CPosixRWMutex's six throws sit on their records' lines.
# Which throw holds which literal is chosen from the messages: the code that loaded them is gone, and they stay in the
# target's data. The six enumerators' values are chosen too (eueipcerror.h).
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
    src/app/vota/eleitor/iniciovotacao/testeteclado/cerrotestetecladofim.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesarioinicial.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesariofinal.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesariovotacao.cpp \
    src/api/ipc/posix/cposixrwmutex.cpp
UENUX2_SRCS += $(CVOTACAOSTATEAUDIO_SRCS)
# cconferevotoemcargo.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit
# 122's cgravadorutil.cpp does)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/cconferevotoemcargo.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# seventeen members are not reconstructed: 97-uenux2-cvotacaostateaudio-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/97-uenux2-cvotacaostateaudio-pending.o: $(ROOT)/src/units/97-uenux2-cvotacaostateaudio-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/97-uenux2-cvotacaostateaudio.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votaproporcional/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votamajoritario/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/97-uenux2-cvotacaostateaudio-pending.cpp -o $(R)
# nothing reconstructed references the unit's vtables or CPosixRWMutex's constructor yet:
# 97-uenux2-cvotacaostateaudio-roots.cpp takes their addresses, and builds the CConfereVotoEmCargo instances as their
# callers do; it instantiates that class template, so it compiles with the tree's flags
$(ROOT)/$(APP)/97-uenux2-cvotacaostateaudio-roots.o: $(ROOT)/src/units/97-uenux2-cvotacaostateaudio-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/97-uenux2-cvotacaostateaudio.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/comum/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votaproporcional/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votamajoritario/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/dados/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/97-uenux2-cvotacaostateaudio-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/97-uenux2-cvotacaostateaudio-pending.o $(APP)/97-uenux2-cvotacaostateaudio-roots.o
