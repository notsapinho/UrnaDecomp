# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**8,684 of 14,343 functions matched (60.55%), 2,358,681 of 5,883,903 code bytes (40.09%).**
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
library function with no evidence of its own that only TSE code calls counts as that TSE component.

<!-- status:origin -->
| origin | components | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 1,183 / 3,285 | 36.01% | 234,012 / 2,168,476 | 10.79% |
| upstream libraries | `openssl`, `libc++`, `sqlite`, `7zip`, `RHVoice`, `libc++abi`, `boost`, `utf8cpp`, `rapidxml` | 6,087 / 8,294 | 73.39% | 1,904,859 / 3,145,292 | 60.56% |
| not attributed | `unknown`, `app` | 1,414 / 2,764 | 51.16% | 219,810 / 570,135 | 38.55% |
| **total** | | **8,684 / 14,343** | **60.55%** | **2,358,681 / 5,883,903** | **40.09%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 56 / 780 | 7.18% | 6,696 / 470,204 | 1.42% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 97 / 599 | 16.19% | 14,548 / 606,487 | 2.40% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 258 / 516 | 50.00% | 23,377 / 214,120 | 10.92% |
| `simulador` | the web simulator's `CWasm*` devices | 104 / 144 | 72.22% | 12,407 / 58,157 | 21.33% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 4 / 11 | 36.36% | 17 / 2,808 | 0.61% |
| **uenux2** | the five rows above | **519 / 2,050** | **25.32%** | **57,045 / 1,351,776** | **4.22%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 308 / 799 | 38.55% | 128,727 / 721,680 | 17.84% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 27 / 59 | 45.76% | 6,073 / 41,909 | 14.49% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 329 / 377 | 87.27% | 42,167 / 53,111 | 79.39% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,126 / 3,258 | 95.95% | 943,466 / 1,014,603 | 92.99% |
| `libc++` | 1,024 / 1,957 | 52.32% | 116,107 / 439,879 | 26.40% |
| `sqlite` | 882 / 927 | 95.15% | 700,936 / 772,965 | 90.68% |
| `7zip` | 477 / 970 | 49.18% | 44,657 / 292,539 | 15.27% |
| `RHVoice` | 288 / 740 | 38.92% | 40,978 / 450,027 | 9.11% |
| `libc++abi` | 230 / 234 | 98.29% | 51,256 / 53,263 | 96.23% |
| `boost` | 53 / 192 | 27.60% | 4,821 / 105,977 | 4.55% |
| `utf8cpp` | 6 / 10 | 60.00% | 2,306 / 8,275 | 27.87% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,109 / 1,508 | 73.54% | 173,018 / 258,975 | 66.81% |
| `app` | 305 / 1,256 | 24.28% | 46,792 / 311,160 | 15.04% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 651 / 668 | 158 / 158 |
| SQLite | 248 / 250 | 37 / 38 |
| our ecourna units | 30 / 41 | 51 / 66 |
| emscripten sysroot: libc (musl) | 54 / 56 | 9 / 9 |
| emscripten sysroot: libc++ | 47 / 54 | 7 / 8 |
| our stand-ins (src/app, src/web) | 23 / 31 | 0 / 13 |
| our uenux2 units | 5 / 10 | 16 / 20 |
| binaryen (functions the optimizer creates) | 16 / 17 | 6 / 6 |
| our ASN.1 runtime and modules | 9 / 11 | 5 / 5 |
| 7-Zip | 11 / 14 | 0 / 1 |
| RHVoice | 6 / 13 | 1 / 2 |
| zlib | 0 / 0 | 9 / 10 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 332 | 0 / 913 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 8,684 | 2,358,681 | matched |
| `differs` | 458 | 98,879 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 645 | 522,526 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 4,556 | 2,903,817 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 1,183 `match`, 86 `differs`, 78 `unresolved` and 1,938 `no-candidate`.
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
300 matches are bodies of 8 B or less, and 54 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 1,061 | 1,061 | 0 | 0 | 0 |
| `fingerprint` | 656 | 655 | 0 | 1 | 0 |
| `addr` | 6,146 | 5,832 | 185 | 127 | 2 |
| `shape` | 310 | 240 | 40 | 28 | 2 |
| `none` | 6,170 | 896 | 233 | 489 | 4,552 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the snapshot in `ledger/history/`.
