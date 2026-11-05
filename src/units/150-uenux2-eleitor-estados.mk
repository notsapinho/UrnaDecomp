# uenux2 three voting states of app/vota/eleitor/ and the screens' names.
#
# vota::CConfirmaVotoSemCandidato (cconfirmavotosemcandidato.cpp, named by its records :64 and :77): slot 15 (fn 7425,
# `return "<literal>";`) and the out-of-line destructor, whose D2 and D0 are the bodies of unit 97's fifteen states (884
# and 883). This object links first of those, so the two match lines are renamed to its symbols (step 9 printed the
# renames). vota::CInstrucaoVotacaoAcessibilidade (cinstrucaovotacaoacessibilidade.cpp, named by its records): the
# out-of-line destructor (D2 2466, D0 7255) and slot 15 (4407), which holds the private GetKeyboardPosition (record :175)
# inlined. vota::CVisualizarCandidatos (iniciovotacao/auxiliares/cvisualizarcandidatos.cpp, named by StartState's
# records): the destructor (D2 2871, D0 11877), GetInst (1279), its constructor inlined, and its statics' exit-time
# destructors (11878, 11880). vota::NomeTela (6718, comum/ctelascargo.cpp, record :60), with ETelaVotacao's enumerators
# (comum/ctelascargo.h) and EUeVotaError's 9327 (app/vota/euevotaerror.h). The class headers say what each layout and
# name rests on. CVisualizarCandidatos::StartState is written and differs (below), so the pending file went.
#
# Not written, and why. CTelasCargo's constructor (fn 2386) calls fn 3251, which had no name. 3251 matches now; its
# match line names the twin src/app/roots_set.cpp's std::map<uebyte, std::string> instance brings, ahead of
# md::CVotosCargos' map's from unit 13's InsereCedula (unit 197); 2386 is still not written.
#
# Written since. CConfirmaVotoSemCandidato's GetInst, its constructor and its two statics: the target holds GetInst,
# the constructor inlined, in fn 4459 (vota::CEleitorVotando::ChamaEstadoProximoCargo, src/units/197-uenux2-celeitorvotando.mk),
# GetInst's one caller, so both are out of line here with no target function of their own, in unit 104's form; their
# lines, after the destructor, are a choice. The statics' exit destructors are fns 7470 (the mutex's, @1832968) and
# 7479 (the pointer's, @1832992); in use band 1 the target links 7479 and 7470 before StartStateAudio and GetMensagem
# (7441, 7425), the order our link has (names.tsv's ld_index). The roots' vtable address went: the vptr store in 4459 keeps it now.
# CInstrucaoVotacaoAcessibilidade's GetInst (fn 4420), its constructor inlined, copies the form at +124
# of vota::CTelasVota through an accessor ctelasvota.h now has; its statics' exit destructors are fns 7287 (the
# pointer's, through the D2) and 7284 (the mutex's). In use band 1 the target links 7287, 7284 and the D0 7255 in that
# order, so the statics are defined above the destructor, which moves below GetInst; our link has the same order
# (names.tsv's ld_index 2812, 2813, 2815). GetInst's two target callers are fns 7377 (unit 197's StartState, in the
# link since) and 7787, not written: the roots stand in for 7787, and its vptr store keeps the vtable the roots took before. The singleton's form is unit 104's;
# the constructor's and GetInst's lines are a choice. CTelasCargo::GetTela (record ctelascargo.cpp:80, code 9330, its
# message formatting the post and NomeTela's name): the target holds it in fn 4135 behind a second stack prologue (pnpm
# wasm fn 4135), binaryen's inlining of a function with one caller, so it is written out of line here and left
# unrooted; it is inlined into CTelasVota::GetTelaCargo (unit 110) in our link too. CConfirmaVotoSemCandidato's
# GetTelaCargoAtual (fn 4483, record :64, code 9307) and StartStateAudio (fn 7441) are unit 97's form (that fragment
# says what it rests on): 4483 joins fn 3921 with three of unit 97's, now with its second caller, ProcessInputAudio
# (7428, below), in the link. Measured before step 8 (pnpm wasm score, whole link): 4420 12 over 55 rows, 4483
# 3 over 8, 7441 11 over 107, 7284 2 over 4 and 7287 4 over 16, all operand-only; each matched at step 9, where 2466's
# match line was renamed from the D2 to its D1 alias. Chosen: GetTelaCargoAtual's parameter name and its being private,
# GetTela's local, the find form, and GetTela's place below NomeTela (lines 76 to 84: the constructor's records :67 and
# :72 stay blank). Other forms are not measured.
# CVisualizarCandidatos::GetCargo (fn 5951): the byte at +24 when +25 is set, else 0, m_cargo.value_or(0), out of line
# in cvisualizarcandidatos.cpp, its place after the statics a choice, and so is its name. Its two target callers,
# vota::CMenuFiltrarCandidatosPorNumero's slots (fns 11891 and 11892): 11892 matches (unit 104's fragment) and 11891 is
# pending there, and the roots stand in for it. 0 over 10 rows (pnpm wasm score, whole link, byte-exact); `m_cargo ?
# *m_cargo : 0` is not measured.
# CInstrucaoVotacaoAcessibilidade's slots 9 and 10 (ProcessInputAudio 7248, records :54 to :60, code 9314;
# StartStateAudio 7242, records :129 and :131) and CConfirmaVotoSemCandidato's slots 13 and 9 (EmiteEcoComInputField
# 4477, record :77, code 9308; ProcessInputAudio 7428), written since and matched. 7242 sets api::ISound's volume (+4)
# to 7 and api::ITextToSpeech's speed to 2 (slot 4), shows the form and keeps the state. 7248 throws unless the form has
# one input field; on Read's 9 it leaves the state and echoes 'C', on 5 it echoes 0, and on 13 it takes the field's last
# key: '3' and '9' raise and lower ISound's volume, '4' and '6' lower and raise ITextToSpeech's speed (slots 5 to 7),
# each saying whether it moved, and any other key echoes 0 (the echo is unit 97's PlayKey). The volume's accessors are
# inline in api/audio/isound.h and the last key's in api/gui/iinputfield.h, each header saying what is chosen. 4477
# echoes the field's last key unless Read returns 5 or 13 and returns Read's result with an empty string; 7428 votes
# null for the post (comum::md::CVoto::NULO_CARGO_SEM_CANDIDATO) when it returns 9 and leaves the state. Measured (pnpm
# wasm score, whole link): the post's id read into a local before CEleitorVotando::GetInst(), as the target calls
# GetInst after it; in RegistraVoto's argument place 7428 scored 15 over 128 rows (3 inserted, 3 deleted), as written
# operand rows only. Lines: StartStateAudio moved below EmiteEcoComInputField, whose throw sits on :77; in use band 1
# the target links 7441, 7428 and 7425 in that order, as our link does (names.tsv's ld_index 4014, 4015, 4016), and the
# rest of the lines are a choice. The locals' names, whose lengths put the calls at :59, :60, :129 and :131's column 18,
# are chosen. TemFala, in the roots, stands for has<api::ITextToSpeech>'s caller 14478 (unit 97 has its copy; its caller
# 7667 is in the link from src/app/roots_texttospeech.cpp); TelaSemCandidato went with 7428, the caller it stood for.
#
# Measured. GetKeyboardPosition: the instance of api::CPolySingleton<api::IUrna> bound to a reference before Modelo() is
# called gives the target's frame, its std::source_location temporary in the slot of the string GetMensagem keeps
# (+20 of a 32-byte frame), and 4407 matches. Other forms put that temporary elsewhere in the object's frame (compiled,
# wasm-objdump -d): Modelo() called on the call's result, with GetMensagem above or below GetKeyboardPosition or the
# result bound to a const std::string&, at +8; the two returns written as an if, at +16; the message built from the
# rvalue GetKeyboardPosition() with operator+, at +16; built with +=, at +12. The first of those, in the whole link,
# scores 23 over 193 rows against 4407 (5 inserted, 4 deleted; pnpm wasm score). The record's column (175:19) fixes the
# length before the call; the names are a choice. The other bodies gave the target's rows as first written:
# CVisualizarCandidatos' constructor, whose three std::optional give GetInst's zero stores, and NomeTela, its cases in
# value order (another order is not measured).
#
# Chosen: the files of the headers (beside their sources), every member and enumerator name, the members' order in each
# class past the first declared (the destructor, declared first as the key function), the lines of the functions no
# record gives (each destructor and CVisualizarCandidatos' GetInst and constructor at the head of their files,
# CConfirmaVotoSemCandidato's slot 15 at line 90, CInstrucaoVotacaoAcessibilidade's slot 15 after GetKeyboardPosition),
# and NomeTela's place above its record so that the throw sits on line 60, column 11.
#
# CVisualizarCandidatos::StartState (fn 11876, slot 2, records :132:15 and :140:19 with EUeVotaError's 9378 and 9379):
# the next state is CMenuVisualizarCandidatos' instance; the candidatures whose candidate, post and party match the
# filters that are set and not 0 are collected as pointers, and 9378 is thrown when none is left; then, for the current
# one, the screen CTelasVota::CriaTelaVisualizacaoCandidato builds (below) with its page number and the count, 9379
# thrown unless the form has one input field, the form shown (Slot2) and read with CInteractiveForm::WaitAndRead
# (api/gui/cinteractiveform.h, its record :62:25, which 11876 alone holds inlined): CORRIGE returns, and on
# INPUT_SEM_TECLA the field's last key '4' or '6' moves to the previous or next candidature, wrapping around.
# - It differs in the numbering of its locals only: 96 over 448 rows in the whole link (pnpm wasm score: 59 rows of
#   local indices; the rest are operand-only, calls, data addresses and the error's destructor's table slot; the 4
#   inserted and 4 deleted rows are one sequence renumbered). Forms compiled, with the local the iterator over the
#   candidatures takes in the object (wasm-objdump -d; 2 as written): an if chain for the filters, a for loop, the wait
#   loop written in StartState, a non-const screen, std::distance for the page and the cases in another order give 2 as
#   well; the iterator over data pointers, `continue` in the loop, ++ and -- in ifs, a const_iterator, and the screen
#   named last give 6 or 7, and the last of those, in the whole link, 131 over 458 rows. No form compiled gives the
#   target's numbering; it stays as first written.
# CTelasVota::CriaTelaVisualizacaoCandidato (fn 6569, in ctelasvota.cpp, unit 110's: a static member, ctelasvota.h says
# why) builds the screen: a fill in colour 31, "VISUALIZAÇÃO" and the post's name for the holder's sex, then label and
# value lines (Partido, Número padded to the post's digits, Nome, Gênero), each below the last, the value a multi-line
# field whose right edge is 478, or where the photos start (644 less 111 and 5 per suplente, 5 at least) when the line
# reaches below 287; for a candidate who runs (situação 0) the holder's photo at (639, 1), 161 by 225, with the post's
# name under it when the post has suplentes, then each suplente through the std::function lambda (12272, record :3366,
# 9356 thrown past two): its photo at y 253 when the post's detail says the suplente has one, its title and Gênero
# lines; for one who does not, two lines in the {25, 0} font; then Situação at 375, Página "n/total", the key D and,
# past one page, the keys 4 and 6. The photos are adicionaFotoEmoldurada (6561, record :487) over a std::bind of the
# reader lambda (record :487's 3323:29), which reads comum::CFotos::GetImagem (3755, unit 109); the target's RTTI names
# the reader $_0 (CDataImage<__bind<...$_0&, const CDadosCandidato&>>, @478246) and the suplentes' lambda $_2
# (__func<$_2, void (short, int)>, @481428).
# - Matched at step 9: 6569; 1588, the line's lambda ($_3); 6561; 12268, 12271, 12272, 12273 and 12276, the
#   std::function's; and 6561's CDataImage, 12520, 12522 and 12524, and its control block, 12529 and 12530. Measured
#   before (pnpm wasm score, whole link): 6569, with the holder's photo written in its body, 382 over 1732 rows (381
#   operand-only; its frame 592 bytes, the target's 528), and with that photo in a lambda of its own, 109 over 1732, all
#   operand-only; 1588, with the photos' start a lambda called after the label's rectangle, 67 over 320 (8 inserted, 5
#   deleted), with the right edge a lambda called in the rectangle's arguments, 11 over 314, and as written (the bottom
#   a named TPosition, the edge's lambda over ints), 8 over 312, all operand-only; 6561 25 over 593 and 12272 39 over
#   520, all operand-only.
# - The lambdas' numbers: llvm-nm of the object named the suplentes' lambda $_1 with textoSexo taking a CSexo::ESexo and
#   $_2, the target's, with textoSexo generic (`const auto`); a reading: clang numbers a function's lambdas in the order
#   it mangles them, and it mangles the reader's (in std::bind's instantiation) and the generic one's early. Other ways
#   to that number were not compiled. The record :3366 spells the parameters `(TPosition, int)`: a using-declaration
#   of api::TPosition in the body and an int parameter give that spelling.
# - Chosen: every name (the lambdas', the locals', the enumerators 9356, 9378 and 9379, whose values are the target's,
#   the accessor csuplencia.h adds for the suplente's photo, and FONTE_SUPLENTE, the {13, 0} font, @476600), which parts
#   are lambdas beyond the two the records give (measured above for the holder's photo and the right edge), the helper
#   adicionaImagem, inlined into 6561, the filters' form and StartState's loop, and every line but the records'.
#
# vota::CVisualizarCandidatos::CarregaCandidaturas (5953), GetCargos (no index: binaryen inlines it into its one caller)
# and SetCargo (inline), for vota::CMenuFiltrarCandidatosPorCargo::StartState (11888; unit 104's fragment has its
# evidence and the forms measured), with std::construct_at<CCandidatura, const CCandidatura&> (5952) and
# std::__uninitialized_allocator_relocate over CCandidatura (5950), the push_back's copy and reallocation, instances
# this object emits first: all three match (5953 named by 11888's call, 5952 and 5950 by pair-addr), and
# cvisualizarcandidatos.h says what each member rests on. Before step 8 they scored 9 over 267 (5953), 4 over 131 (5952)
# and 4 over 184 (5950), all operand-only. Band 2 runs 5954, 5953, 5952, 5951 (GetCargo), 5950 (ledger/ordinals.tsv),
# and our link gives 5953, 5952, GetCargo and 5950 rising ld_index (names.tsv), so CarregaCandidaturas is defined above
# GetCargo and its first mention of construct_at puts 5952 between them; GetCargos after LimpaFiltros is a choice. The
# roots stand in for 5950's other target caller, 5710 (not written), with one call (CandidaturasRelocadas); 5953's,
# 11884 (unit 104's), is in the link, and its stand-in went. The file reaches Boost through cconfiguracaoeleicao.h now
# (the include path below).
#
# cvisualizarcandidatos.cpp also holds CVisualizarCandidatos::GetPartidos, defined after GetCargos (a choice), and the
# header SetPartido, both for unit 104's 11884, which holds them inlined and matches: GetPartidos is out of line here
# (binaryen inlines it into its one caller; it has no frame), and cvisualizarcandidatos.h says what each rests on.
# GetPartidos has no target function of its own, and this object's other functions compile as before it (compared by
# function, relocated operands masked).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
ELEITOR_ESTADOS_SRCS := src/app/vota/eleitor/cconfirmavotosemcandidato.cpp \
    src/app/vota/eleitor/cinstrucaovotacaoacessibilidade.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp \
    src/app/vota/eleitor/comum/ctelascargo.cpp
UENUX2_SRCS += $(ELEITOR_ESTADOS_SRCS)
# cvisualizarcandidatos.cpp reaches Boost through cconfiguracaoeleicao.h (its GetCargos reads comum::CConfiguracaoEleicao)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing reconstructed calls CVisualizarCandidatos::GetInst, CInstrucaoVotacaoAcessibilidade::GetInst, NomeTela,
# CVisualizarCandidatos::GetCargo or has<api::ITextToSpeech> from all of their target callers yet:
# 150-uenux2-eleitor-estados-roots.cpp stands in for the missing callers
$(ROOT)/$(APP)/150-uenux2-eleitor-estados-roots.o: $(ROOT)/src/units/150-uenux2-eleitor-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/150-uenux2-eleitor-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/150-uenux2-eleitor-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/150-uenux2-eleitor-estados-roots.o
