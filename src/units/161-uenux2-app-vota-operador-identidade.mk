# uenux2 vota operador identity and biometry states, in app/vota/operador/leidentidade/ and confirmaidentidade/, and the
# vota::CLogVota members they log through. Target fns matched:
# - vota::CControlaReconhecimento's static members (confirmaidentidade/ccontrolareconhecimento.cpp, the records' file):
#   AvancaTentativa 5406 (record line 167), AtingiuLimiteTentativas 5405, AtingiuLimiteVerificacoes 5404 and
#   PrimeiraTentativa 5403;
# - the StartState of vota::CEleitorJaVotou (10642), CIdentidadeInvalida (10669), CVerificaDadoEleitor (10444) and
#   CDadoEleitorNaoConfere (10448); the ProcessInput of CEleitorJaVotou (10641) and CInformaAnoNascimentoErrado (10493),
#   thunks into binaryen's 6015, which our link forms from the two of them as the target does (matched under
#   byn$mgfn-shared$_ZN4vota15CEleitorJaVotou12ProcessInputEv); vota::CPedeIdentidade::FinishState (10678);
# - vota::CEleitorNaoEncontrado's slot 9 (10663) and its destructors (1907, 1689), over its new base
#   vota::IEleitorImpedidoVotar;
# - two CLogVota members out of line in app/vota/log/clogvota.cpp, unit 119's file: 2097 and 4522; three more there have
#   no target index of their own (10642, 10669 and 10444 hold them inlined);
# - libc++'s std::stoul (4661), which a stand-in brings from libc++.a, and with it 4659 and 4660, 6118 (binaryen's body
#   of those two) and 7731 (as_integer_helper, `unresolved` before; its hand line went, since a generated `pair-addr`
#   line names it now).
# The classes' destructors are bodies the link matched before, under other classes' symbols, and stay so (step 9 renamed
# no line): 244 and 387 (CControlaReconhecimento, CEleitorJaVotou, CInformaAnoNascimentoErrado, CIdentidadeInvalida,
# CVerificaDadoEleitor), 448 and 765 (CDadoEleitorNaoConfere), 1537 and 3629 (CPedeIdentidade);
# CInformaAnoNascimentoErrado's StartState is 1070, matched before.
#
# Evidence, each class's header says the rest (its RTTI, vtable, layout and the function that holds its inlined
# constructor):
# - The log members: 10642, 10669 and 10444 call vota::CLogVota::GetInst (fn 184, `call 184` at +0x3) and then open a
#   stack frame of their own (docs/reference/facts/reading.md R10) that builds the message and calls
#   comum::IEventosLog::logaAlerta (fn 1398), api::CLoga::loga (fn 433, +4 and severity 2) or IEventosLog::loga (fn
#   233), the shape of unit 142's three members; 2097 and 4522 are `f233(p0, <literal>)`, called as `f2097(f184())` by
#   the slots of five states and `f4522(f184())` by two slots of CRegistraDigitalOperador. 10663 calls GetInst inside
#   its own frame (`call 184` at +0xc, after the prologue), as unit 119's 10783 does: the call is written in the slot.
# - CControlaReconhecimento: AvancaTentativa's record names it static and its line; it throws EUeVotaError 9397 with
#   "Limite de tentativas atingido." (column 15). The other three have no record: they are out of line, called from
#   other classes' slots (ledger/callgraph.tsv: 5405 and 5406 by 10473 and 10485, 5404 by 10447 and 10448, 5403 twice by
#   10465), so external functions; that they are static members like AvancaTentativa is a choice. The statics: the
#   target's .data holds 1 at 0x18468c, 0x184690 and 0x184694, which StartState (10512) sets to 1 again, and its .bss a
#   byte at 0x1d1fbc that StartState and AvancaTentativa set to 0 and that AvancaProximoDedo1x4, inlined into 10465
#   under record 187, increments while it is not 4 (else it throws 9399); 10465 and 10425 index the word table at
#   0x1846a0 (1, 6, 2, 7, 3, 4, 5, 8, 9, 10) with it: the index of the finger being captured, an unsigned byte
#   (i32.load8_u, i32.store8), not a flag (10465 at +0xe62, +0xe90 and +0x104e, 10425 at +0x209). The limits are
#   CConfiguracaoEleicao's bytes at +136 and +140 (its CParametrosUrna at +88, numTentativasHabilitacao at +48 and
#   numTentativasVerificacao at +52), read with i32.load8_u: a uedword in the helper instead of the uebyte gives
#   `i32.load 2 136` in the object (wasm-objdump -d), so a uebyte holds the limit.
# - AvancaTentativa's form, measured with `pnpm wasm score` against the plain link: the counter read into a local before
#   CConfiguracaoEleicao::GetInst and the throw under `if (==)`, `39 over 59 rows (same 20, replaced 4 [2 operand-only],
#   inserted 17, deleted 18)`; the same local with the increment under `if (!=)` and the throw in the `else`, `15 over
#   44 rows (same 29, replaced 11 [10 operand-only], inserted 2, deleted 2)`, since the target calls GetInst before it
#   reads the counter; as written, `12 over 42 rows (same 30, replaced 12 [12 operand-only], inserted 0, deleted 0)`. So
#   the block order (the increment first, the throw last) and the order of the call and the read are evidence; that the
#   test is AtingiuLimiteTentativas inlined, which reads in that order, is a reading, and the column (15) puts the throw
#   one level in.
# - CEleitorNaoEncontrado: its destructor is out of line. With the implicit one, its deleting destructor frees what the
#   D2 returns, `4 over 7 rows (same 3, replaced 2 [1 operand-only], inserted 0, deleted 2)` against 1689; defaulted in
#   its .cpp, 1689 and 1907 score operand rows only and match (docs/reference/facts/reading.md R5).
# - The .bss byte's name: splat/symbol_addrs.txt's hand line cites StartState (10512), which clears it, 10465, which
#   reads it and increments it, and 10425, which reads it; its generated line is AvancaTentativa's own vote, so without
#   the hand line 5406 is `unresolved self-voted`.
#
# IEleitorImpedidoVotar's destructor (1257): the target's is a thunk into binaryen's fn 2902 with the class's vptr, a
# body the target forms from four thunks (1257, 1688, 1720 and 1952). It matches with unit 169's 1720 and 1952 in the
# link: binaryen then merges the three into one body, which unit 169 matches as 2902, and ours is the same thunk
# (`f3388(p0, 1391348)` on that link). Alone, ours was a whole body and `differs`. 1688 is no class's here. 1907 and
# 1689 call it and match through its `vtable` name.
#
# Not reconstructed: every class's GetInst and constructor (each header names the function that holds them inlined);
# CControlaReconhecimento::AvancaVerificacao and AvancaProximoDedo1x4 (records 176 and 187, held inlined by 10447 and
# 10465, which are pending or not written), whose lines stay blank; the slots the -pending.cpp traps, with what each
# waits for. Rows of these classes left for later: 10512 and 10511 (CControlaReconhecimento), 10667, 10443, 10447,
# 10680, 10677, 10676, 10625 and 10624 (pending).
#
# Chosen, no evidence names them: the names of the three helpers, of the statics and of every data member, and their
# types where only a width shows (int for the 32-bit counters), and uebyte as the spelling of the byte's unsigned 8-bit
# type, which the target gives: the reads that index the table load it with i32.load8_u before the shift (10465 at
# +0xe90, 10425 at +0x209), where a signed char gives i32.load8_s, and 10465's increment and its bound of 4 make it a
# counter, not a flag; the CLogVota members' names (from their messages) and their
# place, after GetInst; IEleitorImpedidoVotar's slot 9 name (LogaImpedimento, from the one override, which logs) and its
# +20 int; CPedeIdentidade's +16 pointee (the voter's form, as comum::CPedeDigitalMesario's header chooses); GetInst and
# the private constructors, declared and not defined; the destructors declared first. The lines: AvancaTentativa's throw
# is on its record's line, the statics and the destructor above it and the helpers after line 187 are a choice, and so
# is FinishState after StartState's two record lines. Same bytes: CDadoEleitorNaoConfere's StartState as written and
# with a conditional operator choosing the form (its object's function, wasm-objdump -d). The paths: cpedeidentidade.cpp
# and ccontrolareconhecimento.cpp are the records'; every other class is in a file named after it (how-to step 3, rule
# 4), its header beside it, in the directory its vtable's neighbours give (docs/reference/facts/placing.md P5):
# CIdentidadeInvalida (@1588376), CEleitorNaoEncontrado (@1588448) and CEleitorJaVotou (@1588804) lie between
# cpedeidentidade.cpp's records (@1588276) and celeitorencontrado.cpp's (@1588980); IEleitorImpedidoVotar (@1589136) has
# celeitorencontrado.cpp's record before it and justificativa/iconfirmajustificativa.cpp's (@1589992) after it, with
# unrecorded vtables between on both sides, and goes beside the six classes derived from it, a choice;
# CInformaAnoNascimentoErrado (@1591424) lies between cnomeeleitor.cpp's records (@1591336) and
# cdigitalreconhecida.cpp's (@1591684); CDadoEleitorNaoConfere (@1592640) and CVerificaDadoEleitor (@1592712) after
# cregistradigitaloperador.cpp's records (@1592596) with no vtable between, and unrecorded vtables between them and
# aguardaeleitor/cmostraeleitorvotando.cpp's records (@1593044): the adjacent side. The order of the sources below
# follows the data, leidentidade's before confirmaidentidade's.
#
# Roots: the eight classes' vtables, and stand-ins for the target callers of 5403 to 5406, 2097, 4522 and 4661 (the
# roots file names them). ccontrolareconhecimento.cpp reaches Boost through cconfiguracaoeleicao.h, so its object takes
# the include path below, as unit 88's do.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_OPERADOR_IDENTIDADE_SRCS := src/app/vota/operador/leidentidade/cpedeidentidade.cpp \
    src/app/vota/operador/leidentidade/cidentidadeinvalida.cpp \
    src/app/vota/operador/leidentidade/celeitorjavotou.cpp \
    src/app/vota/operador/leidentidade/celeitornaoencontrado.cpp \
    src/app/vota/operador/leidentidade/ieleitorimpedidovotar.cpp \
    src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.cpp \
    src/app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.cpp \
    src/app/vota/operador/confirmaidentidade/cverificadadoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_IDENTIDADE_SRCS)
# ccontrolareconhecimento.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 161-uenux2-app-vota-operador-identidade-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/161-uenux2-app-vota-operador-identidade-pending.o: $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/leidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/161-uenux2-app-vota-operador-identidade-pending.cpp -o $(R)
# nothing reconstructed references the eight classes or calls the members the roots stand for: the roots file
# (161-uenux2-app-vota-operador-identidade-roots.cpp) takes the vtables' addresses and gives those members call sites
$(ROOT)/$(APP)/161-uenux2-app-vota-operador-identidade-roots.o: $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/log/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/log/*.h $(ROOT)/src/uenux2/src/api/uelog/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/161-uenux2-app-vota-operador-identidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/161-uenux2-app-vota-operador-identidade-pending.o $(APP)/161-uenux2-app-vota-operador-identidade-roots.o
