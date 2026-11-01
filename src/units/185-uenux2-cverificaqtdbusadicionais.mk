# uenux2 vota::CVerificaQtdBUsAdicionais (app/vota/eleitor/fimvotacao/cverificaqtdbusadicionais.cpp, the file its
# records name): StartState (target fn 12023), which holds vota::CLimiteCopiasBUAtingido::GetInst inlined (unit 156's
# file writes it). What this unit rests on beyond its source is written where it lands: the getter
# CTelasVota::GetTelaLimiteCopiasBUAtingido (app/vota/eleitor/comum/ctelasvota.h, +108), GetEstadoEncerramento and the
# enumerators EAVENCERRADA and EAEFIMDOSTRABALHOS (app/comum/dados/md/estadoaplicacao/cestadogeralvota.h), and the two
# Assert codes (api/util/eueasserterror.h).
#  Evidence: the records (cverificaqtdbusadicionais.cpp 36:102 and 37:116) and their Assert texts ("Assert
# (egVota.GetEstadoVota() == EAVENCERRADA)", "Assert (egVota.GetEstadoEncerramento() == EAEFIMDOSTRABALHOS)", codes 3461
# and 3462) give the local's name, the getters and the enumerators. The body (`pnpm --silent wasm fn
# ../target/vota_web_wasm.wasm 12023` from asmlift-wasm/) compares the two words of comum::CAppInfo::GetVota()'s result
# with 64 and 52, builds a comum::CInformacaoEleicao over CConfiguracaoEleicao's parameters (+88, fn 603) in its frame,
# adds GetNumViasBU (fn 3847) and GetNumViasBUAdicionais (fn 5914) and compares the sum with the BU count's byte (+8),
# then stores CLimiteCopiasBUAtingido::GetInst()'s result (the vptr 1542836, @1833960, @1833936 and CTelasVota's +108,
# inlined) or CEmitirMaisBU::GetInst()'s (fn 3879) in m_pNextState. The vtable's slots 0 and 1 (fns 174, 144) are the
# destructors the states with no data member share, and fn 7160, which holds GetInst inlined, frees the old object with
# no call through the vtable: final (src/units/104-uenux2-app-vota-estados.mk has the shape).
#  Chosen, no evidence names them: the codes' names (the columns leave 45 characters for each with the invocations
# indented four columns and the codes qualified api::); the local egVota's type (a const reference; the Assert text gives
# its name only) and the CInformacaoEleicao local's name; an if/else over m_pNextState, where the target stores once after
# a value block: the if/else gives the target's rows (before step 8, `pnpm wasm score` against the plain link: 31 over
# 132 rows, all operand-only), and no other spelling was tried; `using namespace comum;`, which lets the Assert texts
# spell the enumerators unqualified; the lines of the body above its records; the header's path beside the .cpp.
#  Not written: GetInst, its statics and the constructor (the base's with 0), inlined into fn 7160, not written.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CVERIFICAQTDBUSADICIONAIS_SRCS := src/app/vota/eleitor/fimvotacao/cverificaqtdbusadicionais.cpp
UENUX2_SRCS += $(CVERIFICAQTDBUSADICIONAIS_SRCS)
# The TU reaches CConfiguracaoEleicao's CParametrosUrna, whose CHorariosUrna includes Boost (unit 156 gives
# citemmenu.cpp the same path)
$(ROOT)/$(APP)/uenux2/$(CVERIFICAQTDBUSADICIONAIS_SRCS).o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# Nothing reconstructed builds the state: 185-uenux2-cverificaqtdbusadicionais-roots.cpp keeps its vtable, the way the
# target reaches its slots
$(ROOT)/$(APP)/185-uenux2-cverificaqtdbusadicionais-roots.o: $(ROOT)/src/units/185-uenux2-cverificaqtdbusadicionais-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/185-uenux2-cverificaqtdbusadicionais.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/185-uenux2-cverificaqtdbusadicionais-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/185-uenux2-cverificaqtdbusadicionais-roots.o
