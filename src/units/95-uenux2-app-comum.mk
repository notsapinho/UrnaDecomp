# uenux2 src/app/comum's root files over comum::EUeComumError, at the paths their std::source_location records name,
# listed in the name order the directory links in: comum::CArquivosResultado::operator[] (target fn 347) in
# carquivosresultado.cpp (record 99:11), comum::CArquivosSavd::operator[] (275, 680) in carquivossavd.cpp (49:15, 73:15),
# comum::CPacoteArquivos::RetornaNomeChave (5900) in cpacotearquivos.cpp (162:11) and
# comum::IInterfaceSavd::EnviarRequisicao (3830) in iinterfacesavd.cpp, which binaryen holds with the two static members
# the records name, DesconverteHeader (553:15, 559:15) and DesconverteMensagem (568:15, 574:15, 578:15), and with
# ConverteHeader; the class headers beside them and app/comum/euecomumerror.h, with the handle formatter of the three
# SAVD enums. The formatter's handle body (fn 536) is the one binaryen keeps for every such enum, ours named by the
# table vote of 275, 680 and 5900; it stays unresolved on libc++'s __fields_integral, and no match here waits for it.
# 480, CBaseError<comum::EUeComumError, ...>'s constructor, is named by the calls and matches with this header's enum:
# it is a thunk of 710, the body unit 94's form gives (the constructor in ecourna/api/exception/cbaseerror.hpp).
#
# comum::CPacoteArquivos::TrataErroPacote (5901, record 169:11), added after the unit landed: it throws code 7222 with
# the key's name (5900 on +24), the package's name (the std::string at +0) and IInterfaceSavd's code and text (+16, an
# int: argument type 3; +4); the getters on IInterfaceSavd and their names are chosen. Fn 4625 (not reconstructed)
# builds the object in its frame and gives the layout: +0 a std::string, +12 a std::vector (its begin and end compared,
# its elements walked), +24 the ESavdChaveValidar, +28 and +32 words. The vector's element type and every member's name
# are chosen; +28 and +32 are not declared, since nothing written reads them. The target's band (uses 2) has 5901
# ahead of 5900 in the link. A reading: 4625, whose records lie at lines 85 to 116 and whose body calls 5901 before
# 5900, is defined above both, and a function takes its place at its first mention; with 4625 not written our object
# has them the other way round.
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
#   3829  the second IInterfaceSavd::EnviarRequisicao: written, `differs` (below)
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
#   the key, a plain ESavdChaveValidar, signed, where 4625 or-s it with the ESavdAplic and compares unsigned
#   (`i32.le_u(i32.or(l3, l10), 255)`): 4625's landing decides between `ESavdChaveValidar : unsigned int` and an
#   unsigned key parameter (iinterfacesavd.h has the two readings). No byte of 5890 depends on it, since 5890 passes the
#   constant 53.
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
#   Written, not matching: 78 over 498 rows (28 of the 32 replaced rows operand-only, 13 inserted, 33 deleted), where
#   the blocks of the early returns and of the response vector's release nest otherwise; the remainder is not explained.
#   Measured (pnpm wasm score against 3829): with the response's checks returning early and the header built by a
#   ConverteHeader overload over the vector, which clang keeps a call (cost 250, threshold 250) and binaryen inlines
#   with the buffer behind a pointer, 224 over 552; that header built in place, 153 over 539; the error and size tests
#   nested as in 3830, 84 over 500, and with the message's size read once into a local, 78 over 498 (as written); then
#   an `inline` overload, 337 over 665; `if (!header->erro) return "";` ahead of the nested size test, 90 over 506. It
#   stays written: 5889 and 5891 call it and match.
# - DescricaoArquivo (5905): a switch over the ESavdArquivoUE 25 to 120 returning each file's text, default "Arquivo nao
#   identificado"; clang makes the table of 96 pointers, which the target holds at 1551420, after carquivossavd.cpp's
#   records and before cinfomtlcd.cpp's (ledger/source-locations.tsv). The enumerators are not recovered, so the case
#   labels are the values; its being a free function is a choice. Its line, after operator[], is a choice.
# Not written here: the ValidarUE over a file and AssinarEcourna, which binaryen inlined into 11179 and 12098 (AssinarUE,
# inlined into 1277, is written: the paragraph on CArquivosSavd below); and 5892, the request over a package and a file that 4625 and 11179 call, which nothing in the link needs yet,
# so it is out, with this measurement. 5892 refuses an ESavdAplic or a key above 255 (or-ed, unsigned) or an empty
# package or file ("Argumento invalido assinar verificar arquivo."), then calls a function binaryen inlined (a prologue
# of its own) that builds sup{pkg{package} key{key}} with 3831, decodes the content of its "sup" with
# CGenericTags::DecodeTLV, which binaryen inlined, as it inlined WalkTreeTLV into that (records cgenerictags.cpp:110
# and 136, codes 7020 and 7021), appends fil{file} with AppendTLV and encodes "sup" again with EncodeTLV, and sends it
# with the command 0x1001 through 3830. WalkTreeTLV walks the TLV from position 0: the tag's characters, the length
# marker after them, which must be one of '<' to '?' (the target's `(c & 252) == 60` over a one-character substr, read
# as `find_first_not_of("<=>?") == 0`), the hexadecimal length (2 * (marker - ';') digits, CStringUtils::HexToInt),
# and the value. Written so in a scratch link (pnpm wasm score against 5892): 597 over 1643 rows (91 inserted, 95
# deleted) first; with ESavdChaveValidar given `: unsigned int` (a plain enum compares the key signed), 591 over 1639;
# the invalid marker a `break` out of the walk where it was a second `return std::string::npos`, 564 over 1624 (read as
# clang's cleanup destinations of a while: 1 return, 3 break); the hexadecimal length a named std::string in both
# functions, freed at the end of its scope where the temporary was freed after HexToInt, 503 over 1596 (44 inserted, 51
# deleted).
# What remains: clang computes the one-character substr's source pointer (campo.data()) once and reuses it for
# campo.back(), where the target computes it again in each place (our cgenerictags.cpp.o already holds the shared
# select, at -O2 and with -fno-strict-aliasing as well; spelling the marker with an if-initializer, std::string's
# constructor, `campo[campo.size() - 1]` or `!= std::string::npos` changes nothing there, and a helper or a lambda drops
# the one-character string the target keeps); the other inserted and deleted rows are local numbers, and the operand
# order of compares, which on both sides puts the lower-numbered local first (a reading). Not explained.
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
#   1164  CArquivosSavd::GetInst, with the constructor and its three loaders inlined  written, unresolved (below)
#   5907  CArquivosSavd::~CArquivosSavd                                              matched
#   3839, 3840, 3841  the three maps' __tree::destroy (each calls itself)           matched, named by 5907's calls
#   11658, 11657      the exit destructors of s_instancia and s_mutex (slots 2144, 2145)  wait for 1164 (below)
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
#   1164 differs by strict aliasing alone. This TU builds with uenux2's -fno-strict-aliasing (src/app/comum/'s top-level
#   files are not in UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6: a choice no row had decided), and every map
#   insertion then reloads __child before __tree_balance_after_insert (fn 152), F6's sign: 80384 B against 77002 B. In a
#   copy of link.cmd with carquivossavd.cpp.o alone compiled from its own compile line without -fno-strict-aliasing
#   (workflow.md W13, "One variant object"), 1164 scores 1850 over 35494 rows, every one operand-only, a scan of that
#   link with the committed symbol file moves no row into or out of match, and with one more line in a copy of the
#   symbol file, a callers+content line for s_mutex of CFederacoes::s_mutex's form (GetInst unlocks it, its exit
#   destructor destroys it, both through fn 150), 1164, 11657 and 11658 match and splat-build gives the target's sha256
#   with 11097 matches. So 1164 waits for strict aliasing in this TU, a flag decision that is not this unit's to make, and
#   11657 and 11658 wait with it: s_mutex's one other reader is 1164, and s_instancia's line reads vote:2 by:11658.
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
    src/app/comum/gravadores/cassinador.cpp
UENUX2_SRCS += $(APP_COMUM_SRCS)
# their callers are not reconstructed yet: 95-uenux2-app-comum-roots.cpp gives each two call sites
$(ROOT)/$(APP)/95-uenux2-app-comum-roots.o: $(ROOT)/src/units/95-uenux2-app-comum-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/95-uenux2-app-comum.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/95-uenux2-app-comum-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/95-uenux2-app-comum-roots.o
