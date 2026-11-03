# uenux2: two platform classes of the wasm simulator, each in a file of its own under mock/app/simulador/wasm/, with the
# interface and data members they need:
# - simulador::CWasmInit (cwasminit.cpp, cwasminit.h), over comum::IInterfaceInit: Slot4 (target fn 9418, slot 4, the
#   key function), the implicit deleting destructor (9388, slot 1, which frees what IInterfaceInit's out-of-line D2,
#   5898, returns), and EnviarMensagem (9405, slot 5): a switch over the message's low 16 bits that answers with a
#   one-element std::vector<int> and logs each answer through the file's Loga (fn 1524), which formats
#   "CWasmInit::{} {}" and writes it to channel 0 of simulador::CWasmCanaisLog (unit 141). Slots 2, 3, 6 and 7 are
#   shared bodies (434, 434, 340, 425). 9405 is named by vtable alone, so no vote names 1524; the scan's content pass
#   finds it (a `callers+content` hand line, weighed as docs/reference/splat.md "Reviewing a match" says, carried
#   nothing), once 5152, which it calls, has its name (unit 141's fragment).
#   Loga builds CWasmCanaisLog's static through the inline GetInst, so this object also emits the static's destructor,
#   fn 5154 (unit 141's fragment), and std::deque<std::string>'s D2, fn 3503, which that destructor calls.
# - simulador::CWasmResource (cwasmresource.cpp, cwasmresource.h), over api::IResource, whose slots 2 to 6 this unit
#   declares (api/gui/iresource.h): GetImage (8633, slot 2), GetFile (8611, slot 3), GetMovie (8605, slot 4, below),
#   Exists (8600, slot 5) and IsResource (8591, slot 6); the file-static helpers ComMulher (4996) and Le (3452), and
#   Caminho (2626), with Normaliza, Candidatos and Existe, which clang inlines into Caminho, and TamanhoImagem, which it
#   inlines into GetMovie. The std::ifstream of Le and Existe brings libc++'s basic_filebuf<char>::open (2145), which
#   matches from libc++.a. Written and not matched: Caminho (2626), below.
# - api::CFixedImage (api/gui/cfixedimage.h): its vector member, GetData (4975, already matched as an RHVoice twin; its
#   line is renamed to this class's) and the implicit destructors, which binaryen merges into the shared bodies the
#   target has: 8563 and 8554, the D2 and D0, are thunks of 3937 and 3936, whose two match lines are renamed to this
#   class's too. The vector constructor GetImage inlines has no target function: it is compared with nothing.
# - api::CMovieFrame's constructor (api/gui/cmovie.cpp, unit 23's file), which GetMovie calls.
#
# Where the code is. No record names a file of either class. That each has an object of its own is the data's:
# CWasmInit's vtable and typeinfo (1528764, 1528804) lie between simulador::CWasmNullTextToSpeech's and CWasmScreen's,
# and CWasmResource's (1530176, 1530212) between CWasmInputMT's and the std::__shared_ptr_emplace<api::CFixedImage> and
# CFixedImage vtable (1530224, 1530264) that its slot 2 instantiates; the names cwasminit.cpp and cwasmresource.cpp are
# the classes' in lower case, the class-convention guess ledger/tu-clusters.tsv gives stretches 207 (9405, 9388) and 91,
# 97, 100 and 108 (8591, 8600, 8605, 8633): chosen. The order of the members in each file is their use band's (Slot4
# before EnviarMensagem, CWasmResource's slots in slot order). The helpers take no `this`, so they are free functions;
# their linkage (file-static) and where they sit in the file are chosen: each is alone in its use band (2626 uses 4,
# 3452 uses 3, 4996 uses 2). Each of the four slots that call Caminho is named by `vtable` alone, so nothing votes a
# name for 2626; its name is the hand edit under splat/symbol_addrs.txt's marker (`callers+content`, the callers and the
# literals only 2626 loads), and 8600, 8611 and 8633 match through it.
#
# GetMovie (8605): TamanhoImagem reads a GIF's width and height (the header's bytes 6 to 9) into two locals, each two
#   bytes joined little-endian, and returns a new SPoint of them. The target copies them with one `i32.load align=0
#   offset=6` and one `i32.store align=1 offset=52`: a 4-byte store at the SPoint's 2-byte alignment. Measured in the
#   object (GetMovie's disassembly, em++ at the tree's flags, the rest of cwasmresource.cpp as landed): that form gives
#   the pair, and so do the two values read with std::memcpy into TPosition or uint16_t locals, or returned as `{...}`,
#   each the same function as the form written, which is a choice among them. The SPoint copied whole with one memcpy
#   gives `i32.store 2 52`, 4-byte aligned (16 over 507 rows in the whole link at 441ae041, all operand-only); the
#   values stored into the SPoint's fields one after the other (a memcpy each, in either order, or each pair of bytes
#   joined), or read through a `const uint16_t*`, give two `i32.store16`, and assigned to the other cases' size locals
#   (one return for all cases) the one pair of `i32.store16` all cases share. A reading of the IR (-S -emit-llvm): the
#   form written loads the four bytes and the uint16_t memcpy form two 16-bit values, each before two 16-bit stores,
#   which the backend joins into one 32-bit load and store at the first store's alignment; the whole-SPoint memcpy is
#   an i32 store in the IR, for which LLVM raises the SPoint's alloca to 4.
#   Measured before, in the whole link: TamanhoImagem with external linkage stays a call (cost 395 against 250,
#   -Rpass-missed=inline) whose own store is 2-byte aligned, and binaryen then inlines it into GetMovie with a frame of
#   its own and the JPEG tests in another order, 135 over 526 rows. At -O2 clang left
#   std::vector<CMovieFrame>'s __init_with_size out of line (cost 230 against 225, -Rpass-missed), 172 over 562 rows.
#   std::vector<CMovieFrame>(1, ...) is inlined at -O2 and gives 41 over 518 rows, but 64 over 522 at -O3: of the two
#   forms tried, the initializer list is the one that gives the target's rows. That CMovieFrame's constructor is out of
#   line is read from 8605, which holds code as binaryen inlines a call (the moved vector stored to the frame and read
#   back, the member zeroed before it is overwritten: docs/reference/facts/reading.md R10); a CMovieFrame aggregate built
#   in GetMovie, with the vector moved through a local, gives 221 over 516 rows at -O3.
#
# Written and not matched:
# - Caminho (2626): 121 over 1920 rows (90 replaced, 83 of them operand-only, 20 inserted, 11 deleted) with each prefix
#   test through ComecaCom, which takes the prefix as a const std::string&, so each test builds and frees a std::string
#   of its literal; 200 over 1934 with the literal passed to rfind, the form before (202 at -O2, d4cbc1a, and 200 at
#   441ae041, this directory at strict aliasing). The target loads the path's size, its long-string flag and its data
#   again after each rfind, for the substr, and again before the second rfind: its body has 5 loads of the size (frame
#   +52), 5 signed and 1 unsigned of the flag (+59) and 6 of the data (+48). With the literal passed to rfind ours had
#   3, 2 and 2, and 4 (the link at 5ab3adc2, the function's disassembly); with ComecaCom 5, 4 and 2, and 6. In the
#   object's IR after GVN (em++ -S -emit-llvm -mllvm -print-after=gvn) the loads follow the prefix's operator delete;
#   that the delete is the write GVN does not look past is a reading. The object's function then has no allocation of
#   the prefix and as many calls as without ComecaCom, 47, and its search compares the literal's bytes as constants. What
#   differs now is where those loads sit: ours loads after the delete, before the test of rfind's result, and keeps the
#   values for the second search when the first fails (a phi in the object's IR); the target loads after that test, in
#   the substr's path, and again before the second search on both paths, which reads as the write sitting after the
#   test there. Measured on the object, each with ours' loads in ours' places: rfind(std::string(literal), 0) written in
#   the condition (the same function as ComecaCom's, the disassemblies' numbers masked), the prefix taken by value, and
#   -mllvm -jump-threading-threshold=10 or 20. The prefix as a named std::string in an if-with-initializer (destroyed
#   after the if) gives 3 loads of the size and 4 of the data. ComecaCom's name, its being a helper in the anonymous
#   namespace and its parameters' form are chosen. With the existence test written in the loop (an std::ifstream temporary in the condition) the frame's
#   shared slot sits at the bottom, 391 rows; Existe, the test as a helper, gives the target's frame. Scored the same,
#   200: a non-const path, the prefix test as a helper (ComecaCom). Further: Candidatos written into Caminho (928),
#   Normaliza into Candidatos (365), the normalised path as Candidatos' parameter (293). Counted in the object
#   (Caminho's disassembly, em++ at the tree's flags), loads of the size: 3 at -O2, with -fno-strict-aliasing, with
#   -mllvm -memdep-block-number-limit= 2, 5, 20, 50 or 100, with -memdep-block-scan-limit=5, with GVN off
#   (-opt-disable=gvn) or with its load PRE off (-enable-load-pre=false), and 1 at -Os; 3 with the substr as
#   std::string(caminho, 17), the prefixes as std::string_view, the test as a lambda, or a non-const path given to
#   push_back, and 4 with the images' substr written twice. What keeps the target from reusing the values is not found.
#
# EnviarMensagem: the cases and the answers are the target's (its br_table on the message less 6, and each block's
#   constants). The order of the case bodies is measured: in value order the blocks come out in another order (108 over
#   310 rows); in the order written, the target's, 26 over 278, all operand-only. 15 and 16, and 17 and 18, are two case
#   groups with one body each, and 7 a case of its own, as the target has a block for each (it passes 7 as a constant
#   there). The empty texts are `{}`: they zero 12 bytes, as the target does, where "" gives two byte stores (the
#   object's disassembly, relocated operands masked); std::string() gives the same object as `{}`. `mensagem & 0xFFFF`
#   is measured too: a cast to ueint16 gives another object. Loga's place in an anonymous namespace (as
#   cwasmresource.cpp's helpers), its name and its parameters' names are chosen; the int of its first parameter is the
#   format's argument type (3).
# Names and types. RTTI names the classes. The slots' names are chosen (iresource.h and cwasminit.h say from what), and
# so are the helpers', the data members', the constructors' parameters, GetImage's two int parameters, which no body
# reads, and that no member is const. "Mulher4", "resolve", "missing" and the paths are the target's literals. Paths
# relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2 header.
SIMULADOR_PLATFORM_SRCS := mock/app/simulador/wasm/cwasminit.cpp mock/app/simulador/wasm/cwasmresource.cpp
UENUX2_SRCS += $(SIMULADOR_PLATFORM_SRCS)
# the two vtables: fn 8302 (unit 188) builds both objects and stores them, so this unit has no roots
