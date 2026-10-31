# uenux2 simulador::CWasmThread, the wasm build's api::IThreadImpl, in
# src/uenux2/mock/app/simulador/wasm/cwasmthread.cpp (+ cwasmthread.h), with the three wrappers of EM_JS functions in
# wasmjs.cpp (+ wasmjs.h). Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the
# source and every uenux2 header.
#
# CWasmThread:
# - Wait (target fn 9652, slot 3) and Yield (fn 9651, slot 5) match, with the global destructor of s_contextos (fn 9662,
#   table slot 494). s_contextos's name is a vote of 9652, and 9652 and 9662 hold each other as a self-voted name needs
#   (docs/reference/splat.md "No circular evidence"). What else ties the operand to the object: 9652, 9655 and 9662 are
#   the only target functions that load 1832648 and 1832652, and 9655 and 9662 the only ones that load 1832656.
# - Create (fn 9655, slot 2) is written and `unresolved`. -O2 inlined its std::string appends, which stay calls in the
#   target (249 over 458 rows, 160 inserted); the tree's -O3 keeps them, and it waits for a name of s_proximoId
#   (1832660): only 9655 loads it, so that name needs a second user even once 9655's `vtable` pair is the same
#   instructions and votes (docs/reference/splat.md "No circular evidence"). In a scratch
#   link with the simulator's three objects at -O3, and at the tree's -O3, it scores 79 over 313 rows, 46 of them operand-only, most of the rest
#   other locals in the vector's growth. Its throw is on its record's line, 31:15. `emplace_back` is measured, not free:
#   `push_back`, whose body is target fn 543, leaves a call and a frame slot for the pointer at both levels (172 over
#   305 rows at -O3, measured with the vector file-static); the target has no such call or slot.
# - slot 4 is the empty 1528, one body with CWasmNullPaper::PrintText's and others', so its match line is not this
#   class's; slots 0 and 1 are the shared 174 and 144. The factory that builds the class is the executable TU's, not
#   reconstructed.
# Evidence: the class and its base (RTTI), Create's name and file (the record). Chosen: the names Wait and Yield (from
# the text they log), Slot4 and the int parameters that fill its wasm type, SContextoThread and its members (16 bytes, a
# 32-bit read of +8, the id at +12), m_contexto, and that s_contextos and s_proximoId are static members. A file-static
# std::vector is not free: once emplace_back inlines into this TU, LLVM's GlobalOpt splits an internal global into `.0`,
# `.1`, `.2`, and the vote names the pieces, not the object, which costs 9652 and 9662. Forms that give the same
# functions (the object's disassembly, object-local numbers masked; Wait, Yield and the destructor): `!contexto` for
# `contexto == nullptr`, `!contexto->concluido` for `== 0`, a for loop for the while, `auto*` for the local's type, and
# s_proximoId with no initializer. Not free: `s_contextos.erase(std::remove(...), end())`, and reading m_contexto
# throughout instead of the local (Wait differs in both).
#
# wasmjs.cpp: EmitEvent (target fn 3533, 22 B), PushKey (9649) and ConsoleError (9646), each a call of one EM_JS
# function with a string's c_str(). What the target shows: each is that import's only caller (`awk -F'\t' '$2==96'
# ledger/callgraph.tsv` for js_emit_event), the executable TU reaches all three by `invoke_*` through table slots 59,
# 105 and 104 (fns 7840, 10384, 10619 and 10857 pass 59, 10703 passes 105, 10857 passes 104), and 9018 and 9022, in
# cwasmscreen.cpp, call 3533 directly. That direct call is what puts it outside cwasmscreen.cpp: defined there, clang
# inlines it and CWasmScreen::Refresh calls js_emit_event itself (measured on the object; docs/how-to-decompile.md step
# 3). So the file is another TU's, and which one is a choice. The glue lists EM_JS functions in link order of their
# sections, and js_emit_event, js_push_key and js_console_error come after cwasmthread.cpp's js_thread_log and before
# js_wasm_web_sound_play_wav, while no vtable or record lies between those two objects' data: an object of its own
# between them, or the end of cwasmthread.cpp, or the head of cwasmwebsound.cpp, all fit. A file of its own is chosen,
# since Create's record at line 31 leaves cwasmthread.cpp little room above it; our link's order of the objects is not
# the target's. Chosen too: every name, wasmjs.* as the path, namespace simulador, and that the wrappers take const
# char* for the event's name (a literal in both callers). `.data()` for `.c_str()` gives the same three functions.
# EmitEvent has one caller in our link (9018 is a trap), and the roots' address keeps it out of line: binaryen inlines a
# function for having one call only when the table does not hold it (the target's table does, slot 59).
CWASMTHREAD_SRCS := mock/app/simulador/wasm/cwasmthread.cpp mock/app/simulador/wasm/wasmjs.cpp
UENUX2_SRCS += $(CWASMTHREAD_SRCS)
# nothing reconstructed builds a thread or calls the wrappers from the executable TU yet:
# 99-uenux2-simulador-wasm-cwasmthread-roots.cpp keeps them (see the file header)
$(ROOT)/$(APP)/99-uenux2-simulador-wasm-cwasmthread-roots.o: $(ROOT)/src/units/99-uenux2-simulador-wasm-cwasmthread-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/99-uenux2-simulador-wasm-cwasmthread.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/99-uenux2-simulador-wasm-cwasmthread-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/99-uenux2-simulador-wasm-cwasmthread-roots.o
