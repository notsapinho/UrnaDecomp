# uenux2 comum::asn::CConversorEntidadeEleitores (app/comum/dados/asn/eleitor/cconversorentidadeeleitores.h, beside the
# .cpp its records name), the entity it converts to, comum::md::CEntidadeEleitores (md/eleitor/centidadeeleitores.h),
# and the partial ASN.1 reader the lambda of CEleitores::GetEleitoresEstaticos (unit 110's celeitores.cpp) calls through
# LeEleitores (unit 280's carregaarquivo.cpp): api::CPartialFileASN (api/io/asn/cpartialfileasn.h, unit 83's header),
# comum::asn::IConversorParcialASN::Desconverte (app/comum/asn/iconversorparcialasn.h), ASN1::CoderEnv's setVisitors and
# getLog and ASN1's TVectorAbstractVisitor and TSharedSeeder (src/asn1/asn1.h), and comum::asn::CVisitanteEleitor's
# constructor and Prepara (unit 225's files). Paths relative to src/uenux2. The unit's own objects are its pending and
# roots files: every function of the chain is compiled in the objects of units 110, 280, 225 and 91, whose fragments
# point here.
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
# Not reconstructed: CConversorEntidadeEleitores::DoDesconverte (slot 2, target fn 11411, 7299 B), a trap in
# 310-uenux2-cconversorentidadeeleitores-pending.cpp, whose header says what the target's body holds; it is the class's
# key function, so the pending object emits the vtable. cconversorentidadeeleitores.cpp is a stub-only file until then,
# and step 9 removes it while the trap holds the slot (src/units/README.md "Pending members").
#
# Roots (310-uenux2-cconversorentidadeeleitores-roots.cpp): w310_visitantes stands for 5704's target caller 7787 (the
# photos' reader, not written); it goes when 7787 is in the link.
W310_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
$(ROOT)/$(APP)/310-uenux2-cconversorentidadeeleitores-pending.o: $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores.mk $(W310_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/comum/dados/asn/eleitor/cconversorentidadeeleitores.cpp) -c src/units/310-uenux2-cconversorentidadeeleitores-pending.cpp -o $(R)
# the roots declare what they reach through __asm__ labels and include no header
$(ROOT)/$(APP)/310-uenux2-cconversorentidadeeleitores-roots.o: $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/310-uenux2-cconversorentidadeeleitores.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/310-uenux2-cconversorentidadeeleitores-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/310-uenux2-cconversorentidadeeleitores-pending.o $(APP)/310-uenux2-cconversorentidadeeleitores-roots.o
