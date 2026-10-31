# Benchmark: baseline

Target `target/vota_web_wasm.wasm` (sha256 `8579ef8d1a938191…`), image `urna-emsdk:6.0.0`, 169 rows (rows.json `22dc3021d1ee`, setups.json `4cbe3c07d2ef`), urna `7e4d88e+dirty`, 2026-10-31T05:58:28.427Z. Lift 92 ms, compile and optimise 3.4 s, total 9.8 s.

Each row is lifted, compiled with `em++ -c` at its setup's flags, and scored against the target at depth 0 with callees, data addresses, the stack pointer and the indirect table canonicalised on both sides (raw); then the object is linked alone and put through the target link's wasm-opt -Oz passes and scored again (-Oz). The ratio is differing rows over target rows; exact is a -Oz score of 0. An isolated function misses what the whole-program link does to it, so no score here means byte-identical.

## Overall

| rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 169 | 169 | 169 | 169 | 31 | 76 | 45.0% | 0.407 | 0.079 | 0.186 |

## By compile setup

| setup | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz | failures |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `uenux2` uenux2, the TSE application | 12 | 12 | 12 | 12 | 3 | 4 | 33.3% | 0.457 | 0.191 | 0.200 | – |
| `ecourna` ecourna (conan libecea1da310e5107) | 12 | 12 | 12 | 12 | 1 | 5 | 41.7% | 0.650 | 0.059 | 0.079 | – |
| `asn1` TSE fork of the III ASN.1 runtime and its generated Modulo* modules | 12 | 12 | 12 | 12 | 4 | 8 | 66.7% | 0.317 | 0.000 | 0.049 | – |
| `zlib` zlib 1.3.1 + minizip | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.358 | 0.156 | 0.179 | – |
| `sqlite` SQLite 3.50.4 amalgamation | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.416 | 0.213 | 0.177 | – |
| `openssl` OpenSSL 3.0.17 libcrypto | 12 | 12 | 12 | 12 | 3 | 5 | 41.7% | 0.423 | 0.082 | 0.178 | – |
| `7zip` 7-Zip / LZMA SDK 21.02, single-threaded | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.541 | 0.240 | 0.462 | – |
| `rhvoice` RHVoice 1.14.0 core (+ hts_engine and sonic in C) | 12 | 12 | 12 | 12 | 4 | 8 | 66.7% | 0.271 | 0.000 | 0.112 | – |
| `boost` Boost 1.89.0, header-only | 12 | 12 | 12 | 12 | 4 | 11 | 91.7% | 0.100 | 0.000 | 0.016 | – |
| `libc` emscripten musl libc (libc.a) | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.446 | 0.213 | 0.242 | – |
| `libc-optz` emscripten musl libc, the -Oz link's size-optimised members (libc_optz.a) | 5 | 5 | 5 | 5 | 0 | 1 | 20.0% | 0.417 | 0.222 | 0.200 | – |
| `dlmalloc` emscripten dlmalloc (libdlmalloc.a) | 8 | 8 | 8 | 8 | 0 | 3 | 37.5% | 0.583 | 0.268 | 0.221 | – |
| `compiler-rt` compiler-rt builtins (libcompiler_rt.a) | 12 | 12 | 12 | 12 | 0 | 2 | 16.7% | 0.641 | 0.522 | 0.415 | – |
| `libcxx` libc++ (libc++.a) | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.433 | 0.159 | 0.173 | – |
| `libcxxabi` libc++abi (libc++abi.a) | 12 | 12 | 12 | 12 | 2 | 6 | 50.0% | 0.326 | 0.051 | 0.110 | – |

## By size band

| band | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| tiny | 45 | 45 | 45 | 45 | 28 | 39 | 86.7% | 0.000 | 0.000 | 0.053 |
| small | 47 | 47 | 47 | 47 | 2 | 30 | 63.8% | 0.278 | 0.000 | 0.073 |
| medium | 33 | 33 | 33 | 33 | 1 | 7 | 21.2% | 0.529 | 0.200 | 0.257 |
| large | 27 | 27 | 27 | 27 | 0 | 0 | 0.0% | 0.634 | 0.317 | 0.353 |
| huge | 17 | 17 | 17 | 17 | 0 | 0 | 0.0% | 0.638 | 0.314 | 0.452 |

## By feature

A row counts under every feature it has.

| feature | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| leaf | 83 | 83 | 83 | 83 | 22 | 43 | 51.8% | 0.333 | 0.000 | 0.182 |
| loop | 62 | 62 | 62 | 62 | 0 | 7 | 11.3% | 0.572 | 0.289 | 0.324 |
| switch | 23 | 23 | 23 | 23 | 0 | 0 | 0.0% | 0.617 | 0.255 | 0.297 |
| call_indirect | 34 | 34 | 34 | 34 | 4 | 19 | 55.9% | 0.299 | 0.000 | 0.108 |
| invoke | 9 | 9 | 9 | 9 | 0 | 2 | 22.2% | 0.614 | 0.200 | 0.197 |
| throw | 12 | 12 | 12 | 12 | 1 | 3 | 25.0% | 0.601 | 0.203 | 0.201 |
| frame | 43 | 43 | 43 | 43 | 0 | 4 | 9.3% | 0.638 | 0.287 | 0.319 |
| alloca | 2 | 2 | 2 | 2 | 0 | 0 | 0.0% | 0.688 | 0.385 | 0.385 |
| inlined-frame | 12 | 12 | 12 | 12 | 0 | 0 | 0.0% | 0.789 | 0.272 | 0.301 |
| i64 | 73 | 73 | 73 | 73 | 6 | 16 | 21.9% | 0.556 | 0.229 | 0.275 |
| float | 13 | 13 | 13 | 13 | 2 | 2 | 15.4% | 0.624 | 0.287 | 0.291 |
| bulk-memory | 23 | 23 | 23 | 23 | 0 | 4 | 17.4% | 0.527 | 0.255 | 0.251 |
| select | 66 | 66 | 66 | 66 | 3 | 10 | 15.2% | 0.605 | 0.272 | 0.323 |

## Failures

None: every row lifted, compiled, linked and was found.

## Largest -Oz ratios

| id | size | target rows | raw | ratio | -Oz | ratio -Oz | features |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 7zip/4943 | 2246 | 678 | 1654 | 2.439 | 1570 | 2.316 | leaf loop i64 select |
| compiler-rt/1733 | 219 | 101 | 102 | 1.010 | 89 | 0.881 | leaf i64 select |
| 7zip/2646 | 526 | 281 | 277 | 0.986 | 213 | 0.758 | leaf loop frame i64 |
| compiler-rt/6225 | 192 | 83 | 66 | 0.795 | 61 | 0.735 | leaf i64 select |
| libc/2968 | 24 | 11 | 4 | 0.364 | 8 | 0.727 | leaf frame float |
| 7zip/2630 | 421 | 211 | 172 | 0.815 | 145 | 0.687 | loop call_indirect frame i64 select |
| compiler-rt/12119 | 16 | 9 | 8 | 0.889 | 6 | 0.667 | leaf |
| compiler-rt/522 | 1361 | 675 | 451 | 0.668 | 448 | 0.664 | frame i64 select |
| zlib/8121 | 81 | 43 | 40 | 0.930 | 27 | 0.628 | select |
| 7zip/1859 | 366 | 195 | 152 | 0.779 | 121 | 0.621 | leaf loop |
| uenux2/11270 | 571 | 309 | 292 | 0.945 | 183 | 0.592 | loop frame select |
| libc/1169 | 65 | 34 | 20 | 0.588 | 20 | 0.588 | leaf i64 |
| openssl/2526 | 2088 | 1109 | 845 | 0.762 | 631 | 0.569 | loop frame alloca i64 bulk-memory select |
| openssl/920 | 985 | 529 | 344 | 0.650 | 299 | 0.565 | leaf loop select |
| compiler-rt/907 | 1236 | 588 | 379 | 0.645 | 326 | 0.554 | frame i64 select |
