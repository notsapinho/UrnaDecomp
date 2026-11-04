# uenux2 api::CSystem in src/uenux2/src/api/util/csystem.cpp, the file its std::source_location records name, with the
# class header api/util/csystem.h and the EUeUtilError enumerators of api/util/eueutilerror.h its throws pass:
#   2759  CSystem::GetFileSize           record at line 334, col 15 (7038)
#   5457  api::truncate                  record at line 1024, col 15 (7070)
#   1690  api::ExistResource             record at line 64, col 15 (7031)
#   2761  CSystem::ZeroFill              record at line 1039, col 15 (7069)
#   412, 5459  CSystem::ExistFile and ExistDir, no record; 6019 is binaryen's merge of the two
#   2760  CSystem::RemoveFile, no record
#   10858, 10859, 10860  slots 8, 7 and 6 of the std::function block of ZeroFill's lambda (__func<...ZeroFill...::$_0>)
#   378   CSystem::CopyFile              records at lines 390 to 476 (7041 to 7048), with AlteraDono and AlteraPermissoes
#                                        inlined; 5456, the std::format arguments' builder it shares with Rename
#   Rename                               record at line 692, col 15 (7058); no target index (inlined into fn 11584)
#   5458  api::RemoveTree, no record: matched, named by 5455's call (below)
#   5454, 5453  api::GetFreeSpace, GetUsedSpace, no record: matched (below), with libc++'s std::filesystem::__space
#         (4677) and libc's statfs (3972) under them
#   5455  CSystem::ReplaceFile, with TemporaryPath (records at lines 236 and 243, col 15: 7034, 7035) and the anonymous
#         namespace's PrepareReplace (916, 922, 928: 7064 to 7066) and ReplaceResource (954, 962: 7067, 7068) inlined:
#         written, unresolved self-voted (below)
#   3645  RenameResource, no record: matched; 5460 and 2858, libc++'s std::operator+(string&&, const string&) and
#         std::make_format_args over three strings, instances this object emits: matched
#   5463  api::GetMemInfo, no record
#   libc's chmod, chown, utime and rename (3997, 6281, 6238, 3974), which CopyFile and Rename call
# truncate is external and not in the header: in the target's run of this file's records, its record (address 1584900,
# line 1024) sits in line order among the external functions' ones, before ZeroFill's (1584916, line 1039); clang defers
# a file-static function's body, and so its records, past every external one. api::ExistResource's record (1584932, line
# 64) comes after ZeroFill's, with the anonymous-namespace helpers: it is file-static, declared in no header. Its three
# callers here (ExistFile, ExistDir, and ExistFile's code inlined into ZeroFill) keep it out of line. ExistFile and
# ExistDir: the target's 412 and 5459 are thunks into 6019 with S_IFREG and S_IFDIR, 6019 a body that calls
# ExistResource and tests the mode against its argument, in a link-order stretch whose anchors on both sides are
# binaryen's (ledger/tu-clusters.tsv 869): two functions that differ in that constant, which binaryen merged. Our link
# forms the same merge (byn$mgfn-shared$ of ExistFile), which matches 6019. 412 is in the table (slot 3567) and
# PrepareReplace's record takes a `bool (*)(const std::string &)`; their names, and their being members, are chosen
# (csystem.h says from what). ZeroFill tests ExistFile, which clang inlines: the target's frame (528 B) reuses the
# struct stat's slot for the std::function. A `struct stat` of ZeroFill's own and a call of ExistResource gave a 624-B
# frame, `score 87 over 357` in the whole link (every row an operand, the frame offsets among them), and ExistFile `28
# over 357`. The lambda's std::function: the target builds one from the lambda (the vtable at 1585036 that RTTI names),
# moves it into a second, and at the end of the scope calls it when it is set, sets it to nullptr and destroys it.
# CScopeGuard, a class with a std::function member taken by value, gives that; the class, its name, its place (an
# anonymous namespace of this file, lines 990 to 1011) and its members' names are chosen. Slot 3 of the lambda's block,
# __clone(__base*) (10861), and slot 2, __clone() (10862), match since src/api/ builds with strict aliasing (src/Makefile
# UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6). With -fno-strict-aliasing our object stored the vptr before
# the captured pointer, where the target stores the pointer first, and 10862 calls the shared body of the lambdas'
# clones (target fn 1083), which our link formed with RHVoice's and which stored the vptr first; it matches with
# app/comum/dados/md/rdv/cvotos.cpp's lambdas built with strict aliasing too. Measured at 694de52, before 1083 matched,
# with csystem.cpp and cgenerictags.cpp compiled by hand with uenux2's set: 10862 scored 2 over 5 rows, operand-only,
# and without -fno-strict-aliasing 10 over 12 (7 inserted), so strict aliasing alone did not close it.
# RemoveFile (2760) calls ZeroFill unless lstat says the path is a symbolic link, then
# libc's remove (fn 1572), which matches with it. At 694de52 our link has no body of remove
# (build/out/wasm-map/vota_web/names.tsv); with RemoveFile it has one, called by RemoveFile and by 7-Zip's
# NWindows::NFile::NDir::DeleteFileAlways (wasm-objdump -d of the link), which is not the target's caller 2583 (`score
# 32 over 35 rows`), so no stand-in is needed for remove's six other target callers. RemoveFile's name, its line (305)
# and its being a static member, as every CSystem function the records name is, are chosen. The target's use band 4 runs
# 2762 (IsEmptyDir), 2761 (ZeroFill), 2760 (RemoveFile), 2759 (GetFileSize), a higher index linking first. RemoveTree
# (line 155), the first function here to mention ZeroFill, puts ZeroFill ahead of RemoveFile and GetFileSize as the
# target has them (ld_index order in build/out/wasm-map/vota_web/names.tsv: ZeroFill, RemoveFile, GetFileSize);
# with RemoveFile the first to mention it, ZeroFill and RemoveFile were the other way round. Either way the
# order is no difference of bytes (docs/how-to-decompile.md step 3, "The order of two members"). IsEmptyDir (2762,
# record at line 255:15, a static member as the record prints it) is written there: ExistDir's test inlined (ExistResource
# and S_IFDIR), the throw of 7036 with "O diretório [{}] não existe: {}" and strerror(errno), then a CDirReader over the
# directory (unit 21) that stops with false at the first subdirectory other than "." and ".." and at the first file.
# Written so with a break at each (pnpm wasm score against the target, before step 8): every row operand-only (30 over
# 416), and it matches. With the flag tested in the loop's condition (`while (vazio && leitor.NextEntry())` and an
# if/else that sets it) it scored 59 over 416, and this fragment's earlier spellings 62 over 416 (`else if (IsFile())
# vazio = false`, `vazio = !IsFile()`, `vazio &= !IsFile()`): the target goes round the loop on a test of its own, not on
# the flag's value (a reading of its rows). The break form, the variables' names and the enumerator's name (7036,
# api/util/eueutilerror.h) are chosen. Its target callers are 5572, 5821, 11167 and 12134; 5821, 5572 and 11167 are
# written (unit 122's CompactaWsq, unit 179's ValidaConteudo, and DiretorioContemApenas, below, inlined into 11167), and
# the roots stand in for 12134 with one call.
# api::CreateDir (a chosen name, a free function, no record and no target index): it walks a path held in a
# std::string component by component (std::find of '/', each component's characters pushed onto the prefix) and calls
# mkdir(prefix, 0755) for each component ExistDir does not find, stopping at a failure; binaryen inlines it into its one
# caller, fn 5821, where it keeps its own 112-byte frame and holds ExistDir's code inlined, which only this file's
# functions can do (ExistResource is file-static), so it is here. Its result, false at a failure, is chosen (5821 reads
# none), and so are the std::copy into a back_inserter for the pushes, `std::distance(...) > 0` for the signed test and
# its line after IsEmptyDir; its rows are not scored apart from 5821's (unit 122's fragment).
# api::DiretorioContemApenas (a chosen name, a free function, no record and no target index): true when a directory
# holds files only, at least as many as the patterns it is given, each file matching one of them and each of them one of
# the files (CasamTodos both ways); false for no pattern, a directory ExistDir's code does not find, one IsEmptyDir (fn
# 2762, a call) finds empty, or one holding a directory other than "." and "..". binaryen inlines it into its one
# caller, fn 11167 (comum::impl::CValidaMidia's slot 8, unit 179), where it keeps its own 128-byte frame and calls
# ExistResource (fn 1690) itself, which only this file's functions can do, so it is here. The target tests IsDir first,
# then the two names, and calls IsFile for "." and ".." as well (its rows), which `IsDir() && nome != "." && nome !=
# ".."` before `IsFile()` gives. Written so, 11167 scored 43 over 609 rows, every row operand-only and none outside calls
# and data addresses (pnpm wasm score after tools/round/link-map.sh, before step 8), splat-remap --no-kinds printed
# IDENTICAL, and it matches. Its parameters' order, the result's type and its place after CasamTodos are chosen.
# Not reconstructed either: AreFilesEqual (records at lines 724 to 745), which 12134 holds inlined, a trap of unit 220
# (its pending file says why it stays one). The flag CSystem::s_dorme, defined here, and the inline CSystem::Dorme over it are
# unit 81's (ISound::Wait, fn 8461, is the first reader written); api/util/csystem.h says what is chosen about them.
#
# CopyFile (378), records at lines 390 to 476 (390:15, 397:15, 414:15, 448:15, 456:19, 465:19, 471:19, 476:19). Its
# record has four parameters (two strings, two bools), its wasm type three: every target caller passes the same value
# for one bool, which binaryen's dead-argument elimination folds (docs/reference/facts/reading.md R1), and 2725 passes
# 1 for the other where its 14 other callers pass 0. The record at line 390 (1584692) is loaded by no function, and its
# message, "O arquivo de destino [{}] já existe" (173211, 35 B), by no target piece (neither the address nor the packed
# `(35 << 32) | 173211` in build/out/splat/pieces/asm): the throw tests the folded bool. Which bool is folded, the names
# sobrescreve and preservaAtributos, the folded value (true), the test's ExistFile and 7041, the throw's code, are
# chosen (api/util/eueutilerror.h). The body: no copy of a file onto itself (a size compare and memcmp), the source
# opened O_RDONLY, the destination O_WRONLY | O_CREAT | O_TRUNC with O_SYNC when CSynchronizer's byte is set and mode
# 0644 (the constants 577, 1052672 and 420 are the target's), a 32768-B zeroed buffer copied with read and a write loop,
# errno kept across the closes, then, under the bool that varies, lstat of the source, utime, the owner and the mode.
# The second open's failure throws strerror of the errno it saved and wrote back (the target passes the saved value).
# The buffer is a std::vector<char>, a choice: the target allocates it with operator new, clears it with memory.fill and
# frees it after CSynchronizer::Sync, not on the throw paths; other forms were not measured. AlteraDono and
# AlteraPermissoes: the target holds two second stack-pointer prologues of 96 B (a struct stat), so binaryen inlined two
# functions with one caller each (docs/how-to-decompile.md step 3); each re-reads the destination string's c_str at every
# use, so each takes the std::string; each tests st_mode & S_IFREG (0x8000), not S_ISREG, and EPERM (63) and EACCES (2)
# after a failed open. Their names, lines (83 to 153) and their being external free functions are chosen. Measured on
# their result, object probes at uenux2's flags: `return r < 0 ? -1 : 0;` in each branch, `if (r < 0) return -1;
# return 0;` in each branch (also at -O1, -O2, -Os and -Oz), one result variable tested once, and a test before the
# closedir all compile to `i32.shr_s 31` where the target branches; one `return 0` after an if / else if / else gives
# the target's branches and block order. The O_SYNC flag: the target computes the
# select of O_SYNC before it loads the destination string and ORs it with 577 at the open. Written inline (`Habilitado()
# ? O_SYNC : 0`, `flags |= O_SYNC` after an if, or with the folded bool choosing O_TRUNC or O_EXCL) it is folded into
# one select of O_SYNC | 577 and 577 at the call: `score 175 over 1956 rows (same 1781, replaced 165 [162
# operand-only], inserted 5, deleted 5)`. An out-of-line CSynchronizer::GetOpenFlag (unit 154), which binaryen inlines
# into its one caller, gives `164 over 1951 rows`, every row an operand, and the match; that it is out of line, in
# csynchronizer.cpp, is a choice that gives those bytes.
# Rename (record 692:15) has no target index: binaryen inlines it into its one caller, fn 11584 (comum::CGravadorLog's
# slot 7, not written), so its body is compared with nothing by the splat build (docs/reference/splat.md "Reviewing a
# match"). Compared by hand (`pnpm wasm fn` of target 11584 and of the roots' RenomeiaUma, which holds our copy of it
# inlined, the callees named by splat/matched.txt, the symbol file and names.tsv): the copy in 11584 has a stack-pointer
# prologue of its own of 528 B, as ours has, and the same 13 calls in the same order, memcmp, rename,
# __cxa_allocate_exception, __strerror_l, 5456, __try_constant_folding, __vformat_to, ~locale, a basic_string
# constructor, emscripten_builtin_free, ~__optional_destruct_base, CBaseError<EUeUtilError>'s constructor (after
# 7058, both) and __cxa_throw. Its store order is the same: `pnpm --silent wasm score ../target/vota_web_wasm.wasm
# 11584 ../build/out/wasm/vota_web/vota_web_wasm.wasm <RenomeiaUma's index in names.tsv>` pairs each of our 30 stores
# with an identical row of 11584's copy, in order; what differs is operands, local numbers and the first argument,
# which 11584 reads out of its own frame. It is written because its std::format of two
# strings and a char* shares the arguments' builder (fn 5456, a libc++ instance this object emits) with CopyFile, which
# the target calls from both: binaryen inlines a function with one caller (docs/how-to-decompile.md step 3), so Rename
# is what keeps 5456 out of line, a reading (a link without Rename was not measured). Rename also gives libc's rename
# (fn 3974) a second caller in our link beside 7-Zip's MyMoveFile (wasm-objdump -d of the link), and 3974 matches. The
# libc callees chmod (3997) and chown (6281), called twice by the helpers, and utime (6238) match.
# RemoveTree (5458) has no record. ledger/tu-clusters.tsv stretch 763 (5453 to 5461) is labelled csystem.cpp, and in
# use band 2 the target runs 5459 (ExistDir), 5458, 5457 (truncate), 5456, a higher index linking first, so 5458 is an
# external function defined between ExistDir and truncate (docs/how-to-decompile.md step 3, "What a record's place
# says"); ours links in that order (ld_index, names.tsv). Its name and line (155) are chosen. It reads
# CDirReader's current entry name inline, which api/util/cdirreader.h gains as GetEntryName (a chosen name). Measured in
# the whole link: with the struct stat declared in the second loop, `129 over 678 rows` (frame offsets: the target puts
# the stat, which shares its slot with the loop's name string, above the vectors); declared first, `52 over 678`, 9
# rows inserted, 1 deleted (`diretorio + '/'` reloads the name's size after the allocation, which the target reuses);
# with `"/"`, `30 over 669 rows (same 639, replaced 30 [30 operand-only], inserted 0, deleted 0)`, every differing row a
# call or a data address. It calls itself, so its name waits for a caller's vote (docs/how-to-decompile.md step
# 1, "The row's own symbol"): 5455's call gives it (splat/symbol_addrs.txt, evidence:call by:5455), and it matches.
# GetFreeSpace and GetUsedSpace (5454 and 5453, no record, names chosen): stretch 763 too, after 5455 in band 2, so
# defined late in the file (their lines, after ZeroFill, are chosen). Each builds a std::filesystem::path from the
# string and calls std::filesystem::space; the path is named first, which puts it above the space_info as the target's
# frame has it (a temporary path scored `20 over 70 rows` for 5453, 5 inserted, 5 deleted). Written, they score `3
# over 60` and `3 over 65`, operand-only, three calls each, and they match since their callee, libc++'s
# std::filesystem::__space (target fn 4677), does. At b7c2e8a5 our link's copy, libc++.a's operations.o, scored `20 over
# 237 rows (same 217, replaced 9 [8 operand-only], inserted 9, deleted 2)` against 4677 (`pnpm wasm score
# ../target/vota_web_wasm.wasm 4677 <our link> <its index>`): libc's statfs (3972, musl's __statfs, which statvfs calls)
# was inlined into it, as statvfs is, our link's one caller of statfs. The target keeps statfs out of line: 2725
# (comum::CControlaArmazenamentoDeImagens, records at ccontrolaarmazenamentodeimagens.cpp 73 to 152) and 5371 (the
# "me{:06}.wsq" writer) call it on a path's c_str() (ledger/callgraph.tsv). The roots' LivreEmDois stood for those two,
# one call each; with it 4677 read `4 over 228 rows`, all operand-only, and 3972 `1 over 11`, and the scan matched 3972
# (pair-addr), 4677, 5453 and 5454 (census pairs). Both are written now (units 293 and 214), so the stand-in went, and
# the four still match. Its helper
# std::filesystem::detail::capture_errno (845) matches since it is in our link.
# GetMemInfo (5463, no record, a chosen name) returns the number on the line of /proc/meminfo that holds the field it
# is given; its one caller, 10226 (vota::CThreadMonitor's slot 2, unit 116's), passes
# "MemTotal" and "MemFree", each from a stack frame of its own (below). It
# reads the file into a zeroed 4096-B buffer (a std::vector<char>, a choice, as CopyFile's), keeps of the string built
# from the buffer as many bytes as read returned, finds the field, cuts its line at '\n' and converts the digits
# between find_first_of and find_first_not_of("0123456789") with ecourna's CStringUtils::ToDWord (fn 1523). Measured
# in the whole link: testing both positions after both searches, `39 over 564 rows (same 525, replaced 28 [25
# operand-only], inserted 7, deleted 4)`, where the target skips find_first_not_of when find_first_of finds nothing;
# with the second search inside the first test, `18 over 557 rows (same 539, replaced 18 [18 operand-only], inserted
# 0, deleted 0)`, the callees, the literal 4096 at its three uses and the string's address, and the scan matches it.
# Object probes at the tree's flags: building the string as `std::string(std::string(buffer), 0, lidos)` gives the
# same object as `std::string(buffer).substr(0, lidos)`; `new char[4096]()` with delete[], and a resize of the string,
# give others. Its place is a choice: in use band 2 it links after 5465 and 5464 (api::CStringUtils's CasaRegex and
# CasaCaractere, unit 179's notes) and
# before 5462, 5461, 5460 and ExistDir (5459), and its nearest neighbours with records are cgenerictags.cpp's
# AppendTLV (5466) on one side and this file's truncate (5457) on the other, so it is a function defined ahead of
# ExistDir in csystem.cpp or in a file that sorts between the two (docs/reference/facts/placing.md P5: the side taken
# is a choice). It is written at the end of csystem.cpp, as the free lines above ExistResource's record are too few
# for it.
# GetFreeSpace, GetUsedSpace and GetMemInfo read no state of CSystem, which is no singleton; that they are free
# functions and not static members of CSystem is a choice (docs/how-to-decompile.md step 3 allows either: CSystem's
# records name only static members that read no state). Nothing names a class for them: they load no record, no table slot holds them (`pnpm wasm fn`),
# the symbol file had no line of evidence for them, their one caller is 10226 (ledger/callgraph.tsv), and a direct
# call is the same for a static member and a free function. Chosen: their namespace, api, the one of the file they are
# written in (step 3's "the namespace of its caller's class" is said of an inlined helper; their caller is vota's), and
# their declarations in api/util/csystem.h. Written as static members of CSystem, the three gave the same object:
# wasm-objdump -d and -x -r of csystem.cpp.o under either form differ in their three symbols alone, and 5463 matched
# under either name.
# ReplaceFile (5455, 4258 B) has no record of its own; its records are TemporaryPath's (a static member, as they print
# it) and those of PrepareReplace and ReplaceResource, both in the anonymous namespace. Its name is chosen from the text
# "CSystem::ReplaceFile" (184723) it passes to both, with "arquivo" (124102, the tail of "O arquivo"); the parameters'
# names and the backup's role are chosen from what the body does: the backup path is the third string, or when that is
# empty TemporaryPath's mkstemp name for the first, removed at once with RemoveFile's code; it throws when the first
# file does not exist (ExistFile through the record's function pointer: a direct call of 412), when the two names are
# the same and when the backup exists; then the second is renamed to the backup, the first to the second (and on
# failure the backup back), each through RenameResource, whose message is the throw's after `contexto + " - "`; last
# the backup goes, with RemoveTree and rmdir when ExistDir says a directory, RemoveFile's code when ExistFile says a
# file. Its one target caller, 7174 (vota::impl::CSincronismoVotoEleitor's slot 2), calls it twice with an empty third
# string: the roots' RepoeDois stands for it, and ZeraAmbos and RemoveUmaArvore, which stood for 5455, are gone.
# The target's frames, read from pnpm wasm fn's disassembly: 48 B for ReplaceFile's three strings, and nested in it
# 608, 544 and 160 B, the frames of PrepareReplace, TemporaryPath and ReplaceResource, which binaryen inlined (with
# libc's mkstemp inside TemporaryPath's). clang inlines an internal function of one call site, so PrepareReplace and
# ReplaceResource had a second caller in the TU (a reading): CSystem::ReplaceDir, a chosen name over ExistDir and
# "diretorio", gives them one, and the link drops it, as nothing calls it (build/out/wasm-map/vota_web/names.tsv has
# no ReplaceDir). Measured in the whole link: all of it inlined by clang, with an earlier body, `785 over 1982 rows
# (same 1197, replaced 494 [449 operand-only], inserted 146, deleted 145)`, a 704-B frame where the target's are 48 and
# 608; the body as landed without ReplaceDir scores `717 over 1984 rows (same 1267, replaced 439 [400 operand-only],
# inserted 148, deleted 130)`, and then 5455 anchors nothing, so RenameResource (3645) and RemoveTree (5458) lose the
# names its calls give them: those two matches rest on this reading; with ReplaceDir,
# `365 over 1847`, the frames 704 and 256 where the target's are 608 and 160 (a struct stat of each function's own,
# 96 B more each); with the stat tests through Existe (an anonymous-namespace helper, a chosen name, which clang
# inlines: no target index), whose struct stat ends with it as the target's slot shared with the throws' buffers says,
# `168 over 1837`, inserted 1, deleted 12: the long-string test before the first move into erro, which the target
# keeps and ours dropped. The destination's rename in the condition of its test (line 953) keeps it (an object compile,
# wasm-objdump -d of ReplaceResource: the test before the move with it, none with the test after an if of its own,
# `std::string erro = ""` or erro.assign()); the throw's column 15 rules out a test nested in the rename's block. Then
# `score 155 over 1836 rows (same 1681, replaced 155 [155 operand-only], inserted 0, deleted 0)`: calls, data
# addresses, the packed format strings and table slots. It stays `unresolved self-voted` (splat/scan.tsv: `+0x205
# i32.const 1932552: __randname.counter = 0x1d7d08 (evidence:vote:2 by:5455) comes from this function's own operand`):
# the counter of libc's __randname, inlined into it, is a .bss word no other target function reads (`/usr/bin/grep -rlE
# 'i32\.const 1932552($|[^0-9])' build/out/splat/pieces/asm` lists only ecourna/5455.wat), so nothing but the match
# would name it (docs/reference/splat.md "No circular evidence"). It stays written: its calls give its callees
# RenameResource and RemoveTree (3645, 5458) the names they match under; 5460 and 2858, pair-fingerprint, are in our
# link because ReplaceFile's code emits them. The lines of TemporaryPath (230 to 247), RenameResource, Existe,
# ReplaceFile and ReplaceDir within what the records leave free, and the error codes' names, are chosen.
# RenameResource (3645, 608 B): `"RenameResource(" + origem + ", " + destino + ") - " + strerror(errno)` when rename
# fails, else an empty string. Its name is chosen from that text, and its linkage (the anonymous namespace, as its
# callers'): no record names it. Named by 5455's call (evidence:call by:5455), it matches; ReplaceResource calls it
# three times, the target's 5455 too. Its ") - " gives ecourna::api::exception::CError's constructor (1143, unit 112's
# note) the literal whose tail it uses, and 1143 matches too.

# Added since: api::GetFileName and GetDirName (target fns 2763 and 5462, no record), the part of a path held in a
# std::string after its last '/' (the whole string when it holds none: the target copies it whole, and substr after the
# '/', which can throw out_of_range) and the part before it (`substr(0, rfind('/'))`). Their callers are comum's and
# vota's (2763: 1501, 5360, 5461, 12098; 5462: 1501 and 12098), and both lie in this file's run of the use bands, 5462 in
# band 2 between 5461 and 5463 (GetMemInfo) and 2763 in band 4 just ahead of 2762 (IsEmptyDir's record, 255) and
# ZeroFill. They read no state of CSystem; that they are free functions of api and not static members of CSystem is a
# choice, GetMemInfo's form, and so are their names. Written as static members of CSystem with GetFreeSpace,
# GetUsedSpace and GetMemInfo, all five compile to the same code (wasm-objdump -d of the two csystem.cpp.o: the
# symbols and one object-local data offset in GetMemInfo, 1472 against 1480, apart). Their places: GetFileName after ExistDir, so that it links ahead of ZeroFill, RemoveFile and GetFileSize as
# 2763 does in its band; GetDirName after GetMemInfo, at the end of the file, which keeps 5463 ahead of it as band 2 does
# and, like GetMemInfo, takes it after ExistDir where the band has it before (a choice, the same one GetMemInfo's place
# makes). 1501 (vota::CAssinadorVota's constructor, comum::CAssinador's inlined) calls each once: PartesDoCaminho in the
# roots stands for 12098 and 5360 (5461 is in the link), so binaryen keeps both out of line as the target does.
# GetMemTotal and GetMemFree (no target index, chosen names, free functions after GetMemInfo, a choice): 10226 calls
# GetMemInfo twice, each time after a 16-B stack frame of its own that builds the field's name, "MemTotal" or
# "MemFree", as a std::string, so each call sits in a function binaryen inlined into its one caller; clang would inline
# so small a function into a caller in its own file, so these two are another object's than 10226's, this one (a
# reading). 10226 widens their results as signed numbers (i64.extend_i32_s), so they return long, a choice of a signed
# 32-bit type. They give GetMemInfo its two call sites in our link, where the roots' MedeEspaco stood for 10226 until
# 10226 was written (unit 116); with it in the link, MedeEspaco and its calls of 5454, 5453 and 5463 went.
# api::CasamTodos (2758) and CasaPadrao (no index: binaryen inlines it into 2758), with the predicate CCasaNome of
# csystem.cpp's anonymous namespace, added since for unit 179's comum::impl::ValidaConteudo (5572): every chosen name,
# the form each was measured in and what 2758 waits for are in src/units/179-uenux2-cvalidamidia.mk. They follow
# ZeroFill in the file: in band 4, 2758 links after GetFileSize (2759), csystem.cpp's last function there.
# api::TrocaExtensao (target fn 5461; no record: its name, its being a free function and its namespace are chosen, as
# GetFileName's are), the last function of csystem.cpp: a path with the extension after its last '.' replaced, called
# by unit 280's comum::CarregaPleito (5778) with "pid" and by 7787 (not written; unit 280's roots stand in for it). It
# holds GetDirName's code inline twice, the target's two copies of the part before the last '/' (the first only compared
# with the path), and calls GetFileName (2763): clang inlines GetDirName only in its own TU, so 5461 is this file's. In
# use band 2 it lies right after GetDirName (5462) and before 5460 and ExistDir (5459): after GetDirName at the file's
# end, it takes the place after ExistDir that GetDirName's takes (a choice, as above). Matched; what the rows decided,
# each step measured with `pnpm wasm score` against the whole link: the prefix a temporary of the return (the target
# appends the name's head to it and moves the result; a named prefix, 146 over 701 rows, 33 inserted and 34 deleted,
# against 127 over 700); the empty directory and prefix "" (the target stores only a short string's size and
# terminator, where std::string() zeroes all twelve bytes: 89 over 700); each conditional's "" arm second (the target
# lays it out last: 45 over 683); and "/" where '/' gave another block order inside operator+ (13 over 668, all
# operand-only, as written).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSYSTEM_SRCS := src/api/util/csystem.cpp
UENUX2_SRCS += $(CSYSTEM_SRCS)
# no caller of these functions outside the file is reconstructed yet: 32-uenux2-csystem-roots.cpp gives each the call
# sites the target gives it (its header names the callers each stand-in stands for)
$(ROOT)/$(APP)/32-uenux2-csystem-roots.o: $(ROOT)/src/units/32-uenux2-csystem-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/32-uenux2-csystem-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/32-uenux2-csystem-roots.o
