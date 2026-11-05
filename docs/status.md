# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**12,673 of 14,343 functions matched (88.36%), 4,087,446 of 5,883,903 code bytes (69.47%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 3,013 / 3,285 | 91.72% | 1,410,685 / 2,168,476 | 65.05% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 7,098 / 8,294 | 85.58% | 2,194,670 / 3,145,292 | 69.78% |
| not attributed | `unknown`, `app` | 2,562 / 2,764 | 92.69% | 482,091 / 570,135 | 84.56% |
| **total** | | **12,673 / 14,343** | **88.36%** | **4,087,446 / 5,883,903** | **69.47%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 710 / 780 | 91.03% | 274,991 / 470,204 | 58.48% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 542 / 599 | 90.48% | 368,481 / 606,487 | 60.76% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 477 / 516 | 92.44% | 82,063 / 214,120 | 38.33% |
| `simulador` | the web simulator's `CWasm*` devices | 135 / 144 | 93.75% | 23,129 / 58,157 | 39.77% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 10 / 11 | 90.91% | 2,648 / 2,808 | 94.30% |
| **uenux2** | the five rows above | **1,874 / 2,050** | **91.41%** | **751,312 / 1,351,776** | **55.58%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 709 / 799 | 88.74% | 570,936 / 721,680 | 79.11% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 55 / 59 | 93.22% | 36,164 / 41,909 | 86.29% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 375 / 377 | 99.47% | 52,273 / 53,111 | 98.42% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,182 / 3,258 | 97.67% | 950,501 / 1,014,603 | 93.68% |
| `libc++` | 1,698 / 1,957 | 86.77% | 288,076 / 439,879 | 65.49% |
| `sqlite` | 919 / 927 | 99.14% | 713,629 / 772,965 | 92.32% |
| `7zip` | 489 / 970 | 50.41% | 45,575 / 292,539 | 15.58% |
| `RHVoice` | 434 / 740 | 58.65% | 66,236 / 450,027 | 14.72% |
| `libc++abi` | 231 / 234 | 98.72% | 52,565 / 53,263 | 98.69% |
| `boost` | 137 / 192 | 71.35% | 74,052 / 105,977 | 69.88% |
| `utf8cpp` | 7 / 10 | 70.00% | 3,704 / 8,275 | 44.76% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,418 / 1,508 | 94.03% | 229,921 / 258,975 | 88.78% |
| `app` | 1,144 / 1,256 | 91.08% | 252,170 / 311,160 | 81.04% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| our uenux2 units | 195 / 206 | 743 / 773 |
| OpenSSL | 668 / 673 | 157 / 157 |
| SQLite | 240 / 242 | 37 / 38 |
| our ecourna units | 98 / 101 | 102 / 104 |
| emscripten sysroot: libc (musl) | 63 / 64 | 11 / 11 |
| emscripten sysroot: libc++ | 68 / 70 | 5 / 5 |
| binaryen (functions the optimizer creates) | 25 / 27 | 36 / 36 |
| our stand-ins (src/app, src/web) | 25 / 28 | 27 / 30 |
| 7-Zip | 12 / 15 | 0 / 0 |
| our ASN.1 runtime and modules | 10 / 11 | 4 / 4 |
| zlib | 0 / 0 | 14 / 14 |
| RHVoice | 5 / 9 | 2 / 2 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 51 | 0 / 75 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 12,673 | 4,087,446 | matched |
| `differs` | 308 | 233,828 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 478 | 583,273 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 884 | 979,356 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 3,013 `match`, 46 `differs`, 44 `unresolved` and 182 `no-candidate`.
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
407 matches are bodies of 8 B or less, and 56 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,358 | 1,358 | 0 | 0 | 0 |
| `fingerprint` | 622 | 621 | 0 | 1 | 0 |
| `addr` | 7,797 | 7,594 | 84 | 118 | 1 |
| `shape` | 1,146 | 1,104 | 29 | 13 | 0 |
| `none` | 3,420 | 1,996 | 195 | 346 | 883 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
