# uenux2 vota operador: vota::CValidaIdentidade (app/vota/operador/leidentidade/cvalidaidentidade.{h,cpp}), the state
# vota::CPedeIdentidade::ProcessInput goes to with an identifier typed, and the two states
# vota::CRegistraDigitalOperador::ProcessTick goes to, vota::CTentativaCapturaDigitalEsgotada and
# vota::CDigitalNaoCapturada (app/vota/operador/confirmaidentidade/, a file each). No record names these files. Target
# fns matched:
# - CValidaIdentidade's destructors 2749 (the D2) and 10628 (the D0), its map's tree destroy 1906, ProcessInput 10626,
#   and its statics' exit destructors 10630 and 10629;
# - CDigitalNaoCapturada::ProcessInput 10458 and CTentativaCapturaDigitalEsgotada::ProcessInput 10461, a thunk into
#   2295, which matches with it (src/units/161-uenux2-app-vota-operador-identidade.mk). The two states' StartState is
#   1070 and their destructors 244 and 387, matched before.
#
# Evidence, each class's header says the rest:
# - CValidaIdentidade (vtable @1589064 [2749, 10628, 10627, 7480, 1661, 218, 425, 10626, 425]): the destructor out of
#   line (the D0 10628 calls the D2 2749, then frees `this`), final (2749 stores no vptr:
#   docs/reference/facts/reading.md R4, R5), destroying the std::map at +20 through its tree's destroy (fn 1906) and
#   then the form at +12. GetInst and the constructor are held inlined by CPedeIdentidade::ProcessInput (10677, unit
#   161's), the one store of the vptr (1589072): s_inst @1905672 and s_mutex @1905648, a new of 32 bytes, CAppState's
#   constructor with EVENTO_ENTRADA (2), the map and the form left empty. The statics' exit destructors are 10630 (which
#   calls 2749) and 10629.
# - ProcessInput (10626, slot 7): Read() of the form at +12 (record cinteractiveform.h:57 @1589120); on CORRIGE (5)
#   CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado (fn 2097) and CPedeIdentidade::GetInst's state (fn 652); on
#   CONFIRMA (9) the state a 400-byte frame returns, stored only when not null. That frame is a function binaryen
#   inlined at its one call site, and clang keeps it out of line (wasm-objdump -x of cvalidaidentidade.cpp.o lists
#   ProximoEstadoOpcaoDigitada): the form's first input's text copied; no state unless it is one character; std::stoi of
#   it (fn 3323) found in the map (std::map::find, inline); found, CLogVota::GetInst's loga (fn 233) of
#   std::format("Identificador digitado pelo mesário foi: ({})", the value's string), inline over fn 146 (__vformat_to),
#   then SetTipoIdentidadeDigitada (fn 3619) of the value's word at +12 and CProcuraEleitor::GetInst's state (fn 5421);
#   not found, loga of "Identificador inválido para o tipo informado" and no state. Measured on the plain link (pnpm
#   wasm score, default depth): with the not-found branch first in the source it scored 138 over 510 rows (same 372,
#   replaced 26 [24 operand-only], inserted 57, deleted 55), the target's two blocks in the other order; with the found
#   branch first, 34 over 453, all operand-only, and it matches.
# - CDigitalNaoCapturada (vtable @1592352) and CTentativaCapturaDigitalEsgotada (@1592280): each final over CAppState
#   with the 49 states' shared destructors (244, 387) and StartState (1070), its form at +12. 10458 goes to
#   CRegistraDigitalOperador::GetInst's state (fn 5396, unit 221's) on CONFIRMA (9); 10461 is `f2295(p0, 9, 1592336)`,
#   its Read() record. Their GetInst and constructors are held inlined by CRegistraDigitalOperador::ProcessTick (10451,
#   pending: unit 221), the one store of each vptr (1592288, 1592360), and are not written.
#
# Chosen: every name of a member, a data member and the helper; ProximoEstadoOpcaoDigitada's being a member (it reads
# the form and the map) and its result type; the map's value type, md::CEleitorIdentidade: ProcessInput formats the
# string at +0 of the value and passes the word at +12 to SetTipoIdentidadeDigitada, which fits that class's layout (a
# std::pair<std::string, ETipoIdentificadorEleitor> has the same layout and is not measured); the switch and if
# spellings; the files (how-to step 3, rule 4: the class's name in lower case) and their directories, by the data:
# CTentativaCapturaDigitalEsgotada's and CDigitalNaoCapturada's vtables and typeinfos lie between cpededigital.cpp's
# last record (@1592092) and cregistradigitaloperador.cpp's vtable (@1592424), each followed by its own copy of the
# inline Read()'s record (@1592336, @1592408), so each class is a TU of its own in confirmaidentidade/;
# CValidaIdentidade's vtable and typeinfo (@1589064, @1589108) lie between CProcuraEleitor's (@1589008) and
# IEleitorImpedidoVotar's (@1589136), leidentidade/ objects.
#
# Pending (278-uenux2-cvalidaidentidade-pending.cpp says what it waits for): CValidaIdentidade::StartState (10627).
#
# Roots: the two states' vtables (for 10451), and stand-ins for two members other units' sources hold: unit 221's
# CRegistraDigitalOperador::GetInst, for its caller 10443, and unit 161's CVerificaDadoEleitor::GetInst, for its four
# callers 10447, 10473, 10477 and 10485. Each of those units' fragments says so.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_VALIDAIDENTIDADE_SRCS := src/app/vota/operador/leidentidade/cvalidaidentidade.cpp \
    src/app/vota/operador/confirmaidentidade/ctentativacapturadigitalesgotada.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalnaocapturada.cpp
UENUX2_SRCS += $(APP_VOTA_VALIDAIDENTIDADE_SRCS)
# The member not reconstructed: 278-uenux2-cvalidaidentidade-pending.cpp gives CValidaIdentidade's vtable a trapping
# body, compiled with UENUX2_CXXFLAGS, as unit 161's pending file is
$(ROOT)/$(APP)/278-uenux2-cvalidaidentidade-pending.o: $(ROOT)/src/units/278-uenux2-cvalidaidentidade-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/278-uenux2-cvalidaidentidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/leidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/eleitor/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/app/dados/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/278-uenux2-cvalidaidentidade-pending.cpp -o $(R)
# The roots file (278-uenux2-cvalidaidentidade-roots.cpp) takes two vtables' addresses and stands for target callers
$(ROOT)/$(APP)/278-uenux2-cvalidaidentidade-roots.o: $(ROOT)/src/units/278-uenux2-cvalidaidentidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/278-uenux2-cvalidaidentidade.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/278-uenux2-cvalidaidentidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/278-uenux2-cvalidaidentidade-pending.o $(APP)/278-uenux2-cvalidaidentidade-roots.o
