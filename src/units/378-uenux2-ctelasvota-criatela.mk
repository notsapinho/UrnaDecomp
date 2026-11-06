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
# api::CMovie::ProximoFrame 5525 (unit 23's). Written, not matched: 6624, 6627, 6608, 1591, 3060 (with 5535 inlined)
# and 3076 (below).
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
# - 3060 (AdicionaCampoNumero<api::CGrayedFramedText>) differs, 13 over 131 (4 rows inserted): the target calls 5535,
#   CGrayedFramedText's constructor, which keeps two callers there (3060 and 4185); 4185 is not written, so our 5535
#   has one call site and binaryen inlines it (the inserted rows are CFramedText's call and the vptr store). It waits
#   for 4185 or a stand-in for its call of 5535 (not measured here).
# - 3076 AdicionaGifCargo(const comum::md::CCargo &, api::CFormBuilder &): the post's gif from a static
#   std::map<comum::TCargoID, std::string> @1833400 (nine pairs through 1444; its exit destructor is 13471, which reads
#   no-candidate), a copy of the movie added at (640, 480) through 5543. It differs, 77 over 562 rows (75
#   operand-only: frame slots and the map's guard and data addresses). Not explained. Its name is chosen.
# - 5543 and 5525: unit 31's and unit 23's fragments; 5543 holds CMovieField's constructor inlined (unit 52's file),
#   whose timer lambda calls the callback AvancaFrame (11056's body).
# Error codes (app/vota/euevotaerror.h): 9354, 9341 and 9344, names chosen from the screens.
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
# Not written, with what each waits for (the pick's list for this class):
# - 6639, 6681 need 6678, which calls 4184, 4185 and 2028 (4184 calls 4129 and 6528; 11501, reached through its table
#   slot 1089 only, has no direct caller in ledger/callgraph.tsv), 7787's builders' callees.
# - 2384, 6689 and 13441 are unit 387's since (its fragment).
# Roots: 378-uenux2-ctelasvota-criatela-roots.cpp stands for 7787, and for 6602, 6603 and 6605 (3060's other callers).
# Stand-ins this unit made idle went, call by call: units 28 (1192's CTextFieldDoubleLine), 191 (6627's vector copy),
# 232 (3074's GetDetalheConsulta), 309 (6601's AdicionaLocal), 88 (12587's GetNomeNeutro), 110 (6592's
# AdicionaTelaQRCode), 92 (the CMaskedTextField blocks' builders and sinks), 102 (the CPreShowProgressBar, CMovie and
# CMovieField blocks), 23 and 52 (their roots files), 173 (its roots file), 100 (the GetInst call that stood for 5543)
# and 373 (1591's call of 2383); the other units' comments name the callers now in the link (units 120, 165, 212). The
# scan with the last of them gone (100, 373, the third call of 3060) changed nothing step 9 reports against the one
# before (0 matches added or renamed, no status or stub file written).
$(ROOT)/$(APP)/378-uenux2-ctelasvota-criatela-roots.o: $(ROOT)/src/units/378-uenux2-ctelasvota-criatela-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/378-uenux2-ctelasvota-criatela.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/378-uenux2-ctelasvota-criatela-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/378-uenux2-ctelasvota-criatela-roots.o
