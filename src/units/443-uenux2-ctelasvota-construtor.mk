# Unit 443: no source of its own. It adds to unit 110's app/vota/eleitor/comum/ctelasvota.cpp and ctelasvota.h
# vota::CTelasVota::CreateInst and the class's constructor, which target fn 7787 (not written; unit 441's fragment has
# what it holds) holds inlined from +0x1674f, every screen the constructor builds that no unit had written, each as
# real code, and CInfoEleitorAudioHabilitado::LarguraMaxima; the CREATE_INST macro (ecourna's api/pattern/singleton.hpp)
# with the pattern code 1304 (epatternerror.hpp); eight vota error codes (app/vota/euevotaerror.h);
# api::CFormBuilder::AddRect over a rectangle made public (api/gui/cformbuilder.h); and api::IForm<api::IScreen> as the
# pointee of m_form in app/vota/eleitor/iniciovotacao's cgerazeresimabase.h, cgeraresumozeresimabase.h and
# ciniciovotacao.h, the type of the CTelasVota members they copy. Its stand-in is unit 441's roots, which call
# CreateInst once, as 7787 does. Paths relative to src/uenux2 unless named; offsets are in 7787's body (pnpm wasm fn
# ../target/vota_web_wasm.wasm 7787; its piece build/out/splat/pieces/asm/comum/7787.wat).
#
# Evidence: the records 7787's region holds (ctelasvota.h has the members', the getters' and the types' evidence):
# - CreateInst, record :3435 column 45 ("CTelasVota - instancia ja criada", pattern code 1304): a 16-byte prologue at
#   +0x1674f, the lock of GetInst's mutex, the test of s_instancia, `new` of 252 bytes, the constructor, the old
#   pointer's destructor (fn 6548) and the unlock (fn 150). Written as CREATE_INST(CTelasVota, s_mutex, s_instancia)
#   on the line after GetInst's, whose `)` falls on the record's column; the macro and its name are chosen
#   (singleton.hpp says what the records of CCargos's and CInfoMTLCD's CreateInst give).
# - The constructor, record :3502 column 19 ("Tipo de cargo nao identificado", code 9357): its 96-byte prologue at
#   +0x1676d, then the screens, the posts' loop and the vote-recording screen in the order ctelasvota.h gives.
# - CriaTelaInputVazioProporcional (:1392 and :1397, codes 9348 and 9349, the second below two digits),
#   CriaTelaInputVazioMajoritarioCom0, Com1 and Com2 (:1413, :1428, :1444; 9350 to 9352) and CriaTelaInputVazioConsulta
#   (:1460, 9353), each record a CUeVotaError over MensagemErroCargo's text (fn 690), and CriaTelaPartido (:1741,
#   9355), the party's number over comum::NumeroPartidoCorrente and the candidate's digits after it, its form built
#   without the progress bar (GetFormularioProgresso's false, as the vote-by-party screens of unit 441).
# - CriaTelaZeresimaTardia, record :2382 column 21, api::CPolySingleton<api::IScreen>::instance()'s default argument
#   (the `auto&` the screen reads the monitor through), and LarguraMaxima, record :3618 column 12 (ctelasvota.h): the
#   width of "Áudio ativado" in FONTE_AGUARDE, which CriaTelaInstrucoesAcessibilidade holds inlined by clang.
# The other screens have no record: CriaTelaFimDosTrabalhos to CriaTelaQuerReimprimirZeresima, read from their bodies
# (their texts, points, fonts and form names, in the target's order); their names are their forms' ("telaFimDos
# Trabalhos" gives CriaTelaFimDosTrabalhos), chosen. Two callbacks they pass are functions of their own, both match:
# 13012 TextoAlertaDesligamento (table slot 1102, the seconds left before the shutdown time, never below 0, through
# std::vformat: named by its slot and its string) and 12974 TextoLimiteCopiasBU (slot 1105, "O número máximo permitido
# é " and GetQuantidadeMaximaBUsAdicionais: named by its string); both names chosen, in the anonymous namespace. The
# five CriaTelasCargo* (one per kind of post, each a 48-byte prologue: ctelasvota.h) hold the posts' std::map; the
# keys are ETelaVotacao's, the two pairs of repeated-choice screens only when the post takes more than one choice and
# may not repeat (CCargo::GetQtdeEscolhas, PodeRepetir), over two arrays (TEXTO_CANDIDATO_REPETIDO,
# TEXTO_NUMERO_REPETIDO, chosen names; step 8 places them by content).
#
# Choices:
# - AdicionaNumeroPartido (CriaTelaPartido's number field) and AdicionaCampoRotulado (CriaTelaEmitirMaisBU's labelled
#   field) are free functions of vota with external linkage, chosen names: the target has a prologue of each inside
#   the screens (16 bytes at +0x1cfde, 48 at +0x1ad2b), which a function clang keeps out of line and binaryen inlines
#   gives. Internal, clang inlined both and the two frames went (the frame list below, measured). AdicionaNumeroPartido
#   holds its two objects as std::shared_ptr<X>(new X), each converted after: the target's RTTI names those control
#   blocks, __shared_ptr_pointer<X*, shared_ptr<X>::__shared_ptr_default_delete<X, X>> for the CDataTextFmt and the
#   CMaskedTextField<CFramedText> (@479470, @479808), and 7787 is the one builder of each (units 79's and 92's roots).
#   A SharedIText and a SharedField over the new-expression gave blocks of two other types, in our link beside the
#   target's (from those units' stand-ins), and data that put carquivossavd.cpp.o's .bss on the target's addresses
#   (below).
# - FONTE_VERSAO's definition moved above its first reader (CriaTelaReimpressaoBU), AreaTela and AdicionaTexto below
#   theirs, unit 441's record-less screens (lines 1461 to 1522 and 1530 to 1561) to 1470 and 1533, all in blank lines,
#   every record line kept (TMPDIR=/tmp make -C src check-srcloc). The new screens' places are the free runs between the
#   records; FONTE_TECLA_ACESSIBILIDADE ({25, 1}) is a constant of the file, a chosen name.
# - AddRect over a rectangle was private, a choice: CriaTelaZeresimaTardia calls it (a 16-byte prologue of its own at
#   +0x174a1, the CRectField of colour 2).
# - Codes 9348 to 9353, 9355 and 9357: names chosen (euevotaerror.h); the values are the target's constants.
#
# Measured:
# - The region's frame list (each stack-pointer prologue, `i32.sub` and `i32.add` of a negative size alike, in order)
#   against our unit 441 stand-in, CreateInst and everything under it inlined (55629 bytes; the region +0x1674f to
#   +0x24132 is 55779): 48 frames each side, sizes 16 96 96 80 96 16 80 64 464 80 64 144 192 64 80 48 64 48 48 48 48 80
#   48 64 80 16 48 32 48 32 48 32 48 48 48 48 48 48 48 48 48 48 32 48 48 32 48 32 in the target, the same in ours but
#   the 16th, AdicionaCampoRotulado's, 64 against 48. The target allocates the api::CTextField's control block (76
#   bytes) before the CFixedText's (32) and builds the field without fn 1918's null test of the text, a constructor of
#   CTextField over the text that our api lacks (a reading, not written); ours makes the CFixedText first.
# - The rows (steps 7 to 9, against the merge of unit 441): 12974 and 13012 match; 11371 (unit 299's
#   CConversorEleicaoPE::DoDesconverte) matches too, its constant at +0xad4 the "o" tail of "em caso de falha na
#   impressão", a literal of CriaTelaVerificaQualidadeBU, where the target holds it (it read `string tail occurs 4098
#   times` before). In band 1 the two callbacks are in 2 inverted pairs each, the fewest any place in the object gives.
# - Lost against the base: 5546 (AddTextRectField) reads `no-candidate`: unit 31's TextoRetangulo, the stand-in for
#   7787's two calls of it, passes its own {35, 0} beside CriaTelaNumeroCopiasErrado's FONTE_TEXTO_CONFIRMA_CORRIGE, so
#   binaryen keeps the font a parameter; a link without TextoRetangulo (its function, constant and sink) gives 5546
#   `match`, the stand-in idle now (unit 31's roots are another branch's file: no landing without it, how-to step 9).
#   10879 reads `unresolved self-voted` (ESCAPES.2's vote from 14478 rests on where our strings fall: facts/splat.md
#   §S10 item 30), the loss the user allows. With the helper's blocks of the other types, 1164 (CArquivosSavd::GetInst),
#   11657 and 11658 (its statics' exit destructors) left `match` too: our data moved the .bss after this object by
#   0x1000, which put carquivossavd.cpp.o's s_mutex and s_instancia at the target's own 0x1c0db8 and 0x1c0dd0; step 8
#   casts no vote for an address both layouts share and a .bss object has no content to place it, so their two lines
#   went, and the two put back on a copy of splat/symbol_addrs.txt gave the three `match`. With the target's types they
#   sit 0x2d0 below the target's, voted, and the three match: a .bss name voted by one pair rests on our address not
#   being the target's.
# - Header edits: the tree's 1083 objects compiled with them; all but ctelasvota.cpp.o and unit 441's roots object are
#   cmp-equal to the base's.
#
# Stand-ins this unit made idle went, each in a commit of its own, with steps 7 to 9 moving no row: the roots files of
# units 378 (TelasVotaConstrutor), 120, 108, 212, 354, 373, 387 and 90, and unit 125's HoraFormatada (779), 150's
# TelasCargo (2386), 296's CodigosResumidos (2792), 309's Locais and TelasNeutras (4161, 2380), 79's
# TextoFormatoConstProprio (the CDataTextFmt block) and 92's MolduraEm, CampoNumeroA and the mask block's builder and
# vtable sink: each stood for 7787's calls of a callee that 7787 calls in CreateInst's region only (pnpm wasm fn's calls
# from +0x1674f to +0x24132), and unit 441's roots now make as many (each of those 71 callees, counted over both
# readouts). Unit 232's stand for 7787's calls before the region and stay. Idle too, in roots files another branch
# changes, so not edited here: unit 31's TextoRetangulo (5546, above), BarraProgresso's call for 7787 and TelaA's and
# TelaB's calls for 7787's adders; the comments of units 88's, 89's, 98's, 109's, 110's, 154's and 165's roots name 7787
# beside a callee only the region calls (not read further).
