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
# comum::md::estadoaplicacao::CEstadoGeral::RecuperarCertificado (target fn 5635, 279 B), matched, at its record's line
# 147 of cestadogeral.cpp (static, returning std::vector<uebyte> by value, as the record reads; the line holds the
# default argument of CPolySingleton<api::pkcs11::IPkcs11>::instance() at column 41, `api::pkcs11::IPkcs11& oPkcs11 = `
# before it a choice of what fills the column), with its static vector's exit destructor, fn 11268, this object's
# __cxx_global_array_dtor, matched by content: 5635 and 11268 alone load the static (@1839076, cestadogeral.h), step 8
# names it by 5635's vote (`vote:5 by:5635`), and 11268 is its second user. 5635 reads the certificate through IPkcs11's
# slots 23, 10 and 24 the first time and returns a copy. Whole link, before steps 7 to 9 (pnpm wasm score): with slot 10
# returning a const std::vector<uebyte>, 20 over 121 rows, operand-only, but a 16-byte frame with the result at +4 where
# the target has 48 and +12; with slot 10 returning a 36-byte object whose vector at +0 is copied through an accessor
# (api::pkcs11::SResultadoCertificado, ipkcs11.h), 11 over 121, all operand-only (the static's address, calls).
# CEstadoGeral::GetDadosQRCodeCertificado (target fn 5634, 2021 B, a chosen name), after it in cestadogeral.cpp, written
# and not matched (no-candidate: nothing names it, so its stub in src/uenux2/unplaced.cpp stays): the certificate's QR
# code fields; cestadogeral.h has what the body does and its callers, fns 12110 and 12039, neither written (unit 220's
# roots stand for both). It stays written: it is 5635's one caller, and the stand-ins' destruction of its result brings
# fn 5980 (unit 220). Whole link: first written with the second certificate's size inside the count's expression and the
# hex text's length read after the result vector is declared, 75 over 973 rows (15 inserted, 14 deleted); as written, 52
# over 963 (45 operand-only, 5 inserted, 2 deleted). The remainder is the destruction of that second call's result: the
# target frees it with no store of its end pointer (`__end_ = __begin_`, which our object keeps) and computes the size
# after the free. Each with that store, measured on variant compiles of cestadogeral.cpp's object (wasm-objdump -d): the
# size in a statement of its own (written), inside the expression, read from a named vector, an unsigned local of twice
# the size, a ternary for the count, GetDadosQRCodeCertificado above RecuperarCertificado, and the size inside the
# expression with -fno-strict-aliasing. Not explained. The name, the bool, the locals and 1082 as an int literal are
# chosen.
#
# api::TerminaComBarraInvertida (target fn 5484, 131 B), matched, in src/uenux2/src/api/io/cinistrings.cpp, a new file,
# declared in a new api/io/cinistrings.h: whether a line ends in a run of backslashes of odd length. Evidence: its one
# target caller, fn 5480 (8780 B, written in fragment 379, not matched), calls it twice and holds the records of
# api::CIniStrings::ParseKeyLine (cinistrings.cpp lines 183 and 187, written in fragment 379); in use band 2
# (ledger/ordinals.tsv) it and 5485, another helper only 5480 calls, link right before cinikey.cpp's CIniKey::operator=
# (5483), and in the data
# cinistrings.cpp's record (1584092) lies right before cinikey.cpp's (1584124). Chosen: the name, the file, the line,
# its being a free function of api with external linkage (it reads no class state: docs/how-to-decompile.md step 3,
# "Names no evidence gives"; a static member of api::CIniStrings, whose only records name the static ParseKeyLine,
# gives the same bytes) and the header. Measured alone (tools/round/try-tu.sh --single 5484): a reverse index loop
# that counts the backslashes, `37 over 74 rows`; the same over reverse iterators flipping a bool, `40 over 76`; the
# empty string and the last character tested before a counting loop, `25 over 79`; the form written, those two tests
# before a loop that flips a bool, `score 0 over 71 rows ... BYTE-EXACT`, and the same in the whole link.
#
# api::CIniFile::FindKey (target fn 10877, 12 B, matched) and EndKey (the end fn 6044 calls, fn 5481, a body the target
# keeps once for boost's sp_counted_impl_pd::get_untyped_deleter too): the find and the end of the std::map at +12 of
# the INI object fn 5480 loads, which comum::md::CVersoesContratos::GetValor and CDependenciasContratos::GetValor
# (fragment 227) call out of line. This unit wrote them in cinistrings.cpp as members of CIniStrings; fragment 379 moved
# them, bodies unchanged, into cinifile.cpp under the class it names CIniFile (step 9 renamed 10877's match line), since
# the band puts them in the loader's object after cinisection.cpp's and ParseKeyLine's records in cinistrings.cpp's
# before cinikey.cpp's (fragment 379 has the evidence). Their callers are fragment 227's sources, so they need no
# stand-in.
#
# comum::md::estadoaplicacao::CEstadoGeral::GetResumoHashVersoesPacotes (target fn 3703, 1126 B), added for unit 287's
# ImprimeVersoesPacotes (11222), in cestadogeral.cpp after SetAjusteDataHora, written and `differs`: 133 over 556 rows
# (pnpm wasm score, whole link). It is the first 8 characters of ecourna::api::security::EncodeBase64 of the hash at
# +168 (the packages' hash, cestadogeral.h), and holds EncodeBase64 inlined by binaryen with its records base64.cpp:247
# and :267, EncodeBase64's one caller in our link as in the target; the rows that differ are that inlined code's,
# base64.cpp's form (unit 00's note; read from the score's alignment). Its target callers are 3059 (unit 110's, in our
# link, written and not matched), 7787, not in it (src/app/roots_ecourna.cpp's UsaBase64B stands for it; UsaBase64A,
# for 3059, went), and 11222, in it. No vote names 3703: 3059 is named by a hand line and 11222 by vtable, and
# neither casts one. In use band 3 it links
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
# names, its lines, and copying the load and the adjustment: std::move on m_dadoCarga's and m_ajusteDataHora's
# arguments gives the same object (cmp).
#
# 215-uenux2-api-app-leftovers-roots.cpp stands for 10205's reference to 5637 (its address); 5484's stand-in went, its
# caller 5480 in the link (fragment 379); 3705's stand-in went, its callers 7160, 7306 and 10710 (units 329, 104, 277)
# in the link, and so did
# 5636's, which stood for 3059: 5636's callers 11200 (unit 123's) and 3059 (unit 110's) are in the link.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
LEFTOVERS_UENUX2_SRCS := src/api/io/cinistrings.cpp src/app/comum/dados/md/estadoaplicacao/cestadogeral.cpp
UENUX2_SRCS += $(LEFTOVERS_UENUX2_SRCS)
# the roots declare what they call through asm labels, so their rule needs no header
$(ROOT)/$(APP)/215-uenux2-api-app-leftovers-roots.o: $(ROOT)/src/units/215-uenux2-api-app-leftovers-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/215-uenux2-api-app-leftovers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/215-uenux2-api-app-leftovers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/215-uenux2-api-app-leftovers-roots.o
