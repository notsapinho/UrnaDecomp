# uenux2 comum::asn::IConversorASN<ENTIDADE, DADO>'s default DoConverte and DoDesconverte, in the class in
# src/app/comum/asn/iconversorasn.h, IConversorBiometriaASN<ENTIDADE, DADO>'s default DoConverte, in
# src/app/comum/asn/iconversorbiometriaasn.h, and the heads of the comum converters that inherit them; and the
# converters of ModuloCandidatos::Candidatura, CConversorCandidaturas and CConversorCandidatura (below).
#
# Matched. Fn 731, binaryen's merge of IConversorASN's two defaults (in our link the byn$mgfn-shared$ body named after
# its first member in link order), and its 29-byte thunks, each converter's inherited slot:
# - slot 2, DoConverte, of the converters landed before: CConversorSuplencia 11358 and CConversorComplementosMunicipios
#   11380 (unit 124), CConversorSituacoesEleicoes 11360 (unit 47), CConversorProcessoEleitoral 11362 and
#   CConversorPleito 11364 (unit 140), CConversorNomesCargo 11368 (unit 88), CConversorDadosCandidato 11449 (unit 96),
#   each emitted with its class's vtable in that unit's object; CConversorImpedido 11409, with unit 98's
#   cconversorimpedido.cpp.o;
# - slot 2 of this fragment's CConversorEleicaoPE 11370, CConversorCargo 11372, CConversorDetalheCandidato 11374,
#   CConversorDetalheConsulta 11376, CConversorDedo 11415, CConversorBiometriaEleitor 11421, CConversorFotoCandidato
#   11439, CConversorCandidaturas 11444 and CConversorCandidatura 11446, and slot 3, DoDesconverte, of
#   CConversorHistoricoVotoImpresso 10275 and of CConversorEntidadeHashes 10265 (its head is
#   gravadores/asn/cconversorentidadehashes.h, over unit 136's md::CEntidadeHashes; RTTI names the class and its base,
#   fn 5367 stores its vptr, and the header's path is chosen, the directory its data class's and its link neighbours'
#   records', docs/reference/facts/placing.md P3) and of CConversorEntidadeBU 10272 (its head is
#   gravadores/asn/cconversorentidadebu.h, beside the .cpp its records name, over md::CEntidadeBU,
#   gravadores/md/centidadebu.h, with which the default returns the TDado in memory, the target's (i32 i32 i32)->();
#   RTTI names the class and its base, and fn 11629, unit 200's, is the one target function that stores its vptr, which
#   matches: the roots' sink went with it);
# and 11418, IConversorBiometriaASN's default DoConverte, slot 2 of CConversorBiometriaEleitorCifrada. All of them come
# from the headers' code, emitted with each class's vtable by the object that writes the class's own slot (the pending
# object, which emitted them while it trapped those slots, went with its last member, 11445):
# CConversorCandidaturas's and CConversorCandidatura's: this unit's cconversorcandidaturas.cpp (11445) and
# cconversorcandidatura.cpp (11448) emit the vtables and the defaults 11444 and 11446 with them;
# CConversorHistoricoVotoImpresso's and CConversorFotoCandidato's: fragment 172 writes their own slots (10276, 11440),
# and those objects emit the vtables now; CConversorCargo's: fragment 191 writes its slot 3 (11373), and
# cconversorcargo.cpp.o emits the vtable and the default 11372 with it; CConversorDetalheConsulta's: fragment 225
# writes its slot 3 (11377), and cconversordetalheconsulta.cpp.o emits the vtable and the default 11376 with it; and
# CConversorEleicaoPE's and CConversorDetalheCandidato's: fragment 299 writes their slot 3 (11371, 11375), and
# cconversoreleicaope.cpp.o and cconversordetalhecandidato.cpp.o emit the vtables and the defaults 11370 and 11374
# with them; and CConversorEntidadeBU's: fragment 321 writes its slot 2 (10273), and cconversorentidadebu.cpp.o emits
# the vtable and the default 10272 with it; and CConversorEntidadeHashes's: unit 293's cconversorentidadehashes.cpp
# writes its slot 2 (10266), and that object emits the vtable and the default 10265 with it. The roots keep no vtable
# of CConversorDetalheCandidato and CConversorDetalheConsulta: fn 11373 (fragment
# 191's) stores both vptrs, the converters it builds on its stack; nor of CConversorEntidadeHashes, whose vptr fn 5367
# (unit 293's comum::asn::GravaArquivo) stores; nor of CConversorCargo, whose vptr fn 11371 (fragment 299's) stores;
# nor of CConversorEleicaoPE, whose vptr fn 5778 (unit 280's comum::CarregaPleito) stores, through the converter's
# constructor out of line in cconversoreleicaope.cpp (fragment 299): its sink went once that constructor was in the
# link, measured (a link without it moves no row); nor of CConversorHistoricoVotoImpresso and CConversorFotoCandidato,
# whose vptrs fns 10273 (fragment 321's) and 3755 (unit 109's) store, both in the link (a link without the two sinks
# moves no row).
#
# Evidence. Records name each default, its class template and its throw's line and column: iconversorasn.h 89 and 98,
# iconversorbiometriaasn.h 81, column 15 (a throw in a body in the class). Each thunk passes its instance's record, code
# (7655 DoConverte, 7656 DoDesconverte), format string ("Metodo DoConverte() nao implementado para {}", 44 bytes, or
# "...DoDesconverte()...", 47, with their accents) and typeid(TEntidade).name() (the entity's typeinfo name) to 731;
# 11418 holds the same with code 7659. RTTI names each converter, its base and so its entity and data types; the
# vtables give the slots. The record of IConversorBiometriaASN's Desconverte (line 62, held by fn 1937) names the
# parameter type md::CParametro.
#
# Measured. The defaults match at -O3, the tree's level (unit 96's fragment has the -O2 measurement). 731 forms as the
# target's only with an inherited DoDesconverte in the link: with CConversorHistoricoVotoImpresso's vtable out of the
# link, our merged body is 25 over 183 rows from 731 (pnpm wasm score, 3 rows not operand-only), and with it 11 over
# 183, all operand-only, and it matches. The only classes that inherit that default are CConversorEntidadeHashes,
# CConversorEntidadeBU and CConversorHistoricoVotoImpresso (the thunks that pass 7656: 10265, 10272, 10275), so this
# fragment holds the last.
#
# Chosen, no evidence names them: the enumerators of 7655, 7656 and 7659 (euecomumasnerror.h), the unnamed
# parameters, md::CParametro declared ahead of iconversorbiometriaasn.h (its header's path is not recovered), that
# IConversorBiometriaASN declares DoDesconverte pure (the target's one instance overrides it), the layouts' member names
# of md::CHistoricoVotoImpresso (gravadores/md/chistoricovotoimpresso.h, from 10276) and md::CFotoCandidato
# (md/candidatura/cfotocandidato.h, from 11440), and the headers' paths where no record names a file:
# processoeleitoral/cconversordetalheconsulta.h and cconversoreleicaope.h, candidatura/cconversorcandidaturas.h and
# cconversorfotocandidato.h (the directories mirror their data classes', docs/how-to-decompile.md step 3, rule 3),
# gravadores/asn/cconversorhistoricovotoimpresso.h (beside its link neighbour CConversorEntidadeBU, whose records are in
# gravadores/asn/cconversorentidadebu.cpp) and the md heads beside it. The others sit beside the .cpp their records name.
#
# No pending file: its last member, CConversorCandidaturas::DoDesconverte (11445), is written (below).
# CConversorDedo's, CConversorBiometriaEleitor's and CConversorBiometriaEleitorCifrada's own slots (11416, 11422, 11419)
# are fragment 335's: those objects emit the three vtables and the defaults 11415, 11421 and 11418 with them, which
# match from there, and the pending file no longer traps them; the roots keep neither class's vtable now that 11422 and
# 11419 store their vptrs.
#
# ModuloCandidatos::Candidatura's converters, in app/comum/dados/asn/candidatura/, all matched:
# - comum::asn::CConversorCandidaturas::DoDesconverte (fn 11445, slot 3 of the vtable @1562360) in
#   cconversorcandidaturas.cpp, with comum::asn::DesconverteCandidaturas (fn 5710), which converts one list of a party's
#   candidacies and appends them to the result;
# - comum::asn::CConversorCandidatura (cconversorcandidatura.{h,cpp}): its constructor (fn 5712) and DoDesconverte
#   (fn 11448, slot 3 of the vtable @1562284); its slot 2 is the default above (11446);
# - ModuloCandidatos::Candidatura, a class head in src/asn1/modules/ModuloCandidatos.h (the header says what it rests
#   on), and comum::asn::CConversorDadosCandidato's constructor, out of line in unit 96's cconversordadoscandidato.cpp
#   for 11448 (cconversordadoscandidato.h says why).
# Evidence. RTTI names both classes and their bases, and so the entity and data types; the vtables give the slots
# (ledger/vtables.json). 5712 stores CConversorCandidatura's vptr (1562292) after a byte at +4, a 16-bit word at +6 and
# a byte at +8, its parameters in that order, and returns this, which 11445 passes on to 5710. 11445 builds on its stack
# the converter whose vptr (1555736) matched fn 11373's CConversorCodigoCargoConsulta stores, converts each post's code
# with it (fn 5828), and for each party of a post whose optional partidos is present (ModuloTiposResultadosEcoUrna::
# CandidatoPorPartido: partido, candidatosAptos, candidatosInaptos) calls 5712 and 5710 twice, the post, the party and
# 1 with the first list, 0 with the second: two call sites each, so binaryen keeps both out of line and no roots stand
# in for them. 11448 hands the flag to CConversorDadosCandidato, whose DoDesconverte (11450) inverts it into the
# candidate's ESituacao, and reads the candidacy's fields 0, 1 and 3 (numero, titular, suplentesVices, at() over the
# last: the target's out_of_range throw) into md::CCandidatura's constructor (5660). 5710 holds
# IConversorASN<ModuloCandidatos::Candidatura, md::CCandidatura>::Desconverte's record (iconversorasn.h:71, @1562404)
# behind a second stack prologue inside its loop, an instance binaryen inlined there, then the push_back; its
# parameters are the result's vector, the converter and the list, in that order.
# The data: the target's run CConversorDadosCandidato's vtable (@1562224, unit 96's object), then
# CConversorCandidatura's vtable and typeinfos with the records of Desconverte<ModuloCandidatos::DadosCandidato, ...>
# (5711's, @1562328) and of the default DoConverte (11446's, @1562344), then CConversorCandidaturas's vtable and
# typeinfos with the records of 5710's inlined Desconverte (@1562404) and of the default DoConverte (11444's, @1562420):
# so the two converters are two objects, each holding what it instantiates first, and 5710 is
# cconversorcandidaturas.cpp's. Each of our two objects holds that run (the link map's .data.rel.ro entries, decoded) at
# the place below. Measured (pnpm wasm score on the whole link, before step 8):
# - 11448 holds CConversorDadosCandidato's constructor inlined by binaryen: the object's address in a local and its
#   byte stored before the vptr, the order the out-of-line 5712 gives. With the constructor inline in the class (that
#   header's form before) 11448 scored 121 over 758 rows (15 inserted, 14 deleted), out of line in
#   cconversordadoscandidato.cpp 24 over 743, all operand-only. 11450, in that object, still matches.
# - With every member written, 11445 scored 6 over 132, 5712 1 over 15, 5710 30 over 631 and 11446 6 over 11, all
#   operand-only, the same in this unit's list place, in unit 96's after cconversordadoscandidato.cpp and in unit
#   225's: among those three places their order decides no row. 5710's operand rows that are no call or data address
#   are the format string's packed pointer and two table slots.
# - Forms that change 11445's code, with the object-local numbers masked against a control compiled beside them
#   (docs/reference/facts/tool-traps.md X12), so what is written is evidence: the result declared before the code's
#   converter (the target stores the converter's vptr, then zeroes the result) and the two CConversorCandidatura named
#   locals instead of temporaries. Forms that give 11445's and 5710's code with only the object's data offsets moved:
#   5710 static, or in an anonymous namespace (clang keeps it out of line with two call sites either way), and 5710
#   defined after 11445.
# - The place: docs/reference/facts/codegen.md C4's record-aware count, per file, on the plain link of the commit that
#   added these files (525b5b8a, over 76661cb7): 276 objects out of the data's order in unit 225's list before
#   cvisitanteeleitor.cpp, 279 in unit 124's before cindexadorfotos.cpp, 284 in unit 172's before
#   cconversorfotocandidato.cpp, 285 in unit 157's after cconversorlocal.cpp, 287 in this fragment's own list, 332 in
#   unit 36's before cvisitantefoto.cpp (the data successor), 333 as a fragment of its own (394) and 372 in unit 96's
#   after cconversordadoscandidato.cpp (the data predecessor). Unit 225's place also links them after
#   cconversorcargo.cpp.o, which then keeps Desconverte<CodigoCargoConsulta>'s copy (5828) as at the base: in this
#   fragment's own list cconversorcandidaturas.cpp linked first and held that copy's record in its run, which the
#   target's run of that object does not hold (its copy's record is @1556684). Left inverted among the data neighbours:
#   cconversordadoscandidato.cpp (unit 96's list links after), cindexadorfotos.cpp and cconversorfotocandidato.cpp
#   (units 124's and 172's link before). Against unit 124's place, 93 objects are inverted here and in order there (49
#   of app/comum, 24 of app/vota/operador, 19 of api, one of app/vota) and 96 the other way (53 of app/vota/eleitor, 33
#   of app/comum, 4 of app/vota/comum, 3 of the simulator's mock, 2 of api, one of app/vota).
# Chosen, no evidence names them: the members' and parameters' names, the flag's type (bool: a byte stored and passed),
# m_cargo's and m_partido's types (md::TCargoID and TPartidoID, the record's types of the md::CCandidatura constructor
# parameters they are passed to; their widths are evidence); DesconverteCandidaturas's name, its being a free function
# of comum::asn (it reads no class state), its external linkage and its place before 11445 in the file (the forms
# above give the same code); the order of the two definitions in cconversorcandidatura.cpp; cconversorcandidatura.h's
# path and both .cpp files' names (the directory mirrors md::CCandidatura's, docs/how-to-decompile.md step 3, rules 3
# and 4); the static_casts to ModuloCandidatos::Candidatura and ModuloCandidatos::DadosCandidato, which those class
# heads' chosen bases force and which generate no code.
#
# This unit's sources, src/app/comum/dados/asn/candidatura/cconversorcandidatura.cpp and cconversorcandidaturas.cpp,
# are compiled by 225-uenux2-comum-asn-converters.mk's list, before cvisitanteeleitor.cpp (the header says why).
# CConversorCandidaturas's builder is not written: 159-uenux2-iconversorasn-defaults-roots.cpp keeps its vtable the way
# the target reaches it (the others' storers are in the link)
$(ROOT)/$(APP)/159-uenux2-iconversorasn-defaults-roots.o: $(ROOT)/src/units/159-uenux2-iconversorasn-defaults-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/159-uenux2-iconversorasn-defaults.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/159-uenux2-iconversorasn-defaults-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/159-uenux2-iconversorasn-defaults-roots.o
