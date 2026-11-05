# uenux2: helpers of the zerésima reports (fns 11946 and 11943, vota::CGeraZeresimaBase's and
# vota::CGeraResumoZeresimaBase's StartState, unit 169's traps), written in landed units' files and in
# app/vota/eleitor/iniciovotacao/cgeradorresumozeresima.{h,cpp} (new; unit 169's list compiles the .cpp, below); this
# fragment holds their notes and their roots. Paths relative to src/uenux2.
#
# Matched, each scored with pnpm wasm score against the whole link's names.tsv before steps 7 to 9, all operand-only:
# - api::GeraArquivoRelatorio (fn 3654, 12 over 181 rows) in api/gui/reports/creportprinter.cpp and api::CScopedReport-
#   File's constructor and destructor (records creport.cpp:31:5 and :37:9, which 3654 holds) in creport.cpp, with
#   api::CReport::ImprimePartes (5486, 0 over 27) and DoPrintJob's lambda's call operator (10884, 0 over 5), which match
#   with them: unit 317's files, whose fragment and creport.h have the evidence and why the files split so.
# - vota::CLogVota::LogaGerandoRelatorio (fn 1047, 17 over 288) in app/vota/log/clogvota.{h,cpp} (unit 119's files), with
#   comum::IEventosLog::ConverteInicioTermino (no target index) in app/comum/log/ieventoslog.{h,cpp} (unit 111's).
# - vota::CRelVotaUtil::CriaCabecalho (fn 5977, 21 over 265) in app/vota/eleitor/iniciovotacao/crelvotautil.{h,cpp}
#   (unit 246's files), and its lambda's __func slots 11999 to 12002. Its call operator is 2881, the body four lambdas
#   share, whose match line step 9 renamed to this lambda's (binaryen keeps the first twin in link order).
# - vota::CriaCabecalhoDetalheZE (fn 3873, 6 over 112) and vota::CriaDetalheCandidato (3872, 5 over 88) in
#   cgeradorresumozeresima.{h,cpp}, with the instances 3872 makes, CDataSourcesRelatorio<CRdvVota, CEleitores>'s
#   DetalheCandidatoZE and DetalheCandidato (11973, 27 over 430; 11972, 20 over 417), which that object emits now. Unit
#   183's roots, compiled with -fno-strict-aliasing, emitted them before; this file builds with strict aliasing (the
#   uenux2 rule's src/app/vota/), and the four score the same at both places measured (below).
# - comum::CRelUtil::FormRodapeZeresima (fn 5579, 33 over 279) in app/comum/relatorios/crelutil.{h,cpp} (unit 123's),
#   below ImprimeSeparadorVia (5581, 11 over 187 on the same link).
#
# Evidence and choices:
# - 1047: the text, "Gerando relatório [{}] [{}]", and ConverteERelatoriosUE (fn 5879) of the report; clogvota.h has its
#   callers' arguments. The phase's text is built in two branches of known length ("INÍCIO" for 0) through a local that
#   holds the string's address. Measured on whole links: `std::string(termino ? "TÉRMINO" : "INÍCIO")` 60 over 300 rows
#   (a select and a copy), `termino ? std::string("TÉRMINO") : std::string("INÍCIO")` 84 over 309, the text from a
#   function out of line returning that ternary 43 over 292, `if (termino) return "TÉRMINO"; return "INÍCIO";` 24 over
#   288 (the branches swapped) and `if (!termino) return "INÍCIO"; return "TÉRMINO";` 17 over 288, operand-only. Out of
#   line was measured with a noinline attribute in clogvota.cpp, then with the function in ieventoslog.cpp, another TU,
#   which gives the same 17 over 288 and no symbol of it in names.tsv (binaryen inlines it into its one caller). The
#   helper reads no state. Two forms give the same link (sha256 f84c4c82...0e76 of build/out/wasm/vota_web's wasm both
#   ways, the two variant objects swapped into the plain link.cmd): the one written, a non-static member of
#   comum::IEventosLog, and a free function of vota, the caller's namespace (reading.md R10's form for a helper that
#   reads no state). The member is kept, a choice: IEventosLog's three Converte members, which turn a value into a
#   log's text, are non-static members by their records (ieventoslog.cpp:426, :440, :456, no `static`), with `this`
#   removed by binaryen, and one of them, ConverteFonteAlim, is out of line in its object and binaryen's inline in fn
#   5875 (ieventoslog.h has both readings), as this one is in 1047. Both names, the bool and the places
#   are chosen: in clogvota.cpp after LogaEleitorSuspensoSemVoto and in clogvota.h after
#   LogaImprimindoRelatorio, apart from the lines another branch adds at both files' ends (17 over 288 at the end too).
# - 5977: the lambda's RTTI (typeinfo 1543360) names it and its class; its body is unit 317's MontaCabecalho's shape,
#   with the place read from CEstadoGeral (GetDadoLocal().GetSecaoCarga(): +20, +24, +26), the labels "Data" and
#   "Hora", GetIdentificacaoUrna by its address (table slot 1567) and no phase separator; GetGeral, Now and
#   CLocal::GetInst in the order of the target's calls. The result's type is spelled std::shared_ptr<api::IForm<
#   api::IPaper>>: fn 5971's record names it api::SharedPaperForm, which no header of ours declares (a typedef of that
#   type, a reading).
# - 3873 and 3872: forms of one field from a data source's address (table slot 1634, and 1636 or 1635 by the argument,
#   which fn 11946 passes as 0 and fn 12110 as 1). Their file is the data's: the link keeps a linkonce copy from the
#   first object that emits it, and DetalheCandidatoZE's record (cdatasourcesrelatorio.h:152, fn 11973), whose one
#   user is 3872, lies at @1544048, after cgeradorresumozeresima.cpp's records (:43 and :47, @1543752 and @1543768) with
#   only header records between, while crelvotautil.cpp's data (api::CSubReport's vtable @1543172, its two lambdas'
#   __func vtables @1543232 and @1543296) end before vota::CDefineRotaPreVotacao's vtable (@1543448). Use band 3 agrees,
#   a reading: 3874, CSubReport::GetTitulo, a slot of that linkonce vtable, which crelvotautil.cpp's object emits after
#   both of its functions (ld_index 5216 against CortaPapel's 5212 and CriaCabecalho's 5214; reading.md R9, a function
#   only a vtable references), comes before 3873 and 3872; but the target's 3874 is one body for four vtables'
#   slots (CSubReport's, CSha's and CSha512's, __func<api::QRCodeSRC>'s), so its band place is the kept copy's, read as
#   crelvotautil.cpp's (uenux2's objects link ahead of ecourna's security ones, link-order.md L3, and the QRCodeSRC
#   vtable lies later in the data). Their names, the bool,
#   their being free functions of vota (no class evidence: how-to step 3, "Names no evidence gives"; the file's records
#   are vota::(anonymous namespace)'s) and their linkage, external (the file's one recorded function is internal, and no
#   record, slot or caller shows theirs: how-to step 3, "What a record's place says") are chosen, their order (3873
#   above 3872) the band's, and their lines (56 to 71, below the records' lines of the unwritten CriaTituloExtratoRDV,
#   which stay blank) chosen.
# - The file's place in the link: unit 169's list compiles it right after cinformacaozeresimatardia.cpp and ahead of
#   cgerazeresimabase.cpp, the data's order (cinformacaozeresimatardia.cpp's records @1543692 and @1543708, this file's,
#   then CGeraZeresimaBase's vtable @1544384), where both places measured give the four the same scores
#   (docs/reference/facts/codegen.md C4). The other place, this fragment's list (after unit 32's csystem.cpp), leaves
#   more pairs of the four against the rest of their bands out of order (higher index, higher ld_index; how-to step 3,
#   "The order of two members"): 6874 in band 1 and 1040 in band 3, against 6332 and 954 here. Inside the object the
#   four keep their bands' order (ld_index 4585, 4586 for 3873, 3872; 4587, 4588 for 11973, 11972), and
#   crelvotautil.cpp's object keeps its own. Out of order across objects, among the iniciovotacao objects' matched
#   members: in band 1, 11973 and 11972 each against crelvotautil.cpp.o's 11999 to 12014, cdefinerotaprevotacao.cpp.o's
#   11994 to 11996 and ciniciovotacao.cpp.o's 11987 to 11990, which the data put ahead of this object and our link
#   after unit 169's list, and ciniciozeresima.cpp.o's 11924 to 11926 and creiniciocomparecimentomesario.cpp.o's 11917
#   to 11919, which band 1 puts after it and our link ahead: 58 pairs; in band 3, 3873 and 3872 each against
#   crelvotautil.cpp.o's 3874, ciniciozeresima.cpp.o's 3865 and creiniciocomparecimentomesario.cpp.o's 3864: 6 pairs.
# - 5579: use band 2 puts it after ImprimeSeparadorVia (5581) in crelutil.cpp's object and before 5578 (the sort's
#   __sort5), with 5580 (not written) between 5581 and 5579, so a static member of CRelUtil (whose records read
#   `static`) defined below ImprimeSeparadorVia: ImprimeSeparadorVia on lines 348 to 353, right after
#   ImprimeSeparadorFase, FormRodapeZeresima on 389 to 408, right above DSCodigoVerificador (410, record 412:27), the
#   lines between them blank for 5580; those lines are chosen. ld_index 3255 and 3256. In band 2 it leaves three pairs
#   out of order, against the linkonce copies 5593, 5594 and 5595, which 5581 to 5584 have too (placing.md P9), and none
#   against the object's other band-2 members (5577, 5578, 5581 to 5584, 5597). CConfiguracaoEleicao's +200, its second
#   argument at both callers, is
#   GetParametrosUrna().GetRodapeZEVOTA()
#   (measured: the address a probe object computes), and the correspondence's +28 its GetCodigoCarga(). ImprimeTitulos
#   is called as the two-argument overload, which clang inlines into the three-argument call the target makes (3689,
#   with the UF). Its name and parameters' types are chosen. The include of api/util/cstringutils.h takes one blank line
#   of the gap after `namespace comum {`.
#
# Roots: 325-uenux2-geradores-zeresima-roots.cpp stands for the target callers not written: 11943, 11946, 12105 and
# 12110 for 1047; 11943 and 11946 for 5977 and 5579; 11946 and 12110 for 3873 and 3872. Stand-ins of other units whose
# every caller is now in the link went: unit 111's w111_relatorio (for 1047; 1127 is matched), unit 230's w230_titulos
# (for 5579) and unit 183's two address sinks (for 3872). Those of units 89, 123, 196 and 317 keep callers that still
# wait, and their comments name the ones now in the link.
#
# Not written, with what each waits for:
# - 11946 and 11943 call fn 5971 (the RDV extract's parts; records iniciovotacao/cgeradorresumozeresima.cpp:43 and :47
#   of its internal CriaTituloExtratoRDV, blank lines of that file), which takes the address of 11981 (table slot 1625)
#   and, through 5970, of 11980 (slot 1626), cdatasourcesrelatorio.h's TrailerProporcional and TrailerMajoritario (2762
#   and 2326 bytes), and calls 5580 and 3699; none of them is written. 11946 also stores 11976's slot (1631) in a
#   std::function<bool()> (__func slots 11953 to 11957).
# - 3871 with 11980, 11981 and its lambda's slots 11966 to 11970; 11975; 12105 and its helpers: not attempted.
#
# nothing in the skeleton gives these functions their target's call sites: the roots stand for those callers, through
# asm labels, so the rule needs no header
$(ROOT)/$(APP)/325-uenux2-geradores-zeresima-roots.o: $(ROOT)/src/units/325-uenux2-geradores-zeresima-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/325-uenux2-geradores-zeresima.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/325-uenux2-geradores-zeresima-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/325-uenux2-geradores-zeresima-roots.o
