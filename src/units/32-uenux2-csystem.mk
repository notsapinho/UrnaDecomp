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
#   5458, 5454, 5453  RemoveTree, GetFreeSpace, GetUsedSpace, no record: written, no-candidate (below)
#   5463  CSystem::GetMemInfo, no record
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
# record at line 255) is not written.
# Written over ExistDir, the CDirReader members of unit 21 and the entry's name, it scores `62 over 416 rows (same 354,
# replaced 47 [43 operand-only], inserted 0, deleted 15)` in the whole link: ours returns the inverse of the last
# NextEntry's result, where the target keeps the flag in a local of its own. Three spellings of the flag's update (`else
# if (IsFile()) vazio = false`, `vazio = !IsFile()`, `vazio &= !IsFile()`) give the same object, and whole-link tries at
# `--flags -fstrict-aliasing` and `--flags -O2` give the same score. Not reconstructed either: 5455 (TemporaryPath's,
# PrepareReplace's and ReplaceResource's records), AreFilesEqual (12134) and std::operator+(string&&, const string&)
# (5460), whose one caller is 5455. The flag CSystem::s_dorme, defined here, and the inline CSystem::Dorme over it are
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
# slot 7, not written). It is written because its std::format of two strings and a char* shares the arguments' builder
# (fn 5456, a libc++ instance this object emits) with CopyFile, which the target calls from both: binaryen inlines a
# function with one caller (docs/how-to-decompile.md step 3), so Rename is what keeps 5456 out of line, a reading (a
# link without Rename was not measured). Rename also gives libc's rename (fn 3974) a second caller
# in our link beside 7-Zip's MyMoveFile (wasm-objdump -d of the link), and 3974 matches. The libc callees chmod (3997) and chown (6281), called twice by the helpers, and utime (6238) match.
# RemoveTree (5458) has no record. ledger/tu-clusters.tsv stretch 763 (5453 to 5461) is labelled csystem.cpp, and in
# use band 2 the target runs 5459 (ExistDir), 5458, 5457 (truncate), 5456, a higher index linking first, so 5458 is an
# external function defined between ExistDir and truncate (docs/how-to-decompile.md step 3, "What a record's place
# says"); ours links in that order (ld_index, names.tsv). Its name and line (155) are chosen. It reads
# CDirReader's current entry name inline, which api/util/cdirreader.h gains as GetEntryName (a chosen name). Measured in
# the whole link: with the struct stat declared in the second loop, `129 over 678 rows` (frame offsets: the target puts
# the stat, which shares its slot with the loop's name string, above the vectors); declared first, `52 over 678`, 9
# rows inserted, 1 deleted (`diretorio + '/'` reloads the name's size after the allocation, which the target reuses);
# with `"/"`, `30 over 669 rows (same 639, replaced 30 [30 operand-only], inserted 0, deleted 0)`, every differing row a
# call or a data address. It stays no-candidate: it calls itself, so its name waits for a caller's vote, and its other
# target caller, 5455, is not written (docs/how-to-decompile.md step 1, "The row's own symbol").
# GetFreeSpace and GetUsedSpace (5454 and 5453, no record, names chosen): stretch 763 too, after 5455 in band 2, so
# defined late in the file (their lines, after ZeroFill, are chosen). Each builds a std::filesystem::path from the
# string and calls std::filesystem::space; the path is named first, which puts it above the space_info as the target's
# frame has it (a temporary path scored `20 over 70 rows` for 5453, 5 inserted, 5 deleted). Written, they score `3
# over 60` and `3 over 65`, operand-only, three calls each; they stay no-candidate while their callee, libc++'s
# std::filesystem::__space (target fn 4677), has no name: our link's copy, libc++.a's operations.o, holds invoke_*
# landing pads the target's lacks (`pnpm wasm score ../target/vota_web_wasm.wasm 4677 <our link> <its index>`: `169 over
# 385 rows`, 157 inserted). Its helper std::filesystem::detail::capture_errno (845) matches since it is in our link.
# GetMemInfo (5463, no record, a chosen name) returns the number on the line of /proc/meminfo that holds the field it
# is given; its one caller, 10226 (vota::CThreadMonitor's slot 2, not written), passes "MemTotal" and "MemFree". It
# reads the file into a zeroed 4096-B buffer (a std::vector<char>, a choice, as CopyFile's), keeps of the string built
# from the buffer as many bytes as read returned, finds the field, cuts its line at '\n' and converts the digits
# between find_first_of and find_first_not_of("0123456789") with ecourna's CStringUtils::ToDWord (fn 1523). Measured
# in the whole link: testing both positions after both searches, `39 over 564 rows (same 525, replaced 28 [25
# operand-only], inserted 7, deleted 4)`, where the target skips find_first_not_of when find_first_of finds nothing;
# with the second search inside the first test, `18 over 557 rows (same 539, replaced 18 [18 operand-only], inserted
# 0, deleted 0)`, the callees, the literal 4096 at its three uses and the string's address, and the scan matches it.
# Object probes at the tree's flags: building the string as `std::string(std::string(buffer), 0, lidos)` gives the
# same object as `std::string(buffer).substr(0, lidos)`; `new char[4096]()` with delete[], and a resize of the string,
# give others. Its place is a choice: in use band 2 it links after 5465 and 5464 (callees of fn 2758, not written) and
# before 5462, 5461, 5460 and ExistDir (5459), and its nearest neighbours with records are cgenerictags.cpp's
# AppendTLV (5466) on one side and this file's truncate (5457) on the other, so it is a function defined ahead of
# ExistDir in csystem.cpp or in a file that sorts between the two (docs/reference/facts/placing.md P5: the side taken
# is a choice). It is written at the end of csystem.cpp, as the free lines above ExistResource's record are too few
# for it.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSYSTEM_SRCS := src/api/util/csystem.cpp
UENUX2_SRCS += $(CSYSTEM_SRCS)
# no caller of these functions outside the file is reconstructed yet: 32-uenux2-csystem-roots.cpp gives each the call
# sites the target gives it (its header names the callers each stand-in stands for)
$(ROOT)/$(APP)/32-uenux2-csystem-roots.o: $(ROOT)/src/units/32-uenux2-csystem-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/32-uenux2-csystem-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/32-uenux2-csystem-roots.o
