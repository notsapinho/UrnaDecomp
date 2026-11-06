# uenux2 api::CIniFile, the INI file object, and its loader Carrega (target fn 5480, 8780 B), in the new
# src/uenux2/src/api/io/cinifile.{h,cpp}; with the INI reader's string helpers and CIniStrings::ParseKeyLine in
# api/io/cinistrings.cpp (unit 215's list compiles it), CIniSection's operator= and constructor in
# api/io/cinisection.cpp (unit 175's), CIniKey's constructor in api/io/cinikey.cpp (unit 01's) and the order of two
# lines of ecourna's CFile::ReadLine in api/io/cfile.cpp (unit 03's). Their notes are here; each unit's fragment points
# to this one.
#
# Matched by this unit (steps 7 to 9): the INI reader's string helpers in cinistrings.cpp, ProcuraNaoEscapado (2234),
# RemoveEspacos (2235), RemoveComentario (2236), TrataEscapes (3651) and LinhaUtil (5485), which step 8 names by the
# census's pairs (3651 and 5485, pair-addr) and by their callers' calls (2234, 2235 and 2236, evidence:call); libc's
# isblank (6272, which 2235 calls twice beside isspace: libc.a's isblank.o, no source); std::map<std::string,
# api::CIniKey>'s tree destroy (1397) and its __emplace_hint_unique_key_args<std::string, const value_type&> (3650),
# libc++ instances our link keeps from cinisection.cpp.o, whose operator= is their first user there; and 6071 and 12862
# (below). FindKey (10877) moved into cinifile.cpp under the new class, and step 9 renamed its match line.
# Written and not matched: Carrega (5480) and the exit destructor of TrataEscapes's static (10879), each below with what
# it waits for.
#
# What 5480 holds (pnpm wasm fn and pnpm wasm lift of the target): a stack frame of 80 bytes for the loader itself, and
# behind second prologues the functions binaryen inlined into it, each with one caller: ecourna's CFile::ReadLine (160
# bytes; records cfile.cpp 336 and 356), the parse of the lines (128 bytes: the stores of the two maps' end nodes come
# first in it, after the file is read), CIniStrings::ParseKeyLine (544 bytes; records cinistrings.cpp 183 and 187), the
# INI object's SetKey (64 bytes) and SetSection (48 bytes), and inside SetSection CIniSection::operator= (record
# cinisection.cpp 36) and the copy of the new section into a pair (8 bytes, the insert's result: which function holds it
# is a reading). It calls out of line 5484, 5485, 2236, 2235, 2234, 3651, 5482 (CIniSection::SetKey), 5483
# (CIniKey::operator=), 3650, 1397 and CFile's constructor (517), Eof (1885) and Close (336).
#
# Why the loader is not cinistrings.cpp's, though unit 215 read the INI object as CIniStrings, the class of the static
# ParseKeyLine it holds. Measured: with the loader in cinistrings.cpp (tools/round/try-tu.sh --symbols, the object's
# calls read with wasm-objdump -d -r), clang inlines TerminaComBarraInvertida, LinhaUtil, RemoveComentario and
# RemoveEspacos into it, where the target's 5480 calls 5484 twice, 5485 twice, 2236 three times and 2235 three times.
# Evidence: in use band 2 (ledger/ordinals.tsv) 5485 and 5484 link before cinikey.cpp's CIniKey::operator= (5483), and
# 5481 (EndKey's body, below) and 5480 after cinisection.cpp's SetKey (5482); in the data ParseKeyLine's records
# (1584092, 1584108) lie before cinikey.cpp's (1584124) and cinisection.cpp's (1584140). So the loader, EndKey and
# FindKey are one object that links after cinisection.cpp's, and cinistrings.cpp holds ParseKeyLine and the helpers. No
# record, slot or RTTI names that object's class or file: CIniFile and cinifile.{h,cpp} are chosen (a name that sorts
# before cinikey.cpp, where the band puts the object after cinisection.cpp: the data show cinistrings.cpp's object
# before cinikey.cpp's too, so the line is not in name order), and CIniStrings keeps the static ParseKeyLine only.
# FindKey and EndKey move from cinistrings.cpp into cinifile.cpp, their bodies unchanged; fragment 227's GetValor and
# the contract headers name the new class.
#
# The loader's shape (each measured with pnpm wasm score against 5480 in the plain link; the score moved from 3189 over
# 5239 rows, the first form, to the one below):
# - Carrega is a static member that reads the lines into a std::vector<std::string> and returns Interpreta(linhas), a
#   private static member that returns the object it builds (chosen names). The end nodes' stores lie inside the inlined
#   128-byte frame, after the read, so the parse is a function of its own that builds the object (a reading). As a
#   constructor CIniFile(const std::vector<std::string>&), its call through the constructor's alias let clang reload the
#   vector's begin and capacity in the read loop, where the target keeps them in locals (the object's Carrega, try-tu
#   --symbols: the loads present with the constructor, absent with the static function; 1436 -> 1443 over the whole
#   function, the loop's rows then equal).
# - The read loop: `break` on an empty part at end of file, the outer loop `while (!fim)` with fim set in both arms,
#   `!LinhaUtil(linha)` tested first. The object's Carrega then destroys parte once and linha twice, twelve frees
#   outside ReadLine as the target's 5480 has; with `continua = false` and `do ... while (!fim)` it held fourteen (1395
#   -> 1332). Interpreta's inner loop ends `while (++it != linhas.end())` after a `break` when the line does not
#   continue: sixteen frees in its object as in the target's 128-byte frame, seventeen with `while (continua && ++it !=
#   linhas.end())` (1230 -> 1178). parte.back() is the test of the newline (the target computes data + size - 1).
# - The current section is a bool and a std::map iterator, tested `!temSecao` first (the global SetKey's inlined code
#   comes before the call of 5482 on the section). std::optional<iterator>, and the bool and the iterator declared in
#   the other order or ahead of `CIniFile ini`, give the same object (cmp of cinifile.cpp's object compiled at its
#   rule); a CIniSection* moves the + 28 to the assignment where the target adds it at the call (1178 -> 1626).
# - Whether a line is a section's is EhSecao (cinistrings.h, a chosen name), a call when clang compiles Interpreta: the
#   target keeps substr(1, size - 2)'s out_of_range test, which clang drops when it sees the size test (1443 -> 1395).
#   It has no target index: binaryen inlines it, frameless, into its one caller. The `!temSecao` test came in the same
#   step.
# - CIniKey's constructor (std::string, std::string), by value, and CIniSection's (std::string) are out of line in
#   cinikey.cpp and cinisection.cpp: the target keeps the destroy tests of the strings they moved from, which clang
#   drops when it inlines them (1332 -> 1230). CIniSection declares its copy and move constructors `= default`, as
#   CIniKey does, since its operator= is user-declared: without the move, the new section's node copied its map and name
#   (1792 -> 1436). The by-value parameters and `= default` are chosen.
# - The INI object's SetKey copies the key's name into a local before the find (the target's 64-byte frame holds that
#   copy; CIniSection::SetKey, 5482, passes the name as is).
# - ecourna's ReadLine (unit 03's cfile.cpp, never in our link before: nothing called it) declares its result string
#   after `buffer[0] = buffer[TAMANHO_BUFFER_LINHA - 2] = '\0'`: its first stores are then +16, +142 and the string's,
#   as the target's inlined copy (the object compiled both ways, wasm-objdump -d), where the string declared first gave
#   +142, +16 (1178 -> 1173); with the stores swapped and the string first, the loop lost its rotation. Line 356's
#   record stays on its line.
# Now: `score 1173 over 4214 rows (same 3041, replaced 1016 [1016 operand-only], inserted 79, deleted 78)`. The inserted
# and deleted rows pair up opcode for opcode (local.get, call, i32.add, block, ...) but for an `i32.const 0` with its
# local.set and a local.tee: before Interpreta's frame our 5480 zeroes two locals, 16 (the bool) and 11 (the section's
# iterator), where the target's zeroes local 12 (the bool) only and holds the iterator in local 9, which it writes
# before only on paths that end at __resumeException; and ours keeps the result's address in a second local (local.tee
# 8) where the target's uses local 0. Interpreta's object zeroes both, the bool and the iterator, ahead of the loop in
# each of the section's forms above, std::optional<iterator> too (wasm-objdump -d of the object). The rows that differ
# are binaryen's packing of locals (a reading). Measured without a change of these rows (the same score): object orders
# in a copy of link.cmd (docs/reference/facts/workflow.md W13: cinistrings.cpp.o ahead of cinikey.cpp.o;
# cinisection.cpp.o or cinikey.cpp.o after cinifile.cpp.o; cfile.cpp's ahead of it or after it; cinifile.cpp.o ahead of
# cinikey.cpp.o or of cinistrings.cpp.o is worse, 1596), and cinifile.cpp's functions in other orders (the same, 1594
# with SetSection and SetKey after Interpreta, 1184 with Carrega first).
#
# 2234, ProcuraNaoEscapado (texto, procurado): find, then an odd run of backslashes before the match means escaped,
# searched again after it. The target dispatches find's result with a br_table on pos + 1, npos to the exit that sets
# npos (the one find's not-found paths take) and 0 to the return of pos. `if (pos == 0) return 0;` ahead of `if (pos ==
# npos) return npos;` (written) gives it: `score 4 over 262 rows (same 258, replaced 4 [4 operand-only], inserted 0,
# deleted 0)` in the plain link, the four rows calls (operator new, the two throws and its own recursive call). The same
# object (cmp): `return pos` for `return 0`, and the rest inside `if (pos != npos) { ... }` with `return npos;` after
# it. Measured and not kept, each a variant object of cinistrings.cpp in a copy of link.cmd
# (docs/reference/facts/workflow.md W13): `pos == npos || pos == 0` and `pos == 0 || pos == npos`, one `return pos`, 101
# over 287 rows (one range test, pos + 1 < 2, and the -1 stored ahead of the find's tests); the npos test first, then
# `if (pos == 0) return pos;`, 118 over 286 (a br_table whose 0 case stores a constant 0); a switch over npos and 0, 119
# over 286; the npos test first and `if (pos > 0)` or `if (pos != 0)` around the rest, 120 over 291 (one range test).
# find_last_not_of's result tested against npos, as written, gives the target's scan loop; `pos -
# texto.find_last_not_of('\\', pos - 1) - 1` gave another loop and a parity test folded otherwise (measured alone,
# tools/round/try-tu.sh --single).
# 2236 (RemoveComentario: the first '#', ';' or NUL, a range-for over "#;" with its NUL), 3651 (TrataEscapes) and 5485
# (LinhaUtil) differed from the target's in call and data operands only while 2234 differed, and read no-candidate. With
# 2234's form above, steps 7 to 9 match the four: the census pairs 3651 and 5485 (pair-addr), and step 8 names 2234,
# 2235 and 2236 by call votes. 3651's Replace is CStringUtils's copying overload, reached through std::as_const (how-to
# step 3, unit 230: the overload set forces it).
# 3651's static (ESCAPES, @1839288, the ten escapes the target's static initializer 14478 stores) is in an anonymous
# namespace, a choice; our link holds it as three words, the symbol file's ESCAPES.0 to .2. Its exit destructor 10879
# reads `unresolved self-voted` on ESCAPES.2: 3651's match votes for .0 and .1, and the third word, 1839296, is loaded
# by 10879 and 14478 (__wasm_call_ctors) only (/usr/bin/grep -rlE 'i32\.const 1839296($|[^0-9])'
# build/out/splat/pieces/asm). It waits for a match of 14478; a hand line would rest on 10879's own operand (how-to step
# 9, "Hand edits"). 10879 is a thunk into the body binaryen keeps for it and for vota::TECLAS_TESTE_TECLADO's exit
# destructor (12862, ctelasvota.cpp.o's), 6071, as the target's 10879 and 12862 are: 6071 and 12862 match, and a link
# with a cinistrings.cpp.o without ESCAPES holds no merged body and 12862's destructor whole
# (docs/reference/facts/splat.md S10 item 30).
#
# Choices besides those above: the helpers' names, their being free functions of api with external linkage (they read
# no class state; the loader is another TU's, so they cannot be internal) and cinistrings.cpp's lines but 183 and 187;
# EhSecao; the error enumerators 6007, 6009 and 6010 (eueioerror.h, from the messages); the members' names and the
# locals. The codes and messages are the target's (6009 "Linha inválida [{}]", 6010 "Linha com nome inválido [{}]",
# 6007 "O nome de uma seção é constante.").
#
# Roots: 379-uenux2-cinifile-roots.cpp stands for 5480's one caller, 12098 (two calls). The stand-ins for 5480 in units
# 175 and 215 went, and so did src/app/roots_uenux2.cpp's ChaveA and ChaveB, which stood for 5483's callers 5480 and
# 5482, both in the link now.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
W379_SRCS := src/api/io/cinifile.cpp
UENUX2_SRCS += $(W379_SRCS)
# the roots declare what they call through an asm label, so their rule needs no header
$(ROOT)/$(APP)/379-uenux2-cinifile-roots.o: $(ROOT)/src/units/379-uenux2-cinifile-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/379-uenux2-cinifile.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/379-uenux2-cinifile-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/379-uenux2-cinifile-roots.o
