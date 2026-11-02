# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**11,480 of 14,343 functions matched (80.04%), 3,181,830 of 5,883,903 code bytes (54.08%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 2,589 / 3,285 | 78.81% | 818,369 / 2,168,476 | 37.74% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 6,786 / 8,294 | 81.82% | 2,048,461 / 3,145,292 | 65.13% |
| not attributed | `unknown`, `app` | 2,105 / 2,764 | 76.16% | 315,000 / 570,135 | 55.25% |
| **total** | | **11,480 / 14,343** | **80.04%** | **3,181,830 / 5,883,903** | **54.08%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 492 / 780 | 63.08% | 95,809 / 470,204 | 20.38% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 432 / 599 | 72.12% | 180,014 / 606,487 | 29.68% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 457 / 516 | 88.57% | 75,508 / 214,120 | 35.26% |
| `simulador` | the web simulator's `CWasm*` devices | 132 / 144 | 91.67% | 21,139 / 58,157 | 36.35% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 9 / 11 | 81.82% | 168 / 2,808 | 5.98% |
| **uenux2** | the five rows above | **1,522 / 2,050** | **74.24%** | **372,638 / 1,351,776** | **27.57%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 647 / 799 | 80.98% | 365,229 / 721,680 | 50.61% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 50 / 59 | 84.75% | 29,323 / 41,909 | 69.97% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 370 / 377 | 98.14% | 51,179 / 53,111 | 96.36% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,173 / 3,258 | 97.39% | 948,669 / 1,014,603 | 93.50% |
| `libc++` | 1,496 / 1,957 | 76.44% | 222,029 / 439,879 | 50.48% |
| `sqlite` | 910 / 927 | 98.17% | 706,459 / 772,965 | 91.40% |
| `7zip` | 486 / 970 | 50.10% | 45,048 / 292,539 | 15.40% |
| `RHVoice` | 429 / 740 | 57.97% | 65,565 / 450,027 | 14.57% |
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
| `unknown` | 1,312 / 1,508 | 87.00% | 200,545 / 258,975 | 77.44% |
| `app` | 793 / 1,256 | 63.14% | 114,455 / 311,160 | 36.78% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 662 / 668 | 157 / 157 |
| our uenux2 units | 132 / 156 | 421 / 550 |
| SQLite | 248 / 250 | 37 / 38 |
| our ecourna units | 47 / 51 | 92 / 99 |
| our stand-ins (src/app, src/web) | 39 / 44 | 30 / 37 |
| emscripten sysroot: libc (musl) | 62 / 63 | 9 / 9 |
| emscripten sysroot: libc++ | 62 / 66 | 5 / 5 |
| binaryen (functions the optimizer creates) | 24 / 26 | 17 / 17 |
| 7-Zip | 11 / 14 | 0 / 1 |
| our ASN.1 runtime and modules | 10 / 11 | 4 / 4 |
| zlib | 0 / 0 | 14 / 14 |
| RHVoice | 6 / 10 | 1 / 1 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 138 | 0 / 317 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 11,480 | 3,181,830 | matched |
| `differs` | 459 | 129,389 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 514 | 601,492 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 1,890 | 1,971,192 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 2,589 `match`, 76 `differs`, 41 `unresolved` and 579 `no-candidate`.
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
376 matches are bodies of 8 B or less, and 56 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,251 | 1,251 | 0 | 0 | 0 |
| `fingerprint` | 672 | 671 | 0 | 1 | 0 |
| `addr` | 7,310 | 6,960 | 204 | 144 | 2 |
| `shape` | 844 | 804 | 31 | 9 | 0 |
| `none` | 4,266 | 1,794 | 224 | 360 | 1,888 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
