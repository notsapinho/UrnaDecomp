# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**12,939 of 14,343 functions matched (90.21%), 4,291,505 of 5,883,903 code bytes (72.94%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 3,121 / 3,285 | 95.01% | 1,546,779 / 2,168,476 | 71.33% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 7,203 / 8,294 | 86.85% | 2,229,911 / 3,145,292 | 70.90% |
| not attributed | `unknown`, `app` | 2,615 / 2,764 | 94.61% | 514,815 / 570,135 | 90.30% |
| **total** | | **12,939 / 14,343** | **90.21%** | **4,291,505 / 5,883,903** | **72.94%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 744 / 780 | 95.38% | 339,661 / 470,204 | 72.24% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 560 / 599 | 93.49% | 388,966 / 606,487 | 64.13% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 492 / 516 | 95.35% | 88,888 / 214,120 | 41.51% |
| `simulador` | the web simulator's `CWasm*` devices | 136 / 144 | 94.44% | 23,661 / 58,157 | 40.68% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 10 / 11 | 90.91% | 2,648 / 2,808 | 94.30% |
| **uenux2** | the five rows above | **1,942 / 2,050** | **94.73%** | **843,824 / 1,351,776** | **62.42%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 748 / 799 | 93.62% | 614,446 / 721,680 | 85.14% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 56 / 59 | 94.92% | 36,236 / 41,909 | 86.46% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 375 / 377 | 99.47% | 52,273 / 53,111 | 98.42% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,190 / 3,258 | 97.91% | 951,072 / 1,014,603 | 93.74% |
| `libc++` | 1,780 / 1,957 | 90.96% | 318,912 / 439,879 | 72.50% |
| `sqlite` | 922 / 927 | 99.46% | 713,977 / 772,965 | 92.37% |
| `7zip` | 491 / 970 | 50.62% | 45,754 / 292,539 | 15.64% |
| `RHVoice` | 436 / 740 | 58.92% | 68,691 / 450,027 | 15.26% |
| `libc++abi` | 231 / 234 | 98.72% | 52,565 / 53,263 | 98.69% |
| `boost` | 145 / 192 | 75.52% | 74,904 / 105,977 | 70.68% |
| `utf8cpp` | 7 / 10 | 70.00% | 3,704 / 8,275 | 44.76% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,428 / 1,508 | 94.69% | 234,761 / 258,975 | 90.65% |
| `app` | 1,187 / 1,256 | 94.51% | 280,054 / 311,160 | 90.00% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| our uenux2 units | 202 / 213 | 779 / 803 |
| OpenSSL | 668 / 673 | 157 / 157 |
| SQLite | 240 / 242 | 37 / 38 |
| our ecourna units | 99 / 101 | 102 / 103 |
| emscripten sysroot: libc++ | 68 / 70 | 6 / 6 |
| emscripten sysroot: libc (musl) | 63 / 64 | 11 / 11 |
| binaryen (functions the optimizer creates) | 26 / 28 | 38 / 38 |
| our stand-ins (src/app, src/web) | 26 / 29 | 31 / 34 |
| 7-Zip | 12 / 15 | 0 / 0 |
| our ASN.1 runtime and modules | 10 / 11 | 4 / 4 |
| zlib | 0 / 0 | 14 / 14 |
| RHVoice | 5 / 9 | 2 / 2 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 42 | 0 / 39 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 12,939 | 4,291,505 | matched |
| `differs` | 263 | 251,245 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 473 | 579,984 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 668 | 761,169 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 3,121 `match`, 43 `differs`, 40 `unresolved` and 81 `no-candidate`.
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
420 matches are bodies of 8 B or less, and 56 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,356 | 1,356 | 0 | 0 | 0 |
| `fingerprint` | 643 | 642 | 0 | 1 | 0 |
| `addr` | 7,943 | 7,777 | 44 | 121 | 1 |
| `shape` | 1,301 | 1,260 | 31 | 10 | 0 |
| `none` | 3,100 | 1,904 | 188 | 341 | 667 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
