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
# above PreencheADireita and 3510 below it (3509, not written, reads as the upper-case counterpart of ToLower: a reading
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
ECOURNA_SRCS += api/exception/cerror.cpp api/security/base64.cpp api/util/cstringutils.cpp app/dados/iidentificadoreleitor.cpp \
                app/dados/cnumerocpf.cpp app/dados/cnumeroinscricaoeleitoral.cpp app/dados/cnumeroidentificacaolivre.cpp \
                app/dados/cfabricaidentificadoreleitor.cpp
