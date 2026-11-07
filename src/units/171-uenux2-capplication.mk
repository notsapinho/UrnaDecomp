# uenux2 api::CApplication (api/gui/capplication.cpp, the records' file), in part, in a header of a chosen path
# (api/gui/capplication.h): EnterLoopDoingNothing (target fn 5566), with the two statics it reads; InitApplication (fn
# 11159, written and not matched, below) with its local facet's do_decimal_point (fn 11156); PushContext (fn 3684) and
# CriaContexto (fn 676), over unit 193's context stack; the statics InitApplication writes and their static destructors
# (fns 11160 to 11163); GetDescricaoModo (fn 5564), written and not matched (below), with the two statics it reads;
# api::Join (fn 1696), GetContexto (fn 1695) and api::GetExceptionLevel (fn 5569).
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
#   masked, and the data bytes, against the objects of the branch's base); fns 433 and 10260 kept their matches under
#   the new names (433's went later, with unit 100's calls of 11157: that fragment). That it is a static member is
#   chosen (it uses no this). The body, in the target's order: the three strings assigned to the statics at .bss
#   1839168, 1839180 and 1839192 (std::string's copy assignment inlined), -1 to s_codigoRetorno, the fourth parameter to
#   the word at 1839204, then
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
#   and the guard's destructor that are not reconstructed (its header lists them); 5564's two target callers, 502
#   (unit 31) and 4620 (unit 165), are both in the link and need no line. InitApplication needs no line: main (fn
#   10307, unit 170) passes its table slot to invoke_viiii.
# - GetDescricaoModo (5564) and s_modo and s_demonstracao: api/gui/capplication.h has the evidence and the choices. In
#   the whole link 5564 scores 8 over 75 rows, every one an operand of a call or of data (pnpm wasm score). Step 8 names
#   it by its call from 4620, which matches, and its row reads `unresolved self-voted` on its .bss byte at 1839208
#   (s_demonstracao, whose one line is 5564's own vote): no target function but 5564 reads the byte, so no second
#   match can hold the name and docs/reference/splat.md 3 allows no hand line for it. Its .data word (s_modo, 48) has
#   a line of 5564's vote too, which the scan does not refuse. It waits for the rule 11159 waits for (below).
# - Lines: 503 is the record's; 303 (QRCodeSRC::build), 377 (ShowExceptionMsgScreen), 432 (LogExceptionMsg) and 478
#   (EnterLoopBeeping's lambda) are records of functions not written and stay blank. Every other line, the statics' place
#   in the file, the order of the definitions but GetDescricaoModo's (after EnterLoopDoingNothing, the uses-2 band's
#   order) and the include order are chosen.
#
# - Join (fn 1696), GetContexto (fn 1695) and GetExceptionLevel (fn 5569), three helpers of vota::CThreadVota's two
#   TrataErro (7709, 7710, traps in unit 116's pending file), written after CriaContexto, their lines a choice;
#   capplication.h has what each does, its evidence and its choices. Their stand-ins are in this unit's roots. Measured
#   in the whole link (pnpm wasm score against our symbol, names.tsv after make -C src link-map):
#   - 1696 matches (the scan's content pass). Written as an iterator loop that tests `parte != partes.begin()`, it read
#     `32 over 305 rows (same 273, replaced 26 [26 operand-only], inserted 3, deleted 3)`: ours read the vector's end
#     again on each pass, the target holds it in a local. The range-for that compares the element's address with the
#     first's gives `20 over 302 rows`, every one an operand, and the match.
#   - 1695 matches, named by its call from 5569, the one caller of it with a name (step 8's `evidence:call`). It
#     copies the stack's last context into a std::optional<CApplicationContext> declared after the empty case and
#     returns the value moved out. The target builds that copy at +0 of its 80-byte frame and leaves +52 to +56
#     unused, under the two string temporaries at +56 and +68: read as a 56-byte object, the context and the optional's
#     flag, whose store and test fold away. The optional is the form written among those that give the same object
#     (below), a choice. Measured in the whole link: the plain local written before, `CApplicationContext contexto =
#     s_contextos.m_contextos.back(); return std::move(contexto);`, built the copy at +4 and read `15 over 142 rows
#     (same 127, replaced 13 [13 operand-only], inserted 2, deleted 0)`; the optional reads `13 over 140 rows (same
#     127, replaced 13 [13 operand-only], inserted 0, deleted 0)` and matches. Forms compiled at the tree's flags,
#     GetContexto read in the object (wasm-objdump -d, the copy constructor's this): the same object code as the form
#     written for the optional's value taken as `std::move(contexto).value()`, a temporary
#     `std::optional<CApplicationContext>(...).value()` returned, `*std::make_optional(...)` returned, and a
#     file-static helper that returns the optional (std::nullopt when the stack is empty) dereferenced after the empty
#     case; the copy at +24 with the optional declared first and tested for the empty case, at +4 with the plain local,
#     and built in the result (NRVO, a 32-byte frame) for the plain local returned as `return contexto;`. Measured
#     when the plain local was written: +4 with the vector held in a reference, a std::move of a temporary copy, or a
#     by-value lambda parameter returned, and with -fno-strict-aliasing or -O2 added or CApplicationContext's copy and
#     move constructors declared; +28 with the non-empty case first or a ternary into the local; NRVO read `97 over 146
#     rows (... 45 deleted)` in the whole link.
#   - 5569 matches, named by its census pair (step 8's `pair-addr`; its addr hash has one body on each side, pnpm wasm
#     fingerprint): `6 over 109 rows (same 103, replaced 6 [6 operand-only])` against our symbol, every one a call, of
#     1695 and of emscripten_builtin_free (fn 136).
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
#   the same two statics, read as EnterLoopBeeping inlined there: it waits for ShowExceptionMsg, and so does 11151; that
#   __async_assoc_state's slots 5560 and 5561 match, as the bodies the target shares with SaiPorVotacaoSuspensa's
#   std::async state (unit 116).
# - 5568, ShowExceptionMsg(EExceptionLevel, const std::string& x4, const TExceptionStacktrace*): the typeinfo name of
#   its lambda's std::async state (ledger/strings.tsv 520532) gives the name and the parameter types, and 5568 is the
#   one function that holds that state's vptr (1577576). Its whole body is the std::async: the state built, then the
#   std::thread's constructor (2541, __thread_struct's), then std::__throw_system_error (1223) with "thread constructor
#   failed", and nothing after it; read as pthread_create failing in a build without threads. A probe gives that
#   shape: a function of the same signature (std::async over a lambda that captures nothing, then calls that pass its
#   parameters on), compiled at uenux2's flags and linked like the build (-Oz -fexceptions) with two callers that pass
#   the stacktrace pointer as nullptr, builds the state and the thread's structures (__thread_struct's constructor
#   inlined, its one caller there) and throws through std::__throw_system_error, with nothing after. It keeps
#   (i32 x5)->(), as 5568 does, the pointer gone, and the same function with nothing after the std::async has ()->().
#   So the source used its parameters after the std::async, read as calls of LogExceptionMsg and
#   ShowExceptionMsgScreen: their records (432 and 377) print ShowExceptionMsg's parameter list, LogExceptionMsg's
#   without the level, and no function loads them, nor the five
#   log texts that begin "CApplication:" (ledger/strings.tsv 80041, 80069, 80097, 80554, 81522; no i32.const or packed
#   i64.const of them in build/out/splat/pieces/asm). Those two bodies are not in the target, and a function no vtable
#   slot holds is never trapped (src/units/README.md "Pending members"), so 5568 waits, and 7709 and 7710 with it.
# api::MostraMensagemTemporaria (no index: binaryen inlines it into its one caller, 11891, unit 104's
# vota::CMenuFiltrarCandidatosPorNumero::ProcessInput, behind a 48-byte prologue), the function of internal linkage
# ExibeMensagemTemporaria that holds its body, and FONTE_MENSAGEM, the SFont {35, 0} at .rodata 520148 that 11891 alone
# reads; capplication.h has the body's evidence and what is chosen. Their file: the target's font lies right after the
# typeinfo name of InitApplication's local facet (@519992, 0x9a bytes), and our link puts FONTE_MENSAGEM right after
# that name in this object's data too (build/out/wasm-map/vota_web/vota_web_wasm.map: 0x772e4 after 0x77247 at
# 836481cb, 0x77384 after 0x772e7 at 543ca8b7): a reading,
# as the lines (after GetExceptionLevel, in the run the records leave blank) are a choice. The target's frame of 48
# bytes holds the builder at +36, the fill's result at +28, the second SPoint (639, 310) and then the text field's
# result at +20, the form at +12, and the first SPoint, the text's SPoint (320, 242) and the "" at +0. Measured in
# object probes compiled at src/api's flags, the offsets each call takes read with wasm-objdump -d: with the body
# written as statements of MostraMensagemTemporaria the second SPoint takes the form's slot, +12, its other slots the
# target's (the two adders' dropped results get no lifetime markers there: the TU's IR, -S -emit-llvm); with the form
# `auto`, the CWait by reference, `(void)` on the text field's call, the form declared before the adders and assigned,
# or std::string() for "", the second SPoint is at +12 too; the text field's result a named local, or a `const auto&`,
# gives every slot of the target's but releases it at the end, where the target releases it right after the call; named
# and then reset() or set to nullptr, the slots are the target's, with the null stores and a second release at the end;
# `std::ignore =`, and a local assigned then reset, give other slots ("" at +8, the form at +20). With the body in a
# function of internal linkage that clang inlines into a thin MostraMensagemTemporaria, every slot and release is the
# target's: the inliner gives the two dropped results lifetime markers from the body's start to its end (the IR's
# lifetime.start and .end around the inlined body), so the text field's result outlives "" and the form and takes the
# second SPoint (docs/reference/facts/codegen.md C5). That helper written external is not inlined by clang, and taking
# the CWait by value there copies it into an 80-byte frame. Written `static` instead of in an anonymous namespace, or as
# a lambda called in place (`[&] { ... }();`), it gives the same function byte for byte (object probes at 836481cb,
# compared by function with docs/reference/facts/tool-traps.md X12's masks). A helper around part of the body gives
# other slots: with only the two adders in it the form shares the text field's result's slot, and with AddTextField
# alone the second SPoint's ("" then shares the text field's). In the whole link 11891 then matched (unit 104's
# fragment).
CAPPLICATION_SRCS := src/api/gui/capplication.cpp
UENUX2_SRCS += $(CAPPLICATION_SRCS)
$(ROOT)/$(APP)/171-uenux2-capplication-roots.o: $(ROOT)/src/units/171-uenux2-capplication-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/171-uenux2-capplication.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/171-uenux2-capplication-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/171-uenux2-capplication-roots.o
