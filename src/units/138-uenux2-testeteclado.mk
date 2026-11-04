# uenux2 the keyboard-test, zeresima and end-of-voting states over vota::CEstadoComDesligamentoAutomatico, and
# vota::CReinicioVotacao, which one of them goes back to. Classes and target functions (each class's head says what its
# layout and declaration rest on):
#   vota::testeteclado::CBase (testeteclado/cbase.{h,cpp}): StartState 11875; the implicit D2 1559, which
#     CPreZeresima's and CRetomada's slot 0 hold too; the constructor 5948
#   vota::testeteclado::CPreZeresima (testeteclado/cprezeresima.{h,cpp}) and vota::testeteclado::CRetomada
#     (testeteclado/cretomada.{h,cpp}): the out-of-line destructors, whose D0 is one body, 5946; CRetomada's slots 11
#     and 12, GetEstadoPassouNoTeste 11830 and GetEstadoSemTeste 11829, and slot 10, GetTela 11831; CPreZeresima's
#     slots 10 and 11, GetTela 11862 and GetEstadoPassouNoTeste 5945, and its statics' exit destructors 11864 and
#     11863 (its GetInst is inlined into unit 199's 11914)
#   vota::CReinicioVotacao (iniciovotacao/creiniciovotacao.{h,cpp}): GetInst 5938, with its constructor inlined by
#     binaryen; the exit destructors of its static std::mutex and std::unique_ptr, 11836 and 11837; ProcessInput 11834
#   vota::CAplicacaoEncerrada (fimvotacao/caplicacaoencerrada.{h,cpp}): StartState 12058, with
#     vota::CLogVota::LogaVotacaoEncerrada inlined by binaryen; GetInst 3877 and its statics' exit destructors 12060 and
#     12059, the first a thunk of binaryen's 1564, which forms with it (and with which unit 37's 2888 and 12057 match)
#   vota::CVerificaHorarioZeresima (iniciovotacao/cverificahorariozeresima.{h,cpp}): FinishState 11868; GetInst 5947,
#     with its constructor inlined by binaryen, and its statics' exit destructors 11873 and 11872; StartState 11871;
#     ProcessTickNaoDesligamento 11870
#   vota::testeteclado::CEsperaRetestar (testeteclado/cesperaretestar.{h,cpp}): StartState 11825 (below); FinishState
#     11824
#   The D2 785 and D0 1560 of CErroTesteTecladoFim (unit 97) are also CAplicacaoEncerrada's, CEsperaRetestar's and
#   CVerificaHorarioZeresima's: caplicacaoencerrada.cpp.o comes first in the link, so the two match lines name its pair.
# Outside the unit, three members that other units' files gain: api::CDateTime::operator+(time_t) const
# (api/util/cdatetime.{h,cpp}, unit 125), vota::CLogVota::LogaVotacaoEncerrada (app/vota/log/clogvota.{h,cpp}, unit 119)
# and vota::CTelasVota::GetTelaReinicioVotacao (app/vota/eleitor/comum/ctelasvota.h, unit 110). Of the 556 objects the
# link held before them, only cdatetime.cpp.o and clogvota.cpp.o change (cmp of each object against a build of the
# commit this unit starts from).
#
# Evidence, measured in the whole link with pnpm wasm score against names.tsv:
# - 12058 sets up a second stack frame after its call of CLogVota::GetInst (fn 184) and releases it before the form's
#   slot 2: a function binaryen inlined (docs/reference/facts/reading.md R10), with GetInst's result as `this`, as unit
#   119's four Loga members are. Written with loga called in StartState, it scores 22 over 69 rows; with the member in
#   clogvota.cpp, 7 over 61, all operand-only.
# - 11825 copies Now's result into a second 12-byte temporary and passes the low word of a 64-bit value zero-extended
#   from +40 to operator+= (fn 2233): a function with a 64-bit parameter that returns a copy of a CDateTime moved by it,
#   inlined by binaryen. Written as `fim += m_segundosEspera` on a local it scores 30 over 64 rows; as
#   `s_fimEspera = api::CDateTime::Now() + m_segundosEspera` over operator+(time_t) in cdatetime.cpp, 6 over 62, all
#   operand-only. It was `unresolved self-voted` while it was the only reader in the link of the CDateTime at 1835000,
#   which __wasm_call_ctors builds with CDateTime(time_t) of 0; it matches since CEsperaRetestar's slot 9 (fn 11823,
#   below) reads the object too (`evidence:vote:3 by:11823,11825`). Its other target reader is the text callback fn
#   11826, written since (below).
# - CReinicioVotacao follows unit 104's states with a std::shared_ptr (104-uenux2-app-vota-estados.mk has the evidence
#   for GetInst's shape, the statics' order and final); 5938 copies the shared_ptr at +148 of CTelasVota::GetInst(). Its
#   statics are named by 5938's votes; their exit destructors 11836 and 11837 load the same two addresses. GetInst has
#   two target callers, 11829 and 11830, both written here, so it has no stand-in.
# - CPreZeresima's slot 12 (fn 11861) calls slot 11 (fn 5945) directly: final, on the class here (on the member alone
#   it would do the same, a choice).
# - CEsperaRetestar's constructor, GetInst (fn 5936) and statics, written since in cesperaretestar.cpp, unit 104's
#   shape: the base's constructor with 4 (EVENTO_TICK), at +28 the form vota::TelaEsperaRepetirTesteTeclado builds
#   (unit 110's ctelasvota.cpp, inlined by binaryen behind its own stack frame) over a std::function of the text
#   callback, at +36 CThreadEleitor::GetInst().AddStoppedTick(100) (fns 316 and 807) and +40 cleared; the pointer
#   @1835036 and the mutex @1835012, whose exit destructors 11828 and 11827 alone load them besides 5936. +28 is what
#   vota::GetFormulario (fn 886) returns, so the member is a std::shared_ptr<api::IForm<api::IScreen>> now, where the
#   head had CFormInterativoTelaVota: StartState and FinishState call its slot 2 and Hide, IForm's, and 11825 and 11824
#   still match (step 9). The text callback, fn 11826 (483 B, table slot 1862, which 5936 passes), is TextoEspera in
#   the anonymous namespace below s_fimEspera: the seconds from Now to s_fimEspera through api::CDateTime::operator-
#   (fn 5471, unit 125), 0 when that time has passed, given to std::vformat with the text as the format (argument code
#   6, unsigned). Its date is a local scoped to the if: with it a plain local before the if, the frame was 400 bytes and
#   the date at +44, against the target's 384 and +40 (each compiled, try-tu.sh --symbols, the frame read in the object);
#   three more spellings with the plain local gave 400 too. Measured in the whole link (pnpm wasm score against
#   names.tsv): 5936 50 over 791 rows before steps 7 to 9, 11826 10 over 223 with the if form (38 over 223 before it,
#   the frame's offsets), operand-only. 5936 first scored 378 over 794,
#   155 rows deleted: unit 79's roots built CDataTextFmt<std::function<...>> for it with std::make_shared, which kept
#   construct_at out of line, a second caller, where the target inlines it; that stand-in went with 5936's landing.
#   Step 8 named 5936 by vptr-anchor and 11826 by its table vote; 11827 and 11828 matched through the content pass. The
#   std::function's __func members over the pointer (11817, 11819, 11820, 11821, 11822) match from this object. 5936
#   has two target callers, CTesteFalhou's and CEnviarManutencao's ProcessInput (11809, 11812), not written: unit 220's
#   roots stand in for them, and this unit's roots no longer keep CEsperaRetestar's vtable, which GetInst stores.
#   Chosen: GetInst, s_inst, s_mutex, TextoEspera and their names, the locals, the lines, and the callback's internal
#   linkage.
# No other spelling of a written body was compiled.
#
# Not written, with what each waits for:
# - CTesteTeclado's constructor and GetInst are unit 217's;
# - vota::CQuerImprimirBU: StartState 12035 (records :40 and :41), which throws api::EUeAssertError 3474 and 3475, is
#   written and matched since, in unit 156, with the assert codes, the EEstadoVota enumerators and CEstadoGeralVota's
#   getters; its ProcessInput 12034 is written and matched since too, in unit 156;
# - CMostraQRCodeCertificado's StartState (12040; its ProcessInput, 12038, matches since in unit 156, and
#   CMostraQRCodeBU's slots are unit 37's: 12051 matches, 12055 is written): callees with no name (455 has one since
#   unit 237, 576 since unit 165, 502 since unit 220, 653 since unit 120); CTesteTeclado is unit 217's;
# - 138-uenux2-testeteclado-pending.cpp names the slots this unit's vtables trap and what each waits for.
#
# Written since, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv
# before steps 7 to 9 matched it:
# - CBase's constructor (fn 5948), in cbase.cpp: the base's constructor with 2 (EVENTO_ENTRADA), +28 cleared, this
#   class's vptr. It is a function of its own called by fns 11914 and 7160, which hold CPreZeresima's and CRetomada's
#   constructors inlined (each stores its class's vptr after the call), so it is out of line in a TU of its own; its
#   line follows its stub's link-order place, a choice. 2 over 12 rows, operand-only. The roots stand in for its two
#   callers.
# - CAplicacaoEncerrada's constructor, GetInst (fn 3877) and statics, pointer first below GetInst (unit 104's shape):
#   with them our link forms fn 1564, binaryen's body for the exit destructors of every static std::unique_ptr whose
#   class's D2 is fn 785, from three members in our link, eight in the target (CMostraQRCodeBU's,
#   CMostraQRCodeCertificado's and this one's here), and 1564,
#   2888 (unit 37's), 12057, 12059 and 12060 match with 3877. The constructor copies CTelasVota's +36 through
#   ctelasvota.h's GetTelaAplicacaoEncerrada. 3877 scores 11 over 55 rows, operand-only. Its three target callers,
#   12034, 12051 and 12055, are in the link (units 156 and 37), so the roots hold no stand-in for it, and its vtable
#   has no sink: GetInst stores it.
# - CReinicioVotacao::ProcessInput (fn 11834): Read(), then CONFIRMA logs and goes to CDefineRotaPosReinicio, BRANCO
#   logs and goes to CMaisInformacoes with this state; each log a vota::CLogVota member binaryen inlines (GetInst, fn 184,
#   is called before the member's own stack frame opens), added to app/vota/log/clogvota.cpp:
#   LogaMesarioConfirmouReinicioVotacao and LogaMesarioSelecionouOutrasOpcoes, names chosen from their messages. 23 over
#   185 rows, operand-only.
# - CReinicioVotacao::StartState (fn 11835, between the statics and ProcessInput: the band's order is 11837, 11836,
#   11835, 11834): it stores `this` as the next state and calls comum::CRdvVota::GetInst (555) and
#   comum::CJustificador::GetInst (1391) before it tests either, so both are locals. When the vote count
#   (CRdvVota::Comparecimento, 1269) or the count of justified voters (the size of CJustificador's map, +8, through an
#   accessor added to cjustificador.h, its name chosen) is not 0, it logs "Apresentada tela do reinício da votação" (a
#   CLogVota member binaryen inlines, GetInst called before its frame opens: LogaApresentadaTelaReinicioVotacao, added
#   to clogvota.cpp after LogaMesarioSelecionouOutrasOpcoes, its name and place chosen) and shows its form (slot 2 of
#   +12). Else, in the voters' training (comum::CAppInfo::EhTreinamentoEleitor, 697, called), it goes to
#   vota::CQuerReimprimirZeresima (5940) when ze.dat is in the internal flash's work directory and to
#   CQuerImprimirZeresima (5957) when not; that test is behind a stack frame of its own, an out-of-line function
#   binaryen inlines: vota::ExisteArquivoZeresima, a free function added to unit 168's votadefs.cpp (its name and file
#   chosen), whose path is a named local (the target frees both temporaries of the `/` before ExistFile, fn 412). Out
#   of training, it reads the urna's internal number (CEstadoGeral +60, CDadoCorrespondencia's first word) and then
#   GetVota()'s optional urnaIdGerouZeresima (+12, flag +16), and goes to vota::CConfirmaRegerarZeresima when the
#   zerésima was made by another urna, else to CQuerReimprimirZeresima. CConfirmaRegerarZeresima::GetInst is held
#   inlined (unit 176's file has it now, with its constructor and statics). 43 over 311 rows, operand-only; matched,
#   and with it the statics' exit destructors 11840 and 11839. Chosen: the locals', the accessor's and the helper's
#   names.
# - CEsperaRetestar::FinishState (fn 11824): it stops the tick and holds api::IForm<MEDIA>::Hide inlined on its form,
#   which api/gui/iform.h now declares public, a reading (it was protected, for CFormStack; a friend of CEsperaRetestar
#   gives the same bytes). 3 over 40 rows, operand-only.
# - vota::CVerificaHorarioZeresima's GetInst (fn 5947), StartState (fn 11871, record :64) and
#   ProcessTickNaoDesligamento (fn 11870, record :80, slot 9, the name the base's header now has). GetInst is unit
#   104's shape; the constructor passes 6 to the base's and copies CTelasVota's +20 (ctelasvota.h's
#   GetTelaVerificaHorarioZeresima) and comum::CConfiguracaoEleicao's +544 (GetDataHoraZeresima), then adds a stopped
#   2000-ms tick through vota::CThreadVota::AddStoppedTick(const std::chrono::milliseconds&), an overload added out of
#   line to app/vota/cthreadvota.cpp (unit 02's file), which binaryen inlines (cthreadvota.h says what shows it).
#   StartState starts the tick, logs through vota::CLogVota::LogaAguardandoHorarioZeresima (GetInst, fn 184, is called
#   before the member's own stack frame opens; added to app/vota/log/clogvota.cpp, unit 119's file), shows the form
#   and stays while the current time is before +36; else, and in slot 9 for the tick's id once the time has come, it
#   asserts the vote's state with the codes 3481 and 3482 (api/util/eueasserterror.h, names chosen to the records'
#   columns) and goes to vota::CInicioZeresima. The assert texts call GetVota() on `appinfo`, which the target calls
#   const (fn 903), so a const reference. 5947 14 over 86 rows, 11871 23 over 130, 11870 11 over 58, all operand-only.
#   GetInst's other target caller, vota::CGeraDadosDinamicos::StartState (fn 11865, pending in unit 199), has a stand-in
#   in the roots: with 5945 alone binaryen inlined GetInst into it (5945 scored 111 over 169 rows, 83 inserted).
# - CBase::ProcessInput (fn 11874, slot 7 of CBase, CPreZeresima and CRetomada): Read() on the form (record
#   cinteractiveform.h:57, inlined); on INPUT_CORRIGE (5) slot 12's state, and when that is not this state (slot 4,
#   GetNextState, compared with `this`) the log of the string at @137526 through a vota::CLogVota member binaryen
#   inlines (GetInst, fn 184, is called before the member's own stack frame opens), added to app/vota/log/clogvota.cpp:
#   LogaTesteTecladoNaoExecutado, a name chosen from its message; on INPUT_CONFIRMA (9) slot 11's state, called before
#   the first of two calls of vota::testeteclado::CTesteTeclado::GetInst (fn 3855, unit 217), stored at +64 of the
#   object it returns, and that object as the next state. 15 over 148 rows, operand-only.
# - CEsperaRetestar::ProcessTickNaoDesligamento (fn 11823, slot 9): for the tick at +36, once Now() is not before the
#   static the StartState sets (fn 759, its result's sign), CTesteTeclado::GetInst() as the next state. 3 over 33 rows,
#   operand-only.
# - CPreZeresima::GetEstadoPassouNoTeste (fn 5945, record :56) goes to vota::CGeraDadosDinamicos (unit 199) for the
#   vote's first two states and to CVerificaHorarioZeresima for EAVAGUARDAHORAZERESIMA, else logs
#   comum::IEventosLog::LogaErroEstadoAplicativo and throws vota::EUeVotaError 9377 with the state appended to "Estado
#   nao esperado " (app/vota/euevotaerror.h). 23 over 86 rows, operand-only. CPreZeresima's GetInst (unit 104's
#   shape over CBase's constructor and CDateTime(0) on +36) and statics are in cprezeresima.cpp, the GetInst inlined by
#   binaryen into vota::CVerificaEleicaoPassou::StartState (fn 11914, unit 199); the statics' exit destructors 11864
#   and 11863 match with it.
# - CPreZeresima::GetEstadoSemTeste (fn 11861, slot 12) copies the date of comum::CConfiguracaoEleicao's zeresima time
#   (+544, through GetDataHoraZeresima) into a local, as the target does into its frame before api::CDate::operator-(int)
#   (fn 3648), and goes to GetEstadoPassouNoTeste's state when +36's date is before that date less one day
#   (CDate::operator<=>, fn 1261), else stays. GetEstadoPassouNoTeste is called directly (the class is final) with the
#   frame pointer as `this`, the target's row, which the source gives. At the end of cprezeresima.cpp, after
#   GetEstadoPassouNoTeste: its line is a choice; its use band (1) puts it below GetTela (fn 11862, below) and the
#   statics' exit destructors, the order a GetTela written above it keeps. The file includes cconfiguracaoeleicao.h,
#   whose line takes a blank line of the run above GetEstadoPassouNoTeste, so its record stays on line 56. 3 over 35
#   rows (pnpm wasm score before step 8), operand-only: the calls of fns 187, 3648 and 5945. The local's name
#   dataZeresima is chosen; a form without the local (the target copies the date's 8 bytes into its frame) was not
#   compiled.
#
# - CRetomada::GetEstadoPassouNoTeste (fn 11830, slot 11), in cretomada.cpp above GetEstadoSemTeste (the use band,
#   11831 to 11829, gives slots 10, 11 and 12 in that order): the load's urna type (CDadoCarga::GetTipoUrna, +32 of
#   CAppInfo::GetGeral()), then CAppInfo::GetInst() again for GetVota(); when the type is 51 (eUrnaContingenciaVota)
#   and the vote state's byte at +96 (m_tecladoTestadoPosConversao in cestadogeralvota.h's layout) is 0, it stores 1
#   there and calls CSincronizaVota::SincronizaEstadoGeralVota (fn
#   491); it returns CReinicioVotacao::GetInst() (fn 5938). The store goes through a setter added to
#   cestadogeralvota.h, whose name and inline definition are chosen; the local's name tipoUrna is chosen.
#   `pnpm wasm score` against the link: 6 over 35 rows, all operand-only (the calls); matched at step 9, named by its
#   vtable slot.
# - GetTela of CRetomada (fn 11831) and of CPreZeresima (fn 11862), slot 10 of each, written above the class's other
#   slots (the use band: 11831 to 11829, 11862 above 11861). CRetomada's sets m_retomada (+36) when the vote state's
#   urnaIdGerouZeresima (+12, a std::optional) holds the urna's internal number (CDadoCorrespondencia's first word, +60
#   of CAppInfo::GetGeral(), read first), else to the byte at +96 (that order of the two tests is the target's), and
#   returns CTelasVota's test screen that offers not to test (fn 6581) when it is set, else the one that does not (fn
#   6580). CPreZeresima's sets +36 to ISystemDateTime's time through CDateTime::ConvertFromLocalTime (fn 5476, which
#   cdatetime.h makes public for it) and returns fn 6581 when that date is before the zeresima's date less one day
#   (GetEstadoSemTeste's test, fn 11861), else fn 6580. 8 over 43 and 7 over 51 rows, operand-only (pnpm wasm score
#   before step 8); both match, named by their vtable slots. 6580 and 6581 are static members of vota::CTelasVota, which
#   both call through CTelasVota::GetInst() (ctelasvota.h says why). cprezeresima.cpp's two new includes take two blank
#   lines of the run above GetEstadoPassouNoTeste, whose record stays on line 56. Chosen: the ifs' sense (the other was
#   not compiled), the local names numeroInternoUrna and vota.
# Chosen, no evidence names them: in CBase::ProcessInput, the local holding slot 11's state and CTesteTeclado's setter
# (that the target calls slot 11 before GetInst is its rows; that the setter called on GetInst() with slot 11 as its
# argument would call GetInst first, and an assignment to a public member would not, is a reading of C++17's order of
# evaluation, neither compiled), the switch over the two cases with an empty default, and the cases' order; `>=` for
# slot 9's test (another spelling is not measured); the names of CBase's slots 10 and 12 (GetTela, GetEstadoSemTeste),
# of every data
# member, of s_fimEspera, LogaVotacaoEncerrada, GetTelaReinicioVotacao, CReinicioVotacao::GetInst and
# CAplicacaoEncerrada::GetInst, s_inst and s_mutex (unit 104's convention for the states' singletons); CBase's
# constructor's protected access; operator+'s parameter type (time_t: the target shows a 64-bit parameter), that it is a
# member and const, and its line in cdatetime.cpp; s_fimEspera's internal linkage; CRetomada's final; +36 of CRetomada
# as uebyte and +40 of CEsperaRetestar as unsigned int (11829 compares the byte with 1, 11825 zero-extends the word);
# GetTelaReinicioVotacao as an inline getter returning a const reference; the out-of-line destructors declared first as
# key functions, and CBase's StartState as its; the paths of the files no record names, cbase, cretomada,
# cesperaretestar, creiniciovotacao, caplicacaoencerrada and every header, by how-to step 3's rules 2 and 4 from the
# data (CAplicacaoEncerrada's vtable lies between cestadocomdesligamentoautomatico.cpp's record and
# cmostraqrcodebu.cpp's objects, and its GetInst's callers are fimvotacao/'s; CBase's between
# auxiliares/cvisualizarcandidatos.cpp's and cverificahorariozeresima.cpp's; CReinicioVotacao's after
# cquerreimprimirzeresima.cpp's, with three unrecorded classes between); the lines of the functions written in
# cverificahorariozeresima.cpp other than StartState and ProcessTickNaoDesligamento (GetInst, the constructor and the
# statics above them, FinishState and the destructor after), and of cprezeresima.cpp's functions above
# GetEstadoPassouNoTeste; the names GetInst, GetTelaVerificaHorarioZeresima, LogaAguardandoHorarioZeresima, the
# AddStoppedTick overload, the assert codes' and 9377's enumerators, and 5945's local estado; the switch in 5945 with
# its cases indented, which puts the throw at its record's column 19; `Now() >= m_horario` for the tick's test (another
# spelling is not measured).
TESTETECLADO_SRCS := src/app/vota/eleitor/fimvotacao/caplicacaoencerrada.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cbase.cpp \
    src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creiniciovotacao.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cretomada.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.cpp
UENUX2_SRCS += $(TESTETECLADO_SRCS)
# cverificahorariozeresima.cpp and cprezeresima.cpp include app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost
# through CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 88 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the pending traps compile at the tree's flags, as the members will
TESTETECLADO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/138-uenux2-testeteclado-pending.o: $(ROOT)/src/units/138-uenux2-testeteclado-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/138-uenux2-testeteclado.mk $(TESTETECLADO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/138-uenux2-testeteclado-pending.cpp -o $(R)
$(ROOT)/$(APP)/138-uenux2-testeteclado-roots.o: $(ROOT)/src/units/138-uenux2-testeteclado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/138-uenux2-testeteclado.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/138-uenux2-testeteclado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/138-uenux2-testeteclado-pending.o $(APP)/138-uenux2-testeteclado-roots.o
