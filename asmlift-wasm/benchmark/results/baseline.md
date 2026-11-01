# Benchmark: baseline

Target `target/vota_web_wasm.wasm` (sha256 `8579ef8d1a938191…`), image `urna-emsdk:6.0.0`, 217 rows (rows.json `493929e3d712`, setups.json `01f48e2e88fa`), urna `6c1e2bef+dirty`, 2026-11-01T18:04:23.331Z. Lift 108 ms, compile and optimise 5.2 s, total 12.3 s.

Each row is lifted, compiled with `em++ -c` at its setup's flags, and scored against the target at depth 0 with callees, data addresses, the stack pointer and the indirect table canonicalised on both sides (raw); then the object is linked alone and put through the target link's wasm-opt -Oz passes and scored again (-Oz). The ratio is differing rows over target rows; exact is a -Oz score of 0. An isolated function misses what the whole-program link does to it, so no score here means byte-identical.

## Overall

| rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 217 | 217 | 217 | 217 | 42 | 94 | 43.3% | 0.407 | 0.074 | 0.188 |

## By compile setup

| setup | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz | failures |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `uenux2` uenux2, the TSE application | 12 | 12 | 12 | 12 | 3 | 6 | 50.0% | 0.370 | 0.003 | 0.142 | – |
| `uenux2-tbaa` uenux2, the directories built with strict aliasing (src/api, comum's data classes dados/md, src/app/vota, mock/app/simulador/wasm) | 12 | 12 | 12 | 12 | 4 | 4 | 33.3% | 0.432 | 0.172 | 0.186 | – |
| `vota-web` the executable TU, wasm/vota_web/vota_web_wasm.cpp: votaInit's, first on the link line | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.173 | 0.043 | 0.221 | – |
| `ecourna` ecourna (conan libecea1da310e5107) | 12 | 12 | 12 | 12 | 1 | 5 | 41.7% | 0.712 | 0.063 | 0.090 | – |
| `asn1` TSE fork of the III ASN.1 runtime and its generated Modulo* modules | 12 | 12 | 12 | 12 | 4 | 8 | 66.7% | 0.317 | 0.000 | 0.049 | – |
| `zlib` zlib 1.3.1 + minizip | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.391 | 0.116 | 0.170 | – |
| `libqrencode` libqrencode 4.1.1 | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.360 | 0.210 | 0.257 | – |
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
| tiny | 56 | 56 | 56 | 56 | 36 | 49 | 87.5% | 0.000 | 0.000 | 0.051 |
| small | 59 | 59 | 59 | 59 | 5 | 37 | 62.7% | 0.267 | 0.000 | 0.067 |
| medium | 44 | 44 | 44 | 44 | 1 | 7 | 15.9% | 0.537 | 0.224 | 0.265 |
| large | 39 | 39 | 39 | 39 | 0 | 1 | 2.6% | 0.633 | 0.303 | 0.346 |
| huge | 19 | 19 | 19 | 19 | 0 | 0 | 0.0% | 0.707 | 0.359 | 0.463 |

## By feature

A row counts under every feature it has.

| feature | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| leaf | 108 | 108 | 108 | 108 | 32 | 58 | 53.7% | 0.299 | 0.000 | 0.175 |
| loop | 80 | 80 | 80 | 80 | 0 | 5 | 6.3% | 0.599 | 0.292 | 0.338 |
| switch | 32 | 32 | 32 | 32 | 1 | 2 | 6.3% | 0.583 | 0.255 | 0.271 |
| call_indirect | 38 | 38 | 38 | 38 | 3 | 20 | 52.6% | 0.406 | 0.000 | 0.119 |
| invoke | 10 | 10 | 10 | 10 | 0 | 1 | 10.0% | 0.645 | 0.219 | 0.234 |
| throw | 15 | 15 | 15 | 15 | 1 | 2 | 13.3% | 0.673 | 0.205 | 0.208 |
| frame | 56 | 56 | 56 | 56 | 0 | 4 | 7.1% | 0.642 | 0.293 | 0.338 |
| alloca | 2 | 2 | 2 | 2 | 0 | 0 | 0.0% | 0.688 | 0.385 | 0.385 |
| inlined-frame | 17 | 17 | 17 | 17 | 0 | 0 | 0.0% | 0.768 | 0.287 | 0.317 |
| i64 | 91 | 91 | 91 | 91 | 6 | 17 | 18.7% | 0.542 | 0.227 | 0.276 |
| float | 17 | 17 | 17 | 17 | 2 | 2 | 11.8% | 0.624 | 0.287 | 0.311 |
| bulk-memory | 30 | 30 | 30 | 30 | 0 | 3 | 10.0% | 0.613 | 0.288 | 0.313 |
| select | 77 | 77 | 77 | 77 | 6 | 13 | 16.9% | 0.608 | 0.290 | 0.334 |

## Failures

None: every row lifted, compiled, linked and was found.

## Largest -Oz ratios

| id | size | target rows | raw | ratio | -Oz | ratio -Oz | features |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 7zip/4943 | 2246 | 678 | 1654 | 2.439 | 1570 | 2.316 | leaf loop i64 select |
| libqrencode/3595 | 1112 | 547 | 668 | 1.221 | 573 | 1.048 | leaf loop frame i64 bulk-memory select |
| compiler-rt/1733 | 219 | 101 | 102 | 1.010 | 89 | 0.881 | leaf i64 select |
| 7zip/2646 | 526 | 281 | 277 | 0.986 | 213 | 0.758 | leaf loop frame i64 |
| compiler-rt/6225 | 192 | 83 | 66 | 0.795 | 61 | 0.735 | leaf i64 select |
| libc/2968 | 24 | 11 | 4 | 0.364 | 8 | 0.727 | leaf frame float |
| 7zip/2630 | 421 | 211 | 172 | 0.815 | 145 | 0.687 | loop call_indirect frame i64 select |
| compiler-rt/12119 | 16 | 9 | 8 | 0.889 | 6 | 0.667 | leaf |
| compiler-rt/522 | 1361 | 675 | 451 | 0.668 | 448 | 0.664 | frame i64 select |
| vota-web/11645 | 446 | 243 | 182 | 0.749 | 156 | 0.642 | leaf loop frame inlined-frame bulk-memory select |
| openssl/294 | 2522 | 1259 | 890 | 0.707 | 806 | 0.640 | frame i64 |
| zlib/8121 | 81 | 43 | 40 | 0.930 | 27 | 0.628 | select |
| 7zip/1859 | 366 | 195 | 152 | 0.779 | 121 | 0.621 | leaf loop |
| vota-web/5944 | 599 | 315 | 245 | 0.778 | 187 | 0.594 | loop switch frame |
| libc/1169 | 65 | 34 | 20 | 0.588 | 20 | 0.588 | leaf i64 |
