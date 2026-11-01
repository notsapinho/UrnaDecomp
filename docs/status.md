# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**10,691 of 14,343 functions matched (74.54%), 2,869,753 of 5,883,903 code bytes (48.77%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 2,177 / 3,285 | 66.27% | 589,506 / 2,168,476 | 27.19% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 6,626 / 8,294 | 79.89% | 1,999,050 / 3,145,292 | 63.56% |
| not attributed | `unknown`, `app` | 1,888 / 2,764 | 68.31% | 281,197 / 570,135 | 49.32% |
| **total** | | **10,691 / 14,343** | **74.54%** | **2,869,753 / 5,883,903** | **48.77%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 326 / 780 | 41.79% | 32,310 / 470,204 | 6.87% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 321 / 599 | 53.59% | 95,484 / 606,487 | 15.74% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 422 / 516 | 81.78% | 62,217 / 214,120 | 29.06% |
| `simulador` | the web simulator's `CWasm*` devices | 130 / 144 | 90.28% | 21,030 / 58,157 | 36.16% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 4 / 11 | 36.36% | 17 / 2,808 | 0.61% |
| **uenux2** | the five rows above | **1,203 / 2,050** | **58.68%** | **211,058 / 1,351,776** | **15.61%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 561 / 799 | 70.21% | 302,486 / 721,680 | 41.91% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 49 / 59 | 83.05% | 25,946 / 41,909 | 61.91% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 364 / 377 | 96.55% | 50,016 / 53,111 | 94.17% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,166 / 3,258 | 97.18% | 948,214 / 1,014,603 | 93.46% |
| `libc++` | 1,358 / 1,957 | 69.39% | 174,250 / 439,879 | 39.61% |
| `sqlite` | 902 / 927 | 97.30% | 705,806 / 772,965 | 91.31% |
| `7zip` | 485 / 970 | 50.00% | 44,989 / 292,539 | 15.38% |
| `RHVoice` | 423 / 740 | 57.16% | 65,100 / 450,027 | 14.47% |
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
| `unknown` | 1,255 / 1,508 | 83.22% | 192,272 / 258,975 | 74.24% |
| `app` | 633 / 1,256 | 50.40% | 88,925 / 311,160 | 28.58% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 662 / 668 | 157 / 157 |
| our uenux2 units | 92 / 116 | 284 / 381 |
| SQLite | 248 / 250 | 37 / 38 |
| our ecourna units | 44 / 51 | 91 / 99 |
| emscripten sysroot: libc (musl) | 60 / 62 | 8 / 8 |
| emscripten sysroot: libc++ | 58 / 61 | 7 / 7 |
| our stand-ins (src/app, src/web) | 31 / 34 | 11 / 33 |
| binaryen (functions the optimizer creates) | 24 / 26 | 11 / 11 |
| our ASN.1 runtime and modules | 10 / 11 | 6 / 6 |
| 7-Zip | 11 / 14 | 0 / 1 |
| zlib | 0 / 0 | 14 / 14 |
| RHVoice | 6 / 10 | 1 / 1 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 194 | 0 / 493 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 10,691 | 2,869,753 | matched |
| `differs` | 454 | 109,325 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 525 | 499,855 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 2,673 | 2,404,970 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 2,177 `match`, 71 `differs`, 35 `unresolved` and 1,002 `no-candidate`.
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
365 matches are bodies of 8 B or less, and 56 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,116 | 1,116 | 0 | 0 | 0 |
| `fingerprint` | 722 | 721 | 0 | 1 | 0 |
| `addr` | 7,054 | 6,711 | 196 | 145 | 2 |
| `shape` | 677 | 642 | 29 | 5 | 1 |
| `none` | 4,774 | 1,501 | 229 | 374 | 2,670 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
