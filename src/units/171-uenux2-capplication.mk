# uenux2 api::CApplication (api/gui/capplication.cpp, the records' file), in part, in a header of a chosen path
# (api/gui/capplication.h): EnterLoopDoingNothing (target fn 5566), with the two statics it reads; InitApplication (fn
# 11159, written and not matched, below) with its local facet's do_decimal_point (fn 11156); PushContext (fn 3684) and
# CriaContexto (fn 676), over unit 193's context stack; the statics InitApplication writes and their static destructors
# (fns 11160 to 11163); GetDescricaoModo (fn 5564), written and not matched (below), with the two statics it reads.
#
# Evidence and choices.
# - The record capplication.cpp:503:32, `static void api::CApplication::EnterLoopDoingNothing()`, gives the class, the
#   name, the static and the line; column 32 is the start of the CPolySingleton<IScreen>::instance() call whose default
#   argument makes the record. How the 31 characters before it are shared out is chosen (a local auto& screen).
# - The body: has<IScreen> (3387) and instance<IScreen> (512), both matched, then IScreen's slot 37 (vtable offset 148:
#   api/gui/iscreen.h's Slot37, a chosen name there); CSystem::Dorme(1000) (api/util/csystem.h); a loop over a byte at
#   .bss 1839209 and a word at .data 1577212. Their widths are the bytes' (a byte tested for non-zero, a word compared
#   signed with 0 whose initial bytes are ff ff ff ff); their names, the bool and int types and the initializer's
#   spelling are chosen (the header says so). InitApplication (fn 11159) stores -1 into the word and fn 11151 (read as
#   holding EnterLoopBeeping inlined, not written) reads both with the same test.
# - The loop: the target tests the byte alone before the first pass, and after each pass the byte first and then the
#   word. Measured on the object at the tree's flags, calls and relocations masked (how-to step 3): `if (!s_finalizar)
#   { do { ... } while (!s_finalizar && s_codigoRetorno <= 0); }`, the form written, gives the same code as
#   `while (!s_finalizar) { ...; if (s_finalizar || s_codigoRetorno > 0) break; }` and as the same with `return`; other
#   code: `while (!s_finalizar && s_codigoRetorno <= 0)`, which tests the word before the first pass too, and
#   `while (!s_finalizar) { ...; if (s_codigoRetorno > 0) break; }`, which tests the word first after each pass and masks
#   the byte with 1.
# - Names. 5566 is named by its record (srcloc-anchor). Its two statics take hand lines in splat/symbol_addrs.txt
#   (callers+content, each listing the other target functions that read the address): the byte's generated line,
#   vote:2 by:5566, is that match's own vote over .bss zeros, which reference/splat.md 3 ("No circular evidence")
#   refuses, and the word is .data, which an anchor does not vote for and whose bytes occur 65+ times, too often for
#   content to place it. Weighed on copies of the symbol file and match list (two splat-scan passes, then splat-build):
#   either line out, or both, takes 5566 out of match and moves no other row; the build, with 5566's line out of the
#   match copy, gives the target's sha256 each way, and a control that removes nothing keeps 5566.
# - InitApplication: its name, its class and its parameter types are the typeinfo name of its local class
#   (ledger/strings.tsv, 519992), which mangles the fourth parameter `15ELogAplicativos`, a type of the global namespace:
#   api/uelog/cescritorlog.h now declares ELogAplicativos there, with a using-declaration in api, which gives
#   cescritorlog.cpp.o, cloga.cpp.o, cwasmlogd.cpp.o, ieventoslog.cpp.o, cmonitoraalimentacao.cpp.o, clogvota.cpp.o and
#   cthreadmonitor.cpp.o the same code and data with their symbols renamed (the disassembly with names and offsets
#   masked, and the data bytes, against the objects of the branch's base); fns 433 and 10260 keep their matches under
#   the new names. That it is a static member is chosen (it uses no this). The body, in the target's order: the three
#   strings assigned to the statics at .bss 1839168, 1839180 and 1839192 (std::string's copy assignment inlined), -1 to
#   s_codigoRetorno, the fourth parameter to the word at 1839204, then
#   std::locale::global(std::locale(std::locale(), new commaAsDecimalSeparator)), whose libc++ code binaryen inlines
#   (locale::global, __install_ctor: the landing pads are libc++'s), then the stack cleared (the vector's clear inlined,
#   ~CApplicationContext called) and the first context pushed. The two stores after the strings are written in the
#   other order, measured: written s_codigoRetorno first, our link stores the word ahead of -1 and 11159 scores 87 over
#   665 rows (3 inserted, 3 deleted).
#   The local facet derives from std::numpunct<char> and overrides do_decimal_point to return ',' (fn 11156, `push 44`,
#   slot 3 of its vtable); its D0 is a twin of numpunct<char>'s, and the match of fn 5563 is renamed to it.
# - PushContextoInicial (a chosen name) has no target index: its one caller is InitApplication, and binaryen inlines it
#   there (a second prologue, 80 bytes, holding the two strings it takes by value and moves into CriaContextoPadrao, fn
#   5558). It reads no state of the class, so it is a free function in api (how-to step 3), declared in this file ahead
#   of InitApplication: both are chosen. Its external linkage is measured: file-static, clang inlines it into
#   InitApplication (the object holds no PushContextoInicial, and InitApplication grows from 385 rows to 489), where the
#   target's 11159 holds it as binaryen's second prologue. As a private static member of CApplication it gives the same
#   object code (the objects' functions compared, relocations as symbols).
# - PushContext (fn 3684) takes the context by value and moves it into unit 193's Push, which binaryen inlines (unit
#   193's fragment has the measurement). CriaContexto from a kind and three strings (fn 676) builds the context with
#   CriaContextoAplicacao (fn 3682) and calls the private CriaContexto from a context, which binaryen inlines into it
#   and which returns the guard built on s_contextos by its constructor's C1; unit 193's fragment has why these are
#   factories.
# - The statics' names and types beyond their widths are chosen (the header says so), and so is their place in the file;
#   their order follows the target's .bss (a reading: our link lays a file's .bss statics out in definition order),
#   except s_finalizar, defined first (chosen); s_contextos is unit 193's stack, at .bss 1839212. Names: InitApplication
#   by vptr-anchor (the local facet's vptr), PushContext and CriaContextoPadrao by its call, CriaContexto by
#   srcloc-anchor (the guard's record, which it holds inlined); the three strings by 11159's votes, which hold through
#   their static destructors' matches, and s_contextos by 676, 3684, 11159 and 11160. The word at 1839204, s_aplicativo,
#   has only its generated line, vote:1 by:11159 (below).
# - InitApplication's locale code releases libc++ rows: 987 (locale::operator=, whose result locale::global reads),
#   7826 (locale::__imp's constructor from a locale and a facet), 7827 and 4691 (the facet vector's operator= and
#   __recommend), 1504 (ios_base::imbue, a caller of 987), and 12020, 2292 and 7825, whose callees now have names.
# - The roots file stands for 5566's two target callers (7709, 7710) and for the callers of PushContext, CriaContexto
#   and the guard's destructor that are not reconstructed (its header lists them), and with DescreveModo for 4620,
#   5564's caller beside 502 (unit 31), which is not written. InitApplication needs no line: main (fn 10307, unit 170)
#   passes its table slot to invoke_viiii.
# - GetDescricaoModo (5564) and s_modo and s_demonstracao: api/gui/capplication.h has the evidence and the choices. In
#   the whole link 5564 scores 8 over 75 rows, every one an operand of a call or of data (pnpm wasm score), and its row
#   is `no-candidate`: no evidence names it while 502, whose records would anchor it, differs, and 4620 is not written.
#   Named, it would still wait: its .bss byte at 1839208 has no reader but 5564 (docs/reference/splat.md 3, no hand
#   line for it), and its .data word, 48, holds one non-zero byte, too little for content to place it, until 7787, the
#   word's other reader, is written.
# - Lines: 503 is the record's; 303 (QRCodeSRC::build), 377 (ShowExceptionMsgScreen), 432 (LogExceptionMsg) and 478
#   (EnterLoopBeeping's lambda) are records of functions not written and stay blank. Every other line, the statics' place
#   in the file, the order of the definitions but GetDescricaoModo's (after EnterLoopDoingNothing, the uses-2 band's
#   order) and the include order are chosen.
#
# Written and not matched:
# - 11159, InitApplication. The scan reads it `unresolved self-voted` on its store of the fourth parameter to the word
#   at .bss 1839204: the word's one line is 11159's own vote, and reference/splat.md 3 ("No circular evidence") holds a
#   .bss name that one body votes for alone only through a second match that uses it. No other target function reads or
#   writes the word: an i32.const, a memarg offset, or a constant plus the offset of a load or store within six rows
#   after it, that reaches 1839204 to 1839207 is in 11159's piece alone (build/out/splat/pieces/asm), no data word of
#   the target holds an address from 1839200 to 1839215, and no record names it. So it waits for a rule that places such
#   a static without a second user, by the other statics of its object as a _ZGV guard is placed by its object
#   (docs/reference/facts/splat.md S13); our link keeps the target's distance from the three strings (36 B after
#   s_aplicacao, 12 B after s_versao) but not from s_contextos (4 B before it, the target 8 B;
#   build/out/wasm-map/vota_web/vota_web_wasm.map against the symbol file). The body stays: main (fn 10307, unit
#   170) passes its table slot to invoke_viiii, and its votes name the three strings and CriaContextoPadrao
#   (their lines' by:11159 in splat/symbol_addrs.txt).
#
# Not written:
# - 3683, EnterLoopBeeping's lambda (record 478:13). Its one caller, 11151, fills a slot of the vtable of libc++'s
#   __async_assoc_state over a lambda of ShowExceptionMsg (ledger/vtables.json) and calls it three times in a loop over
#   the same two statics, read as EnterLoopBeeping inlined there: it waits for ShowExceptionMsg, and so do that
#   __async_assoc_state's other slots (5560, 5561, 11151).
CAPPLICATION_SRCS := src/api/gui/capplication.cpp
UENUX2_SRCS += $(CAPPLICATION_SRCS)
$(ROOT)/$(APP)/171-uenux2-capplication-roots.o: $(ROOT)/src/units/171-uenux2-capplication-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/171-uenux2-capplication.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/171-uenux2-capplication-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/171-uenux2-capplication-roots.o
