# src/ — the reproduction project

```
TMPDIR=/tmp make -C src libs     # the upstream libraries, through tools/libs/*/build.sh
TMPDIR=/tmp make -C src link     # the app objects, the plain link and its --emit-symbol-map twin
TMPDIR=/tmp make -C src census   # census of the plain link → ledger/functions.tsv
TMPDIR=/tmp make -C src splat    # the official check: the target's sha256 and the meter (docs/reference/splat.md)
make -C src status               # README.md's headline, docs/status.md's progress blocks and docs/img/progress-*.svg, from splat/scan.tsv
make -C src stubs                # the stub of every TSE function not decompiled yet, and the gaps (below); stubs-check checks them
TMPDIR=/tmp make -C src check-srcloc   # the source_location records of the app objects against the target's
make -C src print-APP_CXXFLAGS   # any Makefile variable, for scripts (print-APP_INCLUDES, print-LINK_OBJS, …)
```

Outputs: `build/out/wasm/vota_web/vota_web_wasm.{js,wasm,data}` (byte-comparable with `target/`), its `link.cmd`
(the exact link command) and `symbols.{mangled,demangled}.txt` (every symbol of the link's inputs, for the lifter),
and `build/out/wasm-named/vota_web/` (names only: `--emit-symbol-map` changes the -Oz function order, so never
byte-compare it).

| path | what |
| --- | --- |
| `Makefile` | the link order (`LINK_OBJS`), the compile flags per tree, the library targets, the link |
| `mk/` | the build machinery the unit fragments rely on: `ecourna-flags.mk`, `asn1.mk` (the ASN.1 runtime and modules), `splat-*.mk` (the splat build) |
| `units/` | one fragment per landed unit, `<NN>-<component>-<what>.mk`, with its roots, pending and externs files (`units/README.md`) |
| `ecourna/`, `uenux2/`, `asn1/` | the reconstructed TUs: ecourna mirrors the conan package's `b/src/ecourna`, uenux2 mirrors `/home/rubio/tse/uenux2` (`src/…`, `wasm/…`), asn1 the III ASN.1 fork. TSE's sources are Latin-1 (`.editorconfig`) |
| `app/vota_init.cpp`, `vota_api.cpp`, `main.cpp` | the exported functions not decompiled yet as hand-written stand-ins (the glossary's second meaning of *stub*), signatures from the target export types; TU order = export order |
| `app/roots.cpp` | one function the stubs call that reaches every library entry point once (keeps the app's reachable set without exporting) |
| `app/roots_ecourna.cpp`, `app/roots_uenux2.cpp` | callers of the reconstructed ecourna / uenux2 units with the target's call-site counts (binaryen inlines a function it sees called once); they link first, so what they instantiate is the copy the link keeps (`units/README.md` "Companion files") |
| `app/roots_{7zip,rhvoice,boost}.cpp`, `stubs_7zip.cpp` | the library probes' drivers compiled as app code; definitions 7-Zip needs that emscripten lacks |
| `web/wasm_shim.cpp` | the 34 EM_JS functions (generated: `../tools/extract/gen_wasm_shim.py` from `web/library_vota.pretty.js` + the target import types). A reconstructed TSE source that calls one declares it `extern "C"` with this file's signature and never defines it again: the glue lists them in the order of this file's `em_js` sections (`uenux2/mock/app/simulador/wasm/cwasmbeep.cpp` declares three) |

The scripts the build calls are in `../tools/round/` (`census.sh`, `census_report.py`, `link-map.sh`,
`link-kinds.sh`, `link-symbols.sh`, `status.py`) and `../tools/libs/`; `../tools/README.md` describes each.

## Stubs: the TSE functions not decompiled yet

Every unmatched TSE function that `tools/round/stubs.py` finds no code of ours for has a stub in `ecourna/`,
`uenux2/` or `asn1/`: two comment lines generated where the evidence says the function sat, between `// <stubs>`
and `// </stubs>` markers. Code of ours, to the generator, is a body in our link that is the function, a record that
falls on a line of our code or names a function our file defines, a slot of a vtable our link holds, or a virtual
member of a class our sources define (`stubs.py --report` counts each reason; `units/README.md` "Pending members" has
the limits of the last one). A body is the function when the symbol file names the function by it. A
body the census only paired with the function (`splat/scan.tsv` source `ledger`) is the function only when its
symbol names the class and member of one of the function's records or symbol-file names, or the class of a vtable
that holds the function or of a vptr it stores; a sibling class's destructor one vptr apart, or a library body of
like shape, leaves the stub (`--report` counts these pairs too). A record names a function our file defines when a
definition there has the record's qualified name and parameter types, so a defined overload does not hide an
unwritten one, nor a destructor its constructor. So a pending member's trapping body (`units/README.md`) removes its
stub. A non-virtual function we wrote that has no record, a constructor for one, keeps its stub. A function whose
records all fall on lines of our code counts as written even when it is a caller that inlined the code on those lines:
writing `ctextsource.h`'s inline constructor on its record's line (37:19) removed the stubs of 1150 and 652, whose only
record that is. Name such functions in the fragment's header, as for a stub-only file that goes (below).

```
// <stubs>
// f1455 · 496 B · unmatched · name unknown
// void f1455(i32, i32) { ... }
// </stubs>
```

The first line gives the target function index, its body size and its status, then `placement: link order` when no
`std::source_location` record gives the function a line (its place in the file comes from the recovered link order, or
it follows the file's code), and `name unknown` when `splat/symbol_addrs.txt` names no function at that index. The
second is its signature: the demangled name, or `f<index>` and the wasm parameter types; the return type is `?` unless
the wasm signature settles it (`void`). For `f<index>` the types are the target's, after binaryen, so they are not the
C++ declaration. `void` says only that the wasm function returns nothing: a C++ function that returns a class by value
does that too, through a hidden first parameter that holds the result's address, unless the class is trivially
copyable and holds one scalar, which comes back as that scalar (3641, `CTime CTime::operator-(int) const`, is `(i32
i32)->(i32)`); and a constructor or a non-deleting destructor returns `this` until binaryen drops a result no caller
uses (5526, the `api::CMovie` constructor, is `(i32 i32 i32)->()`). A parameter every caller passed as one constant is
folded into the body, so the wasm type can have fewer parameters than the C++ function (`docs/how-to-decompile.md`
step 2). The file comes from the function's records, else from its class's vtable or vptr (`ledger/vtables.json`,
`ledger/func-attribution.tsv`): its records' file when a record names the class, else the one file that defines the
class's members, else `<class>.cpp` in lower case once such a file exists. So a unit that creates `cwasmscreen.cpp`
takes `CWasmScreen`'s stubs out of `unplaced.cpp` at step 9, whatever the file holds. A function with neither is in
its tree's `unplaced.cpp`, grouped by link-order cluster. That tree is the scan's `group` column's (`tree_of` in
`tools/round/stubs.py`), a guess like the group. 5449, `api::IsValidTime`, is in group `ecourna` because it calls
ecourna's `CStringUtils::ToByte`, so its stub was in `ecourna/unplaced.cpp`, and it matches from a uenux2 object (`awk
-F'\t' '$1==5449 {print $9, $11}' splat/scan.tsv` prints `ecourna app/uenux2/src/api/util/ctime.cpp.o`). For the same
reason a stub can sit over a body of a library `third_party/MANIFEST.md` pins, which a TSE function calls: the census's
`owner` column names the library
(`awk -F'\t' '$1==6281 || $1==4936 || $1==2199 {print $1, $4, $5}' ledger/functions.tsv` prints `2199 boost ecourna`,
`4936 7zip ecourna` and `6281 libcxx ecourna`; 6281 is libc's `chown`), or the body calls one whose owner does (2134 calls libc++'s path parser, 2546). Such a row is the library's
code and lands with its caller, never as TSE source. Decide a function's tree from its callers' records and its landing
pads (an `invoke_*` around a throwing call is ecourna's or ASN.1's flags, none is uenux2's:
`docs/reference/facts/app-flags.md` §F6). The comment over a cluster (`// link-order cluster 984 · uses=3 · neighbours'
file uenux2/src/api/gui/ctextfielddoubleline.cpp`) is its stretch's `probable_file` in `ledger/tu-clusters.tsv`: the
file of a record one of the stretch's functions loads, or of a vtable class's records (`label_kinds` `source_location`,
`class-record`), else a guess from a class name (`class-convention`). A stretch also holds unlabelled functions of other
classes: f3660, `api::CSubReport`'s constructor, sits under 3659's record in cluster 984, and a stretch can hold
functions of another digit zone ([../docs/reference/link-order.md](../docs/reference/link-order.md) §7.5). So the
comment is a hint, not the file; `docs/how-to-decompile.md` step 3 gives the file. A file the evidence names that does
not exist yet holds its stubs only, and goes when its last stub goes, even when records name it: they can be an inlined
callee's. Whoever removes that last stub, by a match or a pending member, names the file and its record lines in the
fragment's or the `-pending.cpp`'s header (`units/README.md` "Pending members"), so that whoever writes the functions of
those records finds it. The deletion is left unstaged: `git rm` it before `python3 -I -B tools/round/check_encoding.py`,
which reads the index and stops with `FileNotFoundError` on a tracked file that is gone. The stub files and
`unplaced.cpp` are never compiled: no fragment lists them, and the generator never creates a `.cxx` in `asn1/`, where
`mk/asn1.mk` compiles every one. A stub is a comment, never the target's code: there is no `INCLUDE_ASM`, and an
unmatched function's bytes come from its piece in the splat build
([../docs/reference/include-asm.md](../docs/reference/include-asm.md)).

Stubs only take blank lines (the ones that keep a decompiled function's throw sites at their recorded lines) or go
after the end of a file, so no object changes. They take the blank lines of a record only at namespace level: a record
line inside a class body (a template member defined in its class) keeps its gap, and the stub goes after the end of
the file, marked `placement: link order` though a record names the function (f316 and f270 in
`uenux2/src/api/ipc/cmessagequeue.h`, records 113 and 114). Where a run of blank lines is too short for the stubs its
records put there, a `#line N` after them gives the next line its number back, the same directive a gap ends with
(below). The markers say the runs are generated: `make -C src stubs` rewrites them (`splat-scan` and `splat-match` run
it), and `make -C src stubs-check` (CI) fails on a stub that is missing, extra, stale or out of place. To edit a file
that holds stubs or gaps, `python3 -I -B tools/round/stubs.py --strip <file>` turns them back into blank lines first;
[../docs/how-to-decompile.md](../docs/how-to-decompile.md) step 3 has the rest.

## Gaps: the original lines not recovered

A decompiled function's throw sites must stay on the lines their `std::source_location` records give, so the lines of
TSE's file we have not written (comments, includes, other formatting, inlined helpers) keep their place. The same
generator, `tools/round/stubs.py`, writes each such run as a gap: one blank line, a comment naming the original lines
the run stands for, and a `#line` that gives the next line its original number:

```cpp
namespace ecourna::app::dados {

// (original lines 9-16: content not recovered)
#line 17
CNumeroCPF::CNumeroCPF(const std::string& numeroCPF) : IIdentificadorEleitor(TTipoIdentificadorEleitor(TipoIDCPF), numeroCPF, 11)
```

Write nothing of your own into those lines: they stay blank, and step 9 makes a run of three or more a gap, the
project's statement that the content is not recovered. The lines a record names for a function no file of ours
writes (a constructor its only caller inlined, a pending member) stay blank too, and the members you write go after
them, or before them when evidence says so: their lines are then a choice, which the file's header comment or the
fragment's header says. Such a run gets no gap when
no record line lies below it: lines 4-77 of `uenux2/src/api/gui/cprogressbar.cpp` hold the records 52, 58 and 67 of
the constructor that `std::make_shared`'s 5545 inlined, and stay 74 blank lines. When the records' function has a
stub, step 9 writes the stub over its record's line: `uenux2/src/api/gui/cstepsprogressbar.cpp` holds a gap for
lines 18-424, then f13550's stub on lines 425-428 (its record is 428:15), then the unit's members. A comment there
reads as TSE's, and no evidence gives it.
What a reader needs to know about the reconstruction (which target functions the file holds, which names and paths
are chosen) goes in the file's header comment. Above a record line (a header whose inline member a record names), every
line added there moves the records below it: keep the line count above the first record, folding the note into the
lines already there, and run `TMPDIR=/tmp make -C src check-srcloc` after the link. Files landed before this rule still
hold doc comments of their own above a function
(`LC_ALL=C git grep -l '^ */\*\*' -- 'src/uenux2/*.cpp' 'src/ecourna/*.cpp'` lists them); they are not the form to copy.

The comment is ASCII (a `-` between the numbers: Latin-1 has no dash), indented like the line under it, and sits on
the first line it names; the `#line` names the line after the last. A `#line` without a file name keeps the file
name, so every object compiles byte-identical, and the compiler numbers the lines as TSE's file did: an error or a
warning below a gap names the original line, which can be larger than the line number an editor shows.

Which runs are gaps: 3 or more empty lines of code (outside comments, directive continuations and preprocessor
conditionals) with a line before and after them, and below them a line that a record of the file names
(`ledger/source-locations.tsv`). Runs of 1 or 2 lines are formatting and stay blank. The threshold comes from the
sources: of the 146 runs of 2 blank lines, 119 have no record below them, while 124 of the 126 runs of 3 or more hold
a record's line in place. The other two hold none and stay blank: 3 lines in `asn1/asn1_useful.cxx`, asnparser's
own spacing, and 8 in `ecourna/app/dados/asn/midias/cconversorinformacaomidia.cpp`, above code no record names. The
124 gaps are in 61 files, 26 of them inside a function or class body.

`make -C src stubs` writes the gaps after the stubs (a stub in a long run leaves a gap above and below it), and
`make -C src stubs-check` fails on a run of 3 or more blank lines left blank, a gap comment where the generator writes
none, a range that does not end at its `#line`, a comment or a `#line` without the other, and a comment that no
longer sits on the first line it names. That last one means lines were added or removed above it: the `#line` holds
the code below where it was, and `make -C src stubs` writes the comment again over the lines that are left, which is
what a recovered function written into a gap needs. To move the code below instead, `--strip` the file first and edit
the blank lines. Code added between a `#line` and the line under it moves that code; `TMPDIR=/tmp make -C src
check-srcloc` lists every record that moved, after a link.

## Trying a candidate: tools/round/try-tu.sh

```
tools/round/try-tu.sh --print-flags cand.cpp|dir                                  # each TU's compile command, nothing run
TMPDIR=/tmp tools/round/try-tu.sh --single <target fn> --extract export:<mangled> cand.cpp   # one function, linked alone
TMPDIR=/tmp tools/round/try-tu.sh --symbols cand.cpp                                       # the mangled symbols it defines
TMPDIR=/tmp tools/round/try-tu.sh cand.cpp|dir [--flags '…'] [--targets idx.txt] [--roots mine.cpp|none]  # the whole link
```

[../docs/how-to-decompile.md](../docs/how-to-decompile.md) uses both modes in the decompile loop. try-tu runs the
toolkit (`pnpm exec tsx`, from `asmlift-wasm/`) for `--single` and the whole link's census, so it needs Node 24 first on
`PATH`, as `tools/round/census.sh` (`make -C src census`) and the `splat*` make targets do. With another Node
first it stops after the `flags:` line with only the shell's `tools/round/try-tu.sh: line 47: <pid> Abort trap: 6
pnpm exec tsx src/cli.ts "$@"`, exit status 134. What try-tu does:

- **Flags.** Each candidate TU compiles with the flags the Makefile builds that source with (plus `--flags`): try-tu
  asks `make -n` for the recipe of the object the source would become, so a TU gets its tree's rule
  (`ECOURNA_CXXFLAGS` with `mk/ecourna-flags.mk`'s additions, `UENUX2_CXXFLAGS`, the
  ASN.1 runtime's and modules' rules from `mk/asn1.mk`) or, for a landed unit, its fragment's own rule. The path under
  `src/` names the component; a TU outside `src/` needs `--component <dir under src/>` (`ecourna/app/dados`,
  `uenux2`, `asn1`, …), the directory it would land in.
- **`--single`** compiles the TU alone, keeps one exported function through the toolkit's rank adapter, and scores it
  against the target. A lone link makes other inlining and dead-argument decisions than the whole program, and even a
  function with no callee can come out otherwise alone (a compare the whole link shares between two `select`s stays
  computed twice: a source that matches 11067 scores 9 alone,
  [../docs/reference/facts/tool-traps.md](../docs/reference/facts/tool-traps.md) §X9). So use it to iterate on a body
  and the whole link to conclude. Several TUs are rival candidates, ranked against each other, never linked together:
  a callee in another TU stays an import. Undefined functions become imports, but undefined data fails the link;
  `--flags '-Wl,--unresolved-symbols=ignore-all'` lets it through (`docs/how-to-decompile.md` step 4). The score
  counts what the lone link inlines into the function: for a throw that builds its message with `std::format`, all of
  libc++'s formatting code, so target 5468 (`api::CGenericTags::TagSize`, unit 33) scores `10836 over 10850 rows (…
  inserted 10622 …)` alone and is matched in the whole link. How-to step 4 says when to skip to the whole link. The
  compile and the lone link are one `em++` line, `-Oz -fexceptions` and then the TU's own flags, and emcc takes the
  last `-O`: binaryen runs at the TU's level (`-O3` for uenux2), not at the build link's `-Oz`
  ([../docs/reference/facts/tool-traps.md](../docs/reference/facts/tool-traps.md) §X6). `--single` compiles every TU
  as a copy named `cand.cpp` in a directory of its own, tracked TUs included, so a TU that includes a header beside it
  by a bare quoted name (`#include "cwasmtimer.h"` in `uenux2/mock/app/simulador/wasm/`) fails with `file not found`
  until `--flags "-iquote /work/<its directory>"` names that directory. try-tu rewrites the tree's relative `-I` paths
  for the container, not the paths in `--flags`: write those as `/work/<path>` (`-I/work/third_party/boost`, not
  `-Ithird_party/boost`).
- **`--component`** overrides the path of every TU of the run, not only the ones outside `src/`. It is also the
  way to compile a `src/units/*-pending.cpp`, which has no rule of its own that try-tu can find. A TU that is not at
  the path it would land in is compiled as a copy there, under `build/out/try/<name>/src/`, so a quoted `#include`
  of a file beside the original is not found, and `-Isrc/uenux2/src` (or the tree's other `-I`) finds the tracked
  header of that name instead. To try a variant of a tracked header, put it under a scratch directory at its path in
  the tree and pass `--flags "-iquote /work/<dir>"`: try-tu appends `--flags` after the tree's `-I` paths, so
  `-I/work/<dir>` silently compiles the tracked header, while a `-iquote` directory comes before every `-I` one for
  the tree's quoted includes, at any depth ([../docs/reference/facts/tool-traps.md](../docs/reference/facts/tool-traps.md)
  §X8). Check the object for the variant's symbols afterwards.
- **`--symbols`** compiles the TU and prints the function symbols it defines, mangled and demangled: `llvm-nm`'s `T`
  and `W` lines, so weak data shows too (an inline base's typeinfo) and strong data does not. A class's own vtable and
  typeinfo, which the TU that defines its key function emits, are strong data: to see whether a TU emits them, read
  its object, `TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only
  build/out/app/uenux2/src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp.o | /usr/bin/grep -v ' [TWt] '`, which
  prints the `D` lines of `_ZTIN5comum3asn14CVisitanteFotoE`, `_ZTSN5comum3asn14CVisitanteFotoE` and
  `_ZTVN5comum3asn14CVisitanteFotoE`.
- **The whole link** generates a roots TU (`gen_try_roots.py`: every strong function symbol of the objects is
  address-taken from a static constructor, because nothing in the skeleton calls a candidate and wasm-ld drops what
  nothing references; `--keep-weak` roots the inline and template instantiations too, `--roots your.cpp` supplies
  real callers instead, `none` skips it), then links the whole skeleton with the TUs through
  `make link EXTRA_OBJS=… OUT=build/out/try/<name>/wasm/… OUT_NAMED=…` (the libraries prebuilt, nothing of theirs
  rebuilt; the skeleton's own objects are the shared `build/out/app/` ones, so a stale one is recompiled there, and
  afterwards `make -n -C src link` has nothing left to count for it), runs the census against the target, and writes
  `build/out/try/<name>/report.md`: the census tiers per owner and per component against `ledger/functions.tsv`, the
  functions that moved, and for each target function
  in `--targets` (default: every target function whose best pair in the try link is one of the TU's own symbols) its tier
  before and after, the skeleton function it pairs with and the first differing rows. `unmatched-symbols.txt` lists
  the TU functions that reached the link and paired with no target function. try-tu never writes `ledger/`.
  A census tier of `none` does not mean the body differs. `tools/round/link-map.sh build/out/try/<name>/wasm/vota_web`
  maps the try link the way `make -C src link-map` maps the plain one, `tools/round/link-kinds.sh` with the toolkit's
  `splat-kinds` gives it an operand-kind table the way `make -C src link-kinds` does, and `pnpm wasm splat-remap` then
  compares one function of it with the target (`docs/how-to-decompile.md` step 5). `--name` (default: the first TU's
  base name) is joined to `build/out/try/` as given: `--name ../verify/x` puts the try in `build/out/verify/x/`, and
  then `link-map.sh` and `link-kinds.sh` take its path as try-tu prints it, `build/out/try/../verify/x/wasm/vota_web`
  (the normalised path fails with `link.cmd does not write …`,
  [../docs/reference/facts/tool-traps.md](../docs/reference/facts/tool-traps.md) §X10).

`--skip-units <fragment>.mk` leaves a landed fragment out of the link, with its companion objects, so its TUs can be
tried again without a duplicate symbol. It takes the file name as `src/units/` lists it (`13-uenux2-crdvvota.mk`), not a
path: `src/Makefile` filters the fragments by `$(ROOT)/src/units/<name>`, so a path matches none, is dropped without a
word, and the link stops on `duplicate symbol`. To measure a variant of one source of a landed unit, copy every source
the fragment lists, its `-externs.cpp` included, into one scratch directory, change the copy, and pass that directory
with `--skip-units <fragment>.mk --component <the sources' directory under src/> --roots <the unit's -roots.cpp>`.
`--component` gives the copies their tree's flags and path map, and the externs file, which has no rule of its own once
the fragment is skipped, the flags it has in the fragment. Run the unchanged copy first: it must reproduce the committed
result.

Times: `--single` takes about 7 s on an idle machine and the whole link about a minute (compile, both links,
census). Both are mostly docker runs, so they grow with the machine's load: `--single` takes about 35 s while a fresh
clone's setup runs and ten minutes at a load average above 100, and two whole links running at once take about seven
minutes each.
