# uenux2 comum: the voter's screen of the poll workers' registration (target fn 1255, "REGISTRO DE MESÁRIOS") in
# app/comum/comparecimentomesario/estados/cregistrarmesarios.cpp, and what keeps api::CFormBuilder::GetForm(const
# std::string&) (fn 11140) out of line: a second copy of the screen, comum::IPedeTituloMesario::GetTelaEleitor, in unit
# 71's ipedetitulomesario.cpp. 11140 is written in unit 31's cformbuilder.cpp; with it in the link binaryen forms fn
# 6117, the shared body of 11140 and vota::GetFormulario (fn 886, unit 165), and 886 becomes its thunk, as in the
# target. The same file holds comum::CRegistrarMesarios, the state that asks whether to register the poll workers
# (its paragraph below). Paths relative to src/uenux2.
#
# Target fns matched: 1255 (comum::TelaRegistroMesarios, the one body of both copies), 11140, 6117 and 886;
# CRegistrarMesarios::GetInst 3610 with its constructor and its operator's form, StartState 10392, and its statics' exit
# destructors 10394 (s_inst) and 10393 (s_mutex).
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
#   which fns 10391 and 10392 hold inlined) is GetControlador's return, as written below.
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
#   comum/1255.wat alone), and none of its target callers was written then. Two are now, 3610 below and 5386 (unit
#   135), and step 8 names 1255 by their calls (`evidence:call by:3610,5386`).
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
# cregistrarmesarios.cpp defines, but for line 68's record. Which copy names fn 1255's match line is our link's: the one binaryen
# kept is TelaRegistroMesarios, whose object links first (ld_index 4466, ipedetitulomesario.cpp.o's functions 5228 to
# 5231).
#
# comum::CRegistrarMesarios (RTTI: si_class of comum::CAppState; vtable @1593584 [448, 765, 10392, 7480, 1661, 218, 425,
# 10391, 425]), the 28-byte object of the 19 states over the destructors 448 and 765 (unit 135's fragment has that
# evidence: final, +12 the operator's form, +20 the voter's), written in cregistrarmesarios.cpp around its record.
# Evidence, from the target's bodies (pnpm wasm fn):
# - GetInst (3610) is the project's singleton, as unit 135's CEncerraRegistroMesarios::GetInst (5388): the test of s_inst
#   (@1909428), new of 28 bytes, the old object deleted by a direct call of the D2 448 and free, then the unlock of
#   s_mutex (@1909404) through fn 150. The two statics are read by 3610 and destroyed by 10394 (`f763(p0, 1909428)`)
#   and 10393 (`f150(1909404)`), and no other target function loads either address (/usr/bin/grep -rlE
#   'i32\.const (1909428|1909404)($|[^0-9])' build/out/splat/pieces/asm prints those three); step 8 names them by 3610's
#   votes, and 10394 and 10393 match with them. 3610 alone stores the vptr 1593592 (the grep for 1593592 lists
#   comum/3610.wat alone).
# - The constructor is a function of its own that binaryen inlined into GetInst: its 16-byte frame opens after the new.
#   It calls fn 224 with 2 (EVENTO_ENTRADA), stores 0 at +12, the vptr, 0 at +20 (the members default-initialized, a
#   reading), then moves TelaRegistroMesarios()'s result (fn 1255, into the frame) into +20, and the operator's form
#   into +12, as assignments in the body.
# - The operator's form is built behind a 48-byte frame of its own inside the constructor's: the builder through fn 203,
#   AddBuzz(51, 10) (fn 941), "Registrar mesário?" (18 bytes @335654) at the point word 65537, {1, 1}, and "CORRIGE:
#   Cancelar  CONFIRMA: Prosseguir" (39 bytes @86416) at 262145, {1, 4}, both through fn 180 with alignment 0,
#   AddInputControl (fn 395), GetInteractiveForm with an empty name and 1 (fn 301) into the constructor's frame, then
#   the builder's vector destroyed in line. A frame of its own is binaryen's inlining of an out-of-line function with
#   one caller (docs/reference/facts/reading.md R10), and the linkage decides it: compiled with the builder in an
#   anonymous namespace, clang inlines it into the constructor (wasm-objdump -d of a scratch copy at the directory's
#   flags: the constructor makes the builder's calls itself), and with external linkage the constructor keeps the call,
#   which binaryen inlines in the link. So TelaIndagaRegistroMesarios has external linkage.
# - StartState (10392): `m_pNextState = this`, then three calls through GetControlador (each with the record
#   cregistrarmesarios.cpp:68:12, instance()'s default argument): the controller's slot 23 (+92,
#   LogaIndagaRegistroMesarios in icontroladorregistramesarios.h), slot 5 (+20) and slot 7 (+28, whose result it
#   tests); when slot 7 returns true, the next state is CLimiteMesariosRegistradosAtingido::GetInst() (fn 5386, unit 135), else both forms'
#   slot 2, the voter's (+20) first. Written with an early return; an if/else gives the same function (wasm-objdump -d
#   of the two objects, object-local numbers masked).
# - Measured in this link before steps 7 to 9 (pnpm wasm score at the default depth): 3610 `32 over 425 rows (same 393,
#   replaced 32 [32 operand-only], inserted 0, deleted 0)`, every row that is no call and no data address one of the
#   statics' addresses; 10392 `10 over 83 rows (same 73, replaced 10 [10 operand-only], ...)`, calls and data only.
# - Band: 10394, 10393 and 10392 share use band 1 and their ld_index runs 5017, 5018, 5019 in names.tsv (the higher
#   index first, as docs/how-to-decompile.md step 3 wants): s_inst, then s_mutex, then StartState, as written.
# Pending: ProcessInput (10391), a thunk into binaryen's fn 6011, whose other caller is CMesarioRegistrado::ProcessInput
# (10338, not written); 6011 forms only with both written, and its callee 5389 (CConfirmaFimRegistroMesarios::GetInst)
# has no body in this tree. 247-uenux2-cregistrarmesarios-pending.cpp traps it and gives its source.
# Chosen, no evidence names them: TelaIndagaRegistroMesarios, its being a free function of comum and its declaration in
# cregistrarmesarios.h; the order of the definitions (destructor, constructor, the form's builder after it, GetInst, the
# statics, StartState; the other order of constructor and builder was not measured); the destructor out of line and
# declared first, as the key function, as unit 135's states do; the data members' names (unit 135's); the controller's
# slot names Slot5 and Slot7 (its header's).
#
# Not written: nothing else of this class (ProcessInput is pending, above). CConfirmaFimRegistroMesarios::GetInst (5389,
# unit 135) and IPedeTituloMesario::ProcessInput (10313, unit 71, which calls 5389 too), which build the operator's form
# with fn 395 (matched, unit 31) too, match.
#
# The generic uenux2 rule depends on the source and every uenux2 header.
CREGISTRARMESARIOS_SRCS := src/app/comum/comparecimentomesario/estados/cregistrarmesarios.cpp
UENUX2_SRCS += $(CREGISTRARMESARIOS_SRCS)
# target callers of the screen's two copies and of 3610 that are not written: 247-uenux2-cregistrarmesarios-roots.cpp
# stands for them
$(ROOT)/$(APP)/247-uenux2-cregistrarmesarios-roots.o: $(ROOT)/src/units/247-uenux2-cregistrarmesarios-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/247-uenux2-cregistrarmesarios.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/247-uenux2-cregistrarmesarios-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/247-uenux2-cregistrarmesarios-roots.o
# CRegistrarMesarios::ProcessInput (fn 10391) is not reconstructed: 247-uenux2-cregistrarmesarios-pending.cpp gives the
# vtable a trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/247-uenux2-cregistrarmesarios-pending.o: $(ROOT)/src/units/247-uenux2-cregistrarmesarios-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/247-uenux2-cregistrarmesarios.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/gui/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/247-uenux2-cregistrarmesarios-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/247-uenux2-cregistrarmesarios-pending.o
