# uenux2 comum::teste::CAppInfoBuilder (mock/app/comum/cappinfobuilder.{h,cpp}), compiled at the executable TU's rule,
# VOTA_WEB_CXXFLAGS (-Oz -fexceptions -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing), its object second on the link line
# (VOTA_WEB_OBJS, so the benchmark's setup `vota-web`). The fragment holds no source: the rule is in src/Makefile, beside
# the executable TU's, and listing the source in UENUX2_SRCS would compile it a second time at the tree's flags. This
# file holds the evidence.
#
# The rule, evidence and measurement:
# - The file has landing pads: its two record-bearing functions call invoke_* (10243 at 7 sites, 10212 at 29;
#   docs/reference/facts/app-flags.md F6 has the command), where uenux2's src/ and mock/app/simulador/wasm/ have none.
# - Its records (1528028 to 1528060) lie right after the executable TU's data (up to 1527964) and before the records of
#   the src/ files that pass EUrnaTurno's format handle, table slot 474 (cpath.cpp, util.cpp, cappinfo.cpp,
#   cconversordadocarga.cpp; awk over ledger/source-locations.tsv by file). The iconversorasn.h and cfileasn.h records
#   after them are read as the saves this TU instantiates. So the object links second, a reading from that order.
# - Slot 474 is fn 9868, which calls __formatter_integer<char>::parse (1558) and format<unsigned int> (5906) out of
#   line, where the uenux2 objects' copies of the same handle (merged into 536's body) hold both inlined. This TU throws
#   with the turn formatted, so its object emits the handle at -Oz, and linked ahead of the src/ objects that use it,
#   it gives every user that copy (cpath.cpp.o, util.cpp.o and cappinfo.cpp.o define the same symbol, the handle of a
#   non-const EUrnaTurno): its calls are 9868's (step 8 names 1558 and 5906 by them).
# - Measured on the whole link at 36dda756 (11350 matches), `TMPDIR=/tmp make -C src link census splat-symbols
#   splat-match`, then the counts by index of how-to step 10 against 36dda756, at four places of the object (the
#   others by make overrides of VOTA_WEB_OBJS, APP_OBJS and EXTRA_OBJS, nothing recompiled):
#     A, second, in VOTA_WEB_OBJS (this rule)               17 added, none lost (11367)
#     B, after roots_coderenv.o, first in APP_OBJS           17 added, none lost: the same rows, no twin renamed
#     C, after the last of APP_OBJS, the tree roots          12 added, none lost: 194, 857, 2250, 4669, 4727 stay out
#     D, first in EXTRA_OBJS, after both trees' objects      0 added, none lost
#   So the place decides: from C on, the roots' copies come first (roots_vector.o's of 857, roots_rhvoice.o's of 194
#   and 2250, at the stand-ins' -O2), and from D on the trees'.
#   A and B give the same rows; A keeps the object in the setup of its flags.
#
# Matches, 17, all from the link this object changes (none is a body of a function this file writes):
# - 358 and 1399 (CPath::GetPathTrab and GetPathResult, unit 190), 1553 (CAppInfo::IndiceTurno, unit 109) and 11401
#   (CConversorDadoCarga::DoConverte, unit 96): each differed only by slot 474, and their anchors' table votes now name
#   this object's handle 9868.
# - 5906, format<unsigned int>, from vota_web_wasm.cpp.o: 9868 is its second caller, so binaryen keeps it out of line.
# - This object's copies of inline code, which the target keeps: 857 and 1249 (CDadoCorrespondencia's destructor and
#   copy constructor), 2240 and 9872 (CIdentificadorGeradorMidia's), 10145 (vector<unsigned char>'s copy constructor),
#   178 (string::append over two const char*), 11257 (string::__addr_in_range), 194 (__put_character_sequence) and 2250
#   (__pad_and_output). The members below instantiate them, and other objects call them. Unit 109's fragment read 857's
#   and 2240's -Oz shape as the executable TU's copies, and the base's 194 and 2250 were roots_rhvoice.o's.
# - Three libc++.a bodies: 4669 (string::__init(size_t, char)) gets a second caller in 2250 and stays out of line,
#   so 4727 (moneypunct<char, false>::do_negative_sign) calls it as the target does; 8084
#   (__shared_ptr_emplace<filesystem_error::_Storage>::__on_zero_shared) calls 2240 at +12, as the target's does, read
#   as binaryen sharing 2240 with _Storage's destructor (both destroy three strings at +24, +12 and +0).
# - Step 9 renamed two lines to twins this object brings first: 520 and 4967, vector<char>'s ~vector and
#   __destroy_vector::operator(), to vector<unsigned char>'s.
# - Four hand lines of splat/symbol_addrs.txt went, each carrying nothing on this link (536's out alone, then with
#   2240's and 2250's, then with 1249's: splat-match moves no row each time, and the splat build verifies 11367):
#   536's, which step 8 now writes as a generated table line, the votes no longer split with the turn's handle a body
#   of its own; 2240's and 2250's, now generated pair-addr lines; and unit 123's 1249's, a body that matches here.
#
# Written, and not in the link: nothing reaches these, so wasm-ld drops them (their rows are no-candidate) and only
# their linkonce copies above link.
# - SalvaGeral (10243, table slot 414, passed by 10256) and SalvaApps (10212, slot 419, passed by 6004), with SalvaApp
#   and Converte(EUrnaTurno) inlined into it by binaryen. Both wait for IServicoEstado's save (2894 and its thunks 3592,
#   10112, 10089, 5329), declared in iservicoestado.h, whose body waits for cfileasn.h's writer (2892, and 2891 over
#   CFileASN::CodeObjectFunction's merge); 10212 waits for the derived services' constructors too (thunks 5812, 11566
#   and 3787 of 3897, over CFileASN::ReadFromFile, 3791). A root taking their addresses, as the target's 10256 and 6004
#   do, would need those bodies. The writer's chain ends in a keystone of its own: CodeObjectFunction's four members
#   (9801, 9702, 9695, 9673, the thunks 2891's thunks pass by slot) call the merge 2927 (1275 B), which calls
#   ~CoderEnv (518, no-candidate) and 9790 (no-candidate). And 2894 is binaryen's merge of the four saves, so its shape
#   needs the four in the link, three of them 10212's (pnpm wasm fn on each). The estado copies they pass (10205, 10123, 10101, 10067) and ~CEstadoGeral (2793) come
#   with them.
# - Converte(EMidia) (5344): its callers are those two. With them, its handle (9935) and format<int> (5924) come too.
# - The file writer (10293, table slot 420, called by both).
# - 9868 is in the link, this object's, and named by the votes above, but `unresolved self-voted`: its callee 1558 (the
#   executable TU's parse) has no name but 9868's own call, and 1558's row is unresolved on
#   __format_spec::__fields_integral, a 2-byte object nothing names.
#
# Evidence for the code (pnpm wasm fn on each): 10243 loops over the media, converts each (5344, with the record
# 112:37), writes "assinatura EG" to the dynamic path's "eg.vsu" through 10293 when its bool is set, and saves the
# general state at +0 through a CServicoEstadoGeral (1941) and slot 422; 10212 converts each media (record 277:28) and,
# for each application, inlines SalvaApp: the turn's converter (its own 512-byte frame, record 287:22 read for the
# line), GetPathTrab (358), and a switch on 0, 1 and 2 to the gap's, the apuracao's and the vota application's
# "gap.vsu", "sa.vsu" and "vota.vsu" signatures and states. The converters' messages are ledger/strings.tsv 235304 and
# 235349, std::logic_error's (typeinfo 1525980). The writer creates the parent directories (slots 401 and 10), opens an
# ofstream in binary mode (20) and writes the string (slot 73).
#
# Measured on the object: a file-static Converte(EUrnaTurno) is inlined by clang into SalvaApp (one frame), where the
# target holds the converter's frame apart; with external linkage SalvaApp calls it and binaryen inlines it. So the
# converters are not file-static; where they are declared is chosen.
#
# Chosen, no evidence names them: EMidia's and EApp's enumerators, that they are scoped enums, and their namespace;
# EMidia's formatter (the int base is evidence, 5924); the converters' and the writer's names, parameters and place;
# Salva's name; the data members' names and that they are arrays; the header's path and includes; and every line of the
# source but the three records', whose statements are written to their columns (the column fixes the length only).
