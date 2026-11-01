# uenux2 comum::gravadores classes and converters, paths relative to src/uenux2:
# - comum::CCopiadorMR and comum::CCopiadorWSQMR (src/app/comum/gravadores/ccopiadormr.{h,cpp}, ccopiadorwsqmr.cpp):
#   both constructors (target fns 1276 and 3827) and the destructors defined in the class (fns 11638 and 5872, slots 0
#   and 1 of both vtables, thunks into binaryen's merged bodies fns 1723 and 1722). In our link the two destructors
#   come from ccopiadorwsqmr.cpp.o, whose constructor stores CCopiadorWSQMR's vptr and so emits that vtable and the
#   inline destructors first; 160-uenux2-comum-gravadores-classes-pending.cpp emits CCopiadorMR's vtable with its
#   traps of slots 2 and 3 (fns 5874, 5873; Slot2 is the key function).
# - comum::CGravadorEnvelopeArquivo::LeConteudo (target fn 11623, slot 8, a chosen name), the class's key function, in
#   src/app/comum/gravadores/cgravadorenvelopearquivo.cpp: the class's vtable and implicit destructors (fns 11622,
#   11621, unit 136's matches) are emitted there now, not in unit 136's pending object, under the same symbols.
# - comum::CGravadorEnvelopeArquivo's constructor (target fn 5856), in cgravadorenvelopearquivo.cpp, with
#   comum::IGravadorEnvelope's constructor, which has no target index of its own, out of line in
#   src/app/comum/gravadores/igravadorenvelope.cpp (a chosen path, beside igravadorenvelope.h): binaryen inlines it
#   into its one caller, as the target's 5856 holds it. Measured in this unit's link before step 8 (pnpm wasm score
#   against the target): 6 over 77 rows, operand-only, every operand a call's or a data address. IGravadorEnvelope's
#   constructor defined in the class, in the whole link (one variant object): 8 over 77 rows (same 69, replaced 7, 6 of
#   them operand-only, deleted 1), other bytes; tried alone (try-tu.sh --single), binaryen also inlines
#   CDadoCorrespondencia's copy constructor (fn 1249) and nothing is told. The headers say which types are chosen.
# - comum::md::CVotosVotavel's two constructors (fns 2856, 5863) and the constructor of the identification it holds
#   (fn 5864, class name chosen: comum::md::CIdentificacaoVotavel), in app/comum/gravadores/md/cvotosvotavel.{h,cpp}.
# - comum::asn::CConversorCorrespResultado (gravadores/asn/cconversorcorrespresultado.{h,cpp}): DoConverte (fn 10289)
#   and DoDesconverte (fn 10288), over the head of comum::asn::CConversorCarga (gravadores/asn/cconversorcarga.h,
#   vtable @1596140, which ledger/vtables.json misses; its typeinfo name is the string at 543560), whose two slots (fns
#   10291, 10290) fragment 172 matches.
# - comum::asn::CConversorUrna (gravadores/asn/cconversorurna.{h,cpp}): DoConverte (fn 10287) and DoDesconverte (fn
#   10284), with ConverteTipoUrna, DesconverteTipoUrna, ConverteTipoArquivo and DesconverteTipoArquivo (records :77,
#   :95, :117, :139), which binaryen inlines into them. Urna's generated setter of numeroSerieFV takes
#   numeroSerieFV::const_reference (src/asn1/modules/ModuloTiposResultadosEcoUrna.h): fn 10287 builds a temporary of the
#   field's own type (vptr 1596592) before the assignment (docs/reference/facts/asn1.md A3). A twin moves with it:
#   fn 5368's line now names Constrained_OCTET_STRING<SizeConstraint<2, 4, 4>>'s deleting destructor, which that
#   temporary brings into our link ahead of ASN1::OCTET_STRING's.
# - comum::asn::CConversorEnvelopeGenerico (gravadores/asn/cconversorenvelopegenerico.{h,cpp}): DoConverte (fn 10271)
#   and DoDesconverte (fn 10270), with ConverteTipoEnvelope and DesconverteTipoEnvelope (records :168, :191) and
#   md::CEnvelopeGenerico's GetUrna, GetLocal and GetSeguranca (unit 136's), which binaryen inlines into fn 10271.
#   md::CEnvelopeGenerico's constructors take the local's std::optional by value: fn 10270 copies it into a slot of its
#   own frame for each call (below); the constructors' bytes are the same either way, and their match lines (3821,
#   5860, 5861) follow the new symbols. md::CUrna's implicit destructor (fn 1394) now comes from
#   cconversorenvelopegenerico.cpp.o, whose DoDesconverte deletes one.
# The data classes gain the inline getters these bodies read (ccorrespondenciaresultado.h, curna.h, cenvelopegenerico.h;
# unit 136's headers): their names are chosen.
#
# Evidence: the vtables and RTTI give each class and slot, the records each converter's file, lines and the static
# members' signatures, and the bodies the layouts, the calls, the codes and the messages. CCopiadorMR's header was unit
# 102's at app/comum/ccopiadormr.h; it moves to gravadores/, where the constructors and both vtables lie in link order
# (between gravadores/cassinador.cpp and gravadores/md/cdependenciascontratos.cpp, in the data and in the constructors'
# use bands), and unit 102's two dropped builders pass the constructor's arguments now. Fn 11623 has the (i32 i32) type
# of a result slot and `this`: IGravadorEnvelope's GravaResultado (fn 11626) calls slot 8 with both, and the body
# returns the file's content, a std::vector<uebyte>. The static members' throws in a switch's default (column 19) or
# after it (column 11) are the records' columns.
# Chosen: the paths of the files no record names (ccopiadormr.*, ccopiadorwsqmr.cpp, cgravadorenvelopearquivo.cpp,
# igravadorenvelope.cpp, md/cvotosvotavel.*, asn/cconversorcarga.h, and the converters' headers beside their .cpp),
# CCopiadorMR's parameter types (DeterminaNomeArquivo's) and member name, LeConteudo's name (from its role) and its
# const (the const GravaResultado calls it on `this`), CIdentificacaoVotavel's name, the members' and locals' names,
# the getters' names, CVotosVotavel's count as ueword and its identification by const reference, the lines of every
# function with no record (the four converters' slots, the constructors, LeConteudo), and the order of the definitions
# where no band gives it.
#
# Forms measured in this unit's link (pnpm wasm score against the plain link, then the scan):
# - CCopiadorWSQMR's constructor beside CCopiadorMR's in one .cpp: clang inlines CCopiadorMR's, `8 over 18 rows
#   (... inserted 5 ...)`, where fn 3827 keeps the call (fn 1276) and takes `this` from its result; in its own file,
#   `2 over 13`, operand rows only.
# - LeConteudo passing conteudo.size() to RawRead, with no test of the size: `22 over 112 (... inserted 3, deleted 2)`;
#   the size read once into a local, RawRead given it, and the file opened only when it is not 0 (the target jumps past
#   the CFile when it is): `9 over 109`, operand rows only.
# - CConversorCorrespResultado::DoDesconverte: a pointer to the MunicipioZona taken in the branches and a named
#   converter declared before the return, `58 over 399 (... inserted 9, deleted 7)`; the converter as a temporary in
#   the return, `71 over 396 (... inserted 6, deleted 4)`, its frame slot below the CCarga's where the target has it
#   above; the municipality and zone read in the branches and the named converter after them, `53 over 396 (...
#   inserted 6, deleted 4)`; and with the urna's type declared before the section, `39 over 390`, operand rows only
#   (the branch block's value is the type, as the target's).
# - CConversorEnvelopeGenerico::DoDesconverte with CEnvelopeGenerico's constructors taking the optional by const
#   reference: `216 over 837 (... inserted 42, deleted 40)`, a frame 48 bytes smaller; by value, `82 over 795`, operand
#   rows only.
# The other bodies gave operand rows only as first written; no other form was measured, and no two forms here were
# found to give the same bytes.
#
# Not matched, and what each waits for:
# - CCopiadorMR's slots 2 and 3 (fns 5874, 5873) are pending (the -pending.cpp header says on what).
# - Not attempted: comum::asn::CConversorEntidadeHashes::DoConverte (fn 10266; md::CEntidadeHashes's members past +36
#   are not recovered) and the constructor at fn 5824 (562 B, its one caller vota::CGravaResultado::StartState, fn
#   12098), whose class no evidence names. Not written:
#   template instances whose callers are not written, so that no instance of ours exists
#   (the element types are readings of the bodies; 5859, which was among them, matches from unit 200's roots): 3815 (a
#   destructor of a class no evidence names; fns 11587, 11626, 11629), 5852 and 5854
#   (over a vector of 24-byte elements of two strings; fns 5854, and 5358 and 11620), 5868 (a tree insertion with a
#   string key; fn 5869), 5843 and 5844 (vector<ecourna::app::dados::CEstadoComparecimento>'s reallocating paths;
#   fn 11616) and 3816 (the relocation of a vector of comum::md::CCargo; fns 3818 and 11371).
GRAVADORES_CLASSES_SRCS := src/app/comum/gravadores/ccopiadormr.cpp src/app/comum/gravadores/ccopiadorwsqmr.cpp \
	src/app/comum/gravadores/igravadorenvelope.cpp src/app/comum/gravadores/cgravadorenvelopearquivo.cpp \
	src/app/comum/gravadores/md/cvotosvotavel.cpp
GRAVADORES_CLASSES_ASN_SRCS := src/app/comum/gravadores/asn/cconversorcorrespresultado.cpp \
	src/app/comum/gravadores/asn/cconversorurna.cpp src/app/comum/gravadores/asn/cconversorenvelopegenerico.cpp
UENUX2_SRCS += $(GRAVADORES_CLASSES_SRCS) $(GRAVADORES_CLASSES_ASN_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(GRAVADORES_CLASSES_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# not every caller is reconstructed: 160-uenux2-comum-gravadores-classes-roots.cpp stands in for the others (the copiers'
# builder fn 12134, fns 3819, 3820 and 12098) and keeps CConversorEnvelopeGenerico's vtable; it compiles with the
# tree's flags
$(ROOT)/$(APP)/160-uenux2-comum-gravadores-classes-roots.o: $(ROOT)/src/units/160-uenux2-comum-gravadores-classes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/160-uenux2-comum-gravadores-classes.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/160-uenux2-comum-gravadores-classes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/160-uenux2-comum-gravadores-classes-roots.o
# CCopiadorMR's and CConversorCarga's slots are not reconstructed: 160-uenux2-comum-gravadores-classes-pending.cpp gives
# them trapping bodies, compiled with the tree's flags, and emits the classes' vtables and destructors
$(ROOT)/$(APP)/160-uenux2-comum-gravadores-classes-pending.o: $(ROOT)/src/units/160-uenux2-comum-gravadores-classes-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/160-uenux2-comum-gravadores-classes.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null) $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/160-uenux2-comum-gravadores-classes-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/160-uenux2-comum-gravadores-classes-pending.o
