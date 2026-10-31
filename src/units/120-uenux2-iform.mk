# uenux2 api::IForm<MEDIA>, api::CFormStack<MEDIA> (api/gui/iform.h), api::CInteractiveForm<MEDIA, INPUT>
# (api/gui/cinteractiveform.h) and api::CInteractiveFormBuilder (api/gui/cinteractiveformbuilder.cpp). The classes are
# templates, so their code comes from the objects that build the forms: unit 31's builders (cformbuilder.cpp,
# cmtformbuilder.cpp, cpaperformbuilder.cpp, whose getters that unit's fragment lists) and this unit's
# cinteractiveformbuilder.cpp. The headers rebuild every uenux2 object; the objects that changed only gained functions
# (the static members' guarded initializers, the instantiations); cformbuilder.cpp.o's 16 std::format helpers and unit
# 78's roots' static constructor differ only in i32.const offsets, and unit 31's roots gained the getters' stand-ins
# (docs/agents.md "Shared build outputs").
#
# Target functions, by class (I = IScreen, M = IScreenMT, P = IPaper):
#   IForm<MEDIA>      constructor: 6024, binaryen's body of I's and M's, with the thunks 5548 and 5522 passing the vptr
#                     (P's is inlined into 5515); D2 2781 I, 2776 M, 5514 P; D0 11136, 11045, 5513 (IFormImpressao's
#                     slot, the same body); Slot2 11135, 11044, 11009; Slot3 11134, 11043, 11008; Refresh 11133, 11042,
#                     11007; GetRenderForm 11132, 11041 (P's 11004 differs, below); Slot7 5539, 5518, 11005
#   IFormImpressao<IPaperRelatorios>  GetRenderForm 11006 (cpaperformbuilder.h, record line 51)
#   CFormStack<MEDIA> Exibe 5541 I, 5520 M (P's inlined into 11009); Empilha 5540, 5519 (P's into 11008); Remove 5987 I
#                     (M's and P's inlined into their D2); Notifica 2651, 2631, 3670; GetHandles 5056, 5022, 5512,
#                     thunks of binaryen's 3941; GetObservable's call_once proxies 8902, 8716, 11002; the static
#                     destructors 8641, 8187, 12109 (s_mutex), 8177, 12108 (s_forms, M and P) and 8910, 8727, 11003
#                     (the observable); CObservable's D0 5052, 5019, 5511 and IObservable's D2 3470, 3458, 3669,
#                     thunks of binaryen's 3940; vector<FormHandle>::reserve 8879, one body for the three media
#   CInteractiveForm  SetFocus 1401 and Slot6 5529 (one body each for both instances); <IScreen, IInputKbd>: D2 11079,
#                     D0 11078, Slot2 11077, Slot3 11075, Slot7 11074; <IScreenMT, IInputMT>: 11032, 11031, 11030,
#                     11029, 11028
#   CInteractiveFormBuilder::GetInteractiveForm 554
#   libc++ that the forms reach: std::__shared_mutex_base's lock 3328, unlock 3327 and constructor 4670
#                     (FormControlBlock's std::shared_mutex), std::__call_once 2577, which the forms' callers keep out
#                     of line, and with it std::locale::id::__get (514), which calls it and matches since __call_once
#                     has that second caller and stays out of line
#
# What the bytes fix:
# - SetFocus (1401) inlines one IInputField member twice, with false and with true (iinputfield.h's SetAtivo). Written
#   as two members, Ativa and Desativa, 1401 scored 32 over 184 rows in the whole link (pnpm wasm score); one member
#   with a bool scores 2 over 175, both rows operand-only, and matches. In a lone compile with the uenux2 flags the two
#   members give `i32.const 1; i32.ne` for the deactivating test and keep the timer's reload hoisted, with Ativa out of
#   line or `inline`; SetAtivo gives the target's i32.eqz and its one call through a computed slot.
# - Slot6 (5529) finds the field with std::find_if: in lone objects std::find, a hand loop with break, std::ranges::find
#   and std::find with std::distance all leave the loop's exhaustion to skip the test, and only std::find_if sets the
#   iterator to end and tests it, as 5529 does. With std::find the whole link scored 6 over 43; with std::find_if 1 over
#   42, operand-only.
# - Exibe (5520, 5541) empties the stack with `while (!s_forms.empty()) s_forms.pop_back();`: its rows are the target's
#   `if (begin != end) end += (begin - end + 3) & -4`, where clear() stores begin as the end and resize(0) and
#   erase(begin, end) store it under that test (lone object). With clear() 5520 scored 27 over 94; with the loop 11 over
#   93, operand-only.
# - Empilha (5519, 5540) compares `form == topo`: the other order scored 16 over 132 with one row moved.
# - ClearKeyboardInput's test of +88 is inside it: the record's column 13 is two levels in.
# - The screens' getters (5550, 1694, 301 and 554) call SetName with a copy of the name only when it is not empty (the
#   length test, then the copy and its move into +60) and then empty the builder's vector; the paper's (5515) does
#   neither.
#
# Chosen, the bytes do not decide (each header says which of its names): CFormStack's member names and that the stack
# and its mutex are static data members; FormHandle's members; CObservable's Inicia and Atualiza (that they are its and
# not IObservable's); that IForm's members are defined in the class; IForm's Hide, Desenha, Redesenha, SetName and the
# names Slot2, Slot3, Slot6 and Slot7, which the landed callers use; Slot6's parameter type; IPaper::Refresh, an empty
# non-virtual member (ipaper.h says why); the spacing that puts GetRenderForm's call on its records' columns (iform.h
# 178:52, cpaperformbuilder.h 51:54); CInteractiveFormBuilder deriving from CFormBuilder, its header's path and
# GetInteractiveForm's name and place after the records' lines 76 and 86 of cinteractiveformbuilder.cpp, which stay
# blank (AddLabeledInputControl, fn 653, is not written); SetFocus, SetAtivo, ApagaCursor and every data member's and
# parameter's name.
#
# splat/symbol_addrs.txt gets ten hand lines, each `callers+content`, each shown needed by the scan without it and
# without its own match line (docs/reference/splat.md "Reviewing a match"; the matches each removal takes out are
# counted on the committed state). __assign_with_size of vector<FormHandle> (1872, 16 matches out) and its
# __emplace_back_slow_path (8872, 20), whose bodies of ours differ (106 over 434 rows and 36 over 186, pnpm wasm
# score), are named for their callers. CPolySingleton<IScreenMT>::instance (1714; 11041 out) and <IInputKbd> (455;
# 11077 and 11075 out) differ too (393 over 992 and 1176 over 1459): each loads a record no other target function
# loads, 1714's generated name is `call by:11041`, a vote of the one caller it would release, and 455 has none. The
# guard byte and the std::once_flag of GetObservable's statics, which only their media's Notifica reads: IScreen's (1
# out each, 2651, whose own vote is their generated name), IScreenMT's (8 each) and IPaper's (4 each). The functions of
# the chain (Exibe, Empilha, Notifica, the proxies and the GetHandles thunks, 3941) have no line: the content pass finds
# them once these are in: the scan without any line for them and without their match lines, run again until it adds
# nothing, leaves every row as it is (the first run brings back all but 11029, 11030, 11043 and 11044, the second those).
#
# Not matched:
# - 395 (an MT builder member that adds an input field of api::CInputFieldControl<IScreenMT>) allocates the field's 64
#   bytes first, then the CControlValidation and its control block, and releases the validation right after the
#   IInputField constructor (3673), before the field's vptr. That order is the one `new CInputFieldControl<IScreenMT>`
#   gives with api/gui/cinputfieldcontrol.h's constructor, which builds the validation (lone object). What may differ is
#   where the validation's std::shared_ptr lives: in 395's own frame (+8), a reading not measured.
#   The constructor 395 calls is not recovered, so 395 is not written, and 3673 and 3674 (the IInputField<IScreenMT>
#   constructor and vector<shared_ptr<IFormField<IScreenMT>>>::push_back(&&)), which only 395, 1151 and 5410 call, have
#   no caller in this link.
# - 1151 builds an api::CInputFieldMT (vtable @1587484, Draw 10726), whose class is not written; its vtable and its
#   control block's lie among app/vota/operador/outrasopcoes/ states' data, not in a builder's.
# - 5410, a screen built on a CMTFormBuilder ("ELEITOR(A) PODE VOTAR"), holds a
#   make_shared<CInputFieldControl<IScreenMT>> inlined, whose control block's vtable (@1580748) lies in the MT
#   builder's data, and waits for 395's family; 2024 (IInputField<IScreen>'s constructor) has no written caller (901,
#   2383, 3675, 5565, 5913, 7787).
# - 1872 and 8872 differ (above); 11004 (IForm<IPaper>::GetRenderForm, CPolySingleton<IPaper>::instance inlined)
#   differs at `call 608 | ours call 305`, CPolySingletonList::find, which our link merges (unit 100's fragment).
IFORM_SRCS := src/api/gui/cinteractiveformbuilder.cpp
UENUX2_SRCS += $(IFORM_SRCS)
# no caller of GetInteractiveForm, of CFormStack<IScreen>::Remove's other one or of
# CPolySingleton<IScreenMT>::instance's others is reconstructed yet: 120-uenux2-iform-roots.cpp stands for them, and
# says which they are
IFORM_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/120-uenux2-iform-roots.o: $(ROOT)/src/units/120-uenux2-iform-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/120-uenux2-iform.mk $(IFORM_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/120-uenux2-iform-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/120-uenux2-iform-roots.o
