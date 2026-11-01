# ecourna's IConversorASN<ENTIDADE, DADO> (api/asn/iconversorasn.hpp): the members whose target copies are uenux2's,
# from the tree root src/app/roots_iconversorasn.cpp, and three names for CConversorIdentificadorEleitor::DoConverte
# (9117). The fragment holds no source: the root is in APP_OBJS (its rule is in src/Makefile, as roots_cbasetype.o's
# is), and this file holds the evidence. Matches, 9 target functions:
#   - Converte for IdentificadorGeradorMidia (3734) and DadosComparecimento (5365), binaryen's merge of the two (6031);
#     Deconverte for IdentificadorGeradorMidia (3733) and Foto (5708), and their merge (6032).
#   - 9056, unit 105's CConversorResultadoUrnaCadastro::DoConverte, `unresolved self-voted` before on the table slot of
#     5365, which only its own operand named; 9202, unit 08's CConversorDadosGeracaoMidia::DoDeconverte, `unresolved`
#     before on the table slot of 3733.
#   - 9117, unit 04's CConversorIdentificadorEleitor::DoConverte, by three hand lines (below).
#
# Which copy, evidence. The four members' records name the conan package's installed header,
# .../p/include/ecourna/api/asn/iconversorasn.hpp (49:19 for Converte, 66:19 for Deconverte), as uenux2's compiles of
# ecourna's headers spell it (src/units/112-ecourna-cbasetype.mk); ecourna's own converters' copies, the ones our link
# held, name .../b/src/, so 3734 and 5365 were `unresolved` on `source_location not in the target`, and 3733 and 5708
# `no-candidate` (`awk -F'\t' '$2 ~ /p\/include\/ecourna\/api\/asn\/iconversorasn/ {print $6}'
# ledger/source-locations.tsv` lists the four among the uenux2 copies). In the target 3734 and 5365 are `f6031(p0, p1,
# p2, <record>, <typeid name>)` and 3733 and 5708 the same over 6032, two merges of two members each (`awk -F'\t'
# '$2==6031 || $2==6032' ledger/callgraph.tsv`). Their uenux2 callers are not written (10290 10291 11399 11400 for the
# IdentificadorGeradorMidia pair, 11422 11440 for Foto, 11616 for DadosComparecimento); ecourna's converters reach them
# through table slots (9203 slot 6731, 9202 slot 6734, 9056 and 2772 slot 7027). A fragment's roots link after ecourna's
# objects, which would keep their own copies, so the instances are explicit instantiations in a tree root ahead of both
# trees, at UENUX2_CXXFLAGS, as for CBaseType.
#
# Measured on the whole link (pnpm wasm score): 6031 and 6032 against our merges, 12 over 70 rows, operand-only; each
# thunk 3 over 8, operand-only. Without urna_roots_iconversorasn, the stand-in for 5708's callers that urna_roots calls
# (binaryen inlines it there), wasm-ld dropped the Foto instance (no row of build/out/wasm-map/vota_web/names.tsv names
# it) and 3733 stayed a whole body, 66 over 70 rows against the target's thunk.
#
# What the instances bring. The root is now the link's copy of four functions the uenux2 object
# app/comum/dados/asn/rdv/cconversorvotoscargo.cpp.o gave before, at the same UENUX2_CXXFLAGS, and each still matches:
# string::operator+=(const char*) (678), stringstream's constructor (858) and str() (1075), and CBaseError<EApiAsnError,
# {1900, 1910}>'s constructor (1074). basic_stringbuf::__init_buf_ptrs (674) comes from it too, in place of
# roots_rhvoice.o's, and stays `differs`. Step 8 adds a `call` line for 682, the ecourna copies' Converte merge, matched
# already.
#
# 9117's names. Its body re-pointed IDENTICAL, kind-unverified, before (`pnpm wasm splat-remap ... --against 9117
# --no-kinds`), and the scan held it `unresolved self-voted` on the three alternatives' theInfo objects, .bss objects
# that only 9117 and the static constructors (14478) read, so no vote but its own named them and no content can. The
# hand lines in splat/symbol_addrs.txt (`callers+content`) rest on the target's data: the words at 1621696 are 1913336,
# 1913380 and 1913424, and the next three, at 1621708, point at "numeroInscricao", "numeroCPF" and "identificacaoLivre"
# (ledger/strings.tsv 141452, 329641, 177777): the CHOICE's selectionInfos and selectionNames, which words 4 and 8 of
# its info at 1140484 point at. 14478 builds each with the fixed size of its alternative in
# src/asn1/modules/ModuloTiposEleitorais.cxx, 12, 11 and 12. At c1b2630, without the lines, the row was `unresolved
# self-voted` on the first of them (splat/scan.tsv).
#
# Chosen: the root's file name, the stand-in's name, its label urna_deconverte_foto, and its argument offsets (any
# that differ from each other).
