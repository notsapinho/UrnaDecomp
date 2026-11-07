# Unit 441: no source of its own. It adds members to unit 110's app/vota/eleitor/comum/ctelasvota.cpp (and
# ctelasvota.h) and app/comum/dados/crespostas.cpp, and error enumerators to app/vota/euevotaerror.h; its roots stand
# for fn 7787 (not written). Scores are `pnpm wasm score` against the plain link (ours from
# build/out/wasm-map/vota_web/names.tsv), whole link at the trees' flags, before steps 7 to 9; "operand-only" means rows
# that differ in calls and data addresses alone.
#
# What 7787 holds (pnpm wasm fn ../target/vota_web_wasm.wasm 7787, its piece build/out/splat/pieces/asm/comum/7787.wat;
# offsets in its body): about 92 KB of the vote's data load first (CConfiguracaoEleicao::CreateInst, CCargos,
# CRespostas, CHV, the parties, CFederacoes::Load, CFotos::Load, CCandidaturas::LoadFromFile, CRdv, CRdvVota::CreateInst,
# CInformacaoEleitor::CarregarDadosEstaticos, CEleitores::StaticLoad, the DAO registrations: records of those files),
# then, behind a 16-byte frame of its own at +0x1674f, vota::CTelasVota::CreateInst (the s_instancia test, `new` of 252
# bytes, the constructor's 96-byte frame from +0x1676d, its throw "Tipo de cargo nao identificado" at record
# ctelasvota.cpp:3502, CreateInst's "CTelasVota - instancia ja criada" at record :3435, the unlock of s_mutex), then
# CInfoMTLCD::CreateInst and CInstrucaoVotacaoAcessibilidade::CacheInstructionAudio. So 7787 is a function no record
# names, and CreateInst and the constructor have no index of their own; none of the three is written here.
#
# The constructor builds, for each post of comum::CConfiguracaoEleicao::GetTodosCargos(), the post's screens by its
# kind (a std::map<ETelaVotacao, ...> handed to vota::CTelasCargo's constructor, fn 2386), and holds each screen behind
# a prologue of its own: one caller each, inlined by binaryen, so out of line in the object. Fourteen of them, added to
# ctelasvota.cpp as static members of CTelasVota (ctelasvota.h has the evidence and the choices), are the only callers
# of seven anonymous-namespace builders, two screens each; the builders' records give their names, parameters and
# namespace, each at its record's line, column 15:
# - 6671 adicionaBaseTelaCompletaCandidatoCom1 (:853, :858) and 6660 adicionaBaseTelaCompletaCandidatoCom2 (:890,
#   :895): the post with one or two substitutes. Each throws when the post has no candidate's detail ("não é de
#   candidato") or the wrong count of substitutes ("com número de suplentes incompatível"; Com2 tests `< 2`, the
#   target's le_u 1), then AdicionaDadosCandidato (4185) at 470 or 639 by the post's photo, AdicionaSiglaPartido (2028),
#   each substitute's line ("<post name>: <ballot name>") through api::CFormBuilder::AddDoubleLineField (3068) at (10,
#   320) and (10, 340) (Com1; Com2 at 310/330 and 355/375), the holder's photo (4184 with true) when the post has
#   photos, and each substitute's photo through AdicionaFotoSuplente (4181, below) when it has one. The width the
#   screen's instructions and footer take is returned through the reference: Com1 520 or 639 by substitute 1's photo;
#   Com2 (x - 5), x being substitute 1's photo's left edge when it has a photo, else substitute 2's less 5 when that one
#   has, else 639.
# - 6652 adicionaBaseTelaCompletaConsulta (:942) and 6641 adicionaBaseTelaVotoBrancoConsulta (:993): a consult's post
#   ("não é de consulta"), its question (AdicionaPergunta, 3074), then the number field over comum::CRespostasDSNumero
#   (AdicionaCampoNumero over a source, a CMaskedTextField<CFramedText> of its digits at (100 - 40 * digits, y)) and
#   comum::RespostaCorrente's text (table slot 1096, fn 11479) at (100, y + 3) in FONTE_NUMERO; or "VOTO EM BRANCO",
#   blinking at (320, y).
# - 6605 adicionaBaseTelaCandidatoInexistente (:1075), 6603 adicionaBaseTelaCandidatoInapto (:1101) and 6602
#   adicionaBaseTelaVotoLegenda (:1126): a proportional post ("não é de proporcional", CCargo::IsProporcional inline),
#   its name (1192), the grey number field (3060) at (10, 115); then "CANDIDATO INEXISTENTE" at (10, 190) in
#   FONTE_AGUARDE, the party (2028) and "VOTO DE LEGENDA" blinking at (195, 345); or the text of a candidate who does not
#   run (13101, table slot 1099) at (10, 190) and "VOTO NULO" at (320, 345); or the party and "VOTO DE LEGENDA".
# All seven match, named by srcloc-anchor at step 8: 6602 16 over 164 rows, 6603 17 over 194, 6605 23 over 238, 6641 14
# over 116, 6652 21 over 256, 6660 33 over 228 and 6671 28 over 158, each operand-only.
# - 13101 DS_CandidatoNaoConcorre (:294, anonymous namespace): "CANDIDATA NÃO CONCORRE" when the current candidacy's
#   holder is a woman (comum::CCandidaturasDSSexo(0), fn 5806, against SEXO_FEMININO), else "CANDIDATO NÃO CONCORRE";
#   it throws code 9333 with "Nao foi posicionado no candidato corretamente" when CCandidaturas' cursor is at the end
#   (IsFim). Each literal in its own return: the target copies them in two arms after one allocation, where a
#   conditional over the two literals gives one copy over a select (78 over 112 rows, 25 inserted and 41 deleted, with
#   the throw block first; 16 over 87, operand-only, as written). Matches, named by srcloc-anchor.
# - The substitutes' texts are six captureless lambdas, each a function pointer the builder passes (table slots 1090 to
#   1095): two slots hold one function each in the target (1090 and 1092, 1091 and 1095: identical functions merged),
#   and binaryen merged the rest into two bodies with constants passed by thunks, 6075 (callers 6664 and 13298, the
#   post's name for substitutes 1 and 2) and 6076 (6669 and 13301, the line). Our link forms the same merges. 6076's
#   body names the substitute's comum::CCandidaturasDSNome first (its byte stored first, at the frame's top) and then
#   calls a helper that returns the post's name for the substitute, NomeCargoSuplente, which clang inlines: its
#   CCargoDSNomeSexoCandidato then shares a slot with the concatenation's temporary, as in the target (codegen.md C5,
#   read on the object). With the line written as one expression, 27 over 125 rows (6 inserted, 5 deleted: the byte
#   stored before its own call, the parameters in the other order, so the thunks 6669 and 13301 read 3 over 7); with the
#   name named first and no helper, the object gave the first store but not the shared slot. As written, 6076 6 over
#   119, 6075 1 over 19, and the four thunks 1 over 5 or 6, each operand-only; all six match. The photos' lambdas call
#   the same helper; 6075 and its thunks scored the same with CCargoDSNomeSexoCandidato called in place (1 over 19, 1
#   over 5), so that form gives the same rows.
# - The substitutes' lines go through a second helper clang inlines, AdicionaLinhaSuplente (builder, source, y, width),
#   which the frames show: in 6671 the target reads the width before it stores the two points, and the points take the
#   highest frame slots, which a call over the width gives (its locals above the caller's); in 6660 the two lines'
#   results and the photos' rectangles share one slot (frame 48). With AddDoubleLineField called in place, 6671 scored
#   44 over 158 rows (4 deleted) and 6660 57 over 228 (frame 64); with the helper, the figures above.
# - 4181 AdicionaFotoSuplente (no record of its own: :487 is adicionaFotoEmoldurada's, inlined, its SRCFT
#   comum::CCandidaturasDSFoto; callers 6660 and 6671): the substitute's photo at (x + 1, 288), 111 x 155, through
#   adicionaFotoEmoldurada over CCandidaturasDSFoto(suplente), and the name text centred under it (the source passed,
#   AddTextField over a function, 1191, in an {13, 0} temporary), at (x + 55, 443) when the image is at most 1 wide; it
#   returns the photo's rectangle. Written and differing: 36 over 200 rows, 2 inserted and 3 deleted, the frame slots
#   only (the point's slot against the source_location's and the results'), as 4184's differ (unit 378's fragment has
#   the forms measured there); not explained. Named by call at step 8 (by:6660,6671).
# 6678 (adicionaBaseTelaCompletaCandidatoCom0, unit 378's) matches since: its `unresolved self-voted` waited for a voter
# for 4184's name besides its own call, which 6660 and 6671 give.
#
# Other members:
# - comum::CRespostasDSNumero's constructor, defined in crespostas.cpp (crespostasds.h declared it only): fn 6652 calls
#   it, and the target holds one body for it and api::CSynchronizer's (fn 5729): step 9 renamed 5729's match line to it,
#   our link keeping crespostas.cpp.o's copy. Its file is a choice.
# - GetFormularioProgresso takes the bool GetInteractiveForm (fn 554) takes, defaulted to true: the vote-by-party
#   screens pass false (the target's 0), the others 1. The default, and a parameter where a direct call of
#   GetInteractiveForm in those two screens would do, are choices.
# - Error codes (app/vota/euevotaerror.h): 9336 to 9340, 9342 and 9345 to 9347 the builders', 9333 13101's; names chosen.
#
# Places. Chosen: the builders' and 13101's places are their records'; the helpers' (after AdicionaFotoSuplente, line
# 603), 4181's (after AdicionaFotoCandidato), the screens' and their order are this file's layout. The builders are
# internal and clang emits each right after the definition that first mentions it, so the screens' places order them:
# the Com1, Com2 and full-consult screens follow CriaTelaConferenciaCandidatoCom0, which moved up from line 1522 to
# 1461 (record-less; its code and its place among the landed functions unchanged), and the blank-consult and the
# proportional screens follow CriaTelaVotoBrancoCandidato. Use band 2 then holds the target's order (a higher index at
# a lower ld_index) for 6671, 6660, 6652, 6605, 6603 and 6602 against every function the object defines, and 6641 sits
# after 6639, 6626, 6624, 6616 and 6608 (5 pairs): its screens need 15 lines, and the free runs between 6646's first
# user and 6639's are 4 and 8 lines (6608's own place, before 6646, is the base's). Counted over the object's matched
# members of band 2, template instances apart (placing.md P9): 5 inverted pairs at the base, 10 here. Band 3 holds
# 4185, 4184, 4181, 4161 in order (0 pairs). Band 1: 13101 adds 2 pairs, against 8563 and 12811, which functions above
# line 600 mention first, and the lambdas' thunks 13298 and 13301 8 (231 pairs at the base, 241 here).
#
# Header edits: ctelasvota.h (the screens' declarations and comments) and euevotaerror.h (enumerators and comments) leave
# every other object as it was: the 576 uenux2 objects compiled from this tree with the two headers at the base's text
# give 575 objects cmp-equal to the link's; the 576th, ctelasvota.cpp.o, needs the new declarations and does not compile
# so (workflow.md W13's method, the same compile lines over a copy of the tree).
#
# Roots: 441-uenux2-ctelasvota-bases-roots.cpp stands for 7787's calls of the fourteen screens, one call each, so that
# binaryen inlines each into it as into 7787 and the builders keep their two call sites. It goes when 7787, or the
# constructor 7787 holds, is in the link. Stand-ins these members made idle went, call by call: unit 378's for 6602, 6603
# and 6605 (CamposCinza), 6660 and 6671 (BasesCompletaCandidato) and 4181 (FotoSuplente), and its TelasVotaConstrutor's
# calls of 1593, 1102 and 1190 (7787's calls of them come with the screens); unit 129's NomesSexo (2268's callers 6075
# and 6076); unit 212's calls of TemFoto and its second calls of QtdSuplentes and MensagemErroCargo (one each stays, for
# 7787); unit 92's NovaMoldura (CFramedText's constructor, for 6652); unit 121's builder and sink of
# CDataText<comum::CRespostasDSNumero>, whose vptr 6652 stores. The link without them moved no row (steps 7 to 9: 0
# matches added, 0 renamed, no verdict changed). The same kind of stand-in in units 89's, 154's, 88's, 102's and 110's
# roots is idle too (13101's and 6076's calls of 5806 and 5807, 6652's of 5729, 6660's and 6671's of 1388 and 1545,
# 6652's control block and table slot 1096): a link without them moves no row either (steps 7 to 9 on it), and they go
# with those files' next change. The roots declare what they call through asm labels: they emit no TSE code and
# instantiate nothing, and the census pairs no target function with them.
$(ROOT)/$(APP)/441-uenux2-ctelasvota-bases-roots.o: $(ROOT)/src/units/441-uenux2-ctelasvota-bases-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/441-uenux2-ctelasvota-bases.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/441-uenux2-ctelasvota-bases-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/441-uenux2-ctelasvota-bases-roots.o
