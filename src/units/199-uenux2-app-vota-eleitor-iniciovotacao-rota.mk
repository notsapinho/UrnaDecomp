# uenux2 four iniciovotacao states no landed file holds, in app/vota/eleitor/iniciovotacao/:
# - vota::CDefineRotaPreVotacao (cdefinerotaprevotacao.{h,cpp}): NeedChangeState (slot 3, target fn 11994); its slots 2
#   and 7 are vota::CDefineRotaPosReinicio's bodies (fns 3243 and 5974, unit 104), which binaryen merges with ours; its
#   GetInst, constructor and statics, written in unit 104's shape and compared with nothing: GetInst's one target
#   caller, fn 11991, which holds it inlined, is pending in unit 104, so our link drops GetInst, and the statics' exit
#   destructors 11996 and 11995, in the link, have no voter but themselves (no-candidate). CVerificaEleicaoPassou's are
#   left unwritten instead (below): either way is a choice the bytes do not decide;
# - vota::CInicioVotacao (ciniciovotacao.{h,cpp}): GetInst (fn 2880), with its constructor inlined by binaryen, and its
#   statics' exit destructors (11990, 11989); the destructor is the shared fns 448 and 765;
# - vota::CVerificaEleicaoPassou (cverificaeleicaopassou.{h,cpp}, its records :56 and :70): StartState (fn 11914), with
#   vota::testeteclado::CPreZeresima's GetInst (unit 138's file) and vota::CLogVota::LogaDataEleicaoInvalida (added to
#   app/vota/log/clogvota.cpp, unit 119's file) inlined by binaryen;
# - vota::CGeraDadosDinamicos (cgeradadosdinamicos.{h,cpp}, its record :47): GetInst, constructor and statics, which
#   binaryen inlines into CPreZeresima::GetEstadoPassouNoTeste (fn 5945, unit 138), and the statics' exit destructors
#   (11867, 11866).
# The class heads say what each layout rests on; 199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.cpp names the
# slots left (CGeraDadosDinamicos::StartState 11865, CInicioVotacao's StartState 11988 and ProcessTick 11987) and what
# they wait for. Not written: CVerificaEleicaoPassou's GetInst and statics, inlined into fn 7160, not written.
#
# Evidence, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before
# steps 7 to 9 matched it:
# - 11994: when comum::CInformacaoEleicao over the parameters (fn 603) says ImprimeBJust (fn 1950) and the load is no
#   voter training (comum::CAppInfo::EhTreinamentoEleitor, fn 697), it clears +12, goes to vota::CAguardaMensagem and
#   posts message 7 to vota::CThreadOperador's queue (api::CPriorityMessageQueue::Post, inline in its header, which
#   calls Insert, fn 501, with priority 1); else it goes to
#   vota::CIniciodeCiclo and clears +12, and returns true either way. Of three forms measured, only GetInst's result
#   held in a local before the two assignments gives the else branch's stores in the target's order (+4, then +12, after
#   the call): the two statements written next state first gave +12 before +4 (15 over 61 rows, 5 inserted, 3
#   deleted), the other way round +12 before the call (in the object, wasm-objdump -d); with the local, 7 over 56,
#   operand-only.
# - 11914: it sets the next state to itself; outside a training load (+48 of comum::CAppInfo::GetGeral(), the load's
#   phase) it copies comum::CConfiguracaoEleicao's CDateTime at +580 and, when the current time is not before it, logs
#   (api::CLoga::loga with +4 and severity 2), shows CTelasVota's +76 (a copy, slot 2), posts message 0 with priority
#   100 to vota::CThreadOperador's queue (fn 501), sounds api::IBeep's slot 3 (BeepError, record :56 column 13, the
#   default std::source_location of CPolySingleton<IBeep>::instance) and returns; else it goes to CPreZeresima for the
#   vote's first three states and throws vota::EUeVotaError 9376 (record :70) after LogaErroEstadoAplicativo for any
#   other. The message is a temporary: as a named local it kept its frame slot, the std::source_location took +16 and
#   the throw's string +4 (46 over 244 rows, 2 inserted, 1 deleted), where the target reuses the message's +20 and has
#   the string at +8; as a temporary, 40 over 242, operand-only.
# - 2880: the constructor passes 4 to the base's; +12 copies CTelasVota's +116 (GetTelaInicioVotacao), +20 is the
#   operator's form, +28 copies comum::CConfiguracaoEleicao's +556, +40 a stopped 1000-ms tick (fn 807). Its body builds
#   the form with api::CMTFormBuilder (fn 203, the builder destroyed inline at the end): the time's hour and minutes
#   (api::CTime::Format, fn 779, with "h" and "mm"), "Aguarde o horário de início da votação" at {1, 1}, "Votação a
#   partir das " at {1, 2}, the hour with "h", or with "h", the minutes and "min" (147602, a literal of its own) when the
#   minutes are not "00", at {22, 2}, "Hora atual: " at {1, 3}, the clock at {13, 3} (AddClock, fn 728), and moves
#   GetInteractiveForm("", true) (fn 301) into +20. 60 over 910 rows, operand-only. Its four target callers (7306, 11848,
#   11858, 11920) are pending: the roots stand in for them.
# - 5945's and 11914's GetInst of other classes, and 3279 and 4511: unit 138's and 119's fragments.
#
# Chosen, no evidence names them: the paths, by how-to step 3's rule 4 (the class name in lower case) where no record
# names the file (cdefinerotaprevotacao.cpp, ciniciovotacao.cpp), each header beside its .cpp, and the directory:
# CDefineRotaPreVotacao's vtable (@1543448) is followed by CImprimindoZeresima's vtable and
# iniciovotacao/cimprimindozeresima.cpp's records (@1543548), the adjacent recorded side, and preceded by unrecorded
# vtables and fn 3876's records (api::CLp::CLp, mock/app/simulador/wasm/cwasmclp.cpp:10, and cpolysingleton*.h), so
# the adjacent side is taken (docs/reference/facts/placing.md P5), and its one vptr store is that file's 11991;
# CInicioVotacao's (@1543592) lies between cimprimindozeresima.cpp's records and cinformacaozeresimatardia.cpp's
# (@1543692), where a name in name order would sort after the second: the directory's data are not in name order there
# (cgeradorresumozeresima.cpp follows), so the name is a choice. Chosen too: every data member's and static's name, GetInst (unit 104's convention), the locals, the
# temporary message, the getters' and LogaDataEleicaoInvalida's names, 9376's enumerator, the switch with indented cases
# (column 19 of :70) and the lines of every function no record places (cverificaeleicaopassou.cpp's StartState starts
# where its records fall; ciniciovotacao.cpp's and cdefinerotaprevotacao.cpp's functions are in link order: the statics'
# destructors precede their class's slots in band 0, so the statics are defined above them); the destructor declared
# first in CInicioVotacao, StartState as the key function in the other three classes.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_ROTA_SRCS := src/app/vota/eleitor/iniciovotacao/cdefinerotaprevotacao.cpp \
    src/app/vota/eleitor/iniciovotacao/ciniciovotacao.cpp \
    src/app/vota/eleitor/iniciovotacao/cverificaeleicaopassou.cpp \
    src/app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_INICIOVOTACAO_ROTA_SRCS)
# cdefinerotaprevotacao.cpp, ciniciovotacao.cpp and cverificaeleicaopassou.cpp include
# app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through CConfiguracaoMunicipio's CHorariosUrna (an include
# path, not a flag of the code: unit 88 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/cdefinerotaprevotacao.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/ciniciovotacao.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/cverificaeleicaopassou.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.cpp gives the vtables trapping
# bodies, compiled with the unit's flags; its prerequisites are every header of both trees, as unit 138's are
INICIOVOTACAO_ROTA_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.o: $(ROOT)/src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk $(INICIOVOTACAO_ROTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.cpp -o $(R)
# nothing reconstructed stores two of the classes' vptrs or calls CInicioVotacao::GetInst yet:
# 199-uenux2-app-vota-eleitor-iniciovotacao-rota-roots.cpp takes the vtables' addresses and stands in for the callers
$(ROOT)/$(APP)/199-uenux2-app-vota-eleitor-iniciovotacao-rota-roots.o: $(ROOT)/src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/199-uenux2-app-vota-eleitor-iniciovotacao-rota-pending.o $(APP)/199-uenux2-app-vota-eleitor-iniciovotacao-rota-roots.o
