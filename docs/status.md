# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**9,808 of 14,343 functions matched (68.38%), 2,630,057 of 5,883,903 code bytes (44.70%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 1,669 / 3,285 | 50.81% | 425,550 / 2,168,476 | 19.62% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 6,472 / 8,294 | 78.03% | 1,958,406 / 3,145,292 | 62.26% |
| not attributed | `unknown`, `app` | 1,667 / 2,764 | 60.31% | 246,101 / 570,135 | 43.17% |
| **total** | | **9,808 / 14,343** | **68.38%** | **2,630,057 / 5,883,903** | **44.70%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 135 / 780 | 17.31% | 14,218 / 470,204 | 3.02% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 184 / 599 | 30.72% | 46,685 / 606,487 | 7.70% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 373 / 516 | 72.29% | 50,363 / 214,120 | 23.52% |
| `simulador` | the web simulator's `CWasm*` devices | 116 / 144 | 80.56% | 15,619 / 58,157 | 26.86% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 4 / 11 | 36.36% | 17 / 2,808 | 0.61% |
| **uenux2** | the five rows above | **812 / 2,050** | **39.61%** | **126,902 / 1,351,776** | **9.39%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 458 / 799 | 57.32% | 237,050 / 721,680 | 32.85% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 39 / 59 | 66.10% | 12,230 / 41,909 | 29.18% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 360 / 377 | 95.49% | 49,368 / 53,111 | 92.95% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,136 / 3,258 | 96.26% | 943,694 / 1,014,603 | 93.01% |
| `libc++` | 1,253 / 1,957 | 64.03% | 142,052 / 439,879 | 32.29% |
| `sqlite` | 891 / 927 | 96.12% | 704,025 / 772,965 | 91.08% |
| `7zip` | 485 / 970 | 50.00% | 44,989 / 292,539 | 15.38% |
| `RHVoice` | 416 / 740 | 56.22% | 63,533 / 450,027 | 14.12% |
| `libc++abi` | 230 / 234 | 98.29% | 51,256 / 53,263 | 96.23% |
| `boost` | 53 / 192 | 27.60% | 4,821 / 105,977 | 4.55% |
| `utf8cpp` | 7 / 10 | 70.00% | 3,704 / 8,275 | 44.76% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,188 / 1,508 | 78.78% | 184,632 / 258,975 | 71.29% |
| `app` | 479 / 1,256 | 38.14% | 61,469 / 311,160 | 19.75% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 651 / 668 | 157 / 157 |
| SQLite | 248 / 250 | 37 / 38 |
| our uenux2 units | 48 / 69 | 138 / 185 |
| our ecourna units | 46 / 53 | 87 / 100 |
| emscripten sysroot: libc++ | 54 / 58 | 7 / 10 |
| emscripten sysroot: libc (musl) | 54 / 56 | 8 / 8 |
| our stand-ins (src/app, src/web) | 30 / 38 | 16 / 25 |
| binaryen (functions the optimizer creates) | 21 / 22 | 7 / 7 |
| our ASN.1 runtime and modules | 10 / 12 | 6 / 6 |
| 7-Zip | 11 / 14 | 0 / 1 |
| RHVoice | 6 / 10 | 1 / 1 |
| zlib | 0 / 0 | 9 / 10 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 247 | 0 / 701 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 9,808 | 2,630,057 | matched |
| `differs` | 472 | 105,697 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 537 | 511,206 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 3,526 | 2,636,943 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 1,669 `match`, 75 `differs`, 44 `unresolved` and 1,497 `no-candidate`.
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
324 matches are bodies of 8 B or less, and 55 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,082 | 1,082 | 0 | 0 | 0 |
| `fingerprint` | 685 | 684 | 0 | 1 | 0 |
| `addr` | 6,610 | 6,302 | 184 | 122 | 2 |
| `shape` | 422 | 374 | 30 | 17 | 1 |
| `none` | 5,544 | 1,366 | 258 | 397 | 3,523 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the committed ledger.
