# Unit 309: no source of its own. Its roots file stands for the unwritten target callers of the members this unit adds
# to landed units' sources (src/units/README.md "Landing a unit" item 2), the zerésima chain over comum::CLocal's
# loader; each of those units' fragments describes its members in a paragraph of its own, with the evidence, the choices
# and the scores:
# - unit 89, app/comum/dados/clocal.cpp: comum::CLocal::Carrega (target fn 5740) and GetTodasSecoes (5741), with
#   TemContingencia and the location file's name and path helpers (no index); carregaarquivo.cpp moved into its list;
# - unit 280, app/comum/dados/carregaarquivo.cpp: CarregaArquivo<asn::CConversorLocal>, which 5740 holds inlined;
# - unit 131, app/comum/nomearquivo/cnomearquivo.cpp: CNomeArquivo::NomeArquivoLocal, which 5740 holds inlined;
# - unit 109, app/comum/appinfo/cappinfo.h: CAppInfo::GetGeralInterno, inline, which 5740 holds;
# - unit 110, app/vota/eleitor/comum/ctelasvota.cpp: vota::AdicionaLocal (4161), TelaNeutra (2380) and
#   TelaPorFavorAguarde (6587); their stand-ins went once unit 443's constructor made fn 7787's calls of 4161 and 2380;
# - unit 104, app/vota/eleitor/iniciovotacao/: CReimprimindoResumoZeresima::StartState (11855) and
#   CImprimindoZeresima::StartState (11991), with the printers they hold; with 11991, unit 199's
#   CDefineRotaPreVotacao statics' exit destructors (11995, 11996) match.
# All nine match. The roots compile at APP_CXXFLAGS and declare what they call through asm labels: they emit no TSE
# code, so no match rests on their flags. The census pairs no target function with a stand-in (how-to step 7's
# command). Each stand-in's comment names the target callers it stands for; it goes when they are all in the link.
$(ROOT)/$(APP)/309-uenux2-zeresima-callers-roots.o: $(ROOT)/src/units/309-uenux2-zeresima-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/309-uenux2-zeresima-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/309-uenux2-zeresima-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/309-uenux2-zeresima-callers-roots.o
