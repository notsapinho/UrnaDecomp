# uenux2 api::IForm<MEDIA>, api::CFormStack<MEDIA> (api/gui/iform.h), api::CInteractiveForm<MEDIA, INPUT>
# (api/gui/cinteractiveform.h) and api::CInteractiveFormBuilder (api/gui/cinteractiveformbuilder.cpp). The classes are
# templates, so their code comes from the objects that build the forms: unit 31's builders (cformbuilder.cpp,
# cmtformbuilder.cpp, cpaperformbuilder.cpp, whose getters that unit's fragment lists) and this unit's
# cinteractiveformbuilder.cpp. The headers rebuild every uenux2 object; the objects that changed only gained functions
# (the static members' guarded initializers, the instantiations); cformbuilder.cpp.o's 16 std::format helpers and unit
# 78's roots' static constructor differ only in i32.const offsets, and unit 31's roots gained the getters' stand-ins
# (docs/agents.md "Shared build outputs").
#
# IForm<MEDIA>::FindFieldAs<T> (target fn 1721, the instance for CTextField, record iform.h:142:23) is written in the
# class, on its record's line, for unit 37's vota::CMostraQRCodeBU::AjustaTela (fn 5982), its one caller: it walks the
# fields for the name, copies the shared_ptr it finds (the target increments the count before dynamic_cast), casts it,
# and throws CUeGuiError 4978 when the type differs. It `differs`: unit 37's fragment has the measurement.
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
#   CInteractiveFormBuilder::AddLabeledInputControl 653 (below), GetInteractiveForm 554, and AddInputControl 901 (no
#                     argument) and 5530 (the keys), with
#                     what this object emits first of api/gui/cinputfieldcontrol.h and iinputfield.h:
#                     CInputFieldControlBase<IScreen>'s constructor 5565 and IInputField<IScreen>'s 2024 (unit 92's
#                     headers, whose notes they are), and the free function api::AddInputMenuField 3675 (below)
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
# GetInteractiveForm's name and its place after AddLabeledInputControl (653); what 653's paragraph below lists; SetFocus,
# SetAtivo, ApagaCursor and every data member's and parameter's name.
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
# - 395 and 3674 match from api/gui/cmtformbuilder.cpp's object, unit 31's source, and 3673 (IInputField<IScreenMT>'s
#   constructor) from unit 121's cescolheopcao.cpp.o, whose fragment sorts ahead of unit 31's and whose 1151 (an
#   api::CInputFieldMT pushed through 3674) instantiates it too: src/units/31-uenux2-cformbuilder.mk has their form,
#   what was measured, and 5410's code (a screen over a make_shared<CInputFieldControl<IScreenMT>>, written in unit 161,
#   differs).
#   Measured here before they matched, and a lead for 5410: at -O2 clang leaves CInputFieldControlBase<IScreenMT>'s
#   constructor out of line in a builder member (cost=240, threshold=225); at the tree's -O3 it inlines it there
#   (cost=240, threshold=250), and not into CInputFieldControl's own constructor (cost=260), which fits 5565
#   (IScreen's, out of line) and the copy with a frame of its own that binaryen inlined into 5410, a reading.
# - 3673 scored 12 over 211 rows, reached through those members in a scratch link, while CreateTimer took its callback
#   by value: the store of the 600 ms interval came after the timer lambda's stores, where 3673 (and 2024, 5904, 1265)
#   stores the interval first, right after ITimerScheduler::GetInst. cmtformbuilder.cpp's -O2 IR (-S -emit-llvm) had the
#   600 store first, so the backend moved it, and no spelling of the argument tried changed the object's order
#   (milliseconds(600), {600}, 600LL, duration<int, std::milli>, an explicit std::function, [=]), nor -O3.
#   CreateTimer's callback as a const reference does, in BatteryIconDataSource's constructor's object
#   (api/util/itimerscheduler.h takes it so now), and 3673 matches with it.
# - 901 and 5530, AddInputControl: 901's code holds the control field's construction behind a second prologue, with
#   the keys 4 folded in and CInputFieldControl<IScreen>'s vptr stored last, and 5530 calls 5565 and then stores that
#   vptr. The header's one constructor with the default argument 4 gives both (the object keeps 901's
#   __shared_ptr_emplace constructor over no argument out of line, which binaryen inlines into its one caller, and
#   5530's call of 5565); 5565 keeps its body only with a second caller in the link, 653.
#   5565 is named by its own vptr anchor; 2024 by 5565's call vote alone, which docs/reference/splat.md 3 holds through
#   901, a match that calls 2024 too; 901 and 5530 by the scan's content pass. While 2383 was out of the link (below),
#   2024's callers in it passed the length 0, true and false alike, and binaryen folded the three (2024 then 5
#   parameters, 5565 three rows short), so unit 92's roots stood for 2024's other callers; 2383 is in the link since
#   (unit 110's ctelasvota.cpp) and passes its own parameters on, and unit 92's roots keep a stand-in for 7787.
# - 653, AddLabeledInputControl (records 76:23, the throw of the lambda over a key, EUeGuiError 4936, "Tecla de controle
#   não suportada '{}'"; 86:15, 4937, "O número máximo de teclas suportado é {}", past three keys), matches. For each key
#   it takes the bit of 'B', 'C' or 'D' (1, 4, 2: the switch's table at 524056), adds the key's labels with the alignment
#   popped from a vector {2, 0, 1}, draws a line 50 above the bottom of the area and returns the form's first
#   IInputField<IScreen> or a new CInputFieldControl<IScreen> over the bits (AddInputControl(int), 5530's code, which clang
#   inlines). Of its 14 target callers 2376 is written (vota::TelaTextoConfirmaCorrige, ctelasvota.cpp, which passes
#   api::CApplication::s_areaTela and false); the roots' RotulosA and RotulosB pass the same for the others, and binaryen
#   folds both to the target's three parameters. What fixes its form, each measured on a copy of
#   this tree's link.cmd with the variant objects swapped in (`pnpm wasm score`), or on the object where it says so:
#   - The key loop holds a branch on the bool, which clang unswitches (the object holds the loop twice) and binaryen,
#     with the bool folded, cuts to one loop. Without such a branch the frame is 528 bytes, the target's 544, and the bad
#     key's throw lies inside the loop, before the label call, where the target has it after the loop (objects); with
#     it, both are the target's. That the 16 bytes are the lambda's message, whose lifetime start the
#     unswitched loop holds twice, so that stack colouring keeps its slot (+96) apart from the format code's, is a
#     reading: the loop without the branch compiled with -mllvm -stackcoloring-lifetime-start-on-first-use=false gives
#     the target's 544-byte frame and its slots too (object).
#   - Under that branch the label: with it under `if (!flag)`, or after `if (flag) continue;` (the same wasm), the throw
#     comes between the loop and the line, as in the target; under `if (flag)`, or after `if (!flag) continue;`, at the
#     function's end (objects). So the labels are added when the flag is false, the value the stand-ins pass; its name
#     (semRotulos) and that it gates the labels, not something else the false loop does, are chosen.
#   - The labels through api::CFormBuilder::AddKeyLabel (cformbuilder.cpp), 2243's code with the label first, which only
#     653 calls and binaryen inlines (cformbuilder.h says why it is a function apart from 2243): 653 passes it the key
#     it loaded once for the switch (i32.load8_s); passing the key's whole std::pair loads it twice (68 over 650 rows,
#     with the aggregate SPoint). AddLabeledKey(char, rotulo, alinhamento, 2, 1), the colours two more parameters,
#     gives 653 the same body (wasm-objdump -d of both links).
#   - The line's first point loads area.bottom before area.left: with api::SPoint's constructor (primitives.h) 653 scores
#     49 over 648, every row an operand; with the aggregate SPoint(...) 53 over 649 (1 inserted, 3 deleted, that order
#     alone), and fifteen other spellings of the two points with the aggregate (a named y, named x and y, named
#     points, copies, braces, a copy or a structured binding of the area) gave none of the target's order (objects).
#   - The search for an input field: std::find_if over a dynamic_cast, then std::dynamic_pointer_cast of what it found,
#     the target's two __dynamic_cast calls; the form is chosen among those that give them (no other was measured).
#   Chosen: the names (mascara, teclasAtivas, alinhamentos, the parameters'); the switch with its cases one level in (the
#   record's column 23 puts the throw four levels in, not how); the size check's argument alinhamentos.size(); the
#   loop's range-for with structured bindings and the OR before the label; the blank lines between the lambda and the
#   size check (the records fix only lines 76 and 86).
#   2383, an adder of a CInputField<CFramedText> over a CNumberValidation (callers 1591, 2384, 7787, 11892), matches in
#   unit 110's ctelasvota.cpp, where a file-static helper clang inlines gives the target's frame (unit 110's fragment).
#   Written here before as the target's code reads (the validation a named local, the field a SharedInput, AddField,
#   return), it differed in its frame alone: the target keeps the validation at +16 and the field's SharedField copy at
#   +24, ours the other way round, and the validation as a temporary of the new-expression allocates the field first.
#   Anchored by its vptr, its +24 against the target's +16 voted our table slot 24 (ecourna's CError constructor) onto
#   the target's slot 16, and the conflicting vote took CError's name and ten matches with it (710, 1011, 1898, 2379,
#   3520, 3653, 6133, 9056, 10257, 10881 left `match`), docs/reference/facts/splat.md S8 item 1's case.
# - 8872 matches (above). 11004 (IForm<IPaper>::GetRenderForm, CPolySingleton<IPaper>::instance inlined) matches
#   since unit 170, whose copies of CPolySingletonList::find keep 305 and 608 apart (unit 100's fragment).
# - api::AddInputMenuField (3675, a chosen name; cinteractiveformbuilder.h has its evidence and choices), defined last in
#   cinteractiveformbuilder.cpp, matches, with CInputMenuField's constructor and the members whose records it loads
#   (cinputmenufield.cpp 251 and 477) defined in unit 84's cinputmenufield.cpp and inlined into it by binaryen. Its file
#   is a reading of its use bands (how-to step 3, rule 5), and measured with pnpm wasm score in the plain link: in
#   cinputmenufield.cpp, 162 over 528 rows (16 inserted, 18 deleted); here, 29 over 512, every row an operand (calls,
#   data, and the five rows of the default instruction string's .bss address, which a hand line names: unit 84's
#   fragment). It is named by its srcloc-anchor. The stand-in for its target caller not written (11884) stays in unit
#   84's roots (MenuPorPartido); 11888's went once 11888 was in the link.
IFORM_SRCS := src/api/gui/cinteractiveformbuilder.cpp
UENUX2_SRCS += $(IFORM_SRCS)
# no caller of GetInteractiveForm, of AddInputControl, of CFormStack<IScreen>::Remove's other one or of
# CPolySingleton<IScreenMT>::instance's others is reconstructed yet, nor 653's:
# 120-uenux2-iform-roots.cpp stands for them, and says which they are
IFORM_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/120-uenux2-iform-roots.o: $(ROOT)/src/units/120-uenux2-iform-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/120-uenux2-iform.mk $(IFORM_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/120-uenux2-iform-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/120-uenux2-iform-roots.o
