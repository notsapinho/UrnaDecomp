# uenux2 comum::IServicoEstado<ESTADO, CONVERSOR> (src/app/comum/appinfo/servicos/iservicoestado.h) and the four classes
# derived from its instances, comum::CServicoEstadoGeral, -Vota, -Gap and -SA (servicos/cservicoestadogeral*.{h,cpp}),
# with three codes of EUeComumAppInfoError (src/app/comum/appinfo/euecomumappinfoerror.h); api::CFileASN's readers and
# writers (src/api/io/asn/cfileasn.h, unit 229's header) with five codes of EUeIoError (src/api/io/eueioerror.h); and
# ecourna::api::io::CFile's destructor (src/ecourna/api/io/cfile.hpp), whose catch a member here matches with.
#
# Matched: CServicoEstadoGeral's constructor (target fn 1941) and GetPathArquivo (11569, its vtable's slot 2), and
# CServicoEstadoGeralVota's, -Gap's and -SA's GetPathArquivo (11568, 11567, 11565), thunks of binaryen's merge 3896,
# which the three form in our link too. 3896's match line names our merge body, byn$mgfn-shared$ and the first member, a
# name our link derives and that moves with link order (docs/how-to-decompile.md step 9, "Hand edits").
#
# Evidence:
# - RTTI (ledger/classes.json): each class's only base is its own instance of comum::IServicoEstado<ESTADO, CONVERSOR>,
#   whose arguments are an estado class and its converter; ledger/vtables.json gives the four vtables as [174, 144, slot
#   2]. No vtable of the template is in the target's data: a search of the data segments for the four template
#   typeinfos' addresses (1558048, 1558104, 1558160, 1558216) finds each once, at its class's typeinfo + 8.
# - The three records (servicos/cservicoestadogeral{vota,gap,sa}.cpp, line 32, column 15) give the derived classes'
#   files, GetPathArquivo's name, `virtual`, the std::filesystem::path result and no parameter. The throws' codes are
#   what the thunks pass to 3896 (7607, 7605, 7606), with "Urna sem turno em contexto onde turno era esperado", when the
#   turn at +8 is 48 (SEM_TURNO, eurnaturno.h); else 3896 returns CPath::GetPathTrab (358) of the origin at +4 and the
#   turn, with "vota.bin", "gap.bin" or "sa.bin". 11569 returns GetPathDinamico (1082) of the origin at +4 with
#   "eg.bin".
# - 1941 stores its parameter at +4 and the vptr 1558024 (CServicoEstadoGeral's vtable + 8) and returns the object. The
#   member is written as the class's own; held by the template instead it gives the same bytes (both compiled at the
#   tree's flags, docs/reference/facts/codegen.md C1: in 1941's shape both store +4 and then the vptr, and in a
#   constructor of 3897's shape both store +8, +4 and then the vptr), and 2894 and 3791 never load +4, so which class
#   holds it is chosen (below).
# - Place: no record names CServicoEstadoGeral's file. In the data its vtable, its typeinfo and its base's (1558016,
#   1558036, 1558048) lie just before -Vota's vtable (1558056), and the four classes' run in the order base, Vota, Gap,
#   SA (vtables 1558016, 1558056, 1558112, 1558168, each derived class's record and typeinfos after its vtable); in
#   code, use band 1 (ledger/ordinals.tsv) links 11569 just before 11568, 11567 and 11565. So the class is placed in
#   servicos/ beside them (how-to step 3, rule 2) and named by rule 4; ledger/tu-clusters.tsv's label
#   app/comum/dados/cservicoestadogeral.cpp for 11569 is a class-convention guess. The sources are listed in the
#   target's order, base, Vota, Gap, SA, not their names'; no other order was linked.
#
# Scores before step 8 (pnpm wasm score against the link): 11569 8 over 83, 3896 11 over 106, 11565, 11567 and 11568 5
# over 9 each, 1941 1 over 9, all operand rows.
#
# The template's members, the derived classes' constructors and CFileASN's readers and writers, written later (the unit
# grew; how-to step 6 item 2). Matched:
# - 3791, IServicoEstado<CEstadoGeral, CConversorEstadoGeral>::Carrega (iservicoestado.h; name chosen, named by its
#   records' anchor): GetPathArquivo through slot 2, the path's string, the converter on the stack, then
#   api::CFileASN::ReadFromFile(const std::string &), ReadFromFile(const CFile &) and DecodeObjectFunction (cfileasn.h,
#   at their records' lines 78, 48 and 60, 135 and 143) and IConversorASN::Desconverte (iconversorasn.h 71), each behind
#   a prologue of its own (frames 480, 528, 736 and 640 inside 3791's 96): out of line in the object, one caller each
#   in the link, so binaryen inlines them. The five codes are api/io/eueioerror.h's (5950 to 5954, names chosen from
#   the messages). Its copy is uenux2's (no landing pad), from cservicoestadogeralvota.cpp.o, the first TU that
#   instantiates it.
# - 3897, binaryen's merge of the three derived constructors, and its thunks 3787, 5812, 11566 (each passes its vptr):
#   they store the turn, the origin and the vptr and, for TURNO_ATUAL (51), read the state through a named
#   CServicoEstadoGeral and take its load's turn (+32).
# - 2894, IServicoEstado::Salva's merge, with its thunks 3592 (CEstadoGeral), 5329 (Vota), 10112 (Gap) and 10089 (SA),
#   each passing two table slots and the converter's vptr; 2893, comum::asn::IConversorASN::Converte's merge (thunks
#   10170, 9997, 10051, 10019), with 9843 (its format-argument store) and 255 (CBaseError<EUeComumAsnError>'s
#   constructor, which matches from this copy where cconversorcomplementomunicipio.cpp.o's differed); 2892 and 2891,
#   CFileASN::WriteToFile's two merges (thunks 10168, 9985, 10040, 10008 and 9820, 9684, 9703, 9701); and 3564, CFile's
#   destructor out of line. All are -Oz -fexceptions copies with landing pads, from mock/app/comum/cappinfobuilder.cpp's
#   object (unit 253: its SalvaGeral and SalvaApp call the four saves), which links ahead of the trees; the merges'
#   match lines name our merge bodies, names our link derives (how-to step 9, "Hand edits"). WriteToFile's name is read
#   from the literal "WriteToFile de " that 2891 passes, as "ReadFromFile de " is ReadFromFile's; the two overloads'
#   parameters are what 2892 and 2891 pass (a name and an entity; a CFile and an entity), and their lines in cfileasn.h,
#   between the readers and DecodeObjectFunction, are chosen.
#
# Evidence and measurements for the forms (scores: pnpm wasm score of the target's index against ours in
# build/out/wasm/vota_web/vota_web_wasm.wasm, on links of these sources; frames: wasm-objdump -d of a try object):
# - The readers' and the save's helpers. 3791's frame is 96 bytes with the converter at its top (+92), then the entity
#   (+40), the string (+24) and the path (+12), and its vptr store comes after the string's copy. Written in place with
#   named locals, the frame is 80 and runs the other way (202 over 1664 rows, 4 deleted); as one expression
#   (CONVERSOR().Desconverte(ReadFromFile(GetPathArquivo())) or a converter declared first), the frame is the target's
#   but the vptr is stored before the virtual call; through a helper that takes the string and builds the converter,
#   which clang inlines, both are the target's (137 over 1664, all operand rows). 2894's frame (80: path +0, string
#   +12, entity +24, converter +76) asks the same of the save at the -Oz rule, where a helper of external linkage stays
#   a call (a 32-byte frame of its own in the object) and a file-static one is inlined (frame and offsets the target's).
#   So both helpers, CarregaArquivo and SalvaArquivo (names chosen), are file-static free functions in
#   iservicoestado.h: no class state is read, and their linkage is measured; that the reader's is file-static too, where
#   clang inlines either linkage at -O3, keeps the two alike (a choice).
# - Salva takes `const ESTADO&`: fn 6039 (CAppInfo's two saves, unit 109) passes its singleton's state to 5329 with no
#   copy. The builders 10243 and 10212 copy the state before each save and destroy the copy after; with the reference
#   that copy is theirs, written at their calls (unit 253's fragment). Without it their object instantiates no state
#   copy constructor, and 857, 1249, 2240, 5856, 8084, 9202, 9872, 10145, 11197 and 11395 left match (splat-match on
#   that link, rows by index against the base); with it none did. The header's note that the state by value was
#   evidence went: a copy at the call says little (how-to step 2), and a call with none rules the value out.
# - The constructors: with the service a temporary (`CServicoEstadoGeral(origem).Carrega()`), 3897's frame holds the
#   state above the service, where the target has the service at its top (+184, the state at +4); a named local gives
#   that. With the implicit ~CServicoEstadoGeral the merge ends in one block left by two br_if (17 over 150, 1 inserted
#   and 1 deleted); with it declared and defined out of line, empty, the target's nested ifs (11 over 149, all operand
#   rows), a reading being that binaryen drops the call of the empty D1 after clang's CFG kept the frees apart. Its D2
#   is binaryen's shared 174 either way, and the D0 (144) only frees, so the vtable does not tell the forms apart.
#   Where each constructor starts in its file, before GetPathArquivo's record, is chosen.
# - CFile's destructor (ecourna/api/io/cfile.hpp) holds Close in a try with an empty catch (...): 3564 calls Close
#   through invoke_vi and catches with __cxa_begin_catch and invoke_v of __cxa_end_catch, and CZip::DoAdd (9538) holds
#   the same inlined. Without the catch, 3564 scored 26 over 51 (19 deleted); with it 10 over 51, all operand rows.
#   Every object the edit rebuilt was compared with the one before (functions by name, object-local numbers masked):
#   only api_compression_czip.cpp.o (DoAdd and the destructor) and cappinfobuilder.cpp.o (the destructor) changed, so
#   no uenux2 object without -fexceptions saw it. DoAdd stays unresolved (unit 06's fragment).
# - The service headers include their estado's and converter's headers, which the template's members need complete
#   where they are instantiated (cappinfobuilder.cpp instantiates the four saves).
# - What it moved elsewhere: CoderEnv::decode (679) comes from cservicoestadogeralvota.cpp.o now, and
#   src/app/roots_iconversorasn.cpp's instance of it went (679 matches without it, steps 7 to 9); CodeObjectFunction's
#   and encode's copies (2927 and its thunks, 518, 9790, 3552, 1928, 210, 9770 and the rest unit 229 lists) come from
#   cappinfobuilder.cpp.o now, and src/app/roots_coderenv.cpp's instances and its stand-in for 2891's slots went;
#   steps 7 to 9 on the link without them moved no row. Step 9 renamed 307's line (make_format_args) to the instance
#   over a const std::string first, DecodeObjectFunction's, the same body. The vtable sinks of CConversorEstadoGeral
#   (unit 124) and CConversorEstadoGeralSA (unit 93) went: 3791 and 3592, and 10089, the target's storers of their
#   vptrs, are in the link.
# - Stubs: 5825, 5740, 5706, 5778 and 3735 (other entities' readers; 5706, 5778 and 3735 are unit 280's, 5825 unit
#   305's and 5740 unit 89's, written since) lost
#   theirs, whose records are
#   cfileasn.h's reader lines, which hold code now (docs/reference/facts/placing.md P1).
#
# Not written: Carrega's other caller 11572 (2273 is written, unit 296) and 1941's builders 10243 and 10212 (unit 253's, written and not
# in the link; 1941's caller 3333 is written, unit 205): the roots stand in for them.
#
# Chosen, no evidence names them: m_origem and m_turno, that each class, not the template, holds the origin, the
# template's parameter names, the paths of iservicoestado.h, of CServicoEstadoGeral's header and source and of the
# derived classes' headers, the destructor's spelling, that GetPathArquivo is pure in the template, the eight
# enumerators' names (three here, five in eueioerror.h), the constructors' parameter types, the names Carrega, Salva,
# CarregaArquivo, SalvaArquivo and servicoEstadoGeral, the helpers' being free functions, the lines of every member but
# the throws, the order of CServicoEstadoGeral's three members and of the template's two, and WriteToFile's lines.
#
# Roots (206-uenux2-app-comum-appinfo-servicos-roots.cpp): two stand-ins give 1941 three call sites that read its
# result, for two of its target callers (10243, 11572; 3897, 3333 and 2273 are in the link); the three derived classes'
# constructors (table slots 438, 431 and 434) and the four saves (slots 422, 440, 433 and 436) have their addresses
# taken, for 10243's and 10212's slots, which keeps each out of line whatever its direct callers (6039, in the link,
# calls 3787 and 5329). The constructors store their classes' vptrs, so the vtables' sinks went. The roots declare
# what they use through asm labels and emit no TSE code, so they compile at APP_CXXFLAGS.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
SERVICOS_SRCS := src/app/comum/appinfo/servicos/cservicoestadogeral.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralvota.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralgap.cpp \
                 src/app/comum/appinfo/servicos/cservicoestadogeralsa.cpp
UENUX2_SRCS += $(SERVICOS_SRCS)
# nothing reconstructed calls CServicoEstadoGeral's constructor or references the three derived classes' vtables yet:
# 206-uenux2-app-comum-appinfo-servicos-roots.cpp stands in for the callers and takes the vtables' addresses
$(ROOT)/$(APP)/206-uenux2-app-comum-appinfo-servicos-roots.o: $(ROOT)/src/units/206-uenux2-app-comum-appinfo-servicos-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/206-uenux2-app-comum-appinfo-servicos.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/206-uenux2-app-comum-appinfo-servicos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/206-uenux2-app-comum-appinfo-servicos-roots.o
