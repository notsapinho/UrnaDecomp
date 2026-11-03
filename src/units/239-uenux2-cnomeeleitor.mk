# uenux2 vota operador: vota::CNomeEleitor (app/vota/operador/confirmaidentidade/cnomeeleitor.{h,cpp}), the operator's
# screen with the voter's name: GetInst (target fn 5401) with the constructor and the helper that builds the form, the
# statics' destructors (10503, s_inst's, and 10502, s_mutex's) and the destructor. Paths relative to src/uenux2.
#
# Target fns matched: 5401, 10503, 10502. The destructor's slots hold the shared fns 244 and 387.
#
# Evidence:
# - The class: RTTI and its vtable @1591248 [244, 387, 10501, 7480, 1661, 218, 425, 10500, 425], which 5401 alone stores
#   (its vptr 1591256). The file is the records': cnomeeleitor.cpp:145 and :156, ProcessInput's (10500), which stay
#   blank; the vtable lies just before them in the data. 5401 allocates 20 bytes: CAppState's 12 and the form at +12.
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
# Chosen: the header's path (beside the records' file), the member names, the helper's name and its being in an
# anonymous namespace, the lines before the records.
#
# Pending (239-uenux2-cnomeeleitor-pending.cpp says what each waits for): StartState (10501) and ProcessInput (10500).
# GetInst's two target callers, fns 10635 (vota::CEleitorEncontrado's StartState, unit 104) and 10677 (CPedeIdentidade's
# ProcessInput, unit 161), are in the link, so the roots file that stood in for them went.
CNOMEELEITOR_SRCS := src/app/vota/operador/confirmaidentidade/cnomeeleitor.cpp
UENUX2_SRCS += $(CNOMEELEITOR_SRCS)
# StartState and ProcessInput are not reconstructed: 239-uenux2-cnomeeleitor-pending.cpp gives the vtable trapping
# bodies, compiled with the unit's flags.
$(ROOT)/$(APP)/239-uenux2-cnomeeleitor-pending.o: $(ROOT)/src/units/239-uenux2-cnomeeleitor-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/239-uenux2-cnomeeleitor.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/239-uenux2-cnomeeleitor-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/239-uenux2-cnomeeleitor-pending.o
