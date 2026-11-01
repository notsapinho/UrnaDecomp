# uenux2 api::CApplication (api/gui/capplication.cpp, the records' file), in part: EnterLoopDoingNothing (target fn
# 5566), with the two statics it reads, in a header of a chosen path (api/gui/capplication.h); and GetDescricaoModo (fn
# 5564), written and not matched (below), with the two statics it reads.
#
# Evidence and choices.
# - The record capplication.cpp:503:32, `static void api::CApplication::EnterLoopDoingNothing()`, gives the class, the
#   name, the static and the line; column 32 is the start of the CPolySingleton<IScreen>::instance() call whose default
#   argument makes the record. How the 31 characters before it are shared out is chosen (a local auto& screen).
# - The body: has<IScreen> (3387) and instance<IScreen> (512), both matched, then IScreen's slot 37 (vtable offset 148:
#   api/gui/iscreen.h's Slot37, a chosen name there); CSystem::Dorme(1000) (api/util/csystem.h); a loop over a byte at
#   .bss 1839209 and a word at .data 1577212. Their widths are the bytes' (a byte tested for non-zero, a word compared
#   signed with 0 whose initial bytes are ff ff ff ff); their names, the bool and int types and the initializer's
#   spelling are chosen (the header says so). Fn 11159 stores -1 into the word and fn 11151 (read as holding
#   EnterLoopBeeping inlined) reads both with the same test; neither is written.
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
#   either line out, or both, takes 5566 out of match and moves no other row; the build gives the target's sha256 each
#   way, and a control that removes nothing keeps 5566.
# - The roots file stands for 5566's two target callers, 7709 and 7710, as two noinline call sites, and with
#   DescreveModo for 4620, 5564's caller beside 502 (unit 31), which is not written.
# - GetDescricaoModo (5564) and s_modo and s_demonstracao: api/gui/capplication.h has the evidence and the choices. In
#   the whole link 5564 scores 8 over 75 rows, every one an operand of a call or of data (pnpm wasm score), and its row
#   is `no-candidate`: no evidence names it while 502, whose records would anchor it, differs, and 4620 is not written.
#   Named, it would still wait: its .bss byte at 1839208 has no reader but 5564 (docs/reference/splat.md 3, no hand
#   line for it), and its .data word, 48, holds one non-zero byte, too little for content to place it, until 7787, the
#   word's other reader, is written.
# - Lines: 503 is the record's; 303 (QRCodeSRC::build), 377 (ShowExceptionMsgScreen), 432 (LogExceptionMsg) and 478
#   (EnterLoopBeeping's lambda) are records of functions not written and stay blank. Every other line, the statics' place
#   in the file and the include order are chosen.
#
# Not written:
# - 3683, EnterLoopBeeping's lambda (record 478:13). Its one caller, 11151, fills a slot of the vtable of libc++'s
#   __async_assoc_state over a lambda of ShowExceptionMsg (ledger/vtables.json) and calls it three times in a loop over
#   the same two statics, read as EnterLoopBeeping inlined there: it waits for ShowExceptionMsg.
# - 11159, InitApplication (the slot main passes to invoke_viiii; it stores the vptr of its local class
#   commaAsDecimalSeparator, whose vtable lies among this file's records). It calls 1468, 5558, 3684 and 987, which have
#   no name (no-candidate in splat/scan.tsv). Its landing pads are read as libc++'s code that binaryen inlined into it, not as this
#   file's: the pads sit around a call of locale::__global (4710), two of locale::name and a compare of the name with
#   "*", the body of locale::global, and around operator new(156) and fn 7826, read as the locale constructor's
#   __install_ctor. 11156, the local class's do_decimal_point (`push 44`), comes with it.
CAPPLICATION_SRCS := src/api/gui/capplication.cpp
UENUX2_SRCS += $(CAPPLICATION_SRCS)
$(ROOT)/$(APP)/171-uenux2-capplication-roots.o: $(ROOT)/src/units/171-uenux2-capplication-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/171-uenux2-capplication.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/171-uenux2-capplication-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/171-uenux2-capplication-roots.o
