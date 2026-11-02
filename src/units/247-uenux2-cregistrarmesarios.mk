# uenux2 comum: the voter's screen of the poll workers' registration (target fn 1255, "REGISTRO DE MESÁRIOS") in
# app/comum/comparecimentomesario/estados/cregistrarmesarios.cpp, and what keeps api::CFormBuilder::GetForm(const
# std::string&) (fn 11140) out of line: a second copy of the screen, comum::IPedeTituloMesario::GetTelaEleitor, in unit
# 71's ipedetitulomesario.cpp. 11140 is written in unit 31's cformbuilder.cpp; with it in the link binaryen forms fn
# 6117, the shared body of 11140 and vota::GetFormulario (fn 886, unit 165), and 886 becomes its thunk, as in the
# target. Paths relative to src/uenux2.
#
# Target fns matched: 1255 (comum::TelaRegistroMesarios, the one body of both copies), 11140, 6117 and 886.
#
# Evidence:
# - 1255: the status header with the fields 7 (fn 502's bits: date and time, mode, battery icon), then two
#   api::CFixedText fields through fn 202, "REGISTRO DE MESÁRIOS" at (320, 150) with the SFont {35, 0} @540572 and "Siga
#   as instruções no terminal do mesário." at (320, 250) with {25, 0} @540580, alignment 2 (ALINHAMENTO_CENTRO),
#   colours 2 over 1, then 11140 with an empty name, whose temporary gets two byte stores (its NUL and its size), as
#   `""` gives. Only 1255 reads the fonts (/usr/bin/grep -rlE 'i32\.const (540572|540580)($|[^0-9])'
#   build/out/splat/pieces/asm prints comum/1255.wat); they lie between comum::CRegistrarMesarios's typeinfo name
#   (@540542, 29 bytes with its NUL, then one of alignment) and comum::CPedeTituloMesario's (@540588;
#   ledger/strings.tsv). clang puts a file's constants before the typeinfo name of the class whose key function the
#   file defines, and after it only constants that file-internal code alone reads (a probe at the uenux2 flags,
#   wasm-objdump -x of its data segments), so the order fits cpedetitulomesario.cpp with ordinary constants at least as
#   well as cregistrarmesarios.cpp, which it fits only with file-internal fonts (both copies in that file): the file is
#   a choice the data leave open. cregistrarmesarios.cpp's one record (line 68, CRegistrarMesarios::GetControlador,
#   which fns 10391 and 10392 hold inlined) stays a blank line.
# - 11140: `f6117(p0, p1, p2, 1577960, 1577896)`, the vptrs of CPreShowClearScreen's __shared_ptr_pointer block and of
#   api::CPreShowClearScreen, whose vtable and typeinfo lie in cformbuilder.cpp's data (cpreshowclearscreen.h); 6117
#   news the pre-show and the block and calls fn 5550, GetForm(preShow, nome). 886 passes vota::CPreShowFormVota's two
#   vptrs the same way.
# - Two functions for 1255: fn 1255 is 11140's one caller (pnpm wasm fn: `callers (1): 1255`) and 11140 is in no
#   table slot (wasm-objdump -x -j Elem target/vota_web_wasm.wasm prints no ref.func:11140), yet it keeps its body, and
#   binaryen inlines a function with one call site and no slot (docs/reference/facts/tool-traps.md X1). So two bodies
#   called it when the inlining pass ran; that duplicate-function-elimination joined them after that pass is a reading
#   (X1's "a surviving twin that its callers became"). Measured in the whole link (TMPDIR=/tmp make -C src link,
#   tools/round/link-map.sh, then build/out/wasm-map/vota_web/names.tsv and pnpm wasm score at the default depth):
#   - TelaRegistroMesarios alone, with its stand-ins: names.tsv has no GetForm(const std::string&) and no
#     byn$mgfn-shared$ of GetFormulario; 1255 scores 95 over 321 rows (57 inserted) and 886 59 over 63 (55 inserted);
#   - with a second, identical free function in the same file, each called twice: names.tsv has no GetForm(const
#     std::string&) and no shared body either, and holds one of the two only (they are one body before the inlining
#     pass);
#   - with the second copy a member that does not read `this` (in this file, of a class declared for the measurement,
#     or as written, in ipedetitulomesario.cpp), each called twice: names.tsv holds GetForm(const std::string&),
#     TelaRegistroMesarios and byn$mgfn-shared$ of GetFormulario, and no GetTelaEleitor. The image's wasm-opt -Oz runs
#     duplicate-function-elimination first, then dae-optimizing, inlining-optimizing, duplicate-function-elimination
#     again and merge-similar-functions (BINARYEN_PASS_DEBUG=1 wasm-opt -Oz in urna-emsdk:6.0.0 prints them as passes 1,
#     45, 46, 47 and 49); that dead-argument elimination's dropping the unused `this` is what makes the two one body
#     only after the inlining pass is a reading. A probe of four objects linked at -Oz gave the same: a free
#     function and a member of that body, each called twice, leave one body that calls an out-of-line GetForm; the free
#     function alone, none.
#   Each copy needs two call sites when binaryen inlines, or it is inlined into its one caller with 11140's call, and
#   11140 would end with two callers: in the target all ten call sites of 1255 (ledger/callgraph.tsv) call it.
# - In this link, before steps 7 to 9, every row of 1255 (21 over 264), 11140 (3 over 8), 886 (3 over 8) and 6117 (3
#   over 63) that differs is operand-only, a call or a data address (pnpm wasm score; its `~` rows less `call fn:` and
#   `data:` print nothing). Step 8 names 11140 by vptr-anchor and 6117 by the calls of 886 and 11140; 1255 has no line
#   in splat/symbol_addrs.txt. Step 9's first scan found it by its content (scan source `content`, detail `address
#   same-content`), a rescan reads `symbol`; no other target body equals ours, no other target function loads its two
#   strings (/usr/bin/grep -rlE 'i32\.const (324002|365472)($|[^0-9])' build/out/splat/pieces/asm prints
#   comum/1255.wat alone), and none of its target callers is written.
# - Band: 11140 is in use band 1 of cformbuilder.cpp.o right after 11139 (CPreShowClearScreen::PreShow), and its
#   ld_index (4508) is below 11139's (4514), as docs/how-to-decompile.md step 3 wants.
# - The stand-ins that stood for 11140, CPreShowClearScreen's vtable builder in unit 158's roots and its control block's
#   SBloco in unit 102's, went: cformbuilder.cpp.o, first in the link, now emits 11139 and 11138.
#
# Chosen, no evidence names them: TelaRegistroMesarios, its being a free function of comum, and its header's path,
# cregistrarmesarios.h, beside the .cpp; that the second copy is IPedeTituloMesario's protected non-static member
# GetTelaEleitor, the one form measured (another function of the same body with a parameter dead-argument elimination
# drops would read the same, not measured); which target callers call which copy (the three derived constructors of
# IPedeTituloMesario, inlined into fn 10388, call GetTelaEleitor; the constructors of the states over comum::CAppState,
# in fns 3610, 5386, 5389, 10313 three times and 10337, call TelaRegistroMesarios). At 10388's three sites the target
# calls 1255 before IPedeTituloMesario's constructor (fn 3608) runs on the new state, so the chosen calls there run a
# member before its base subobject exists, undefined behaviour ([class.base.init]); the parameter form above, not
# measured, would not. The other seven sites call 1255 in a constructor body, after the state's vptr store. Chosen as
# well: the fonts' names and their being
# external constants of cregistrarmesarios.cpp, which the second copy reads (the target holds one pair);
# GetForm(const std::string&) as an overload, its name and its place after the first GetForm; the lines of what
# cregistrarmesarios.cpp defines, after line 68. Which copy names fn 1255's match line is our link's: the one binaryen
# kept is TelaRegistroMesarios, whose object links first (ld_index 4466, ipedetitulomesario.cpp.o's functions 5228 to
# 5231).
#
# Not written, and what each waits for: comum::CRegistrarMesarios (GetInst 3610, StartState 10392, ProcessInput 10391),
# CConfirmaFimRegistroMesarios::GetInst (5389), CLimiteMesariosRegistradosAtingido::GetInst (5386) and
# IPedeTituloMesario::ProcessInput (10313, trapped in unit 71) build the operator's form with fn 395, matched (unit 31),
# so they wait only to be written (10313 calls 5389 too); vota::CFimAquisicaoVotos::StartState (10737, trapped in unit
# 104) calls 3610 and fn 501 (written, `differs`).
#
# The generic uenux2 rule depends on the source and every uenux2 header.
CREGISTRARMESARIOS_SRCS := src/app/comum/comparecimentomesario/estados/cregistrarmesarios.cpp
UENUX2_SRCS += $(CREGISTRARMESARIOS_SRCS)
# no target caller of either copy is written: 247-uenux2-cregistrarmesarios-roots.cpp stands for them
$(ROOT)/$(APP)/247-uenux2-cregistrarmesarios-roots.o: $(ROOT)/src/units/247-uenux2-cregistrarmesarios-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/247-uenux2-cregistrarmesarios.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/247-uenux2-cregistrarmesarios-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/247-uenux2-cregistrarmesarios-roots.o
