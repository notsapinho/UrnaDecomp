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
#                     11007; GetRenderForm 11132, 11041 (P's 11004, below); Slot7 5539, 5518, 11005
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
#   CInteractiveFormBuilder::GetInteractiveForm 554, and AddInputControl 901 (no argument) and 5530 (the keys), with
#                     what this object emits first of api/gui/cinputfieldcontrol.h and iinputfield.h:
#                     CInputFieldControlBase<IScreen>'s constructor 5565 and IInputField<IScreen>'s 2024 (unit 92's
#                     headers, whose notes they are)
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
# splat/symbol_addrs.txt gets nine hand lines, each `callers+content`, each shown needed by the scan without it and
# without its own match line (docs/reference/splat.md "Reviewing a match"; the matches each removal takes out are
# counted on the committed state). vector<FormHandle>'s __emplace_back_slow_path (8872, 20 matches out) is named for its
# caller; its body of ours, 36 over 186 with -fno-strict-aliasing (pnpm wasm score), matches since src/api/ builds with
# strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6). Its __assign_with_size (1872) had a tenth line
# while our body differed (106 over 434 rows at -std=c++20; 16 matches out): it matches at the tree's -std=c++23, and
# the scan without the line and without the match lines of 1872 and its six callers brings all seven back, every row as
# it was, so the line went. CPolySingleton<IScreenMT>::instance (1714; 11041 out) and <IInputKbd> (455;
# 11077 and 11075 out) differed too when the lines were added (393 over 992 and 1176 over 1459; 1714 matches since the
# executable TU's 455 differs from it, unit 100's fragment): each loads a record no other target function loads,
# 1714's generated name was `call by:11041`, a vote of the one caller it would release, and 455 had none. The
# guard byte and the std::once_flag of GetObservable's statics, which only their media's Notifica reads: IScreen's (1
# out each, 2651, whose own vote is their generated name), IScreenMT's (8 each) and IPaper's (4 each). The functions of
# the chain (Exibe, Empilha, Notifica, the proxies and the GetHandles thunks, 3941) have no line: the content pass finds
# them once these are in: the scan without any line for them and without their match lines, run again until it adds
# nothing, leaves every row as it is (the first run brings back all but 11029, 11030, 11043 and 11044, the second those).
#
# Not matched:
# - 395 (an MT builder member that adds an input field of api::CInputFieldControl<IScreenMT>) allocates the field's 64
#   bytes first, then the CControlValidation and its control block, and releases the validation right after the
#   IInputField constructor (3673), before the field's vptr: the order `new CInputFieldControl<IScreenMT>` gives with
#   api/gui/cinputfieldcontrol.h's constructor, which builds the validation (lone object). The validation's
#   std::shared_ptr lives in 395's own frame (+8): 395 holds CInputFieldControlBase's constructor inlined, in one frame
#   and with no store of the base's vptr. Measured on a scratch copy of cmtformbuilder.cpp with 395 written as a member
#   that pushes a local std::shared_ptr<IInputField<IScreenMT>> (`m_campos.push_back(campo)`), by -Rpass=inline and
#   -Rpass-missed=inline: at -O2 clang leaves that constructor out of line (cost=240, threshold=225); at the tree's -O3
#   it inlines it into the member (cost=240, threshold=250), and not into CInputFieldControl's own constructor
#   (cost=260), which fits 5565 (IScreen's, out of line) and the copy with a frame of its own that binaryen inlined into
#   5410, a reading. At both levels clang also inlines vector::emplace_back(&&) into the member (cost=300,
#   threshold=325), where 395 calls it (3674, whose body appends at the end): so do emplace_back of the converted
#   temporary, a copy then push_back(std::move), a non-const local, and a by-value helper that clang inlines (cost=300
#   each); insert keeps a call, to insert. No form tried keeps 3674 a call, so 395 is not written, and 3673 and 3674,
#   which only 395, 1151 and 5410 call, have no caller in this link.
# - 1151 builds an api::CInputFieldMT (whose Draw is unit 146's) the same way, a std::shared_ptr<IInputField<IScreenMT>>
#   pushed through 3674, and is not written for the same reason. The vtable of its control block (@1588176) lies among
#   app/vota/operador/outrasopcoes/cescolheopcao.cpp's data, before that file's record of CEscolheOpcao's slot 7
#   (@1588216), not in a builder's.
# - 3673, IInputField<IScreenMT>'s constructor (api/gui/iinputfield.h), reached through those two members in a scratch
#   link, scored 12 over 211 rows: the store of the 600 ms interval comes after the timer lambda's stores, where 3673
#   (and 2024, 5904, 1265) stores the interval first, right after ITimerScheduler::GetInst. cmtformbuilder.cpp's -O2 IR
#   (-S -emit-llvm) has the 600 store first, so the backend moves it, and no spelling of the argument tried changes the
#   object's order (milliseconds(600), {600}, 600LL, duration<int, std::milli>, an explicit std::function, [=]), nor
#   -O3. CreateTimer's callback as a const reference does, in BatteryIconDataSource's constructor's object
#   (api/util/itimerscheduler.h, which takes it so now); 3673 is not measured again with it.
# - 5410, a screen built on a CMTFormBuilder ("ELEITOR(A) PODE VOTAR"), holds a
#   make_shared<CInputFieldControl<IScreenMT>> inlined, whose control block's vtable (@1580748) lies in the MT
#   builder's data, and waits for 395's family.
# - 901 and 5530, AddInputControl: 901's code holds the control field's construction behind a second prologue, with
#   the keys 4 folded in and CInputFieldControl<IScreen>'s vptr stored last, and 5530 calls 5565 and then stores that
#   vptr. The header's one constructor with the default argument 4 gives both (the object keeps 901's
#   __shared_ptr_emplace constructor over no argument out of line, which binaryen inlines into its one caller, and
#   5530's call of 5565); 5565 keeps its body only with a second caller in the link, which the roots give for 653.
#   5565 is named by its own vptr anchor; 2024 by 5565's call vote alone, which docs/reference/splat.md 3 holds through
#   901, a match that calls 2024 too; 901 and 5530 by the scan's content pass. With 2383 out of the link (below), 2024's callers in it pass the length 0, true and false alike, and binaryen
#   folded the three (2024 then 5 parameters, 5565 three rows short); unit 92's roots stand for 2024's other callers.
# - Not written, measured with each written here and taken out again, as nothing that matches needs it:
#   653, AddLabeledInputControl (records 76:23, the throw of a lambda over the key, "Tecla de controle não suportada
#   '{}'", EUeGuiError 4936; 86:15, "O número máximo de teclas suportado é {}", 4937, past three keys): for each
#   key it takes the bit of 'B', 'C' or 'D' (1, 4, 2, the table at 524056), adds the key's labels through the twin of
#   2243 that it inlines (31-uenux2-cformbuilder.mk) with the alignments 1, 0, 2 popped from a vector {2, 0, 1}, draws
#   a line 50 above the bottom of the screen's area (the SRect at .data 1577200), and returns the form's first
#   IInputField<IScreen> or a new CInputFieldControl<IScreen> over the bits. Written so, it scores 206 over 712: the
#   target lays the bad key's throw after the loop, ours inside it, and the frame slots of the two std::format calls
#   differ; not explained. The roots' ControleTeclas stands for its call of 5565.
#   2383, an adder of a CInputField<CFramedText> over a CNumberValidation (callers 1591, 2384, 7787, 11892), written
#   as the target's code reads (the validation a named local, the field a SharedInput, AddField, return) differs in
#   its frame alone: the target keeps the validation at +16 and the field's SharedField copy at +24, ours the other
#   way round, and the validation as a temporary of the new-expression allocates the field first. Anchored by its
#   vptr, its +24 against the target's +16 voted our table slot 24 (ecourna's CError constructor) onto the target's
#   slot 16, and the conflicting vote took CError's name and ten matches with it (710, 1011, 1898, 2379, 3520, 3653,
#   6133, 9056, 10257, 10881 left `match`), docs/reference/facts/splat.md S8 item 1's case.
# - 8872 matches (above). 11004 (IForm<IPaper>::GetRenderForm, CPolySingleton<IPaper>::instance inlined) matches
#   since unit 170, whose copies of CPolySingletonList::find keep 305 and 608 apart (unit 100's fragment).
IFORM_SRCS := src/api/gui/cinteractiveformbuilder.cpp
UENUX2_SRCS += $(IFORM_SRCS)
# no caller of GetInteractiveForm, of AddInputControl, of CFormStack<IScreen>::Remove's other one or of
# CPolySingleton<IScreenMT>::instance's others is reconstructed yet, nor 653, 5565's other caller:
# 120-uenux2-iform-roots.cpp stands for them, and says which they are
IFORM_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/120-uenux2-iform-roots.o: $(ROOT)/src/units/120-uenux2-iform-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/120-uenux2-iform.mk $(IFORM_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/120-uenux2-iform-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/120-uenux2-iform-roots.o
