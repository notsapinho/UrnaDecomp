# uenux2 vota::testeteclado::CTesteTeclado (app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.{h,cpp}), the
# keyboard test, and the code its StartState (target fn 11805) holds behind second stack-pointer prologues. Matched:
# GetInst (3855), with the constructor inlined by clang; the D2 and D0 (2868, 11806); the exit destructors of its static
# std::unique_ptr and std::mutex (11808, 11807); the destroy of its std::map's tree (2023, now linked from
# ctelasvota.cpp.o, which instantiates the map first); api::CPolySingletonList::has<impl::IGeradorTeclas> (3853) and
# std::vector<std::string>::at (3854), from this object; in other units' files, api::CTextBox::SetStatus (940, unit 65's
# ctextbox.cpp) and the destroy of GetKeyboardLayout's map (4148, unit 110's ctelasvota.cpp). Written and not matched
# (below says what each waits for): StartState (11805); impl::CGeradorTeclasAleatorio::GeraSequencia (11803, slot 2 of
# its vtable); the initializer-list constructor of GetKeyboardLayout's map (6579, ctelasvota.cpp's instance).
# 217-uenux2-ctesteteclado-pending.cpp traps ProcessInput (11804). The class head says what its layout and declaration
# rest on; igeradorteclas.h and cgeradorteclasaleatorio.h say what the generator's do.
#
# What StartState holds (pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11805), in order, and where it is written:
# - CLogVota::GetInst (184), then a 16-byte frame that passes "Inicio do teste de Teclado do TE" to fn 233:
#   CLogVota::LogaInicioTesteTeclado, added to unit 119's clogvota.cpp after LogaTesteTecladoNaoExecutado, the shape
#   clogvota.h lists (GetInst called before the member's own frame opens). Then `this` stored at +4.
# - A 432-byte frame, vota::TelaTesteTeclado in ctelasvota.cpp. Record 1538476 (ctelasvota.cpp:1301:9, `const auto
#   vota::(anonymous namespace)::GetKeyboardLayout()`) is the default std::source_location of the
#   api::CPolySingleton<api::IUrna>::instance() call in it (fn 923), and an anonymous-namespace function is called from
#   its own TU only, so the function that holds it is that file's. GetKeyboardLayout compares api::IUrna's slot 0
#   (Modelo) with 2019 and builds one of two 13-entry maps from an initializer list (fn 6579, a call in each branch,
#   its count folded: 312 bytes of 24-byte entries), keyed by the 13 strings of a std::vector<std::string> at @1833360,
#   which __wasm_call_ctors builds ("1" to "9", "0", "BRANCO", "CORRIGE", "CONFIRMA"); each value is two points, a
#   16-bit font size and a char (+12, +16, +20 and +22 of an entry). Per key: map::at (the throw of "map::at:  key not
#   found", fn 1239), a 32-byte frame (vota::AdicionaCaixaTecla: std::make_shared<api::CTextBox>, 80 bytes, the
#   constructor behind a 16-byte frame of its own with its record ctextbox.cpp:41, then api::CFormBuilder::AddField, fn
#   426), and the insert of {name, {char, box}} into a map; then AdicionaCabecalhoTesteTeclado (3054), "Pressione a
#   tecla destacada" at (320, 440) in the {20, 0} font at @474896 through AddTextField (202), and
#   GetFormularioInterativo (576) of "telaTesteTeclado". It returns the form and a copy of the map, which StartState
#   moves into +28 and +36.
# - A 16-byte frame, impl::IGeradorTeclas::GetInst (record ctesteteclado.cpp:121:89), with has<T> (3853, two calls),
#   push<T> (512 bytes) and instance (112 and 576 bytes) behind frames of their own, and last the unlock of a static
#   std::mutex (@1837656; its exit destructor is fn 11802): unit 50's POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO,
#   whose column is 52 plus the lengths of the interface's and the class's names (unit 50's reading): 89 = 52 + 14 + 23,
#   IGeradorTeclas and CGeradorTeclasAleatorio, the class whose vptr (@1547296) the 4-byte object GetInst creates holds.
# - A 16-byte frame, vota::SorteiaTeclasTesteTeclado in ctelasvota.cpp: a copy of the key vector passed to the
#   generator's slot 2 (vtable + 8); StartState moves the result into +48 and stores 0 at +60.
# - The throws on the records' lines: 9359 "Sem teclas para testar" (:38) when the sequence is empty, 9360 "Tecla nao
#   encontrada: " + at(+60) (fn 345 over fn 3854; :42) when the map has no first key; else the form's slot 2, then
#   fn 940 with the key's box and 1.
#
# Matched. Measured in the whole link (pnpm wasm score against build/out/wasm-map/vota_web/names.tsv) before steps 7 to
# 9 matched each: 940 1 over 36 rows, 3853 18 over 169, 3854 1 over 21, 4148 2 over 25, all operand-only. Step 8 named
# 940 and 4148 by pair-addr and 3853 by content-anchor (the typeinfo name it copies). 3854 has no line in the symbol
# file and no census pair (`awk -F'\t' '$1==3854' ledger/functions.tsv`: kind none), so the scan's content pass found
# it; its target callers, 11804 and 11805, call it on +48, the std::vector<std::string>, the instance whose name it
# took.
# In use band 3 (ledger/ordinals.tsv) this object's 3855, 3854 and 3853 run in that link order, as the target's index
# does: GetInst is defined above StartState, the first function that mentions at(); and ctelasvota.cpp.o's 4152, 4148,
# 4137, 4135 do: TelaTesteTeclado, which first mentions 4148, sits after AdicionaTelaAguarde and before CTelasVota's
# destructor, which first mentions 4137 (build/out/wasm-map/vota_web/names.tsv's ld_index).
# The map's char is evidence: ProcessInput compares the found node's byte with the key it reads and widens it signed
# (`i32.load8_s` at +28 in fn 11804).
#
# Evidence for the members matched when the unit landed, measured in the whole link with pnpm wasm score against
# build/out/wasm-map/vota_web/names.tsv before steps 7 to 9 matched each:
# - 3855 11 over 56 rows, 2868 3 over 84, 11806 2 over 7, 11808 4 over 16, 11807 2 over 4, 2023 2 over 50, all
#   operand-only. Step 8 named 3855 by vptr-anchor, 2868, 11806 and 11808 by pair-addr, and 2023 by a call vote; 11807
#   matched through the content pass, its body the destructor of the mutex that 3855's vote names
#   (CTesteTeclado::s_mutex at 0x1c0074), next to 11808, the same object's other static. 3855, 2868 and 11806 score the
#   same in this link.
# - The order of ctesteteclado.cpp's definitions: in use band 1 (ledger/ordinals.tsv) the target's index runs 11808,
#   11807, 11806, so the statics' exit destructors come before the D0 in link order (docs/reference/facts/reading.md
#   R9). With the destructor defined first, our D0 took ld_index 3518, ahead of the exit destructors' 3521 and 3522;
#   with the statics defined above it, the D0 comes after them (build/out/wasm-map/vota_web/names.tsv). The pointer is
#   defined first: 11808 comes before 11807 in the band, as ours does.
# - 2023's body has a twin shape in our link: RHVoice's language_list map destroy (from src/app/roots_rhvoice.o) scored
#   the same 2 over 50 against it, and our link keeps the two apart (a reading: each calls itself). The census paired
#   our CTesteTeclado instance with the target's 3634 too (caller 10812, not written); it now pairs RHVoice's with it,
#   and 3634 reads unresolved on its own recursive call.
# No other spelling of these bodies was compiled.
#
# Written and not matched, and what each waits for. Measured on private links: a copy of build/out/app in which only
# the named objects are rebuilt, with UENUX2_TBAA_DIRS= for this lane's two files, then make -C src link APP=<copy> and
# tools/round/link-map.sh; pnpm wasm score as above.
# - Strict aliasing. src/Makefile's UENUX2_TBAA_DIRS (src/app/vota/%) gives ctelasvota.cpp and ctesteteclado.cpp TBAA;
#   docs/reference/facts/app-flags.md F6 reads app/vota's setting from one row (1719) and calls it a choice for its
#   other directories. 6579 reloads the tree's begin after a new node's stores, with no call between
#   (docs/reference/facts/reading.md R21): 74 over 308 rows here, 2 over 292, operand-only, with both files without
#   TBAA. 11803 holds std::uniform_int_distribution<long>::operator() inlined and reloads its lower bound after the
#   engine's loop; here that operator stays a call (cost 375, threshold 250, -Rpass-missed=inline) with a second
#   caller, unit 50's 5412, and 11803 scores 255 over 447 (226 rows deleted). With both files without TBAA and 5412's
#   distribution of unsigned long (unit 50's same-object form): 24 over 447, operand-only, and 5412 31 over 350,
#   operand-only; with this lane's files without TBAA alone, still 255 (the long instance has the two callers). The
#   flag is the user's decision: the bodies stay as written.
# - ProcessInput in this TU. StartState: 1699 over 4686 rows here; 392 over 4520 (379 operand-only, 4 inserted, 4
#   deleted) with both files without TBAA. What is left is push<IGeradorTeclas>'s frame (its string temporary at +120
#   where the target's, as fn 599's, is at +172) and where l8 + 28, the sequence's result slot, is set. With a call of
#   api::CPolySingleton<api::IInputKbd>::instance() in a function above line 121 (a scratch line, not kept:
#   ProcessInput calls that instance, fn 455), push's frame is the target's: 310 over 4520 (302 operand-only, the same
#   4 and 4); docs/reference/facts/codegen.md C5 has the mechanism. ProcessInput (11804) waits for fn 653,
#   api::CInteractiveFormBuilder::AddLabeledInputControl, which has no body of ours. The l8 + 28 rows are not explained.
# - 11802, the exit destructor of GetInst's mutex (`f150(1837656)`), and 12862, the key vector's, read no-candidate:
#   no matched function uses either object (StartState uses both, __wasm_call_ctors builds the vector). 12862 is also
#   `f6071(p0, 1833368, 1833364, 1833360, 4, 1, 12)`, a thunk into the body binaryen merged from it and fn 10879 (not
#   written); ours is a whole body.
#
# Chosen, no evidence names them: every name the records do not give (LogaInicioTesteTeclado, TelaTesteTeclado,
# SorteiaTeclasTesteTeclado, AdicionaCaixaTecla, TTeclasTesteTeclado, TECLAS_TESTE_TECLADO, SLayoutTecla and its
# members, FONTE_INSTRUCAO_TESTE_TECLADO, GeraSequencia and every parameter and local, the enumerators 9359 and 9360 in
# app/vota/euevotaerror.h); the three vota:: functions being free functions of vota (the file's code is in vota by the
# record; none reads a class's private state: docs/how-to-decompile.md step 3); AdicionaCaixaTecla in
# ctesteteclado.cpp, another TU than its caller, because in ctelasvota.cpp clang inlines it into TelaTesteTeclado (cost
# 120, threshold 375, -Rpass=inline) where the target keeps it behind its own frame (which other TU is the choice);
# TelaTesteTeclado returning a std::pair that StartState assigns with std::tie (a struct or a structured binding were
# not compiled); the map's std::shared_ptr<api::CTextBox> (StartState calls fn 940 on the pointer as it is); the `if`
# over the first layout (the other order not compiled); CGeradorTeclasAleatorio not final, IGeradorTeclas's slot 2
# pure; the header paths.
# Forms measured: AdicionaCaixaTecla reads the font size into a named local before std::make_shared, where the target
# loads it before the allocation; passed as `fonte.size` it loads after it, and as
# `static_cast<api::TFontSize>(fonte.size)` before it, as the local does (the object's disassembly of the function).
# The instruction string in TelaTesteTeclado is a named local declared after the loop: the target destroys it after
# the return's temporaries and before the map (a temporary was not compiled). The insert of a value_type temporary is
# the target's +112 object (emplace was not compiled).
# Placement: GetKeyboardLayout's `if` on line 1301, with SLayoutTecla above it in the anonymous namespace; the {20, 0}
# font after FONTE_TITULO (the target holds it at @474896, after FONTE_TITULO's @474888); TECLAS_TESTE_TECLADO,
# TelaTesteTeclado and SorteiaTeclasTesteTeclado after CTelasVota's statics, and CTelasVota's destructor after them
# (line 3463; it was on 3439): the band order above; and in band 1 the index runs 12882, 12875, 12862, the statics'
# exit destructors before the vector's, so its definition follows theirs, and ctelasvota.h declares it extern for line
# 1303. In ctesteteclado.cpp, GetInst, the statics and the D0 above StartState (record :38), the constructor (no index)
# below ProcessInput's blank record lines 50, 60 and 81, GeraSequencia above the macro (its static std::mt19937,
# @1835152, lies below the macro's mutex in .bss), AdicionaCaixaTecla last; api/gui/ctextbox.h and
# api/gui/cinteractiveform.h moved into ctesteteclado.h, whose members name both, to keep StartState's record lines.
# Other lines chosen.
# The roots give fns 940 and 3854 the second call site the target gives them (ProcessInput, 11804, calls both; fn 5982,
# not written, calls 940): binaryen would inline each into StartState, its one caller in our link.
CTESTETECLADO_SRCS := src/app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp
UENUX2_SRCS += $(CTESTETECLADO_SRCS)
# The member not reconstructed: 217-uenux2-ctesteteclado-pending.cpp gives the vtable its trapping body, compiled at
# the class's flags
CTESTETECLADO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/217-uenux2-ctesteteclado-pending.o: $(ROOT)/src/units/217-uenux2-ctesteteclado-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/217-uenux2-ctesteteclado.mk $(CTESTETECLADO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,$(CTESTETECLADO_SRCS)) -c src/units/217-uenux2-ctesteteclado-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/217-uenux2-ctesteteclado-pending.o
# The stand-ins for the target callers not in the link: 217-uenux2-ctesteteclado-roots.cpp
$(ROOT)/$(APP)/217-uenux2-ctesteteclado-roots.o: $(ROOT)/src/units/217-uenux2-ctesteteclado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/217-uenux2-ctesteteclado.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/217-uenux2-ctesteteclado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/217-uenux2-ctesteteclado-roots.o
