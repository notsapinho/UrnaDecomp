# Unit 387: no source of its own. It adds members to landed units' files (src/units/README.md "Landing a unit" item 2):
# unit 110's app/vota/eleitor/comum/ctelasvota.cpp (and ctelasvota.h), unit 31's api/gui/cformbuilder.{h,cpp}, unit
# 156's app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.cpp (whose -pending.cpp goes with its last trap) and the
# header api/gui/cmaskedtextfield.h; its roots stand for vota::CTelasVota's constructor (target fn 7787, not written).
# Scores are `pnpm wasm score` against the plain link (ours from build/out/wasm-map/vota_web/names.tsv), whole link at
# the trees' flags; "operand-only" means rows that differ in calls and data addresses alone.
#
# The input fields of the empty-input screens, in ctelasvota.cpp:
# - vota::AdicionaCamposInputVazio (target fn 2384, no record). Evidence, its body: AdicionaImagemAudioHabilitado (6689)
#   at (176, 445); the text callback 13424 (table slot 1087) through api::CFormBuilder::AddTextField over a function (fn
#   1191) at (10, 445) in the {25, 0} font (@474992, FONTE_AGUARDE), left-aligned; vota::AdicionaCampoNumerico (fn 2383)
#   with the length digitos, the flags 0 1 0 1 0, the point (x, y), the {40, 0} font (@474880, FONTE_NUMERO) and
#   alignment 0, its field kept to the end; and, when digitosRestantes is not 0, CFormBuilder::AddMaskedTextField
#   (below) of "" with that length at (the field's Rect().right + 5, y) and FONTE_NUMERO. Its one target caller is 7787,
#   five times, each call right before the throws of one CriaTelaInputVazio* screen 7787 holds inlined (records
#   ctelasvota.cpp:1392 and 1397 Proporcional, 1413, 1428 and 1444 MajoritarioCom0 to Com2, 1460 Consulta; the folded
#   readout of `pnpm wasm fn ../target/vota_web_wasm.wasm 7787`): the name is chosen after them. With the masked field
#   built by a helper of ctelasvota.cpp, 134 over 363 rows: the target keeps the "" temporary's destruction after the
#   helper's call (its long-mode byte at +31 tested, the buffer freed), which clang drops when the helper is in this TU
#   and only reads its parameter, and keeps the temporary's address in a local where the target folds it into the loads;
#   with a test copy of the helper, a free function, in cformbuilder.cpp's TU, 17 over 353, operand-only; as landed, the
#   member below, 17 over 353 before steps 7 to 9, operand-only, and it matches, named by the content pass.
# - vota::AdicionaImagemAudioHabilitado (target fn 6689, no record; its stub was in src/uenux2/unplaced.cpp): an
#   api::CDataImage<std::vector<uebyte> (*)()> over 13441 (slot 1086; the RTTI spells the instantiation) in an
#   api::CImageField at the point given, ANCHOR_TOP_LEFT (0), added and returned: adicionaImagem's shape (this file)
#   with another anchor and its source fixed. Target callers 2384 and 7787, which puts it at the width of "Áudio
#   ativado" in the 25-point font plus 20 (the screen's slot 32, under the record of
#   CInfoEleitorAudioHabilitado::LarguraMaxima, ctelasvota.cpp:3618, inlined). Matches: 8 over 125 before steps 7 to 9,
#   operand-only; step 8 names it by vptr-anchor.
# - vota::ImagemAudioHabilitado (target fn 13441, no record; its stub was in api/gui/cfixedimage.cpp, placed by the vptr
#   of the temporary it destroys): with the audio on (vota::CEstadoAudio::GetInst().Ativo(), mode +4 not 2) the bytes of
#   api::CFixedImage(":/resource/images/audioHabilitado.jpg") (fn 2246, its GetData and destructor inlined: the vector
#   at +4 copied, the vptr @1530272 stored), else ecourna's CStringUtils::HexStringToBytes (fn 3506) of a 1x1 bitmap's
#   132 hex digits (@357998). Its one reference is slot 1086, which 6689 stores. Matches: 17 over 163, operand-only;
#   named by 6689's table vote.
# - vota::TextoAudioAtivado (target fn 13424, no record): "Áudio ativado" (@137480, 13 bytes) with the audio on, else
#   "". Its one reference is slot 1087, which 2384 and 7787 pass to fn 1191. Matches: 4 over 34, operand-only, by the
#   content pass.
# - Places: 2384 links right before 2383 in use band 5 (target indices 2384 > 2383 > 2380 > 2376 > 2369, all this
#   object's), so it is defined above AdicionaCampoNumerico (line 792), which a forward declaration above it names; that
#   2384 is external is a reading of that order (an internal function first mentioned by 7787, far below, would take
#   7787's place). 6689 lies in band 2 above 6646 (adicionaBaseTelaVotoBrancoCandidato, first mentioned at line 1570),
#   so before it. They take lines 753 to 775 of the run above AdicionaCampo (6689, the declarations, 2384), lines
#   chosen. 13441 and 13424 lie in band 1 between 13527 (the gif map's exit destructor, line 428) and 13176
#   (NumeroDigitado, line 300): every place in the file inverts one pair or more, and above line 300 the fewest, two
#   (13527 against each), where after line 428 four (13176 and 13137 against each) would; they take lines 248 to 264 of
#   the run above AdicionaGifCargo (placing.md P9: the fewest pairs among the file's own functions), lines chosen. The
#   two includes they need (api/gui/cfixedimage.h, cfixedtext.h) took two blank lines of that run. Counted per use band
#   as docs/reference/facts/placing.md P9 says, over `wasm-objdump -x -j linking` of the base's object (compiled at
#   8f35addb) and this one, a function's position its index in the symbol table: pairs between the file's own functions
#   33 at 8f35addb and 35 here, the two new 13441 and 13424 before 13527; pairs with a linkonce copy on one side 320 and
#   386, three of the new ones these four's (CFixedImage's D2 8563 before 13424, GetData 4975 and the gif map's 6643
#   before 6689).
# - Chosen: the four names, their being free functions of vota with external linkage (6689 a roots target; 13441 and
#   13424 as NumeroDigitado), the parameters' names and types (size_t for the lengths, as 2383 takes them), 2384's field
#   a named local, and the lines.
#
# CFormBuilder::AddMaskedTextField (no target index: binaryen inlines it into 2384, behind a 16-byte prologue, the
# field's copy for AddField), in cformbuilder.cpp after AddProgressBar: a CMaskedTextField<CFramedText> over a
# CFixedText of the text (alignment 0); the font, ctelasvota.cpp's @474880, is a parameter dead-argument elimination
# folds, as AddTextRectField's (a reading). The mask takes its alignment from the text inside the field's constructor
# (slot 3 called after the vptr store, right before fn 1385), a second constructor in cmaskedtextfield.h. Evidence for
# another TU than 2384's: the destruction above; its place among the CFixedText adders, its name, membership and
# parameters' order are chosen (cformbuilder.h).
#
# The certificate's screen:
# - vota::CMostraQRCodeCertificado::StartState (target fn 12040, slot 2 of its vtable, no record): the form from
#   vota::CTelasVota::CriaTelaQRCodeCertificado over the callback 12039 (a std::function of the function pointer, slot
#   1529, by value), moved into +28, its slot 2 (IForm's Slot2, shown), `this` next. The screen (ctelasvota.h has its
#   evidence) is a static member called through CTelasVota::GetInst(), whose result 12040 drops: as a const member, 204
#   over 873 rows, the locals renumbered, and static, 47 over 853, operand-only, the measurement
#   docs/reference/facts/codegen.md C4 gives, reproduced here. Its "Certificado digital" is a named array of
#   ctelasvota.cpp (TEXTO_CERTIFICADO_DIGITAL, a chosen name): the target loads it at @475040 with `i64.load align=3`,
#   16-byte aligned between the {20, 1} font (@475032) and TEXTO_ERRO_TESTE_TECLADO (@475072); with the text a literal,
#   ours loaded it `align=0`; the version line's y (the area's bottom - 80) is a local declared above the version's
#   text, which the target computes ahead of it. Matches: step 8 names it by content-anchor.
# - Its callback (target fn 12039, no record; slot 1529 only): api::CStringUtils::JuntaTags (fn 3646) of the first list
#   CEstadoGeral::GetDadosQRCodeCertificado (fn 5634) returns with false, over CAppInfo::GetInst() (185) and GetGeral()
#   (291), the outer vector destroyed (fn 5980) before JuntaTags. The copy of the first list comes from a file-static
#   helper clang inlines: with the copy a named local, 26 over 208 (the outer vector at +4, the copy at +16, the target
#   the other way round); with the helper, whose temporary takes the place above the caller's
#   (docs/reference/facts/codegen.md C5), 12 over 208, operand-only. Matches since 5634 is named (below); named by
#   12040's table vote.
# - Places: use band 1 holds 12042 and 12041 (the statics' exit destructors), 12040, 12039 and 12038 (ProcessInput,
#   record :39), in that link order, so StartState is defined above line 36; the callback's internal linkage is a choice
#   (external, the object's order is the same), declared in an anonymous namespace above StartState and defined after
#   ProcessInput: its first mention, in StartState, puts it
#   between the two (how-to step 3). The lines above line 39 are a layout of ours: the three includes and StartState
#   took the blank lines between the functions there.
# - Chosen: the callback's and helper's names, their linkage and lines, `front()` for the first list, StartState's
#   lines.
#
# 5634: its target callers are 12039 and 12110 (not written), and its body (unit 215's) differs: 52 over 963 rows. Step
# 8 names it `call by:12039` alone, which the build refuses as self-voted, so a `callers+content` hand line in
# splat/symbol_addrs.txt names it from its own body: the one target function that loads the tail @1226 ("{}:{}"), alone
# on its depth-0 fingerprint, addr and shape hashes, with two calls of 5635; its comment has the commands. Weighed by
# removal on copies (docs/reference/splat.md "Reviewing a match"): without the line, 12039 is unresolved self-voted and
# splat-build refuses it (UNCONFIRMED), and with 12039's match line out the build refuses 12040 too (self-voted on
# 12039's name, which 12040's table store alone votes for); nothing else moves. It goes when a generated vote of
# another holding match (12110's, once written) repeats it, weighed by removal.
#
# Stretch, not worked further: vota::CTelasVota::CriaTelaMaisInformacoes (6599, unit 110's, differs): 306 over 2151 rows
# in this link (278 operand-only, 14 inserted, 14 deleted; the rows beyond operands are loads at +76 and +12 through
# locals numbered and ordered otherwise), not explained.
#
# Roots: 387-uenux2-ctelasvota-audio-certificado-roots.cpp stands for 7787 (2384 twice, 6689 once). Stand-ins this unit
# made idle went, call by call: units 29 (CampoImagemA, for 6689), 31 (TextoMultiLinha's call for 12040), 79
# (ImagemDaFonte for 6689, ImagemQRCodeCompartilhada for 12040), 120 (RotulosB, for 12040), 158 (ImagemFixaEm, for
# 13441), 165 (FormulariosVota: 576's callers in the link but 7787, for which FormularioVota stays), 220
# (ChamaCertificado, for 12039) and 373 (the call for 2384), each a call whose target callers are all in the link now;
# unit 156's -pending.cpp went with its trap. In the same link no row left match: how-to step 9's join against 8f35addb
# prints this unit's six rows and 5634's (no-candidate to differs, named now).
$(ROOT)/$(APP)/387-uenux2-ctelasvota-audio-certificado-roots.o: $(ROOT)/src/units/387-uenux2-ctelasvota-audio-certificado-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/387-uenux2-ctelasvota-audio-certificado.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/387-uenux2-ctelasvota-audio-certificado-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/387-uenux2-ctelasvota-audio-certificado-roots.o
