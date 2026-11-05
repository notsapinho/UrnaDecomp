# uenux2 comum's result data classes, the converter of one of them, and the recorders' destructors, in the files the
# records name (paths relative to src/uenux2/src/app/comum):
# - md::CCarga (dados/md/correspondencia/ccarga.h, layout only): its implicit copy constructor (target fn 1557), which
#   the objects of curna.cpp, cenvelopegenerico.cpp and ccorrespondenciaresultado.cpp hold, the link keeping
#   curna.cpp.o's; md::CCorrespondenciaResultado's constructor (fn 2801, ValidaCriacao inlined by binaryen) in
#   dados/md/correspondencia/ccorrespondenciaresultado.cpp.
# - md::CUrna (gravadores/md/curna.{h,cpp}): both constructors (fns 2854, 2855), ValidaCriacao (fn 5862) and the implicit
#   destructor (fn 1394), which unit 160's igravadorenvelope.cpp.o emits (11626 destroys a CUrna; before it, unit 160's
#   cconversorenvelopegenerico.cpp.o, whose DoDesconverte deletes one), ahead of this unit's roots object;
#   comum::ETipoArquivo is declared in curna.h.
# - md::CEnvelopeGenerico (gravadores/md/cenvelopegenerico.{h,cpp}): the three constructors (fns 3821, 5860, 5861) and
#   ValidaCriacao (fn 3822); the getters GetUrna, GetLocal and GetSeguranca (records :96, :106, :117), which binaryen
#   inlines into their one caller, CConversorEnvelopeGenerico::DoConverte (fn 10271, unit 160), as the target's does.
# - md::CEntidadeHashes::ValidaCriacao (fn 5855, gravadores/md/centidadehashes.{h,cpp}; the header holds the head of
#   the layout only).
# - md::CTipoApuracaoSA (gravadores/md/ctipoapuracaosa.{h,cpp}) and asn::CConversorTipoApuracaoSA
#   (gravadores/asn/cconversortipoapuracaosa.{h,cpp}): DoConverte (fn 10283, the four ConverteMotivo* inlined by
#   binaryen) and DoDesconverte (fn 10282, the data class's constructor and checks inlined).
# - The recorders' destructors: CGravadorHashes's (5853, 11619), emitted with its vtable in
#   136-uenux2-app-comum-gravadores-md-pending.cpp, whose trap is the class's key function (src/units/README.md "The key
#   function pending"), and CGravadorLog's (5823, 11583), emitted with its vtable by cgravadorlog.cpp (below), which
#   holds its key function, under the symbols the pending object gave them. IGravadorEnvelope's (fn 11625) and
#   CGravadorRDV's (11586, and 11585, matched, below) come with their vtables from unit 160's igravadorenvelope.cpp and
#   unit 305's cgravadorrdv.cpp, which hold their key functions (GravaResultado, fns 11626 and 11587), under the same
#   symbols; and binaryen's merge
#   of the base-object destructors of CGravadorRDV and IGravadorEnvelope (fn 6043, written, below; our link forms the
#   same two-member merge, byn$mgfn-shared$_ZN5comum17IGravadorEnvelopeD2Ev since igravadorenvelope.cpp.o links ahead
#   of cgravadorrdv.cpp.o: step 9 renamed the match line). The class heads are unit 102's (gravadores/cgravador*.h,
#   igravadorenvelope.h); this unit adds their layouts and virtual members there. CGravadorRCSecao's deleting destructor
#   (fn 11615) is unit 122's. CGravadorEnvelopeArquivo's (fns 11622, 11621, matched, below) are emitted with its vtable
#   by unit 160's cgravadorenvelopearquivo.cpp, which holds its key function, and CGravadorVersoesArquivos's (11581,
#   11580) by unit 122's cgravadorversoesarquivos.cpp, which holds its key function (11582).
# - comum::CGravadorLog::GravaResultado (fn 11584, slot 7, the class's key function) in gravadores/cgravadorlog.cpp, the
#   class's name in lower case beside igravador.h, a path chosen: no record names the file. Its one record is
#   api::CSystem::Rename's (csystem.cpp:692, unit 32), which binaryen inlines into it, and which names it
#   (srcloc-anchor). The body builds a std::filesystem::path of +52, a std::map<path, path> from the one pair {that
#   path, its filename()} (the hinted insert of an initializer-list constructor, a reading of the inlined __find_equal),
#   inserts {path, filename()} of each regular file of the directory +40 names (the key copied and the value moved,
#   looked up before the node is allocated: insert(value_type&&), a reading), builds +64 + "temp.jez" (one 8-byte
#   store), zips the map into that file and closes it, and renames the file to +64 followed by IResultado's file name
#   (+20); the api::CFile it is given is not read. The directory_iterator's path temporary is freed after the loop,
#   C++23's lifetime of a range-for initializer's temporaries (-std=c++23, the tree's), a reading. The map's
#   __tree::destroy is fn 3797, matched from this object, named by 11584's call; its key and value types are those of
#   ICompressor::Add(const std::map<path, path>&) (fn 9529), which takes the map, and its key is a path, whose
#   path::__compare the inlined finds call. The tree's find and insert members are this object's too, and binaryen
#   inlines them into their one caller (names.tsv has none of them), as 11584 holds them in the target.
#   The zip is built by a second ecourna::api::compression::CZip constructor, CZip(const path&, const map<path, path>&,
#   ENivelCompressao), at the end of ecourna's czip.cpp (unit 06's), which binaryen inlines into 11584, its one caller,
#   with the landing pads uenux2's code has none of (czip.hpp gives the evidence). Measured with pnpm wasm score in this
#   unit's link: with the level written as ENivelCompressao::PADRAO in that constructor's initializer, clang stores +28
#   and +32 as one i64, and 11584 scored 93 over 2052 rows (87 of the 90 replaced operand-only, 3 deleted); with the
#   level a parameter GravaResultado passes, 88 over 2052, every row an operand, and the match.
#   Unit 32's roots' stand-in for 11584, which called Rename, went with it, and so did unit 06's roots' address-takes of
#   ICompressor::Add(map), CZip::SafeClose and CZip::CreateZipFile (the invoke_* slots 6050, 6122 and 6119, whose
#   target users are 11584 and CZip's constructor 5193), of ICompressor's constructor and destructor (5192, 1526) and
#   of CZip::Close and CZip's destructor (2691, 2690), whose every other target caller is in the link: these matches
#   are measured on the link without them, which moved no other scan row.
#   The order of the objects: the target's data put CGravadorLog's vtable (@1557188) after cgravadorutil.cpp's records
#   (to @1557172) and before CGravadorVersoesArquivos's vtable (@1557240), and use band 1 runs CGravadorRDV's 11587 to
#   11585, then 11584 and 11583, then CGravadorVersoesArquivos's 11582 (a higher index linking first), so the target's
#   object sits between cgravadorutil.cpp's and cgravadorversoesarquivos.cpp's, a place in unit 122's list. At the end
#   of this unit's list, after unit 122's objects and ahead of unit 305's cgravadorrdv.cpp, 11584 and 3797 match too:
#   the plain link's command with the object moved to just ahead of cgravadorversoesarquivos.cpp.o (docs/reference/
#   facts/workflow.md W13, "One variant object in the whole link") scored both the same (88 over 2052 and 3 over 39,
#   every row an operand), and the link with the file compiled in unit 122's list holds every match of the link with
#   it at the end of this unit's, no row entering or leaving match. Both places give the bytes, so the file is
#   compiled at the data's, in unit 122's list ahead of cgravadorversoesarquivos.cpp (docs/how-to-decompile.md step
#   3), with the include paths its CZip needs. Of the 50 objects between the two places the move puts 39 in the data's
#   order and inverts 8, whose data lie before @1557188 (docs/reference/facts/codegen.md C4):
#   gravadores/cgravadorrcsecao.cpp (records from @1554780), md/cversoesarquivos.cpp (@1553472),
#   vota/eleitor/celeitorvotando.cpp (@1533188), this unit's md/curna.cpp (@1553732), md/cenvelopegenerico.cpp
#   (@1553844) and md/centidadehashes.cpp (@1554560), and the simulator's mock/app/simulador/wasm/cwasminit.cpp and
#   cwasmresource.cpp (their vtables); 3 have no data place. Counted over every app object with records or a strong
#   vtable, 253 pairs with it are out of the data's order at the data's place and 284 at the end of this unit's list
#   (a record's place: awk -F'\t' '$2 ~ /<file>$/' ledger/source-locations.tsv). Inside the object 11584 links ahead
#   of 11583, the band's order (ld_index in names.tsv).
#   Chosen: the file's path, the member names (cgravadorlog.h), the locals' names and their being const, the explicit
#   PADRAO argument (a default argument in czip.hpp was not measured), and the second constructor's file, line,
#   parameters' forms (references) and order. No other form of 11584 or of the constructor was measured to give the
#   same bytes.
# - ModuloTiposResultadosEcoUrna (src/asn1/modules/): the records and RTTI name ModuloTiposResultadosEcoUrna::TipoApuracaoSA
#   (the converter's base, typeinfo @1596936) and MotivoApuracaoManual, MotivoApuracaoEletronica, MotivoApuracaoMistaComBU
#   and MotivoApuracaoMistaComMR (the four ConverteMotivo* records' result types), which the generated module held
#   nested as Urna::motivoUtilizacaoSA::value_type and the four motivoApuracao::value_type; they are classes at namespace
#   scope now, the fields' value_type a typedef of them (src/asn1/README.md "The generated modules"). The module's
#   object holds the same code and data bytes before and after (wasm-objdump -d and -s -j Data compared), its data
#   symbols renamed.
#
# Evidence: the records give each member's file, line, column and signature, the vtables and RTTI each class and slot,
# and the bodies the layouts (each header says from what), the codes and the messages. The recorders' layouts come from
# their destructors and from vota::CGravaResultado::StartState (fn 12098) and fn 5856, which build them.
# Chosen: every member, enumerator, parameter and getter name; the headers' paths (beside the .cpp their records name,
# or beside igravador.h); comum::EUrnaTipo (dados/md/estadoaplicacao/eurna.h) as the urna's type, the CBaseType
# identifiers of iresultado.h in CEnvelopeGenerico, ETipoArquivo's and CEnvelopeGenerico::Tipo's enumerator
# names, CTipoApuracaoSA's type as a nested enum with a formatter, the motivos as integer literals in the switches,
# the parameter forms beyond what the bodies copy (const references), the lines of every function with no record, the
# recorders' trivial members' types, the order of the md classes' constructors, and that the checks are private.
#
# Forms measured in this unit's link (pnpm wasm score, then the scan):
# - CCorrespondenciaResultado's identifiers are plain unsigned words: with iresultado.h's CBaseType aliases read through
#   Get(), the three unsigned throws store the format's argument types before its string, the target the reverse
#   (the header has the probe).
# - CConversorTipoApuracaoSA::DoConverte reads the type into a local before the switch, which the default's
#   std::format takes by address: written as dado.GetTipoApuracao() in both places, the store of the value moves into
#   the default case (7 rows inserted, 5 deleted against the target).
# - CTipoApuracaoSA::ValidaMotivoApuracao's cases run 1, 3, 4, 2: in the order 1, 2, 3, 4 the br_table differs.
# - CGravadorLog's destructor is declared in the class: implicit, its deleting destructor inlines the base-object body
#   (53 rows inserted), where the target calls it. CGravadorHashes's implicit destructor gives the target's call
#   shape (a reading: its base-object body, two shared_ptr releases more, costs more to inline), and so does
#   `~CGravadorHashes() override = default;` in the class: the pending object is byte-identical either way at the
#   tree's -O3. Implicit is the choice.
# - The phase tests of CEnvelopeGenerico and CEntidadeHashes are written `m_fase == '0' || m_fase > FASE_TREINAMENTO`,
#   the target's two compares (48 and 52, signed); no other spelling was measured.
# Same bytes: CGravadorHashes's destructor implicit or declared `= default` in the class (above); no other form here
# was measured to give the same bytes.
#
# CGravadorEnvelopeArquivo's destructors (fns 11622, 11621), CGravadorRDV's deleting destructor (11585) and the merge
# 6043 call md::estadoaplicacao::CDadoCorrespondencia's base-object destructor (fn 857) and drop the this it returns.
# They match while a function of our link uses that result, and with none they differ by that drop alone (pnpm wasm
# score: deleted 1, every other row operand-only). At -O2, CAppInfo's destructor in appinfo/cappinfosingleton.cpp.o
# used it at two of its three calls; at the tree's -O3 it calls the destructor once and drops it. The target's users of
# the result are fns 5532, 7787, 9873 and 11395; src/app/roots_vector.cpp holds the executable TU's copies of 5532 and
# 9873, which keep it (docs/reference/facts/splat.md §S10 item 17).
#
# Not matched, and what each waits for:
# - The converters of CUrna, CCorrespondenciaResultado and CEnvelopeGenerico (fns 10287, 10284, 10289, 10288, 10271,
#   10270) are unit 160's. CConversorEntidadeHashes::DoConverte (10266) matches from unit 293's
#   cconversorentidadehashes.cpp, which reads CEntidadeHashes's members past +36 (centidadehashes.h says how).
# - IGravador's slots 2 to 6 (fns 11630 to 11634) are not this unit's: unit 122's. CCarga::ValidaCriacao (fn 5670) is
#   unit 157's (dados/md/correspondencia/ccarga.cpp), and matches.
GRAVADORES_MD_SRCS := src/app/comum/gravadores/md/curna.cpp src/app/comum/gravadores/md/cenvelopegenerico.cpp \
	src/app/comum/gravadores/md/centidadehashes.cpp src/app/comum/gravadores/md/ctipoapuracaosa.cpp \
	src/app/comum/dados/md/correspondencia/ccorrespondenciaresultado.cpp
GRAVADORES_ASN_SRCS := src/app/comum/gravadores/asn/cconversortipoapuracaosa.cpp
UENUX2_SRCS += $(GRAVADORES_MD_SRCS) $(GRAVADORES_ASN_SRCS)
# cgravadorlog.cpp, this unit's GravaResultado, is compiled in unit 122's list (its place in the link, below), with the
# include paths its CZip needs (minizip's zip.h and, through ICompressor, Boost's signals2), not flags of the code
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(GRAVADORES_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# not every caller is reconstructed: 136-uenux2-app-comum-gravadores-md-roots.cpp stands in for the others, two call
# sites each; it compiles with the tree's flags, since it emits CUrna's inline destructor (fn 1394), TSE code (the link
# keeps unit 160's copy, from igravadorenvelope.cpp.o, linked ahead of it)
$(ROOT)/$(APP)/136-uenux2-app-comum-gravadores-md-roots.o: $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/136-uenux2-app-comum-gravadores-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/136-uenux2-app-comum-gravadores-md-roots.o
# CGravadorHashes's key function is not reconstructed: 136-uenux2-app-comum-gravadores-md-pending.cpp gives it a
# trapping body, compiled with the tree's flags, and emits its vtable and implicit destructors
$(ROOT)/$(APP)/136-uenux2-app-comum-gravadores-md-pending.o: $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/136-uenux2-app-comum-gravadores-md-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/136-uenux2-app-comum-gravadores-md-pending.o
