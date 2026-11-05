# uenux2 comum::CPath (src/app/comum/cpath.cpp, cpath.h), the urna's directories, with the EFlashOrigem enum
# (src/app/comum/eflashorigem.h) and three codes of EUeComumError (src/app/comum/euecomumerror.h).
#
# Matched: GetPathRootSemSA (target fn 634), GetPathTrab(EFlashOrigem) and GetPathResult(EFlashOrigem) (436, 1274),
# GetPathRoot (3834), GetPathEstatico and GetPathDinamico (762, 1082, thunks of binaryen's merge 6047, which the two
# form here too), GetPathMR and GetPathChave (949, 1948, thunks of the merge 6048), GetPathLog (5899), GetPathWsq
# (2864), the exit destructors of the two statics (11649, the array; 11648, the root), and libc++'s
# path::__relative_path (1651), which comes with them. Unit 06's ICompressor::Add over a vector of paths (9530) matches
# with this unit: it calls path::__filename (1224), which the symbol file names from GetPathTrab's and GetPathResult's
# calls (`call by:358,1399`).
#
# GetPathTrab and GetPathResult with the turn (358, 1399) match since mock/app/comum/cappinfobuilder.cpp links ahead of
# this object at the executable TU's rule (unit 253). They were operand rows only (`pnpm wasm score`: 37 over 393, 30
# over 323), and the scan stopped at the turn's format handle, `differs ... target i32.const 474 | ours i32.const 966`:
# slot 474 is fn 9868, EUrnaTurno's handle at -Oz, which the target keeps apart from the 31 slots of 536 and our link
# merged into 536's body until that object gave every user its copy. Unit 109's CAppInfo::IndiceTurno (1553) was the
# same case.
#
# path::operator/=(const path&) (183), has_filename (3679) and has_root_directory (5549) match from
# mock/app/comum/cappinfobuilder.cpp's object, at the executable TU's rule (unit 253), since unit 227's
# CMontadorHash::CriaHashesDiretorio (5360) calls std::filesystem::weakly_canonical, whose libc++.a functions 7738, 7742
# and 7749 (matched with it) call 3679 and 5549 too. Before unit 253, 183 differed, 87 over 105 rows, from cpath.cpp's
# copy at the tree's -O3, which inlines has_root_directory, operator= and has_filename; a compile of operator/= at the
# executable TU's -Oz -fexceptions keeps has_root_directory, operator=, has_filename, push_back and append(const
# string&) as calls, in that order, which are 183's callees 5549, 1700, 3679, 409 and 3717, and with that object (a
# function returning `a /= b`) first on the link line, as docs/reference/facts/levels.md V4 does, its copy, the link's
# from unit 253 until 5360 was in it, read 31 over 52 rows (at b1711c89): binaryen inlined has_root_directory and
# has_filename, which had one caller there, where the target's 5549 has 183 and 7749 and 3679 has 183, 7738 and 7742,
# three functions only the table holds (slots 8848, 8871, 8866). That the three are the executable TU's copies was read
# so, and the callers 5360 brings are what they waited for (docs/reference/facts/splat.md S10 item 29).
#
# Written and not matched, each with its measurement:
# - path::__filename (1224) is libc++.a's, and matches with 1840 (path::__parent_path) and 2134 (PathParser::decrement,
#   which calls consumeName and consumeAllSeparators), both libc++.a's, since unit 62's CWasmLogd constructor, inlined
#   into fn 8302, calls 1840. Before, 1224 read 180 over 252 rows and our link had no body of 2134
#   (build/out/wasm-map/vota_web/names.tsv named none), read as binaryen inlining it into __filename, its one caller
#   then. 2134's third target caller, 5360, has no body of ours.
#
# Evidence:
# - The three records (cpath.cpp lines 153, 189, 216, column 11) give the names, `static`, the std::filesystem::path
#   result and the parameter types. The throws' codes are what each passes to CBaseError<EUeComumError>'s constructor
#   (fn 480): 7224 (634), 7226 (1399), 7227 (358). 634 formats an int (type 3), so the origin is cast; 358 and 1399 pass
#   the turn's handle (15).
# - The two statics: a 24-byte object at 1838576, 16-aligned, that the static initializer builds from "/dsk/fi/" and
#   "/dsk/fe/" and fn 11649 destroys in reverse, which 358, 1399, 762 and 1082 index by the origin times 12; and a path
#   at 1838600, built from "/" and destroyed by fn 11648, that 634, 949, 1948 and 3834 copy. The bands put 3834 (uses 3)
#   between cinfomtlcd.cpp's 3836 and iinterfaceinit.cpp's 3833, 2864 (uses 4) between
#   informacao/cinformacaoeleicao.cpp's 2865 and iinterfaceinit.cpp's 2862, and 11648, 11649 (uses 1) between
#   cinfomtlcd.cpp's 11653 and iinterfaceinit.cpp's 11646: where cpath.cpp's records lie in the data
#   (docs/reference/facts/placing.md P5), a reading that fits the file.
# - GetPathLog is read as inline in cpath.h, and the array is declared there with no bound. 5899 loads 1838576 with
#   `i64.load align=2`, where the static initializer, the code 8302 and 12098 hold behind a second prologue and the
#   code 11620 (comum::CGravadorHashes's slot 7) holds behind a third (each read as functions of this file binaryen
#   inlined there) use align=3. Measured on probes at the tree's flags: a TU that declares the array as path[2] loads
#   it with align=3, one that declares it with no bound with align=2, and every function of the TU that defines it
#   gets align=3, defined before the definition or after. 5899 lies in band 2 after cpacotearquivos.cpp's 5900 and
#   5901 and before iinterfaceinit.cpp's 5897, where a copy deferred to the end of cpacotearquivos.cpp's object would
#   be: a reading. Our copy comes from the roots object, compiled at UENUX2_CXXFLAGS.
# - 436 and 1274 call GetGeral's const overload (457), not the one GetInst()'s reference picks (291): `splat-remap` said
#   `differs at body byte 9 (target instruction +8 call 457)`; a `const CAppInfo&` local gives 457, as
#   CEleitorDetalhe::GetImpedimento (3769, matched) spells it.
#
# Measured forms (`pnpm wasm score` against the link, before step 8):
# - The turn's digit is appended with path::concat: `path += std::to_string(...)` calls string::append(const char*,
#   size_t) where the target calls 178, append(first, last), which concat gives (object of a variant, wasm-objdump -d).
# - GetPathMR, GetPathChave and GetPathRootSemSA's two cases name the path built from the literal before taking its
#   relative_path. The one expression `s_pathRoot / std::filesystem::path("...").relative_path()` gives the target's
#   rows with the two paths' frame slots swapped (6048: offsets 16 and 0 the other way round; 634: 416 and 48), and a
#   helper declared `inline` in cpath.cpp stays a call in 634.
# - Every call of operator/= keeps the target's `drop` only while its result has a reader: the target's 183 is table
#   slot 71, which fns 5968 (libc++'s operator/ of directory_iterator.o, in the link since unit 214) and 5821 (unit
#   122's CompactaWsq) pass to invoke_iii; both are in the link and take its address, as the roots did before 5821
#   was. Without that address, binaryen drops the result, and 358, 1399, 634, 2864, 6047 and 5899 each lost a row per
#   call (`deleted 2`, `1`, `2`, `1`, `1`, `1`).
# - The scores with the forms above: 634 42 over 484, 436 and 1274 3 over 8, 2864 8 over 83, 3834 6 over 23, 762 and
#   1082 3 over 7, 6047 5 over 66, 949 and 1948 3 over 6, 6048 12 over 153, 5899 11 over 61, all operand rows.
#
# Chosen, no evidence names them: every member's name but the three records', the statics' names, EFlashOrigem's
# enumerators, its comum:: scope and its header's path, cpath.h's path, the EUeComumError enumerators' names, the lines
# of every member but the three throws, the order of the members, GetPathWsq's class and file (2864 calls 358 and
# appends "wsq/"; its band fits cpath.cpp, above), and `static_cast<int>` for the origin's format argument.
#
# Not CPath's: 1487 and 1488, the "dinamico/imprimindo" marker, which call 634 and fn 620 (CSynchronizer::Sync, unit
# 154), written as vota's free functions in app/vota/comum/votadefs.cpp (unit 168); 3896, the merge body of
# CServicoEstadoGeralSA's, Gap's and Vota's GetPathArquivo (11565, 11567, 11568), those classes' slots, which unit 206
# writes. Not CPath's: 6035 and 6036, the merge bodies of 1701, 5762, 1551 and
# 2826, which build a string from GetPathTrab(EFlashOrigem) and "rdv.dat" or "uenux.db" and call 436: a probe
# function of cpath.cpp that does the same holds 436 inlined (calls of GetInst, GetGeral and 358), so they are read as
# another file's; their bands put them in crdv.cpp and celeitores.cpp, where unit 381 writes them. Not CPath's
# either: 5907, which destroys three members of the object at 1838544 and builds no path,
# is comum::CArquivosSavd's destructor (unit 95). The code 8302 and 12098 hold behind a second prologue, and 11620
# (comum::CGravadorHashes's slot 7) behind a third, that reads this file's statics (a setter of the root and the two
# flash paths in 8302; GetPathLog's body with "arquivados/" in 12098; s_pathRoot and s_pathFlash[0] in 11620, which
# appends "dinamico/" inline rather than calling 1082): 12098's waits for its caller; 11620's is written (below). The
# setter is written: CPath::SetPathRoot, a chosen name (unit 188's fragment says what its form rests on); binaryen
# inlines it into 8302, its one caller, so it has no target function, and no match checks it while 8302 does not match.
#
# Roots (190-uenux2-cpath-roots.cpp): it gives the members whose target callers are not all in the link the call sites
# its header lists (two each; none for 1399, whose callers 1164 and 1274 are both in the link, none for 634, whose
# callers 1164, 1487 and 1488 are, and none for 358) and emits GetPathLog's copy. It
# compiles at UENUX2_CXXFLAGS, app/comum's flags, since it emits GetPathLog, code of a tree header.
#
# Added since: CPath::GetPathTrabExterno (no target index), `std::filesystem::path path("/dsk/fe/dinamico/trab/");
# return s_pathRoot / path.relative_path();`, GetPathMR's form (above), under a chosen name. binaryen inlined it into
# comum::CArquivosSavd::GetInst (fn 1164, unit 95), its one caller, behind a stack frame of its own, where it builds the
# path of the package 156 ("tabcorr.vsc" under it). It is a member, as GetPathMR is, a choice (it reads s_pathRoot,
# private by our header's choice); its line, after GetPathChave, is a choice too. 1164 matches with strict aliasing in
# its TU (unit 95's fragment), so its match checks this body.
#
# Added since: CPath::GetDiretoriosSemHash and GetPathTmp (chosen names, no target index), the code 11620 holds behind
# its third and fourth frames, inlined by binaryen into comum::CalculaHashesArquivos (unit 136's cgravadorhashes.cpp),
# their one caller, as 11620 holds them: a std::set<std::string> built from eight paths converted to strings, the root
# followed by "dev/", "dsk/", "proc/" and "sys/", GetPathTmp (`std::filesystem::path path("/tmp/"); return s_pathRoot /
# path.relative_path();`, GetPathMR's form, its frame of 48 bytes), GetPathDinamico of the internal and the external
# flash, and the internal one followed by "tmp/". This file's object is the TU: it loads s_pathFlash[0] with `i64.load
# align=3`, as the TU that defines the array does (the GetPathLog paragraph above), and clang inlines GetPathRoot and
# GetPathDinamico there (-Rpass=inline: costs 40 and 200 against 250) and not GetPathTmp (490), the frames 11620 holds.
# Both are static members, as the file's landed members are (a choice: GetPathTmp reads s_pathRoot, private by our
# header's choice, and GetDiretoriosSemHash reads the statics through the members it calls); their lines, after
# GetPathTrabExterno, are a choice. The set's eight inserts are the one form measured that differs, and it waits for the
# flag: built without strict aliasing, as app/comum is, this object inlines libc++'s __emplace_hint_unique_extract_key
# into the set's insert loop and calls __emplace_hint_unique_key_args (fn 2281's body), where the target calls fn 1163,
# the emplace inlined into it, eight times, which is the shape a TU with strict aliasing gives (unit 136's fragment has
# the probe and the scores: 11620 scores 182 over 2053, every row an operand, with this object compiled so, and the 15
# of this unit's matches scored, all but the statics' exit destructors, score the same both ways, pnpm wasm score in the
# link of each). cgravadorhashes.cpp, unit 136's file, is compiled in this list right after cpath.cpp: the target's data
# put cpath.cpp's records (@1552104) ahead of cgravadorhashes.cpp's (@1554632), and with the object there 11620's locals
# are the target's, where at the end of unit 136's list (after centidadehashes.cpp.o) they differ (unit 136's fragment).
# The place keeps cgravadorhashes.cpp.o ahead of cmontadorhash.cpp.o, which the range insert 5854 needs (unit 227's).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CPATH_SRCS := src/app/comum/cpath.cpp src/app/comum/gravadores/cgravadorhashes.cpp
UENUX2_SRCS += $(CPATH_SRCS)
# the unit's target callers are not reconstructed: 190-uenux2-cpath-roots.cpp stands in for them
$(ROOT)/$(APP)/190-uenux2-cpath-roots.o: $(ROOT)/src/units/190-uenux2-cpath-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/190-uenux2-cpath.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/190-uenux2-cpath-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/190-uenux2-cpath-roots.o
