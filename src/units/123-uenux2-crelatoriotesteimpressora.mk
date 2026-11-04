# uenux2 comum::CRelatorioTesteImpressora, the printer test report, in src/app/comum/relatorios/: its overrides in
# crelatoriotesteimpressora.cpp (the file of its records), the class in crelatoriotesteimpressora.h, its base
# comum::CImprimirExtratoCarga in cimprimirextratocarga.h with its one out-of-line member in cimprimirextratocarga.cpp, and
# the callee comum::CRelUtil::GetSeparadorFase in crelutil.cpp (its record's file) with crelutil.h and
# euecomumrelatorioserror.h, the error it throws; and CRelUtil's IncluiCabecalhoEleicoesMZS (with the std::sort it
# instantiates and CPleito's copy assignment), ImprimeResumoCorrespondencia, ImprimeSeparadorFase, GetIDCargaFormatado,
# IncluiAvisoModoDemonstracao,
# DSCodigoVerificador and FormTituloPartido and the file's internal TituloPartido in crelutil.cpp (below).
#
# Matched: the overrides TemHorarioVerao, EhTreinamento, GetHorarioVerao, EstaEmHorarioVerao, GetCorrespondencia,
# GetCabecalho, EhEleicaoComunitaria, EhModoDemonstracao, GetNomeEleicao, GetPleito, GetTipoUrna, GetUF, GetTitulo,
# GetMensagemEncerramento, GetMensagemCondicoes and GetSeparadorFase (target fns 11202, 11201, 11199, 11198, 11197, 11195,
# 11194, 11193, 11192, 11191, 11190, 11189, 11187, 11186, 11184, 11183: slots 3, 2, 7, 8, 9, 11, 12, 22, 13, 14, 17, 16,
# 21, 18, 19, 20 of the vtable @1576652); the base's ImprimeDataHoraEmissao (11216, slot 25); CRelUtil::GetSeparadorFase
# (1919, record crelutil.cpp:554:23) and CBaseError<EUeComumRelatoriosError>'s constructor (580, the thunk of binaryen's
# 710 for that enum); and three libc++ instances InicializaTradutorFrase brings, from this unit's object:
# pair<const char, CLabelParametrizado>'s constructor from a char and a label (1552) and its copy constructor (5793), and
# the label map's __assign_multi (5794, found by content; its target callers are 11196 and 7787, and it holds the address
# of CTradutorFrase's map). The map's __tree::destroy (1706), matched before from ctradutorfrase.cpp.o, comes from this
# object now, which links first. The base's GetConteudosQRCodeAdicionais (slot 6) is the body of 902, whose match line
# it takes over from RHVoice's language_info::get_country, a twin.
# - EstaEmHorarioVerao (11198) tests the date of api::CDateTime::Now() (fn 479) against the CHorarioVerao of CHV through
#   comum::md::CHorarioVerao::Contem, out of line in chorarioverao.cpp (unit 147, which has the two forms measured).
# - GetCorrespondencia (11197) calls CDadoCorrespondencia's copy constructor, fn 1249 in the target, which has landing
#   pads (invoke_iii), so the target's copy is an -fexceptions object's, and ours, from this unit's object, differed from
#   it (188 over 232 rows). 1249 matches since mock/app/comum/cappinfobuilder.cpp's object, at the executable TU's rule
#   and ahead of this one, gives the link's copy (unit 253); the callers+content hand line that named 1249 from its body
#   and from 11197's call, on which 11197 (3 over 9 rows, all operand-only, with the roots' stand-in for 1249's other
#   callers) matched, went then, carrying no row.
# - ImprimeDataHoraEmissao (11216) prints "EMISSAO DO RELATORIO" and one std::format line of the date and the time, from
#   api::CDateTime::FormatCurrentDate and FormatCurrentTime (fns 5472, 5473, unit 125's callbacks, which match at the
#   tree's -O3 with their callees 706 and 779). The four
#   strings of the second line (the two formats and the two results) are destroyed after its call, the last built first,
#   which reads as one statement holding the format and both calls, as written; other forms were not linked. The style 1
#   and the alignments 2 and 0 are the constants the target passes (IPaper::EStyle has no enumerators, ipaper.h).
#
# InicializaTradutorFrase (11196, slot 10) matches, with the map's initializer-list constructor (fn 5795) that this
# object instantiates for it: it builds a std::map<char, CLabelParametrizado> of the four labels of
# CConfiguracaoEleicao's CParametrosUrna ('M' municipio, 'Z' zona, 'S' secao, 'P' partido) and hands it to
# CTradutorFrase::SetLabels (ctradutorfrase.h). The target calls that constructor, which holds the insertion inlined;
# at -O2 clang inlines it into 11196, 281 over 345 rows (`unresolved` on the insertion's
# __emplace_hint_unique_extract_key, which the target has inside 5795), and at the tree's -O3 with 11196 its only
# caller binaryen does (212 over 453 in the whole link). With a second caller standing for 7787, the target's other
# one (the roots' w123_mapa, below), 11196 scores 20 over 289 and 5795 1 over 172, all operand-only, and both match;
# 11196's body did not change. The list handed straight to the setter keeps the constructor out of line at -O3 too, in
# a probe object; it was not linked.
#
# GetConteudoQRCode (slot 5, target fn 11200) matches: a comum::CQRCodeDS of CAppInfo's general state's
# GetDadosQRCode (5636), SetOrigem(eOrigemImpressora) (5783, the 1 the target passes) and its call operator (5782), all
# fragment 299's, which has the evidence for the class; 12 over 168 rows before steps 7 to 9, all operand-only. The
# named local and the temporary sit where the target's frame has them (+20 and +8). It is defined between EhTreinamento
# and GetHorarioVerao, the order of target indices below. The -pending.cpp, which held its trap, went with it.
#
# comum::CImprimirExtratoCarga::Imprime (target fn 5591) is written in cimprimirextratocarga.cpp and matches:
# src/units/296-uenux2-relatorios-impressao.mk has it, and its roots keep its stand-ins.
#
# comum::CImprimirExtratoCarga::Imprime (target fn 5591) is written in cimprimirextratocarga.cpp and matches:
# src/units/296-uenux2-relatorios-impressao.mk has it, and its roots keep its stand-ins.
#
# The constructor (target fn 5586, no record; at the file's top, a chosen line: it is in use band 2, apart from the
# slots' band): the general state's urna type for its turn (GetTipoUrna, inline) against eUrnaContingencia; then, when
# CPE::Existe (2788) says no instance, CPE::CreateInst(geral, FLASH_INTERNA) (2787, unit 110); then, when CPE's processo
# holds a second pleito, that pleito's date against a default api::CDate, today (1382): operator== inline, then <
# through operator<=> (1261, unit 125). The flag is stored false first. The byte at +4 is stored 0 before the vptr, the
# base's member (cimprimirextratocarga.h), and +5 is the flag. CPleito::GetData (cpleito.h) is added for it. Its two
# target callers, 11869 (not written) and 11911 (unit 296's, in the link), read its returned this: unit 280's roots
# stand in for 11869. It
# matches: 9 over 99 rows, all operand-only, before step 8 (11 over 99, the result's row deleted, with no reader).
#
# GetDadosLocal (slot 15, target fn 11188): the lines of the section's data, in a vector of strings. For a voting urna
# (eUrnaVota, eUrnaContingenciaVota, eUrnaContingenciaVotaRecupera) it adds "Local ... {:04}" of CLocal::GetLocalID in
# the official phase, calls the InicializaTradutorFrase slot (10), then the section's line, PreencheADireita of the
# translated "<SCSN>" to 34 and "{}{:04}" of GetSecaoID, then, when the section has aggregated sections
# (CLocal::GetQtdAgregadas, 2816, unit 89), their count's line "{:<33s} {:04}" and FormataAgregadas (5738, unit 89) of
# the translated "<SCPN> agregad<S|os|os|as>: {}", then the place's type and "Local com biometria"; last, for every
# urna, "Tipo de alimentaÃ§Ã£o". Every literal, padding width and format is the target's; the strings the target
# destroys only at the end of their block are named locals, and those destroyed right after the push_back are
# temporaries (frame slots read off 11188's rows), as written. The three parameter lines are one inlined helper,
# FormataParametro (the name's copy, then PreencheAEsquerda of the value to 38 less the name's size, the constants the
# target passes: 25 and 19), cgeradorrelpu.cpp's AdicionaParametro's line; ConverteTipoLocal (CLocal::GetInst again,
# CLocal::GetTipoLocalVotacao, its four types and "InvÃ¡lido") is shaped after the record's ConverteTipoAlimentacao (line
# 173, CPolySingleton<IPower>::instance()'s default std::source_location at column 20, `auto& ipower = ` before it, the
# idiom of cthreadmonitor.cpp, then IPower::Fonte: 0 "R. ElÃ©trica", 1 "B. Interna", 2 "B. Externa", else "NÃ£o
# identificada", in the target's block order). Both helpers are in the anonymous namespace, their names chosen;
# ConverteTipoAlimentacao's is the record's. It matches: 132 over 1413 rows, all operand-only, before step 8; with
# ConverteTipoAlimentacao's cases 1 to 3 first and its default last, 175 over 1434 (21 inserted, 21 deleted), the
# target laying out the "R. ElÃ©trica" arm first.
#
# Slots 4, 23 and 24 are the base's defaults,
# bodies binaryen shares (434, 425), matched under other classes' names; slots 0 and 1 are the implicit destructors,
# 174 and 144, shared too.
#
# Where things are. crelatoriotesteimpressora.cpp's one record is line 173 (ConverteTipoAlimentacao, inlined into
# GetDadosLocal). The members are defined in the order of their target indices, a higher index first: inside the use-1
# band that is the link order (docs/how-to-decompile.md step 3), 11202 to 11189 before 11188 and 11187 to 11183 after;
# their lines are chosen (the includes, the helpers and the constructor are placed so that line 173 stays the record's).
# cimprimirextratocarga.h's path and the base's slot names are chosen;
# that header says what places the base in a file of its own (its typeinfo, and 11216 in the band), whose one function's
# lines are chosen. crelutil.h, euecomumrelatorioserror.h and crelatoriotesteimpressora.h are chosen paths beside the
# sources.
#
# What the bytes decide, measured with `pnpm wasm score` in the whole link:
# - GetTipoUrna reads the urna's type through CDadoCarga::GetTipoUrna, an inline member of cdadocarga.h (unit 93's header,
#   one line added): the target keeps GetGeral() + 32 apart from the select of 4 or 8, the shape a member clang simplifies
#   before it inlines it gives. The same ternary written in the slot folds to a select of 36 or 40 (11 over 62, 2 rows
#   deleted), and the member out of line in cdadocarga.cpp, which binaryen inlines, gives 17 over 67. The inline member
#   gives 7 over 62, all operand-only. The constructor (5586) holds the same shape.
# - GetSeparadorFase (1919) builds its CInformacaoEleicao as a named local: as a temporary in the if, its frame differs
#   (111 over 346). Its cases run SIMULADO, TREINAMENTO, OFICIAL: in phase order the br_table is [3 0 1] where the target's
#   is [1 3 0] (45 over 343). The if/else around the switch puts the throw at column 23, a choice among forms that do.
# Chosen, the other way not linked: the slots' const; GetTipoUrna's switch; the getters this unit adds and their return
# by reference (cconfiguracaoeleicao.h, cestadogeral.h, chv.h, cpe.h, cprocessoeleitoral.h, cdadocarga.h: inline, chosen
# names, no layout changed; every other object compiles to the same bytes with them, cmp before and after).
#
# The type at CConfiguracaoEleicao + 88. EhModoDemonstracao and 1919 build comum::CInformacaoEleicao on it. That header
# (unit 111) took a struct of its own there, SDadosInformacaoEleicao; cconfiguracaoeleicao.h holds an
# ecourna::app::dados::CParametrosUrna, whose fields are at the offsets CInformacaoEleicao's members read. Its constructor
# takes that class now: 603's match line follows the new symbol (a rename, splat-match), and the masked disassembly of
# cinformacaoeleicao.cpp's object is the same before and after.
#
# Roots (123-uenux2-crelatoriotesteimpressora-roots.cpp): the vtable's address went when the constructor (5586) was
# written, since its vptr store keeps the vtable now; and three stand-ins for callers not reconstructed, each of a
# function with several callers in the target that binaryen would
# inline into its one caller here: w123_separador for 1919's (without it 11183 scores 388 over 390, measured on an earlier form of 1919), w123_erro for 580's 13 other throwers (without it
# binaryen inlines the constructor into 1919, 90 over 387, and neither 580 nor 1919 matches). w123_erro stands for the
# five throwers not in the link (the roots file lists them) and goes with the last, and w123_separador when 11943,
# 11946, 12105 and 12110 are in the link (2785 is). w123_copia, which stood for 1249's other callers
# (without a second caller binaryen inlines the copy and 11197 scored 204 over 208), went before all of them landed, on
# a link without it that moves no row: 11395 (unit 93) calls 1249 three times and reads its result as the stand-in did,
# and with it out 11197 and 5856 (unit 160) keep `match` (without 11395 in the link they left it: `+0xf target drop |
# ours +0xf end` in 11197's scan row); 5740 (unit 89's) is in the link since, and 5637 and 12098 still wait. The third, w123_labels, stands for 7787's call of 5794 through SetLabels, so that 5794 keeps two call sites; it goes when 7787
# lands. A fourth, w123_mapa, stands for 7787's call of the label map's initializer-list constructor (fn 5795, which
# this unit's object instantiates for InicializaTradutorFrase), so that 5795 keeps two call sites and stays out of
# line; it goes when 7787 lands. It declares the constructor through an __asm__ label with the object's signature
# ((i32, i32, i32) -> i32 in crelatoriotesteimpressora.cpp.o, wasm-objdump -x) and reads the result, which the target's
# wasm type, (i32 i32)->(i32), keeps; the comparator, the object's third parameter, is in neither link's type (pnpm
# wasm fn on both). Measured with `pnpm wasm score` against our plain link with the stand-in in it: 5795 1 over 172
# rows and 11196 20 over 289, all operand-only, and splat-match then matched both (5795 by content, 11196 under the
# symbol file's name).
#
# CRelUtil's other written members, in crelutil.cpp (that file's note gives their lines), all matched; the scores of
# 11181 and 11182 are `pnpm wasm score` against the plain link before steps 7 to 9:
# - GetIDCargaFormatado (target fn 2786, record crelutil.cpp:69:15) joins seven three-character pieces of the load code
#   with "." and the rest from position 21, and throws CUeComumRelatoriosError 9085 with the code between brackets when
#   the code has 20 characters or fewer. The test comes first with the throw inside it: written as an else after the
#   return, the compare came out as `i32.ge_u 21` where the target has `i32.gt_u 20`, and the success path's temporaries
#   8 bytes higher in the frame (198 over 1144 rows, 3 not operand-only); as written, 40 over 1144, all operand-only, the one operand that is
#   no call and no data address being the thrown object's destructor's table slot (69, fn 4636). Measured with
#   `pnpm wasm score` against our plain link.
# - IncluiAvisoModoDemonstracao (fn 5583, no record) reads as a CRelUtil member: its callers are
#   IncluiCabecalhoEleicoesMZS (fn 1543, record crelutil.cpp:307) and fn 5591 (comum::CImprimirExtratoCarga::Imprime,
#   unit 296's), and it tests CInformacaoEleicao::EhModoDemonstracao as GetSeparadorFase does. It adds the
#   demonstration-mode line, centred in style 1, and two blank lines: 10 over 69, all operand-only. Its name, its lines
#   and its being a static member are chosen.
# - ImprimeSeparadorVia (fn 5581, no record), on lines 348 to 353 (427 B, `pnpm wasm fn ../target/vota_web_wasm.wasm
#   5581`), builds std::format's result for "-------------- {:02} / {:02} ---------------" (the 44-byte literal at
#   378206, which no other target function loads: `/usr/bin/grep -rlE 'i32\.const 378206($|[^0-9])'
#   build/out/splat/pieces/asm`) over its second and third arguments, both of argument code 6, unsigned (the i64 198
#   it stores: docs/reference/facts/reading.md R13), adds it to the api::CPaperFormBuilder its first argument is with
#   AddTextField (fn 193), style 1 and alignment 0, then calls AddNewLine(1) (fn 198). Its one caller is fn 12110,
#   vota::CGeraBU's slot 2 (ledger/vtables.json), which calls it twice (+0xdbe and +0x1086), each time with the
#   builder at +36 of its frame, a counter plus one and a total, and which also calls GetIDCargaFormatado (fn 2786).
#   Before steps 7 to 9 it scored 11 over 187 rows (`pnpm wasm score`), all operand-only, the one operand that is no
#   call and no data address being the format buffer's table slot (148 in the target). No symbol-file line names
#   it: the scan's content pass pairs it (its `source` read `content` in the first scan), and no other target
#   function loads its literal. w123_vias stands for 12110 with two calls; it goes when 12110 is in the link.
#   Chosen: the file. No record names it, and in the uses-2 band of ledger/ordinals.tsv no function between the
#   matched cparte*.cpp rows (5590 to 5587) and cvalidamidia.cpp's GetInst (5575, record line 182) holds a record. In
#   link order 5581 follows fn 5583, which this unit put in crelutil.cpp by choice, and fn 5582 (no record), and
#   precedes fns 5580 to 5576 (no record; 5576's callers are fn 3689, which holds csubstituidortitulo.cpp's records,
#   and fn 11175). crelutil.cpp is taken for that neighbour and for the caller's other CRelUtil call; the other
#   relatorios files whose names sort in that stretch, csigverifier.cpp (unit 26) and csubstituidortitulo.cpp, were
#   not linked with it (docs/reference/facts/placing.md P5). Also chosen: its name, its being a static member of
#   CRelUtil (the class's records name only static members: how-to step 3, "Names no evidence gives"), its
#   parameters' unsigned int (the argument code gives the signedness, not the width), its line (in the blank run
#   between IncluiCabecalhoEleicoesMZS's record, line 307, and DSCodigoVerificador, line 410), and the style's
#   spelling as a cast of 1 and the alignment's as api::ALINHAMENTO_ESQUERDA, as IncluiAvisoModoDemonstracao spells
#   its style.
# - TituloPartido (fn 11181, record crelutil.cpp:58:15, `std::string comum::(anonymous namespace)::TituloPartido()`)
#   returns CTradutorFrase::Traduz("<PLSN>") + ": " + the current party's number + " - " + its abbreviation (the string
#   at +4 of md::CPartido, GetSigla), and throws CUeComumRelatoriosError 9084 "Partido nÃ£o posicionado" when
#   CPartidos::GetInst()'s cursor is at the end (IsFim, inline). The number is read into a named local right after
#   GetCurrent, as the target loads it before it builds "<PLSN>": 21 over 246 rows, all operand-only, the one operand that
#   is no call and no data address the thrown object's destructor's table slot (69); with the number read inside the
#   expression, 26 over 247 (1 inserted, 2 deleted).
# - The target reaches TituloPartido only by its table slot (3050), which only fn 11946 (vota::CGeraZeresimaBase's slot
#   2, not written) loads, behind a stack-pointer prologue of its own: a function binaryen inlined there that builds a
#   CPaperFormBuilder, adds one text field over the slot (AddTextField, fn 604, alignment 0) and returns Build's form
#   (fn 357). Only crelutil.cpp's TU can take the address of its internal function, so that function is crelutil.cpp's:
#   FormTituloPartido, a static member of CRelUtil (its name and membership chosen: the class's records name only static
#   members), defined last in the file. In our link 11182's ld_index is then below 11181's (1543's paragraph, below, has them), the order their
#   use band (1) asks; the other places were not linked. w123_titulo stands for 11946 and calls it once, so binaryen
#   inlines it there as in the target; it goes when 11946 lands.
# - DSCodigoVerificador (fn 11182, record crelutil.cpp:412:27, the default std::source_location of its
#   CPolySingleton<CCalculaCV>::instance() call) formats CCalculaCV::CalculaCodigo's result (fn 3700, unit 121) as
#   "CÃ³digo Verificador: {}.{}.{}.{}" of its substrings (0, 1), (1, 3), (4, 3) and (7, 3), the lengths the target's
#   copies clamp to. 18 over 501 rows, all operand-only, the one operand that is no call and no data address the format
#   buffer's table slot (148 in the target). The target reaches it only by table slot 3048, which fn 11256 (unit 139)
#   passes: it needs no stand-in. `CCalculaCV& calculo = ` before the call, what fills the line to column 27, is chosen.
# Two of GetIDCargaFormatado's four callers are not reconstructed (12105, 12110; 11256 and unit 325's 5579 are in the
# link): w123_idcarga stands for them and calls it twice, as the target's several callers do; it goes when every caller it
# stands for is in the link. IncluiAvisoModoDemonstracao's two callers, 1543 and 5591, are in the link.
#
# Four more CRelUtil statics in crelutil.cpp, all matched; their stand-ins are in unit 230's roots, the unit of
# comum::CSubstituidorTitulo, which the first one uses:
# - ImprimeTitulos (target fn 3689) prints a report's title lines (std::vector<ecourna::app::dados::CTituloRelatorio>):
#   when CSubstituidorTitulo does not exist yet it creates it from a map of "<uf>" to the UF it is given; then for each
#   title it splits CTradutorFrase::Traduz of the text on '\n' (CStringUtils::Split, fn 1880), drops a last empty line,
#   and adds each line, a new line for an empty one and otherwise the line with the substitutions applied, style 2 for an
#   expanded title and 1 otherwise, the title's alignment mapped to ETextAlignment (centre to 2, right to 1, else 0). It
#   holds CSubstituidorTitulo's GetInst and CreateInst (records csubstituidortitulo.cpp:21 and :26), the test of the
#   pointer, the constructor and the substitution inlined, those with a frame each behind a prologue of their own (unit
#   230 has them). Both loops go by index: the target divides the vectors' byte lengths by 20 and 12 on each pass.
# - its overload without the UF (fn 5584, 15 B) passes comum::CLocal::GetInst().GetUF() (fns 401, 1702);
# - ImprimeAberturaFechamento (fn 3688) prints the UE's opening and closing date and time through ImprimeDataHora (fn
#   1542), then a new line; ImprimeDataHora adds two text fields, style 1 and alignment 0: the date label padded to 28
#   with CStringUtils::PreencheADireita (fn 1881) followed by CDate::Format("DD/MM/YYYY") (fn 706) of the date, and the
#   time label so followed by CTime::Format("  hh:mm:ss") (fn 779).
# Where they are: none has a record. In the use bands they sit among this file's functions: 1542 right after 1543
# (IncluiCabecalhoEleicoesMZS, record :307) in band 8, so ImprimeAberturaFechamento and ImprimeDataHora follow 1543
# (above), 5584 right before 5583 (IncluiAvisoModoDemonstracao) in band 2,
# and 3689 and 3688 in band 3 between fn 3691 (comum::CGeradorRelVersaoPacoteDados's D2) and capplication.cpp's 3684
# (`awk -F'\t' '$1>=3683 && $1<=3691' ledger/ordinals.tsv`). That they are crelutil.cpp's is a reading of those bands and
# a choice; that 3689 is not csubstituidortitulo.cpp's is a reading: GetInst is a plain function, which clang inlines in
# its own TU at uenux2's flags (docs/reference/facts/codegen.md C6), and 3689 holds it inlined by binaryen. Their lines
# are chosen (ImprimeTitulos after GetIDCargaFormatado; the other two after 1543); in our link 3689's ld_index is below
# 3688's and 5584's below 5583's, as the bands ask (1543's paragraph, below, has the ld_index values).
# What the bytes decide: 3689's frame. Written with the lines built in ImprimeTitulos itself, 3689 scored 70 over 796
# rows, all operand-only, with the map at +20 of the frame where the target has it at +36 and the key's tuple and the
# insertion's result above it where the target has them below; the lines built in a helper clang inlines
# (QuebraLinhas, the title's text translated, split and its last empty line dropped) give the target's frame, 41 over
# 796, all operand-only, the operands that are no call and no data address being the two .bss words and the thrown
# object's destructor's table slot (69 in the target). Compared on the object (wasm-objdump -d, the offsets of the
# map's stores), these forms gave the first frame: the lines built by a helper that takes the translated text, the
# vector assigned after its declaration, the map's creation in a helper; the Traduz result a named local gave a third
# (the map at +28). Scores with
# `pnpm wasm score` against the plain link before steps 7 to 9: 5584 3 over 7, 3688 23 over 172, 1542 20 over 239, all
# operand-only.
# Chosen: the four names and QuebraLinhas's, their parameters' types (the vector, api::CDateTime), that they are static
# members of CRelUtil (its records name only static members) and that QuebraLinhas is in the anonymous namespace (a
# static member was not tried), the conditionals for the style and the alignment (a switch was not tried), `continue`
# for the empty line.
#
# IncluiCabecalhoEleicoesMZS (target fn 1543, record crelutil.cpp:307:19, `static void
# comum::CRelUtil::IncluiCabecalhoEleicoesMZS(api::CPaperFormBuilder &, const std::string &, const TMunicipioID, const
# TZonaID, const TSecaoID, const std::string &, const ETipoCabecalho, const bool)`) matches, with what it brings:
# - Its body (pnpm wasm fn ../target/vota_web_wasm.wasm 1543): behind a 240-byte frame of its own,
#   IncluiCabecalhoEleicoes, which copies CConfiguracaoEleicao's pleito (fn 1281), takes CPE's pleito 2 (fn 1267)
#   instead through CPleito's implicit copy assignment (fn 5597) when the last argument and a contingency header (2)
#   come together, CPE is created first if it does not exist (2788, 2787 over CAppInfo::LeGeralInterno, 2273) and the
#   pleito 2's date is today or earlier (CDate's ==, inline, then operator<=>, 1261: the test of the constructor 5586);
#   behind a 32-byte frame inside it, IncluiCabecalhoPleito (the demonstration notice, 5583; ImprimeTitulos with the
#   configuration's header and CLocal's UF, 3689; the title when not empty; "Eleições Comunitárias" for the origin 2;
#   the configuration's name, the pleito's name and its date as "(DD/MM/YYYY)"); then the pleito's elections copied
#   (1953), sorted and printed when there are two or more. Back in 1543: the municipality's line "{:<32s} {:05}" over
#   Traduz("<MLSN>"), the municipality's name centred, the zone's "{:<33s} {:04}" over "<ZLSN>", and a switch on the
#   header type: 0 the place's line "Local de Votação" (not for a community election) and the section's "<SLSN>", and
#   with aggregated sections (CLocal::GetQtdAgregadas, 2816) their count, through comum::FormataQtdAgregadas behind a
#   384-byte frame (clocal.cpp's, unit 89's fragment has it), and FormataAgregadas (5738); 1 "Mesa Receptora" {:03} of
#   the section over 10 and "Urna" {} of the rest; 2 "Urna de contingência"; 3 the throw, CUeComumRelatoriosError 9086
#   "Tipo inválido: {}" over the type (argument code 15, a handle: the enum has a formatter, crelutil.h); no default.
#   Every literal, format, width and alignment is the target's. Before steps 7 to 9 (pnpm wasm score against the plain
#   link): 212 over 2729 rows, all operand-only, the operands that are no call and no data address being the format
#   buffer's table slot (148 in the target) and the thrown object's destructor's (69).
# - The sort: std::sort over the copied std::vector<md::CEleicaoPE> with a lambda that takes both elections by value
#   (5582 copies both elements at each comparison, pnpm wasm fn ../target/vota_web_wasm.wasm 5582) and compares
#   CConfiguracaoEleicao::GetInst().GetSituacoesEleicoes(id).GetOrdemImpressao() of the two (fns 187 once, 271 twice,
#   the byte at +5). This object instantiates libc++'s __introsort (5582), __sort3 (1386), __sort4 (3687), __sort5
#   (5578), __insertion_sort_incomplete (5577), CEleicaoPE's move assignment (817) and std::swap of two (818), which
#   match with it; their names mangle the lambda of IncluiCabecalhoEleicoes ($_0).
# - CPleito's implicit copy assignment (5597) and what it instantiates: the copy of a CEleicaoPE range (5595), CCargo's
#   copy assignment (5594), CNomesCargo's (3692) and a std::copy of md::CRespostaConsulta (5593), named so by step 8's
#   pairs. Their target copy lies in use band 2 before cgeradorrelversaopacotedados.cpp's ImprimeRodape (5596), so an
#   earlier object instantiates it in the target (a reading); this object's copy, at comum's flags, matches. 5597 has
#   two target callers, 1543 and 11902 (unit 176's, in the link), which keep it out of line.
# - The forms the bytes decide, each measured with pnpm wasm score: the pleito 2's test written in IncluiCabecalhoEleicoes
#   gave 216 over 2730 rows (1 inserted, 1 deleted), the target's `and` of the two (crelutil.h says how) 212 over 2729;
#   with 5597 called once in the link binaryen inlines it into 1543 (1415 over 3800 rows, 1071 inserted), so it needed
#   its second caller, 11902 (a stand-in until 11902 was written).
# - Where they are. The record puts the switch's throw on line 307, column 19. The other functions have no record; the
#   bands order them: in band 2 5583 (IncluiAvisoModoDemonstracao) precedes 5582 (the sort, first mentioned in
#   IncluiCabecalhoEleicoes) and 5581 (ImprimeSeparadorVia), and in band 8 1543 precedes 1542 (ImprimeDataHora) and
#   1541 (below). So IncluiAvisoModoDemonstracao, IncluiCabecalhoPleito and IncluiCabecalhoEleicoes precede 1543, and
#   ImprimeAberturaFechamento and ImprimeDataHora (moved from above line 294) follow it: ImprimeDataHora's first mention
#   is ImprimeAberturaFechamento's call. In this link's build/out/wasm-map/vota_web/names.tsv, ld_index by target
#   index: band 2 5584 3211, 5583 3212, 5582 3216, 5581 3228; band 8 1543 3220, 1542 3223, 1541 3224; band 3 3689 3209,
#   3688 3222; band 4 2786 3208, 2785 3225; band 1 11182 3229, 11181 3234: each higher index has the lower ld_index.
# - Evidence in the shape: one CLocal::GetInst and one CConfiguracaoEleicao::GetInst call in 1543, right after
#   IncluiCabecalhoEleicoes (named locals); the two formats of the aggregated-sections branch live to its end (the target
#   destroys them there, named locals), while the other lines' temporaries die with their statement.
# - Chosen: the two helpers' names, parameters and membership (crelutil.h); ETipoCabecalho's scope, enumerators and
#   formatter (crelutil.h); the parameters' and locals' names; IncluiCabecalhoPleito calling ImprimeTitulos without the
#   UF (5584, which clang inlines here; calling 3689 with CLocal's UF was not linked).
# - ImprimeResumoCorrespondencia (target fn 1541, no record: "RESUMO DA CORRESPONDÊNCIA" and FormataCodigoCargaResumido,
#   2792, in style 2, then a new line; 11 over 83 rows, all operand-only) and ImprimeSeparadorFase (fn 2785, no record:
#   GetSeparadorFase of the phase, centred; 4 over 51, all operand-only), both called by 11902 and by five unwritten
#   reports (crelutil.h has what places them, the use bands 8 and 4). 2785's CInformacaoEleicao that nothing reads and
#   its separator assigned after a default construction are the target's frame (+28 and a move from +4 to +16): the
#   separator initialized from the call gives a 16-byte frame and no move, measured on a probe TU compiled at this
#   directory's flags (tools/round/try-tu.sh --symbols, then wasm-objdump -d of the object). Their names, their
#   parameters' types and their being static members are chosen.
# - Roots: w123_cabecalho stands for 1543's five callers not in the link, w123_rodape for 1541's five and 2785's three;
#   w123_demonstracao, which stood for 1543 as 5583's caller, went with 1543's landing.
CRELATORIOTESTEIMPRESSORA_SRCS := src/app/comum/relatorios/crelatoriotesteimpressora.cpp src/app/comum/relatorios/crelutil.cpp \
                                  src/app/comum/relatorios/cimprimirextratocarga.cpp
UENUX2_SRCS += $(CRELATORIOTESTEIMPRESSORA_SRCS)
# cconfiguracaoeleicao.h reaches ecourna's chorariosurna.hpp, which includes Boost (unit 88 adds the path the same way)
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,$(CRELATORIOTESTEIMPRESSORA_SRCS))): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the roots object includes the class header, which reaches ecourna and uenux2 headers alike
W123_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/123-uenux2-crelatoriotesteimpressora-roots.o: $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/123-uenux2-crelatoriotesteimpressora.mk $(W123_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/123-uenux2-crelatoriotesteimpressora-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/123-uenux2-crelatoriotesteimpressora-roots.o
