# uenux2 the keyboard-test, zeresima and end-of-voting states over vota::CEstadoComDesligamentoAutomatico, and
# vota::CReinicioVotacao, which one of them goes back to. Classes and target functions (each class's head says what its
# layout and declaration rest on):
#   vota::testeteclado::CBase (testeteclado/cbase.{h,cpp}): StartState 11875; the implicit D2 1559, which
#     CPreZeresima's and CRetomada's slot 0 hold too; the constructor 5948
#   vota::testeteclado::CPreZeresima (testeteclado/cprezeresima.{h,cpp}) and vota::testeteclado::CRetomada
#     (testeteclado/cretomada.{h,cpp}): the out-of-line destructors, whose D0 is one body, 5946; CRetomada's slot 12,
#     GetEstadoSemTeste 11829
#   vota::CReinicioVotacao (iniciovotacao/creiniciovotacao.{h,cpp}): GetInst 5938, with its constructor inlined by
#     binaryen; the exit destructors of its static std::mutex and std::unique_ptr, 11836 and 11837; ProcessInput 11834
#   vota::CAplicacaoEncerrada (fimvotacao/caplicacaoencerrada.{h,cpp}): StartState 12058, with
#     vota::CLogVota::LogaVotacaoEncerrada inlined by binaryen; GetInst 3877 and its statics' exit destructors 12060 and
#     12059, the first a thunk of binaryen's 1564, which forms with it (and with which unit 37's 2888 and 12057 match)
#   vota::CVerificaHorarioZeresima (iniciovotacao/cverificahorariozeresima.{h,cpp}): FinishState 11868
#   vota::testeteclado::CEsperaRetestar (testeteclado/cesperaretestar.{h,cpp}): StartState 11825, written and
#     `unresolved self-voted` (below); FinishState 11824
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
#   operand-only. It stays `unresolved self-voted`: the CDateTime at 1835000, which __wasm_call_ctors builds with
#   CDateTime(time_t) of 0, has 11825 as its only reader in the link. Its other target readers are CEsperaRetestar's
#   slot 9 (fn 11823, which calls CTesteTeclado::GetInst, fn 3855, over the base's constructor) and the text callback fn
#   11826 (which calls fn 5471, with no name); either one in the link gives the object a second voter.
# - CReinicioVotacao follows unit 104's states with a std::shared_ptr (104-uenux2-app-vota-estados.mk has the evidence
#   for GetInst's shape, the statics' order and final); 5938 copies the shared_ptr at +148 of CTelasVota::GetInst(). Its
#   statics are named by 5938's votes; their exit destructors 11836 and 11837 load the same two addresses. GetInst has
#   two target callers, 11829 and 11830 (pending); the roots stand in for 11830.
# - CPreZeresima's slot 12 (fn 11861) calls slot 11 (fn 5945) directly: final, on the class here (on the member alone
#   it would do the same, a choice).
# No other spelling of a written body was compiled.
#
# Not written, with what each waits for:
# - the other constructors over CEstadoComDesligamentoAutomatico, and so their GetInst: CVerificaHorarioZeresima's 5947
#   (its constructor copies vota::CTelasVota::GetInst()'s +20, which app/vota/eleitor/comum/ctelasvota.h has no accessor
#   for), CTesteTeclado's 3855 and CEsperaRetestar's 5936 (not read for this unit);
# - CVerificaHorarioZeresima's slot 9 (fn 11870, record :80) and CEsperaRetestar's (fn 11823): the base's header names
#   slot 9 ProcessTickNaoDesligamento, the record's name, and neither class overrides it here, so the base's empty
#   body, fn 425, fills both slots and their stubs go. 11870 and StartState (11871) throw through the assert macro
#   with the condition `appinfo.GetVota().GetEstadoVota() == EAVAGUARDAHORAZERESIMA` (ledger/strings.tsv 400939) and
#   the codes 3482 and 3481, so they wait for the two codes in api/util/eueasserterror.h (the EEstadoVota enumerator,
#   51, is in app/comum/dados/md/estadoaplicacao/cestadogeralvota.h now); 11823 calls fn 3855;
# - vota::CQuerImprimirBU: StartState 12035 (records :40 and :41), which throws api::EUeAssertError 3474 and 3475, is
#   written and matched since, in unit 156, with the assert codes, the EEstadoVota enumerators and CEstadoGeralVota's
#   getters; its ProcessInput 12034 calls fns 455, 491, 3877 and 5986;
# - CMostraQRCodeBU's and CMostraQRCodeCertificado's slots (12055, 12051, 12040; 12038, ProcessInput, matches since in
#   unit 156), CTesteTeclado's (2868, 11806, 11805, 11804): callees with no name, 455, 1285, 2023 and 502 among them
#   (576 has one since unit 165);
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
#   ctelasvota.h's GetTelaAplicacaoEncerrada. 3877 scores 11 over 55 rows, operand-only. The roots stand in for its
#   three target callers (12034, 12051, 12055), and its vtable has no sink: GetInst stores it.
# - CReinicioVotacao::ProcessInput (fn 11834): Read(), then CONFIRMA logs and goes to CDefineRotaPosReinicio, BRANCO
#   logs and goes to CMaisInformacoes with this state; each log a vota::CLogVota member binaryen inlines (GetInst, fn 184,
#   is called before the member's own stack frame opens), added to app/vota/log/clogvota.cpp:
#   LogaMesarioConfirmouReinicioVotacao and LogaMesarioSelecionouOutrasOpcoes, names chosen from their messages. 23 over
#   185 rows, operand-only.
# - CEsperaRetestar::FinishState (fn 11824): it stops the tick and holds api::IForm<MEDIA>::Hide inlined on its form,
#   which api/gui/iform.h now declares public, a reading (it was protected, for CFormStack; a friend of CEsperaRetestar
#   gives the same bytes). 3 over 40 rows, operand-only.
#
# Chosen, no evidence names them: the names of CBase's slots 10 and 12 (GetTela, GetEstadoSemTeste), of every data
# member, of s_fimEspera, LogaVotacaoEncerrada, GetTelaReinicioVotacao, CReinicioVotacao::GetInst and
# CAplicacaoEncerrada::GetInst, s_inst and s_mutex (unit 104's convention for the states' singletons); CBase's
# constructor's protected access; operator+'s parameter type (time_t: the target shows a 64-bit parameter),
# that it is a member and const, and its line in cdatetime.cpp; s_fimEspera's internal linkage; CRetomada's final; +36 of CRetomada as uebyte and +40 of
# CEsperaRetestar as unsigned int (11829 compares the byte with 1, 11825 zero-extends the word); GetTelaReinicioVotacao
# as an inline getter returning a const reference; the out-of-line destructors declared first as key functions, and
# CBase's StartState as its; the paths of the files no record names, cbase, cretomada, cesperaretestar, creiniciovotacao,
# caplicacaoencerrada and every header, by how-to step 3's rules 2 and 4 from the data (CAplicacaoEncerrada's vtable lies
# between cestadocomdesligamentoautomatico.cpp's record and cmostraqrcodebu.cpp's objects, and its GetInst's callers
# are fimvotacao/'s; CBase's between auxiliares/cvisualizarcandidatos.cpp's and cverificahorariozeresima.cpp's;
# CReinicioVotacao's after cquerreimprimirzeresima.cpp's, with three unrecorded classes between); the lines of the
# functions written in cverificahorariozeresima.cpp, after its records' lines 64 and 80, which stay blank, and of
# CPreZeresima's destructor in cprezeresima.cpp, ahead of its record's line 56 (GetEstadoPassouNoTeste, pending).
TESTETECLADO_SRCS := src/app/vota/eleitor/fimvotacao/caplicacaoencerrada.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cbase.cpp \
    src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creiniciovotacao.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cretomada.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.cpp
UENUX2_SRCS += $(TESTETECLADO_SRCS)
# the pending traps compile at the tree's flags, as the members will
TESTETECLADO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/138-uenux2-testeteclado-pending.o: $(ROOT)/src/units/138-uenux2-testeteclado-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/138-uenux2-testeteclado.mk $(TESTETECLADO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/138-uenux2-testeteclado-pending.cpp -o $(R)
$(ROOT)/$(APP)/138-uenux2-testeteclado-roots.o: $(ROOT)/src/units/138-uenux2-testeteclado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/138-uenux2-testeteclado.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/138-uenux2-testeteclado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/138-uenux2-testeteclado-pending.o $(APP)/138-uenux2-testeteclado-roots.o
