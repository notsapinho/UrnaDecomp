# uenux2 comum::gravadores over comum::EUeComumGravadoresError (app/comum/gravadores/euecomumgravadoreserror.h), in the
# files the records name, paths relative to src/uenux2:
# - CBaseError<comum::EUeComumGravadoresError, SErrorLimits{8600, 8800}>'s constructor (target fn 283, a thunk of fn 710
#   that passes the vptr 1552984), which the header's alias instantiates; the symbol file names it by that vptr.
# - comum::CGravadorUtil (src/app/comum/gravadores/cgravadorutil.{h,cpp}): ConverteFase (target fn 2274, record :97).
#   DeterminaNomeArquivo (fn 3798, a chosen name) with DeterminaNomeArquivoSemLetra (records :28, :33, :38), which
#   binaryen inlines into it (its second stack frame), matches at the tree's -O3 (below).
# - comum::asn::ConverteSerialFlash (target fn 3605, records :26 and :31) and DesconverteSerialFlash (fn 3604, record
#   :54, matched at the tree's -O3: below) in src/app/comum/gravadores/asn/util.cpp, with the header util.h beside it,
#   which also declares comum::asn::CalculaHashSha512 (fn 3602, no record). That function and its CSha512 pointer
#   block (10277, 10279) are fragment 321's, in gravadores/asn/cassinavotavelbu.cpp with its callers, the members of
#   comum::asn::CAssinaVotavelBu: the target's table gives the block's slots, and the class's statics', after
#   cconversortipoapuracaosa.cpp's, so after util.cpp's object (cassinavotavelbu.h has the slots and the records).
# - comum::md::CVersoesArquivos's constructor (target fn 5867) with ValidaCriacao (records :28, :33), which binaryen
#   inlines into it, in md/cversoesarquivos.cpp, the class header beside it; libc++'s hinted emplace into its
#   std::map<std::string, std::string> (fn 1221) comes from that object. The hinted __find_equal it calls (fn 1346)
#   matches under the symbol of std::set<std::string>'s, a twin (the two compare only the key), from the tree root
#   app/roots_set.o (splat/scan.tsv's object column), since the Boost probe's std::map<std::string, unsigned short>
#   copy, which matched before it, left the link.
# - comum::IGravador's constructor (fn 1396) with IResultado's (record iresultado.cpp:40) inlined by binaryen, written
#   in iresultado.cpp and matched at the tree's -O3 (below); comum::CGravadorWSQ's constructor (target fn 3796) with
#   ValidaTipoBiometria (record cgravadorwsq.cpp:73) inlined by clang; comum::CGravadorRCSecao::CriaIdentidadeEleitor
#   (target fn 5845, record cgravadorrcsecao.cpp:230). The class heads are unit 60's (igravador.h, iresultado.h,
#   cgravadorwsq.h) and the head-only cgravadorrcsecao.h; this unit declares there the constructors and members it
#   writes.
# - IResultado's destructor (fn 12090, unit 60's match): its copy in the link now comes from iresultado.cpp.o, which
#   emits IResultado's vtable with the constructor, ahead of unit 102's roots object; the same symbol, and it still
#   matches.
# - comum::IGravador's Slot2, Slot6 and Slot3 (target fns 11632, 11631 and 11630, slots 2, 6 and 3 of IGravador's vtable
#   and of the eight recorders' that hold them), in iresultado.cpp after the constructor, in the order their use band
#   gives. Slot2 is the class's key function, so iresultado.cpp.o emits IGravador's vtable now, where unit 60's pending
#   object did.
#   Each slot builds two paths from comum::CPath's directories (GetPathTrab and GetPathResult over EFlashOrigem, fns
#   436 and 1274) and the file name at +20 (std::filesystem::path's operator/), and calls api::CSystem::CopyFile (fn
#   378) on their strings: Slot2 and Slot6 copy the work file to the result directory of the internal and of the
#   external flash, Slot3 copies the work file and then the result file from the internal flash to the external one.
#   The target's calls pass 0 for the CopyFile bool its type keeps, so the slots pass false there; true for the bool
#   binaryen folded is unit 32's choice of which bool that is and of its value (api/util/csystem.h). Measured in this
#   link before step 8 (pnpm wasm score against the target): 11632 19 over 294 rows, 11631 19 over 294, 11630 38 over
#   582, every one operand-only and every operand a call's or a data address. The paths are named locals, as the
#   target keeps each to the end of the function (Slot3 destroys its four there, the last built first); `const` on
#   them and their names are chosen, and no other form was measured.
# - comum::IGravador's Slot4 and Slot5 (target fns 11634 and 11633, slots 4 and 5), in iresultado.cpp before Slot2, in
#   their use band's order (11634, 11633, then 11632), where unit 60's pending object trapped them until the type of
#   GravaResultado's parameter was declared: its records spell api::CFile, which api/io/cfile.h makes an alias of
#   ecourna::api::io::CFile, and igravador.h and app/comum/asn/iconversorparcialasn.h include it in place of their
#   forward declarations. Each builds the path of the file in the work directory of one flash (CPath::GetPathTrab
#   with FLASH_INTERNA or FLASH_EXTERNA, fn 436, then / m_nomeArquivo), opens it with ecourna's CFile constructor (fn
#   517, the mode "wb"), passes it to GravaResultado (slot 7) and closes it (fn 336); the CFile's inline destructor
#   follows.
#   Measured in this link before step 8 (pnpm wasm score against the target): 11634 and 11633 15 over 210 rows each,
#   every one operand-only and every operand a call's or a data address. The path is a named const local, a choice;
#   no other form was measured. The include changes the mangled name of every GravaResultado (traps and declarations:
#   units 60, 122, 136 and 200's pending objects, cgravadorenvelopearquivo.cpp.o's vtable reference), and no other
#   object of the link (every object compared with cmp before and after).
# - CGravadorRCSecao's implicit deleting destructor (fn 11615, slot 1): cgravadorrcsecao.cpp emits the class's vtable
#   with GravaResultado (fn 11616, slot 7, record cgravadorrcsecao.cpp:110, below), its key function; the roots keep
#   the vtable for 12098, which stores it and is not written. cgravadorrcsecao.h gives the class its layout (60 bytes,
#   from fn 12098, which builds it); slot 0 holds IResultado's destructor (fn 12090).
# - Two inline accessors under chosen names, CConfiguracaoEleicao::GetPleito() and md::CPleito::GetID(): fn 3798 formats
#   the word at +28 of CConfiguracaoEleicao, its CPleito's identifier. With the unit's edits of headers (these two and
#   unit 60's), every object the link held before is byte-identical (542 objects, sha1 before and after).
#
# comum::CGravadorWSQ's members (cgravadorwsq.cpp; the class head is unit 60's cgravadorwsq.h), which empty unit 60's
# pending object:
# - Slot2 (fn 11579), Slot6 and Slot3: the result file's path on the internal (Slot2) or external flash (CPath::
#   GetPathResult, fn 1274, with FLASH_INTERNA or FLASH_EXTERNA, then / m_nomeArquivo) passed to CompactaWsq with false
#   (Slot2, Slot3) or true (Slot6); Slot6 and Slot3 do it only when the byte at +84 (m_gravaMidiaExterna) is set. They
#   differ in that bool alone, and binaryen merges them into one body, the target's fn 6041 (our
#   byn$mgfn-shared$_ZN5comum12CGravadorWSQ5Slot6Ev), with the slots its 9-byte thunks 11577 and 11578 passing 0 and 1;
#   they are not called anywhere else. Their order in the file is band 1's (11579, 11578, 11577). Measured (pnpm wasm
#   score against the target, before step 8): with CompactaWsq taking the file name as a std::string by value, 11579 and
#   6041 scored 51 over 159 and 51 over 165 rows, a 64-byte frame where the target's is 48: the target reuses the
#   directory temporary's slot for the converted string; taken as const std::string& with the path passed to it (its
#   conversion's temporary), every row is operand-only (10 over 155, 10 over 161) and they match. The named const local
#   for the path is IGravador's slots' form, a choice that gives these rows; no other spelling was measured.
# - CompactaWsq (fn 5821, a chosen name): GetCaminhoCorretoExternal() or GetCaminhoCorretoInternal() by the bool, then
#   for each directory CSystem::ExistDir (fn 5459) and, when it is missing, api::CreateDir (csystem.cpp, inlined by
#   binaryen with its own frame), and CSystem::IsEmptyDir (fn 2762) while every directory so far was empty; when all
#   are empty an ecourna::api::compression::CZip (fn 5193) of the file at ENivelCompressao::PADRAO (2), closed at once,
#   else one at NENHUM (0) to which each directory + "*.wsq" is added through ICompressor::Add(const path&), which
#   binaryen inlines (its one caller in both links), then CZip::Close (2691) and the destructor (2690), which czip.cpp
#   defines out of line (unit 06's fragment). The target's first branch is the internal one (an i32.eqz before the if):
#   `!midiaExterna ? GetCaminhoCorretoInternal() : GetCaminhoCorretoExternal()` puts the internal call first in
#   cgravadorwsq.cpp.o, where `midiaExterna ? ...External() : ...Internal()` put the external one (wasm-objdump -d of
#   the object compiled both ways); the conditional's spelling is chosen.
# - GetCaminhoCorretoInternal and GetCaminhoCorretoExternal (records 175:19 and 192:19, binaryen-inlined into 5821 with
#   frames of 480 B each): a switch on m_tipoBiometria whose cases return a vector of the one WSQ directory (5819,
#   5818, 3795 internal; 5817, 5816, 3794 external) as a string, and whose default throws 8652 or 8653 with
#   "Tipo de biometria inválido: {}" over the enum's formatter (cgravadorwsq.h). Their rows are the target's up to
#   operands within 5821's score.
# - The WSQ directories, in pathwsq.cpp (pathwsq.h; GetPathWsqNaoRegistrado, fn 3793, moved there from cgravadorwsq.cpp
#   and cgravadorwsq.h): fns 5819, 5818, 3795, 3793 on the internal flash, 5817, 5816, 3794 on the external one, each a
#   15-byte thunk `f2298(p0, end, begin)` or `f3898(...)` of its literal into a body binaryen merged, 2298 (internal)
#   and 3898 (external), which loads the turn (CAppInfo::GetInst, GetGeral, +32) ahead of its stack prologue, calls
#   CPath::GetPathWsq (fn 2864) with the flash and the turn and appends the literal. Each is written as a function with
#   no argument that reads the turn and calls its overload with the turn, which holds the frame and which binaryen
#   inlines into it (docs/reference/facts/reading.md R10, statements ahead of the body's only prologue). Measured in the
#   whole link: written as one function each in cgravadorwsq.cpp, 2298 scored 14 over 89 (the turn read after the
#   prologue; 34 over 89 when 3793 was the only one written); split in two in cgravadorwsq.cpp, clang inlined the wrappers into
#   GetCaminhoCorreto*, binaryen kept the turn overloads and merged those (33 over 90 against 2298); in a file of their
#   own every row of 2298, 3898 and the seven thunks is operand-only, and steps 8 and 9 match them. So the file is not
#   cgravadorwsq.cpp; band 3 (3834 of cpath.cpp.o, 3796 of cgravadorwsq.cpp.o, 3795 to 3793, 3792 of
#   cappinfosingleton.cpp.o) puts it after cgravadorwsq.cpp.o and so not in cpath.cpp. Its directory is a choice:
#   gravadores/, beside the band's left neighbour; appinfo/, beside the right one, fits as well. Its name
#   pathwsq.cpp, the functions' names, the turn overloads, their being free functions of comum and their order (the
#   bands' 5819, 5818, 5817, 5816 and 3795, 3794, 3793) are chosen.
# - GetPathWsqRegistrado (fn 5815, "registrado/" on the internal flash, the same form), a thunk into 2298 as the
#   target's: its callers are 3614 (unit 221's) and 5382 (unit 135's), both matched; a roots stand-in gave it its
#   second call site until 3614 was in the link. It matches (`3 over 6 rows`, operand-only, before step 8). Its
#   external twin,
#   GetPathWsqRegistradoExterno, has no index: 5382 holds it inlined behind its 32-byte frame, its one caller. Both are
#   after GetPathWsqNaoRegistrado, at the end of pathwsq.cpp, and their names are chosen.
# - 9531 (vector<std::filesystem::path>::__init_with_size<const path*, const path*>, 5821's only user of its table slot
#   6150) comes from icompressor.cpp.o with Add(path). Its match line named vector<std::string>'s instance from
#   app_dados_asn_datahoraasn.cpp.o, a twin until now: with both in the link, they differ in one table slot (each its own
#   __throw_length_error) and binaryen merged them (`matched.txt only: [9531]`). The target's vector<std::string> copy is
#   fn 5585, an -Oz -fexceptions body (__vallocate and __construct_at_end out of line, slots 232 and 233); src/app/
#   roots_coderenv.cpp's instantiation of it gives our link that copy first, 5585 against it reads 8 over 69 rows,
#   operand-only (5585 stays unresolved: its callees 11180 and 11177 have no name), and 9531's line now names the vector<path> instance, the scan's symbol for it (docs/how-to-decompile.md
#   step 10, "A symbol that stays while its body moves").
# - The directories' other target callers are in the link (5382, unit 135's, 10425, unit 142's, and 10451 and 3614,
#   unit 221's), so the roots' stand-ins for 10425, for 10451 (3793's) and for 3614 (5815's) went.
#
# comum::CGravadorVersoesArquivos::GravaResultado (target fn 11582, slot 7, the class's key function, which unit 136's
# pending object trapped), in cgravadorversoesarquivos.cpp: the class's name in lower case, chosen, in
# app/comum/gravadores/, a reading of the data: the class's vtable (@1557240) lies between cgravadorutil.cpp's records
# (to @1557172) and cgravadorwsq.cpp's (from @1557332), and no record names CGravadorLog's file. Its band neighbours are
# CGravadorWSQ's 11575 to 11579 and CGravadorLog's 11583 and 11584 (band uses 1 of ledger/ordinals.tsv). The object
# emits the class's vtable and implicit destructors (11581, 11580) now, and the kept copy of 720 (the destroy of a
# std::map<std::string, std::string>'s tree), which came from crelutil.cpp.o before and still matches (splat/scan.tsv's
# object column). It calls comum::asn::GravaArquivo, unit 145's (cconversorversoesarquivos.cpp), which binaryen inlines
# into it (unit 145's fragment and cconversorversoesarquivos.h say why the converter's object defines it). The file is
# in this unit's list for the order of the objects, measured with pnpm wasm score against each link: linked after unit
# 145's object, in a fragment of its own, 11582 scored 100 over 715 rows (98 operand-only, 1 inserted, 1 deleted: the
# locals are numbered otherwise); linked ahead of it, as the target's band has it (11582 above unit 145's 10264 and
# 10263), 63 over 714, every row an operand: the calls, the data addresses, the format strings' packed addresses and the
# format buffer's and the exception's table slots. Its place before cgravadorwsq.cpp follows the band (11582 above
# CGravadorWSQ's rows); that order against cgravadorwsq.cpp was not measured otherwise.
# comum::CGravadorRCSecao::GravaResultado (target fn 11616, slot 7, which this unit's pending object trapped) is written
# in cgravadorrcsecao.cpp at its record's line (110), with what it holds: LeChavePublica (records :65, :75 and :83),
# ObtemComparecimentoEleitores, CriaIdentidadeEleitor (fn 5845, :230) and the free functions cgravadorrcsecao.h declares
# after the class. The target holds them behind stack frames of their own, in this order (the sizes read off the
# prologues of pnpm wasm fn's readout): 976 (11616's own), 464 (FormataDataHora's std::format), 256
# (ObtemComparecimentoEleitores), 80 (CriaHabilitacaoPorMesario), 96 (ObtemSituacaoReconhecimentoMesario), 64
# (ObtemJustificativas), 64 and 64 for each period (ObtemMesariosAbertura with ObtemRegistrosMesariosAbertura, then
# Encerramento's two), 176 (LeChavePublica), 80, 32 and 656 (comum::asn::CodificaDadosComparecimento with
# CFileASN::CodeObject and CodeObjectFunction, gravadores/asn/cconversorresultadournacadastro.cpp) and 80 (ecourna's
# CPlainText delegating constructor, cplaintext.cpp, with landing pads): each the shape of an out-of-line function
# binaryen inlined into its one caller; which function each frame is is a reading of the calls it holds. Ours gives the
# same frames in the same order. The two functions with no frame are static, so clang inlines them:
# ConverteEstadoColetaDigital (measured, 5841 below) and CriaJustificativa, read from the target's order of
# destructions (the shared pointer and its temporaries released before the push_back of the CIdentificacaoJustificativa,
# which a function that returns it gives; no other form was measured). The forms the target's instances show: the poll
# workers and the justifications pushed as rvalues (its slow paths 5375 and 5842 take `T&&`), the case of tipo
# habilitação 2 before case 1 (the target's block order). Chosen: every name but the records' (GravaResultado,
# LeChavePublica, CriaIdentidadeEleitor), that the functions which read no state of the class are free functions of
# comum (or comum::asn) and not members, their parameters' names and types, the lines of the functions with no record
# (after GravaResultado, CriaIdentidadeEleitor's record line kept), the file and path of the comum::asn functions,
# CJustificador::HasInst's name and its being inline (cjustificador.h), and the CPlainText constructor's being a
# delegating constructor of that class with its parameters (cplaintext.hpp). The linkages are readings: external where
# the target shows a frame, static where it shows none.
# 11616 is `differs` (scan detail +0x16, a local's number: target local.tee 11, ours 10); its call of parse_iso_time,
# 5851, re-points since 5851 matches (below). Against the target it scores 1203 over 7245 rows (pnpm wasm score: 732
# replaced, 698 of them operand-only, 57 inserted, 414 deleted), and what differs past the operands is not explained in
# full. Two parts
# are read: the copy of the CInfoSalt the CPlainText constructor takes by value is inlined in the target (two vector
# copies and a vector length error) and a call of cinfosalt.cpp's out-of-line copy constructor in ours (fn 9470, unit
# 05's), so the target's header defines that copy inline (a reading; unit 05's files are not changed); and the target
# keeps `call 158; unreachable` (vector<unsigned char>'s __throw_length_error, a twin) at five places where ours has one
# that the others branch to (read as binaryen's folding of identical tails in our link; why the target's are apart is not
# traced). It stays
# written: it brings 5366, 5841, 5843 and 5844 into the link, its object 1006 and 3813, and its parse_iso_time copy
# (5851) 2849, 3811, 5833, 5838, 3812, 5839 and 8887 (below).
# Matched with 11616 written (steps 7 to 9; every row operand-only before the scan, pnpm wasm score):
# - 5841, comum::ConverteComparecimentoMesario (11 over 274 rows): a free function after CriaIdentidadeEleitor (its
#   band order: 5845, 5844, 5843, 5842, 5841 and 5839 run down ld_index in names.tsv), its collection state from a
#   static helper over the three values by value, which clang inlines. Measured in the whole link: the mapping over the
#   poll worker by reference, an accessor in each condition, in another TU, where binaryen inlines it, gave an early
#   exit on PertenceSecao that the target does not have (44 over 278 rows; in this TU, the scratch objects below show
#   the same exit before binaryen); by value with the finger tested
#   `!= 0` and `== 0`, one row was left, `!(dedo | !t)` against ours `!dedo & t` (14 over 274); `dedo` and `!dedo` give
#   the target's. A helper that reads the three into locals first gives the same object as one that takes them by
#   value, and so does no helper, the three read into locals in ConverteComparecimentoMesario itself (the same 69 lines
#   of wasm-objdump -d); one that takes them by value in another TU nests its selects otherwise (a scratch TU at the
#   tree's flags, wasm-objdump -d of each form). The helper, the helper's and the function's names, their being free
#   functions and the parameters' types are chosen.
# - 5843 and 5844, vector<CEstadoComparecimento>'s __emplace_back_slow_path over the arguments of the four emplace_back
#   calls with a CApresentacaoFotoEleitor (4 over 116 and 4 over 115 rows). The object emits one instance per argument
#   list (four with the Faltou case's two arguments, llvm-nm), and two are in the link: 5843 is the two five-argument
#   calls' (with the CHabilitacaoBiometrica), and 5844 binaryen's fold of SemCargoParaVotar's (the enumerator, so
#   ESituacaoComparecimento) and the other four-argument call's (`situacao`, const ESituacaoComparecimento&), which
#   11616 calls twice. 5844's symbol is the one the fold kept (link order, not evidence), and the template arguments'
#   qualifiers follow the calls' argument forms, which are chosen. 3813 (vector<ecourna's
#   CComparecimentoMesario>'s slow path, `T&&`, 4 over 270) and 1006 (CEstadoComparecimento's D2, 0 over 121), which
#   unit 105's notes say only this uenux2 caller brings: copies of this object, ahead of ecourna's.
# - 5366, comum::asn::GravaArquivo for the voter-register result (55 over 540), in
#   gravadores/asn/cconversorresultadournacadastro.cpp, whose header says what places it.
# - 5839 (boost::date_time::string_parse_tree<char>::match, 1 over 314) and 3812 (basic_stringstream's constructor from
#   a string, 15 over 151): Boost's parse_iso_time<ptime> instantiated here (no landing pads, the tree's flags) calls
#   them, and its copy now links ahead of ecourna's app_dados_asn_datahoraasn.cpp.o. With that copy gone the slot
#   unit 87's notes name (basic_stringstream's, which ecourna's copy loaded) is gone too, and
#   ASN1::AVNDecoder::do_visit(OBJECT_IDENTIFIER&) (8887, unit 87's) matches.
# - 5842, 5846 (src/app/roots_iconversorasn.cpp's instances), 5375 (unit 186's stand-in) and 2278 match from this object
#   now, with the stand-ins that stood for 11616 gone (the README row lists them). The ecourna copy of parse_iso_time
#   had been the last caller of a vector<std::string> chain (special_values_parser's sv_strings calls
#   __init_with_size, 5585, roots_coderenv.o's instance), and with it out 3895, 5562, 5573, 5774, 5786 and 11158 left
#   `match`: src/app/roots_coderenv.cpp now stands for 5585's target users, 11332 and 9586, and they match again.
# Matched since the Boost tree root's probe (tools/libs/boost/probe.cpp) dropped its date parsing, clock and
# lexical_cast calls (steps 6 to 10, every row operand-only before the scan, pnpm wasm score): Boost's
# parse_iso_time<ptime> (5851, 9824 B), this object's copy, 200 over 4667 rows, with what only it calls:
# bad_lexical_cast's constructor (2849, 3 over 14), lcast_ret_unsigned's convert for unsigned short (3811, 23 over 612)
# and for unsigned long long (5833, 7 over 635), and token_iterator<offset_separator>'s constructor (5838, 3 over 159),
# which matched from app/roots_boost.o before and from this object now. The target holds parse_undelimited_date,
# gregorian::date's constructor from a year, a month and a day, and lcast_ret_unsigned's convert for unsigned int
# inlined in 5851 (binaryen inlines a function with one call site), and in cb34a517's link urna_roots (app/roots.o,
# with the probe's functions inlined into it) called them once,
# twice and twice (wasm-objdump -d of that link, the `call` sites of each): 5851 read 2079 over 4695 rows there (714
# replaced, 701 of them operand-only, 28 inserted, 1337 deleted). With the probe's from_undelimited_string and its
# lexical_cast calls out and its two clocks in, 5851 read 729 over 4667 (429 replaced, 415 operand-only, 300 deleted):
# the deleted rows are the target's inlined date constructor behind a second prologue (its month-end lengths and the
# "Day of month is not valid for year" throw), where ours has one call (a reading of the score's rows; the clocks called
# the constructor too, twice). In cb34a517's link 2849's
# copy kept the source type a parameter ((i32 i32 i32)->(i32), 5 over 14), where the target's stores std::string's
# typeinfo (the probe cast from other types), and 3811's and 5833's were app/roots_boost.o's, at APP_CXXFLAGS (295 over
# 666 and 242 over 681 rows); this object's are the target's. The probe's change left the bodies of gregorian's
# bad_year (its D0, 2846) and wrapexcept<bad_year> (3804 to 3809, and binaryen's merges 3899 to 3901) to this object.
# 2846 matches as this object's bad_year D0, the name the target's bad_year vtable gives it. 3804 to 3809, 3899 and
# 3900 match as the byte-identical members and merges of app/roots_boost.o's wrapexcept<std::invalid_argument>, which
# links first, and 3901 as that class's throw_exception merge: those names are the link order's pick, the target's
# vtables holding these bodies under bad_year, bad_month and bad_day_of_month (step 9 renamed the nine lines); the
# target's own wrapexcept<std::invalid_argument> is 5127 to 5133, 9335 and 9336. The
# probe keeps bad_weekday's typeinfo alone for a toolkit test: a call of greg_weekday's range check gave bad_weekday's
# twins of these bodies, which named them and took 2846 to app/roots_boost.o (measured on a link with that call).
# Evidence: the records give each member's name, file, line and column, and the signatures; the codes, the messages and
# the bodies give the rest. The enum's values are the codes every thrower passes to fn 283 and the two that fns 3825 and
# 3826 pass to their merged body 6044 (docs/reference/facts/placing.md P6). IGravador's constructor is in iresultado.cpp
# by choice, one the data allows: IGravador's vtable (@1553648) follows that file's record (@1553632), so the object
# that emits it (the key function's, or the vtable's first user's: docs/reference/facts/placing.md P4) can be
# iresultado.cpp's. The constructor has no record, and a record-less object between that record and
# ccabecalhoentidade.cpp's (@1553700) would give the same order; its line there is a choice too.
# Chosen: the enumerators' names, the header paths, DeterminaNomeArquivo's name, the two accessors' names, the
# CVersoesArquivos map alias, the constructors' parameter types beyond what the records spell (CGravadorWSQ's tipo de
# biometria as cgravadorwsq.h's ETipoBiometria and its last argument as bool, from the unsigned compare and the byte
# store), the lines of
# the functions with no record (each above the function it calls, DeterminaNomeArquivo after the one it calls), that
# CriaIdentidadeEleitor, ValidaCriacao and ValidaTipoBiometria are private, `.Get()` where DeterminaNomeArquivoSemLetra
# formats the identifiers, and every member and parameter name.
#
# Forms measured in this unit's link (pnpm wasm score against the target, then the scan):
# - ConverteFase lists its cases 't', 's', 'o'. In the order 'o', 's', 't' the switch starts with 49 and sets 51 in a
#   block, where the target starts with 51 and sets 49: 20 rows differ, three of them the two constants and the
#   br_table's targets, and the order written matches.
# - ConverteSerialFlash fills `char byte[3] = {0}` and then its two digits, and keeps HexToInt's result in a local
#   before push_back. An initializer list {c0, c1, '\0'} stores the NUL after the digits, where the target stores it
#   first, and push_back(HexToInt(byte)) in one expression frees the temporary string after the push_back, where the
#   target frees it before: 68 over 367 rows with both, a match with neither. Each was not measured alone.
# No other spelling was measured, so no form here is listed as giving the same bytes.
#
# Matched only at the tree's -O3:
# - 3798 DeterminaNomeArquivo and 3604 DesconverteSerialFlash call std::string::append(const char*, size_t) in the
#   target (fn 160), which clang inlines at -O2 and calls at -O3: compiled by tools/round/try-tu.sh --symbols at -O2,
#   the objects of cgravadorutil.cpp and gravadores/asn/util.cpp call __grow_by_and_replace in both functions, and
#   with --flags -O3 they call append(const char*, size_t). At -O2 they scored 200 over 954 rows and 121 over 346. At the
#   tree's -O3 3604 matches, and 3798 scored 82 over 862 (72 operand-only, 10 inserted) while comum's ID names were
#   iresultado.h's CBaseType aliases, which masked the zone and the section it takes with 65535 where the target
#   compares them with no mask. Since those names are plain integers (143-uenux2-cidentificacao.mk has the
#   measurement), 3798 compares them with no mask, as the target does, and matches at the tree's -O3.
# - 1396 IGravador's constructor equalled the target's but for operands (20 over 239 rows), and the scan read it
#   `unresolved self-voted`: its call of 3798 was the only vote for 3798's name. It matches since 3798 does.
#
# Not matched, and what each waits for:
# - The gravadores/md data classes, CConversorTipoApuracaoSA and the other recorders' destructors are unit 136's.
#   CVersoesContratos::GetValor and CDependenciasContratos::GetValor (3825, 3826, the merge thunks of 6044) are fragment
#   227's.
# - comum::CGravadorWSQ::CompactaWsq (fn 5821): written (above) and `differs`, its first difference the frame (scan
#   detail +0x6: the target's is 160 bytes, ours 80). It scores 453 over 3911 rows (pnpm wasm score: 15 inserted, 19
#   deleted, 411 of 419 replaced operand-only); ecourna's globToFileList, its lambda and ~CZip are written in the forms
#   5821's rows show (unit 06's fragment; the lambda matches, and globToFileList is read off 5821's rows), and the rest
#   is the frame's slot offsets, the locals' numbering, block placement (the place of the inlined Add's epilogue) and
#   the store order of the inlined CreateDir's string (unit 32's code). The frame, measured on cgravadorwsq.cpp.o
#   (wasm-objdump -d, and -emit-llvm for the allocas): clang gives CompactaWsq seven allocas (the vector, two CZip,
#   three paths and the "*.wsq" string) and packs them into 80 bytes, the vector at 68, the CZip at 28, the paths at 16
#   and the string at 0. The target's 5821 uses 148 (the vector), 104 (the CZip), 88 (the string) and 64 (the paths) of
#   160, and no instruction of it addresses 0 to 63, 76 to 87, 100 to 103 or 144 to 147. A reading of that layout, slots
#   in frame-index order from the top and an inline memset or memcpy raising a slot's alignment to 8 (our string at 0
#   leaves 12 to 15 empty so): the vector, the CZip, the string, a 12-byte object, the paths and a 64-byte object
#   aligned to 16, the size of a three-argument std::format store or of a std::filesystem::directory_entry. No
#   instruction of the target uses the two, so their code is gone: a reading that binaryen removed it after folding a
#   constant (docs/reference/facts/reading.md R1 has the pass). The file's three records are all loaded
#   (ledger/source-locations.tsv), so no record shows it. What it was is not recovered, so it is not written, and 5821
#   waits for it. Its name is a callers+content hand line of splat/symbol_addrs.txt, on the three records it alone loads
#   (cgravadorwsq.cpp:175 and :192, icompressor.cpp:61), which slots 2, 3 and 6 and their merged body need: no vote
#   reaches 5821, since its callers are named by vtable or by content.
GRAVADORES_SRCS := src/app/comum/gravadores/cgravadorutil.cpp src/app/comum/gravadores/iresultado.cpp \
	src/app/comum/gravadores/cgravadorlog.cpp \
	src/app/comum/gravadores/cgravadorversoesarquivos.cpp src/app/comum/gravadores/cgravadorwsq.cpp src/app/comum/gravadores/pathwsq.cpp \
	src/app/comum/gravadores/cgravadorrcsecao.cpp src/app/comum/gravadores/asn/util.cpp \
	src/app/comum/gravadores/md/cversoesarquivos.cpp src/app/comum/gravadores/asn/cconversorresultadournacadastro.cpp
UENUX2_SRCS += $(GRAVADORES_SRCS)
# cgravadorrcsecao.cpp and gravadores/asn/cconversorresultadournacadastro.cpp read ecourna's voter-register result
# classes, whose headers include Boost's ptime, and the latter ecourna's converters, which include the generated ASN.1
# modules by their bare names: include paths, not flags of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorrcsecao.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/asn/cconversorresultadournacadastro.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Isrc/asn1/modules
$(foreach u,src/app/comum/gravadores/cgravadorrcsecao.cpp src/app/comum/gravadores/asn/cconversorresultadournacadastro.cpp,$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# cgravadorutil.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit 88's
# sources do): an include path, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorutil.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# cgravadorwsq.cpp's CompactaWsq builds an ecourna::api::compression::CZip, whose header includes minizip's zip.h and,
# through ICompressor, Boost's signals2: include paths, not flags of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Ithird_party/zlib -Ithird_party/zlib/contrib
# cgravadorlog.cpp is unit 136's (CGravadorLog::GravaResultado, fn 11584), compiled in this list at its place in the
# target's data, between cgravadorutil.cpp's records and CGravadorVersoesArquivos's vtable (unit 136's fragment has the
# measurement and the pairs it inverts); its CZip needs the same include paths as cgravadorwsq.cpp's
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/cgravadorlog.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) -Ithird_party/zlib -Ithird_party/zlib/contrib
# nothing reconstructed calls most of these yet: 122-uenux2-app-comum-gravadores-roots.cpp stands in for the target's
# callers, two call sites each (its stand-in for 11616, the caller of CriaIdentidadeEleitor, went when 11616 was written)
$(ROOT)/$(APP)/122-uenux2-app-comum-gravadores-roots.o: $(ROOT)/src/units/122-uenux2-app-comum-gravadores-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/122-uenux2-app-comum-gravadores.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -I$(BOOST_HDR) -c src/units/122-uenux2-app-comum-gravadores-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/122-uenux2-app-comum-gravadores-roots.o
