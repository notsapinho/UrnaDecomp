# uenux2 comum::gravadores classes and converters, paths relative to src/uenux2:
# - comum::CCopiadorMR and comum::CCopiadorWSQMR (src/app/comum/gravadores/ccopiadormr.{h,cpp}, ccopiadorwsqmr.cpp):
#   both constructors (target fns 1276 and 3827), the destructors defined in the class (fns 11638 and 5872, slots 0
#   and 1 of both vtables, thunks into binaryen's merged bodies fns 1723 and 1722), and CCopiadorMR's slots 2 and 3
#   (fns 5874 and 5873, slots of both vtables too), in ccopiadormr.cpp after the constructor, Slot2 first, as their use
#   band gives. Slot2 is the key function, so ccopiadormr.cpp.o emits CCopiadorMR's vtable and with it the two inline
#   destructors, ahead of ccopiadorwsqmr.cpp.o's copies (the pending object emitted the vtable before). CCopiadorWSQMR's
#   deleting destructor is the same body as CCopiadorMR's, so fn 5872's match line follows CCopiadorMR's symbol now
#   (step 9 renamed it). Each slot copies the file named at +4 from the result directory of one flash
#   (comum::CPath::GetPathResult, fn 1274, with FLASH_INTERNA for Slot2 and FLASH_EXTERNA for Slot3) to the MR's
#   (CPath::GetPathMR, fn 949), with api::CSystem::CopyFile (fn 378), passing false and true as unit 122's fragment
#   says of IGravador's slots. Measured in this link before step 8 (pnpm wasm score against the target): 5874 and 5873
#   19 over 293 rows each, operand-only, every operand a call's or a data address; the paths as named const locals and
#   their names are chosen, and no other form was measured.
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
# - comum::IGravadorEnvelope::GravaResultado (target fn 11626, slot 7, the class's key function) in
#   igravadorenvelope.cpp, which emits IGravadorEnvelope's vtable and implicit destructor now (fn 11625, under the same
#   symbol; unit 136's pending object held the trap), with its builder MontaEnvelope (no index of its own: binaryen
#   inlines it, the 400-byte frame inside 11626's 224-byte one; clang keeps it out of line, wasm-objdump -d of the
#   object). The file's notes say what the body reads; igravadorenvelope.h why +56 is the urna's ETipoArquivo, the type
#   the CUrna constructors take there (it was a chosen EUrnaTipo; 49 either way, the constructor's bytes the same). It
#   reads the media's serial through comum::CarregaArquivoEcourna (fn 3735, unit 280) and a getter of
#   ecourna::app::dados::CSerialMidia added for it (cserialmidia.hpp; its name chosen). With it ecourna's
#   CInformacaoMidia's implicit destructor (fn 3815) comes from this object (its band place, among cgravadorbu.cpp's
#   functions, reads as that object's copy in the target: a reading; the copies are the same code). Measured in this
#   link before step 8 (pnpm wasm score against the target): 11626 57 over 664 rows and 3815 8 over 137, operand-only,
#   every operand a call's or a data address; it is the first form written, and no other was measured.
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
#   5860, 5861) follow the new symbols. md::CUrna's implicit destructor (fn 1394) came from
#   cconversorenvelopegenerico.cpp.o then, whose DoDesconverte deletes one; it comes from igravadorenvelope.cpp.o
#   since (11626, below, destroys one, and that object links ahead).
# - comum::asn::GravaArquivo for the envelope (fn 2724, a thunk into fn 6006), in cconversorenvelopegenerico.cpp after
#   the static members (its line a choice): a converter on the stack, Converte and api::CFileASN::WriteToFile, which
#   binaryen inlines. Its notes, and the merge 6006 it forms with the hashes' writer, are in its header and unit 293's
#   fragment, whose roots stand for its callers (2725, 11629; 11626 is this unit's). It stores
#   CConversorEnvelopeGenerico's vptr, so the vtable's sink in this unit's roots went with it.
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
# - comum::asn::CConversorEntidadeHashes::DoConverte (fn 10266) is unit 293's file's and matches (centidadehashes.h has
#   the members it reads). The constructor at fn 5824 (562 B, its one caller vota::CGravaResultado::StartState, fn
#   12098) matches in unit 195, as comum::CGeradorResultados's (a chosen class: no evidence names it). Not written:
#   template instances whose callers are not written, so that no instance of ours exists (the element types are readings
#   of the bodies; 5859 and 3815, which were among them, match from unit 200's roots and igravadorenvelope.cpp.o): 5843
#   and 5844 (vector<ecourna::app::dados::CEstadoComparecimento>'s reallocating paths; fn 11616). 3816 (the relocation
#   of a vector of comum::md::CCargo; fns 3818 and 11371) and 5868 (a tree insertion with a string key), which were
#   among them, match: 3816 from unit 200's cgravadorbu.cpp.o (3818's object; fragment 299's cconversoreleicaope.cpp.o,
#   11371's, held the copy before), 5868 from fragment 268's object, its caller fn 5869's.
# - 5852 and 5854 (std::vector<api::hash::CHashArquivo>'s range insert and its helper; fns 5358 and 11620 call 5854) are
#   fragment 227's: 5852 matches from cmontadorhash.cpp's object, and 5854 waits for 11620, whose object, built without
#   strict aliasing, reads as the one that holds the target's copy (fragment 227 has the measurement).
GRAVADORES_CLASSES_SRCS := src/app/comum/gravadores/ccopiadormr.cpp src/app/comum/gravadores/ccopiadorwsqmr.cpp \
	src/app/comum/gravadores/igravadorenvelope.cpp src/app/comum/gravadores/cgravadorenvelopearquivo.cpp \
	src/app/comum/gravadores/md/cvotosvotavel.cpp
GRAVADORES_CLASSES_ASN_SRCS := src/app/comum/gravadores/asn/cconversorcorrespresultado.cpp \
	src/app/comum/gravadores/asn/cconversorurna.cpp src/app/comum/gravadores/asn/cconversorenvelopegenerico.cpp
UENUX2_SRCS += $(GRAVADORES_CLASSES_SRCS) $(GRAVADORES_CLASSES_ASN_SRCS)
# igravadorenvelope.cpp reads ecourna's media information (CInformacaoMidia, whose CDadosGeracaoMidia holds a Boost
# ptime) through its converter, whose header includes the generated ASN.1 module by its bare name
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/igravadorenvelope.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/igravadorenvelope.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(GRAVADORES_CLASSES_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# not every caller is reconstructed: 160-uenux2-comum-gravadores-classes-roots.cpp stands in for the others (the copiers'
# builder fn 12134 and fn 12098); it compiles with the tree's flags
$(ROOT)/$(APP)/160-uenux2-comum-gravadores-classes-roots.o: $(ROOT)/src/units/160-uenux2-comum-gravadores-classes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/160-uenux2-comum-gravadores-classes.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/160-uenux2-comum-gravadores-classes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/160-uenux2-comum-gravadores-classes-roots.o
