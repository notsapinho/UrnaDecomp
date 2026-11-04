# uenux2: the reports' lines of the voters able to vote and the voters' list report. comum::CEleitoresAptos in
# src/app/comum/relatorios/celeitoresaptos.{h,cpp}; api::CReport in src/api/gui/reports/creport.{h,cpp} (creport.cpp
# was a stub-only file); the voters' list in src/app/comum/relatorios/cgeradorrellistaeleitores.{h,cpp} (a stub-only
# file until now), whose one user is vota::CImpressaoListaEleitores::StartState (target fn 11908), unit 176's, written
# with it. Paths relative to src/uenux2. Unit 287's CGeradorRelVersaoPacoteDados::ImprimeTituloJE (11223) is written
# with this unit in that unit's file, over CEleitores::QuantidadeAptos returning comum::SQtdeAptos (unit 110's
# celeitores.h, 2823; the RTTI of four std::function<comum::SQtdeAptos()> whose call operator is 2881 says so).
#
# Matched: CEleitoresAptos's constructor (1922) and Formata (1921); the call operator four lambdas share (2881) and the
# __func slots of ImprimeTituloJE's lambda (11217, 11218, 11219, 11221) and of MontaCabecalho's (11229 to 11232); 11223;
# CReport's constructor (2259); DoPrintJob's lambda's slots 10882, 10883, 10885 and 10886; CabecalhoEleitores (11234).
# Scores before steps 7 to 9 (pnpm wasm score against this link's names.tsv): 1922 0 over 39 rows and 2259 0 over 27
# (byte-exact), 1921 27 over 592, 11223 81 over 945, 11234 13 over 356, the slots 1 or 2 rows each, all operand-only.
#
# Written, not matched:
# - 11908 (vota::CImpressaoListaEleitores::StartState, with ImprimeListaEleitores, MontaCabecalho and the other parts'
#   builders, CReport::Imprime with DoPrintJob and CParteEleitores's constructor held inlined): 242 over 2056 rows, 7
#   inserted and 7 deleted, every one a local.get/set/tee whose index the target and ours permute (the five parts'
#   pointers and control blocks: the target's part 2 is locals 11 and 12, ours 10 and 14). The target stores
#   CParteEleitores's member through its control block (+16, +20), ours through the object (+4, +8 of ctrl + 12). Not
#   explained. Measured, each on a whole link: creport.cpp before or after cgeradorrellistaeleitores.cpp in this list
#   (the same 242); cgeradorrellistaeleitores.cpp ahead of unit 77's cparteeleitores.cpp (the same); with unit 176's
#   cimpressaolistaeleitores.cpp ahead of both too, 262 over 2057; CParteEleitores's constructor defined in its class,
#   221 over 2053 with the constructor's 16-byte frame gone, which the target keeps (a second prologue in 11908). It stays
#   written: it brings matches only it calls (11234, the slots of MontaCabecalho's and DoPrintJob's lambdas).
# - 11233, SituacaoEleitor (record cgeradorrellistaeleitores.cpp:100:15, its throw, EUE_COMUM_RELATORIOS_9068 and the
#   target's message): 42 over 565, one row inserted, the test of the voter's biometry flag (+100): the target tests the
#   byte as nonzero, `i32.eqz`, where md::CEleitor::TemBiometria, defined in its class, gives `i32.const 1; i32.ne`
#   (docs/reference/facts/reading.md R14) in this function under every form tried (the flag read through a local or
#   GetEleitor(), the vector declared first, `!detalhe`, `== true`: wasm-objdump -d of each object). With TemBiometria
#   defined out of line in md/eleitor/celeitor.cpp (binaryen inlines its two-instruction body at every call: names.tsv
#   holds no TemBiometria) 11233 scored 40 over 564, all operand-only, and steps 7 to 9 matched it with no row of the
#   base leaving match. celeitor.{h,cpp} is another stage's claim for that same change, so 11233 waits for it.
# - 10884, DoPrintJob's lambda's call operator: the target calls 5486, CReport::ImprimePartes, which clang inlines into
#   it here (24 rows inserted); 5486 has no body of ours. Not explained. 5486's other target caller is fn 3654 (the
#   records creport.cpp:31 and :37 of api::CScopedReportFile, not written); a body clang sees in the lambda's TU is
#   inlined whatever its callers (a reading), so the target's may be defined in another TU.
#
# Evidence and choices:
# - CEleitoresAptos (no record, slot or RTTI names the class or its members; celeitoresaptos.h has the reading): the
#   six target callers of 1921 and 1922 (3871, 5977, 11223, 11908, 12105, 12110) each build a std::function from a
#   lambda (one __func's RTTI per caller); the three read (3871, 11223, 11908) call 1922 on a 20-byte object with it,
#   call 1921 on that object and destroy both; 1922 returns its first argument, a
#   constructor, and libc++'s std::function copy, its body, is inlined where clang sees it (cost 40, threshold 250, in
#   cgeradorrelversaopacotedados.cpp's object with -Rpass=inline; cost 50 with the source a reference parameter, a probe
#   object), so it is defined in another TU than every caller (a reading). The parameter is a std::function by value: in
#   11223 the "Hora" temporary of CRelUtil::ImprimeDataHora shares the frame slot of 1921's result, where with a const
#   reference it took the std::function temporary's (docs/reference/facts/codegen.md C10). The class, its name, Formata's
#   name and const, the members' names, the header's path and the file's name are chosen. The file's place: in use band
#   6, 1922 and 1921 lie between ccargo.cpp's 1923 and cgeradorbuqrcode.cpp's 1920 (its __sort4 over GetCamposConsulta's
#   local lambda, which only that TU instantiates), so the object links there (rule 2 of how-to step 3);
#   app/comum/relatorios/ is the directory of 1920's object and of the report callers, and the file's name sorts before
#   cgeradorbuqrcode.cpp, as that directory's data run in name order: a choice within the window. The constructor is
#   defined first (1922 above 1921 in the band; ld_index 6111 and 6112).
# - ImprimeTituloJE (unit 287's class header has the slot): CGeradorRelPU::ImprimeTituloJE's shape (unit 183), with the
#   aptos lines when the urna is no contingency's and a new line otherwise, and the process and pleito codes, "{:<32s}
#   {:05}" of CPE's GetID, GetPleito1().GetID() and, when TemPleito2, GetPleito2().GetID(), in a frame of their own (400
#   bytes: binaryen inlined a function of its own). That function takes the builder, not the object: the target passes
#   this + 4 to it (a member over m_builder took a local more). Its name, ImprimeCodigosProcessoEleitoral, its being a
#   free function of comum in cgeradorrelversaopacotedados.cpp (external: clang keeps it out of line) and its place below
#   ImprimeTituloJE are chosen; that place is measured: above its caller 11223 scored 377 over 966 rows (21 inserted, 21
#   deleted, local numbers), below it 81 over 945, operand-only (docs/reference/facts/codegen.md C4).
# - CReport (creport.h has the class's evidence): the constructor in creport.cpp, below the records' lines 31 and 37
#   (api::CScopedReportFile's, held by 3654, not written), which stay blank; Imprime and ImprimePartes after it, their
#   names chosen. DoPrintJob is the RTTI's (`api::(anonymous namespace)::DoPrintJob(api::CReport const&, std::string
#   const&, std::string const&)`); in 11908 its frame copies the two strings for CSubReport's by-value parameters and
#   frees the copies before CLp::Imprime, so the sub-report is a named local.
# - The voters' list (cgeradorrellistaeleitores.{h,cpp}): MontaCabecalho is the lambda's RTTI's; SituacaoEleitor the
#   record's; the other helpers' names (MontaTitulos, MontaEleitores, MontaLegenda, MontaRodape, CabecalhoEleitores),
#   ImprimeListaEleitores's name and its being a free function of comum, TITULO's name and every line but 100 are chosen.
#   Evidence: 11908's 144-byte frame builds five parts, each with a builder of its own freed right after the part is
#   made, into a CReport from an initializer list (the five copies' counts raised, the five temporaries released after
#   2259 returns), so each part is a function's result in one full-expression; the third is std::make_shared of
#   comum::CParteEleitores (vptr 1576212), the others of api::CFormPart. The title "Lista de eleitores" is a named char
#   array: the target holds it at 518848, among this object's typeinfo names (MontaCabecalho's lambda's at 518867), not
#   in the string pool, and loads it with align=3 and align=1, where a literal gives align=0 (measured: 245 over 2056
#   rows against 242). The columns' padding is a named string: as a temporary, `+` takes the overload that calls
#   insert, where the target concatenates two lvalues inline (11234 152 over 370 rows against 13 over 356; 11233 185
#   against 42). CabecalhoEleitores reads the principal identifier's type before it declares its string (the target's
#   order of the call and the stores). The legend's separator is unit 168's vota::AdicionaSeparador (fn 1387), whose
#   namespace is that unit's choice, called from this comum file.
#
# Roots: 317-uenux2-relatorios-aptos-roots.cpp stands for 1921's and 1922's callers 3871, 5977, 12105 and 12110 (11223
# and 11908 are in the link) and for 2259's callers 7787, 11943, 11946 and 12105 (11908 is in the link). Unit 57's and
# unit 219's roots, unit 77's CParteEleitores stand-in and unit 280's w280_cpe, which stood for 11908 or 11223 alone,
# went with this unit, and unit 176's and 287's pending files with their last traps (11908, 11223).
RELATORIOS_APTOS_SRCS := src/api/gui/reports/creport.cpp src/app/comum/relatorios/celeitoresaptos.cpp \
    src/app/comum/relatorios/cgeradorrellistaeleitores.cpp
UENUX2_SRCS += $(RELATORIOS_APTOS_SRCS)
# cgeradorrellistaeleitores.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost's headers, and
# UENUX2_CXXFLAGS has no path to them. An include path is not a flag of the code (asmlift-wasm/benchmark/README.md "The
# compile setups").
$(ROOT)/$(APP)/uenux2/src/app/comum/relatorios/cgeradorrellistaeleitores.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing in the skeleton gives these functions their target's call sites: the roots stand for those callers, through
# asm labels, so the rule needs no header
$(ROOT)/$(APP)/317-uenux2-relatorios-aptos-roots.o: $(ROOT)/src/units/317-uenux2-relatorios-aptos-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/317-uenux2-relatorios-aptos.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/317-uenux2-relatorios-aptos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/317-uenux2-relatorios-aptos-roots.o
