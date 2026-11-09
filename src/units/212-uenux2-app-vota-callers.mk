# Unit 212: no source of its own. It adds members to landed units' sources, each of which that unit's fragment describes
# in a paragraph of its own, with its evidence, its choices and its score:
# - unit 97, app/vota/eleitor/cvotacaostateaudio.cpp: vota::CVotacaoStateAudio::FormatPartyName (target fn 6954, record
#   :297), with EUeVotaError's 9321 (app/vota/euevotaerror.h); its one caller, fn 6999, is written (unit 97), so it has
#   no stand-in;
# - unit 119, app/vota/log/clogvota.cpp: vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550, a chosen name);
# - unit 88, app/comum/dados/md/processoeleitoral/ccargo.cpp: comum::md::CCargo's TemFoto and QtdSuplentes (fns 1546 and
#   1157, chosen names), with two accessors of CDetalheCandidato (cdetalhecandidato.h);
# - unit 110, app/vota/eleitor/comum/ctelasvota.cpp: vota::MensagemErroCargo (fn 690, a chosen name), whose literal
#   ") - " lets unit 112's fn 1143 match too.
# All five match. No roots: 212-uenux2-app-vota-callers-roots.cpp stood for their unwritten target callers
# (src/units/README.md "Landing a unit" item 2), the last of them fn 7787's calls of QtdSuplentes and MensagemErroCargo,
# which unit 443's constructor makes since; the file went, and the link without it moved no row (steps 7 to 9: 0
# matches added, 0 renamed, no verdict changed).
