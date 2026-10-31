# uenux2 the keyboard-test, zeresima and end-of-voting states over vota::CEstadoComDesligamentoAutomatico, and
# vota::CReinicioVotacao, which one of them goes back to. Classes and target functions (each class's head says what its
# layout and declaration rest on):
#   vota::testeteclado::CBase (testeteclado/cbase.{h,cpp}): StartState 11875; the implicit D2 1559, which
#     CPreZeresima's and CRetomada's slot 0 hold too
#   vota::testeteclado::CPreZeresima (testeteclado/cprezeresima.{h,cpp}) and vota::testeteclado::CRetomada
#     (testeteclado/cretomada.{h,cpp}): the out-of-line destructors, whose D0 is one body, 5946; CRetomada's slot 12,
#     GetEstadoSemTeste 11829
#   vota::CReinicioVotacao (iniciovotacao/creiniciovotacao.{h,cpp}): GetInst 5938, with its constructor inlined by
#     binaryen; the exit destructors of its static std::mutex and std::unique_ptr, 11836 and 11837
#   vota::CAplicacaoEncerrada (fimvotacao/caplicacaoencerrada.{h,cpp}): StartState 12058, with
#     vota::CLogVota::LogaVotacaoEncerrada inlined by binaryen
#   vota::CVerificaHorarioZeresima (iniciovotacao/cverificahorariozeresima.{h,cpp}): FinishState 11868
#   vota::testeteclado::CEsperaRetestar (testeteclado/cesperaretestar.{h,cpp}): StartState 11825, written and
#     `unresolved self-voted` (below)
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
# - every constructor of a class over CEstadoComDesligamentoAutomatico, and so their GetInst (CBase's 5948;
#   CAplicacaoEncerrada's 3877, CMostraQRCodeBU's 2888, CVerificaHorarioZeresima's 5947, CTesteTeclado's 3855,
#   CEsperaRetestar's 5936) and the exit destructors of their statics (the 1564 group): the base's constructor (fn 1285)
#   is not declared in this tree;
# - CVerificaHorarioZeresima's slot 9 (fn 11870, record :80) and CEsperaRetestar's (fn 11823): the base's header names
#   slot 9 ProcessOutroTick, a chosen name, where the record names it ProcessTickNaoDesligamento; so the base's empty
#   body, fn 425, fills both slots here and their stubs go. 11870 also throws through the assert macro (next item),
#   11823 calls fn 3855;
# - vota::CQuerImprimirBU (fimvotacao/cquerimprimirbu.cpp, a stub file): StartState 12035 (records :40 and :41) throws
#   api::EUeAssertError 3474 and 3475 with "Assert (poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU)" and
#   "Assert (poInfo.GetVota().GetQtdBU() == 0)", as CVerificaHorarioZeresima's StartState (pending) throws 3481: they
#   need the assert macro's header, the EEstadoVota enumerators and CEstadoGeralVota's GetEstadoVota and GetQtdBU, none
#   in this tree; its ProcessInput 12034 calls fns 455, 491, 3877 and 5986;
# - CMostraQRCodeBU's and CMostraQRCodeCertificado's slots (12055, 12051, 12040, 12038), CTesteTeclado's (2868, 11806,
#   11805, 11804): callees with no name, 455, 1285, 2023, 502 and 576 among them;
# - 138-uenux2-testeteclado-pending.cpp names the slots this unit's vtables trap and what each waits for.
#
# Chosen, no evidence names them: the names of CBase's slots 10 and 12 (GetTela, GetEstadoSemTeste), of every data
# member, of s_fimEspera, LogaVotacaoEncerrada and GetTelaReinicioVotacao; operator+'s parameter type (time_t: the target
# shows a 64-bit parameter); s_fimEspera's internal linkage; CRetomada's final; +36 of CRetomada as uebyte and +40 of
# CEsperaRetestar as unsigned int (11829 compares the byte with 1, 11825 zero-extends the word); GetTelaReinicioVotacao
# as an inline getter returning a const reference; the out-of-line destructors declared first as key functions, and
# CBase's StartState as its; the paths of the files no record names, cbase, cretomada, cesperaretestar, creiniciovotacao,
# caplicacaoencerrada and every header, by how-to step 3's rules 2 and 4 from the data (CAplicacaoEncerrada's vtable lies
# between cestadocomdesligamentoautomatico.cpp's record and cmostraqrcodebu.cpp's objects, and its GetInst's callers
# are fimvotacao/'s; CBase's between auxiliares/cvisualizarcandidatos.cpp's and cverificahorariozeresima.cpp's;
# CReinicioVotacao's after cquerreimprimirzeresima.cpp's, with three unrecorded classes between); the lines of the
# functions written in cverificahorariozeresima.cpp, after its records' lines 64 and 80, which stay blank.
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
