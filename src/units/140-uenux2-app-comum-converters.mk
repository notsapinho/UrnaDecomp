# uenux2 comum::asn converters of app/comum/dados/asn/ and the comum::md data they build. The unit's other members are in
# landed units' files: comum::asn::Utils's dates in unit 96 (util.cpp), md::CVotosCargos::SCargoInfo, md::CVotos's
# constructor, CVotosCargos::GetVotos and comum::CRdvVota's converter in unit 13; each fragment says what it holds.
#
# Matched:
# - CConversorPleito::DoDesconverte (target fn 11365, slot 3 of the vtable @1570332), in
#   app/comum/dados/asn/processoeleitoral/cconversorpleito.{h,cpp}, over Utils::DesconverteDataJE (fn 2276, unit 96),
#   and md::CPleitoDTO's constructor, out of line in app/comum/dados/md/processoeleitoral/cpleitodto.cpp: 11365 copies
#   the date with the 2-byte alignment of a const api::CDate& (i64.load align=1), so binaryen inlined the constructor
#   from another function. Defined in the class, 11365 is 16 over 104 rows (5 inserted, 2 deleted); out of line in
#   another TU, 4 over 99, operand-only (pnpm wasm score).
# - CConversorVotosCargo's constructor (fn 5683), in app/comum/dados/asn/rdv/cconversorvotoscargo.{h,cpp}: the
#   SCargoInfo at +4 and a CConversorVoto at +16 (that class's vptr, @1570816).
# - CConversorEleicoesVota's D2 and D0 (fns 11348, 11347), in app/comum/dados/asn/rdv/cconversoreleicoesvota.{h,cpp}:
#   implicit, the class final (the D2 does not begin with its vptr store), and fn 1160, the destroy of its map from each
#   election to a vector of md::CCargo. Five functions call 1160 in our link: those two destructors, the
#   CConversorRegistroDigitalVoto<CConversorEleicoesVota> ones (11484, 11485) and ~CRdvVota (5734, unit 13); 5734, named
#   by `call`, casts the vote that names 1160 in the generated part of splat/symbol_addrs.txt, so it has no hand line.
# - CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s D2 and D0 (fns 11485, 11484), implicit, emitted with
#   comum::CRdvVota's destructor (unit 13, fn 5734), whose member at +44 the class is, in
#   app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h.
# - std::__tree<md::TCargoID, md::CVotos>::destroy (fn 2877), from this unit's roots (below).
# - Copies of library and ecourna template code this unit's objects bring first: 858, 1074 and 1075 (the error path of
#   ecourna's IConversorASN, basic_stringstream and CBaseError<EApiAsnError>) from cconversorvotoscargo.cpp.o.
#
# Written and not matched, and what each waits for:
# - 11363, CConversorProcessoEleitoral::DoDesconverte, in cconversorprocessoeleitoral.{h,cpp} (record line 50), with
#   md::CProcessoEleitoralDTO's two constructors out of line in cprocessoeleitoraldto.{h,cpp}: `differs`, 84 over 1088
#   rows (67 operand-only, 10 inserted, 7 deleted). The target ends the function with the identifiers vector's
#   __throw_length_error and then __throw_bad_array_new_length; every form measured puts the second right after the
#   loop, in the object before binaryen too: push_back at -O2 and at -O3, emplace_back, an index loop, an iterator loop,
#   std::transform with a back_inserter, the vector declared first, the principal identifier after the loop, std::find
#   into a local, std::ranges::find, and the constructors defined in the class. What is written, emplace_back, is inlined
#   by clang at -O2 (cost 225 against the hint's threshold 325) as the target's is; push_back is inlined only at -O3 (225
#   against 250, and 225 against 225 at -O2, where the call merges with vector<long>::push_back); the object of
#   emplace_back at -O2 and push_back at -O3 is the same, masked.
# - 11352 and 11351, CConversorVotosCargo::DoConverte and DoDesconverte, and 11350, CConversorEleicoesVota::DoConverte,
#   waited for uenux2 at -O3; at the tree's -O3 11352 matches, and 11351 and 11350 differ by the scores the private
#   -O3 link below gave, which the plain link gives too (pnpm wasm score): what is left is not explained. What was
#   measured at -O2 and -O3: ecourna's IConversorASN Converte and Deconverte, which 11352 and 11351 hold for
#   CConversorCargoID, append ": " with std::string::operator+=(const char*), which clang leaves out of line in that cold
#   path at both levels; at -O2 it inlines append into it, and binaryen folds the literal into our copy, which no target
#   function holds (the rows are `unresolved` on that call); at -O3 operator+= is the append the target calls (fn 678).
#   11350's inner loop pushes each converted VotosCargo into the SEQUENCE_OF: the target holds that
#   vector<AbstractData*>::push_back inlined and the outer loop's called; -Rpass=inline gives both cost 260 against 225
#   at -O2, and at -O3 the inner one inlined (threshold 787) and the outer not (250). In a private link with this unit's
#   three converter objects compiled with UENUX2_EXTRA=-O3 and every other object at -O2: 11352 is 53 over 421 rows,
#   operand-only; 11351 94 over 1235 (89 operand-only, 2 inserted, 3 deleted); 11350 99 over 870 (96 operand-only, 3
#   deleted).
#
# The base's default DoConverte of CConversorPleito and CConversorProcessoEleitoral (11364, 11362) is emitted with
# their vtables in their objects and matches: fragment 159's row.
# Pending (this unit's -pending.cpp traps them): 11349, CConversorEleicoesVota::DoDesconverte
# (records :69, :74, :94 and :104, not written); 11483 and 11482, CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s
# DoConverte and DoDesconverte (not written; 11483 holds Converte<Eleicoes, ...> inlined, iconversorasn.h:56).
#
# Not written: 11437 and 11438, the DoDesconverte and DoConverte of comum::asn::CConversorCabecalhoPacote (RTTI at the
# typeinfo 1562760; vtable @1562736, slots 3 and 2, table slots 2546 and 2545). They hold, inlined, util.cpp's
# DesconverteIdEleitoral, DesconverteTipoPacote and DesconverteIdSistema (records util.cpp:89, 329, 451) and
# ConverteTipoPacote, ConverteIdPacote and ConverteIdSistema (231, 344, 419), and the md::CIDEleitoral, CIDPacote and
# CCabecalhoPacote members of cideleitoral.cpp:21, 29, 37, cidpacote.cpp:21, 67, 75, 83 and ccabecalhopacote.cpp:33,
# 36, 39. Every function they call is named.
#
# Where no record names a file (docs/how-to-decompile.md step 3): cconversorpleito.* by rule 3, the directory of
# md::CPleitoDTO's, and its vtable lies between cconversororigemconfiguracao.cpp's objects (@1570224 to @1570320) and
# cconversorprocessoeleitoral.cpp's record (@1570392), where a file of its own sorts; cconversorregistrodigitalvoto.h by
# rule 3; cpleitodto.cpp beside its header, chosen. The records name cconversorvotoscargo.cpp,
# cconversoreleicoesvota.cpp, cconversorprocessoeleitoral.cpp and cprocessoeleitoraldto.cpp.
#
# Evidence for forms:
# - each throw's line and column, and each definition's return type spelled as its record (md::CProcessoEleitoralDTO,
#   ModuloRegistroDigitalVoto::VotosCargo, std::pair<md::CVotosCargos::SCargoInfo, md::CVotos>); written as TDado,
#   11363's row was `unresolved` on its record (`an address of ours: source_location not in the target`);
# - 11352 builds each entity Voto into a local before set_votos() is read: in one expression the field's address is
#   read first, 62 over 424 rows (3 inserted, 5 deleted), against 55 over 421 (2 deleted, the append above), both at
#   -O2; as written it matches at the tree's -O3;
# - ModuloRegistroDigitalVoto::EleicaoVota::set_idEleicao takes const_reference (src/asn1/modules, a hand edit, the
#   per-field form units 93 and 124 measured): the target's 11350 builds the field's temporary, ASN1::INTEGER's
#   constructor (call 553 with the info 1556824), the vptr 1560492 and the value at +40, then stores the value
#   (build/out/splat/pieces/asm/comum/11350.wat, offsets 0x8c to 0xae);
# - read from the target's rows, not measured against another form: 11363 copies the name with a 4-byte alignment
#   (i64.load align=2), a reference's, where its own copy into a local is 8-byte aligned, so the DTO's constructors are
#   out of line in another TU; two constructors, since the branch with the second pleito copies the result of
#   Desconverte into the optional directly; the vector is taken by value (copied, then moved in); 11351 copies each
#   CVoto's string and then destroys the temporary (a const local pushed with push_back), and builds md::CVotos from a
#   copy of the vector (CVotos(votos), a by-value parameter).
# Chosen, no evidence names them: every member's name in the new heads, md::CProcessoEleitoralDTO's id type
# (uedword), the format casts (static_cast<int> in 11363, which formats an int, type code 3; cargo.Get() in 11351, an
# unsigned, code 6), CConversorEleicoesVota's map alias, the lines of every function no throw of which has a record, and
# std::make_pair in 11350.
#
# The converters include generated ASN.1 modules; paths relative to src/uenux2; the generic uenux2 rule depends on the
# sources and every uenux2 header.
CONVERSORES_140_SRCS := src/app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp \
  src/app/comum/dados/asn/rdv/cconversorvotoscargo.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversorpleito.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.cpp \
  src/app/comum/dados/md/processoeleitoral/cpleitodto.cpp \
  src/app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.cpp
UENUX2_SRCS += $(CONVERSORES_140_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CONVERSORES_140_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# cconversorvotoscargo.cpp includes ecourna's app/dados/asn/cconversorcargoid.hpp, which includes its ASN.1 module by
# its bare name, as the ecourna objects' include path finds it
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversorvotoscargo.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
# the slots not written: 140-uenux2-app-comum-converters-pending.cpp traps them, compiled with the tree's flags
$(ROOT)/$(APP)/140-uenux2-app-comum-converters-pending.o: $(ROOT)/src/units/140-uenux2-app-comum-converters-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/140-uenux2-app-comum-converters.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/140-uenux2-app-comum-converters-pending.cpp -o $(R)
# the converters' users are not reconstructed yet: 140-uenux2-app-comum-converters-roots.cpp reaches them the way the
# target does. It compiles at the tree's flags: it holds the link's copy of a std::map instance (the file says which)
$(ROOT)/$(APP)/140-uenux2-app-comum-converters-roots.o: $(ROOT)/src/units/140-uenux2-app-comum-converters-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/140-uenux2-app-comum-converters.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/140-uenux2-app-comum-converters-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/140-uenux2-app-comum-converters-pending.o $(APP)/140-uenux2-app-comum-converters-roots.o
