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
# Written and not matched, each with its measurement:
# - GetPathTrab and GetPathResult with the turn (358, 1399): operand rows only (`pnpm wasm score`: 37 over 393, 30 over
#   323), and the scan stops at the turn's format handle: `differs ... target i32.const 474 | ours i32.const 966`. Slot
#   474 is fn 9868, EUrnaTurno's handle, which the target keeps apart from the 31 slots of 536; our link merges it into
#   536's body. It is unit 109's case for CAppInfo::IndiceTurno (1553): the two wait for that copy of the handle.
# - path::operator/=(const path&) (183) is named by the anchors' calls (`call by:358,634,1399`), and its body differs,
#   87 over 105 rows: ours is cpath.cpp's copy at the tree's -O3, which inlines has_root_directory, operator= and
#   has_filename. A compile of operator/= at the executable TU's -Oz -fexceptions keeps has_root_directory, operator=,
#   has_filename, push_back and append(const string&) as calls, in that order, which are 183's callees 5549, 1700, 3679,
#   409 and 3717. With that object (a function returning `a /= b`) first on the link line, as
#   docs/reference/facts/levels.md V4 does, its copy is the link's and reads 31 over 52 rows: binaryen inlines
#   has_root_directory and has_filename, which have one caller there, where the target's 5549 has 183 and 7749 and 3679
#   has 183, 7738 and 7742, three functions only the table holds (slots 8848, 8871, 8866). So 183, 3679 and 5549 are
#   read as the executable TU's copies and wait for its code that calls them.
# - path::__filename (1224) is libc++.a's: 180 over 252 rows. Our link has no body of 2134 (PathParser::decrement, which
#   calls consumeName and consumeAllSeparators; build/out/wasm-map/vota_web/names.tsv names none), read as binaryen
#   inlining it into __filename, its one caller here. 2134's other target callers, 1840 and 5360, have no body of ours.
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
# - GetPathLog is inline in cpath.h and the array is declared there with no bound. 5899 loads 1838576 with `i64.load
#   align=2`, where the static initializer and the code 8302 and 12098 hold behind a second prologue (read as functions
#   of this file binaryen inlined there) use align=3. Measured on probes at the tree's flags: a TU that declares the
#   array as path[2] loads it with align=3, one that declares it with no bound with align=2, and every function of the
#   TU that defines it gets align=3, defined before the definition or after. 5899 lies in band 2 after
#   cpacotearquivos.cpp's 5900 and 5901 and before iinterfaceinit.cpp's 5897, where a copy deferred to the end of
#   cpacotearquivos.cpp's object would be: a reading. Our copy comes from the roots object, compiled at UENUX2_CXXFLAGS.
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
#   slot 71, which fns 5968 (read as an -fexceptions copy of operator/) and 5821 pass to invoke_iii. Without the roots'
#   address of it, binaryen drops the result, and 358, 1399, 634, 2864, 6047 and 5899 each lost a row per call (`deleted
#   2`, `1`, `2`, `1`, `1`, `1`).
# - The scores with the forms above: 634 42 over 484, 436 and 1274 3 over 8, 2864 8 over 83, 3834 6 over 23, 762 and
#   1082 3 over 7, 6047 5 over 66, 949 and 1948 3 over 6, 6048 12 over 153, 5899 11 over 61, all operand rows.
#
# Chosen, no evidence names them: every member's name but the three records', the statics' names, EFlashOrigem's
# enumerators, its comum:: scope and its header's path, the EUeComumError enumerators' names, the lines of every member
# but the three throws, the order of the members, GetPathWsq's class and file (2864 calls 358 and appends "wsq/"; its
# band fits cpath.cpp, above), and `static_cast<int>` for the origin's format argument.
#
# Not written: 3896, the merge body of CServicoEstadoGeralSA's, Gap's and Vota's GetPathArquivo (11565, 11567, 11568),
# which are those classes' slots, not CPath's; 6035 and 6036, the merge bodies of 1701, 5762, 1551 and 2826, which build
# a string from GetPathTrab(EFlashOrigem) and "rdv.dat" or "uenux.db" and call 436: a probe function of cpath.cpp that
# does the same holds 436 inlined (calls of GetInst, GetGeral and 358), so they are read as another file's; 1487 and
# 1488, the "dinamico/imprimindo" marker, which call fn 620, not written; 5907, which destroys three members of the
# object at 1838544 and builds no path. The code 8302 and 12098 hold behind a second prologue and that reads this file's
# statics (a setter of the root and the two flash paths in 8302; GetPathLog's body with "arquivados/" in 12098) waits
# for those callers.
#
# Roots (190-uenux2-cpath-roots.cpp): no target caller of the unit is in the link, so it gives the members the call
# sites its header lists (two each, one for 1399 beside 1274, none for 358), emits GetPathLog's copy and takes
# operator/='s address. It compiles at UENUX2_CXXFLAGS, app/comum's flags, since it emits GetPathLog, code of a tree
# header.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CPATH_SRCS := src/app/comum/cpath.cpp
UENUX2_SRCS += $(CPATH_SRCS)
# the unit's target callers are not reconstructed: 190-uenux2-cpath-roots.cpp stands in for them
$(ROOT)/$(APP)/190-uenux2-cpath-roots.o: $(ROOT)/src/units/190-uenux2-cpath-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/190-uenux2-cpath.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/190-uenux2-cpath-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/190-uenux2-cpath-roots.o
