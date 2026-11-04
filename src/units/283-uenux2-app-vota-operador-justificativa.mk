# uenux2 vota operador: the justification's states in app/vota/operador/justificativa/ that no landed unit compiles.
# vota::CPedeAnoNascimento (cpedeanonascimento.{h,cpp}), the screen vota::IConfirmaJustificativa::ProcessInput (fn
# 10588, unit 174) goes to when the identifier typed is no CPF, and its two answers, vota::CEleitorMenor16Anos and
# vota::CAnoInformadoInvalido (celeitormenor16anos.{h,cpp}, canoinformadoinvalido.{h,cpp});
# vota::CEleitorImpedidoJustificarVotoCPF (celeitorimpedidojustificarvotocpf.{h,cpp}), which unit 174 lists (its
# fragment has why); and the Temporario and
# Transito pairs of unit 243's two classes that vota::CEleitorEncontrado::StartState (fn 10635, unit 104) goes to:
# CConfirmaJustificativaTemporario, CIniciaJustificativaTemporario, CConfirmaJustificativaTransito and
# CIniciaJustificativaTransito, a file each. Paths relative to src/uenux2. Target fns matched:
# - CPedeAnoNascimento::GetInst (5418), with the constructor inlined behind a stack frame of its own (its form:
#   GetTextoIdentidadeDigitada at {1, 1}, "Digite o ANO de nascimento: ", a four-digit numeric field through
#   outrasopcoes/cescolheopcao.h's AdicionaCampoNumerico at {29, 2}, "CORRIGE: cancelar" and "CONFIRMA: justificar"),
#   and its statics' exit destructors (10592, 10591); its callers are 10588 and 6014;
# - CEleitorMenor16Anos::ProcessInput (10598) and CAnoInformadoInvalido::ProcessInput (10601), thunks into 6014, the
#   body binaryen merges from the two, which our link forms the same way (matched under
#   byn$mgfn-shared$_ZN4vota21CAnoInformadoInvalido12ProcessInputEv): on CONFIRMA, back to CPedeAnoNascimento;
# - CEleitorImpedidoJustificarVotoCPF's statics' exit destructors (10606, 10605: unit 174's object) and its ProcessInput
#   (10604, slot 7, in celeitorimpedidojustificarvotocpf.cpp after StartState): `f2295(p0, 5, <its Read() record>)`, a
#   thunk into the body binaryen merges from five states' slot 7, written as its siblings are,
#   `if (m_form->Read() == api::INPUT_CORRIGE) m_pNextState = &CPedeIdentidade::GetInst();`
#   (src/units/161-uenux2-app-vota-operador-identidade.mk has 2295's family); the census pairs 10604 with it, and the
#   scan matches it under its own name;
# - the four pair classes' statics' exit destructors (10615 and 10614, 10613 and 10612, 10611 and 10610, 10609 and
#   10608) and 3885, binaryen's body of the three Confirma pointers' destructors (10615, 10611 and unit 243's 10622, a
#   thunk into it, which matches with them).
# - CPedeAnoNascimento::ProcessInput (10590, slot 7, in cpedeanonascimento.cpp after StartState), which holds
#   CAnoInformadoInvalido's and CEleitorMenor16Anos's GetInst with their constructors (binaryen inlined each into its
#   one caller), and their statics' exit destructors (10603 and 10602, 10600 and 10599), whose objects' names come from
#   10590's votes; the notes below.
# No member is pending: the -pending.cpp went with 10590's trap.
#
# vota::CPedeAnoNascimento::ProcessInput (10590). Evidence, the target's body (pnpm wasm fn):
# - Read()'s result, less 5, goes through a br_table: 9 (api::INPUT_CONFIRMA) reads the year, 5 (INPUT_CORRIGE) logs
#   "Mesário cancelou entrada dos dados" (severity 1) and goes to CPedeIdentidade (652), any other stays: a switch.
# - CONFIRMA copies the text of the form's first entry (the vector at +72, at(0): its out_of_range throw is 234) into a
#   std::string of the function's own 16-byte frame and acts only on 4 characters or more (i32.ge_u 4): it assigns it to
#   CThreadOperador's string at +84 (the self-assignment test, fns 196 and 205), converts it with
#   ecourna::api::util::CStringUtils::ToInt16 (3508) and subtracts it from CConfiguracaoEleicao's (187) 16-bit year at
#   +48. The year is compared signed (i32.ge_s 1900; ueint16 is std::int16_t in uetypes.hpp), the age as a signed
#   16-bit value (extend16_s, then > 0) and then unsigned against 15, which is clang's `< 16` once the age is known
#   positive (a reading).
# - Three outcomes, each a CLogVota member in a 16-byte frame of its own after GetInst (184), then the next state:
#   below 1900 or not positive, "Ano de nascimento inválido" and CAnoInformadoInvalido; under 16, "Eleitor não tem
#   idade mínima" and CEleitorMenor16Anos; else the justification and CJustificativaEfetuada::GetInst (2747, called).
#   One store of m_pNextState (+4) follows the three.
# - The justification, functions binaryen inlined into their one caller, each in a frame of its own:
#   - vota::JustificaEleitor (16 B, iiniciajustificativa.cpp, unit 152): CJustificador::GetInst (1391), then
#     GetIdentidadeEleitor (1535), whose result's string the target frees before it builds the key from it, so the
#     source binds a const reference to the temporary's member, as written (the target reads freed memory there); the
#     year is narrowed to Justifica's ueword (& 65535) after that call, inside this frame, so the parameter is the
#     caller's ueint16; then the count at +54 of CAppInfo::GetVota() (261) incremented, SincronizaJustificativa, and
#     SetRecebida(true) on 2747's result.
#   - CJustificador::Justifica(const std::string&, ueword) (32 B, the key built and destroyed) and
#     Justifica(const CNumeroInscricaoEleitoral&, ueword) (48 B, record cjustificador.cpp:55): Find, which stores the
#     cursor when the título is there, then the throw 8800; else Add(key, CJustificadorDetalhe(ano)): the detail at
#     +6, the pair built in place with 3743, and 5725.
#   - CSincronizaVota::SincronizaJustificativa (176 B): VerificaUrnaDesligando inlined (the byte at 1832936, 1685), two
#     contexts (676, kinds 2 and 4), SalvaVotaInterno (3790), SaveCurrentInternal, the signing of file 31 (1501, 1277,
#     1007: csincronizavota.cpp's AssinaArquivo, clang-inlined), Sync (600, 620), GravaBancoDadosMI (4657),
#     SalvaVotaExterno (3789), SincronizaAssinaturaVota (4687), Sync.
#   - CJustificador::SaveCurrentInternal (80 B, record cjustificador.cpp:83): the map's size (+8), the cursor's node
#     read once (a reference to *m_corrente; through m_corrente twice the body reloads +12 after the key's string
#     copy), make_shared<CNumeroInscricaoEleitoral> of the key into a CRegistroIdentificacaoEleitor (1675), the
#     CIdentificacaoJustificativa (1875) with TAno (2277) of the detail's year, then the servico's Salva.
#   - comum::servico::CJustificadorServico::Salva (32 B): GetIdentificadorHabilitacao (2669) and GetNumero (1139) come
#     before the DAO pointer is read, and the DAO's slot 7 result dies before the test that guards slot 3: Existe,
#     taking the número and clang-inlined, is a reading of that order.
# Measured (pnpm wasm score against 10590 on the whole link, after make -C src link-map):
# - Salva and Existe defined in cjustificador.cpp above SaveCurrentInternal: 199 over 1839 rows, all operand-only. In
#   cjustificadorservico.cpp, their class's file: 231 over 1845 (6 inserted, 6 deleted), the locals of the vector
#   teardown inside both inlined constructors swapped. Replays of the link's own wasm-opt -Oz
#   (docs/reference/facts/codegen.md C4) give the target's locals there in three orders that put Salva ahead of
#   SaveCurrentInternal on the module, and not in that link's order: the place is measured, and binaryen's inlining
#   order as its cause is a reading.
# - Measured at that 231 state, each a scratch link with variant objects (workflow.md W13): JustificaEleitor's object
#   (iiniciajustificativa.cpp.o) after cpedeanonascimento.cpp.o, 560 over 1863; CAnoInformadoInvalido's and
#   CEleitorMenor16Anos's GetInst inline in their class, 646 over 1858; CThreadOperador's setter out of line in
#   cthreadoperador.cpp, 240 over 1849; the next state in a local stored once, 238 over 1849. The same wasm at that
#   state: GetInst defined above the constructor in canoinformadoinvalido.cpp and celeitormenor16anos.cpp.
# Chosen: the three CLogVota members' names (from their messages) and place; the inline
#   CThreadOperador::SetAnoNascimentoDigitado and CEstadoGeralVota::IncrementaQtdJustificativa and their names;
#   JustificaEleitor's name, its being a free function and its file; the overload of Justifica over std::string (a
#   function of its own, a reading of its frame), its name and signature; the names SincronizaJustificativa, Salva and
#   Existe; the 8800 and 8801 enumerators' names; the switch's form; ueint16, ToInt16's type, for the year and the age
#   (their signedness is the evidence above, the spelling a choice); every local's name.
# 5725 differs (unit 113's fragment: a flag of cjustificador.cpp's), and its name, which 10590's call needs, rests on a
# callers+content hand line in splat/symbol_addrs.txt, whose comment gives its evidence.
#
# Evidence, each class's header says the rest (RTTI, vtable, statics, the function that holds GetInst inlined):
# - The pairs' constructors pass IConfirmaJustificativa's (3625) the literals 10635 loads, "está impedido de votar nesta
#   seção" and "optou por votar EM TRÂNSITO" (strings 122762 and 326637), and the Inicia classes hand
#   IIniciaJustificativa's (3624) their Confirma's GetInst(), as unit 243's CIniciaJustificativa does; 10635 holds each
#   pair's GetInst and constructors inlined (binaryen: one caller each), Inicia's around Confirma's. The Confirma
#   classes' destructor is out of line (slot 0 is 3626, the D2 the three share; slot 1 2748), the Inicia classes' left
#   implicit (174 and 144), as unit 243's two; GetInst above the constructor, as there. Their vtables alternate with
#   unit 243's in the data (@1589252 to @1589532), and in use band 1 their exit destructors (10615 down to 10608) link
#   after unit 243's (10622 to 10616), this unit's order.
# - The year-of-birth states: CPedeAnoNascimento's slots 0 and 1 are 244 and 387 (a std::shared_ptr at +12),
#   StartState (1718) shows the form and stays; CEleitorMenor16Anos's and CAnoInformadoInvalido's ProcessInput differ
#   only in their TU's record of api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (cinteractiveform.h:57),
#   the merge's parameter. The two answers' texts are read from 10590's body, CPedeAnoNascimento's from 5418's.
# Chosen: the eight new files' names (after the classes, how-to step 3's rule 4) and their directory (the vtables' data
#   neighbours are unit 243's and unit 142's justificativa/ classes'), the forms' helper names, the lines, and every
#   member and local name.
#
# Roots (283-uenux2-app-vota-operador-justificativa-roots.cpp): a stand-in for fn 7787 (not written), the second target
# caller of std::set<ecourna::app::dados::ETipoIdentificadorEleitor>'s range insert (6733), which 10635 calls: with
# 10635 as its one caller, binaryen inlined it there and 10635 differed by that body. Unit 104's fragment has the rest
# of 6733, which matches from celeitorencontrado.cpp.o, built without strict aliasing (src/Makefile's
# UENUX2_NOTBAA_FILES).
APP_VOTA_OPERADOR_JUSTIFICATIVA_SRCS := src/app/vota/operador/justificativa/canoinformadoinvalido.cpp \
    src/app/vota/operador/justificativa/cconfirmajustificativatemporario.cpp \
    src/app/vota/operador/justificativa/cconfirmajustificativatransito.cpp \
    src/app/vota/operador/justificativa/celeitormenor16anos.cpp \
    src/app/vota/operador/justificativa/ciniciajustificativatemporario.cpp \
    src/app/vota/operador/justificativa/ciniciajustificativatransito.cpp \
    src/app/vota/operador/justificativa/cpedeanonascimento.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_JUSTIFICATIVA_SRCS)
$(ROOT)/$(APP)/283-uenux2-app-vota-operador-justificativa-roots.o: $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/283-uenux2-app-vota-operador-justificativa-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/283-uenux2-app-vota-operador-justificativa-roots.o
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/justificativa/cpedeanonascimento.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
