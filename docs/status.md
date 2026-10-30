# Status

The project has one progress number: the functions matched in `splat/matched.txt`, which the splat build
verifies on every run ([reference/splat.md](reference/splat.md)). A match means that our whole-program link
produces that target function's body byte for byte, once its calls and addresses are re-pointed into the target's.
Everything else that counts functions, such as the census tiers at the end of this page, is a diagnostic.

<!-- status:headline -->
**7,439 of 14,343 functions matched (51.87%), 2,140,846 of 5,883,903 code bytes (36.38%).**
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
| TSE code | `vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1` | 430 / 3,285 | 13.09% | 81,397 / 2,168,476 | 3.75% |
| upstream libraries | `openssl`, `sqlite`, `libc++`, `7zip`, `RHVoice`, `boost`, `libc++abi`, `utf8cpp`, `rapidxml` | 5,664 / 8,294 | 68.29% | 1,846,384 / 3,145,292 | 58.70% |
| not attributed | `unknown`, `app` | 1,345 / 2,764 | 48.66% | 213,065 / 570,135 | 37.37% |
| **total** | | **7,439 / 14,343** | **51.87%** | **2,140,846 / 5,883,903** | **36.38%** |
<!-- /status:origin -->

`ASN1` is TSE's fork of the III ASN.1 runtime: upstream code with TSE's additions ([src/asn1/README.md](../src/asn1/README.md)). The upstream
libraries are rebuilt from their own sources at the versions `third_party/MANIFEST.md` pins, so most of their matches
come from getting the version, the flags and the link order right, not from writing code.

## By component

### TSE code

<!-- status:tse -->
| component | what it is | functions | | code bytes | |
| --- | --- | ---: | ---: | ---: | ---: |
| `vota` | uenux2 `src/app/vota`: the voting application | 10 / 780 | 1.28% | 3,212 / 470,204 | 0.68% |
| `comum` | uenux2 `src/app/comum`: shared urna code (domain model, converters, reports) | 26 / 599 | 4.34% | 2,043 / 606,487 | 0.34% |
| `api` | uenux2 `src/api`: GUI toolkit, io, ipc, util, logging, audio | 63 / 516 | 12.21% | 5,971 / 214,120 | 2.79% |
| `simulador` | the web simulator's `CWasm*` devices | 6 / 144 | 4.17% | 2,543 / 58,157 | 4.37% |
| `vota-web` | the web engine (`CVotaWebEngine`, …) | 4 / 11 | 36.36% | 17 / 2,808 | 0.61% |
| **uenux2** | the five rows above | **109 / 2,050** | **5.32%** | **13,786 / 1,351,776** | **1.02%** |
| `ecourna` | the ecourna library: security, SQLite wrapper, compression, `app/dados` | 145 / 799 | 18.15% | 51,403 / 721,680 | 7.12% |
| `asn1-modules` | the generated `Modulo*` ASN.1 types | 19 / 59 | 32.20% | 3,338 / 41,909 | 7.96% |
| `ASN1` | TSE's fork of the III ASN.1 runtime | 157 / 377 | 41.64% | 12,870 / 53,111 | 24.23% |
<!-- /status:tse -->

### Upstream libraries

<!-- status:libraries -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `openssl` | 3,124 / 3,258 | 95.89% | 943,452 / 1,014,603 | 92.99% |
| `sqlite` | 878 / 927 | 94.71% | 700,394 / 772,965 | 90.61% |
| `libc++` | 838 / 1,957 | 42.82% | 109,766 / 439,879 | 24.95% |
| `7zip` | 477 / 970 | 49.18% | 44,657 / 292,539 | 15.27% |
| `RHVoice` | 278 / 740 | 37.57% | 39,137 / 450,027 | 8.70% |
| `boost` | 51 / 192 | 26.56% | 4,131 / 105,977 | 3.90% |
| `libc++abi` | 11 / 234 | 4.70% | 2,209 / 53,263 | 4.15% |
| `utf8cpp` | 6 / 10 | 60.00% | 2,306 / 8,275 | 27.87% |
| `rapidxml` | 1 / 6 | 16.67% | 332 / 7,764 | 4.28% |
<!-- /status:libraries -->

The library versions and the evidence for them are in `third_party/MANIFEST.md`.

### Not attributed

<!-- status:unattributed -->
| component | functions | | code bytes | |
| --- | ---: | ---: | ---: | ---: |
| `unknown` | 1,063 / 1,508 | 70.49% | 169,201 / 258,975 | 65.33% |
| `app` | 282 / 1,256 | 22.45% | 43,864 / 311,160 | 14.10% |
<!-- /status:unattributed -->

`unknown` holds functions that `ledger/func-attribution.tsv` gives no component, and `app` holds functions the
library census classed as application code that no component evidence places. Neither means "TSE code". For the
functions our link has a body for, the object that body is compiled from says where the code comes from (the
scan's `object` column):

<!-- status:unattributed-origin -->
| our candidate is compiled from | `unknown` matched / total | `app` matched / total |
| --- | ---: | ---: |
| OpenSSL | 647 / 668 | 158 / 158 |
| SQLite | 247 / 249 | 37 / 38 |
| our ecourna units | 10 / 32 | 43 / 56 |
| emscripten sysroot: libc (musl) | 52 / 54 | 9 / 9 |
| emscripten sysroot: libc++ | 42 / 52 | 7 / 8 |
| our stand-ins (src/app, src/web) | 21 / 27 | 0 / 8 |
| binaryen (functions the optimizer creates) | 15 / 16 | 4 / 4 |
| RHVoice | 4 / 14 | 1 / 2 |
| 7-Zip | 11 / 14 | 0 / 1 |
| our ASN.1 runtime and modules | 4 / 8 | 3 / 3 |
| our uenux2 units | 1 / 4 | 5 / 6 |
| zlib | 0 / 0 | 9 / 10 |
| emscripten sysroot: libc++abi | 4 / 5 | 2 / 2 |
| emscripten sysroot: compiler-rt | 1 / 1 | 4 / 5 |
| emscripten sysroot: dlmalloc | 4 / 5 | 0 / 0 |
| no candidate in our link | 0 / 359 | 0 / 946 |
<!-- /status:unattributed-origin -->

Most of these are OpenSSL, SQLite and emscripten's own system libraries (musl libc, libc++, dlmalloc and
compiler-rt from the image's sysroot) whose callers the attribution could not name. The functions with no
candidate are not placed by anything yet.

## What is left

`make -C src splat-scan` gives every target function one verdict:

<!-- status:verdicts -->
| verdict | functions | code bytes | what it means |
| --- | ---: | ---: | --- |
| `match` | 7,439 | 2,140,846 | matched |
| `differs` | 422 | 79,989 | our link has a candidate body and it differs; `detail` names the first difference. These are the closest to a match. |
| `unresolved` | 816 | 531,738 | an operand of our body has no counterpart in the target: a callee the symbol file maps to no target function (such as our roots stand-in or a `byn$mgfn-shared$` thunk), an address or table slot of ours (by its operand kind) whose object or function has no target image, or a data name only this function voted for (*self-voted*). It is checked before the bytes are compared, so a body that is also different shows only this |
| `no-candidate` | 5,666 | 3,131,330 | our link has no body for it yet |
<!-- /status:verdicts -->

<!-- status:tse-verdicts -->
For TSE code alone: 430 `match`, 77 `differs`, 200 `unresolved` and 2,578 `no-candidate`.
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
263 matches are bodies of 8 B or less, and 38 matches have a byte-identical twin in the target. 0 matches are kind-unverified: the operand-kind table cannot vouch for their constants, so the check offered each one every reading (`make -C src splat` names them).
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
| `byte` | 921 | 920 | 0 | 0 | 1 |
| `fingerprint` | 541 | 540 | 0 | 1 | 0 |
| `addr` | 5,609 | 5,250 | 187 | 168 | 4 |
| `shape` | 219 | 145 | 32 | 40 | 2 |
| `none` | 7,053 | 584 | 203 | 607 | 5,659 |
<!-- /status:tiers -->

`pnpm wasm progress --by component`, run from `asmlift-wasm/`, prints the tiers per component, with what moved
since the snapshot in `ledger/history/`.
