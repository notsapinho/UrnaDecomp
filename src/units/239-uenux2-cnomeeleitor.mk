# uenux2 vota operador: vota::CNomeEleitor (app/vota/operador/confirmaidentidade/cnomeeleitor.{h,cpp}), the operator's
# screen with the voter's name: GetInst (target fn 5401) with the constructor and the helper that builds the form, the
# statics' destructors (10503, s_inst's, and 10502, s_mutex's), the destructor, StartState (10501), ProcessInput (10500)
# with the four members it holds inlined, and HabilitaEleitor (5400) in cnomeeleitorauxiliares.cpp. Both files are
# compiled in unit 282's list (src/units/282-uenux2-confirmaidentidade-estados.mk), after its
# cinformaanodesabilitadodemo.cpp: this fragment holds no source list (the order, below). Paths relative to src/uenux2.
#
# Target fns matched: 5401, 10503, 10502, 10500, 10501, 5400. The destructor's slots hold the shared fns 244 and 387.
#
# Evidence:
# - The class: RTTI and its vtable @1591248 [244, 387, 10501, 7480, 1661, 218, 425, 10500, 425], which 5401 alone stores
#   (its vptr 1591256). The file is the records': cnomeeleitor.cpp:145 and :156 (@1591292, @1591308), NavegaBiometrica's
#   and NavegaAnoNascimento's, which ProcessInput (10500) holds inlined; the vtable lies just before them in the data.
#   5401 allocates 20 bytes: CAppState's 12 and the form at +12.
# - GetInst, the project's singleton: lock_guard on s_mutex (@1908816), s_inst (@1908840) reset with a new object, its
#   constructor inlined behind a 112-byte frame of its own (CAppState's with EVENTO_ENTRADA, 2). Fn 301 writes the form
#   at +12 directly, with no zeroing first, so the form comes from the member list, from a helper clang inlines.
# - The helper: AddLed(LED_OPERACAO_0); the voter's name (CEleitorDadoNomeParaUrna::Text, slot 3906) at {1, 1} with
#   the format "{:2}" (its four bytes and size stored in place); GetTextoIdentidadeDigitada (3907) at {1, 2}; "Seq:" at
#   {32, 2}; CEleitorDadoSequencial::Text (4055) at {40, 2} with "{:04}" on the right; "Seção:" at {30, 3};
#   CEleitorDadoSecao::Text (4056) at {40, 3} with "{:04}" on the right; CEleitorDadoTTE::Text (4113) at {1, 3};
#   "CORRIGE: cancelar" at {1, 4}; "CONFIRMA: prosseguir" at {40, 4} on the right; AddInputControl;
#   GetInteractiveForm("telaNomeEleitor", false). Before steps 7 to 9, 62 over 683 rows, all operand-only: the statics'
#   addresses and the calls (pnpm wasm score).
# - The statics are defined before the records: their destructors (10503, 10502) sit above StartState (10501) in use
#   band 1, a choice of line beyond that.
# - Names (step 8): 5401 by vptr-anchor, the statics by its votes, their destructors match through them.
#
# - ProcessInput (10500, slot 7): the form's Read (record cinteractiveform.h:57 in this object's data); on CONFIRMA,
#   GetParametrosUrna().GetPedeAnoNascimentoEleitor() (+489) picks ConfirmaComAnoNascimento or ConfirmaSemAnoNascimento,
#   each behind a frame of its own in 10500, so out of line and inlined by binaryen into their one caller (a reading,
#   how-to step 3); clang does not inline them (cost 860 and 455 against 250, -Rpass=inline). On CORRIGE, CLogVota's
#   LogaHabilitacaoCanceladaConfirmacaoDado (2097) and CCancelaHabilitacaoEleitor::GetInst (1536) as the next state; the
#   cases are written CONFIRMA, CORRIGE, the br_table's block order. NavegaBiometrica and NavegaAnoNascimento hold the
#   records (lines 145 and 156, column 19: `bool ehDemo = ` at four spaces, a spelling chosen of that length); clang
#   inlines each into its callers (no frame of its own). NavegaAnoNascimento holds CInformaAnoDesabilitadoDemo's and
#   CPedeAnoNascimentoSemBiometria's GetInst, each behind its constructor's frame: out of line in their files, inlined by
#   binaryen, each its one caller's (units 282 and 142 write them).
# - ConfirmaComAnoNascimento's shape, measured on the objects and in the link: the flag test after a && reads `i32.eqz`
#   on CEleitor's +100 in the target, which comum::md::CEleitor::TemBiometria out of line in celeitor.cpp gives (unit
#   157's), where the inline accessor gave `i32.const 1; i32.ne`; HabilitaBiometria (+665) read into a local before the
#   test gives the target's `i32.and` with 1, where a call in the condition gave `i32.ne`; the training test, the
#   current voter's sequence number above five sixths of the voters and not past them, reads `i32.eqz(i32.and(gt_u,
#   le_u))` in the target, which clang turns into `i32.or(le_u, gt_u)` whenever it sees the whole expression (seven
#   polarities and spellings tried on probe objects, every one gave the or), and keeps as the call of an out-of-line vota::EleitorNaFaixaSemBiometria
#   (cnomeeleitorauxiliares.cpp) that binaryen inlines (the three tests' forms measured on probe objects at the tree's
#   flags). In the link, 10500 read 343 over 1749 rows (13 inserted, 13 deleted) with none of the three, 339 over 1748
#   with the first two, 335 over 1748 with all three, and 172 over 1736, all operand rows, with
#   cinformaanodesabilitadodemo.cpp's object ahead of this one (below; pnpm wasm score each time).
# - The order of objects, measured (docs/reference/facts/codegen.md C4): with cinformaanodesabilitadodemo.cpp.o after
#   cnomeeleitor.cpp.o, as this list ahead of unit 282's gave it, 10500 read 335 over 1748 rows (12 inserted, 11
#   deleted), its locals in CInformaAnoDesabilitadoDemo::GetInst's inlined code numbered apart from the target's; with
#   that object ahead of this one, 172 over 1736, all operand rows (pnpm wasm score on the whole link). In the target's
#   data the four classes' vtables come in the order CInformaBioDesabilitadaDemo (@1591104), CInformaAnoDesabilitadoDemo
#   (@1591176), CNomeEleitor (@1591248), CInformaEleitorPodeVotar (@1591352) (ledger/vtables.json), so cnomeeleitor.cpp
#   and cnomeeleitorauxiliares.cpp are compiled in unit 282's list between the second's and the fourth's files, and stay
#   this unit's. The move takes cnomeeleitor.cpp.o past 38 objects: the other units' between the two lists and unit
#   282's first two. Of the 29 with a vtable or typeinfo, 25 keep the data's order and 4 are inverted, their vtables
#   after CNomeEleitor's in the data and their objects ahead of it in the link: comum::CRegistrarMesarios (@1593584,
#   unit 247), vota::CTentativaCapturaDigitalEsgotada (@1592280) and vota::CDigitalNaoCapturada (@1592352, both unit
#   278), and comum::CMesarioRegistrado (@1594872, unit 279). Each address is the lowest of the object's _ZTV/_ZTI
#   symbols in splat/symbol_addrs.txt, the symbols from the link map. With cinformaanodesabilitadodemo.cpp.o ahead of
#   cnomeeleitor.cpp.o no place inverts fewer: of the 38 from this list's place to cinformaeleitorpodevotar.cpp's, this
#   one alone inverts 4, the others 5 or more. Compiling cinformaanodesabilitadodemo.cpp in this list instead, ahead of
#   cnomeeleitor.cpp, also gave 10500 172 over 1736 rows, but inverted 24 of that object's 29 pairs and renamed 3883's
#   merge body. In this order 10500 reads 172 over 1736 rows, all operand rows, and binaryen's merge body of unit 282's
#   three ProcessInput slots keeps the name of its first member in link order, CInformaBioDesabilitadaDemo's (3883's
#   match line in splat/matched.txt).
# - HabilitaEleitor (5400): LimpaBiometria, then CHabilitaAudioEleitor when IsAudioAtivado, else Post(1) to
#   CThreadEleitor's queue and CMostraEleitorVotando, the next state stored in each branch (two stores, which
#   comum::CAppState::SetNextState called in both gives: docs/reference/facts/codegen.md C13; assignments gave one store
#   after the join, 17 over 42 rows, 3 inserted, 5 deleted). Its two target callers keep the call where clang inlines it
#   in their TU (cost 185, threshold 250), so it is in a TU of its own (docs/reference/facts/placing.md P2): the file,
#   cnomeeleitorauxiliares.cpp, and its place right after cnomeeleitor.cpp in unit 282's list are chosen; the band
#   (5401, 5400 and cinformaeleitorpodevotar.cpp's 5399) has it between those objects, which that list gives.
# - StartState (10501): CAppInfo::EhTreinamentoEleitor (697) sends the voter to HabilitaEleitor; else
#   vota::ApresentaFotoEleitor (3616, unit 319), the form's slot 2 and `this`. It is defined before ProcessInput, the
#   band's order (10501 above 10500). Named by its vtable; its call of 3616 holds through 3616's hand line.
# - Names (step 8): 5401 by vptr-anchor, the statics by its votes, their destructors match through them; 10500 by
#   srcloc-anchor, 5400 by 10500's call.
#
# Chosen: the header's path (beside the records' file), the member names but NavegaBiometrica's and
# NavegaAnoNascimento's, the helper's name and its being in an anonymous namespace, cnomeeleitorauxiliares.cpp and
# EleitorNaFaixaSemBiometria (name, being a free function of vota, file), the lines before and between the records.
# GetInst's two target callers, fns 10635 (vota::CEleitorEncontrado's StartState, unit 104) and 10677 (CPedeIdentidade's
# ProcessInput, unit 161), are in the link; so are 5400's two, 10500 and 10501, so no roots file is needed.
# The sources (cnomeeleitor.cpp, cnomeeleitorauxiliares.cpp) are compiled through
# 282-uenux2-confirmaidentidade-estados.mk's list.
# cnomeeleitor.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through CConfiguracaoMunicipio's
# CHorariosUrna (an include path, not a flag of the code: unit 104 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/cnomeeleitor.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
