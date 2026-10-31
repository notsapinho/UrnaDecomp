# The first ecourna unit: the voter-identifier classes of app/dados (IIdentificadorEleitor, CNumeroCPF,
# CNumeroInscricaoEleitoral, CNumeroIdentificacaoLivre, CFabricaIdentificadorEleitor) and what they call: CError
# (api/exception), base64 (api/security) and CStringUtils (api/util). The ecourna flags were measured on these units
# (docs/reference/app-flags.md); src/app/roots_ecourna.cpp calls them with the target's call-site counts.
# CStringUtils::Trim, the two converters and HexStringToBytes match since src/units/112-ecourna-cbasetype.mk, which has their
# evidence and the stand-ins for their other callers.
# IIdentificadorEleitor's constructor (9256) matches. Its zero string is a temporary in the condition, destroyed before the
# throw as in the target; as a named local it lives across the throw (241 rows against 52 in try-tu.sh --single, with the
# record's line right in both). iidentificadoreleitor.cpp is Latin-1: the target's literal is 60 bytes of Latin-1
# (ledger/strings.tsv row 377803), and the UTF-8 file gave 64. The blank lines above the constructor put its throw on
# its record's line, 28; where the constructor starts is chosen.
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
