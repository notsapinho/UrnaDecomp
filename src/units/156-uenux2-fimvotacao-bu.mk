# uenux2 the BU states of app/vota/eleitor/fimvotacao/ and comum's menu items. By class, with the target functions:
# - vota::CLimiteCopiasBUAtingido: StartState (fn 12027), ProcessInput (fn 12026), the out-of-line destructor (the
#   shared fns 244, 387), and GetInst (inlined into fn 12023, unit 185's), the constructor and the statics (exit-time
#   destructors fns 12028, 12029);
# - vota::CMostraQRCodeCertificado: ProcessInput (fn 12038), the destructor (fns 785, 1560), GetInst (inlined into fn
#   12051, so dropped from our link), the constructor and the statics (exit-time destructors fns 12041, 12042);
# - vota::CQuerImprimirBU: StartState (fn 12035) and the destructor (fns 244, 387);
# - vota::CRetirarMR: ProcessInput (fn 12030) and the destructor (fns 1284, 2884);
# - vota::CImprimindoBU: GetInst (fn 5986), the constructor, the destructor (fns 244, 387) and the statics (fns 12079,
#   12080);
# - comum::CItemImprimeEstadoUrna, CItemImprimeListaEleitores, CItemParametrosUrna and CItemVersoesPacotes: slot 2 (fns
#   11669, 11668, 11667, 11666), in app/comum/informacao/citemmenu.cpp, whose note says what it rests on;
# - four vota::CLogVota members these states and others call, in app/vota/log/clogvota.cpp (unit 119's file), after
#   LogaPedidoTituloSuspensao: LogaImprimindoRelatorio (fn 1127), LogaMesarioIndagadoQualidadeBU (fn 4551),
#   LogaQtdViasAdicionaisExcedeMaximo (fn 4556) and LogaHabilitacaoCanceladaReconhecimentoBiometrico (fn 2495), the last
#   two thunks of the body binaryen merges from them (fn 6115).
# 156-uenux2-fimvotacao-bu-pending.cpp names the slots left as traps and what each waits for; the class heads say what
# each layout rests on. The destructors are bodies other states share, so the match lines of 785 and 1560, and of 1284
# and 2884, name this unit's symbols, the first in link order (docs/reference/facts/splat.md S6).
#  Evidence: the records name the .cpp files (climitecopiasbuatingido.cpp:37, cmostraqrcodecertificado.cpp:39,
# cquerimprimirbu.cpp:40 and 41, cretirarmr.cpp:54 to 96, cimprimindobu.cpp:70 to 114). The vtables' slots, the D0
# shapes (a call of the D2 and a free: an out-of-line destructor) and the D2s (no vptr store: final) are
# docs/reference/facts/reading.md R4 and R5. Each ProcessInput holds CInteractiveForm::Read() inlined (its record's
# copy, api/gui/cinteractiveform.h:57, in each object), compared with api::INPUT_CONFIRMA (9) or INPUT_CORRIGE (5). The
# Assert texts give StartState's conditions, the getter GetQtdBU and the enumerator EAVIMPRIMIRBU (61, the value the
# body compares); the two records' columns (102 and 85) fix the codes' names at 34 characters with the invocation
# indented four columns and qualified api::. CImprimindoBU's constructor copies CTelasVota's +100, which ctelasvota.h
# gains the getter GetTelaImprimindoBU for. CLimiteCopiasBUAtingido::StartState's Assert text ("Assert
# (comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA)", code 3473) is longer than its record's column
# (37:56), so the invocation closes on a line of its own: with the code there indented eight columns and qualified
# api::, the name has 42 characters, chosen to that length. EAVENCERRADA comes with
# app/comum/dados/md/estadoaplicacao/cestadogeralvota.h, which this unit takes byte for byte from the unit that writes
# it. Its constructor copies CTelasVota's +108 (fn 12023, offsets 0x7c and 0x86), through the getter
# GetTelaLimiteCopiasBUAtingido, and GetInst has the shape of CImprimindoBU's (fn 5986): the vptr 1542836, the base's
# constructor with 2, the pointer at @1833960 and the mutex at @1833936, read by fns 12029 and 12028 alone besides fn
# 12023. The CLogVota members: 1127 builds the 37-byte format string at 234223 (ledger/strings.tsv) with
# std::format over ConverteERelatoriosUE's string (fn 5879) and an unsigned (the argument code 205: 13, then 6), and
# 4551 makes a std::string of its 51-byte text; both pass it to IEventosLog::loga (fn 233) as a call, which
# ieventoslog.cpp's members hold inlined, so they are in another TU: clogvota.cpp, beside CLogVota's other out-of-line
# members (a reading). 4556 and 2495 are thunks of fn 6115, which builds a 55-byte std::string from the seven words its
# callers pass and calls IEventosLog::logaAlerta (fn 1398); our link merges the two members into that body too
# (build/out/wasm-map/vota_web/names.tsv names a byn$mgfn-shared$ body after LogaQtdViasAdicionaisExcedeMaximo).
# Each is called on CLogVota::GetInst()'s result: 1127 by ten slots (12078 passes 3 and 1), 4551 by 12077 and 12078,
# 4556 by 12027 and 12081, 2495 by 10466, 10473, 10477 and 10485. CRetirarMR::ProcessInput's record (78:19) is the
# instance() call of CPolySingleton<comum::IInterfaceInit>: the 18 characters of ` bool ehDemo = ` before it are a
# chosen spelling of that length.
#
# Not matched, with what it waits for:
# - fn 12030, CRetirarMR::ProcessInput, `differs` at +0x38: the target carries the Read() result out of a value block
#   (`block (result i32)` and a `local.set` after it), ours sets the local in each arm. Measured on the whole link, by
#   `pnpm wasm score`: the ternary written here and an if/else of the two Read() calls give the same rows (score 15 over
#   95, 2 inserted, 1 deleted); one Read() on the form the ternary selects gives score 44 over 98, and an if per arm
#   that compares its own Read() and sets m_pNextState gives 50 over 125 (32 inserted). No other form found. The
#   written form's other differing rows are operand-only (12 of 12: calls and data addresses).
# - fns 12041 and 12042, CMostraQRCodeCertificado's statics' destructors: their only other reader is GetInst, inlined
#   into fn 12051 (pending in unit 37), so the data have no voter but themselves, and 12042 is also a thunk of fn 1564,
#   which matches since unit 138 gave our link its third member (unit 37 says so for fn 2888).
#  Chosen, no evidence names them: the member names; GetInst's name and its reference result; s_inst and s_mutex and
# their order (the shape unit 104 measured: GetInst first, then the pointer and the mutex); the local trava; the
# destructors declared first; the lines of the functions with no record (above the first record line of each file, and
# ProcessInput below StartState's record lines, and in climitecopiasbuatingido.cpp the constructor, GetInst and the
# statics above StartState); +12's type in CRetirarMR (an IForm<IScreen>: only its slot 2 is
# called); the getters' names (GetEntradas in cinteractiveform.h, GetNumViasImpressasRelatorios in cestadogeralvota.h,
# GetTelaImprimindoBU and GetTelaLimiteCopiasBUAtingido in ctelasvota.h); the enumerators' names
# (vota::EUE_VOTA_QRCODE_CERTIFICADO_NUMERO_INPUTS_INVALIDO, 9408; api::EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO and
# EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO, 3474 and 3475; api::EUA_LIMITECOPIASBUATINGIDO_ESTADO_INVALIDO, 3473);
# `using namespace comum;` in cquerimprimirbu.cpp and climitecopiasbuatingido.cpp, which lets the Assert texts spell
# EAVIMPRIMIRBU, EAVENCERRADA and poInfo's class unqualified; the CLogVota members' names (from their messages), their
# place in clogvota.cpp and LogaImprimindoRelatorio's parameter types (an enum and an unsigned int: the body only
# forwards them); `!= 1` with the throw first in fn 12038; ehDemo and
# the ternary in fn 12030; the headers' paths beside their .cpp files. Each state's form member is spelled
# std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>>, the type of CFormInterativoTelaVota (a record
# names it for CMostraQRCodeBU's form, unit 37; for the others it is chosen alike), spelled out where a file does not
# include its header, app/vota/eleitor/cvotacaostateaudio.h. A TU that calls Read() can include it since the two
# declarations of api::EInputResult agree (climitecopiasbuatingido.cpp does, through ctelasvota.h).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
FIMVOTACAO_BU_SRCS := src/app/vota/eleitor/fimvotacao/cimprimindobu.cpp \
    src/app/vota/eleitor/fimvotacao/climitecopiasbuatingido.cpp \
    src/app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.cpp \
    src/app/vota/eleitor/fimvotacao/cquerimprimirbu.cpp \
    src/app/vota/eleitor/fimvotacao/cretirarmr.cpp \
    src/app/comum/informacao/citemmenu.cpp
UENUX2_SRCS += $(FIMVOTACAO_BU_SRCS)
# citemmenu.cpp reaches CConfiguracaoEleicao's CParametrosUrna, whose CHorariosUrna includes Boost (unit 88 gives
# cconfiguracaoeleicao.cpp the same path)
$(ROOT)/$(APP)/uenux2/src/app/comum/informacao/citemmenu.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 156-uenux2-fimvotacao-bu-pending.cpp gives the vtables trapping bodies, compiled with
# the unit's flags
$(ROOT)/$(APP)/156-uenux2-fimvotacao-bu-pending.o: $(ROOT)/src/units/156-uenux2-fimvotacao-bu-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/156-uenux2-fimvotacao-bu.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/156-uenux2-fimvotacao-bu-pending.cpp -o $(R)
# nothing reconstructed builds these states or comum's items yet: 156-uenux2-fimvotacao-bu-roots.cpp keeps their
# vtables, the way the target reaches their slots, and stands for the callers of CImprimindoBU::GetInst and of the four
# CLogVota members
$(ROOT)/$(APP)/156-uenux2-fimvotacao-bu-roots.o: $(ROOT)/src/units/156-uenux2-fimvotacao-bu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/156-uenux2-fimvotacao-bu.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/156-uenux2-fimvotacao-bu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/156-uenux2-fimvotacao-bu-pending.o $(APP)/156-uenux2-fimvotacao-bu-roots.o
