# uenux2 vota operador: vota::CValidaIdentidade (app/vota/operador/leidentidade/cvalidaidentidade.{h,cpp}), the state
# vota::CPedeIdentidade::ProcessInput goes to with an identifier typed, and the two states
# vota::CRegistraDigitalOperador::ProcessTick goes to, vota::CTentativaCapturaDigitalEsgotada and
# vota::CDigitalNaoCapturada (app/vota/operador/confirmaidentidade/, a file each). No record names these files. Target
# fns matched:
# - CValidaIdentidade's destructors 2749 (the D2) and 10628 (the D0), its map's tree destroy 1906, ProcessInput 10626,
#   and its statics' exit destructors 10630 and 10629; vota::MontaOpcoesIdentidade (5420), which StartState calls
#   twice, matched by its content (step 9's first scan; the one target function its body equals);
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
# - StartState (10627, slot 2) is written and not matched. In the target's order: vota::GetIdentidadeDigitada (fn 3623)
#   into a local; comum::md::CValidadorIdentidade::GetInst (fn 1926) and a 16-byte frame binaryen inlined, the member
#   TiposValidos added to unit 110's cvalidadoridentidade.cpp (the types of the rules whose IRegraIdentidade::EhValida,
#   fn 3723, accepts the number); then a switch on the count. None: the next state is vota::CIdentidadeInvalida's,
#   whose GetInst and constructor it holds inlined (unit 161's cidentidadeinvalida.cpp, written now: a 20-byte object,
#   CAppState(2), AddBeep(2), "Identidade:" at {1, 1}, the identifier typed through the slot 3860, fn 10670, at {13, 1},
#   "Número errado" at {1, 2}, "CORRIGE: retornar" at {1, 4}, AddInputControl, GetInteractiveForm("", true), the static
#   mutex @1905340 and pointer @1905364). One: CLogVota's loga (fn 233) of std::format("Identificador digitado pelo
#   mesário foi: ({})", the name option 1 has in the map 5420 builds from a copy of the types, found through
#   operator[], which inserts a default node when the key is absent, as the target's body does), then
#   SetTipoIdentidadeDigitada (fn 3619) of the first type and vota::CProcuraEleitor::GetInst's state (fn 5421). More:
#   the next state is this, the map at +20 is 5420's (from a copy) and the form at +12 MontaTelaOpcoes's (held inlined
#   by binaryen behind a 464-byte frame: AddBuzz(51, 10), AddClock at {33, 1}, "Tipo de identidade digitada" at {1, 1},
#   "{}-{}" of each option's number and name at {1, number + 1}, AddLed(0), "ESCOLHA O TIPO:" at {24, 4},
#   AdicionaCampoNumerico(builder, 1, false, {40, 4}) (fn 1151), "CORRIGE: retornar" at {1, 4},
#   GetInteractiveForm("", true)), then the form's slot 2. Measured with pnpm wasm score in the whole link, before
#   steps 7 to 9: `149 over 1740 rows (same 1591, replaced 121 [118 operand-only], inserted 10, deleted 18)`. Two
#   places differ, neither explained. (1) In the case of more types the target loads the vector's end and begin again
#   after its store of m_pNextState, for the copy; ours keeps the switch's values (wasm-objdump -d of
#   cvalidaidentidade.cpp.o: clang's code, before binaryen). The same object built without strict aliasing
#   (UENUX2_NOTBAA_FILES with this file, on the make command line, a scratch link) keeps them too: `157 over 1745`. (2)
#   In MontaTelaOpcoes's loop the target reads the option's number for the point after the formatted text and before
#   it stores the point's x, ours after that store. With api::SPoint given a constructor of its two coordinates (an
#   -iquote overlay of api/gui/primitives.h for this object only) the loop reads as the target's: `144 over 1739 rows
#   (same 1595, replaced 120 [117 operand-only], inserted 9, deleted 15)`, (1) left. primitives.h is not this unit's
#   file and every api/gui user includes it, so that is a lead, not landed. TiposValidos's loop is the target's with
#   std::views::filter (find the first rule that accepts, push, find from the next); a range-for with an if read
#   `211 over 1742`. Its trap and the pending file went.
# - 5420 builds a std::map<int, std::pair<std::string, ETipoIdentificadorEleitor>>: per type of its by-value vector,
#   1 "Título de eleitor", 2 "CPF" and 3 "Identificador" (the tail of "o Identificador" in the data) with the type,
#   numbered from 1; a type past the three gets no option and no number. Each value is built from the literal and the
#   type, with no call of md::CEleitorIdentidade's constructor (fn 566, which formats and validates), so the map's
#   value type is no CEleitorIdentidade. Forms of the insertion, measured on 5420 alone (try-tu.sh --single):
#   emplace(n, std::make_pair(std::string(text), tipo)), insert({n, {text, tipo}}), insert(std::make_pair(...)) and
#   insert(value_type(...)) read `32 over 358` (11 deleted: the target carries the last word of the "CPF" string's
#   storage from one turn of the loop to the next, which ours folds); emplace(n, mapped_type(text, tipo)) and emplace(n,
#   mapped_type{text, tipo}) `16 over 358`, no row inserted or deleted, the two rows that are no operand being the lone
#   link's re-encoded Latin-1 literal; in the whole link `12 over 358`, all operand rows, and it matches.
# - The exit destructors of CIdentidadeInvalida's statics, 10671 (the mutex) and 10672 (the pointer), read `differs` on
#   the census's pairs with other objects' destructors: 10627 is the one other target function that loads 1905340 and
#   1905364 (grep over build/out/splat/pieces/asm), so they wait for its match.
#
# Chosen: every name of a member, a data member, a free function, the alias and the helpers but the overrides'
# (StartState, ProcessInput and the destructors are comum::CAppState's slots, app/comum/cappstate.h);
# ProximoEstadoOpcaoDigitada's being a member (it reads the form and the map) and its result type; MontaOpcoesIdentidade
# and MontaTelaOpcoes being free functions of vota with external linkage, in this file, above StartState; the map's
# value type, std::pair<std::string, ETipoIdentificadorEleitor> (the layout the bodies read: the name at +0, the type
# at +12) and the alias TOpcoesIdentidade; the lambda of TiposValidos; tipos[0] for the first type; the switch and if
# spellings; the files (how-to step 3, rule 4: the class's name in lower case) and their directories, by the data:
# CTentativaCapturaDigitalEsgotada's and CDigitalNaoCapturada's vtables and typeinfos lie between cpededigital.cpp's
# last record (@1592092) and cregistradigitaloperador.cpp's vtable (@1592424), each followed by its own copy of the
# inline Read()'s record (@1592336, @1592408), so each class is a TU of its own in confirmaidentidade/;
# CValidaIdentidade's vtable and typeinfo (@1589064, @1589108) lie between CProcuraEleitor's (@1589008) and
# IEleitorImpedidoVotar's (@1589136), leidentidade/ objects.
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
# The roots file (278-uenux2-cvalidaidentidade-roots.cpp) takes two vtables' addresses and stands for target callers
$(ROOT)/$(APP)/278-uenux2-cvalidaidentidade-roots.o: $(ROOT)/src/units/278-uenux2-cvalidaidentidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/278-uenux2-cvalidaidentidade.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/278-uenux2-cvalidaidentidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/278-uenux2-cvalidaidentidade-roots.o
