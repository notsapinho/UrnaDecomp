# Two uenux2 functions whose callers are not written, each in the file of its own the evidence below points to.
#
# comum::md::estadoaplicacao::CEstadoGeral::SetAjusteDataHora (target fn 3705, 12 B), matched, in
# src/uenux2/src/app/comum/dados/md/estadoaplicacao/cestadogeral.cpp, declared in cestadogeral.h. Evidence: its three
# callers, 7160, 7306 and 10710, take the object from comum::CAppInfo::GetGeral() (fn 291), read the 8-byte
# CAjusteDataHora at +52 inline (CEstadoGeral's adjustment, cestadogeral.h), change it with
# CAjusteDataHora::AdicionaDeltaT (fn 3702) and pass it to 3705, which stores the 8 bytes back at +52. Chosen: the name
# (no record, slot or RTTI names it), the file (the class's own, whose one record, RecuperarCertificado's at line 147,
# fn 5635, holds that function's generated stub: docs/how-to-decompile.md step 3, "When no record names the file",
# rule 4), the line after it, and its being a member: it writes the class's member at +52, which cestadogeral.h
# declares private, an access the header chooses. Whole link, before step 9: `score 0 over 6 rows
# (same 6, replaced 0 [0 operand-only], inserted 0, deleted 0) BYTE-EXACT`; step 8 names it by pair-fingerprint.
#
# api::TerminaComBarraInvertida (target fn 5484, 131 B), matched, in src/uenux2/src/api/io/cinistrings.cpp, a new file,
# declared in a new api/io/cinistrings.h: whether a line ends in a run of backslashes of odd length. Evidence: its one
# target caller, fn 5480 (8780 B, not written), calls it twice and holds the records of
# api::CIniStrings::ParseKeyLine (cinistrings.cpp lines 183 and 187, which stay blank); in use band 2 (ledger/ordinals.tsv)
# it and 5485, another helper only 5480 calls, link right before cinikey.cpp's CIniKey::operator= (5483), and in the data
# cinistrings.cpp's record (1584092) lies right before cinikey.cpp's (1584124). Chosen: the name, the file, the line,
# its being a free function of api with external linkage (it reads no class state: docs/how-to-decompile.md step 3,
# "Names no evidence gives"; a static member of api::CIniStrings, whose only records name the static ParseKeyLine,
# gives the same bytes) and the header. Measured alone (tools/round/try-tu.sh --single 5484): a reverse index loop
# that counts the backslashes, `37 over 74 rows`; the same over reverse iterators flipping a bool, `40 over 76`; the
# empty string and the last character tested before a counting loop, `25 over 79`; the form written, those two tests
# before a loop that flips a bool, `score 0 over 71 rows ... BYTE-EXACT`, and the same in the whole link.
#
# api::CIniStrings::FindKey (target fn 10877, 12 B, matched) and EndKey (the end fn 6044 calls, fn 5481, a body the
# target keeps once for boost's sp_counted_impl_pd::get_untyped_deleter too), in cinistrings.cpp after
# TerminaComBarraInvertida, declared with the class's head in cinistrings.h: the find and the end of the std::map at +12
# of the INI object fn 5480 loads, which comum::md::CVersoesContratos::GetValor and CDependenciasContratos::GetValor
# (fragment 227) call out of line. Evidence: their merged body, fn 6044, calls both with its own `this`, and 10877 is
# `f163(p0 + 12, p1)`, the map's find; in the uses-1 band 10877 lies between api/hwil's rows (10880, 10881) and
# api/util/cajustedatahora.cpp's (10874 to 10876), where api/io's objects fit. Chosen: the class (CIniStrings, whose
# static ParseKeyLine fn 5480 holds: a reading, cinistrings.h says it), the names, the iterator type, that they are not
# const, the file and the lines. Whole link, before step 8: 10877 `score 0 over 7 rows`; step 8 names it by
# pair-fingerprint. Their callers are fragment 227's sources, so the roots below need no stand-in for them.
#
# comum::md::estadoaplicacao::CEstadoGeral::GetResumoHashVersoesPacotes (target fn 3703, 1126 B), added for unit 287's
# ImprimeVersoesPacotes (11222), in cestadogeral.cpp after SetAjusteDataHora, written and `differs`: 133 over 556 rows
# (pnpm wasm score, whole link). It is the first 8 characters of ecourna::api::security::EncodeBase64 of the hash at
# +168 (the packages' hash, cestadogeral.h), and holds EncodeBase64 inlined by binaryen with its records base64.cpp:247
# and :267, EncodeBase64's one caller in our link as in the target; the rows that differ are that inlined code's,
# base64.cpp's form (unit 00's note; read from the score's alignment). Its target callers are 3059 and 7787, not in our
# link (src/app/roots_ecourna.cpp's UsaBase64A and UsaBase64B stand for them), and 11222, in it. In use band 3 it links
# after 3705 and 3704, so after SetAjusteDataHora in the file. The hash goes into a named local before substr(0, 8):
# this tree's -std=c++23 makes the temporary's substr the rvalue overload, which docs/reference/facts/app-flags.md F1
# measured changing 3703 (that form was not linked here). No generated line names it: its opcodes differ, so no
# srcloc-anchor, and its caller in our link, 11222, is named by its vtable slot, which casts no vote (unit 287 says why
# there is no hand line). Chosen: the name, its being a member (it reads the class's +168, private in cestadogeral.h),
# the file (the class's own) and its line.
#
# comum::md::estadoaplicacao::CEstadoGeral::GetDadosQRCode (target fn 5636, 3903 B), matched, in cestadogeral.cpp: the
# state as key and value pairs for comum::CQRCodeDS (fragment 299, which has the class's evidence), each pushed with
# push_back(std::make_pair(tag, value)): a value that is a string member is copied into the make_pair temporary, whose
# tag the target then reloads after the copy's out-of-line call and measures with strlen, while a computed value's tag
# is folded (cestadogeral.h lists the tags and their conditions). Evidence for the place: in use band 2 it links between
# 5637 (the constructor, below) and 5635 (RecuperarCertificado, record line 147, not written), stretch 804 of
# ledger/tu-clusters.tsv (label cestadogeral.cpp), so it is defined before line 147; its lines there are a choice. idPE
# is formatted with std::to_string(unsigned int) (fn 327), so cestadogeral.h's idPE is uedword now; every other object
# compiles to the same bytes with the header edits (cmp of each object before and after). Whole link, before steps 7
# to 9: 104 over 1771 rows, all operand-only. Chosen: the name, its being a member (it reads the members), the locals.
#
# comum::md::estadoaplicacao::CEstadoGeral's constructor from its eight parts (target fn 5637, 222 B), matched, in
# cestadogeral.cpp before GetDadosQRCode, declared in cestadogeral.h: it stores the state and idPE, moves the locality
# (its string zeroed in the argument), copies the load and the adjustment, copies the correspondence through fn 1249,
# and moves the version and the hash, at the offsets cestadogeral.h gives, in the parameters' order. Its one direct
# caller is 11398 (unit 124's CConversorEstadoGeral::DoDesconverte), which copies each part it passes by value and
# passes its correspondence's local with no copy (cestadogeral.h has the forms). Its table slot 427 is passed to
# invoke_iiiiiiiiii by fn 10205 alone (not written; docs/reference/facts/units.md U11's script), and a function the
# table holds keeps its body under one direct call (src/units/README.md "Companion files"): the roots take its address
# for 10205. The place is a reading: in use band 2 it links between md/rdv/cvotoseleicoesvota.cpp's 5638 and
# GetDadosQRCode (5636), as cestadogeral.cpp's first function would; a definition in the class was not measured. Its
# object code as written equals the target's 5637 but the call (wasm-objdump of the object beside pnpm wasm fn's
# disassembly); whole link before step 8: `score 1 over 91 rows (same 90, replaced 1 [1 operand-only], inserted 0,
# deleted 0)`, the call of 1249. Step 8 names it by 11398's call vote (`evidence:call by:11398`). Chosen: the parameter
# names and its lines.
#
# 215-uenux2-api-app-leftovers-roots.cpp stands for the callers: 5480 (twice) for 5484, 3059 for 5636 (11200, unit
# 123's, is in the link) and 10205 for 5637 (its address); 3705's stand-in went, its callers 7160, 7306 and 10710
# (units 329, 104, 277) in the link.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
LEFTOVERS_UENUX2_SRCS := src/api/io/cinistrings.cpp src/app/comum/dados/md/estadoaplicacao/cestadogeral.cpp
UENUX2_SRCS += $(LEFTOVERS_UENUX2_SRCS)
# the roots declare what they call through asm labels, so their rule needs no header
$(ROOT)/$(APP)/215-uenux2-api-app-leftovers-roots.o: $(ROOT)/src/units/215-uenux2-api-app-leftovers-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/215-uenux2-api-app-leftovers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/215-uenux2-api-app-leftovers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/215-uenux2-api-app-leftovers-roots.o
