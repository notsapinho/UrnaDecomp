# uenux2's api::CStringUtils, in src/uenux2/src/api/util/cstringutils.cpp, the file its records name; its header,
# api/util/cstringutils.h, is a chosen path (no record names one). Target functions:
#   matched    1539 GetVersionNumber (record line 59): the start of a version string that matches
#              "^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+", through ecourna's CStringUtils::FindRegex (2199, unit 00, matched; its
#              name came from 654's and this function's calls); when the match does not start at 0, or
#              there is none, it throws CUeUtilError 7025 with the message at 231188 (ledger/strings.tsv), formatted with
#              the string. The expression is a named local: the target frees its string after the substr.
#   written    SetBit, the records at lines 71 and 83, for unit 296 (its fragment has them): only functions that hold
#              it inlined load them (2772, the second), and the header declares the two overloads as the records print
#              them.
#   matched    5465 CasaRegex, added for unit 179 (src/units/179-uenux2-cvalidamidia.mk has its evidence and choices),
#              over ecourna's CStringUtils::FindRegexPosition (unit 00's file), which binaryen inlines into it.
#   matched    5464 CasaCaractere, added with it, once isalnum kept one call site in our link, as in the target
#              (unit 179 has the measurement, the Boost probe's change that gives it and the cases' order).
#   matched    3646 JuntaTags: "chave:valor" of each pair of a std::vector<std::pair<std::string, std::string>>, joined
#              by spaces, the last space dropped (pop_back), for comum::CQRCodeDS (fragment 299) and vota::CGeraBU's
#              slot 2 (12110) and 12039. The target builds the text in a local and moves it into the result before
#              pop_back (its rows), the shape of std::accumulate, whose init it returns by value; a plain loop was not
#              linked, and that it is std::accumulate is a reading. No record names it; in use band 3 it links between
#              cgenerictags.cpp's 3647 and csystem.cpp's 3645, a run of api/util/ in name order (cdate, cgenerictags,
#              csystem, ctickmanager, ctime), so its file is one of cgenerictags.cpp, csystem.cpp and the files that
#              sort between them (cstringutils.cpp, csynchronizer.cpp). This one is a choice, which band 2 supports: it
#              puts CasaRegex (5465, this file's) between cgenerictags.cpp's 5466-5468 and csystem.cpp's 5463, so
#              cstringutils.cpp.o lies between those objects in the link. Its name, its being a static member and the
#              lambda's form are chosen too.
#              Whole link, before steps 7 to 9: 8 over 320 rows, all operand-only. The roots stand for 12110 (12039,
#              unit 387's, is in the link).
# Chosen: the parameter's and the locals' names; 7025's local constant in the .cpp, as
# app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp names a code the shared header lacks
# (api/util/eueutilerror.h has no enumerator for it; the constant goes when it gains one); GetVersionNumber's line
# within what its record leaves free. Of its six target callers, 12110 is not in our link (5596, unit 296's, 5604,
# unit 155's written Gera, 11908, unit 176's, 5579, unit 325's, and 12105, fragment 372's, are):
# 196-uenux2-api-util-cstringutils-roots.cpp stands for it.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# The list compiles unit 296's src/api/gui/cqrcodeimagepaper.cpp first, ahead of this unit's file: 2772
# (api::CQRCodeImagePaper's constructor, which holds MontaImagem and through it the vector SetBit, inlined) matches only
# with cqrcodeimagepaper.cpp.o linked before cstringutils.cpp.o (unit 296's fragment has the scores), the order of the
# target's data (cqrcodeimagepaper.cpp's records @1582124 to @1582156, this file's @1584560 to @1584592). The places
# src/units/README.md "Names" gives, by docs/reference/facts/codegen.md C4's record-aware count on 76661cb7's link line:
# cqrcodeimagepaper.cpp here leaves 332 objects out of the data's order against it, 341 at its place in unit 296's list;
# this file after it in unit 296's list would leave 340 against cstringutils.cpp.o, 341 where it is (after
# cqrcodeimage.cpp in unit 79's list, which the rule does not give for this pair, 286). The move restores 53 pairs:
# cstringutils.cpp.o, 7 other api/ objects (api/gui/ctextfield and ctextfielddoubleline, api/hash/, api/io/cinistrings,
# api/util/cdirreader and ctime), 8 of app/comum/ (comparecimentomesario/ and two more) and 37 of app/vota/operador/
# (confirmaidentidade/, justificativa/, outrasopcoes/ and two more); it inverts 44: api/gui/cbmpconversor, cimagefield,
# cmovie and cqrcodeguard, api/hwil/euedesligandoerror, mock/app/simulador/wasm/cwasmclp, 19 of app/comum/
# (appinfo/servicos/, dados/, gravadores/, md/, relatorios/) and 19 of app/vota/ (comum/csincronizavota, 17 of eleitor/,
# mostly fimvotacao/ and iniciovotacao/, and operador/outrasopcoes/cescolheopcao). The file stays unit 296's, which
# keeps its notes and its include path's rule.
CSTRINGUTILS_UENUX2_SRCS := src/api/gui/cqrcodeimagepaper.cpp src/api/util/cstringutils.cpp
UENUX2_SRCS += $(CSTRINGUTILS_UENUX2_SRCS)
# nothing in the skeleton calls GetVersionNumber: 196-uenux2-api-util-cstringutils-roots.cpp stands for its callers,
# through an asm label, so its rule needs no header
$(ROOT)/$(APP)/196-uenux2-api-util-cstringutils-roots.o: $(ROOT)/src/units/196-uenux2-api-util-cstringutils-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/196-uenux2-api-util-cstringutils.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/196-uenux2-api-util-cstringutils-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/196-uenux2-api-util-cstringutils-roots.o
