# The first ecourna unit: the voter-identifier classes of app/dados (IIdentificadorEleitor, CNumeroCPF,
# CNumeroInscricaoEleitoral, CNumeroIdentificacaoLivre, CFabricaIdentificadorEleitor) and what they call: CError
# (api/exception), base64 (api/security) and CStringUtils (api/util). The ecourna flags were measured on these units
# (docs/reference/app-flags.md); src/app/roots_ecourna.cpp calls them with the target's call-site counts.
# CStringUtils::Trim, the two converters and HexStringToBytes match since src/units/112-ecourna-cbasetype.mk, which has their
# evidence and the stand-ins for their other callers.
# CStringUtils::PreencheADireita (target fn 3511) pads a string in place on the right with a character up to a length.
# Its callers are api::CInputFieldMT::Draw (fn 10726, src/units/146-uenux2-cinputfieldmt.mk) and fns 11972 and 11973
# (CDataSourcesRelatorio's DetalheCandidato and DetalheCandidatoZE, src/units/183-uenux2-relatorios.mk), all in the link,
# so roots_ecourna.cpp no longer stands for them. No record names it. Its use band, 3, puts it
# between fn 3513 (api/sql/sqlite/csqlstatement.cpp) and this file's ToInt16 (fn 3508), with fns 3509, 3510 and 3512
# (`awk -F'\t' 'NR>1 && $2==3 && $1>=3505 && $1<=3514' ledger/ordinals.tsv`). That it is this file's is a reading of
# that, and its name, after PreencheAEsquerda's, its being a CStringUtils member and its line after PreencheAEsquerda are
# chosen.
# The zero helpers and the copying pad, read from their bodies, with no record either, so every name below, each being
# a CStringUtils member and each line is chosen; the in-place and copying overloads follow Trim's pair:
# - PreencheAEsquerda(std::string&, char, size_t) (fn 3512) pads in place on the left. Its callers, 566 and 2798 (unit
#   178), pass '0', which binaryen folds into the body (reading.md R1), so the char parameter is a choice too.
# - RemoveZerosAEsquerda(std::string&) (fn 3510) erases the leading '0's: erase(0, find_first_not_of('0')). It returns
#   the string, a measured form: as void it scored 15 over 91 rows in the whole link (locals renumbered, 1 row inserted,
#   1 deleted), and returning erase's result, which every caller drops (binaryen removes it, R2), 0 over 90.
# - RemoveZerosAEsquerda(const std::string&) (fn 5159; callers 566's inlined IRegraIdentidade::Valida and 3723) copies,
#   then erases: its landing pad wraps the erase's __erase_external_with_move itself, so clang inlined the in-place
#   form into it and the two share this TU (a reading).
# - PreencheADireita(const std::string&, char, size_t) (fn 1881) pads a copy on the right; its five callers pass ' '
#   (folded) and roots_ecourna.cpp's UsaPreencheCopiaA and B stand for them.
# The bands give the order: in uses 3, read in link order, 3512, 3511, 3510, 3509, then ToInt16 (3508), so 3512 sits
# above PreencheADireita and 3510 below it (3509, ToUpper in place, below, is the upper-case counterpart of ToLower: a reading
# of its body). In uses 2, 5159 comes right before 5158, and in uses 6, 1881 before 1880 and 1879: 5158 and 1879 are the
# two ToLower that src/units/12-ecourna-api-sql-sqlite-externs.cpp holds for this file, so neither band has a neighbour
# in this object, and 5159 and 1881 sit beside their in-place forms by choice.
# IIdentificadorEleitor's constructor (9256) matches. Its zero string is a temporary in the condition, destroyed before the
# throw as in the target; as a named local it lives across the throw (241 rows against 52 in try-tu.sh --single, with the
# record's line right in both). iidentificadoreleitor.cpp is Latin-1: the target's literal is 60 bytes of Latin-1
# (ledger/strings.tsv row 377803), and the UTF-8 file gave 64. The gap above the constructor (the comment of original
# lines 10-23 and `#line 24`) puts its throw on its record's line, 28; where the constructor starts is chosen.
# Target fn 3703, which holds EncodeBase64's two records, is not EncodeBase64: it is a caller that binaryen inlined
# EncodeBase64 into, returning `.substr(0, 8)` of the result for an object with a std::vector<uebyte> at +168 (callers
# 3059, 7787, 11222); roots_ecourna.cpp's ResumoBase64 has that shape, and the class is not identified, so 3703 waits for
# it. Against the stand-in it is 135 rows over 556, among them both size computations: the target's is
# (n << 2) - ((n / 3) << 3), and base64.cpp's `(n / 3 + n % 3) * 4` compiles to an i32.mul of n / 3 by 3 (so do
# `4 * (...)`, the terms swapped, `n / 3 * 4 + n % 3 * 4` and `n % 3` written out); `(n - n / 3 * 2) * 4` computes both
# without one (base64.cpp's object, instruction kinds only). base64.cpp stays as it was until 3703's class is written.
#
# CStringUtils' string members, all matched but FindRegex, none named by a record, so every name below, each being a
# CStringUtils member and each one's line is chosen; the overloads follow Trim's pair and unit 12's Replace. That their
# file is this one is a reading of the bands (ledger/ordinals.tsv), as for the zero helpers above: in uses 3, 3509 lies
# between 3510 and 3508; in uses 6, 1880 between 1881 and 1879; in uses 5, 2199 right after 2200; in uses 1, 9407 right
# before 9406 (Trim), and the Boost.Regex code 2199 calls (9399 to 9401) between 9402 and 9398, the static destructor and
# Replace of unit 12's externs. ToUpper's static set and guard (1911820, 1911832) sit right before ToLower's (1911836,
# 1911848) in the target's .bss.
# - Replace in place (fn 9407) replaces every occurrence of a string, the search going on after each replacement; it reads
#   both sizes into locals before the loop and returns at once when the searched string is empty. `const size_t
#   tamanhoDe = de.size(); if (tamanhoDe == 0)` tests the size with one select, as the target does; `if (de.empty())`
#   ahead of the locals branches once per string form (each object's first rows; both forms otherwise alike). Its copying
#   form (2677) copies, then calls it through invoke_viii, the copy having a landing pad.
# - Split (1880) cuts a string at each separator: an empty piece is push_back(""), a non-empty one
#   emplace_back(resto, 0, posicao), whose 0 the target stores in its frame (the literal's type, int, is chosen: a
#   plain 0) and whose __emplace_back_slow_path (9404) matches with it; the last piece is push_back(resto). Its landing pad calls the
#   -Oz ~vector<std::string> read as the executable TU's (2255), which src/app/roots_vector.cpp holds.
# - ToUpper in place (3509) is ToLower's counterpart over the same 19 accented capitals (the 76 bytes at 1118052, which
#   5158 reads too): its static set is built by transforming the capitals with | 32 through std::inserter
#   (insert_iterator::operator=, 9397, matches with it), each read as a char (the target's load8_s, a char parameter's),
#   and it upper-cases with & ~32 or toupper. The capitals come from a file-static helper that returns their set,
#   AcentuadasMaiusculas, which clang inlines: with the list written inline, the init lambda's frame held the array at +8,
#   the list at +88 and the set at +96; through the helper, the set at +8, the array at +24 and the list at +104, the
#   target's (a reading: an inlined callee's allocas come first in the frame). 3509's votes name the set and its guard
#   (evidence:vote:10 and vote:2 by:3509 in splat/symbol_addrs.txt): 654's call names 3509, and their bodies are the same
#   opcodes; 9403, the set's static destructor, matches over the set's name, and the guard sits at our link's distance
#   from the set (docs/reference/facts/splat.md S13). The copying ToUpper (5156) is a thunk into binaryen's merge 3942, as the copying ToLower and
#   Trim are. ToLower stays in unit 12's externs, so std::set<int>'s constructor (5157), __tree<int>::destroy (1522) and
#   __find_equal (2676), and __split_buffer<std::string>'s destructor (5184), come from this object now, which ToUpper and
#   Split instantiate first, ahead of the externs and datahoraasn.cpp.o on the link line; they are linkonce copies and
#   their places in this object are no evidence.
# - FindRegex (2199), written and `unresolved`: the start and end of a boost::regex's first match in a string, npos for
#   both when there is none, either string is empty, or the regex throws (catch (...)). The regex, the boost::cmatch and
#   inicio/fim, set to npos and changed on a match, are locals of the try block, which returns {inicio, fim}: that gives
#   the target's one store of the result for a match and for none; returning from inside the if gave the case of no
#   match a cleanup of its own (pnpm wasm score 2199: 111 rows inserted). `{std::string::npos, std::string::npos}` loads
#   npos from its definition (the object's i32.load of _ZNSt3__212basic_string...4nposE; a reading: std::pair's
#   constructor binds it by reference), so the npos results go through a local copy, naoEncontrada. Its callers 654 and 1539 match. It waits for Boost.Regex's
#   -fexceptions copies: its callees do_assign (9401) and regex_search (9400), both with landing pads in the target, read
#   as this file's instantiations (their band, above), and our link takes do_assign from src/app/roots_boost.o (APP_CXXFLAGS, no -fexceptions),
#   which links first: `ours +0x5f i32.const 2875: a table slot of ours: ...do_assign... has no target function`
#   (splat/scan.tsv). The same copies keep match_results<const char*>'s destructor (5153) inlined in our link: its other
#   target caller, 5121, reads as the -fexceptions perl_matcher's push of a saved state with a copy of the results, which
#   our link does not hold.
# The members by band in this object (target index/ld_index in build/out/wasm-map/vota_web/names.tsv) follow the target's
# order but where a linkonce copy is involved, and 9407 lies, as Trim (9406) already did, after CBaseError<EUtilError>'s
# constructor (9410), which uses 1 puts before both.
ECOURNA_SRCS += api/exception/cerror.cpp api/security/base64.cpp api/util/cstringutils.cpp app/dados/iidentificadoreleitor.cpp \
                app/dados/cnumerocpf.cpp app/dados/cnumeroinscricaoeleitoral.cpp app/dados/cnumeroidentificacaolivre.cpp \
                app/dados/cfabricaidentificadoreleitor.cpp
