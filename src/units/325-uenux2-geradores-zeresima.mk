# uenux2: helpers of the zerésima reports (fns 11946 and 11943, vota::CGeraZeresimaBase's and
# vota::CGeraResumoZeresimaBase's StartState; 11943 is written since, 11946 is unit 169's trap), and 11943, written in
# landed units' files and in
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
# Matched since, each scored with pnpm wasm score against the whole link's names.tsv before steps 7 to 9, all
# operand-only (calls, data, and two table slots of matched functions: 7324, the format buffer's __prepare_write, and
# the assert error's destructor):
# - vota::CriaPartesExtratoRDV (fn 5971, 85 over 1132 rows) in cgeradorresumozeresima.cpp, over the file's internal
#   CriaTituloExtratoRDV, whose records are the file's two (:43:94 and :47:100, codes 3479 and 3480 of
#   api/util/eueasserterror.h) and which clang inlines into it (one frame: its builder is at +200 of 5971's), and
#   vota::(anonymous namespace)::CriaTrailerMajoritario (5970, 5 over 88), which 5971 calls twice (its
#   CriaTrailerProporcional, called once, is inlined). 5971 returns {CFormPart(the title), CParteCargos(CFormPart(5580's
#   form), CParteRdv(CFormPart(3699's form), CFormPart(5970's), CFormPart(the proportional trailer's),
#   CFormPart(5970's), CFormPart(an empty form)))}. Two parts of the title, vota::ImprimeAvisoSemVotos and
#   ImprimeTituloExtratoRDV (no index: 5971 holds each behind a frame of its own), are in unit 169's
#   cgerazeresimabase.cpp, measured: in votadefs.cpp, whose object links ahead of 5971's, 5971 scores 155 over 1141 (9
#   inserted, 9 deleted, local numbers in the two helpers); in a scratch link of the same objects with votadefs.cpp.o
#   moved after cgeradorresumozeresima.cpp.o, 85 over 1132 (docs/reference/facts/codegen.md C4). cgerazeresimabase.cpp's
#   object is the one after 5971's in the data (vota::CGeraZeresimaBase's vtable @1544384) and in our link; the file,
#   the two names and their being free functions of vota (they read no state) are chosen. The two functions' names,
#   CriaPartesExtratoRDV's and the trailers', are chosen; the title's is its records'.
# - CDataSourcesRelatorio<CRdvVota, CEleitores>'s TrailerProporcional (fn 11981, 65 over 1242) and TrailerMajoritario
#   (11980, 56 over 1054) at their records' lines (241 and 305), and GetLinhasEleitoresAptos (3871, 4 over 104) with its
#   lambda's call operator (11968, record 212, 22 over 294) and that lambda's __func slots 11966, 11967, 11969 and
#   11970, in cdatasourcesrelatorio.h; cgeradorresumozeresima.cpp's object emits them (5970 and 5971 take the trailers'
#   addresses, table slots 1626 and 1625).
# - comum::CriaTituloCargo (fn 3699, 6 over 112) in unit 139's cgeradorbu.cpp, above the destructor, over
#   AddTextField<CPadDS<...>> (5613) and the inline constructors of app/comum/dados/ccargods.h. In use band 3 it lies
#   between CCalculaCV::CalculaCodigo (3700, ccalculacv.cpp) and CGeradorBU's D2 (3698, cgeradorbu.cpp), the end of the
#   one object or the start of the other; no record names either, and cgeradorbu.cpp, the BU report's file, is chosen.
# - comum::CRelUtil::FormCabecalhoEleicao (fn 5580, 11 over 184) in unit 123's crelutil.cpp, between ImprimeSeparadorVia
#   (5581) and FormRodapeZeresima (5579), use band 2's order. The two lines of 38 '=' come from the file's internal
#   ImprimeLinhaIgual, which clang inlines into both calls: written in place, the strings' temporaries take +8 and the
#   builder +20 of the 32-byte frame (33 over 184, the frame rows), where the target has the builder at +8 and the
#   strings at +20, the helper's frame (the object's stores read so; a callee clang inlines brings its locals above the
#   caller's, codegen.md C5). The helper, its name and its linkage are chosen.
# - vota::CGeraResumoZeresimaBase::StartState (fn 11943, 54 over 801) in unit 169's cgeraresumozeresimabase.cpp: the
#   next state set to this, the form's slot 2, vota::GeraResumoZeresima, slot 9, and slot 10's result stored as the next
#   state. GeraResumoZeresima (the phase's separator, the report, LogaGerandoRelatorio with RELATORIO_RESUMO_ZERESIMA
#   around writing rze.dat, SincronizaRelatorios, the urna's number stored as CEstadoGeralVota's urnaIdGerouZeresima, fn
#   491) and CriaRelatorioResumoZeresima ({CFormPart(CriaCabecalho("Resumo da Zer�sima")), CFormPart(5579's form)},
#   5971's parts inserted after the first) have no index: 11943 holds each behind an 80-byte frame. Measured: both in
#   cgeraresumozeresimabase.cpp, 835 over 1390 (589 inserted: binaryen inlined the vector's insert, below); with a roots
#   stand-in for that insert that read the call's result (no target caller reads it: reading.md R18), 202 over 813; the builder in cgeradorresumozeresima.cpp and the generator in
#   cgeraresumozeresimabase.cpp, 62 over 805 (4 inserted, 4 deleted: the report's address taken at the call, where the
#   target takes it in the builder); both in cgeradorresumozeresima.cpp, the generator above or below the builder, 54
#   over 801. The target's builder keeps 5971's result's begin and end in locals across its calls and drops that
#   vector's last store, which ours does only in 5971's TU: a reading, that clang sees there that 5971 does not capture
#   its result's address. The two names, their being free functions of vota, their file and their order are chosen, and
#   so is CEstadoGeralVota::SetUrnaIdGerouZeresima.
# - The insert: the builder calls std::vector<std::shared_ptr<api::IReportPart>>::__insert_with_size, which clang keeps
#   out of line (-Rpass-missed=inline: cost 1090, threshold 250). The target's 2875 is that body, one with RHVoice's
#   vector<shared_ptr<correction>> instance, called by 11943, 11946, 1245 and 813; our instance is RHVoice's code in
#   the objects (wasm-objdump -d, the object-local numbers masked), and our link inlined it into its one caller all the
#   same, so the roots stand in for 11946's call. With two callers ours is out of line, and step 9 renamed 2875's line
#   from RHVoice's instance to it, the copy binaryen keeps (it links first). With 5971 in the link, step 9
#   renamed 5969's line (one body for CParteCandidatos's and CParteRdv's __shared_ptr_emplace::__on_zero_shared, slot 2
#   of both blocks' vtables) to CParteRdv's, which 5971's object emits.
#
# Roots: 325-uenux2-geradores-zeresima-roots.cpp stands for the target callers not written: 11946, 12105 and 12110 for
# 1047; 11946 for 5977, 5579, 5971, 5580 and the insert (2875's instance); 11946 and 12110 for 3873, 3872 and 3699.
# Stand-ins of other units whose every caller is now in the link went: unit 111's w111_relatorio (for 1047; 1127 is
# matched), unit 230's w230_titulos (for 5579), unit 183's two address sinks (for 3872), unit 88's s11556 (5580 passes
# 11556's slot), unit 77's CParteRdv builder (5971), unit 129's Totais (5801's callers 11980 and 11981) and unit 140's
# w140_mapa (2877's caller 5971). Those of units 58, 77, 89, 109, 110, 121, 123, 162, 168, 196, 205, 216 and 317 keep
# callers that still wait; the comments of those with callers now in the link name them.
#
# Not written, with what each waits for:
# - 11946 (vota::CGeraZeresimaBase::StartState, unit 169's pending trap), and what only it reaches: 11975 and 11976
#   (table slots 1632 and 1631, read as a CDataSourcesRelatorio text of the comparecimento over 3871 and a parties'
#   filter over CCandidaturas::GetCandidatosPartido and ExisteCandidatoFederacao, 2272 and 5809) and the __func<bool (*)(),
#   bool ()> slots 11953 to 11957. A form written as 11943's (StartState, a generator writing ze.dat with
#   RELATORIO_ZERESIMA, a builder of the header, the candidates' list, CParteCargos over CParteCandidatos's four parts
#   and the footer, and five forms of other functions binaryen inlines) scored on whole links: builder and generator in
#   cgeradorresumozeresima.cpp, 250 over 3011 (3 inserted, 14 deleted), 234 over 3008 with crelutil.cpp.o moved after
#   that object; both in cgerazeresimabase.cpp and the forms in cgeradorresumozeresima.cpp, 502 over 3053, 157 over 3008
#   operand-only with crelutil.cpp.o moved after cgerazeresimabase.cpp.o, twelve of those rows two locals swapped. The
#   data put crelutil.cpp's records (@1576792 on) after cparterdv.cpp's and crelatoriotesteimpressora.cpp's, after both
#   objects; our link has it in unit 123's list, ahead of them. 11946 hands the parts forms (shared_ptr<IForm<IPaper>>)
#   with no CFormPart around them where cpartecandidatos.h's constructors take IReportPart (all of
#   CParteCandidatosMajoritarios's and CParteCandidatosConsultas's, six of CParteCandidatosProporcionais's seven, the
#   first two of CParteCandidatos's), so those types change with it.
# - 12105, 12110 and the stretch: not attempted.
#
# nothing in the skeleton gives these functions their target's call sites: the roots stand for those callers, through
# asm labels, so the rule needs no header
$(ROOT)/$(APP)/325-uenux2-geradores-zeresima-roots.o: $(ROOT)/src/units/325-uenux2-geradores-zeresima-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/325-uenux2-geradores-zeresima.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/325-uenux2-geradores-zeresima-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/325-uenux2-geradores-zeresima-roots.o
