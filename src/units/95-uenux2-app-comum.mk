# uenux2 src/app/comum's root files over comum::EUeComumError, at the paths their std::source_location records name,
# listed in the name order the directory links in: comum::CArquivosResultado::operator[] (target fn 347) in
# carquivosresultado.cpp (record 99:11), comum::CArquivosSavd::operator[] (275, 680) in carquivossavd.cpp (49:15, 73:15),
# comum::CPacoteArquivos::RetornaNomeChave (5900) in cpacotearquivos.cpp (162:11) and
# comum::IInterfaceSavd::EnviarRequisicao (3830) in iinterfacesavd.cpp, which binaryen holds with the two static members
# the records name, DesconverteHeader (553:15, 559:15) and DesconverteMensagem (568:15, 574:15, 578:15), and with
# ConverteHeader; the class headers beside them and app/comum/euecomumerror.h, with the handle formatter of the SAVD
# enums (three, and ESavdAplic's since 4625). The formatter's handle body (fn 536) is the one binaryen keeps for every
# such enum, ours named by the table vote of 275, 680 and 5900; it matches since unit 253's data hand line names
# libc++'s __fields_integral.
# 480, CBaseError<comum::EUeComumError, ...>'s constructor, is named by the calls and matches with this header's enum:
# it is a thunk of 710, the body unit 94's form gives (the constructor in ecourna/api/exception/cbaseerror.hpp).
#
# comum::CPacoteArquivos::TrataErroPacote (5901, record 169:11), added after the unit landed: it throws code 7222 with
# the key's name (5900 on +24), the package's name (the std::string at +0) and IInterfaceSavd's code and text (+16, an
# int: argument type 3; +4); the getters on IInterfaceSavd and their names are chosen.
#
# Added since: the CPacoteArquivos members fn 4625 (vota::VerificaAssinaturaArquivos, unit 168's votadefs.cpp) holds,
# none with a target index of its own: the constructor (frameless) and, behind frames of their own (528, 16 and 560
# bytes), ValidarChaveEAplicacaoValida (records 85:15, 91:15), Validar (116:29, the default location of
# CPolySingleton<IInterfaceSavd>::instance()) and TrataErroPacoteArquivo (190:15): out-of-line functions binaryen
# inlined, one call each (docs/reference/facts/reading.md R10). With them, comum::IInterfaceMensagem and
# CInterfaceMensagemVazia (app/comum/iinterfacemensagem.h, new: RTTI and a vtable only, all inline), EUeComumError's
# 7219, 7220 and 7223, and ESavdAplic's formatter in iinterfacesavd.h. pnpm wasm score of 4625 against the link before
# step 8: 125 over 1607 rows, all operand-only; then it matched (named by srcloc-anchor).
# - The layout is the object 4625 builds in its frame: +0 a std::string, +12 a std::vector<std::string> (Validar walks
#   it and passes each element on as the file), +24 the ESavdChaveValidar, +28 the command (stored with i32.store,
#   loaded with i32.load: 32 bits) and +32 the ESavdAplic. The names, the command's type (ueint32), each member's
#   access, and the constructor's parameters and their order are chosen.
# - The constructor: the name copied into +0, the vector zeroed and the key, the command 0x1001 and the application
#   stored (+32, +28, +24, +20, +12, the target's order, which the member-initializer list as written gives; other
#   forms not measured), ValidarChaveEAplicacaoValida, the file pushed when it is not empty (fn 1108, libc++'s
#   __emplace_back_slow_path), then the command again: 0x2021 when the vector is empty, else 0x1001. The first store
#   is the target's (+28 = 4097 before ValidarChaveEAplicacaoValida's code), so the member is initialized and then set.
#   Its being out of line in this file, and its line, are chosen: a definition in the header, which 4625's TU would
#   inline, was not measured.
# - ValidarChaveEAplicacaoValida throws 7219 for a key outside 49 to 59 and 7220 for an application outside 1 to 9,
#   each formatting the member (argument type 15, a handle: the key's through table slot 2156, the application's
#   through 2157, both binaryen's body 536; the application's formatter is new in iinterfacesavd.h). `x < lo || x > hi`
#   gives the target's compares, `(x - (hi + 1)) <= -(hi - lo + 2)` unsigned, for both. Its record has no `const`.
# - Validar: CPolySingleton<IInterfaceSavd>::instance() (fn 1822); for the commands 0x2021 and 0x1011, the message's
#   slot 2 with the package, IInterfaceSavd::ValidarPacote (iinterfacesavd.cpp; binaryen inlined it, frame 32) with the
#   application, the key, the command and the name, and TrataErroPacote when it fails; otherwise, for each file, slot 3
#   with the package and the file, VerificarArquivo (5892) and TrataErroPacoteArquivo when it fails. The target loads
#   the vector's end again on every turn, which an iterator loop testing end() gives; a range-for does not (this
#   object compiled with each, Validar compared with object-local numbers masked: the range-for's lacks that load).
#   The package branch's return and the order of the two branches are chosen.
# - TrataErroPacoteArquivo: TrataErroPacote for the SAVD codes 1 to 3, else code 7223 with the key's name, the
#   package, the file and the SAVD's code and text. The target tests `(code - 1) > 2` unsigned and throws when it holds:
#   `code >= 1 && code <= 3` around the call with the throw in the `else` gives it in the link; `code < 1 || code > 3`
#   around the throw gave `(code - 4) <= -4` (3 rows of the score's 135 over 1610 before the next item's change). On
#   this object the negated `&&` around the throw compiles to `(code - 1) < 3` where the `else` form has `<= 2`; it was
#   not linked.
# - ValidarPacote (iinterfacesavd.cpp) takes the command as a ueint32: the target loads +28 with i32.load and stores
#   its low half, where a ueword parameter made our link load it with i32.load16_u (the same score). The request's
#   application is assigned before its command: that order stores the command first, as the target does, and the other
#   the other way round (clang stores values read first in reverse, docs/reference/facts/codegen.md C1), measured on
#   the object, then in the link. ValidarUE (5890), into which clang inlines it, is the same function with each of
#   those (iinterfacesavd.cpp compiled with each, masked). Its key is a uedword, the reading taken for 5892 below: an
#   `ESavdChaveValidar : unsigned int` with the enum parameter gives the same functions in iinterfacesavd.cpp's and
#   this file's objects (masked), so the parameter is a choice.
# - The order: the target's band (uses 2) has 5901 ahead of 5900, and our object now has it so (build/out/wasm-map's
#   ld_index 7978 and 7980): Validar, defined above both, mentions TrataErroPacote first. The lines of the constructor,
#   of Validar's definition and of TrataErroPacoteArquivo's (from 185) are chosen around the records.
#
# comum::CArquivosResultado::GetInst (348), its out-of-line constructor and destructor and its two statics are in this
# unit's files and belong to unit 111's measurement: its fragment says why GetInst sits above the statics.
#
# IInterfaceSavd's destructor (5503, slot 0 of its vtable and of the executable TU's CWasmSavd) is not written here: its
# body calls the string's destructor, which -Oz gives and -O2 does not (a probe of the class's shape at both levels, not
# at -O3; docs/reference/facts/levels.md V1), so the copy the target kept is the executable TU's and no object here can
# match it. It matches from that TU's object (unit 170), whose CWasmSavd derives from the class.
#
# Added since: the SAVD requests of iinterfacesavd.cpp with their TLV builder, and CArquivosSavd's file names:
#   5890  comum::ValidarUE(IInterfaceSavd&, ESavdAplic, const std::string&)  record 886:15, code 7323
#   5889  comum::EnviarAcaoHSM(IInterfaceSavd&, ESavdAplic, ESavdCmdHSM)     record 1040:15, code 7340
#   3831  comum::MontaRequisicaoTLV, a chosen name                          no record; named by 5890's call
#   5891  IInterfaceSavd::AssinarArquivo, a chosen name                     no record; matched by its content
#   5905  comum::DescricaoArquivo, a chosen name, in carquivossavd.cpp      no record
#   2283  std::map<std::string, uebyte>'s __tree::destroy, which CGenericTags's implicit destructor brings into this
#         object (it calls itself; 3831's call names it)
#   3829  the second IInterfaceSavd::EnviarRequisicao: matched since its response vector got a scope of its own (below)
# 5890 puts the 62-byte literal at 8090 ("Falha ao validar assinatura UE\npacote: ({})\nErro SAVD: ({})\n{}") in the
# link, whose tail is the "{}" that 2285 (unit 59), 11470 (unit 66), 11542 and 3766 (unit 91) format with: written
# there, they match with this unit.
# - ValidarUE: fn 4625 holds, behind a prologue of its own, the code clang inlined into 5890: it refuses an ESavdAplic
#   or a key above 255 and an empty package ("Argumento invalido validar assinar o pacote."), builds the TLV with 3831
#   from the package and the key, zeroes a request, stores a 16-bit command at +2 and the ESavdAplic at +1 and sends it
#   with 3830. That is IInterfaceSavd::ValidarPacote (a chosen name; a member, as it writes +4 and +16), which ValidarUE
#   calls with SAVD_CHAVE_UE (53, the key 5890 passes 3831) and the command 0x2021; clang inlines it (cost 220,
#   threshold 250: -Rpass=inline -Rpass-missed=inline on this file). 5890 stores the ESavdAplic 1 at +1 with a byte
#   store of its own after the i64 store of the zeroed request and command: at clang's time it is the parameter, which
#   binaryen's dead-argument elimination folds (5890's wasm type drops it), so the roots pass 1 from both stand-ins;
#   with the 1 a constant at clang's time, clang merged it into the i64 (measured: 0x20210100). ValidarPacote compares
#   the key unsigned, or-ed with the ESavdAplic, as 4625 does (`i32.le_u(i32.or(l3, l10), 255)`): a uedword parameter
#   since 4625 landed (the CPacoteArquivos paragraph above has the two readings and the command's ueint32). No byte of
#   5890 depends on either, since 5890 passes the constant 53; the inline cost above was measured with the earlier
#   parameter types.
# - 3831 builds sup{pkg{package} key{key}}: a CGenericTags with the four tags inserted (CriaTags, a chosen helper in the
#   anonymous namespace, which clang inlines: 3831 and 5892 hold the same four inserts), the content, which binaryen
#   inlined into 3831 (MontaConteudoTLV, a chosen name; a prologue of its own in 3831, and clang keeps it a call at cost
#   800), then EncodeTLV("sup", content); clang keeps 3831 a call in 5890 (cost 380). The content's string is
#   default-constructed, then assigned the encoded "pkg": the target moves EncodeTLV's result from a temporary into it,
#   where `std::string conteudo = tags.EncodeTLV(...)` constructs it in place (49 over 301 rows, 2 inserted, 11 deleted,
#   against 34 over 299, operand-only). The key reaches std::format as an int (argument type 3): the parameter is a
#   ueint32, a choice.
# - The four tags are `const std::string`s of external linkage, declared in iinterfacesavd.h. Constant std::strings of
#   three characters need no initializer or destructor, and the target has neither (no target function loads 494896 to
#   494943 but 3831 and 5892: the i32.const and offset= search of how-to step 1 on the split's pieces). With external
#   linkage clang emits them in the order the file defines them, the target's (sup, pkg, key, fil); in the anonymous
#   namespace this object held them fil, sup, pkg, key (wasm-objdump -x -j Data). Names chosen.
# - EnviarAcaoHSM: binaryen inlined IInterfaceSavd::EnviarAcaoHSM into 5889 (a prologue of its own; clang keeps it a
#   call, cost 370). It refuses an ESavdAplic or an action above 255 and an action above 1, sends the bytes {254,
#   action} with the command 0x1604 through 3829 and keeps the returned text at +4. The bytes are a
#   std::vector<uebyte>(2) with both assigned: the target stores the zeroed pair merged with 254 as one 16-bit store,
#   then the action. The request takes its ESavdAplic, then its command; the two assignments the other way round store
#   them the other way round (3 rows inserted, 3 deleted).
# - AssinarArquivo (5891): the same over {254, operation, file} with a command and the ESavdAplic, refusing an
#   ESavdAplic above 255, a command above 65535 or a file above 255 (signed compares for the two ueint32). The target
#   stores the three bytes one by one, so the operation (61 in the target) is a parameter at clang's time, which
#   binaryen folds (5891's wasm type has four parameters): the roots pass 61 from both stand-ins. std::vector<uebyte>(3)
#   with the three assigned stores the end pointer before the bytes, as the target does; a braced list stores it after
#   them (18 over 131 rows, 6 inserted, 6 deleted). The request's two assignments are in 5889's order.
# - 3829 (named by 5889's call): sends a byte vector and returns the failure's text, empty when the SAVD accepts.
#   The response vector lives in a block scope of its own, from its declaration to the end of the error branch, and
#   `return "";` follows the block. Evidence: on the accepting path the target frees the vector and then stores the
#   empty text (`i32.store8[p0] = 0; i32.store8[p0+11] = 0` after the free, in a block of their own: pnpm wasm fn on
#   3829), where a `return "";` inside the vector's scope stores the text first and shares the release with the other
#   returns. Measured in the plain link, this object compiled with each form and linked (pnpm wasm score against 3829):
#   the scope as written, 31 over 485 rows, every one operand-only and each a call or data operand; the scope opened
#   above the header's two stores instead gives the same module (cmp of the two wasm files). Before it, the body
#   matched no form: 78 over 498 rows (28 of the 32 replaced rows operand-only, 13 inserted, 33 deleted), where the
#   blocks of the early returns and of the response vector's release nested otherwise. Measured then: with the
#   response's checks returning early and the header built by a ConverteHeader overload over the vector, which clang
#   keeps a call (cost 250, threshold 250) and binaryen inlines with the buffer behind a pointer, 224 over 552; that
#   header built in place, 153 over 539; the error and size tests nested as in 3830, 84 over 500, and with the
#   message's size read once into a local, 78 over 498 (both kept); then an `inline` overload, 337 over 665;
#   `if (!header->erro) return "";` ahead of the nested size test, 90 over 506.
# - DescricaoArquivo (5905): a switch over the ESavdArquivoUE 25 to 120 returning each file's text, default "Arquivo nao
#   identificado"; clang makes the table of 96 pointers, which the target holds at 1551420, after carquivossavd.cpp's
#   records and before cinfomtlcd.cpp's (ledger/source-locations.tsv). The enumerators are not recovered, so the case
#   labels are the values; its being a free function is a choice. Its line, after operator[], is a choice.
# Added since: the two SAVD requests CAssinador::AssinaArquivosResultado makes (unit 34's paragraph), neither with a
# target index: fn 12098 (vota::CGravaResultado::StartState) holds that member inlined, and inside it each of these
# behind a stack frame of its own (496 and 32 bytes, at lines 3183 and 3097 of pnpm wasm fn's folded readout of 12098;
# binaryen's inlining of a function with one caller), so they match only with 12098:
#   AssinarEcourna  record iinterfacesavd.cpp 1022:15, code 7338
#   IInterfaceSavd::EnviarLocal, a chosen name  no record
# - AssinarEcourna: AssinarUE's form, `if (!savd.AssinarArquivo(aplic, comando, 61, arquivo))` it throws 7338 with
#   std::format("Falha ao assinar ({}-Ecourna[{}])", savd.GetMensagem(), arquivo) (types string and int, 109), the
#   record's four parameters; 12098 passes 5891 the ESavdAplic, the command 128 and the file, and 5891's folded
#   operation is 61 for both its target callers. That AssinaArquivosResultado passes 128 and AssinarEcourna passes 61 is
#   the choice Assina's 66 and AssinarUE's 61 are. EUE_COMUM_ASSINAR_ECOURNA is a chosen name, in euecomumerror.h.
# - EnviarLocal: 12098's 32-byte frame refuses an ESavdAplic above 255 ("Argumento inválido para local."), allocates
#   16 zeroed bytes, then refuses a local whose size is not 15 ("Argumento inválido, tamanho do local.", the bytes
#   freed), stores 254 and the local's 15 characters (one copy, two overlapping 8-byte loads and stores), the command
#   0x404 and the ESavdAplic (in 5889's order: the request's application assigned first, as EnviarAcaoHSM does), sends
#   them with 3829 and keeps the returned text at +4. Two loads of m_mensagem.empty() follow that nothing reads: the
#   caller drops the bool. A member, as it writes +4 and +16; its name is chosen from its texts, the local's type is
#   CAssinador's +36 std::string, and its line (959, before IInterfaceSavd::EnviarAcaoHSM) is a choice. The local's
#   copy is written as std::copy, not measured against the other forms of the same copy.
# - Each function's code in this object holds the readout's calls, constants and stores in its order (wasm-objdump -d,
#   read by hand: with no target index, nothing scores them). ESavdCmdHSM's two values, the actions
#   AssinaArquivosResultado sends 5889, get names in iinterfacesavd.h, chosen from the CLogComum logs beside the calls.
# - With these and unit 34's, 111's and 165's members written (3829's form as before) and nothing calling them, every
#   object the headers' edits rebuilt compiled cmp-equal to the base's but the four sources' own, and the plain link was
#   byte-identical to the base's (sha256 8a9bce39); wasm-ld drops them, as 12098 is not written.
#
# Added since: the request over a package and a file, which fns 4625 and 11179 call, and the ValidarUE over a file:
#   5892  IInterfaceSavd::VerificarArquivo, a chosen name                    no record of its own; matched
#         with MontaRequisicaoTLV over a file (a chosen name) and unit 33's CGenericTags::DecodeTLV and WalkTreeTLV
#         (records cgenerictags.cpp 110:15 and 136:15), which binaryen inlined into it
#   ValidarUE(IInterfaceSavd &, ESavdAplic, const std::string &, const std::string &)  record 898:15, code 7324; no
#         target index: binaryen inlined it into 11179 (comum::CSigVerifier::Verify, unit 26's), its one caller
# - VerificarArquivo (5892): it refuses an ESavdAplic or a key above 255 (or-ed, compared unsigned) or an empty package
#   or file, storing "Argumento inválido assinar verificar arquivo." at +4, the text its name is chosen from; then it
#   builds the request TLV over the file, zeroes a request whose i64 store holds the command 0x1001 (a constant at
#   clang's time, so a literal of the function, not a parameter: 5890's paragraph above has the sign), stores the
#   ESavdAplic at +1 with a byte store of its own and sends it with 3830. A member, as it writes +4; the key is a
#   uedword, the unsigned parameter of the two readings iinterfacesavd.h gives (chosen). It is defined before
#   AssinarArquivo (5891): 5892 links first of this file's band-2 rows (5892 to 5889), its line a choice in the blank
#   run after 3829.
# - MontaRequisicaoTLV over a file: behind a 48-byte frame of its own inside 5892, so binaryen inlined it, and clang
#   keeps it a call (-Rpass-missed=inline on this file): the four tags inserted (CriaTags), 3831's TLV of the package,
#   its "sup" decoded with DecodeTLV, fil{file} appended with AppendTLV and "sup" encoded again with EncodeTLV, the frame
#   holding the tags, 3831's TLV and the content in that order from the top. An overload of 3831's chosen name, defined
#   after VerificarArquivo (the caller first, as 3830's measured order is; this order is not measured).
# - The ValidarUE over a file: `if (!savd.VerificarArquivo(aplic, SAVD_CHAVE_UE, pacote, arquivo))` it throws 7324 with
#   the package, the file and the SAVD's code and text (the format's types string, string, int, string), as the record's
#   four parameters and 5890's form give; EUE_COMUM_VALIDAR_ASSINATURA_UE_ARQUIVO is a chosen name.
# - The order. 5892 holds this file's helper around cgenerictags.cpp's DecodeTLV and WalkTreeTLV, and 11179
#   csigverifier.cpp's Verify around this file's ValidarUE. The units' lists linked csigverifier.cpp.o (unit 26) and
#   cgenerictags.cpp.o (unit 33) ahead of this list, where the target's data has iinterfacesavd.cpp, cassinador.cpp,
#   csigverifier.cpp, then cgenerictags.cpp (records at 1552548, 1553268, 1576892 and 1584416). Measured with pnpm wasm
#   score, the first link of these sources and scratch links of its link.cmd with objects moved (workflow.md W13):
#   - both in their units' places, WalkTreeTLV's last character as campo.back(): 11179 55 over 436 rows (2 inserted, 2
#     deleted, local numbers at the call of 5892), 5892 503 over 1596 (44 inserted, 51 deleted);
#   - both moved after iinterfacesavd.cpp.o: 11179 26 over 434, all operand-only; 5892 176 over 1564 (12 inserted, 17
#     deleted), and with unit 33's `*campo.rbegin()` 81 over 1552, all operand-only;
#   - with rbegin, csigverifier.cpp.o alone after cassinador.cpp.o: 11179 26 over 434, 5892 491 over 1588 (36
#     inserted, 38 deleted);
#   - with rbegin, both after cassinador.cpp.o, in the data's order: 26 over 434 and 81 over 1552, all operand-only.
#   So both files are listed here after cassinador.cpp, in the data's order, and both rows match; units 26 and 33 keep
#   their notes and rows (src/units/README.md "Names"). Against each object's first record in
#   ledger/source-locations.tsv (objects with none left out), on the plain link.cmd at b5d3f599, the move of
#   csigverifier.cpp.o (from fragment 26's place) puts 60 of the 102 objects it passes in the data's order and inverts
#   42, whose records lie after its 1576892: api/gui's ctextfield, ctextfielddoubleline, ctextfieldmt, ctextfieldpaper,
#   ctextfieldupdate, ctextfieldblinking, ctextrectfield, ctextbox, cframedtext, cimagefield, cimagefieldupdate,
#   cdsimagefield, cmoviefield, cledfieldmt, cqrcodeimage, cprogressbar, cstepsprogressbar, cformbuilder,
#   cinputmenufield and reports/creport, api's util/csystem, util/isystemdatetime, audio/alsa/cwavfile,
#   uelog/cescritorlog and hwil/iimpressorarelatorios, vota operador's outrasopcoes/caguardaeleitoresvotarem,
#   cencerramentohorarioinvalido and cescolheopcao, confirmaidentidade/cnomeeleitor, cdigitalreconhecida,
#   cdigitalnaoreconhecida, cpededigital and cregistradigitaloperador, and comum/cinformacaothreadoperador, and comum's
#   comparecimentomesario/ccontroladorreconhecimetomesario, cregistradormesario, estados/cmesarioregistrado and
#   ipedetitulomesario, comparecimentomesario/dao/ccomparecimentomesariodao,
#   reconhecimentobiometrico/ccontrolaarmazenamentodeimagens, gravadores/asn/cassinavotavelbu and cconversorentidadebu;
#   the move of cgenerictags.cpp.o (from fragment 33's) puts 63 of the 69 it passes in the data's order and inverts 6
#   (cwavfile, isystemdatetime, cescritorlog, cinformacaothreadoperador, ipedetitulomesario, ccomparecimentomesariodao;
#   cqrcodeimagepaper.cpp.o links in unit 196's list, before both places, and is passed by neither). The end of this
#   list is the place in it that inverts fewest (cassinador.cpp's records lie before both files', csigverifier.cpp's
#   before cgenerictags.cpp's), and steps 6 to 10 on this list lose no match.
# - Measured before, in a scratch link at the tree's flags then and in the units' order (each form kept here): 597 over
#   1643 rows first; the key compared unsigned (a plain enum compares it signed), 591 over 1639; the invalid marker a
#   `break` out of the walk where it was a second `return std::string::npos`, 564 over 1624 (read as clang's cleanup
#   destinations of a while: 1 return, 3 break); the hexadecimal length a named std::string in both functions, freed at
#   the end of its scope where the temporary was freed after HexToInt, 503 over 1596. What that left, clang reusing the
#   marker substr's source pointer for the field's last character where the target computes it again, is the spelling
#   unit 33's fragment measures, and the rows of local numbers were the order's (a reading of the four links above).
# - The roots: VerificaArquivo stood for fn 4625, 5892's other target caller, and went when 4625 was written (unit 168):
#   5892 has two call sites, 11179's inlined ValidarUE and 4625's inlined Validar, and binaryen keeps it out of line.
#
# Evidence and choices. The records fix each throw's line and each function's name and types. Chosen, and marked where
# declared: every enumerator's name, ESavdChaveValidar's and EExtensaoArquivoResultado's enumerator names, the two
# request and response structs' members, IInterfaceSavd's slot and member names, EnviarRequisicao and ConverteHeader
# (no record: their roles), the maps' names and every header's path. EExtensaoArquivoResultado's enumerators are defined
# in carquivosresultado.h, the one reader of its values; iresultado.h keeps its opaque declaration. Chosen too, for its
# inline cost at the tree's -O3: that ConverteHeader fills in the request's mark and size from the data. Taking the
# request and the data, it costs 255 at its call and stays a call (-Rpass=inline -Rpass-missed=inline on this file), and
# 3830 scores 81 over 1168 rows in the whole link, all operand-only, and matches. With the two stores in
# EnviarRequisicao it costs 230 (3830: 331 over 1335 rows, 167 inserted), with the size passed for the data 235 (328
# over 1332): both are inlined at -O3, and both stayed calls at -O2's 225. No target body shows where the two stores
# belong: binaryen inlined the helper into 3830, where either form puts them. 3829 holds the same two stores and copy
# over a std::vector in its own frame (above).
# What the bytes decide, measured on this unit's objects at -O2, the tree's level then, function by function with
# object-local numbers masked:
# - the `case` order of 347 and 5900: moving 347's first case or 5900's first or SEINT's case changes the br_table (the
#   target's [11 0 1 3 4 5 6 7 8 9 2] for 5900), so the order written is evidence, SEINT (59) after SECINP (51);
# - the format argument of 347 is an int (argument type 3), of 275, 680 and 5900 a handle (type 15);
# - EnviarRequisicao's `m_mensagem = ""`: the size is stored before the terminator; clear() stores them the other way;
# - ConverteHeader's std::copy into a std::back_inserter keeps the vector in memory through the loop, with the one
#   store of 0 before the allocation, as the target does; a push_back loop promotes it to locals (146 lines against 132);
# - ConverteHeader stays a call in 3830, at the tree's -O3: the target keeps it out of 3830 for binaryen, and clang
#   inlines it when its cost at the call is at most -O3's threshold of 250 (the chosen form above says how it stays out);
# - DesconverteMensagem's std::copy: an index loop and an iterator loop give other code;
# - the order of `if (header->tamanho)`'s two branches: the other gives other code;
# - the order of the definitions, measured in the whole link (pnpm wasm score, rows that differ of the body's rows):
#   ConverteHeader, DesconverteHeader, DesconverteMensagem, EnviarRequisicao 379 over 1191; ConverteHeader,
#   EnviarRequisicao, then the two Desconverte 130 over 1178; EnviarRequisicao, ConverteHeader, then the two Desconverte
#   81 over 1168, every one operand-only. EnviarRequisicao, the two Desconverte, then ConverteHeader gives the same module too, so what
#   decides is that the caller stands before all three helpers; ConverteHeader's place and the exact lines are a choice.
# Forms that give the same function (measured the same way), the one written first:
# - 275, 680: `const auto it` and `auto it`;
# - 347: the case falling out of the switch and `default: break;`; static_cast<int>, a C cast and unary +;
# - 275, 680, 5900: the formatter of iinterfacesavd.h, written as an explicit specialization with a template format,
#   with a format over std::format_context, as a template constrained on std::is_enum_v over formatter<unsigned int>,
#   and over the underlying type made unsigned. A template over the underlying type alone needs plain enums: over an
#   int enum it gives formatter<int>'s body, the target's 1711, not 536;
# - DesconverteHeader: `size != sizeof` and `sizeof != size`;
# - EnviarRequisicao: `m_mensagem = ""`, `= {}`, erase() and resize(0); `const uebyte erro` and `const bool erro = ... != 0`;
#   `if (header->tamanho)` and `!= 0`.
#
# Added since: comum::CArquivosSavd's construction and singleton in carquivossavd.cpp, comum::AssinarUE in
# iinterfacesavd.cpp, and app/comum/gravadores/cassinador.cpp moved into this list from unit 34's:
#   1164  CArquivosSavd::GetInst, with the constructor and its three loaders inlined  matched (below)
#   5907  CArquivosSavd::~CArquivosSavd                                              matched
#   3839, 3840, 3841  the three maps' __tree::destroy (each calls itself)           matched, named by 5907's calls
#   11658, 11657      the exit destructors of s_instancia and s_mutex (slots 2144, 2145)  matched (below)
#   AssinarUE  record iinterfacesavd.cpp 1004:15, code 7336; no target index: binaryen inlined it into 1277
#              (comum::CAssinador::Assina, unit 34's), its one caller, behind a stack frame of its own
# - GetInst: a std::lock_guard on s_mutex (@1838520; 1164 unlocks it through fn 150), s_instancia.reset(new
#   CArquivosSavd) on a 36-B object of three std::maps (+0 by ESavdPacote and +12 by ESavdArquivoUE, the two operator[]
#   read; +24 by a third key), as CArquivosResultado's GetInst does. The statics are defined in that order, s_instancia
#   then s_mutex: their exit destructors take table slots 2144 and 2145 in that order (wasm-objdump -x -j Elem). 1164
#   holds the constructor and, behind two stack frames of their own (80 B, then 32 B), the loaders of the +0 and +12
#   maps, so the loaders are functions binaryen inlined, each with one caller; that the +24 map's twenty entries, which
#   need no frame, are a third loader and not the constructor's own statements is a choice, and so are the three
#   members' names, and the constructor's being out of line (a reading: at -fPIC clang keeps a C1 call in its own TU,
#   docs/reference/facts/codegen.md C6, and binaryen inlines a function with one caller). The 188 insertions are written in the target's order from 1164's readout: `m[key] = value`, the value
#   built before the insertion (C++17 orders the right side first) from CPath's builders `/` a name, `.string()` (the
#   implicit conversion is the other spelling, not measured), with `+` a name of CArquivosResultado's or a literal, or a
#   literal assigned after it; the keys are the target's constants, written `ESavdPacote(120)` (the enumerators are not
#   recovered). One builder has no target index: binaryen inlined it into 1164, `s_pathRoot /
#   path("/dsk/fe/dinamico/trab/").relative_path()` in a frame of its own, the form of CPath::GetPathMR (949); it is
#   CPath::GetPathTrabExterno in unit 190's cpath.cpp, a chosen name. The +24 map's key is a signed type of its own
#   (carquivossavd.h says why); no target function reads that map.
#   1164 matches with strict aliasing in this TU: src/Makefile lists carquivossavd.cpp in UENUX2_TBAA_DIRS, the one file
#   of src/app/comum/'s own directory there (docs/reference/facts/app-flags.md F6). With uenux2's -fno-strict-aliasing
#   every map insertion reloads __child before __tree_balance_after_insert (fn 152), F6's sign: our body is 80384 B
#   against the target's 77002 B and scores 35926 over 37186 rows (1692 inserted); with strict aliasing it is 77000 B and
#   scores 1850 over 35494, every row operand-only. Built so in place, step 8 names s_mutex by 1164's operand (vote:1
#   by:1164) and s_instancia by 1164's and 11658's (vote:6), and step 9 matches 1164, 11658 and 11657, our s_mutex's
#   exit destructor, which the scan pairs by its body. A private link with that one object changed, scanned with the
#   plain link's symbol file, moves none of the three: their names come from step 8 at the flag, so s_mutex takes no
#   hand line (one of CFederacoes::s_mutex's form, tried, carries nothing there: without it the same three match).
# - The destructor is out of line, `= default` in the .cpp, as CArquivosResultado's is: 1164 and 11658 call 5907. 3839
#   to 3841 follow 5907's calls, the +24 map first.
# - AssinarUE: `if (!savd.AssinarArquivo(aplic, comando, 61, arquivo)) throw CUeComumError(EUE_COMUM_ASSINAR_UE,
#   std::format("Falha ao assinar ({}-UE[{}])", savd.GetMensagem(), arquivo))`, the record's four parameters; in 1277
#   it passes 5891 the ESavdAplic, the command 66 and the file. That Assina passes 66 and AssinarUE passes 61 is a
#   choice: both are constants in the one inlined body, and the other placements were not measured. The enumerator
#   ESavdAplic's SAVD_APLIC_VOTA (1) and EUE_COMUM_ASSINAR_UE are chosen names, marked where declared.
# - cassinador.cpp joins this list after iinterfacesavd.cpp (src/units/README.md "Names"): 1277 holds AssinarUE
#   inlined, and with cassinador.cpp.o linked before iinterfacesavd.cpp.o, its unit 34 place, 1277 scores 151 over 376
#   rows (7 inserted, 7 deleted, local numbers); after it, in a copy of link.cmd with that one object moved, 31 over 369,
#   all operand-only, and it matches in the link with this list.
# - The roots: ValidarUE's two stand-ins stood for 3288 and 3290, now in the link (unit 168), and are gone; AssinaArquivo,
#   AssinaDoisArquivos, DescreveArquivo and DescreveDoisArquivos stand for 12098 still (1277 is in the link), and the
#   stand-ins of 275's and 680's callers for the ones not written (1501, 1836, 4657, 4682 and 4687 are).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_SRCS := src/app/comum/carquivosresultado.cpp src/app/comum/carquivossavd.cpp src/app/comum/cpacotearquivos.cpp src/app/comum/iinterfacesavd.cpp \
    src/app/comum/gravadores/cassinador.cpp src/app/comum/relatorios/csigverifier.cpp src/api/util/cgenerictags.cpp
UENUX2_SRCS += $(APP_COMUM_SRCS)
# cassinador.cpp includes app/comum/dados/cconfiguracaoeleicao.h (its second constructor reads the pleito), whose
# ecourna headers include Boost, as cgravadorutil.cpp does (unit 122): an include path, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cassinador.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# their callers are not reconstructed yet: 95-uenux2-app-comum-roots.cpp gives each two call sites
$(ROOT)/$(APP)/95-uenux2-app-comum-roots.o: $(ROOT)/src/units/95-uenux2-app-comum-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/95-uenux2-app-comum.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/95-uenux2-app-comum-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/95-uenux2-app-comum-roots.o
