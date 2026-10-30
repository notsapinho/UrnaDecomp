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
# EUeIpcError. The class headers say what each layout and name rests on. The ten members not written are in
# 97-uenux2-cvotacaostateaudio-pending.cpp, with what each waits for. 1785, the CVotacaoStateAudio constructor, is not
# reconstructed: it calls fns 316 and 807, which have no name, and with it fns 5929 and 11752.
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
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3). Slot 15:
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
# ten members are not reconstructed: 97-uenux2-cvotacaostateaudio-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/97-uenux2-cvotacaostateaudio-pending.o: $(ROOT)/src/units/97-uenux2-cvotacaostateaudio-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/97-uenux2-cvotacaostateaudio.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/votaproporcional/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/97-uenux2-cvotacaostateaudio-pending.cpp -o $(R)
# nothing reconstructed references the unit's vtables or CPosixRWMutex's constructor yet:
# 97-uenux2-cvotacaostateaudio-roots.cpp takes their addresses
$(ROOT)/$(APP)/97-uenux2-cvotacaostateaudio-roots.o: $(ROOT)/src/units/97-uenux2-cvotacaostateaudio-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/97-uenux2-cvotacaostateaudio.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/97-uenux2-cvotacaostateaudio-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/97-uenux2-cvotacaostateaudio-pending.o $(APP)/97-uenux2-cvotacaostateaudio-roots.o
