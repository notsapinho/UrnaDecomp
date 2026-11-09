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
# Matches, 17, all from the link this object changes (none is a body of a function this file writes), and six more
# over two data lines (below):
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
# - Two data lines of splat/symbol_addrs.txt, below the marker, name libc++'s __format_spec::__fields_integral and
#   __fields_bool, 2 bytes each (37 01 and 30 01, libc++'s two field sets, in both links), right after the typeinfo name
#   "NSt3__212format_errorE" in both links (target 450343, ours 344597; each object at +23 and +25). Six rows match over
#   them (11373): 9868, this object's handle, and its callee 1558 (the executable TU's
#   __formatter_integer<char>::parse), which were `unresolved` on the first; 3923 (__process_display_type_bool_string),
#   on the second; and the handles 536, 1699 and 1711, which hold both inlined. Each line weighed (taken out, then
#   splat-match): without __fields_integral, 536, 1558, 1699, 1711 and 9868 leave match; without __fields_bool, 536,
#   1558, 1699, 1711 and 3923, and the splat build then refuses 9868 too (`UNCONFIRMED: self-voted`: 1558's name, `call
#   by:9868`, rests on 9868's own call), so that line carries all six. 7884 (money_get<char>::do_get, libc++.a) reads
#   `differs` at +0xf2 where it read `unresolved` on a table slot: no
#   match either way.
#
# Written, and not in the link: nothing reaches these, so wasm-ld drops them (their rows are no-candidate) and only
# their linkonce copies above link.
# - SalvaGeral (10243, table slot 414, passed by 10256) and SalvaApps (10212, slot 419, passed by 6004), with SalvaApp
#   and Converte(EUrnaTurno) inlined into it by binaryen. The save they call, the services' constructors and
#   CFileASN's writer are written now (unit 206), and a root taking the two addresses, as the target's 10256 and 6004
#   do, is what is left; 10212 is the target's one holder of the constructors' and the saves' table slots (unit 206's
#   roots stand for it). Each call passes a copy of the state: IServicoEstado::Salva takes a reference (fn 6039, unit
#   109, passes its state with no copy), and the target's 10243 and 10212 copy before each save (10205, 10123, 10101,
#   10067) and destroy the copy after it, so the copy is the builder's own, written as a temporary at the call
#   (`Salva(CEstadoGeral(m_geral))`), which keeps the target's order, the service first (a reading: the object
#   expression is evaluated before the argument); that spelling is chosen. This
#   object's linkonce copies give the link, ahead of every other object: the four saves and their merge 2894 (thunks
#   3592, 5329, 10112, 10089), IConversorASN::Converte's four (merge 2893, thunks 10170, 9997, 10051, 10019, with the
#   format-argument store 9843 and CBaseError<EUeComumAsnError>'s constructor 255), CFileASN::WriteToFile's eight
#   (merges 2892 and 2891, thunks 10168, 9985, 10040, 10008 and 9820, 9684, 9703, 9701), CodeObjectFunction's four
#   (2927 and its thunks, from src/app/roots_coderenv.cpp before), ~CoderEnv (518), 9790, 3552, 1928 and 210 (the same,
#   from that root before), and CFile's destructor (3564): all match. The estado copies the two members make and
#   ~CEstadoGeral (2793) come with them.
# - Converte(EMidia) (5344): its callers are those two. With them, its handle (9935) and format<int> (5924) come too.
# - The file writer (10293, table slot 420, called by both).
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
#
# Since the executable TU's votaInit (unit 170) is written, it constructs the builder and calls the members unit 440's
# notes list (written in this file and its header): 23 rows of this object match with them, among them the
# setters 10176, 10181, 10188 and 10197, TodosApps 10286, the destructor 5644 and the default constructors of the
# states (10261, 10278, 9952, 9963); the constructor 10268, SalvaTudo 10256 and the per-turn saves (10242, 10239
# over 6004) are written and not matched. SalvaGeral and SalvaApps are in the link now, through those saves.
