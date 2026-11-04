# uenux2 comum::asn::CConversorEntidadeEleitores (app/comum/dados/asn/eleitor/cconversorentidadeeleitores.h, beside the
# .cpp its records name), the entity it converts to, comum::md::CEntidadeEleitores (md/eleitor/centidadeeleitores.h),
# and the partial ASN.1 reader the lambda of CEleitores::GetEleitoresEstaticos (unit 110's celeitores.cpp) calls through
# LeEleitores (unit 280's carregaarquivo.cpp): api::CPartialFileASN (api/io/asn/cpartialfileasn.h, unit 83's header),
# comum::asn::IConversorParcialASN::Desconverte (app/comum/asn/iconversorparcialasn.h), ASN1::CoderEnv's setVisitors and
# getLog and ASN1's TVectorAbstractVisitor and TSharedSeeder (src/asn1/asn1.h), and comum::asn::CVisitanteEleitor's
# constructor and Prepara (unit 225's files); and the converter's slot 2, DoDesconverte (target fn 11411), in
# app/comum/dados/asn/eleitor/cconversorentidadeeleitores.cpp, with what it calls: md::CDataJE's constructor
# (md/cdataje.{h,cpp}), md::CTransferenciaTemporaria's two constructors (md/eleitor/ctransferenciatemporaria.cpp) and
# md::CEntidadeEleitores's two (md/eleitor/centidadeeleitores.cpp). Paths relative to src/uenux2. Every function of the
# read's chain is compiled in the objects of units 110, 280, 225 and 91, whose fragments point here.
#
# Matched with the chain: target fn 11523 (the lambda's call operator, unit 110's object), which holds the whole read,
# and 5704 and 5703, the visitors' vector's __assign_with_size over two const pointers and the copy loop it calls, from
# carregaarquivo.cpp.o. 11523 scored 140 over 1774 rows before step 8, all operand-only: calls, data addresses, packed
# std::format strings and table slots (pnpm wasm score in this unit's link).
#
# What the target shows: 11523 holds five frames of its own, each an out-of-line function with one caller that binaryen
# inlined (docs/how-to-decompile.md step 3):
# - 32 bytes, the lambda's own: the "rb" mode string and the api::CFile opened from the lambda's argument (fn 517),
#   closed after the read (fn 336, then the inline destructor's test of the handle).
# - 80 bytes, LeEleitores: the entity at +8, the visitor's std::shared_ptr at +68 and the converter at +76; the visitor
#   (operator new of 64 bytes, its constructor, the __shared_ptr_pointer block) before the converter's vptr store
#   (1566776), then Desconverte; the visitor released before the voters are copied out (fn 946 each), the entity
#   destroyed after (the voters' vector, then the optional's).
# - 720 bytes, Desconverte (record iconversorparcialasn.h:52, code 7665): the store of 1 at the visitor's +4 and the
#   list of two path and visitor pairs (cvisitanteeleitor.h's Prepara says what each is), ReadFromFile, the entity's
#   validity tested with its typeid name copied into a std::string (fn 148, before the std::ostringstream's
#   constructor, fn 220, and at a higher frame offset: a named local declared first) and traced into the stream, then
#   slot 2 of the converter's vtable called with the entity and the visitor's object.
# - 480 bytes, CPartialFileASN::ReadFromFile (record :182, code 5963): the open test, a std::shared_ptr<ASN1::ISeeder>
#   over a new api::CFileSeeder (its constructor inline), then "ReadFromFile de " + the file's name.
# - 752 bytes, CPartialFileASN::DecodeObjectFunction (records :277 and :285, codes 5968 and 5969): the CoderEnv at
#   +264 (rule 2 stored, the visitors assigned through fn 5704, then the entity built), ASN1::CoderEnv::decode over
#   the seeder (fn 5060); each throw traces the entity into a std::stringstream and formats the coder's log, copied
#   out, and the second also fires when that log is not empty.
# The partial reader's records, its control blocks' vtables and CFileSeeder's records lie in the entity readers' run of
# the target's data (unit 280's fragment), between the Candidatos reader's records and LeBiometriaEleitor's: so
# carregaarquivo.cpp's object instantiates them, and LeEleitores is defined there, before LeBiometriaEleitor. Inside
# that stretch the target puts the visitor's control block's vtable and typeinfo first (@1564316, @1564344, ahead of the
# entity's typeinfo @1564356), and ours puts them after the entity's vtable (wasm-objdump -x -j Data of
# carregaarquivo.cpp.o: the entity's typeinfo is segment 156, its vtable 194, the block's vtable and typeinfo 195 and
# 196): the file holds, and the form's first reference to the block comes later than the original's.
#
# Measured forms (each object compiled alone at its file's flags and read with llvm-objdump -d; the whole link scored):
# - LeEleitores: a converter named in it and the entity built from Desconverte over a visitor temporary stores the vptr
#   first and puts the shared_ptr at +8, below the entity; a helper template naming the converter over a visitor passed
#   by its caller stores the vptr after the news but keeps the shared_ptr at +8; the written form, a helper that creates
#   the visitor over one that takes it (CarregaArquivoParcial, both clang-inlined), gives the target's offsets and
#   order.
# - CVisitanteEleitor's constructor: out of line (cvisitanteeleitor.h has the three forms measured).
# - CoderEnv::setVisitors: assign over the list's two pointers (asn1.h has the two other forms and what each lost).
# - The roots stand-in below: without it binaryen inlined 5704 into its one caller, 11523, which then scored 1028 over
#   2175 rows (measured with an earlier setVisitors, the copy assignment).
#
# Chosen, no evidence names them: LeEleitores, CarregaArquivoParcial and Prepara (names, and their being a free
# function, a template pair and the visitor's static member), setVisitors and getLog and the typedefs' places in asn1.h,
# CPartialFileASN's being a `class` rather than a `struct` (that it is a class the records give: they print `static`),
# the error enumerators (from their messages), every local's name and every line of the headers but the throws'. The
# record lines are the targets'; the classes' file paths are the records' (cpartialfileasn.h, iconversorparcialasn.h) or
# rule 1 to 4 of how-to step 3 (the converter's head beside its .cpp, CEntidadeEleitores in md/eleitor/, as the
# converter's directory mirrors).
#
# Matched: 11411, CConversorEntidadeEleitores::DoDesconverte, and 2805, under the name of the hinted __find_equal of
# std::map<md::CEleitorIdentidade, md::CIndexer>'s tree, which this object instantiates (11411's copy of the visitor's
# map). The target's 2805 is binaryen's merge of at least three such instances, of maps whose nodes differ (the node
# each caller allocates right after its call of 2805: 40 bytes in 11411, 236 in 3614, 84 in 5376 and 10451; pnpm wasm
# fn), so the name is the instance our link holds, and the roots' stand-in stands for callers of the others. The
# converter's .cpp is the class's key function's file, so its object emits the vtable (@1566768). Before step 8, 11411
# scored 149 over 3308 rows, all operand-only: calls, data addresses, packed std::format strings and two table slots
# (pnpm wasm score in this unit's link; the rows that are no call or data address are 69 against 9 and 148 against 43,
# the throw's destructor slot and the format buffer's callback, and the format strings' packed i64 constants).
#
# What the target shows of 11411 (frames, pnpm wasm fn): DoDesconverte's own frame of 256 bytes, and inside it ten
# frames of out-of-line functions binaryen inlined, each with one caller: __emplace_hint_unique_key_args (16 bytes; the
# visitor's map copied node by node, the hinted __find_equal a call), GetInscricoesEleitor (528, records :49 and :76),
# ConverteNecessidadeEspecial (496, :38), DesconverteTransferenciaTemporaria (16, :236) and in it
# DesconverteTipoTransferenciaTemporaria (480, :210), the two CTransferenciaTemporaria constructors (16 each), CDataJE's
# constructor (480, cdataje.cpp:26) and vector<CEleitor>'s two __emplace_back_slow_path (32 each). The two
# CEntidadeEleitores constructors leave no frame; centidadeeleitores.h says why they are out of line.
#
# Measured (whole link, pnpm wasm score against 11411 unless an object is named; the object reads are wasm-objdump -d of
# the TU compiled alone at its flags). Each form below against the one written, everything else as written:
# - The voters' strings: std::string(field).substr(0, 40), the string_view constructor's __init inline and C++23's
#   rvalue substr truncating in place, is the target's; the identities pass the field to CEleitorIdentidade's by-value
#   std::string, the copy constructor (138 a call on its long path). nomeSocial default-constructed: 152 over 3308 rows
#   (3 not operand-only: twelve bytes zeroed where the target stores two), so it is built from "", as
#   CTransferenciaTemporaria's m_uf is.
# - The key: an assignment from the CSeguranca's GetChave, 482 over 3469 (161 inserted: the copy inlined where the
#   target calls 1158, vector<uebyte>::__assign_with_size over __wrap_iter); chave.assign over the vector's iterators,
#   as written, takes the CSeguranca as a named local (a temporary would be converted twice, a reading). The last arm's
#   CSeguranca as the constructor's temporary argument: 162 over 3314 (6 inserted, 7 deleted); it is named, as written.
# - The voters' list bound to a reference before the map's copy: without it (the range-for over get_eleitores()) 171
#   over 3314, the field read after the copy. Each voter's EleitorUrna through get_eleitor() at each use: one reference
#   to it, 654 over 3365. The biometria's search: assigning each find's result and testing it gives the same rows as the
#   written form (149 over 3308); the written one is chosen.
# - GetInscricoesEleitor: the copy's emptiness tested first, then the vector and std::transform into a back_inserter
#   over MontaEleitorIdentidade, a helper clang inlines, gives the target's zeroing of the vector after that test and
#   its blocks' order (the 7900 throw before the copy's destruction, the 7899 throw last), and so does a do-while loop;
#   a range-for, an iterator loop or a reserve after the same test place the 7899 throw right after the loop, and the
#   test of the result after the loop zeroes the vector before it (objects). Three push_backs, one per selection, give
#   three calls of the slow path where the target has one.
# - DoDesconverte's place: after its callees (last in the file) 302 over 3319 rows, 11 inserted, 11 deleted, every one a
#   local's number in the inlined callees; between GetInscricoesEleitor and DesconverteTipoTransferenciaTemporaria, the
#   149 above. The four objects in name order or with ctransferenciatemporaria before centidadeeleitores score the same,
#   302 (with DoDesconverte last); name order is kept, the data's for cdataje and ctransferenciatemporaria (records
#   @1571564, @1572300; centidadeeleitores.cpp has no data).
#
# The generated module (src/asn1/modules/ModuloEleitores.{h,cxx}) gains NecessidadeEspecial, the class RTTI names for
# EleitorUrna's necessidade, whose vptr 11411 stores in its copy, and EleitorUrna's identificacaoEleitor becomes a
# typedef of ASN1::SEQUENCE_OF<ModuloTiposEleitorais::IdentificadorEleitor>, whose vptr 11411 stores in its copy.
#
# Chosen, no evidence names them: MontaEleitorIdentidade and its being a file-local helper, GetIdentidades, CDataJE's
# GetData and its test's spelling, the names of CEleitor::ENecessidadeEspecial's enumerators, which
# ConverteNecessidadeEspecial returns (SEM_NECESSIDADE and NECESSITA_AUDIO, 0 and 1: returning casts of 0 and 1 gives
# the same object, measured), the enumerators of CTransferenciaTemporaria::ETransferenciaTemporaria (their values are
# the target's) and the code 8069 (euecomumdadoserror.h), the `case unknownEnumeration_` that throws (the target's
# table: -1 throws, 0 and unknown kinds give no transfer), every local's name, DoDesconverte's line and the blank lines,
# the helper's and the files' lines above the first record, and each file's header path (rule 4 of how-to step 3, beside
# its .cpp; md/cdataje.h in md/ as its record's .cpp is).
#
# Roots (310-uenux2-cconversorentidadeeleitores-roots.cpp): w310_visitantes stands for 5704's target caller 7787 (the
# photos' reader, not written) and w310_busca for 2805's target callers 3614, 5376 and 10451 (not written; they call the
# other maps' instances that the target's 2805 merges); each goes when its callers are in the link.
W310_SRCS := src/app/comum/dados/asn/eleitor/cconversorentidadeeleitores.cpp src/app/comum/dados/md/cdataje.cpp \
  src/app/comum/dados/md/eleitor/centidadeeleitores.cpp src/app/comum/dados/md/eleitor/ctransferenciatemporaria.cpp
UENUX2_SRCS += $(W310_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/eleitor/cconversorentidadeeleitores.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# the roots declare what they reach through __asm__ labels and include no header
$(ROOT)/$(APP)/310-uenux2-cconversorentidadeeleitores-roots.o: $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/310-uenux2-cconversorentidadeeleitores-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/310-uenux2-cconversorentidadeeleitores-roots.o
