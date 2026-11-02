# uenux2 comum::md::CDadosDisponiveisCarga (src/app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.cpp) and its
# converter, comum::asn::CConversorDadosDisponiveisCarga (src/app/comum/dados/asn/correspondencia/
# cconversordadosdisponiveiscarga.cpp), with the two list helpers over comum::asn::CConversorCabecalhoPacote
# (cconversorcabecalhopacote.cpp beside it).
#
# Matched: the converter's DoDesconverte (target fn 11423) and DoConverte (11424), and the libc++ instances 2807
# (vector<md::CSecaoEleitoral>::__init_with_size, the vector's copy) and 5669 (__uninitialized_allocator_copy_impl over
# md::CCabecalhoPacote). 11423 holds, inlined by binaryen, CDadosDisponiveisCarga's constructor (records
# cdadosdisponiveiscarga.cpp:41 to :69), CMunicipioDisponivel's, DesconvertePacotes and two vector slow paths; 11424
# holds ConvertePacotes, IConversorASN<CabecalhoPacote, CCabecalhoPacote>::Converte (record iconversorasn.h:56) and three
# SEQUENCE_OF assignments, inlined by binaryen. 11423 and 11424 are named by srcloc-anchor, 5669 by pair-addr and 2807 by
# 11423's call (it matched by its body first).
# Written and not matched: 3863 (vector<md::CCabecalhoPacote>'s __destroy_vector) and 5956
# (vector<md::CMunicipioDisponivel>'s), which this unit's converter object emits. The target's copies are ones compiled
# with strict aliasing, and app/comum/dados/asn has none: as linked, 3863 is 20 over 108 rows and 5956 45 over 127 (pnpm
# wasm score); in a private link with src/app/comum/dados/asn/correspondencia/% added to UENUX2_TBAA_DIRS on the make
# command line (the converter object recompiled, measured before DoConverte was written), 4 over 104 and 4 over 118,
# call operands only, and pnpm wasm splat-remap reads both bodies identical to the target's, with 11423 unchanged (11424,
# written since, differs so). They wait for a strict-aliasing object that emits them ahead of this
# unit's: their other target callers, 11905 (vota::CImpressaoVersaoPacotes's slot 2, which calls 679, CoderEnv::decode)
# and 3691 (comum::CGeradorRelVersaoPacoteDados's slot 0), are not written. Two hand lines in splat/symbol_addrs.txt name
# them for 11423, whose own call is otherwise their only voter (without them 11423 reads unresolved self-voted, measured);
# the lines say what each body shows.
# Pending (the -pending.cpp traps them): 11438 and 11437, CConversorCabecalhoPacote's DoConverte and DoDesconverte.
#
# Evidence. RTTI names both converters and their bases; their vtables are read from the data
# (docs/reference/facts/reading.md R20; ledger/vtables.json has no row for either), so step 8 gives their slots no vtable
# name. CDadosDisponiveisCarga's layout and its constructor's tests and throws are 11423's (the constructor is the code
# behind its second stack-pointer prologue, of 112 bytes); CMunicipioDisponivel's layout is what 11423 builds and copies;
# CIDPacote's and CIDEleitoral's layouts are fn 11437's (md/ccabecalhopacote.h and md/cideleitoral.h say how). The order
# in which DoDesconverte reads the entity is the target's: fase (a call), then idPE and idPleito, then pais's copy before
# serialFlashCarga's and the UF's sigla and nome (the frame: the first local takes the highest offset, +240, +224, +208
# and +192), the zone before the three converters' vptr stores, and the converters before the municipalities' vector
# (+188, +184 and +180 above +168). DoConverte's frame orders its locals the same way (the UF at +168 above the
# converters at +164, +160 and +156). ModuloDadosDisponiveisCarga's set_idPE, set_idPleito and set_zona take
# const_reference (src/asn1/modules, a hand edit): 11424 builds a temporary of each field's type before the store (call
# 553 with the field's info), the sign docs/reference/facts/asn1.md A3 gives.
#
# Forms measured, each with pnpm wasm score against the target on the whole link as the source then stood:
# - CMunicipioDisponivel's constructor out of line, in another TU than DoDesconverte: written in the class, 11423 was 1046
#   over 2930 rows (the sections' vector lived in locals, where the target keeps it in the frame at +60; a reading: its
#   address goes to a constructor clang cannot inline); out of line, 420 over 2749. Which TU, cdadosdisponiveiscarga.cpp,
#   is chosen.
# - The link order: the converter's objects before cdadosdisponiveiscarga.cpp's (this list's order). With that file first,
#   11423 was 403 over 2741, its slow path and the constructor's copy loading begin and end in the other order; with it
#   last, 171 over 2706 (docs/reference/facts/codegen.md C4).
# - DoDesconverte's sections: std::transform over a back_inserter. A range-for (push_back and emplace_back give one
#   sha256) or an iterator loop with its end cached puts the slow path's two throws (length, bad_array_new_length) right
#   after the inner loop in the object (wasm-objdump -d of the try object), where the target has them after the outer
#   one: 171 over 2706, against 145 over 2696, all operand-only, with transform. std::for_each with a lambda that calls
#   push_back gives the same function as transform (DoDesconverte's disassembly in the two objects, calls masked). The
#   entity's sections are bound to a reference before the vector is declared, as the target loads them before the
#   vector's stores: 412 over 2746 so, against 420 over 2749 with get_secoes() as the range-for's range.
# - DoConverte's sections: std::transform likewise. With a range-for the municipality entity takes the frame's top slot
#   (+220) and the temporaries +64, the target's other way round (the object's offsets), 567 over 1647, against 544 over
#   1639; a reading: the inlined lambda's temporary is the first 52-byte alloca, so the temporaries' slot comes first.
#   Not measured: which other forms (std::for_each, as for DoDesconverte) give DoConverte's bytes, and whether a
#   range-for in ConvertePacotes' and DesconvertePacotes' index loops gives the same functions.
# - ConvertePacotes in another TU than DoConverte: in DoConverte's TU clang inlines it, 544 over 1639; in
#   cconversorcabecalhopacote.cpp, 109 over 1513, all operand-only. DesconvertePacotes leaves 11423 at 145 operand-only
#   rows over 2696 in either TU.
# - DesconvertePacotes declares its result before the converter (the converter's vptr is stored after the vector's
#   words), and the constructor's last test is m_municipios.size() == 0 (the target loads the end before the begin;
#   empty() loads the begin first): the two together took 11423 from 412 to 403 rows, each removing its own difference.
# - Read from the target, not measured against another form: the constructor's tests read the members, not the
#   parameters (the loads are from the object); CInfoMunicipio's daylight-saving variant is assigned over the plain one
#   (the second constructor builds a temporary, then a move assignment).
#
# Where no record names a file (docs/how-to-decompile.md step 3): cconversordadosdisponiveiscarga.* by rule 3, the
# subdirectory of app/comum/dados/asn/ that mirrors md/correspondencia/. In the use band 11424 and 11423 come after
# candidatura's CConversorFotoCandidato (11440) and CConversorCabecalhoPacote's two slots, and before 11422, whose record
# is app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.cpp; in the data the vtable lies between
# ModuloTiposEcoUrna::Carga's and CConversorBiometriaEleitor's: where a correspondencia/ directory sorts.
# cconversorcabecalhopacote.* beside it, chosen. md/cideleitoral.h beside the records' cideleitoral.cpp, chosen.
#
# Chosen, no evidence names them: CMunicipioDisponivel's namespace, header, members and getters (its name is the record's,
# cdadosdisponiveiscarga.cpp:41, which prints it unqualified), the place and
# type of comum::TProcessoEleitoralID and comum::TPleitoID, EUrnaFase's FASE_INDEFINIDA ('0', app/comum/eurnafase.h), the
# member, getter and parameter names of CDadosDisponiveisCarga and the order of its four string parameters, CIDPacote's
# and CIDEleitoral's member names, ConvertePacotes and DesconvertePacotes (names and free functions; the file is a
# reading for ConvertePacotes, cconversorcabecalhopacote.cpp says why), and the lines of
# the functions with no record (the constructors' first lines in cdadosdisponiveiscarga.cpp, every line of the asn files).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
DADOS_DISP245_SRCS := src/app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.cpp \
  src/app/comum/dados/asn/correspondencia/cconversordadosdisponiveiscarga.cpp \
  src/app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.cpp
UENUX2_SRCS += $(DADOS_DISP245_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(DADOS_DISP245_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# CConversorCabecalhoPacote's two slots are not written: 245-uenux2-cdadosdisponiveiscarga-pending.cpp traps them,
# compiled with the flags of their directory, app/comum/dados/asn/, which keeps -fno-strict-aliasing
$(ROOT)/$(APP)/245-uenux2-cdadosdisponiveiscarga-pending.o: $(ROOT)/src/units/245-uenux2-cdadosdisponiveiscarga-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/245-uenux2-cdadosdisponiveiscarga.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/245-uenux2-cdadosdisponiveiscarga-pending.cpp -o $(R)
# the converter's user and the libc++ instances' other callers are not reconstructed yet:
# 245-uenux2-cdadosdisponiveiscarga-roots.cpp keeps the vtable and gives each instance the call sites the target gives it
$(ROOT)/$(APP)/245-uenux2-cdadosdisponiveiscarga-roots.o: $(ROOT)/src/units/245-uenux2-cdadosdisponiveiscarga-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/245-uenux2-cdadosdisponiveiscarga.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/245-uenux2-cdadosdisponiveiscarga-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/245-uenux2-cdadosdisponiveiscarga-pending.o $(APP)/245-uenux2-cdadosdisponiveiscarga-roots.o
