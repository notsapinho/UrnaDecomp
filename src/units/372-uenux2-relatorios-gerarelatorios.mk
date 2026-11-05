# uenux2: vota::CGeraRelatorios::StartState (target fn 12105, record cgerarelatorios.cpp:51:104) and the three reports
# it writes at the end of the vote, with the template instances and callbacks they bring. No source list of its own: the
# files are other units' lists' (step 6 item 2: units 214's and 113's fragments are another stage's claim): unit 220's
# cgerarelatorios.cpp, unit 93's line for the two new files cgeradorbuj.cpp and cgeradorreleleitoreshabbiograf.cpp
# (beside unit 155's), unit 214's cimprimiridentificacaomesariosfinal.cpp, unit 113's cjustificador.cpp. Paths below
# relative to src/uenux2/src/app/.
#
# Matched (`pnpm wasm score` against the plain link before steps 7 to 9, all operand-only):
# - comum::CGeradorRelEleitoresHabBiograf's file (comum/relatorios/cgeradorreleleitoreshabbiograf.{h,cpp}, the report of
#   the voters a poll worker enabled, written to behb.dat): the __func members of MontaCabecalho's lambda (RTTI:
#   comum::(anonymous namespace)::MontaCabecalho(comum::CGeradorRelEleitoresHabBiograf::EGeradorRelatorio)::$_0, vtable
#   @1576044): target_type 11236 (1 over 3), target 11237 (1 over 11), __clone(p) 11238 (1 over 5) and __clone() 11239
#   (2 over 8); the column header the report passes by table slot 2961, 11240 (15 over 364); the instances its sort of
#   each section's voters brings, over a std::pair<uedword, std::string> by its first member: std::__introsort 5600 (7
#   over 2798), std::__insertion_sort_incomplete 5599 (0 over 779) and std::__sort4 2789 (byte-exact); and the vector's
#   push_back 5602 (4 over 151), which 12105 calls twice.
# - comum::CJustificadorDadoQuantidade::Text (fn 11474, 18 over 318) in comum/justificativa/cjustificador.cpp: the count
#   of justified voters in "{:05} Justificativas", the last letter dropped for one, which comum::CGeradorBUJ hands to a
#   CDataTextFmt by table slot 2948.
# - Fn 13414 (`mac_gettable_params`, OpenSSL) matched by the scan's content pass (`address same-content`); its slot
#   (11358) is id 12 (OSSL_FUNC_KEYMGMT_GETTABLE_PARAMS) of the MAC key manager's OSSL_DISPATCH table at 1780192, and
#   the slot of 13412 (11360), listed as `mac_gettable_params` since before this unit, is id 14 (SETTABLE) of that table
#   and of CMAC's at 1780336: 13412's line reads `mac_settable_params` now (docs/reference/facts/splat.md S11's
#   dispatch-table command), and a rescan keeps both. No source of ours changed them; the data our unit adds moved the
#   content pass's pick.
#
# Written, not matched:
# - 12105, 1793 over 8330 rows (96 inserted, 66 deleted, the rest operand rows, most of them local numbers): StartState
#   in cgerarelatorios.cpp with three external functions it holds inlined by binaryen (frames of 224, 160 and 144
#   bytes), GeraRelatorioBUJ, GeraRelatorioBIM and GeraRelatorioBEHB (chosen names), each a context guard, a generator
#   and the report's file in the internal flash, then CSincronizaVota::SincronizaRelatorios. Its direct callees are the
#   target's, call for call (the `call` rows of `pnpm wasm fn` on both links, mapped by splat/matched.txt), but one more
#   free (fn 136: 107 calls against 106) and 3695, which our link calls under another name. Not explained yet: the BUJ's
#   buj.dat string, whose size the target folds into the path's append range and ours reloads after CriaContexto and
#   GetPathTrab (clang's object already reloads it), and the rest's local numbering.
# - 3695 (the std::map of sections' __tree::destroy, 3 over 67): recursive, so its own call waits for a name, and its
#   one caller is 12105 (docs/how-to-decompile.md step 1, the `unresolved` rows).
# - 4027 (std::__visit_format_arg over __handle_replacement_field's lambda, 393 over 3752, 111 inserted, 8 deleted):
#   12105 holds a std::format("{:04}", ...) whose __vformat_to clang inlines and whose visitor it calls; with that
#   second caller our link keeps the executable TU's copy out of line, as the target does (146, that TU's __vformat_to,
#   now 12 over 212, all operand rows, `unresolved self-voted` on it). The rows differ where the visitor calls fn 5924
#   (a char formatter over an integer), which our link inlines: 5924's other target caller, 9935 (the format function of
#   a handle argument, table slot 468), is passed by 5344, which is not written. 3838 and 5822 (two parse members 4027
#   calls) stay unresolved on their 2-byte field sets.
#
# What the bytes decide, measured with `pnpm wasm score` of 12105 against the plain link:
# - The record order: cimprimiridentificacaomesariosfinal.cpp's records lie as GetNomeMesario's (1594496), the inline
#   GetDtHr throws (1594512, 1594528), then GetPrinter's (1594544), so the member that first mentions GetPrinter,
#   Imprime, is defined after the one that mentions the throws: with Imprime defined first, 2472 over 8402; last, 1793
#   over 8330.
# - The report's generator stores 0 in a constructor of no parameter: 12105 calls 2262 (comum::CLocal's body); with the
#   enum as a parameter its one caller passes, our 12105 called comum::CInformacaoEleicao's constructor (fn 603) there,
#   the body that stores the parameter, and never 2262 (the callee lists of both links).
# - The BIM's object is built by an out-of-line constructor of one bool (+12 a byte store of 1, +13 and +14 one 16-bit
#   store of 0, through `this` in a local); an inline constructor of three gave a 16-bit store at +12 and a byte at +14.
# - The column header pads with `tamanho > 38 ? "" : std::string(38 - tamanho, ' ')` written in place: a helper with the
#   two callers stays out of line (11240, 302 over 365); `< 39` with the branches swapped, 147 over 398; `std::string()`
#   for the empty one, 124 over 388 (it clears 12 bytes, the target stores two, and the frame's slots move: the object's
#   stores at +16 and +0 against the target's +20 and +8, as comum's 11234 has them).
# - The titles' part holds Build and std::make_shared once per branch, as two returns give; one return, one copy.
# - The voters' loop reads the record through the cursor (CEleitores::GetDetalheCorrente, celeitores.h) and the dynamic
#   data's optional in place (CEleitorDetalhe::GetDadosDinamicos, celeitordetalhe.h): GetCurrent (656) and GetDinamico
#   (1271) stay calls in our link, where 12105 has none.
# - The BUJ's "{:05} Justificativas" field: CPaperFormBuilder::AddTextField<FONTE>(fonte, formato), which 12105 holds
#   behind a 16-byte frame (cpaperformbuilder.h).
#
# Places: comum::CGeradorBUJ's object has records only (cgeradorbuj.cpp:189 at 1575808, between cgeradorbu.cpp's run and
# cgeradorbuqrcode.cpp.o's at 1575936), and CGeradorRelEleitoresHabBiograf's vtable (1576052) lies after
# cgeradorbuqrcodevota.cpp.o's and before cgeradorrellistaeleitores.cpp.o's (1576188): their data run in name order, so
# both go in unit 93's line beside unit 155's two files, before and after them. docs/reference/facts/codegen.md C4's
# count, the objects that have records and no named vtable ranked by their lowest .cpp record
# (ledger/source-locations.tsv, ecourna's objects too), on the merged link at 63b2b9ab: both files have 301 objects out
# of the data's order against them here; cgeradorbuj.cpp would have 311 after unit 183's cgeradorrelpu.cpp, 320 at
# this fragment's own place (after unit 37's cmostraqrcodebu.cpp) and 338 after unit 139's cgeradorbu.cpp; the
# report's file 323 at this fragment's own place, 326 first in unit 317's list and 328 there before
# cgeradorrellistaeleitores.cpp, its data successor. C4's awk alone (vtables only) reads 207 for the report's file
# here and 202 to 204 at the others. Here the four files of the BU reports' data run (cgeradorbuj.cpp, unit 155's
# two, the report's file) link in their data order, after cgeradorbu.cpp, and the one pair of data neighbours left
# inverted is the report's file with cgeradorrellistaeleitores.cpp, which unit 317's list links before them. Against
# the next place, each file's place inverts the objects linked between the two whose data lie after its own and puts
# in order those whose data lie before. cgeradorbuj.cpp against cgeradorrelpu.cpp's place: 120 put in order, 110
# inverted (by directory: 42 of app/vota/operador, 37 of api/gui, 8 of app/comum/comparecimentomesario, 7 of
# app/comum/relatorios, 5 of api/util, 4 of app/comum/gravadores, 3 of api/hash, one each of
# app/comum/reconhecimentobiometrico, api/uelog, api/io and api/audio). The report's file against this fragment's own
# place: 61 put in order, 39 inverted: api/gui's ctextfieldpaper.cpp, cprogressbar.cpp, cstepsprogressbar.cpp,
# ctextfieldupdate.cpp, cimagefieldupdate.cpp, ctextfieldblinking.cpp, cmoviefield.cpp, cqrcodeimagefieldpaper.cpp,
# clinefield.cpp, cdsimagefield.cpp, cledfieldmt.cpp, ctextbox.cpp, reports/cformpart.cpp, cbeepfieldmt.cpp,
# cbuzzfieldmt.cpp, cclockfieldmt.cpp, cpreshowclearmt.cpp, cqrcodeimage.cpp, ccutfieldpaper.cpp,
# cnewlinefieldpaper.cpp, cinputmenufield.cpp, cfillfield.cpp, crectfield.cpp, ctextrectfield.cpp and cframedtext.cpp;
# api's audio/alsa/cwavfile.cpp, uelog/cescritorlog.cpp and util/isystemdatetime.cpp; comum's relatorios/
# cpartecargos.cpp, cparteeleitores.cpp, cparterdv.cpp and cpartecandidatos.cpp, gravadores/asn/
# cconversorhasharquivo.cpp, comparecimentomesario/estados/ipedetitulomesario.cpp and its dao/
# ccomparecimentomesariodao.cpp; vota/operador's comum/cinformacaothreadoperador.cpp, ctextfieldupdatemt.cpp,
# telasoperador.cpp and aguardaeleitor/celeitorvotounaovotou.cpp. The bytes are the same here and in unit 317's list
# (12105's score above); in unit 317's list the report's object came before clocal.cpp's, its constructor took 2262's
# match line from comum::CLocal's (a twin rename), and it gave fn 5601's copy, which the target keeps from it too (its
# record 1576108 lies in its run): here 5601 comes from cparteeleitores.cpp's object, as before this unit.
#
# Stand-ins that 12105, in the link, made idle went, call by call (each file's comment says which callers still wait):
# units 31 (RelatorioA's second adder calls, FormPapelC's second Build), 39 and 77 (their roots files and rules: every
# caller of 2771 and of api::CFormPart's constructor is in the link), 109 (Votos' two calls of 2841), 113
# (AvancaUm/AvancaDois over the voters' map, CriaJustificadores for 11474, ConsultaRegistrador), 123 (one call each of
# 2786, 1543, 1541 and both of 2785), 168 (AdicionaSeparador's CENTRO call), 178 (its roots file and rule), 196
# (VersoesDe), 205, 216, 230 (one call each of 1836, 1391, 3688), 309 (one call of 5741) and 317 (ArquivosRelatorios and
# one call of 2259); units 154, 171 and 325 keep their calls, which stand for other callers too (comment lines). Idle
# with 12105 in the link as well, and gone at the merge: unit 104's pair for 5983, unit 214's roots file and rule
# (GetNomeMesario's two calls), unit 111's w111_informacao (603, 1950, 2286), unit 89's Construtores (2262) and one
# call of Nomes (1077), and one of unit 100's two calls of api::IPaperRelatorios's instance (905).
#
# Chosen, no evidence names them: GeraRelatorioBUJ, GeraRelatorioBIM, GeraRelatorioBEHB and their being free functions;
# CGeradorBUJ's constructor's parameters, its members' names and its helpers (MontaCabecalho, MontaTotais,
# MontaJustificativa, MontaRodape); CImprimirIdentificacaoMesariosFinal's members but GetNomeMesario and GetPrinter, its
# parameter and fields; the report's enumerators, member, Gera and its helpers (MontaTitulo, MontaTitulos,
# MontaEleitores, MontaSeparador, MontaRodape, DescricaoSecao, CabecalhoHabilitados) and the key struct SChaveSecao (its
# members' types: a 16-bit section, an unsigned word compared unsigned, a byte); the sorted voters' element type,
# std::pair<uedword, std::string> (the bytes give a 4-byte first member compared unsigned and a std::string), whose
# name the matched instances 2789, 5599, 5600 and 5602 carry; CJustificadorDadoQuantidade; the
# accessors GetDetalheCorrente and GetDadosDinamicos; the assert enumerator EUA_GERARELATORIOS_EST_INVALIDO (3455,
# api/util/eueasserterror.h); every line but the records' (cgerarelatorios.cpp:51, cgeradorbuj.cpp:189,
# cimprimiridentificacaomesariosfinal.h:41, cimprimiridentificacaomesariosfinal.cpp:229); the two new files' paths.
