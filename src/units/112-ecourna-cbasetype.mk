# CBaseType<TYPE, MIN_VAL, MAX_VAL, BASIC_TYPE>'s constructor (ecourna's api/pattern/cbasetype.hpp), the copies uenux2's
# objects kept and the ones ecourna's did, and CStringUtils::Trim (api/util/cstringutils.cpp, unit 00's source) with the
# functions that stop at it. The constructors have no source of their own: they are the header's code, so this fragment
# holds the evidence and the roots rule. The bodies of src/ecourna/api/util/cstringutils.cpp stay unit 00's.
#
# Matches, 22 target functions:
#   - uenux2's copies, from app/roots_cbasetype.o: 2299, binaryen's merge of the 16-bit constructors, with its thunks 1960
#     (TQtdEleitor) 2277 (TAno) 2850 (TScoreHabilitacao) 5848 (TSecaoID) 5850 (TZonaID); 6042, the 32-bit merge, with 2851
#     (TMunicipioID) 5849 (TLocalID); 5682 (TCargoID), a body of its own, since MIN_VAL 1 gives it another range test.
#   - ecourna's copies, from app_dados_tiposbasicos.cpp.o: 2666 (TTipoIdentificadorEleitor, instantiated there and
#     called out of line: below), and 2668,
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
# first object wins. So src/Makefile's UENUX2_PREFIX_MAP gains the third spelling (facts/app-flags.md F6 has its evidence),
# and src/app/roots_cbasetype.cpp, ahead of both trees, instantiated the eight constructors explicitly while no real uenux2
# caller of them was written, since a fragment's roots link after ecourna's objects, which would keep their own copies
# (`source_location not in the target`, 5682's row before this unit). 11616 (unit 122's cgravadorrcsecao.cpp) is written
# and calls six, which match from uenux2 objects now (TAno's from cjustificador.cpp.o, the five others from 11616's), so
# the root keeps 1960's and 5682's. This unit's roots file only calls them.
#
# roots_cbasetype.o compiles at UENUX2_CXXFLAGS, not APP_CXXFLAGS: the constructors are the same at both, but the libc++
# format bodies the instances bring to the head of the link are not, and those stay the tree's code this way.
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
# throw: no record fixes lines 34 to 38. The column reads as a body inside the class at TSE's 4-space indentation (a
# member's throw inside an `if` is at 19, as iconversorasn.hpp's 66:19; a definition at namespace scope puts it at 15, as
# cnumerocpf.cpp's 20:15): the definition below the class (next paragraph) keeps the in-class indentation, a choice that
# keeps the record's column. The forms above were measured with the constructor defined in the class. With it below,
# the constructor's declaration sits on line 23 and Get, operator TYPE and m_valor on lines 25 to 29, above the record:
# their lines are a choice.
#
# TTipoIdentificadorEleitor's constructor out of line, evidence. 2666's callers in the target call it with a constant:
# 3939, binaryen's merge of CNumeroCPF's, CNumeroIdentificacaoLivre's and CNumeroInscricaoEleitoral's constructors (unit
# 00's; their thunks 5107, 5106 and 1241 pass 2, 3 and 1), and 9116, CConversorIdentificadorEleitor::DoDeconverte
# (`f2666(p1 + 24, 2)`, `(p1 + 20, 3)` and `(p1 + 28, 1)`: `pnpm wasm fn ../target/vota_web_wasm.wasm 9116`). With a
# constant the range test folds, and clang inlines the constructor where it has the body. The copy the target keeps is
# tiposbasicos.cpp.o's: its record (1122400) follows the three constructors' (1121860, 1121944, 1122040), so none of their
# objects defined one. Here app/dados/tiposbasicos.hpp declares the instance `extern template` and tiposbasicos.cpp
# instantiates it, after CErroLeituraBiometria's constructor, where the record lies; the stand-in that made the copy
# there (CriaTipoIdentificadorEleitor) went, and so did unit 07's two stand-in callers of 2666. Measured on
# cnumerocpf.cpp's object at its flags (wasm-objdump -d): with the constructor defined in the class, the extern template
# leaves the object byte-identical (clang instantiates an inline member of an extern template to inline it, and inlines
# it); defined below the class, not inline, it stays a call (frame +76 and 2, then an i32.load of the value), the
# target's rows. The line's place, in the header the four calling files include, is a choice, and so is its naming the
# class: cnumerocpf.cpp's object is the same with the line in that file after its includes and none in the header, and
# with the header's line naming the constructor alone; with the constructor below the class and no line, it is inlined
# (each form a copy of the sources compiled at that object's compile line, compared with cmp). 3939 then matches at
# step 9 (33 over 375 rows, all operand-only, at step 6), and no match moved. 9116 calls 2666 three times with the
# target's constants now and reads `unresolved` on CIdentificadorEleitor::Cria (3497 of our link, unit 00's
# cfabricaidentificadoreleitor.cpp), which ours calls and the target's 652-byte body holds inlined (ours is 360 bytes).
# The explicit instantiation of the class, not of the constructor alone, is a choice: the object's Get and operator
# TYPE copies leave the link.
#
# CStringUtils::Trim(std::string&), evidence, each measured on the whole TU (16 functions, same-length paths, numbers masked):
#   - the first test is a select over both sizes, loaded before it. `!std::empty(valor)` is written, and `std::size(valor) >
#     0`, `std::size(valor) != 0` and `valor.compare("") != 0` give the same functions. `!valor.empty()`, the form before this
#     unit, `valor.size() > 0`, `valor.length() > 0` and `valor != ""` branch on the long bit first (188 rows of 186). Without
#     -fno-delete-null-pointer-checks `!valor.empty()` gives the select too, so that flag is what those forms get round
#     (facts/app-flags.md F3 has the flag). Which of them is a choice.
#   - the empty path holds no erase. The `if` around both erases is a choice: `if (std::empty(valor)) { return; }` ahead of
#     them gives the same object.
#   - the second erase is the iterator form (one begin for find_if and the difference, then erase's npos test before the
#     short and long paths). `erase(0, find_if(...) - begin())` splits the difference over the two paths.
#   - the first erase takes a position: `erase(ultimo.base(), end())` gives another object (138 of 186 rows).
#     `std::distance(rbegin, ultimo)` for the difference gives the same one.
#   - a lambda for NaoEhBranco gives the same object. The named function is a choice.
#
# Trim(const std::string&): 1374 is `f3942(p0, p1, slot 6416)`, and elem[6416] is 9406, so a copy of the string, Trim, and
# the copy returned; 1879 and 5156 are the same over 5158 and 3509. It has no record: that it is a static member called Trim,
# and its line beside the other Trim, are choices, and `std::string resultado(valor);` gives the same object. 3509 and
# 5156, ToUpper in place and its copying form, are unit 00's, and the merge forms from 1374, 1879 and 5156 (3942).
#
# The converters and HexStringToBytes, evidence. All three call the copying Trim, and clang inlines it (the object has the
# invoke and no call of 1374): `invoke` of slot 6416 with a landing pad of its own, that frees the copy and resumes, apart
# from the function's other cleanups. `std::string
# texto(valor); Trim(texto);` has one pad for both: 609 of 3506's 670 rows move, and 2202 scored 13 rows inserted and 31
# deleted.
#   - 2202 and 5155 throw EUE_VALOR_INVALIDO on an empty string (br 2 out of the size test, to the first throw), so `texto.empty() ||`
#     stands before find_first_not_of. Without it 602 of 681 rows differ, with `std::empty(texto)` 590: the member is
#     evidence here. `texto` without `const` gives the same object.
#   - 3506's throw is 808:15, one level deep, so the check is one `if`, not a loop with an `if` inside. `std::all_of` over a
#     lambda is written. `[](char c) { return isxdigit(c); }`, `std::any_of` over the negation and `!std::none_of` give the same
#     object, and `std::find_if_not(...) != end()` does not (577 of 670 rows).
#   - 3506 has no test of its own for an empty string: without one the object has the target's, the size test as the check
#     loop's entry and the vector's two stores on the empty path. `if (texto.empty()) return {};` gives another (575 of 670).
#   - the loop's bound is computed once, ahead of the loop: `i < static_cast<int>(texto.size()) - 1` in the `for` reloads it,
#     597 of 670 rows. Unsigned in `tamanho / 2`, signed in the bound (`i32.shr_u`, `i32.lt_s`). Same object: `tamanho` left
#     out for two calls of size(), `static_cast<int>(tamanho - 1)`, and `(alto | baixo) >= 0`. The local is a choice.
#   - HexCharToInt takes int: the compares are on the sign-extended byte. With `char` 305 of 670 rows differ.
#
# Left, each measured:
#   - 9215, TPartidoID's constructor, is ecourna's copy (b/src record) with table slot 6695. It left this list when its
#     users landed: it matches from cconversorfederacao.cpp's object, unit 105's. In tiposbasicos.cpp NOME's definition
#     folds, 25 rows, which a converter's TU does not see.
#   - 1143, CError's constructor, left this list: it matches since fn 690 (vota::MensagemErroCargo, unit 110's
#     ctelasvota.cpp) is in the link, and fn 3645 (RenameResource, unit 32's csystem.cpp) holds the same tail. Its
#     literal " - " lies in the target in the tail of ") - ", which fns 690 and 3645 hold; while
#     690 was not written, ours lay in the tail of "] - ", and all 67 of its 787 rows that differed were operands.
#   - 3858, __to_chars_itoa<unsigned>, is the executable TU's copy: libc++.a's loads its power table with the address
#     folded into the load's offset where the target adds it, and its 2869 inlines the digit helpers (3856 3852 2867
#     3850) that the target keeps out of line. All six match from that TU's object at -Oz (unit 170).
#   - 9258 matches since unit 84's CMenuItem::GetTextoFormatado (5492) votes for 2416, std::regex's constructor, beside
#     it (docs/reference/facts/splat.md S10 item 23).
#   - 1877 and 5162 wait for the slot of parse_iso_time, 5851 (9824 B), whose one direct caller is uenux2's 11616. Instantiated
#     in roots_boost.o, at APP_CXXFLAGS, in a scratch link, it scored 2708 over 4726 rows, 1764 deleted: not the target's body.
#     The link's copy is cgravadorrcsecao.cpp's now (unit 122, which has what 5851 waits for).
#   - 2204, a Boost body, matches from clzmacompress.cpp.o with two of its callers, 5204 and 9576, since the tree root
#     src/app/roots_boost.cpp leaves the app signal's operator() to unit 06's objects (fragment 06); its callers 9570,
#     9578 and 9583 match too, since the Boost probe calls no disconnect (fragment 06). 9032, which waited for 306,
#     matches since src/app/roots_vector.cpp holds it.
#
# Hand line: CSerialMidia::ValidaSerial (9258), a callee with one user, the slot 9259's constructor takes, or 9259 stays
# `self-voted`: the literal only it loads is its own evidence, and the line says so. 9258 itself matches (above).
#
# Rename at this unit: 556 to std::format_error's D0, a twin whose first copy moved to roots_cbasetype.o.
$(ROOT)/$(APP)/112-ecourna-cbasetype-roots.o: $(ROOT)/src/units/112-ecourna-cbasetype-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/112-ecourna-cbasetype.mk $(shell find $(ROOT)/src/ecourna -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c /work/src/units/112-ecourna-cbasetype-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/112-ecourna-cbasetype-roots.o
