# uenux2 comum::md::CVersoesContratos and CDependenciasContratos (app/comum/gravadores/md/, the files the records name,
# each class header beside its file): GetValor, target fns 3825 and 3826, and their merged body, fn 6044; and
# api::hash's CMontadorHash::CriaHashesDiretorio (fn 5360), ListaHashesDiretorio (fn 5359) and ListaHashesArquivos (fn
# 5358), written, not matched, in api/hash/cmontadorhash.cpp, the records' file, with the header cmontadorhash.h beside
# it. Paths relative to src/uenux2. Members of the same work that live in other units' files: IGravador's Slot4 and
# Slot5 (unit 122, iresultado.cpp), api::CIniFile::FindKey and EndKey (fragment 379's cinifile.cpp; unit 215 wrote them
# in cinistrings.cpp) and ecourna::api::io::CFile::Write (fn 5180, ecourna's api/io/cfile.cpp, unit 03's source), whose
# callers' stand-ins are this fragment's roots.
#
# GetValor (records cversoescontratos.cpp:42 and cdependenciascontratos.cpp:59, `const std::string ...::GetValor(const
# std::string &)`): the INI object's key map's find (fn 10877, CIniFile::FindKey) and end (fn 5481), and when the key
# is not there CUeComumGravadoresError 8697 (8663) "Propriedade inexistente: {}" with the key; else a copy of the
# CIniKey's value. The two bodies differ only in their record and code, so binaryen merged them into fn 6044, which
# takes the two as parameters, and keeps each GetValor as a thunk (3825, 3826) that passes its own. Our link forms the
# same merge, byn$mgfn-shared$ over CDependenciasContratos::GetValor's name (step 9 matches 6044 under it; the name is
# our link's, docs/how-to-decompile.md step 9 "Hand edits"). FindKey and EndKey stay calls: they are defined in
# cinistrings.cpp, and each had two callers before the merge; EndKey's body (this plus 16) is the one fn 5481 the
# target and our link keep for boost's sp_counted_impl_pd::get_untyped_deleter too (matched before, now named `call
# by:6044`). Measured in this link before step 8 (pnpm wasm score against the target): 6044 14 over 246 rows, 3825 and
# 3826 3 over 8, 10877 0 over 7, every row that differs an operand: a call, a data address, the format string's packed
# address, the format buffer's table slot and the exception's destructor slot.
#
# ListaHashesArquivos (fn 5358): a CHashDiretorio's files as CHashArquivo with the directory's name before each file's,
# then its subdirectories' lists, recursively, appended with vector::insert. It scores 20 over 603 rows in this link,
# every row a call's or a data address's operand, and reads no-candidate: no record names it, the census pairs it with
# no target function, and its recursive call waits for its own name, which its other caller, 5359, would give once it is
# named itself. Its range insert, fn 5854, matches since unit 136's cgravadorhashes.cpp (comum/gravadores, built without
# strict aliasing) instantiates it ahead of this object: compiled here, with strict aliasing (src/api is in
# UENUX2_TBAA_DIRS), it scored 84 over 921 rows (14 inserted, 7 deleted: the circular buffer's swap loads in another
# order), and 20 over 907, operands only, from an object built without it, as the band read it (5854 sat among
# comum/gravadores' rows, the stubs' clusters of 5852 and 5854 naming cgravadorhashes.cpp and md/centidadehashes.cpp).
# 5852, the insert's __insert_assign_n_unchecked, comes from that object now too. In the band 5358 and 5359 link right
# after 5360, whose records are cmontadorhash.cpp's (lines 49, 78, 91, 98, 121) and chashdiretorio.cpp's, and before
# api/ipc's objects: so the file.
#
# ListaHashesDiretorio (fn 5359, a chosen name): ListaHashesArquivos of CriaHashesDiretorio's directory, which it then
# destroys (fn 2220). Its one caller is fn 11620, which calls it twice through comum::CalculaHashesArquivos (unit
# 136's). 3 over 24 rows, every row an operand (its three calls); no-candidate: nothing names it while 11620 does not
# match (unit 136's fragment says what 11620 waits for), and its callees 5360 and 5358 have no name either.
#
# CMontadorHash::CriaHashesDiretorio (fn 5360, record :121, the throw when the directory does not open, with its class's
# name in its message), with what binaryen inlines into it behind frames of their own: CalculaHash (record :78) with the
# file-static CalculaHashArquivo (record :49, which clang inlines into it: one frame of 4144 bytes, a 4096-byte buffer;
# its record lies last in the object's run, after the external members', as a file-static function's does,
# docs/reference/facts/reading.md R8), CalculaHashGeral (records :91 and :98) and CHashDiretorio's constructor with
# ValidaObjeto (chashdiretorio.cpp:41, unit 198's), and libc++.a's read_symlink and weakly_canonical, whose landing pads
# give its invoke_* calls. It walks the directory with api::CDirReader, skips ".", "..", "lost+found", "tmp" and every
# path the set holds (a link resolved, made absolute, and each parent up to the root, with a "/" after a directory),
# sorts the files' and the directories' paths, hashes each file (IHash's factory, then ITextEncoding's,
# CPolySingleton<IGenericFactory<...>>::instance, fns 5362 and 5361, which match with it) and folds the hash into the
# static s_hashGeral but for "uenux.cfg" and "avbootcfg.vsu", then recurses into the directories. Written so that 5359
# and 11620 link (a function the link reaches must be defined); 1584 over 4755 rows (229 inserted, 228 deleted),
# no-candidate, the remainder not explained. Its libc++ and libc callees that match with it: 7738, 7739, 7740, 7742,
# 7743, 7744, 7747 and 7749 (7741, lexically_normal's code, reads unresolved, a slot of path's constructor over a
# char[2] with no target function; 7748 no-candidate), 3335, 4676, 4681, 4686, 1266, 2545, 2547, 3332, 4674, 4675, 4680,
# 5619 and binaryen's merge 1085; the sort of strings 2722 with 939, 3599, 5356 and 5357; libc's strdup (6253), strnlen
# (6250) and memmove (6259). Rows of library code turn match with it too, their objects and bodies unchanged, read as
# bodies binaryen treats otherwise once 5360's callees give their callees more call sites (how-to step 9; their old
# scan details: a constant where the target has a parameter, a callee inlined; docs/reference/facts/splat.md S10 item 29
# has each): libc's printf_core (6233) and getcwd (3984), libc++'s money_get::do_get (7884) and path's constructor from
# a string_view (4789), with unit 190's 183, 3679 and 5549 (its fragment), and src/app/roots_coderenv.cpp's
# vector<string>::__vallocate (11180), all in the link before with the same bodies; and allocator<string>::allocate
# (5570), whose body is also path.o's allocator of pair<string_view, PathPartKind> (binaryen keeps one,
# roots_coderenv.o's by link order). The forms (the loops, the set's spelling, the
# link's parent walk, the "/"s literal) are chosen among those that compile to its calls; none was measured against
# another.
#
# ecourna::api::io::CFile::Write (fn 5180, matched; step 9 found it by the census's pair) is written in ecourna's
# api/io/cfile.cpp, unit 03's source, and declared in cfile.hpp, whose comment has its evidence and the forms measured;
# its callers 5371 (unit 214's GravaWsq, matched) and 11587 (unit 305's) are in the link, so the roots' stand-in for
# 5371 went. Unit 03's fragment and row say so.
#
# fn 5869, CDependenciasContratos::GetValor's other caller (comum::CGeracaoVersoesContratos::ObtemDependencias, a
# chosen name), is fragment 268's, written in app/comum/gravadores/cgeracaoversoescontratos.cpp and matched; that
# fragment has its measurements, and those of CGeracaoVersoesContratos's destructor (fn 5866, the four trees from +36
# down, fns 1397 and 2859), matched there too.
#
# The md classes' constructors (records cdependenciascontratos.cpp:27:15 and cversoescontratos.cpp:29:15), which
# vota::CGravaResultado::StartState (fn 12098) holds inlined, each behind a 528-byte frame (lines 1203 and 1281 of the
# folded readout `pnpm --silent wasm fn ../target/vota_web_wasm.wasm 12098` prints, counted from the line after
# `;; --- folded readout`): written, unrooted (wasm-ld drops them), so with no target index and no match until 12098 is
# written. Each loads its INI file with api::CIniFile::Carrega (fn 5480) into its member, reads "tag" with GetValor,
# compares it with "20260601173148" (12098 compares 14 bytes) and otherwise throws 8662 or 8696 with "Tag do arquivo
# de dependências de contratos inválida: [{}]. Tag atual: [{}]" (235617) or "Tag do arquivo de versões de contratos
# inválida: [{}]. Tag atual: [{}]" (235546) over GetValor("tag") read again and the array (5870 is the
# make_format_args over a const std::string and a const char[15] both throws call). Measured on the objects
# (wasm-objdump -d): both open 528-byte frames; check_srcloc.py --strict: each object's 2 records are the target's. In
# dependencias' code in 12098 the key "tag" is built at +80 and the value returned at +136, then the value is tested,
# compared and freed and the key freed; its object does the same. In versoes' code the key is at +136 and the value at
# +80, and the key is freed before the compare: the file writes the sibling's form, which gives dependencias' layout
# there, and none of the forms measured gives versoes' (the value in a named local, in the if's initializer or bound to
# a const reference: the key at +136 and freed first, but the value at +68 and kept past the throw; the literal on the
# left of the !=: dependencias' layout), so its form waits for 12098's measurement. The array is the target's one
# literal (341442, which 12098 also loads to build a std::string, and at which 5870's folded argument points), written
# in place. With the constructors written, md/cdependenciascontratos.cpp.o instantiates that make_format_args, and the
# link keeps its copy of 5870 (the same symbol, still matched), which came from unit 268's roots object before.
#
# Chosen (each header marks its own): the classes' members and parameter names; the md constructors' comparison and
# throw as written, the literal in place, and their first lines; that each md class holds its INI object
# as a member (a base would give the same layout; not measured); ListaHashesArquivos's and ListaHashesDiretorio's names,
# their being free functions and their header; CMontadorHash's members' access, s_hashGeral's name and its being a
# static member, the using-declarations that place the records' columns, ITextEncoding's header and slot name
# (ecourna/api/security/itextencoding.hpp); the lines of the functions with no record. One form of each was measured
# (of the versoes constructor's comparison, the five above), none listed as the same, but for CFile::Write: a free function of ecourna::api::io taking the CFile by reference gives
# the const member's instructions (cfile.hpp says so).
#
# Roots: 227-uenux2-contratos-cmontadorhash-roots.cpp stands in for the callers not written (12098 for both GetValor;
# 5869, CDependenciasContratos's other caller, is in the link since unit 268); each stand-in names them. Its stand-ins
# for 5358's caller 5359 and 5854's caller 11620 went: both are in the link. No census pair falls on a function the
# roots object defines (step 7's check).
W227_SRCS := src/api/hash/cmontadorhash.cpp \
    src/app/comum/gravadores/md/cdependenciascontratos.cpp src/app/comum/gravadores/md/cversoescontratos.cpp
UENUX2_SRCS += $(W227_SRCS)
# The roots read uenux2 headers, and through them ecourna's.
W227_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/227-uenux2-contratos-cmontadorhash-roots.o: $(ROOT)/src/units/227-uenux2-contratos-cmontadorhash-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/227-uenux2-contratos-cmontadorhash.mk $(W227_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/227-uenux2-contratos-cmontadorhash-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/227-uenux2-contratos-cmontadorhash-roots.o
