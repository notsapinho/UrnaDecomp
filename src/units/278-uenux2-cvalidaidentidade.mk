# uenux2 vota operador: vota::CValidaIdentidade (app/vota/operador/leidentidade/cvalidaidentidade.{h,cpp}), the state
# vota::CPedeIdentidade::ProcessInput goes to with an identifier typed, and the two states
# vota::CRegistraDigitalOperador::ProcessTick goes to, vota::CTentativaCapturaDigitalEsgotada and
# vota::CDigitalNaoCapturada (app/vota/operador/confirmaidentidade/, a file each). No record names these files. Target
# fns matched:
# - CValidaIdentidade's destructors 2749 (the D2) and 10628 (the D0), its map's tree destroy 1906, ProcessInput 10626,
#   StartState 10627, and its statics' exit destructors 10630 and 10629; vota::MontaOpcoesIdentidade (5420), which
#   StartState calls twice, matched by its content (step 9's first scan; the one target function its body equals);
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
#   its Read() record. Their GetInst and constructors, written now, are held inlined by
#   CRegistraDigitalOperador::ProcessTick (10451, unit 221's), the one store of each vptr (1592288, 1592360); their
#   statics' exit destructors (10459, 10460, 10462, 10463) wait for 10451's match (unit 221's fragment says why).
# - StartState (10627, slot 2) matches. In the target's order: vota::GetIdentidadeDigitada (fn 3623) into a local;
#   comum::md::CValidadorIdentidade::GetInst (fn 1926) and a 16-byte frame binaryen inlined, the member TiposValidos
#   added to unit 110's cvalidadoridentidade.cpp (the types of the rules whose IRegraIdentidade::EhValida, fn 3723,
#   accepts the number); then a switch on the count. None: the next state is vota::CIdentidadeInvalida's, whose GetInst
#   and constructor it holds inlined (unit 161's cidentidadeinvalida.cpp, written now: a 20-byte object, CAppState(2),
#   AddBeep(2), "Identidade:" at {1, 1}, the identifier typed through the slot 3860, fn 10670, at {13, 1}, "Número
#   errado" at {1, 2}, "CORRIGE: retornar" at {1, 4}, AddInputControl, GetInteractiveForm("", true), the static mutex
#   @1905340 and pointer @1905364). One: CLogVota's loga (fn 233) of std::format("Identificador digitado pelo mesário
#   foi: ({})", the name option 1 has in the map 5420 builds from a copy of the types, found through operator[], which
#   inserts a default node when the key is absent, as the target's body does), then SetTipoIdentidadeDigitada (fn 3619)
#   of the first type and vota::CProcuraEleitor::GetInst's state (fn 5421). More: the next state is this, the map at +20
#   is 5420's (from a copy) and the form at +12 MontaTelaOpcoes's (held inlined by binaryen behind a 464-byte frame:
#   AddBuzz(51, 10), AddClock at {33, 1}, "Tipo de identidade digitada" at {1, 1}, "{}-{}" of each option's number and
#   name at {1, number + 1}, AddLed(0), "ESCOLHA O TIPO:" at {24, 4}, AdicionaCampoNumerico(builder, 1, false, {40, 4})
#   (fn 1151), "CORRIGE: retornar" at {1, 4}, GetInteractiveForm("", true)), then the form's slot 2. Each case stores
#   its next state at +4 (m_pNextState), through comum::CAppState::SetNextState (app/comum/cappstate.h, out of line in
#   cappstate.cpp; binaryen inlines its one store). Evidence for the call in the case of more types: there the target
#   loads the vector's end and begin again after the store, for the copy 5420 takes, which a call clang cannot see
#   through gives (a reading of why). Measured with pnpm wasm score at the default depth, in scratch links of the plain
#   link.cmd with this one object swapped (docs/reference/facts/workflow.md W13): `m_pNextState = this` in that case
#   reads `144 over 1739 rows (same 1595, replaced 120 [117 operand-only], inserted 9, deleted 15)`, as the landed text
#   read before the setter came, and the call `108 over 1730 rows (same 1622, replaced 108 [108 operand-only], inserted
#   0, deleted 0)`, which matches. In the other two cases the call and an assignment of m_pNextState give byte-identical
#   links (one sha256 for each variant and for the source as written, the rest of the link unchanged): the calls there
#   are a choice, one form for the three. Before the setter: the object built without strict aliasing
#   (UENUX2_NOTBAA_FILES with this file, a scratch link) did not reload either, `157 over 1745`; and with api::SPoint an
#   aggregate, MontaTelaOpcoes's loop read the option's number after storing the point's x, where the target reads it
#   before, `149 over 1740`, which SPoint's constructor of its two coordinates (api/gui/primitives.h, landed with fn
#   653, unit 120) put in the target's order. TiposValidos's loop is the target's with std::views::filter (find the
#   first rule that accepts, push, find from the next); a range-for with an if read `211 over 1742`. Its trap and the
#   pending file went.
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
# - The exit destructors of CIdentidadeInvalida's statics, 10671 (the mutex, `f150(1905340)`) and 10672 (the pointer,
#   `f389(p0, 1905364)`), bodies of unit 161's cidentidadeinvalida.cpp.o, match with 10627, which names the statics:
#   step 8 names s_mutex (0x1d12bc, `vote:1 by:10627`) and s_inst (0x1d12d4, `vote:4 by:10627`) from 10627's vptr-anchor
#   pair, and the exit destructors, the other target functions that load 1905340 and 1905364 (the grep of each over
#   build/out/splat/pieces/asm lists 10627 and the one destructor), are the second matches that hold those names
#   (docs/reference/splat.md section 3, "No circular evidence"). Step 9 paired them by content; the data agree: the
#   target's table holds 10670 at slot 3860, 10672 at 3861 and 10671 at 3862 (wasm-objdump -x -j Elem), 10670 being
#   cidentidadeinvalida.cpp's TextoIdentidadeInvalida. No hand line names either static: the scan and the splat build
#   hold the three matches without one. Their order against 10670 (the pointer's destructor, the mutex's, then 10670, in
#   band 1) is the object's once cidentidadeinvalida.cpp defines the statics above the form helper and the constructor
#   (step 3, "The order of two members"): 10670's first mention, the constructor's form, came above them.
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
# Roots: none. The two states' vtable sinks went, their one storer, 10451, being in the link; their files are compiled
# by unit 221's list, ahead of cregistradigitaloperador.cpp, where the data put them (unit 221's fragment has the
# measurement). The stand-ins for two members other units' sources hold went before, their target callers being in the
# link: unit 221's CRegistraDigitalOperador::GetInst's two, 10458 (this unit's) and 10443
# (unit 161's), and unit 161's CVerificaDadoEleitor::GetInst's four, 10447 (unit 161) and 10473, 10477 and 10485
# (unit 282).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_VALIDAIDENTIDADE_SRCS := src/app/vota/operador/leidentidade/cvalidaidentidade.cpp
UENUX2_SRCS += $(APP_VOTA_VALIDAIDENTIDADE_SRCS)
