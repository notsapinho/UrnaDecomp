# Unit 212: no source of its own. Its roots file stands for the unwritten target callers of the members this unit adds
# to landed units' sources (src/units/README.md "Landing a unit" item 2), each of which that unit's fragment describes
# in a paragraph of its own, with its evidence, its choices and its score:
# - unit 97, app/vota/eleitor/cvotacaostateaudio.cpp: vota::CVotacaoStateAudio::FormatPartyName (target fn 6954, record
#   :297), with EUeVotaError's 9321 (app/vota/euevotaerror.h);
# - unit 119, app/vota/log/clogvota.cpp: vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550, a chosen name);
# - unit 88, app/comum/dados/md/processoeleitoral/ccargo.cpp: comum::md::CCargo's TemFoto and QtdSuplentes (fns 1546 and
#   1157, chosen names), with two accessors of CDetalheCandidato (cdetalhecandidato.h);
# - unit 110, app/vota/eleitor/comum/ctelasvota.cpp: vota::MensagemErroCargo (fn 690, a chosen name), whose literal
#   ") - " lets unit 112's fn 1143 match too.
# All five match. The roots compile at APP_CXXFLAGS and declare what they call through asm labels: they emit no TSE
# code, so no match rests on their flags. The census pairs no target function with a stand-in (step 7's command). Each
# stand-in's comment names the target callers it stands for; it goes when they are all in the link.
$(ROOT)/$(APP)/212-uenux2-app-vota-callers-roots.o: $(ROOT)/src/units/212-uenux2-app-vota-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/212-uenux2-app-vota-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/212-uenux2-app-vota-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/212-uenux2-app-vota-callers-roots.o
