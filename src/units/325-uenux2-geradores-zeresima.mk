# uenux2: helpers of the zerésima reports (fns 11946 and 11943, vota::CGeraZeresimaBase's and
# vota::CGeraResumoZeresimaBase's StartState, unit 169's traps), written in landed units' files; this fragment holds
# their notes and their roots. Paths relative to src/uenux2.
#
# Matched, each scored with pnpm wasm score against the whole link's names.tsv before steps 7 to 9, all operand-only:
# - api::GeraArquivoRelatorio (fn 3654, 12 over 181 rows) in api/gui/reports/creportprinter.cpp and api::CScopedReport-
#   File's constructor and destructor (records creport.cpp:31:5 and :37:9, which 3654 holds) in creport.cpp, with
#   api::CReport::ImprimePartes (5486, 0 over 27) and DoPrintJob's lambda's call operator (10884, 0 over 5), which match
#   with them: unit 317's files, whose fragment and creport.h have the evidence and why the files split so.
# - vota::CLogVota::LogaGerandoRelatorio (fn 1047, 17 over 288) in app/vota/log/clogvota.{h,cpp} (unit 119's files), with
#   comum::IEventosLog::ConverteInicioTermino (no target index) in app/comum/log/ieventoslog.{h,cpp} (unit 111's).
# - vota::CRelVotaUtil::CriaCabecalho (fn 5977, 21 over 265), CriaCabecalhoDetalheZE (3873, 6 over 112) and
#   CriaDetalheCandidato (3872, 5 over 88) in app/vota/eleitor/iniciovotacao/crelvotautil.{h,cpp} (unit 246's files),
#   and CriaCabecalho's lambda's __func slots 11999 to 12002. Its call operator is 2881, the body four lambdas share,
#   whose match line step 9 renamed to this lambda's (binaryen keeps the first twin in link order).
# - comum::CRelUtil::FormRodapeZeresima (fn 5579, 33 over 279) in app/comum/relatorios/crelutil.{h,cpp} (unit 123's), in
#   the gap above ImprimeSeparadorVia.
# crelvotautil.cpp's object now holds two copies that matched from unit 183's roots before:
# CDataSourcesRelatorio<CRdvVota, CEleitores>'s DetalheCandidato and DetalheCandidatoZE (11972, 11973), which 3872
# instantiates, at the roots' flags (UENUX2_CXXFLAGS with -fno-strict-aliasing): 20 over 417 and 27 over 430,
# operand-only, and both still match.
#
# Evidence and choices:
# - 1047: the text, "Gerando relatório [{}] [{}]", and ConverteERelatoriosUE (fn 5879) of the report; clogvota.h has its
#   callers' arguments. The phase's text is built in two branches of known length ("INÍCIO" for 0) through a local that
#   holds the string's address. Measured on whole links: `std::string(termino ? "TÉRMINO" : "INÍCIO")` 60 over 300 rows
#   (a select and a copy), `termino ? std::string("TÉRMINO") : std::string("INÍCIO")` 84 over 309, the text from a
#   function out of line returning that ternary 43 over 292, `if (termino) return "TÉRMINO"; return "INÍCIO";` 24 over
#   288 (the branches swapped) and `if (!termino) return "INÍCIO"; return "TÉRMINO";` 17 over 288, operand-only. Out of
#   line was measured with a noinline attribute in clogvota.cpp, then with the function in ieventoslog.cpp, another TU,
#   which gives the same 17 over 288 and no symbol of it in names.tsv (binaryen inlines it into its one caller). That it
#   is IEventosLog's, beside ConverteERelatoriosUE, both names, the bool and the places are chosen: in clogvota.cpp
#   after LogaEleitorSuspensoSemVoto and in clogvota.h after LogaImprimindoRelatorio, apart from the lines another
#   branch adds at both files' ends (17 over 288 at the end too).
# - 5977: the lambda's RTTI (typeinfo 1543360) names it and its class; its body is unit 317's MontaCabecalho's shape,
#   with the place read from CEstadoGeral (GetDadoLocal().GetSecaoCarga(): +20, +24, +26), the labels "Data" and
#   "Hora", GetIdentificacaoUrna by its address (table slot 1567) and no phase separator; GetGeral, Now and
#   CLocal::GetInst in the order of the target's calls. The result's type is spelled std::shared_ptr<api::IForm<
#   api::IPaper>>: fn 5971's record names it api::SharedPaperForm, which no header of ours declares (a typedef of that
#   type, a reading).
# - 3873 and 3872: forms of one field from a data source's address (table slot 1634, and 1636 or 1635 by the argument,
#   which fn 11946 passes as 0 and fn 12110 as 1). Use band 3 has them after crelvotautil.cpp's copy of
#   api::CSubReport::GetTitulo (3874), so this file, a reading; their names, the bool and their being CRelVotaUtil's are
#   chosen, their order (3873 above 3872) the band's. In our object that copy comes after both (ld_index 5216 against
#   5211 and 5212), where the target's band has it first: not explained.
# - 5579: use band 2 puts it between two functions of crelutil.cpp's object (5578 and ImprimeSeparadorVia, 5581), so a
#   static member of CRelUtil (whose records read `static`). CConfiguracaoEleicao's +200, its second argument at both
#   callers, is GetParametrosUrna().GetRodapeZEVOTA() (measured: the address a probe object computes), and the
#   correspondence's +28 its GetCodigoCarga(). ImprimeTitulos is called as the two-argument overload, which clang
#   inlines into the three-argument call the target makes (3689, with the UF). Its name and parameters' types are
#   chosen. The include of api/util/cstringutils.h takes one blank line of the gap after `namespace comum {`.
#
# Roots: 325-uenux2-geradores-zeresima-roots.cpp stands for the target callers not written: 11943, 11946, 12105 and
# 12110 for 1047; 11943 and 11946 for 5977 and 5579; 11946 and 12110 for 3873 and 3872. Stand-ins of other units whose
# every caller is now in the link went: unit 111's w111_relatorio (for 1047; 1127 is matched), unit 230's w230_titulos
# (for 5579) and unit 183's two address sinks (for 3872). Those of units 89, 123, 196 and 317 keep callers that still
# wait, and their comments name the ones now in the link.
#
# Not written, with what each waits for:
# - 11946 and 11943 call fn 5971 (the RDV extract's parts; records iniciovotacao/cgeradorresumozeresima.cpp:43 and :47
#   of its internal CriaTituloExtratoRDV), which takes the address of 11981 (table slot 1625) and, through 5970, of
#   11980 (slot 1626), cdatasourcesrelatorio.h's TrailerProporcional and TrailerMajoritario (2762 and 2326 bytes), and
#   calls 5580 and 3699; none of them is written. 11946 also stores 11976's slot (1631) in a std::function<bool()>
#   (__func slots 11953 to 11957).
# - 3871 with 11980, 11981 and its lambda's slots 11966 to 11970; 11975; 12105 and its helpers: not attempted.
#
# nothing in the skeleton gives these functions their target's call sites: the roots stand for those callers, through
# asm labels, so the rule needs no header
$(ROOT)/$(APP)/325-uenux2-geradores-zeresima-roots.o: $(ROOT)/src/units/325-uenux2-geradores-zeresima-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/325-uenux2-geradores-zeresima.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/325-uenux2-geradores-zeresima-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/325-uenux2-geradores-zeresima-roots.o
