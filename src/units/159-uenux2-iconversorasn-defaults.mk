# uenux2 comum::asn::IConversorASN<ENTIDADE, DADO>'s default DoConverte and DoDesconverte, in the class in
# src/app/comum/asn/iconversorasn.h, IConversorBiometriaASN<ENTIDADE, DADO>'s default DoConverte, in
# src/app/comum/asn/iconversorbiometriaasn.h, and the heads of the comum converters that inherit them.
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
#   11439 and CConversorCandidaturas 11444, and slot 3, DoDesconverte, of CConversorHistoricoVotoImpresso 10275 and of
#   CConversorEntidadeHashes 10265 (its head is gravadores/asn/cconversorentidadehashes.h, over unit 136's
#   md::CEntidadeHashes; RTTI names the class and its base, fn 5367 stores its vptr, and the header's path is chosen,
#   the directory its data class's and its link neighbours' records', docs/reference/facts/placing.md P3);
# and 11418, IConversorBiometriaASN's default DoConverte, slot 2 of CConversorBiometriaEleitorCifrada. All of them come
# from the headers' code; the pending object emits this fragment's classes' vtables, and the defaults with them, except
# CConversorHistoricoVotoImpresso's and CConversorFotoCandidato's: fragment 172 writes their own slots (10276, 11440),
# and those objects emit the vtables now.
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
# roots, our merged body is 25 over 183 rows from 731 (pnpm wasm score, 3 rows not operand-only), and with it 11 over
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
# Pending: each class's own slot (this fragment's -pending.cpp names what each waits for). Not written: 10272, the
# inherited DoDesconverte of CConversorEntidadeBU, waits for md::CEntidadeBU's layout: with an empty head for the class,
# the default returned the empty TDado in nothing and took the wasm type (i32 i32)->(), where the target's 10272 is
# (i32 i32 i32)->() (fragment 172 has the measurement); 11446, CConversorCandidatura's inherited DoConverte, whose
# entity ModuloCandidatos::Candidatura the
# generated module lacks (its typeinfo name is the string 11446 passes); with it 5712 (CConversorCandidatura's
# constructor, whose vptr store names the class), 11448 and 5710, and 11445, which stays a trap.
#
# No source of its own: the defaults are the headers' code, emitted with each converter's vtable.
# the converters' own slots that are not written: 159-uenux2-iconversorasn-defaults-pending.cpp traps them and emits
# their vtables, compiled with the tree's flags
$(ROOT)/$(APP)/159-uenux2-iconversorasn-defaults-pending.o: $(ROOT)/src/units/159-uenux2-iconversorasn-defaults-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/159-uenux2-iconversorasn-defaults.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/159-uenux2-iconversorasn-defaults-pending.cpp -o $(R)
# the converters' users are not reconstructed yet: 159-uenux2-iconversorasn-defaults-roots.cpp keeps their vtables the
# way the target reaches them
$(ROOT)/$(APP)/159-uenux2-iconversorasn-defaults-roots.o: $(ROOT)/src/units/159-uenux2-iconversorasn-defaults-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/159-uenux2-iconversorasn-defaults.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/159-uenux2-iconversorasn-defaults-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/159-uenux2-iconversorasn-defaults-pending.o $(APP)/159-uenux2-iconversorasn-defaults-roots.o
