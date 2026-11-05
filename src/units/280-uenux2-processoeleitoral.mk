# uenux2 comum's load of the processo eleitoral: comum::CarregaProcessoEleitoral (target fn 3771) and CarregaPleito
# (5778) in app/comum/dados/carregaprocessoeleitoral.{h,cpp}, the ASN.1 file reader they instantiate,
# comum::CarregaArquivo<CONVERSOR> (app/comum/dados/carregaarquivo.{h,cpp}; its CConversorCabecalhoPacote instance is fn
# 5706, and its CConversorImpedido instance the reader fn 11517 holds; with comum::CLeitorASN::LeBiometriaEleitor beside
# it, below), the same reader for an ecourna converter, comum::CarregaArquivoEcourna<CONVERSOR> (its
# ecourna::app::dados::asn::CConversorInformacaoMidia instance is fn 3735), and comum::SIdentificacaoArquivo's
# constructor (5726, app/comum/nomearquivo/sidentificacaoarquivo.cpp; the struct is unit 279's, in cnomearquivo.h, one
# type for the object both units read). The members this load needs in files landed units compile are those units'
# (their fragments say what each holds): CPE::Existe and CreateInst (2788, 2787; unit 110), CPleito's constructor (5652;
# unit 88), CProcessoEleitoral's two constructors (unit 88), CProcessoEleitoralDTO::GetPleito2 and its getters (unit
# 140), api::TrocaExtensao (5461; unit 32), and the name builder NomeArquivoPE in app/comum/nomearquivo/cnomearquivo.cpp
# (unit 131's file; it has no index). Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and
# every uenux2 header, and these objects get Boost's include path, which cfileasn.h's converters reach.
#
# What the target shows, and what is chosen:
# - 3771's wasm type is (i32 i32)->(): the result and the general state; the origin is folded (below). It calls
#   CPath::GetPathEstatico in a 16-byte frame, then holds the rest behind a 272-byte prologue of its own
#   (LeProcessoEleitoral, binaryen's inlining of a function with one caller), which holds NomeArquivoPE behind a 96-byte
#   one (the phase's letter and the 5-digit id from cnomearquivo.cpp's internal FormataFase and FormataNumero, fns 2828
#   and 1161, which only that file's code can call: docs/reference/facts/placing.md P2), the
#   reader of the "cp" file behind a 64-byte one (CarregaArquivo<CConversorProcessoEleitoral>), GetPleito2 behind a
#   16-byte one (record cprocessoeleitoraldto.cpp:57), CarregaPleito's two calls (5778), the UF upper-cased byte by
#   byte, and the two CProcessoEleitoral constructors of its two branches, whose moved-from identifiers vector it tests
#   and frees (how-to step 3: the constructors are out of line in another TU).
# - 5778 holds CarregaArquivo for the "ste" and "ce" files behind 64-byte prologues, calls 5706 for the ".pid" file,
#   5461 for that file's name, vector<CEleicaoPE>::push_back (5777) and CPleito's constructor (5652). Its path from the
#   ".pid" name is built from a named string: the target copies it into the path (basic_string's append of a range),
#   where a temporary would be moved; 3771's "cp" name is built the same way.
# - 5726 stores the phase at +0, the id at +4, CStringUtils::ToLower of the UF (fn 1879) at +8 and the pleito's address
#   at +20, and returns this: 7787 builds one at CConfiguracaoEleicao+620 (and reads the result), 2787 at CPE+180.
#   2787 keeps it a call, which clang would inline from its own TU: so another TU, a reading. The struct (unit 279's
#   SIdentificacaoArquivo, whose header says what of it is evidence), its name, its members' names, the
#   constructor's file and its place are chosen; in use band 2 it lies between fns 5727 and 5725, which have no record
#   either.
# - CarregaArquivo's form (a converter on the stack, CFileASN::ReadFromFile<TEntidade>, Desconverte), its name, its file,
#   its being a template over the converter and the order of the explicit instantiations are chosen; the target holds
#   the ReadFromFile instances it calls (records cfileasn.h:78) inline in each instance.
# - carregaarquivo.cpp stands for one object of the target, its entity readers': the data from 1562844 to 1565964 hold,
#   entity by entity, the typeinfo, the records of CFileASN's readers (cfileasn.h:78, :48 and :60, :135 and :143), the
#   vtable and IConversorASN's Desconverte record for 19 entities, this file's instances among them (ProcessoEleitoral's
#   @1563464, SituacoesEleicoes' @1563608, Eleicao's @1563740, CabecalhoPacote's @1565368), and no .cpp record (`awk
#   -F'\t' 'NR>1 && $1>=1562844 && $1<=1565964 {print $1, $2, $3, $6}' ledger/source-locations.tsv`: 109 records, none
#   a .cpp's), so one TU (docs/reference/facts/link-order.md L7 item 15). Among them lie legravaentidade.h's records of
#   LeEntidadeBiometria (@1564660, @1564676), a template of an anonymous namespace, which only the TU that instantiates
#   it emits: so comum::CLeitorASN::LeBiometriaEleitor (app/comum/asn/cleitorasn.h), which instantiates it and which
#   target fn 1937 (comum::CEleitorDetalhe::GetBiometria) holds behind a frame of its own, is defined here, between the
#   EleicaoPE and CabecalhoPacote instances as the run orders their records (@1563740, @1564660, @1565368). It has no
#   index of its own; unit 98's fragment has its class's and its name's evidence, its forms and their scores. With it,
#   each other function of this object is the same with the object-local numbers masked, and 5706, 3771 and 5778 score
#   as below. Chosen: this file's name and path, which no record gives. Four more of the run's readers are here, each
#   where the run orders its records:
#   - ModuloImpedidos::EntidadeImpedidos' (records @1564800 to @1564916, after LeEntidadeBiometria's and before the
#     FotosCandidatos reader's, fn 7787's): CarregaArquivo<asn::CConversorImpedido>, which the lambda of
#     CEleitores::GetEleitoresImpedidos (unit 110's celeitores.cpp) calls, and which binaryen inlines into the lambda's
#     call operator, fn 11517, which opens with this instance's 64-byte frame (the converter's vptr at +60) as 3735
#     does. With the read in the lambda itself, as before, 11517 scored 169 over 1604 rows with 35 rows of local
#     numbers (locals 5 and 6 swapped); from here, 134 over 1604, every differing operand a call, a data address, a
#     packed format string or a table slot (pnpm wasm score in this unit's link, before step 8).
#   - ModuloInformacaoMidia::InformacaoMidia's (records @1565512 to @1565628, after CabecalhoPacote's, the run's last
#     reader): CarregaArquivoEcourna<CConversorInformacaoMidia>, fn 3735, which stores the converter's vptr in a 64-byte
#     frame of its own and calls ecourna's Deconverte (record iconversorasn.hpp:66); its callers are the recorders
#     11587 (unit 305), 11626 (unit 160) and 11629 (unit 200). After its records the run holds
#     ModuloTiposEcoUrna::Carga's vtable and typeinfo and IConversorASN<IdentificadorGeradorMidia, ...>'s Converte and
#     Deconverte records (fns 3734 and 3733, matched from other objects): code of this object no function here
#     accounts for, not identified.
#   - ModuloEleitores::EntidadeEleitores' partial reader (the data from the visitor's control block's vtable @1564316
#     through the records @1564368 to @1564608, after the Candidatos reader's, fn 7787's, and before
#     LeBiometriaEleitor's, CFileSeeder's vtable, records and control block among them): LeEleitores over the CarregaArquivoParcial pair, which fn 11523 (the lambda of
#     CEleitores::GetEleitoresEstaticos, unit 110's celeitores.cpp) holds behind an 80-byte frame of its own;
#     src/units/310-uenux2-cconversorentidadeeleitores.mk has its evidence and forms. From this object match 5704 and
#     5703 (the visitors' vector's __assign_with_size and copy loop) and the members of CFileSeeder (unit 83) and of
#     the two control blocks (11427, 11435: unit 102), which this object now emits.
#   - ModuloLocal::Local's (records @1563320 to @1563436, after ModuloFederacoes' and before ProcessoEleitoral's):
#     CarregaArquivo<asn::CConversorLocal>, first among the explicit instantiations as the run orders it, which
#     comum::CLocal::Carrega (fn 5740, unit 89's clocal.cpp) holds behind its 64-byte frame (the converter's vptr at
#     +60), the md::CLocal it returns built in the memory Carrega allocates first. 5740 matches; unit 89's fragment has
#     the order of the two objects it needed.
#   The run's other readers are not written.
# Every name above but the records' (CPE::CreateInst, GetPleito2, the cfileasn.h template) is chosen, and so are the
# functions' being free functions of comum (they read no class's state), their lines and these paths;
# CarregaArquivoEcourna's being a second template beside CarregaArquivo (ecourna's converters name the member
# Deconverte) is chosen too.
#
# Matched: 5706 (114 over 1366 rows before step 8, all operand-only: calls, the table slots of the format buffer and the
# thrown object's destructor, the packed std::format strings), 5726 (1 over 17), std::vector<CEleicaoPE>::push_back
# (5777, 13 over 420, from carregaprocessoeleitoral.cpp.o), 3735 (126 over 1432, all operand-only, the same kinds as
# 5706's; the first form written) and 5778 (349 over 4644 rows before step 8, all operand-only: calls, data addresses,
# the thrown errors' destructor slots and the packed std::format strings), with CPleito's constructor (5652, unit 88)
# and comum::asn::CConversorEleicaoPE's default constructor out of line in cconversoreleicaope.cpp (unit 299's file; no
# record names it, and binaryen inlines it into 5778). The evidence for that constructor: in the "ce" reader, inside
# CarregaPleito's loop, the target keeps the converter's address (+60 of the 64-byte frame) in a local from its vptr
# store on, stored at offset 0, and passes that local to DoDesconverte, where its "ste" reader and the readers of 3771
# and 5706 store the vptr at offset 60 and compute the address again where they pass it; with the constructor implicit,
# as the other converters', 5778 scored 461 over 4649 rows (451 operand-only, 5 inserted, 4 deleted), those rows. That
# such code is binaryen's inlining of a call that takes the converter as `this` is a reading; unit 299's
# CConversorCargo constructor is out of line on a like sign. Defined `= default` or `{}`, it gives the same object (the
# two objects are cmp-equal). Chosen: the constructor's declaration, its file and its place there.
# Written and not matched:
# - 3771: 1126 over 3025 rows (1019 operand-only, 51 inserted, 56 deleted); the rows left are local numbers and the
#   order of a few operands, the place of the general state's UF above all (ours computes it before the inner frame, the
#   target where it reads it). Its scan row is `differs` on a local's number (+0x13); it read `unresolved` on its call
#   of 5778 until 5778 matched. A `callers+content` hand line in splat/symbol_addrs.txt names it from the seven
#   std::source_location records only it loads (cfileasn.h's ReadFromFile and DecodeObjectFunction for
#   EntidadeProcessoEleitoral, IConversorASN's Desconverte,
#   GetPleito2's), which ours loads too: with it CPE::CreateInst (2787, unit 110) matches, without it 2787 is
#   `unresolved self-voted` on this call.
# Measured forms (same command, each against the whole link with the other functions as written):
# - 3771 with LeProcessoEleitoral taking the general state in place of the UF and reading its UF where it is first
#   passed, with fase and idPE still its arguments: 989 over 3020 rows (46 inserted, 52 deleted). The UF's address is
#   then computed where the first CarregaPleito call passes it, as the target does, but the upper-casing loop reads the
#   UF through the state (offsets 12, 19 and 8), where the target reads it through that address (4, 11 and 0), as the
#   UF parameter gives. With the local numbers masked, what is left beside that is: our copy of the result's address at
#   the top, where the target copies it before the first CarregaPleito call; two locals the target zeroes before
#   ReadFromFile(const CFile&)'s 528-byte frame (no loop holds it there), ours none; the order of two operands at
#   ReadFromFile(const std::string&)'s 480-byte epilogue; and the pleito-2 test, an `i32.eq` with 1 on the optional's
#   flag in the target, a test of the byte in ours (`dto.TemPleito2() == true` gives the same object as ours). Not
#   explained, so the UF parameter stays.
# - 3771 with LeProcessoEleitoral taking the general state alone and reading fase, idPE and the UF itself: 1005 over
#   3024 (50, 56): fase's and idPE's loads come after its 272-byte prologue, where the target has them before it.
# - The ".pid" and "cp" names as named strings: with each a temporary of the path's operator/ (moved into the path),
#   5778 scored 728 over 4676 rows (32 inserted, 48 deleted) and 3771 1399 over 3105 (131 and 153).
# - 3771's origin is folded: its wasm type has no such parameter, and it passes the constant 0, FLASH_INTERNA, to
#   CPath::GetPathEstatico (dead-argument elimination over its callers, 2787 and 7787); ours, 2787 (through
#   CRelatorioTesteImpressora's constructor) and the roots' stand-in, pass FLASH_INTERNA too, and ours folds it alike.
#
# Roots (280-uenux2-processoeleitoral-roots.cpp): stand-ins for the target callers not reconstructed, each named in its
# comment, so that each function keeps the call sites the target gives it, and the constructors' results are read where
# a target caller reads them: 2787 and 3771 drop the returned this of CPleito's copy constructor (1281) and 2787 that of
# SIdentificacaoArquivo's (5726), while 1543, 5967, 7787 and 11902 read 1281's (1543 and 11902 are in the link now, unit 123's and 176's), 7787 reads 5726's, and 11869 and 11911
# read CRelatorioTesteImpressora's (5586; 11911 is written now, unit 296's, and reads it). Without a reader binaryen
# drops the result: 1281 scored 9 over 215 rows, 5726 3 over 17 and 5586 11 over 99, each with the target's result row
# deleted; with the readers, 7, 1 and 9, all operand-only. libc++'s vector<CEleicaoPE>::push_back and the version map's
# __find_equal are called through __asm__ labels with the objects' signatures (wasm-objdump -x), so this file
# instantiates neither: with one caller each, binaryen inlined push_back into CarregaPleito (no body for 5777) and
# __find_equal into the hinted insert (3870 scored 270 over 345, 244 inserted); with the stand-ins 3870 scores 2 over
# 101, 3869 0 over 246, 5777 13 over 420. The stand-ins for 3752 and 5738 (unit 89; 5738's went once its other caller, 1543, was in the link) and the 5586 readers are here
# because this unit's chain needs them; unit 123's vtable sink went when 5586 was written, and w280_informacao, which
# stood for 3735's caller 11629, when unit 200 wrote it (3735's callers 11587, 11626 and 11629 are all in the link). A
# stand-in goes when every target caller its comment names is in the link.
# carregaarquivo.cpp, this unit's file, is compiled in unit 89's list, after clocal.cpp: 5740 needs clocal.cpp's object
# ahead of it (unit 89's fragment has the measurement). Its include paths stay here.
PROCESSOELEITORAL_280_SRCS := src/app/comum/dados/carregaprocessoeleitoral.cpp \
  src/app/comum/nomearquivo/sidentificacaoarquivo.cpp
UENUX2_SRCS += $(PROCESSOELEITORAL_280_SRCS)
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(PROCESSOELEITORAL_280_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/carregaarquivo.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# ecourna's converter headers, which carregaarquivo.cpp includes for CarregaArquivoEcourna's instance, include the
# generated ASN.1 modules by their bare names
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/carregaarquivo.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/carregaarquivo.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
W280_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/280-uenux2-processoeleitoral-roots.o: $(ROOT)/src/units/280-uenux2-processoeleitoral-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/280-uenux2-processoeleitoral.mk $(W280_HDRS) $(wildcard $(ROOT)/src/asn1/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -Isrc/asn1/modules -c src/units/280-uenux2-processoeleitoral-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/280-uenux2-processoeleitoral-roots.o
