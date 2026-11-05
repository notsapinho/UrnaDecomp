# uenux2 vota::testeteclado::CTesteTeclado (app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.{h,cpp}), the
# keyboard test, and the code its StartState (target fn 11805) holds behind second stack-pointer prologues. Matched:
# GetInst (3855), with the constructor inlined by clang; the D2 and D0 (2868, 11806); the exit destructors of its static
# std::unique_ptr and std::mutex (11808, 11807); the destroy of its std::map's tree (2023, now linked from
# ctelasvota.cpp.o, which instantiates the map first); api::CPolySingletonList::has<impl::IGeradorTeclas> (3853) and
# std::vector<std::string>::at (3854), from this object; StartState (11805), with vota::SorteiaTeclasTesteTeclado
# defined in this file (below), and the exit destructor of impl::IGeradorTeclas::GetInst's std::mutex (11802); in other
# units' files, api::CTextBox::SetStatus (940, unit 65's ctextbox.cpp), the destroy of GetKeyboardLayout's map (4148,
# unit 110's ctelasvota.cpp) and that map's initializer-list constructor (6579, ctelasvota.cpp's instance, matched
# since that file builds without strict aliasing: src/Makefile's UENUX2_NOTBAA_FILES). Written and not matched (below
# says what it waits for): impl::CGeradorTeclasAleatorio::GeraSequencia (11803, slot 2 of its vtable). The class head
# says what its layout and declaration rest on; igeradorteclas.h and cgeradorteclasaleatorio.h say what the
# generator's do.
#
# ProcessInput (11804, records :50, :60 and :81), written in ctesteteclado.cpp over its blank record lines: it reads a
# key from api::CPolySingleton<api::IInputKbd>::instance() (record :50, column 20: `auto& leitor = ` is a chosen
# spelling of that length) when one is there (IInput::GetKey, inline in api/hwil/iinput.h, its record 86:19), finds the
# key expected in the screen map (throws vota error 9361 at :60 with "Tecla não encontrada: " and the key when it is
# not there); on a wrong key it calls CLogVota::LogaFimTesteTecladoSucesso (fn 4511: the target calls it on this
# path too, its name is unit 119's choice), stores the two keys in vota::CEstadoAudio (SetTeclasTesteTeclado) and goes to
# vota::testeteclado::CTesteFalhou::GetInst() (held inlined); on the right one it marks its box with
# api::TEXTSTATUS_DESTAQUE (2), moves to the next key, and at the end logs again and goes to the state +64 holds;
# otherwise it finds the next key (9362 at :81, the same message) and marks it TEXTSTATUS_PREENCHIDO (1). Operand rows
# only in the whole link at once (73 over 624, pnpm wasm score; `i32.const 69 ~ 9` twice is __cxa_throw's destructor
# slot) and matched (srcloc-anchor); the lines between its records and the codes' names are chosen, and so is the
# function's first line right below StartState's brace (line 50 leaves no room for a blank line above it).
# ProcessInput's instance() call gives StartState push<IGeradorTeclas>'s frame, as the scratch line measured
# (StartState's paragraph below).
#
# The failure states it reaches, in testeteclado/ (new files, but cerrotestetecladofim.cpp, moved here from unit 97's
# list), each a singleton whose GetInst and constructor its one caller holds inlined, with its statics' two exit
# destructors (all matched with their callers):
# - vota::testeteclado::CTesteFalhou (ctestefalhou.{h,cpp}): GetInst in 11804; ProcessInput (11809, slot 7), on
#   CONFIRMA to CEsperaRetestar::GetInst() (5936), on CORRIGE to CEnviarManutencao::GetInst(); statics 11811, 11810.
# - vota::testeteclado::CEnviarManutencao (cenviarmanutencao.{h,cpp}): GetInst in 11809; ProcessInput (11812), on
#   CONFIRMA to CEsperaRetestar, on CORRIGE to CErroTesteTecladoFim::GetInst(); statics 11814, 11813.
# - vota::testeteclado::CErroTesteTecladoFim (unit 97's class): GetInst in 11812; statics 11816, 11815.
# Their screens are ctelasvota.cpp's (TelaTeclaErradaTesteTeclado with its lambda, fn 12903, matched by its table
# slot from 11804's anchor; TelaEnviarManutencaoTesteTeclado; TelaErroTesteTeclado: ctelasvota.h has them). Their
# classes' shape is CErroTesteTecladoFim's: slots 0 to 2 and 8 of the three vtables are one body each (785, 1560, 3857,
# 12061). Evidence: the vtables, the GetInst bodies inlined (sizes, vptrs, the base's argument, the statics'
# addresses), the br_table of each ProcessInput (CONFIRMA in its first block). The files are in the data's order
# (CErroTesteTecladoFim's vtable @1546920, CEnviarManutencao's @1546980, CTesteFalhou's @1547056, CTesteTeclado's
# @1547132), ahead of ctesteteclado.cpp: with cerrotestetecladofim.cpp in unit 97's list (behind cenviarmanutencao.cpp)
# 11812 differed in local numbers (190 over 471 rows, 176 operand-only, 7 inserted, 7 deleted), and here it has
# operand rows only; 11804 and 11809 had operand rows only at once. The move jumps 240 objects of the link. Counted
# with each object's vtables, typeinfos and records in .data (their target addresses from the symbol file and the
# records, against the link map), it inverts 29 pairs, objects whose data the target holds after the class's and the
# link before it: cgerabu, cgerarelatorios, ccopiaresultadoparamr, cfinalizaaquisicao, cimprimindobehb, cimprimirbjust
# and cmostraqrcodebu (fimvotacao/), cfimvotoeleitor, csincronismovotoeleitor, crelvotautil, cqrcodeds,
# cexibealertadesligamento, cvotacaostateaudio, cestadocomdesligamentoautomatico and fifteen of
# mock/app/simulador/wasm/ (cwasmclp, cwasmtimer, cwasmtimerscheduler, cwasmlogd, cwasmscreen, cwasmbeep,
# cwasmwebsound, cwasmscreenmt, cwasmnullprinter, cwasmnullpaper, cwasminputkbd, cwasminputmt, cwasmnullsound,
# cwasmsystemdatetime, cwasmnulltexttospeech); 183 keep their order, 9 have data on both sides and 19 none. The four
# testeteclado files are the data's order among themselves. Chosen: the classes' files and every member name, the
# `switch`es.
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
# - A 16-byte frame, vota::SorteiaTeclasTesteTeclado in this file (its place is measured: StartState's paragraph
#   below): a copy of the key vector passed to the generator's slot 2 (vtable + 8); StartState moves the result into
#   +48 and stores 0 at +60.
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
# StartState (11805) and 11802, matched once SorteiaTeclasTesteTeclado was defined here. Measured on whole links (pnpm
# wasm score as above), StartState scored 1699 over 4686 rows with ctelasvota.cpp at strict aliasing and 392 over 4520
# without it (379 operand-only, 4 inserted, 4 deleted), the same with ctesteteclado.cpp without it too; with a call of
# api::CPolySingleton<api::IInputKbd>::instance() in a function above line 121 (a scratch line, not kept: ProcessInput
# calls that instance, fn 455), push<IGeradorTeclas>'s frame was the target's (its string temporary at +172, as fn
# 599's, where it had been at +120): 310 over 4520 (302 operand-only, the same 4 and 4);
# docs/reference/facts/codegen.md C5 has the mechanism, and ProcessInput (11804) is that call now. The 4 and 4 were one
# statement, l9 = l8 + 28, the address of the frame slot GeraSequencia's result goes to: the target sets it inside
# impl::IGeradorTeclas::GetInst's inlined code, after instance<T>'s has() check and its throw, ours set it after
# GetInst's epilogue, right before SorteiaTeclasTesteTeclado's frame. The object does not decide it: StartState
# computes that address before its call of GetInst in this object, before and after the move (wasm-objdump -d). The
# order of the functions binaryen inlines does (docs/reference/facts/codegen.md C4): in replays of the link's own
# wasm-opt -Oz on its r02-stripped.wasm, four rewrites of the call's two operands (the address or GetInst's result
# held in a local first, both, neither) all scored 310 over 4520, 4 and 4; SorteiaTeclasTesteTeclado's function moved
# after StartState's (right after it, or after GetInst) scored 300 over 4516, none inserted or deleted; GetInst moved
# above StartState, 359 over 4521 (5 inserted, 5 deleted). ctelasvota.cpp.o links far ahead of this object, so the
# function is defined here, below StartState, which mentions it first: the object holds it right after StartState and
# GetInst (clang keeps it out of line; binaryen inlines it into its one caller). Measured on a scratch copy of it
# under another name that StartState called (ctelasvota.cpp's then dropped by wasm-ld): defined above StartState, on
# the blank line 13, it came first in the object and StartState scored 310 over 4520 in the whole link, 4 and 4;
# defined above AdicionaCaixaTecla and as the file's last function, the objects were the same (cmp).
# The last operand to resolve was 1837656, impl::IGeradorTeclas::GetInst's std::mutex (the macro's s_mutexGetInst),
# which StartState unlocks (150) at the end of GetInst's code and 11802 passes to 150 (std::mutex's destructor, one body
# with unlock): no other target function loads it (the grep of i32.const 1837656 in build/out/splat/pieces/asm), and
# none loads 1837657 to 1837679. With StartState's rows the target's, its records (:38, :42) anchor it at step 8
# (srcloc-anchor, where its line had been vtable), and the anchor's vote names the mutex (vote:2 by:11805 in
# splat/symbol_addrs.txt), a .bss name that only StartState votes for, so StartState holds through 11802, the object's
# static destructor, which the content pass matches from this object's __cxx_global_array_dtor.12
# (docs/reference/splat.md section 3, "No circular evidence": such a name holds through a second match that uses it,
# such as the object's static destructor): splat-build without 11802's match line refuses 11805 as UNCONFIRMED
# self-voted, and splat-review of either without the name's line fails, so the two land and leave together. No hand
# line names the mutex: step 8's vote reaches it. The callers+content hand line of fn 624
# (api::CMutexCompartilhado::unlock, which StartState calls) went with this match: step 8's own line names 624 too
# (evidence:call), and copies of the symbol file without the hand line, scanned twice beside a control over the same
# match list, kept every row (12794 match rows each), and splat-build on the copies gave the target's sha256.
#
# Written and not matched, and what each waits for. Measured on whole links of objects rebuilt with UENUX2_TBAA_DIRS=
# (the line a carve-out from strict aliasing gives them): first private links (a copy of build/out/app, make -C src
# link APP=<copy>, tools/round/link-map.sh), then in place with steps 7 to 9 (docs/reference/facts/app-flags.md F6);
# pnpm wasm score as above.
# - Strict aliasing. 6579 reloads the tree's begin after a new node's stores, with no call between
#   (docs/reference/facts/reading.md R21): 74 over 308 rows with ctelasvota.cpp at src/app/vota/'s strict aliasing, 2
#   over 292, operand-only, without it, and it matches since src/Makefile's UENUX2_NOTBAA_FILES lists ctelasvota.cpp.
#   ctesteteclado.cpp keeps strict aliasing: without it no row moves on the whole link, with or without 5412's
#   distribution of unsigned long (F6). 11803 holds std::uniform_int_distribution<long>::operator() inlined and reloads
#   its lower bound after the engine's loop; here that operator stays a call (cost 375, threshold 250,
#   -Rpass-missed=inline) with a second caller, unit 50's 5412, and 11803 scores 255 over 447 (226 rows deleted). With
#   this file without TBAA and 5412's distribution of unsigned long (unit 50's same-object form): 24 over 447,
#   operand-only, and 5412 31 over 350, operand-only, but both rows are then `unresolved self-voted` on the guards of
#   their std::mt19937 and std::random_device, statics no other target function reads (docs/reference/splat.md section
#   3, "No circular evidence"); with this file without TBAA alone, still 255 (the long instance has the two callers).
#   The body stays as written.
# - 12862, the key vector's exit destructor, reads no-candidate: it is `f6071(p0, 1833368, 1833364, 1833360, 4, 1,
#   12)`, a thunk into the body binaryen merged from it and fn 10879 (not written); ours is a whole body.
#
# Chosen, no evidence names them: every name the records do not give (LogaInicioTesteTeclado, TelaTesteTeclado,
# SorteiaTeclasTesteTeclado, AdicionaCaixaTecla, TTeclasTesteTeclado, TECLAS_TESTE_TECLADO, SLayoutTecla and its
# members, FONTE_INSTRUCAO_TESTE_TECLADO, GeraSequencia and every parameter and local, the enumerators 9359 and 9360 in
# app/vota/euevotaerror.h); the three vota:: functions being free functions of vota (the file's code is in vota by the
# record; none reads a class's private state: docs/how-to-decompile.md step 3); AdicionaCaixaTecla in
# ctesteteclado.cpp, another TU than its caller, because in ctelasvota.cpp clang inlines it into TelaTesteTeclado (cost
# 120, threshold 375, -Rpass=inline) where the target keeps it behind its own frame (which other TU is the choice);
# SorteiaTeclasTesteTeclado in ctesteteclado.cpp, below StartState (no record names its file; a place after StartState
# in the module gives the target's rows, measured above, which this file below StartState or a TU linked after it
# gives, and which one is the choice);
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
# font's line (3170, with the fonts of the screen builders that unit 110's fragment places above
# CriaTelaVisualizacaoCandidato) is a choice: the target holds it at @474896, after FONTE_TITULO's @474888, but clang
# emits such a constant at its first reader, not by its line. TelaTesteTeclado sits after AdicionaTelaAguarde and
# before CriaTelaVisualizacaoCandidato (lines 3266 to 3281; use band 2 puts 6579, which TelaTesteTeclado first
# mentions, before 6569, whose lines the records fix: unit 110's fragment), CTelasVota's destructor below (line 3478):
# the band order above. The lines SorteiaTeclasTesteTeclado held there (3283 to 3286) are blank, a gap, the line count
# kept: record 1538492 (6561's, adicionaFotoEmoldurada's instance) names the lambda of CriaTelaVisualizacaoCandidato
# it is instantiated over by its line and column (ctelasvota.cpp:3323:29), and with the definition's lines deleted 6561
# read unresolved, its record not the target's (a scratch link). TECLAS_TESTE_TECLADO follows CTelasVota's statics (line 3439): in
# band 1 the index runs 12882, 12875, 12862, the statics' exit destructors before the vector's, so its definition
# follows theirs, and ctelasvota.h declares it extern for line 1303. The data agree: the target holds
# TECLAS_TESTE_TECLADO (0x1bf990) before CTelasVota::s_mutex (0x1bf99c) and s_instancia (0x1bf9b4), and since
# TelaTesteTeclado, which reads the vector, moved above GetInst's line 3434, our link does too (0x1babfc, 0x1bac08,
# 0x1bac20 in build/out/wasm-map/vota_web/vota_web_wasm.map when SorteiaTeclasTesteTeclado moved to ctesteteclado.cpp;
# it held them after the statics before), which fits the reading that clang lays a file's globals out by first use.
# In ctesteteclado.cpp, GetInst, the statics and the D0 above StartState (record :38), the constructor (no index)
# below ProcessInput's blank record lines 50, 60 and 81, GeraSequencia above the macro (its static std::mt19937,
# @1835152, lies below the macro's mutex in .bss), SorteiaTeclasTesteTeclado and AdicionaCaixaTecla last (the two in
# either order gave the same object, on the scratch copy above); api/gui/ctextbox.h and
# api/gui/cinteractiveform.h moved into ctesteteclado.h, whose members name both, to keep StartState's record lines.
# Other lines chosen.
# No roots and no -pending.cpp: fns 940 and 3854 have their second target caller in the link (ProcessInput, 11804,
# calls both; fn 5982, unit 37's, calls 940), so the stand-ins that gave them one went.
CTESTETECLADO_SRCS := src/app/vota/eleitor/iniciovotacao/testeteclado/cerrotestetecladofim.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/cenviarmanutencao.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/ctestefalhou.cpp \
    src/app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp
UENUX2_SRCS += $(CTESTETECLADO_SRCS)
