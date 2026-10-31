# CBaseType<TYPE, MIN_VAL, MAX_VAL, BASIC_TYPE>'s constructor (ecourna's api/pattern/cbasetype.hpp), the copies uenux2's
# objects kept and the ones ecourna's did, and CStringUtils::Trim (api/util/cstringutils.cpp, unit 00's source) with the
# functions that stop at it. The constructors have no source of their own: they are the header's code, so this fragment
# holds the evidence and the roots rule. The bodies of src/ecourna/api/util/cstringutils.cpp stay unit 00's.
#
# Matches, 22 target functions:
#   - uenux2's copies, from app/roots_uenux2.o: 2299, binaryen's merge of the 16-bit constructors, with its thunks 1960
#     (TQtdEleitor) 2277 (TAno) 2850 (TScoreHabilitacao) 5848 (TSecaoID) 5850 (TZonaID); 6042, the 32-bit merge, with 2851
#     (TMunicipioID) 5849 (TLocalID); 5682 (TCargoID), a body of its own, since MIN_VAL 1 gives it another range test.
#   - ecourna's copies, from app_dados_tiposbasicos.cpp.o: 2666 (TTipoIdentificadorEleitor), and 2668,
#     CErroLeituraBiometria's constructor, which holds CBaseType<EErroLeituraBiometria, ...>'s inlined. binaryen inlined it,
#     not clang: a second prologue (facts/reading.md R10), and tiposbasicos.cpp.o still has the `call`, its one call site.
#   - 9228, CConversorCargoID::DoDeconverte, which only waited for 5682's name.
#   - CStringUtils: 9406 Trim(std::string&), 1374 Trim(const std::string&), 3942 the merge of 1374 and 1879, 1879 the copying
#     ToLower (unit 12's), 3506 HexStringToBytes, 2202 and 5155 the two converters, 9259 CSerialMidia's constructor (unit
#     07's, it waited for 3506's name), and 1136, std::string::__erase_external_with_move, from libc++.a, which matches
#     once it has a second caller.
#
# Which copy. The target has two sets of constructors, as it has of IConversorASN's (facts/tool-traps.md X7). 13 records
# name cbasetype.hpp: 8 under .../p/include/ecourna/, the conan package's installed header, so a uenux2 TU compiled them,
# and 5 under .../b/src/ecourna/, ecourna's own (`awk -F'\t' '$2 ~ /cbasetype/ {print $1, $2, $6}' ledger/source-locations.tsv`).
# The bodies agree: the eight have no landing pad, and 9215, 2666 and 2668 have. ecourna's callers (9066 9127 9130 9142
# 9221 9228) call the uenux2 copies directly, because uenux2's objects come first in the link and the linkonce copy of the
# first object wins. So src/Makefile's UENUX2_PREFIX_MAP gains the third spelling, and src/app/roots_uenux2.cpp, ahead of both
# trees, instantiates the eight constructors explicitly: no real uenux2 caller of them is written (11616 calls six), and a
# fragment's roots link after ecourna's objects, which would keep their own copies (`source_location not in the target`,
# 5682's row before this unit). This unit's roots file only calls them. The map changes no other object: `LC_ALL=C
# /usr/bin/grep -rl src/ecourna/ build/out/app/uenux2` printed nothing before it.
#
# roots_uenux2.o compiles with TBAA and uenux2 with -fno-strict-aliasing. The nine constructors compare the same at both
# flag sets with the object's numbers masked (9 same of 9; the rest of a probe TU that holds them: 105 same, 9 differ, all
# libc++ format internals: __handle_replacement_field's lambda, __parse_type, __format_floating_point ...). The object now
# comes first in the link for those format internals too: 43 scan rows name it, 14 at the commit before this unit (`awk
# -F'\t' '$11=="app/roots_uenux2.o"' splat/scan.tsv`). No verdict of those rows moved and no match left. A real uenux2 caller
# lands the constructors at the tree's flags, and the eight lines then go.
#
# The range test, evidence. 5682 is `(p1 - 1) & 0xffff >= 99`, and 2666 the same over 1 and 3. `valor < MIN_VAL || valor >
# MAX_VAL`, the form before this unit, gives `(p1 - 100) & 0xffff <= 65436`, 3 rows off. Same object as the form written:
# `!(valor <= MAX_VAL && valor >= MIN_VAL)`, and an empty `if (valor >= MIN_VAL && valor <= MAX_VAL) {} else {`. The spelling
# among those is a choice.
#
# The limits as named ints, evidence. std::format's argument codes are 13, 3, 3 (the i64 3181: facts/reading.md R13), so
# they reach it as int for every TYPE, and the enum instances cannot pass TYPE: no formatter. With prvalues
# (`static_cast<int>(MIN_VAL)`) 2666 and 2668 keep their landing pads in another order, 18 rows inserted and 19 deleted,
# and so does `static constexpr int` in the class. Named `int` locals give the target's order: the `unreachable` after
# __cxa_throw stays in place. Same object as written: the locals non-const, or declared before the `if` in the constructor
# (all nine constructors and CErroLeituraBiometria's, at both trees' flags). The uenux2 copies do not tell them apart, having
# no pads. The names and which of those forms is the source are choices. CErroLeituraBiometria's own throw has the other
# order, prvalues as written in tiposbasicos.cpp: the target's 2668 holds both.
#
# Line. 39:19 is the throw's record in all 13. The constructor starts on line 34 only because the two locals sit above the
# throw: no record fixes lines 34 to 38.
#
# CStringUtils::Trim(std::string&), evidence, each measured on the whole TU (16 functions, same-length paths, numbers masked):
#   - the first test is a select over both sizes, loaded before it. `!std::empty(valor)` is written, and `std::size(valor) >
#     0` and `valor.compare("") != 0` give the same object. `!valor.empty()`, the form before this unit, and `valor != ""`
#     branch on the long bit first (188 rows of 186). Without -fno-delete-null-pointer-checks `!valor.empty()` gives the
#     select too, so that flag is what the three forms get round (facts/app-flags.md F3 has the flag). Which of the three is
#     a choice.
#   - the second erase is inside the `if` (the target returns from the empty case with no erase) and is the iterator form
#     (one begin for find_if and the difference, then erase's npos test before the short and long paths).
#     `erase(0, find_if(...) - begin())` splits the difference over the two paths.
#   - the first erase takes a position: `erase(ultimo.base(), end())` gives another object (138 of 186 rows).
#     `std::distance(rbegin, ultimo)` for the difference gives the same one.
#   - a lambda for NaoEhBranco gives the same object. The named function is a choice.
#
# Trim(const std::string&): 1374 is `f3942(p0, p1, slot 6416)`, and elem[6416] is 9406, so a copy of the string, Trim, and
# the copy returned; 1879 and 5156 are the same over 5158 and 3509. It has no record: that it is a static member called Trim,
# and its line beside the other Trim, are choices. 3509, the ToUpper-like body, and 5156 stay unwritten, and the merge forms
# from 1374 and 1879 alone.
#
# The converters and HexStringToBytes, evidence. All three call the copying Trim, and clang inlines it (the object has the
# invoke and no call of 1374): `invoke` of slot 6416 with a landing pad of its own, that frees the copy and resumes, apart
# from the function's other cleanups. `std::string
# texto(valor); Trim(texto);` has one pad for both: 609 of 3506's 670 rows move, and 2202 scored 13 rows inserted and 31
# deleted.
#   - 2202 and 5155 throw EUE_VALOR_INVALIDO on an empty string (br 2 out of the size test, to the first throw), so `texto.empty() ||`
#     stands before find_first_not_of. Without it 602 of 681 rows differ.
#   - 3506's throw is 808:15, one level deep, so the check is one `if`, not a loop with an `if` inside. `std::all_of` over a
#     lambda is written, and `[](char c) { return isxdigit(c); }` gives the same object. `std::find_if_not(...) != end()` does
#     not (577 of 670 rows).
#   - 3506 has no test of its own for an empty string: without one the object has the target's, the size test as the check
#     loop's entry and the vector's two stores on the empty path. `if (texto.empty()) return {};` gives another (575 of 670).
#   - the loop's bound is computed once, ahead of the loop: `i < static_cast<int>(texto.size()) - 1` in the `for` reloads it,
#     597 of 670 rows. Unsigned in `tamanho / 2`, signed in the bound (`i32.shr_u`, `i32.lt_s`). Same object: `tamanho` left
#     out for two calls of size(), `static_cast<int>(tamanho - 1)`, and `(alto | baixo) >= 0`. The local is a choice.
#   - HexCharToInt takes int: the compares are on the sign-extended byte. With `char` 305 of 670 rows differ.
#
# Left, each measured:
#   - 9215, TPartidoID's constructor, is ecourna's copy (b/src record) with table slot 6695, and its users 3649, 9064, 9216
#     are not in this link, so it stays no-candidate. An instance in a scratch TU gives its rows but for NOME: that TU was
#     tiposbasicos.cpp, where NOME's definition folds, 25 rows, which a converter's TU does not see. Not measured over such a
#     TU. It waits for those callers.
#   - 1143, CError's constructor, stays `differs`, written and right. All 67 of its 787 rows that differ are operands, and the
#     first the scan cannot re-point is the literal " - ": the target's lies in the tail of ") - ", which fn 690 holds, a helper
#     of vota/eleitor/comum/ctelasvota.cpp that builds `prefixo + " - cargo " + ... + ") - " + sufixo`. Ours lies in the tail
#     of "] - ". With that literal in a scratch link, `pnpm wasm splat-remap ... --against 1143 --no-kinds` prints IDENTICAL.
#   - 3858, __to_chars_itoa<unsigned>, is not ours to match from libc++.a: the target loads its power table through an
#     i32.add of the address and ours folds the address into the load's offset, one row no name changes, so it has no hand
#     line. It calls 2869, which keeps its digit helpers out of line (3856 3852 2867 3850) where ours inlines them, 357 over
#     486 rows. Which object's copy the target has is not measured; the executable TU's level, -Oz, is the lead.
#   - 9258 waits for 2416, std::regex's constructor, whose row stops at std::collate<char>::id (.bss), no target symbol.
#   - 1877 and 5162 wait for the slot of parse_iso_time, 5851 (9824 B), whose one direct caller is uenux2's 11616. Instantiated
#     in roots_boost.o, at APP_CXXFLAGS, in a scratch link, it scores 2708 over 4726 rows, 1764 deleted: not the target's body.
#   - 9032 waits for 306, the executable TU's. 2204 is a Boost body whose callers (5204 9570 9576 9578 9583) are not written.
#
# Hand line: CSerialMidia::ValidaSerial (9258), a callee with one user, the slot 9259's constructor takes, or 9259 stays
# `self-voted`: the literal only it loads is its own evidence, and the line says so. 9258 itself stays `unresolved` (above).
#
# Renames at this unit: 454 to CError's D0 and 556 to std::format_error's D0, twins whose first copy moved to roots_uenux2.o,
# and 710's merge body, named after its first member.
$(ROOT)/$(APP)/112-ecourna-cbasetype-roots.o: $(ROOT)/src/units/112-ecourna-cbasetype-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/112-ecourna-cbasetype.mk $(shell find $(ROOT)/src/ecourna -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c /work/src/units/112-ecourna-cbasetype-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/112-ecourna-cbasetype-roots.o
