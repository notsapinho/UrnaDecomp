# Benchmark: baseline

Target `target/vota_web_wasm.wasm` (sha256 `8579ef8d1a938191…`), image `urna-emsdk:6.0.0`, 205 rows (rows.json `b71404f6cadc`, setups.json `02016cca8b7b`), urna `686cdd1b+dirty`, 2026-11-01T15:34:13.289Z. Lift 85 ms, compile and optimise 4.7 s, total 10.5 s.

Each row is lifted, compiled with `em++ -c` at its setup's flags, and scored against the target at depth 0 with callees, data addresses, the stack pointer and the indirect table canonicalised on both sides (raw); then the object is linked alone and put through the target link's wasm-opt -Oz passes and scored again (-Oz). The ratio is differing rows over target rows; exact is a -Oz score of 0. An isolated function misses what the whole-program link does to it, so no score here means byte-identical.

## Overall

| rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 205 | 205 | 205 | 205 | 37 | 89 | 43.4% | 0.404 | 0.068 | 0.190 |

## By compile setup

| setup | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz | failures |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `uenux2` uenux2, the TSE application | 12 | 12 | 12 | 12 | 3 | 5 | 41.7% | 0.263 | 0.005 | 0.148 | – |
| `vota-web` the executable TU, wasm/vota_web/vota_web_wasm.cpp: votaInit's, first on the link line | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.173 | 0.043 | 0.221 | – |
| `ecourna` ecourna (conan libecea1da310e5107) | 12 | 12 | 12 | 12 | 1 | 5 | 41.7% | 0.712 | 0.063 | 0.090 | – |
| `asn1` TSE fork of the III ASN.1 runtime and its generated Modulo* modules | 12 | 12 | 12 | 12 | 4 | 8 | 66.7% | 0.317 | 0.000 | 0.049 | – |
| `zlib` zlib 1.3.1 + minizip | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.391 | 0.116 | 0.170 | – |
| `libqrencode` libqrencode 4.1.1 | 12 | 12 | 12 | 12 | 1 | 4 | 33.3% | 0.363 | 0.210 | 0.293 | – |
| `sqlite` SQLite 3.50.4 amalgamation | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.416 | 0.213 | 0.193 | – |
| `openssl` OpenSSL 3.0.17 libcrypto | 12 | 12 | 12 | 12 | 3 | 5 | 41.7% | 0.423 | 0.082 | 0.216 | – |
| `7zip` 7-Zip / LZMA SDK 21.02, single-threaded | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.541 | 0.240 | 0.462 | – |
| `rhvoice-ignore` RHVoice 1.14.0, the core objects built at -fignore-exceptions (userdict.cpp) | 12 | 12 | 12 | 12 | 4 | 6 | 50.0% | 0.289 | 0.050 | 0.115 | – |
| `rhvoice` RHVoice 1.14.0 core (+ hts_engine and sonic in C) | 12 | 12 | 12 | 12 | 4 | 6 | 50.0% | 0.360 | 0.012 | 0.121 | – |
| `boost` Boost 1.89.0, header-only | 12 | 12 | 12 | 12 | 3 | 10 | 83.3% | 0.200 | 0.000 | 0.031 | – |
| `libc` emscripten musl libc (libc.a) | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.446 | 0.213 | 0.242 | – |
| `libc-optz` emscripten musl libc, the -Oz link's size-optimised members (libc_optz.a) | 5 | 5 | 5 | 5 | 0 | 1 | 20.0% | 0.417 | 0.222 | 0.200 | – |
| `dlmalloc` emscripten dlmalloc (libdlmalloc.a) | 8 | 8 | 8 | 8 | 0 | 3 | 37.5% | 0.583 | 0.268 | 0.221 | – |
| `compiler-rt` compiler-rt builtins (libcompiler_rt.a) | 12 | 12 | 12 | 12 | 0 | 2 | 16.7% | 0.641 | 0.522 | 0.415 | – |
| `libcxx` libc++ (libc++.a) | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.433 | 0.070 | 0.145 | – |
| `libcxxabi` libc++abi (libc++abi.a) | 12 | 12 | 12 | 12 | 2 | 6 | 50.0% | 0.326 | 0.051 | 0.110 | – |

## By size band

| band | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| tiny | 51 | 51 | 51 | 51 | 33 | 45 | 88.2% | 0.000 | 0.000 | 0.047 |
| small | 57 | 57 | 57 | 57 | 3 | 35 | 61.4% | 0.278 | 0.000 | 0.082 |
| medium | 44 | 44 | 44 | 44 | 1 | 8 | 18.2% | 0.531 | 0.224 | 0.262 |
| large | 36 | 36 | 36 | 36 | 0 | 1 | 2.8% | 0.637 | 0.299 | 0.355 |
| huge | 17 | 17 | 17 | 17 | 0 | 0 | 0.0% | 0.705 | 0.300 | 0.450 |

## By feature

A row counts under every feature it has.

| feature | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| leaf | 100 | 100 | 100 | 100 | 26 | 52 | 52.0% | 0.333 | 0.000 | 0.186 |
| loop | 74 | 74 | 74 | 74 | 0 | 6 | 8.1% | 0.611 | 0.292 | 0.353 |
| switch | 29 | 29 | 29 | 29 | 1 | 2 | 6.9% | 0.588 | 0.251 | 0.264 |
| call_indirect | 35 | 35 | 35 | 35 | 4 | 19 | 54.3% | 0.300 | 0.000 | 0.104 |
| invoke | 9 | 9 | 9 | 9 | 0 | 1 | 11.1% | 0.617 | 0.200 | 0.165 |
| throw | 12 | 12 | 12 | 12 | 1 | 2 | 16.7% | 0.616 | 0.187 | 0.145 |
| frame | 50 | 50 | 50 | 50 | 0 | 3 | 6.0% | 0.639 | 0.272 | 0.334 |
| alloca | 2 | 2 | 2 | 2 | 0 | 0 | 0.0% | 0.688 | 0.385 | 0.385 |
| inlined-frame | 13 | 13 | 13 | 13 | 0 | 0 | 0.0% | 0.744 | 0.256 | 0.314 |
| i64 | 85 | 85 | 85 | 85 | 6 | 17 | 20.0% | 0.536 | 0.200 | 0.271 |
| float | 16 | 16 | 16 | 16 | 2 | 2 | 12.5% | 0.630 | 0.336 | 0.333 |
| bulk-memory | 27 | 27 | 27 | 27 | 0 | 3 | 11.1% | 0.590 | 0.287 | 0.324 |
| select | 71 | 71 | 71 | 71 | 5 | 11 | 15.5% | 0.610 | 0.286 | 0.340 |

## Failures

None: every row lifted, compiled, linked and was found.

## Largest -Oz ratios

| id | size | target rows | raw | ratio | -Oz | ratio -Oz | features |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 7zip/4943 | 2246 | 678 | 1654 | 2.439 | 1570 | 2.316 | leaf loop i64 select |
| libqrencode/3595 | 1112 | 547 | 668 | 1.221 | 573 | 1.048 | leaf loop frame i64 bulk-memory select |
| compiler-rt/1733 | 219 | 101 | 102 | 1.010 | 89 | 0.881 | leaf i64 select |
| 7zip/2646 | 526 | 281 | 277 | 0.986 | 213 | 0.758 | leaf loop frame i64 |
| uenux2/2662 | 821 | 432 | 412 | 0.954 | 327 | 0.757 | loop float bulk-memory select |
| libqrencode/5349 | 64 | 34 | 30 | 0.882 | 25 | 0.735 | leaf loop |
| compiler-rt/6225 | 192 | 83 | 66 | 0.795 | 61 | 0.735 | leaf i64 select |
| libc/2968 | 24 | 11 | 4 | 0.364 | 8 | 0.727 | leaf frame float |
| 7zip/2630 | 421 | 211 | 172 | 0.815 | 145 | 0.687 | loop call_indirect frame i64 select |
| compiler-rt/12119 | 16 | 9 | 8 | 0.889 | 6 | 0.667 | leaf |
| compiler-rt/522 | 1361 | 675 | 451 | 0.668 | 448 | 0.664 | frame i64 select |
| vota-web/11645 | 446 | 243 | 182 | 0.749 | 156 | 0.642 | leaf loop frame inlined-frame bulk-memory select |
| openssl/294 | 2522 | 1259 | 890 | 0.707 | 806 | 0.640 | frame i64 |
| zlib/8121 | 81 | 43 | 40 | 0.930 | 27 | 0.628 | select |
| 7zip/1859 | 366 | 195 | 152 | 0.779 | 121 | 0.621 | leaf loop |
