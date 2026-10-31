# Facts: traps of probe links and of the shell

Commands and links that give a plausible wrong answer, collected where more than one topic hits them. Topic-specific
traps stay with their topic: [toolchain.md §T7](toolchain.md) (comparing bodies), [link-order.md §L7](link-order.md),
[app-flags.md §F9](app-flags.md), [asn1.md §A4](asn1.md), [splat.md §S3–S4](splat.md).

## X1. binaryen never inlines an exported function, so exporting library code to keep it alive changes its bodies

binaryen's Inlining pass inlines a function of **any** size when it has exactly one call site and is not used
globally (exported, or in the table). With `-sEXPORTED_FUNCTIONS` covering a library's symbols that rule never
fires. Measured: target func 444 (`BN_div`) is 866 rows = `BN_div` with its only callee `bn_div_fixed_top` inlined;
in a probe that exports `bn_div_fixed_top`, `BN_div` stays 65 rows at every -O level (817/866 rows differ). Target
981 is `BN_mod_exp` with `BN_mod_exp_mont_word` and `BN_mod_exp_recp` inlined (their ERR strings share the
function); they are separate functions in an exporting probe.

So a byte-for-byte reproduction needs the app's real root set: each function the app calls, called for real, so
that internal one-caller functions keep one caller. Not `-sEXPORTED_FUNCTIONS=<everything>`, not
`-Wl,--export-all`, not a table of function pointers (table slots are "used globally" too). Functions matched by
fingerprint only need their own body and callees to agree, so census counts under an exporting probe are a lower
bound. The same holds for the app's own roots TUs (`src/app/roots.cpp`, `src/units/*-roots.cpp`): an uncalled
root keeps the target's bodies, a called one behaves as in the app.

The rule counts call sites in the whole link, so a match that rests on it holds only while the count does. A member
defined in its class that clang leaves out of line, and binaryen inlines into its one caller, stays out of line in
both callers once a second one links ([codegen.md §C3](codegen.md)). When the target holds the same inlined code in
two functions, clang inlined it in at least one TU (an `inline`-specified definition is inlined in each), and a form
that only binaryen inlines matches until the other caller is written: link with both before choosing.

## X2. Probe links

1. `em++ … -o probe.wasm` (no `.js`) silently selects `STANDALONE_WASM`: an `_initialize` export, WASI-flavoured
   libc paths, and a passed `-sEXPORT_ALL` is dropped. Link to `-o probe.js` like the target and read the
   `probe.wasm` next to it.
2. `-sEXPORT_ALL=1` does not keep library functions alive (11 function exports with and without it). The
   1,230–1,850 functions that survive a **bare link** of a C++ library are those reachable from vtables (the elem
   table), so a bare probe covers only virtual-reachable code (RHVoice: 101 functions). Give the probe a driver
   whose `EMSCRIPTEN_KEEPALIVE` functions call the app's entry points into the library; that also keeps one-caller
   inlining behaving as in the app (X1).
3. `score`'s `byteExact` can be true while the score is > 0: rows symbolise `i32.const` data addresses as
   `data:<segment hash>+rel`, and segment hashes differ between modules even when the function bytes are identical.
   `byteExact` is the stronger statement.
4. A SourceForge 7-Zip `.7z` source has CRLF line endings: diff it against the LF git mirror with
   `--strip-trailing-cr`, or every file "changes".

## X3. zsh, the default shell here

1. zsh does not word-split an unquoted `$var`: `set -- $var`, `$C arg` or `em++ $FLAGS` pass one argument (errors
   like `invalid integral value '2 -fPIC …'` or `no such file or directory: pnpm --filter …`). Use an array
   (`F=(-O2 -fPIC); em++ $F`) or `${=var}`.
2. Building a list as a string (`A="$A x=y"`) and passing `$A` gives an argument with a leading space
   (`ENOENT ' /…/probe.wasm'`): use `A=(); A+=("x=y"); "${A[@]}"`.
3. A word starting with `=` is `=cmd` expansion: `echo ====` fails with `=== not found`. Quote it.
4. In `until for h in …; do grep -q … || exit 1; done; do sleep 5; done` the `exit` leaves the whole script at
   the first miss; it is not a loop break.
5. A `:` after a parameter is a history modifier: `git show $E:src/…` takes `:s` and prints `fatal: ambiguous argument`
   over a path that names no file. Brace it: `git show "${E}:src/…"`.
6. A `#!/bin/zsh` script can lose an exported Node 24 `PATH`, and then each `pnpm` exits 134 in under a second with an
   empty log: set `PATH` on the script's first line, and read a loop's exit statuses.
7. `LC_ALL=C grep …` can print nothing where `/usr/bin/grep …` prints matches. A bare `grep`'s silence is no evidence.

## X4. Fetching from the TSE site

A plain `curl` to `https://www.justicaeleitoral.jus.br/simulador-votacao/…` returns HTTP 403 "Access Denied" (an
Akamai edge rule) for every path, including ones that exist. A 403 there does not mean the file is absent. The
target files were fetched through a browser.

## X5. Callers of `std::to_string` pair at `none` at depth 2, and the readout reads error codes as strings

1. A function that calls `std::to_string(int)` or `std::to_string(unsigned)` (targets 296 and 327, 128 callers
   between them) pairs at tier `none` at depth 2 in the skeleton however exact its own body is. `to_string` calls
   `string::__init<const char*>` (target 1544, 16 B), which in the target wraps an out-of-line
   `__init_with_size` (5607, called by 1544 and 679). While 679's owner is not built, the skeleton has one caller
   and wasm-opt inlines it, so the depth-2 fingerprints differ. `to_string` itself is identical at depth 0
   (`pnpm wasm score <target> 327 <a named link> <to_string(unsigned)> --depth 0` gives 0 differing rows of 27). Shown
   on 1931 (`CRdvVota::Candidato`) in a whole link: depth 0 `addr` with 3 differing data addresses, depth 1 `shape`
   with 8 operand-only rows, depth 2 `none`. This is why the symbol file names `to_string(unsigned)` by its depth-0
   pair (`evidence:pair-depth0`).
2. `fn`'s "strings referenced" reads an error-code immediate in the data range as a string pointer: 1931 shows
   `4725 (+13 into 4712) "Tipo de identificador inválido: {}"`, but 4725 is an `EUeRdvError` code (the second
   argument of the `CBaseError` constructor, through 3707), and its siblings 3749, 2814, 2813 and 5732 list 4726 to
   4729 the same way. The `addr` tier does not see it either: the row is `i32.const data:<seg>+3701` on both sides.

## X6. `try-tu.sh --single` and exceptions

The rank template of `--single` compiles and links in one `em++ -Oz -fexceptions …` (the build's link has
`-fexceptions` too). A uenux2 TU is compiled without it (app-flags.md §F6), so `--single` adds `-fignore-exceptions`
to a TU whose own flags lack `-fexceptions`. Without it a uenux2 TU scored alone grows landing pads. With the
reconstructed `api::CDirReader::NextEntry`:

```sh
TMPDIR=/tmp tools/round/try-tu.sh --single 1260 --extract export:_ZN3api10CDirReader9NextEntryEv \
  src/uenux2/src/api/util/cdirreader.cpp
# flags: -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing … -I/work/src/asn1  -fignore-exceptions
# score 224 over 250 rows (same 26, replaced 13 [6 operand-only], inserted 211, deleted 0)
```

No `invoke_*` row is left (without `-fignore-exceptions` the same TU scores 162 over 184 rows, with `invoke_iii`,
`invoke_iiiii`, `invoke_viii` and `__resumeException` calls). The rest of the difference is what binaryen inlines
into a body linked alone; the splat build matches this source.

The same line also sets the lone link's level, and not to the build link's `-Oz` ([workflow.md](workflow.md) §W2
item 5 has what that changes in a body). The TU's flags come after the
template's `-Oz -fexceptions`, and emcc takes the last `-O` for the compile and the link alike, so binaryen runs at the
TU's level, `-O2` for uenux2 and `-O3` for ecourna:

```sh
P=build/out/try-facts/olevel; mkdir -p $P; printf 'extern "C" int f(int x) { return x * 3; }\n' > $P/a.cpp
for l in -Oz -O2 -O3; do TMPDIR=/tmp build/docker-build.sh em++ -Oz $l /work/$P/a.cpp -o /work/$P/a.js --no-entry -sEXPORTED_FUNCTIONS=_f -v 2>&1 | /usr/bin/grep -oE 'wasm-opt --strip-target-features --post-emscripten -O[0-9sz]'; done
# wasm-opt --strip-target-features --post-emscripten -Oz
# wasm-opt --strip-target-features --post-emscripten -O2
# wasm-opt --strip-target-features --post-emscripten -O3
```

binaryen at `-O2` numbers locals and merges branches otherwise than at `-Oz`: a lone body can differ in its locals or
keep two `br_if` where the whole link has one `i32.or`, from a source that matches. To see the build's body alone,
compile with `-c` and the TU's flags, then link the object in a second `em++ -Oz -fexceptions` (the template's other
options, with `-sEXPORTED_FUNCTIONS=_<symbol>`).

## X7. A TSE file name the path map does not rewrite

`-ffile-prefix-map` rewrites a path as clang spells it. A source compiled from a relative `src/uenux2/…` path, or a
header found through `-Isrc` (`src/ecourna/api/asn/iconversorasn.hpp`), is spelled relatively, so a map of
`/work/src/…` alone leaves `__FILE__` and the `std::source_location` records at `src/…` instead of the target's
`/home/rubio/tse/uenux2/…` or conan path. Compiled from relative paths with only `/work/src/…` mapped, three
objects of unit 01 (`cinikey`, `cposixmutex`, `cposixsemaphore`) hold 10 such records, and eleven ecourna objects
35 more from those two headers. So every uenux2 and ecourna compile runs from `/work/src/…`, `UENUX2_PREFIX_MAP` and
`ECOURNA_PREFIX_MAP` map both spellings, and `check-srcloc` fails with `UNMAPPED` on a record named `src/…`:

```sh
TMPDIR=/tmp tools/round/try-tu.sh --print-flags src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp
# … -ffile-prefix-map=/work/src/uenux2=/home/rubio/tse/uenux2 -ffile-prefix-map=src/uenux2=/home/rubio/tse/uenux2
#   -Isrc -Isrc/uenux2/src -Isrc/asn1  -c /work/src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp
TMPDIR=/tmp make -C src check-srcloc
# at 9271d74: 294 source_location records in 217 objects (78 files): 273 are records of the target;
#   0 that matched functions load are not; 21 that only unmatched functions load are not; 0 name an unmapped file
```

The 21 records that only unmatched functions load are wrong in code nobody has fixed yet, and the check passes with
them. A range adds to them only through an object it rebuilds, so compare the list per object with the base's:

```sh
TMPDIR=/tmp make -C src check-srcloc 2>&1 | /usr/bin/grep '^unmatched' | awk '{print $2}' | sort | uniq -c
# at 9271d74:
#    9 build/out/app/ecourna/api_sql_sqlite_csqlstatement.cpp.o:
#    2 build/out/app/ecourna/api_util_cstringutils.cpp.o:
#    2 build/out/app/ecourna/app_dados_asn_cconversorcargoid.cpp.o:
#    2 build/out/app/ecourna/app_dados_asn_cconversorfase.cpp.o:
#    2 build/out/app/ecourna/app_dados_asn_midias_cconversordadosgeracaomidia.cpp.o:
#    1 build/out/app/ecourna/app_dados_asn_midias_cconversorinformacaomidia.cpp.o:
#    1 build/out/app/ecourna/app_dados_asn_resultadournacadastro_cconversorhabilitacaobiometrica.cpp.o:
#    1 build/out/app/ecourna/app_dados_iidentificadoreleitor.cpp.o:
#    1 build/out/app/uenux2/src/api/util/ctickmanager.cpp.o:
```

A record in an object the range does not rebuild (`make -n -C src link -W $PWD/<file>` for each file it changed) and
on a line of a file it does not edit is the base's. Any other needs the base's own list
(`tools/round/build-at.sh <base> <dir>`, then the same command there).

A function that loads a record with the wrong file name does not match: most of the functions that need the mapped
records are `ecourna::api::asn::IConversorASN<…>::Converte` and `Deconverte` instantiations. A uenux2 TU that
includes an ecourna header needs a third spelling: the target names those `…/libecea1da310e5107/p/include/ecourna/…`,
the conan package's installed headers (23 records in `ledger/source-locations.tsv`). `UENUX2_PREFIX_MAP` has that
spelling as its third map, for any object compiled with uenux2's flags or `APP_CXXFLAGS`: the headers come through `-Isrc`
as `src/ecourna/…`. `src/app/roots_cbasetype.cpp` holds the first such records ([app-flags.md](app-flags.md) §F6).

## X8. `try-tu.sh --flags "-I<dir>"` loses to a tracked header of the same name

try-tu appends `--flags` after the tree's own `-Isrc -Isrc/uenux2/src -Isrc/asn1`, so a variant of a tracked header
passed through `-I` is never read: the try compiles the tracked header, links, and reports as usual. A quoted
`#include` searches the including file's directory, then the `-iquote` directories, then the `-I` ones; the tree's
headers include each other by their path under the tree (`#include "api/gui/iformfield.h"`), which is not beside
the including file, so a `-iquote` directory holding the variant at that path wins at any include depth. A variant
of unit 43's class header that declares the destructor without defining it:

```sh
mkdir -p build/out/variant-facts/inc/api/gui
LC_ALL=C sed 's/~CImageFieldUpdate() override = default;/~CImageFieldUpdate() override;/' src/uenux2/src/api/gui/cimagefieldupdate.h > build/out/variant-facts/inc/api/gui/cimagefieldupdate.h
for f in "-I/work/build/out/variant-facts/inc" "-iquote /work/build/out/variant-facts/inc"; do
  TMPDIR=/tmp tools/round/try-tu.sh --symbols --name variant-facts --component uenux2/src/api/gui --flags "$f" src/units/43-uenux2-cimagefieldupdate-pending.cpp | /usr/bin/grep -c 'CImageFieldUpdateD[02]Ev'; done
# 2      (-I: the tracked header, whose in-class destructor the pending object emits with the vtable)
# 0      (-iquote: the variant, whose destructor is now the key function and is defined nowhere)
TMPDIR=/tmp tools/round/try-tu.sh --print-flags --component uenux2/src/api/gui --flags "-iquote /work/build/out/variant-facts/inc" src/units/43-uenux2-cimagefieldupdate-pending.cpp | /usr/bin/grep -oE -- '-I[^ ]+|-iquote [^ ]+' | tr '\n' ' '
# -Isrc -Isrc/uenux2/src -Isrc/asn1 -iquote /work/build/out/variant-facts/inc
```

A variant that only another tracked header includes is reached the same way. A copy of `api/gui/iformfield.h` with
one `#define` added, and a TU that includes only the tracked `api/gui/cimagefieldupdate.h`, whose line 29 is
`#include "api/gui/iformfield.h"`:

```sh
mkdir -p build/out/variant-facts/inc/api/gui
{ cat src/uenux2/src/api/gui/iformfield.h; printf '#define VARIANT_SEEN 1\n'; } > build/out/variant-facts/inc/api/gui/iformfield.h
printf '%s\n' '#include "api/gui/cimagefieldupdate.h"' '#ifdef VARIANT_SEEN' 'int VariantSeen() { return 1; }' '#endif' 'int Probe() { return 2; }' > build/out/variant-facts/deep.cpp
for f in "-I/work/build/out/variant-facts/inc" "-iquote /work/build/out/variant-facts/inc"; do
  TMPDIR=/tmp tools/round/try-tu.sh --symbols --name variant-deep --component uenux2/src/api/gui --flags "$f" build/out/variant-facts/deep.cpp | /usr/bin/grep -c VariantSeen; done
# 0      (-I: the tracked iformfield.h)
# 1      (-iquote: the variant, one include down)
```

After a try with a variant header, check that the object holds the variant's symbols
(`TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/try/variant-facts/obj/43-uenux2-cimagefieldupdate-pending.o`
for the last try above lists no `CImageFieldUpdateD` symbol).

## X9. `try-tu.sh --single` can differ for a function with no callee

A lone link's binaryen run does not always give the body the whole link gives, even for a leaf: a compare that the
whole link computes once and shares between two `select`s (`local.tee`) can stay computed twice alone. A scratch
class with target 11067's layout (`api::CLineField::Rect`, no callee and no argument binaryen could drop) and its
matched source form, scored alone, then linked whole and re-pointed:

```sh
mkdir -p build/out/try-facts
printf '%s\n' '#include <algorithm>' '' '#include "api/gui/primitives.h"' '' 'namespace api {' '' 'class CLinhaProbe {' 'public:' \
  '    virtual ~CLinhaProbe();' '    virtual SRect Rect() const;' '' 'private:' '    char m_resto[20];' '    SPoint m_inicio;' '    SPoint m_fim;' '};' '' \
  'CLinhaProbe::~CLinhaProbe() = default;' '' 'SRect CLinhaProbe::Rect() const' '{' '    const TPosition x1 = m_inicio.x;' \
  '    const TPosition y1 = m_inicio.y;' '    const TPosition x2 = m_fim.x;' '    const TPosition y2 = m_fim.y;' \
  '    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};' '}' '' '} // namespace api' > build/out/try-facts/clinhaprobe.cpp
TMPDIR=/tmp tools/round/try-tu.sh --single 11067 --extract export:_ZNK3api11CLinhaProbe4RectEv --component uenux2/src/api/gui build/out/try-facts/clinhaprobe.cpp | /usr/bin/grep '^score'
# score 9 over 46 rows (same 37, replaced 3 [3 operand-only], inserted 4, deleted 2)
TMPDIR=/tmp tools/round/try-tu.sh --name ../try-facts/clinha --component uenux2/src/api/gui build/out/try-facts/clinhaprobe.cpp | tail -1
# total 31 s (link 30 s incl. census); outputs in build/out/try/../try-facts/clinha
TMPDIR=/tmp tools/round/link-map.sh build/out/try-facts/clinha/wasm/vota_web
# build/out/try-facts/clinha/wasm/vota_web/link.cmd does not write try-facts/clinha/wasm/vota_web/vota_web_wasm.js   (exit 2)
TMPDIR=/tmp tools/round/link-map.sh build/out/try/../try-facts/clinha/wasm/vota_web
# scratch link byte-identical to build/out/try/../try-facts/clinha/wasm/vota_web/vota_web_wasm.wasm
# build/out/try/../try-facts/clinha/wasm-map/vota_web/names.tsv: 10970 functions named (224 binaryen thunks), 16578 wasm-ld functions
TMPDIR=/tmp tools/round/link-kinds.sh build/out/try/../try-facts/clinha/wasm/vota_web | tail -1
# shifted link (data +1048576, table +20000) named: build/out/try/../try-facts/clinha/wasm-kinds/vota_web/names.tsv
cd asmlift-wasm && pnpm --silent wasm splat-kinds ../build/out/try-facts/clinha/wasm/vota_web/vota_web_wasm.wasm | tail -1
#   every function: 10970/10970 kind-verified; …
pnpm --silent wasm splat-remap ../target/vota_web_wasm.wasm ../build/out/try-facts/clinha/wasm/vota_web/vota_web_wasm.wasm sym:_ZNK3api11CLinhaProbe4RectEv --against 11067 | tail -1
# target 11067: IDENTICAL (0 ambiguous operands read as -)
```

The lone score's rows are the two compares the target shares (`local.tee 5`, `local.tee 6`, then `local.get 5`/`6`)
and the lone link computes again; the whole link gives the target's body. So a lone score ranks the parts binaryen
does not touch (the instructions, the loads, the store order, C1 of [codegen.md](codegen.md)), and the whole link
concludes.

## X10. A try outside `build/out/try/`: map it by the path try-tu prints

`--name` is joined to `build/out/try/` as given, so `--name ../try-facts/clinha` writes the try under
`build/out/try-facts/clinha/` (X9). `link-map.sh` and `link-kinds.sh` then look for the output path inside the try's
`link.cmd` as they are given it: the normalised `build/out/try-facts/…` fails with `link.cmd does not write …`, and
the spelling try-tu prints, `build/out/try/../try-facts/clinha/wasm/vota_web`, works. `splat-kinds` and `splat-remap`
take either.
