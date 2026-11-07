# Unit 378: no source of its own. It adds to unit 110's app/vota/eleitor/comum/ctelasvota.cpp (and ctelasvota.h) the
# vote screens CTelasVota's constructor (target fn 7787, not written) builds per post, and the helpers they share; its
# roots stand for 7787's calls of them (src/units/README.md "Landing a unit" item 2). Scores are `pnpm wasm score`
# against the plain link (names.tsv's index), whole link at the tree's flags; "operand-only" means rows that differ in
# calls and data addresses alone.
#
# Matched (33, the comm of docs/how-to-decompile.md step 10 against the commit this unit started from): 3064
# CTelasVota::CriaTelaVotoCargoSemCandidato, 6626 CriaTelaVotoNuloConsulta, 6616 CriaTelaConferenciaVotoNuloConsulta,
# 6592 CriaTelaConfirmaImpressaoZeresima, 6601 CriaTelaFim, 3063 CriaTelaVotoBrancoCandidato, 3067
# CriaTelaConferenciaVotoBrancoCandidato, 1767 CriaTelaConferenciaVotoNuloCandidato; 1192 AdicionaNomeCargo with its
# data source's slots (CDataText<DS_NomeCargoNeutroComEscolha>'s GetText 12587, D0 12588, D2 12589, its block's D0
# 12591 and D2 12592); 1102 AdicionaInstrucaoTeclas with its lambda 13137 (table slot 1097); 1190
# AdicionaRodapeConfira; 3074 AdicionaPergunta; 13176 NumeroDigitado; 6646 adicionaBaseTelaVotoBrancoCandidato; the gif
# screens' 1593 AdicionaGif with its map's tree members 4189 and 6643, the map's exit destructor 13527 and 6696
# (std::vector<api::CMovieFrame>'s __init_with_size), 1444 (the pair<const unsigned char, std::string> constructor
# 3076 calls), api::CFormBuilder::AddMovie 5543 (unit 31's file) with CMovieField's timer lambda 11054 to 11058, and
# api::CMovie::ProximoFrame 5525 (unit 23's). Then 11 more (the same comm against the commit they started from), the
# candidate's complete screens and what they call, below: 2028, 3060, 4129, 4185, 5535, 6528, 6639, 6681, 11501, 12641,
# 12811. Written, not matched: 6624, 6627, 6608, 1591, 3076, 4184 and 6678 (below).
#
# - 3064: the record ctelasvota.cpp:1585 (column 15) gives the name, the parameters (const comum::md::CCargo &,
#   api::TPosition) and the throw: code 9354 with MensagemErroCargo(name, post, "não é de candidato") when the post
#   has no candidate's detail. Its api::TPosition is unused: the rectangle's corner (639, 401) is one i32 constant in
#   the target, which clang gives for constants, where a parameter binaryen folds later stays two 16-bit stores (in the
#   link, with the parameter used there). The blinking text goes through AdicionaTextoPiscante, which takes its font by
#   value and builds the point inside: the target stores the font as one 8-byte constant after the string and before the
#   point, which a by-value copy of the file constant inlined there gives (a temporary SFont{30, 0} gives two field
#   stores, a named local one 8-byte store at the declaration; probes compiled at the tree's flags). The footer (the
#   rectangle, "Aperte a tecla:", "CONFIRMA", " para continuar") is AdicionaInstrucaoContinuar, an internal helper clang
#   inlines: the target's discarded results share frame slots as an inlined callee's give, and written in place they
#   took slots of their own (121 over 558 rows against 45 over 555, operand-only, with the helper). The form's name is
#   built before the progress bar's block: GetFormularioProgresso takes the name, as vota::GetFormularioInterativo does,
#   and builds the block inside; the direct GetInteractiveForm(std::make_shared<CPreShowProgressBar>(), name, true)
#   builds the block first (measured in the whole link).
# - 6626 and 6616: the post and a text (7787 passes "NÚMERO ERRADO"); adicionaBaseTelaVotoNuloConsulta (6624) with the
#   screen's name, then 6626 the keys' footer over "CONFIRMAR este voto" and the input control, 6616 the "CONFIRA O SEU
#   VOTO" footer. "CONFIRMAR este voto" is a named char array (TEXTO_CONFIRMAR_VOTO, @474912, loaded i64 align=3, as
#   unit 110's arrays are), passed through AdicionaInstrucaoConfirmarVoto, an internal helper clang inlines: the target
#   holds the screens' string slot above the builder's in 6626, 6639 and 3063, the three that pass that text, and below
#   it in the others; with the std::string made in the static, 6626 took them the other way (35 over 251 rows against
#   23, operand-only, with the helper).
# - 6592: AdicionaTelaQRCode (3059) over the text in upper case, two empty texts and the origin 2 (no enumerator of
#   comum::CQRCodeDS::EOrigem), the labels 'C' with the text and 'B' "Mais informações",
#   "telaConfirmaImpressaoZeresima".
# - 6601: "FIM" at (320, 140) and the text at (629, 408), right-aligned in colour 5, AdicionaLocal (4161), "telaFim"
#   through GetFormulario. The fonts' sizes are parameters 7787 passes as 200 and 40 at both its calls: the target
#   stores each SFont field by field at the top, the style before the size, which named locals over parameters give and
#   constants do not (an 8-byte store; probes at the tree's flags); in the link 12 over 232 rows, operand-only.
# - 1192: (const md::CCargo &, api::CFormBuilder &) in that order is its wasm type's (the post first). The name of the
#   post, with " - " and its choice's ordinal (GetOrdinalEscolha over vota::g_escolhaAtual) when it has more than one,
#   is DS_NomeCargoNeutroComEscolha (the RTTI name of CDataText<vota::(anonymous
#   namespace)::DS_NomeCargoNeutroComEscolha>, whose GetText 12587 is its call operator inlined), drawn on two lines
#   (CTextFieldDoubleLine, (10, 60) and (10, 95), 639, the font {30, 1} @475328, background 1) when the post has photos,
#   else as a CTextField at (10, 60). The positions are parameters every caller passes as 10 and 60: the target stores
#   the points' coordinates as four 16-bit stores, which parameters folded by binaryen give and constants do not (clang
#   merges them into two 32-bit stores: 32 over 451 rows; 17, operand-only, with the parameters). The text is released
#   before the field after AddField, which a helper returning the field into the caller's discarded temporary gives:
#   AdicionaTextoDuasLinhas and AdicionaTextoFonte, templates over the source as api::CFormBuilder's AddTextFieldUpdate
#   is. The data source as an aggregate and with a constructor give the same link (sha256 equal).
# - 6627 (std::make_shared<CDataText<DS_NomeCargoNeutroComEscolha>>, 1192's two calls) differs: 72 over 329 rows, the
#   inlined copies of the post's optionals branching otherwise (the same with this object built with strict aliasing, a
#   variant object only; with the source moved into make_shared, 182 over 417). Not explained. Its name is a
#   callers+content hand line in splat/symbol_addrs.txt (it alone holds both blocks' vptrs), which 1192's match needs.
# - 1102 and 1190: the footers, with the width as a parameter (7787 passes 389, 639 and a variable). The rectangle is
#   AdicionaLinhaRodape, an internal void helper clang inlines: the target's points take the frame's top slots and the
#   discarded field the slot below, which that form gives (probe of five forms at the tree's flags: the rectangle in
#   place, in a helper returning the field, its points as named locals or as the helper's parameters give other
#   offsets). " para REINICIAR este voto" is a captureless lambda passed as std::string (*)() (slot 1097, 13137).
# - 3074: the consulta's question (GetDetalheConsulta's GetPergunta) with '|' turned into '\n' (std::replace, which
#   -O3 unrolls by four as the target has it), a CTextFieldMultiLine in SRect(10, 50, 629, 255) in {35, 0} centred, and
#   its Rect's bottom plus 23, read after the field is released (a named SRect: with the expression in the return the
#   bottom was read first, 2 rows inserted and 2 deleted).
# - 6624, adicionaBaseTelaVotoNuloConsulta (record :1014, code 9344 over "não é de consulta"), differs, named by
#   6626's and 6616's calls: 56 over 322 rows, every row a frame offset but two deleted (an add of an offset that is 0
#   in ours): the target holds the strings' slot above the throw's message, ours below. Written with the body first and
#   the throw in the else, the frame's size and the strings' place are the target's but the test is `== 1` where the
#   target tests the byte (48 over 324, 2 inserted); the blinking helper over a const char*, with a named point or with
#   a copied font gave other offsets (object probes). Not explained. Its masked number field is
#   AdicionaCampoNumero<CFramedText>, a template of vota (not internal): clang keeps it out of line for its one call, as
#   the target does (binaryen inlines it, behind a second prologue), where an internal one is inlined (-Rpass=inline:
#   cost -14725 against the threshold 250, with LLVM's last-call-to-static bonus of 15000, so 275 without it); its text
#   is a CDataText over NumeroDigitado, and cmaskedtextfield.h's constructor copies it (that header has the
#   measurement).
# - 13176 NumeroDigitado returns vota::g_numeroDigitado (table slot 1098, which 6624's helper and 3060 store: one
#   function, so a named one); defined near the top, after AdicionaGifCargo (3076), a choice the use band does not
#   bound: 13527 (the gif map's exit destructor), a higher band-1 index, links after it in our object (below).
# - CPreShowProgressBar: its declared constructor is gone (implicit). Its key function PreShow (13550) was the trap of
#   this unit's pending file until fragment 391 wrote it, in app/vota/eleitor/comum/cpreshowprogressbar.cpp, whose
#   object emits the vtable now; the pending file and its rule went with it.
# The gif screens and the VotoBranco/VotoNulo pairs:
# - 1593 AdicionaGif(comum::md::CVoto::ETipo, api::CFormBuilder &, bool): the gif of a vote type
#   (":/resource/gifs/votoBranco.gif", "votoNulo.gif", "votoLegenda.gif", ledger/strings.tsv @169156, @169127,
#   @169355), loaded once per name and kind into the static std::map<std::pair<std::string, bool>,
#   std::shared_ptr<api::CMovie>> @1833348 (its tree members 4189 and 6643, its exit destructor 13527), a one-frame
#   movie (the current frame, through 6696) for a conferência screen, added at (640, 480)
#   through 5543. The internal CarregaGif is inlined; its name, the map's and the parameter's type are chosen.
# - 3063, 3067: the gif (BRANCO), adicionaBaseTelaVotoBrancoCandidato (6646, record :964, whose signature gives the
#   parameters; code 9341 over "não é de candidato") with the post's name and the blinking "VOTO EM BRANCO" at (x, 200),
#   x being 195 at both callers, then the "CONFIRMAR este voto" footer and the input control (3063) or the confira
#   footer (3067).
# - 1591, 1767: the gif (NULO), adicionaBaseTelaVotoNuloCandidato (6608, record :1049: its signature gives the
#   parameters, the field's right edge returned through a TPosition &; code 9344 over "não é de candidato"): the post's
#   name, a grayed number field of the untyped digits (3060, AdicionaCampoNumero<api::CGrayedFramedText>), the text
#   in FONTE_AGUARDE and the blinking "VOTO NULO". 1591 adds the keys' footer and the input control or a numeric field
#   (2383, flags 0 1 1 0 1) at the returned x, 1767 the confira footer. 1767 matches; 1591 differs, 53 over 290 rows
#   (43 operand-only, 3 inserted, 5 deleted: its frame is 64 bytes, the target's 48); 6608 differs, 47 over 211 (43
#   operand-only, 2 deleted, every operand row a constant or a load or store offset). Not explained.
# - 3060 (AdicionaCampoNumero<api::CGrayedFramedText>) calls 5535, CGrayedFramedText's constructor, out of line, which
#   keeps its two target callers (3060 and 4185): it differed, 13 over 131 (4 rows inserted, 5535 inlined), while 4185
#   was not written, and matches with 4185 in the link (below), as 5535 does.
# - 3076 AdicionaGifCargo(const comum::md::CCargo &, api::CFormBuilder &): the post's gif from a static
#   std::map<comum::TCargoID, std::string> @1833400 (nine pairs through 1444; its exit destructor is 13471, which reads
#   no-candidate), a copy of the movie added at (640, 480) through 5543. It differs, 77 over 562 rows (75
#   operand-only: frame slots and the map's guard and data addresses). Not explained. Its name is chosen.
# - 5543 and 5525: unit 31's and unit 23's fragments; 5543 holds CMovieField's constructor inlined (unit 52's file),
#   whose timer lambda calls the callback AvancaFrame (11056's body).
# Error codes (app/vota/euevotaerror.h): 9354, 9341 and 9344, and 6678's 9334 and 9335, names chosen from the screens
# and the messages.
# Chosen: every name above but the statics' (whose names the records and strings give), the free functions' being free
# and external (no record gives their linkage, as for unit 110's 690; NumeroDigitado's place is chosen, above) and the
# internal helpers' being helpers, the parameters' names and the lines (no record but 964, 1014, 1049 and 1585):
# AdicionaGifCargo at 266, the top of the file's anonymous-namespace run for the shared helpers (lines 300 to 422,
# closing and reopening the namespace around the external ones), the gif map and AdicionaGif after them (428 to 460),
# 6646 and 6608 at their records, 1591, 1767 and 3067 above 3064 (1530 to 1580) and 3063 after 6616 (1622), places the
# use bands were not read for; AdicionaNomeCargo and AdicionaRodapeConfira after MensagemErroCargo (806 to 820), 6624 at
# its record, 6626 and 6616 after 3064 (1603 to 1619), 6601 at 2950 and 6592 after AdicionaTelaQRCode (3121), which the
# use bands bound: in bands 2, 4, 11 and 12 the new members' ld_index runs as the target's indices do (6627, 6626, 6624,
# 6616, 6601 before 6595, 6594, 6592, 6587; 3074, 3064 before 3054; 1192 before 1190), but for 6643 before 6646 in band
# 2 (the gif map's tree member, which AdicionaGif at 428 mentions first, against 6646's record :964). Inverted pairs of
# ctelasvota.cpp.o's matched members (how-to step 3, "The order of two members"; ledger/ordinals.tsv's bands, the
# object's own function order): 571 at 0fb386d8, 998 at 7149483a; 487 new and 60 gone (CTextField's block members 12628
# and 12631 link earlier now). Three of the new are between two of this file's own functions: 13176 (NumeroDigitado) and
# 13137 (AdicionaInstrucaoTeclas's lambda) before 13527 in band 1, and 6643 before 6646 in band 2; every other has a
# template instance, a control block, a lambda's invoke or an exit destructor on a side. The object's fonts now hold
# FONTE_INSTRUCAO_TESTE_TECLADO, the {35, 0}, the {30, 1}, FONTE_TITULO, FONTE_VERSAO, FONTE_AGUARDE, FONTE_TECLA, the
# arrays, FONTE_NUMERO, TEXTO_CONFIRMAR_VOTO and FONTE_SUPLENTE in that order (wasm-objdump -x, segments 1 to 420),
# against the target's {40, 0}, {30, 0}, {20, 0}, "CONFIRMAR este voto", ...: their first readers in the target are
# 7787's and the unwritten builders'.
#
# The candidate's complete screens without substitutes and what they call. Scores: pnpm wasm score against the plain
# link before step 8, whole link at the tree's flags; frames compared on the object by their frame operands against the
# target's.
# - 6639 CTelasVota::CriaTelaCompletaCandidatoCom0 and 6681 CriaTelaConferenciaCandidatoCom0 (the strings
#   "CriaTelaCompletaCandidatoCom0" and "CriaTelaConferenciaCandidatoCom0" give the names, as 1767's does; both
#   declared in ctelasvota.h): adicionaBaseTelaCompletaCandidatoCom0 (6678) with the screen's name, then 6639 the
#   "CONFIRMAR este voto" keys' footer (AdicionaInstrucaoConfirmarVoto, 639) and the input control, 6681 the confira
#   footer, through GetFormularioProgresso ("telaCompletaCandidatoCom0", "telaConferenciaCandidatoCom0"). 25 over 258
#   and 19 over 199 rows, operand-only; matched at step 9.
# - 6678 adicionaBaseTelaCompletaCandidatoCom0 (records :822 and :827, column 15, which give the name and parameters):
#   code 9334 with MensagemErroCargo's "não é de candidato" when the post has no candidate's detail, 9335 with "com
#   número de suplentes incompatível" when it has substitutes (QtdSuplentes, 1157); then 4185 with 639, 2028 unless the
#   post is 25, and 4184 with false when the post has photos. That 25 is the conselheiro distrital is a reading (the gif
#   map at line 275 pairs it with conselheiroDistrital.gif); no evidence names a constant, and the literal is written.
#   19 over 84 rows, operand-only; at step 9 it reads `unresolved self-voted`: 4184's name rests on 6678's own call
#   vote while 4184 differs (below). It waits for 4184's match; no hand line names 4184 (its evidence would be that vote).
# - 4185 AdicionaDadosCandidato (no record; target callers 6660, 6671, 6678): the post's name by 12811 through
#   api::CFormBuilder's AddDoubleLineField (3068: (10, 60), (10, 95), the width + 237, FONTE_NOME_CARGO, background 1)
#   when the post has photos, else AddTextField (1191: (10, 60)); the number field (adicionaNumeroCandidato); the holder's
#   name, CDataText<comum::CCandidaturasDSNome>(0), on two lines at (10, 190) and (10, 215) to the width, FONTE_AGUARDE,
#   background 0, through AdicionaTextoDuasLinhas. That template and AdicionaTextoFonte are vota's now (they were the
#   anonymous namespace's; 1192's instances, over the internal DS_NomeCargoNeutroComEscolha, stay internal): binaryen
#   inlines the instance over CCandidaturasDSNome behind a 32-byte prologue, which needs it out of line in clang's
#   object, as an external template's linkonce instance is and an internal one with one call is not (a reading).
#   adicionaNumeroCandidato is an internal helper clang inlines: the target's frame holds its point (10, 115) and its
#   discarded field above 4185's own slots, as a clang-inlined helper's allocas give (42 over 413 rows with the call in
#   place, 22 with the helper, both operand-only, and with the call in place step 9 read the two points' frame offsets
#   apart). It calls
#   the AdicionaCampoNumero overload over a text source (CGrayedFramedText, comum::CCandidaturasDSNumero), which binaryen
#   inlines behind a 16-byte prologue. Matched at step 9.
# - 12811 NomeCargoCandidatoComEscolha (no record; no stub: its group is libc++; table slot 1088, which only 4185 loads):
#   the post's name for the current candidate's sex (CCargoDSNomeSexoCandidato(0, false), a named local: the target's
#   frame holds it above the name: 50 over 231 rows with a temporary, 2 inserted; 15 over 229, operand-only, with the
#   local) and, when the post has more
#   than one choice, " - " and the choice's ordinal, as DS_NomeCargoNeutroComEscolha does. Its first statement binds
#   CCargos::GetCurrent's result to a reference it never reads: the target calls GetCurrent (332) and drops the result
#   before the operator, and calls it twice more; that the source spelled that call so is a reading. Its file: use band
#   1 puts it beside 12812 and 12813, this object's CPreShowProgressBar block's members.
# - 2028 AdicionaSiglaPartido: the current party's abbreviation by comum::SiglaPartidoCorrente (11501, cpartidos.cpp;
#   table slot 1089) in "{}" at (10, 250), FONTE_AGUARDE, when the urna's parameters say to show the party
#   (CParametrosUrna::GetApresentarPartido, the byte at +396, 484 from CConfiguracaoEleicao::GetInst()), through
#   AdicionaTextoFormatado (a CDataTextFmt and a CTextField in the colours 2 over 1), which binaryen inlines behind a
#   32-byte prologue. It takes the point before the format: the target stores the point first and above the "{}"
#   string (33 over 230 rows, 5 inserted, with the format first; 13 over 225, operand-only, so).
# - 4184 AdicionaFotoCandidato(builder, bool) (no record of its own: :487 is adicionaFotoEmoldurada's, inlined in each
#   arm; target callers 6660 and 6671 pass true, 6678 false): the photo by adicionaFotoEmoldurada over
#   comum::CCandidaturasDSFoto(0) at (639, 35) in 161 x 225, and with the flag, below it, the post's abbreviated name for
#   the candidate's sex (CCargoDSNomeSexoCandidato(0, true)) in a {20, 0} temporary, centred (6528), at the photo's
#   centre and bottom + 1, or at (719, 261), the frame's own centre and bottom + 1, when the image is at most 1 wide (the
#   target calls 6528 in each arm, and 4181 does the same with (x + 55, 443)). Differs: 46 over 276 rows; on the object
#   the top two frame-slot groups (the photo's field result, the photo's point) come the other way round and the
#   photo's rectangle lies above the text calls' results. Not explained. Forms compiled at the tree's flags and read on
#   the object, none with the target's slots: the photo in each arm (written); the photo once above the flag (one text
#   call then, and the photo's code once); early return, or the plain arm first; a named font; one call over a computed
#   point; the text arms in an internal helper over the rectangle, by reference or by value; the named arm in an
#   internal helper (the closest: the top two groups as the target's, the rectangle still above), with the text arms
#   swapped or the rectangle passed on by value; adicionaFotoEmoldurada's field result named, default-constructed first,
#   or its rectangle returned directly.
# - 4129 vota::adicionaImagem<comum::CCandidaturasDSFoto> (target callers 4181 and 4184, which calls it twice):
#   adicionaImagem is vota's template now, out of the anonymous namespace: its instance over an external type is
#   linkonce, which clang keeps out of line as the target has it (in the anonymous namespace clang inlined it into
#   adicionaFotoEmoldurada, which then stayed out of line), and its instance over 6561's std::bind of a lambda stays
#   internal and inlined (6561 still matches). The source's byte stays a parameter only with a second value: the roots'
#   FotoSuplente stands for 4181's call. 7 over 125 rows, operand-only; matched at step 9.
# - 6528 vota::AdicionaTextoAlinhado<comum::CCargoDSNomeSexoCandidato>: AdicionaTextoFonte's body with the alignment
#   passed to CDataText (2 at both of 4184's calls, folded by binaryen). A template of its own, chosen: an alignment
#   parameter on AdicionaTextoFonte made 1192's two text calls two std::make_shared instances, and 1192 left match at
#   step 9 (6627 left the link).
# - 12641 CDataImage<comum::CCandidaturasDSFoto>::GetData: the link needs the source's call operator once 4129 builds
#   the image. It holds it inlined (ccandidaturas.cpp, beside GetCandidatoAtual, whose code it holds; ccandidaturasds.h
#   says what is chosen) with comum::CFotos::Posiciona (cfotos.cpp after GetImagem, a chosen place; cfotos.h says why):
#   the holder's or substitute's
#   code, and the photo when CFotos has it and its bytes begin FF D8 and end FF D9, read again for the result, else
#   empty. The four tests are at()s (the empty and one-byte images reach out_of_range's throw in the target), and the
#   two empty results are two return statements (with one, 51 over 258 rows, 9 inserted, 14 deleted; 23 over 249,
#   operand-only, so). Matched at step 9.
# - 11501 comum::SiglaPartidoCorrente: cpartidos.h says what places it and what is chosen; GetInst's result is held
#   before the call, as the target reads it before the format string and calls GetCurrent after (73 over 281 rows with
#   GetInst in the argument, 16 over 261, operand-only, held).
# Their lines are chosen: the helpers at 495 to 587, after adicionaFotoEmoldurada and inside the file's run of internal
# records (the anonymous namespace closed around them); 6678 at its records (816 to 840, the run 748 to 815 moved up
# five lines for it, no record there); 6681 at 1522 and 6639 at 1603 (6626, 6616 and 3063 moved down nine lines), the
# places use band 2 bounds: 6689, 6681, 6678 (deferred, after 6681), 6646 (after 3067), 6639, 6626 and 6616 run so in
# names.tsv's ld_index, the target's order (docs/how-to-decompile.md step 3, "The order of two members"; the other
# pairs of the new members are with template instances, counted apart). 12811 takes the place of its first mention,
# 4185's address-take, whatever its line: written
# below 4185's own line or at the file's end, the link is byte-identical (sha256). There it reads before CTelasVota's
# statics' destructors 12862, 12875 and 12882 and the lambdas 13023 and 12903 in band 1, five inverted pairs, which
# 4185's band-3 place (before 4161's AdicionaLocal) keeps. Their names, their linkage (external for 4185, 4184 and 2028,
# so the roots reach them; no record shows it) and AdicionaCampoNumero's overload over a source are chosen too.
# - 2384, 6689 and 13441 are unit 387's since (its fragment).
# Roots: 378-uenux2-ctelasvota-criatela-roots.cpp stands for 7787 (its calls of 6639, 6681 and 2028 too), for 6602, 6603
# and 6605 (3060's other callers, and 2028's calls for 6602 and 6605), for 6660 and 6671 (4185, 4184 and 2028:
# BasesCompletaCandidato) and for 4181 (its call of 4129: FotoSuplente).
# Stand-ins this unit made idle went, call by call: units 28 (1192's CTextFieldDoubleLine), 191 (6627's vector copy),
# 232 (3074's GetDetalheConsulta), 309 (6601's AdicionaLocal), 88 (12587's GetNomeNeutro), 110 (6592's
# AdicionaTelaQRCode), 92 (the CMaskedTextField blocks' builders and sinks), 102 (the CPreShowProgressBar, CMovie and
# CMovieField blocks), 23 and 52 (their roots files), 173 (its roots file), 100 (the GetInst call that stood for 5543)
# and 373 (1591's call of 2383); the other units' comments name the callers now in the link (units 120, 165, 212). The
# scan with the last of them gone (100, 373, the third call of 3060) changed nothing step 9 reports against the one
# before (0 matches added or renamed, no status or stub file written). The complete screens' members made more idle,
# and they went with them: units 28's and 29's roots files (CTextFieldDoubleLine's and CImageField's constructors'
# stand-ins for 4185 and 4129), unit 79's three CDataText stand-ins for 4185 and 6528 and its CDataTextFmt one for 2028,
# unit 88's Ordinais (2258 for 12811), unit 109's Imagens and ConstroiFotos and one call of Fotos (12641), unit 120's
# FormInterativoB (554 for 6639 and 6681); units 92's, 129's and 212's comments name the callers now in the link.
# Idle too, and removed when the screens were merged onto the stage that held their files: unit 102's roots' builders
# and sinks for CDataText over CCandidaturasDSNumero, CCandidaturasDSNome and CCargoDSNomeSexoCandidato and CDataImage
# over CCandidaturasDSFoto (4185, 6528 and 4129 store the vptrs), and unit 89's roots' CandidaturasAtuais (2838 for
# 12641); a link with each file's back moved no row.
$(ROOT)/$(APP)/378-uenux2-ctelasvota-criatela-roots.o: $(ROOT)/src/units/378-uenux2-ctelasvota-criatela-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/378-uenux2-ctelasvota-criatela.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/378-uenux2-ctelasvota-criatela-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/378-uenux2-ctelasvota-criatela-roots.o
