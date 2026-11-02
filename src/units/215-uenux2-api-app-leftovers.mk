# Two uenux2 functions whose callers are not written, each in the file of its own the evidence below points to.
#
# comum::md::estadoaplicacao::CEstadoGeral::SetAjusteDataHora (target fn 3705, 12 B), matched, in
# src/uenux2/src/app/comum/dados/md/estadoaplicacao/cestadogeral.cpp, declared in cestadogeral.h. Evidence: its three
# callers, 7160, 7306 and 10710, take the object from comum::CAppInfo::GetGeral() (fn 291), read the 8-byte
# CAjusteDataHora at +52 inline (CEstadoGeral's adjustment, cestadogeral.h), change it with
# CAjusteDataHora::AdicionaDeltaT (fn 3702) and pass it to 3705, which stores the 8 bytes back at +52. Chosen: the name
# (no record, slot or RTTI names it), the file (the class's own, whose one record, RecuperarCertificado's at line 147,
# fn 5635, stays blank: docs/how-to-decompile.md step 3, "When no record names the file", rule 4) and the line after
# it. It is a member because it writes the class's private member. Whole link, before step 9: `score 0 over 6 rows
# (same 6, replaced 0 [0 operand-only], inserted 0, deleted 0) BYTE-EXACT`; step 8 names it by pair-fingerprint.
#
# api::TerminaComBarraInvertida (target fn 5484, 131 B), matched, in src/uenux2/src/api/io/cinistrings.cpp, a new file,
# declared in a new api/io/cinistrings.h: whether a line ends in a run of backslashes of odd length. Evidence: its one
# target caller, fn 5480 (8780 B, not written), calls it twice and holds the records of
# api::CIniStrings::ParseKeyLine (cinistrings.cpp lines 183 and 187, which stay blank); in use band 2 (ledger/ordinals.tsv)
# it and 5485, another helper only 5480 calls, link right before cinikey.cpp's CIniKey::operator= (5483), and in the data
# cinistrings.cpp's record (1584092) lies right before cinikey.cpp's (1584124). Chosen: the name, the file, the line,
# its being a free function of api with external linkage (it reads no class state: docs/how-to-decompile.md step 3,
# "Names no evidence gives") and the header. Measured alone (tools/round/try-tu.sh --single 5484): a reverse index loop
# that counts the backslashes, `37 over 74 rows`; the same over reverse iterators flipping a bool, `40 over 76`; the
# empty string and the last character tested before a counting loop, `25 over 79`; the form written, those two tests
# before a loop that flips a bool, `score 0 over 71 rows ... BYTE-EXACT`, and the same in the whole link.
#
# 215-uenux2-api-app-leftovers-roots.cpp stands for the callers: 7160, 7306 and 10710 for 3705, 5480 (twice) for 5484.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
LEFTOVERS_UENUX2_SRCS := src/api/io/cinistrings.cpp src/app/comum/dados/md/estadoaplicacao/cestadogeral.cpp
UENUX2_SRCS += $(LEFTOVERS_UENUX2_SRCS)
# the roots declare what they call through asm labels, so their rule needs no header
$(ROOT)/$(APP)/215-uenux2-api-app-leftovers-roots.o: $(ROOT)/src/units/215-uenux2-api-app-leftovers-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/215-uenux2-api-app-leftovers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/215-uenux2-api-app-leftovers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/215-uenux2-api-app-leftovers-roots.o
