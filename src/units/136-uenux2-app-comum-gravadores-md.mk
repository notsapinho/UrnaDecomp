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
# - md::CEntidadeHashes (gravadores/md/centidadehashes.{h,cpp}): ValidaCriacao (fn 5855) and the two constructors, one
#   per identification, which binaryen inlines into fn 11620, their one caller (below; the header has the layout).
# - md::CTipoApuracaoSA (gravadores/md/ctipoapuracaosa.{h,cpp}) and asn::CConversorTipoApuracaoSA
#   (gravadores/asn/cconversortipoapuracaosa.{h,cpp}): DoConverte (fn 10283, the four ConverteMotivo* inlined by
#   binaryen) and DoDesconverte (fn 10282, the data class's constructor and checks inlined).
# - The recorders' destructors: CGravadorHashes's (5853, 11619) and CGravadorLog's (5823, 11583), emitted with their
#   vtables by cgravadorhashes.cpp and cgravadorlog.cpp (below), which hold their key functions, under the symbols the
#   pending object gave them before. IGravadorEnvelope's (fn 11625) and
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
# - comum::CGravadorHashes::GravaResultado (fn 11620, slot 7, the class's key function, record cgravadorhashes.cpp:112)
#   in gravadores/cgravadorhashes.cpp, the record's file, written and not matched (below), with the free function
#   comum::CalculaHashesArquivos it calls, which binaryen inlines into it (a frame of its own inside 11620's), a chosen
#   name: it builds the set of directories to leave out (CPath::GetDiretoriosSemHash, unit 190's cpath.cpp, inlined into
#   it behind a third frame), lists the hashes under the root followed by "" and under CPath::GetPathChave()
#   (api::hash::ListaHashesDiretorio, fn 5359, unit 227's, twice), and appends the second list to the first with
#   vector::insert, the range insert 5854. GravaResultado builds the header (fn 1945 with the pleito's id, as
#   CGravadorBU's does), the hashes, then the entity with the section's identification at +68 or else the contingency's
#   at +76, each written with comum::asn::GravaArquivo (fn 5367, unit 293's), else throws 8644 "Tipo de urna inválido"
#   (its record). Its object is compiled in unit 190's list, right after cpath.cpp (below and unit 190's fragment).
#   5854, the range insert, matches from this object, built without strict aliasing as app/comum/gravadores is (the
#   target's copy, which unit 227's fragment had read so from 5854's band): ahead of cmontadorhash.cpp.o, which
#   compiles the same instance with strict aliasing; its helper 5852 and the set's __tree::destroy (633) come from
#   this object too now, the first on the link line to emit them.
# - Written for vota::CGravaResultado::StartState (fn 12098), which holds them inlined, so with no target index and no
#   match until 12098 is written (unrooted: wasm-ld drops them): CGravadorHashes's two constructors in
#   cgravadorhashes.cpp, one per identification type, and CGravadorLog's in cgravadorlog.cpp, each ahead of
#   GravaResultado. In the folded readout `pnpm --silent wasm fn ../target/vota_web_wasm.wasm 12098` prints (lines
#   counted from the one after `;; --- folded readout`), the two Hashes constructors sit in the arms of 12098's test of
#   the section (vptr stores at lines 842 and 903): each calls IGravador's constructor with the identification's
#   municipality and zone, its place and section or 0 and 0, the extension 12 and the SAVD file 46, then copies the
#   date-time, ConverteFase's result, a string, a new copy of the identification behind a std::shared_ptr (+68 or +76)
#   and a string; the Log constructor follows `new` (line 2266) and copies three strings from temporaries 12098 frees
#   after it. The 32-byte frame of lines 2226 to 2265, before that `new`, is not the constructor's: it builds the
#   "arquivados/" directory (GetPathLog's code, then / "arquivados/"), an argument: comum::GetPathLogArquivados,
#   written after the Log constructor in cgravadorlog.cpp (its name, its being a free function of comum, its file and
#   its line chosen; external, so that clang keeps it out of line for binaryen to inline: cgravadorlog.h), unrooted. Its
#   object opens the readout's 32-byte frame, the "dinamico/log/" path at +16, GetPathLog's result at +0, then the
#   "arquivados/" path at +16. Measured on the objects (wasm-objdump -d): the three constructors open no frame, as 12098
#   shows none for them. With the Hashes
#   constructors written, cgravadorhashes.cpp.o instantiates the two pointer blocks' members, and the link keeps its
#   copies of CIdentificacaoSecao's and CIdentificacaoUrnaContingencia's __get_deleter (11618, 11617; the same symbols,
#   still matched), which came from unit 102's roots object before. Chosen: the constructors' parameters (order and
#   form), the extension and the SAVD file as their own constants rather than 12098's arguments, the two overloads
#   (a reading of the two inlined copies), and their lines.
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
#   `~CGravadorHashes() override = default;` in the class: the pending object that emitted the vtable before was
#   byte-identical either way at the tree's -O3 (not measured again on cgravadorhashes.cpp's object). Implicit is the
#   choice.
# - fn 11620, with pnpm wasm score in this unit's link: 477 over 2075 rows, 22 inserted and 6 deleted, all of them in
#   the set CPath::GetDiretoriosSemHash builds: cpath.cpp, built without strict aliasing as app/comum is, inlines
#   libc++'s __emplace_hint_unique_extract_key and calls __emplace_hint_unique_key_args (fn 2281's body) with an 8-byte
#   result in the frame, where the target calls __emplace_hint_unique_extract_key (fn 1163) eight times, the emplace
#   inlined into it, the shape a TU built with strict aliasing gives (cpath.cpp compiled both ways with -Rpass=inline:
#   the emplace costs 250 against a threshold of 250 without it, 245 with it; src/app/roots_set.cpp and unit 268's
#   fragment read 1163's shape so). With cpath.cpp.o compiled with strict aliasing in the same link, 11620 scores 182
#   over 2053, every row an operand: calls, data addresses, CPath's statics (.bss, named) and the exception's destructor
#   slot; the 15 of unit 190's matches scored (all but the statics' exit destructors) score the same both ways. The flag
#   is the user's decision (docs/reference/facts/app-flags.md F6), and it alone matches nothing yet: the scan stops at
#   `+0x43d i32.const 333562: an address of ours: string tail occurs 4098 times`, the end of "/tmp/", which the target
#   holds as the tail of "c:/tmp/" (358564), a literal of 7-Zip's CSequentialOutTempBufferImp2::Write (fn 8324) that the
#   7-Zip our link builds lacks; and 5359 waits for a name (unit 227's fragment). With the file in this unit's list,
#   after centidadehashes.cpp, 11620 scores 557 over 2091 (38 inserted, 22 deleted), and with strict aliasing in
#   cpath.cpp 270 over 2071 (18 inserted, 18 deleted, the locals of the set's address): after cpath.cpp.o, as the data
#   put cpath.cpp's records (@1552104) ahead of this file's (@1554632), the locals are the target's.
# - The entity's constructors written in the class (inline) were not measured.
# - The phase tests of CEnvelopeGenerico and CEntidadeHashes are written `m_fase == '0' || m_fase > FASE_TREINAMENTO`,
#   the target's two compares (48 and 52, signed); no other spelling was measured.
# Same bytes: CGravadorHashes's destructor implicit or declared `= default` in the class (above); no other form here
# was measured to give the same bytes.
# Chosen for 11620: CalculaHashesArquivos's name, file and its being a free function with external linkage (it reads no
# class state; clang leaves it out of line, cost 1300 against 250, and binaryen inlines it, the frame the target holds),
# the members' and locals' names, the +56 string's name m_siglaUF (CEntidadeHashes::ValidaCriacao tests its length
# against 2, "UF inválida"), the branch's spelling and the lines of the functions above the record.
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
# - fn 11620 (above): strict aliasing in cpath.cpp's object (the user's decision), the literal "c:/tmp/" of 7-Zip's
#   8324, and 5359's name.
# - The converters of CUrna, CCorrespondenciaResultado and CEnvelopeGenerico (fns 10287, 10284, 10289, 10288, 10271,
#   10270) are unit 160's. CConversorEntidadeHashes::DoConverte (10266) matches from unit 293's
#   cconversorentidadehashes.cpp, which reads CEntidadeHashes's members past +36 (centidadehashes.h says how), and so
#   does fn 1300, the copy of the entity's hashes, from centidadehashes.cpp.o now, under std::vector<CHashArquivo>'s
#   name (its byte-identical twin std::vector<std::pair<std::string, std::string>>'s link copy left the link, and
#   step 9 renamed the line).
# - IGravador's slots 2 to 6 (fns 11630 to 11634) are not this unit's: unit 122's. CCarga::ValidaCriacao (fn 5670) is
#   unit 157's (dados/md/correspondencia/ccarga.cpp), and matches.
GRAVADORES_MD_SRCS := src/app/comum/gravadores/md/curna.cpp src/app/comum/gravadores/md/cenvelopegenerico.cpp \
	src/app/comum/gravadores/md/centidadehashes.cpp \
	src/app/comum/gravadores/md/ctipoapuracaosa.cpp \
	src/app/comum/dados/md/correspondencia/ccorrespondenciaresultado.cpp
GRAVADORES_ASN_SRCS := src/app/comum/gravadores/asn/cconversortipoapuracaosa.cpp
UENUX2_SRCS += $(GRAVADORES_MD_SRCS) $(GRAVADORES_ASN_SRCS)
# cgravadorhashes.cpp reaches Boost through CConfiguracaoEleicao's header (CHorariosUrna) and the generated module
# ModuloHashes through the converter's header: an include path, not a flag of the code, and the module headers
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorhashes.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorhashes.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# cgravadorhashes.cpp, CGravadorHashes's GravaResultado, is compiled in unit 190's list after cpath.cpp (above), with
# the rules below.
# cgravadorlog.cpp, this unit's GravaResultado, is compiled in unit 122's list (its place in the link, below), with the
# include paths its CZip needs (minizip's zip.h and, through ICompressor, Boost's signals2), not flags of the code
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(GRAVADORES_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# not every caller is reconstructed: 136-uenux2-app-comum-gravadores-md-roots.cpp keeps the recorders' vtables, which
# their constructors store (unrooted; their one caller, fn 12098, is not written); it compiles with the tree's flags. Its stand-in for 11620's two
# calls of CEntidadeHashes::ValidaCriacao (5855) went: 11620 is in the link.
$(ROOT)/$(APP)/136-uenux2-app-comum-gravadores-md-roots.o: $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/136-uenux2-app-comum-gravadores-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/136-uenux2-app-comum-gravadores-md-roots.o
