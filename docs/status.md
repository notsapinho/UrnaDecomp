# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**10,313 of 14,343 functions matched (71.90%), 2,762,511 of 5,883,903 code bytes (46.95%).**
<!-- /status:headline -->

Every block between `status:` markers on this page is written by
`make -C src status` from two committed files: `splat/matched.txt` and `splat/scan.tsv`, the scan that
`make -C src splat-match` writes together with the match list. CI runs `python3 -I -B tools/round/status.py --check`,
which fails when the scan's `match` rows are not exactly the lines of `splat/matched.txt` or when a block here is
not what the scan gives. The same command draws the README's waffles in `docs/img/` from the scan, and the check
fails when one is stale.
Never edit the numbers or the waffles by hand.

## By origin

The meter groups each target function by its [component](glossary.md#component-and-owner). A component records
who calls a function, not which library its code comes from: libc's `pad` (target 788) counts as `RHVoice`, and a
library function with no evidence of its own that only TSE code calls counts as that TSE component. So `not
attributed` is mostly OpenSSL, SQLite and emscripten's own system libraries whose callers the attribution could not
name ([Not attributed](#not-attributed)).

<!-- status:origin -->
| origin | components | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 1,958 / 3,285 | 59.60% | 508,011 / 2,168,476 | 23.43% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 6,572 / 8,294 | 79.24% | 1,985,294 / 3,145,292 | 63.12% |
| not attributed | `unknown`, `app` | 1,783 / 2,764 | 64.51% | 269,206 / 570,135 | 47.22% |
| **total** | | **10,313 / 14,343** | **71.90%** | **2,762,511 / 5,883,903** | **46.95%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 243 / 780 | 31.15% | 24,318 / 470,204 | 5.17% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 274 / 599 | 45.74% | 67,540 / 606,487 | 11.14% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 395 / 516 | 76.55% | 56,110 / 214,120 | 26.20% |
| `simulador` | the web simulator's `CWasm*` devices | 123 / 144 | 85.42% | 18,955 / 58,157 | 32.59% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 4 / 11 | 36.36% | 17 / 2,808 | 0.61% |
| **uenux2** | the five rows above | **1,039 / 2,050** | **50.68%** | **166,940 / 1,351,776** | **12.35%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 513 / 799 | 64.21% | 268,687 / 721,680 | 37.23% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 45 / 59 | 76.27% | 22,967 / 41,909 | 54.80% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 361 / 377 | 95.76% | 49,417 / 53,111 | 93.04% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,155 / 3,258 | 96.84% | 946,696 / 1,014,603 | 93.31% |
| `libc++` | 1,320 / 1,957 | 67.45% | 162,973 / 439,879 | 37.05% |
| `sqlite` | 900 / 927 | 97.09% | 705,573 / 772,965 | 91.28% |
| `7zip` | 485 / 970 | 50.00% | 44,989 / 292,539 | 15.38% |
| `RHVoice` | 420 / 740 | 56.76% | 64,372 / 450,027 | 14.30% |
| `libc++abi` | 230 / 234 | 98.29% | 51,256 / 53,263 | 96.23% |
| `boost` | 54 / 192 | 28.12% | 5,399 / 105,977 | 5.09% |
| `utf8cpp` | 7 / 10 | 70.00% | 3,704 / 8,275 | 44.76% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,224 / 1,508 | 81.17% | 189,055 / 258,975 | 73.00% |
| `app` | 559 / 1,256 | 44.51% | 80,151 / 311,160 | 25.76% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 655 / 668 | 157 / 157 |
| our uenux2 units | 77 / 99 | 214 / 306 |
| SQLite | 248 / 250 | 37 / 38 |
| our ecourna units | 45 / 51 | 89 / 100 |
| emscripten sysroot: libc++ | 57 / 60 | 7 / 7 |
| emscripten sysroot: libc (musl) | 55 / 57 | 8 / 8 |
| our stand-ins (src/app, src/web) | 28 / 31 | 11 / 17 |
| binaryen (functions the optimizer creates) | 23 / 25 | 9 / 9 |
| our ASN.1 runtime and modules | 10 / 12 | 6 / 6 |
| 7-Zip | 11 / 14 | 0 / 1 |
| zlib | 0 / 0 | 14 / 14 |
| RHVoice | 6 / 11 | 1 / 1 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 219 | 0 / 585 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 10,313 | 2,762,511 | matched |
| `differs` | 466 | 114,745 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 543 | 506,186 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 3,021 | 2,500,461 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 1,958 `match`, 82 `differs`, 42 `unresolved` and 1,203 `no-candidate`.
<!-- /status:tse-verdicts -->

[how-to-decompile.md](how-to-decompile.md) walks from picking one of these to a match.

## Reading the meter

`TMPDIR=/tmp make -C src splat` ends by printing the meter: a sha256 line that must name the target's
`8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2` with the match count, a `substituted:` line with
the totals above, one row per component (`component matched/total matched-bytes/total-bytes percent`, the rows of
the component tables), and three lines about readings:

- **re-pointing alone** counts matches whose body re-points into the target's with no choice to make.
- **another reading** counts matches where an `i32.const` or a memarg offset could be an address, a table slot or a
  plain integer, and the target body picked one of our readings.
- **which copy** counts matches whose content sits at several places in the target, such as a tail-merged string, or
  whose function pointer names a function the target's table holds in several slots, and the target body picked the
  copy.

[reference/splat.md](reference/splat.md) "Substitute" explains readings. Some matches carry an arbitrary name,
because binaryen merges identical bodies and the target keeps one copy under one index:

<!-- status:twins -->
342 matches are bodies of 8 B or less, and 55 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
<!-- /status:twins -->

A meter that does not show the target's sha256 is not a meter: the build failed, and its output lists the matches
that drifted ([reference/splat.md](reference/splat.md) "The drift rule").

## Regenerating this page

The commit that changes `splat/matched.txt` also commits `splat/scan.tsv` and these blocks. `make -C src
splat-match` writes all three. After a scan alone, or a hand edit of the match list, run:

```sh
TMPDIR=/tmp make -C src splat-scan    # about two and a half minutes; rewrites splat/scan.tsv and the blocks
make -C src status                    # the blocks alone, from the committed scan
```

The origin groups, the component descriptions and the object-to-origin rules are in `tools/round/status.py`.

## Diagnostics: the census tiers

`make -C src census` pairs every target function with the closest function of our link and records the pairing's
[tier](glossary.md#pairing-and-progress) in `ledger/functions.tsv` (column `best_kind`). The tiers show what is
close to matching. They are not the meter: a `byte` or `fingerprint` pair is not a match, and most matched
functions pair at a weaker tier, because a fingerprint also covers the callees two calls deep (see
[depth](glossary.md#pairing-and-progress)). Each tier against the scan's verdicts:

<!-- status:tiers -->
| tier | functions | match | differs | unresolved | no-candidate |
| --- | ---: | ---: | ---: | ---: | ---: |
| `byte` | 1,103 | 1,103 | 0 | 0 | 0 |
| `fingerprint` | 707 | 706 | 0 | 1 | 0 |
| `addr` | 6,892 | 6,549 | 193 | 148 | 2 |
| `shape` | 614 | 573 | 31 | 9 | 1 |
| `none` | 5,027 | 1,382 | 242 | 385 | 3,018 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
