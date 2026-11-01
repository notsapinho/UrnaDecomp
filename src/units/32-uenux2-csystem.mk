# uenux2 api::CSystem in src/uenux2/src/api/util/csystem.cpp, the file its std::source_location records name, with the
# class header api/util/csystem.h and the EUeUtilError enumerators of api/util/eueutilerror.h its throws pass:
#   2759  CSystem::GetFileSize           record at line 334, col 15 (7038)
#   5457  api::truncate                  record at line 1024, col 15 (7070)
#   1690  api::ExistResource             record at line 64, col 15 (7031)
#   2761  CSystem::ZeroFill              record at line 1039, col 15 (7069)
#   412, 5459  CSystem::ExistFile and ExistDir, no record; 6019 is binaryen's merge of the two
#   2760  CSystem::RemoveFile, no record
#   10858, 10859, 10860  slots 8, 7 and 6 of the std::function block of ZeroFill's lambda (__func<...ZeroFill...::$_0>)
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
# UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6). With -fno-strict-aliasing our object stored the vptr before the captured pointer, where the target
# stores the pointer first, and 10862 calls the shared body of the lambdas' clones (target fn 1083), which our link
# formed with RHVoice's and which stored the vptr first; it matches with app/comum/dados/md/rdv/cvotos.cpp's lambdas
# built with strict aliasing too. RemoveFile (2760) calls ZeroFill unless lstat says the path is a symbolic link, then
# libc's remove (fn 1572), which matches with it. At 694de52 our link has no body of remove
# (build/out/wasm-map/vota_web/names.tsv); with RemoveFile it has one, called by RemoveFile and by 7-Zip's
# NWindows::NFile::NDir::DeleteFileAlways (wasm-objdump -d of the link), which is not the target's caller 2583 (`score
# 32 over 35 rows`), so no stand-in is needed for remove's six other target callers. RemoveFile's name, its line (305)
# and its being a static member, as every CSystem function the records name is, are chosen. The target's use band 4 runs
# 2762 (IsEmptyDir), 2761 (ZeroFill), 2760 (RemoveFile), 2759 (GetFileSize), a higher index linking first. RemoveFile,
# the first function here to mention ZeroFill, puts ZeroFill ahead of GetFileSize as the target has it (ld_index in
# build/out/wasm-map/vota_web/names.tsv: RemoveFile, ZeroFill, GetFileSize); ZeroFill and RemoveFile stay the other way
# round from the target's, which a function above line 305 that mentions ZeroFill would give. None is written, and the
# order is no difference of bytes (docs/how-to-decompile.md step 3, "The order of two members"). IsEmptyDir (2762,
# record at line 255) is not written.
# Written over ExistDir, the CDirReader members of unit 21 and the entry's name, it scores `62 over 416 rows (same 354,
# replaced 47 [43 operand-only], inserted 0, deleted 15)` in the whole link: ours returns the inverse of the last
# NextEntry's result, where the target keeps the flag in a local of its own. Three spellings of the flag's update (`else
# if (IsFile()) vazio = false`, `vazio = !IsFile()`, `vazio &= !IsFile()`) give the same object, and whole-link tries at
# `--flags -fstrict-aliasing` and `--flags -O2` give the same score. Not reconstructed either: 5455 (TemporaryPath's
# records), CopyFile (378), Rename (11584), AreFilesEqual (12134), 5458 and std::operator+(string&&, const string&)
# (5460), whose one caller is 5455. The flag CSystem::s_dorme, defined here, and the inline CSystem::Dorme over it are
# unit 81's (ISound::Wait, fn 8461, is the first reader written); api/util/csystem.h says what is chosen about them.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSYSTEM_SRCS := src/api/util/csystem.cpp
UENUX2_SRCS += $(CSYSTEM_SRCS)
# no caller of these functions outside the file is reconstructed yet: 32-uenux2-csystem-roots.cpp gives each two call
# sites or more
$(ROOT)/$(APP)/32-uenux2-csystem-roots.o: $(ROOT)/src/units/32-uenux2-csystem-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/32-uenux2-csystem-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/32-uenux2-csystem-roots.o
