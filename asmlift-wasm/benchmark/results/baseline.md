# Benchmark: baseline

Target `target/vota_web_wasm.wasm` (sha256 `8579ef8d1a938191…`), image `urna-emsdk:6.0.0`, 181 rows (rows.json `7823066bfafb`, setups.json `cba43edf5648`), urna `1900524+dirty`, 2026-10-31T10:42:32.954Z. Lift 113 ms, compile and optimise 4.3 s, total 10.8 s.

Each row is lifted, compiled with `em++ -c` at its setup's flags, and scored against the target at depth 0 with callees, data addresses, the stack pointer and the indirect table canonicalised on both sides (raw); then the object is linked alone and put through the target link's wasm-opt -Oz passes and scored again (-Oz). The ratio is differing rows over target rows; exact is a -Oz score of 0. An isolated function misses what the whole-program link does to it, so no score here means byte-identical.

## Overall

| rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 181 | 181 | 181 | 181 | 35 | 83 | 45.9% | 0.407 | 0.068 | 0.178 |

## By compile setup

| setup | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz | failures |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `uenux2` uenux2, the TSE application | 12 | 12 | 12 | 12 | 3 | 5 | 41.7% | 0.347 | 0.119 | 0.141 | – |
| `ecourna` ecourna (conan libecea1da310e5107) | 12 | 12 | 12 | 12 | 1 | 6 | 50.0% | 0.650 | 0.003 | 0.070 | – |
| `asn1` TSE fork of the III ASN.1 runtime and its generated Modulo* modules | 12 | 12 | 12 | 12 | 4 | 8 | 66.7% | 0.317 | 0.000 | 0.049 | – |
| `zlib` zlib 1.3.1 + minizip | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.358 | 0.156 | 0.179 | – |
| `sqlite` SQLite 3.50.4 amalgamation | 12 | 12 | 12 | 12 | 2 | 5 | 41.7% | 0.416 | 0.213 | 0.193 | – |
| `openssl` OpenSSL 3.0.17 libcrypto | 12 | 12 | 12 | 12 | 3 | 5 | 41.7% | 0.423 | 0.082 | 0.178 | – |
| `7zip` 7-Zip / LZMA SDK 21.02, single-threaded | 12 | 12 | 12 | 12 | 2 | 4 | 33.3% | 0.541 | 0.240 | 0.462 | – |
| `rhvoice-ignore` RHVoice 1.14.0, the core objects built at -fignore-exceptions (userdict.cpp) | 12 | 12 | 12 | 12 | 4 | 7 | 58.3% | 0.289 | 0.000 | 0.101 | – |
| `rhvoice` RHVoice 1.14.0 core (+ hts_engine and sonic in C) | 12 | 12 | 12 | 12 | 4 | 6 | 50.0% | 0.360 | 0.012 | 0.121 | – |
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
| tiny | 48 | 48 | 48 | 48 | 31 | 42 | 87.5% | 0.000 | 0.000 | 0.050 |
| small | 50 | 50 | 50 | 50 | 3 | 32 | 64.0% | 0.280 | 0.000 | 0.069 |
| medium | 36 | 36 | 36 | 36 | 1 | 8 | 22.2% | 0.515 | 0.191 | 0.252 |
| large | 30 | 30 | 30 | 30 | 0 | 1 | 3.3% | 0.628 | 0.294 | 0.319 |
| huge | 17 | 17 | 17 | 17 | 0 | 0 | 0.0% | 0.638 | 0.314 | 0.452 |

## By feature

A row counts under every feature it has.

| feature | rows | lifted | compiled | -Oz linked | exact raw | exact -Oz | exact share | median ratio | median -Oz | mean -Oz |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| leaf | 89 | 89 | 89 | 89 | 25 | 48 | 53.9% | 0.333 | 0.000 | 0.171 |
| loop | 64 | 64 | 64 | 64 | 0 | 5 | 7.8% | 0.553 | 0.289 | 0.329 |
| switch | 22 | 22 | 22 | 22 | 1 | 1 | 4.5% | 0.602 | 0.255 | 0.277 |
| call_indirect | 37 | 37 | 37 | 37 | 4 | 20 | 54.1% | 0.305 | 0.000 | 0.114 |
| invoke | 9 | 9 | 9 | 9 | 0 | 2 | 22.2% | 0.614 | 0.200 | 0.197 |
| throw | 12 | 12 | 12 | 12 | 1 | 3 | 25.0% | 0.601 | 0.203 | 0.201 |
| frame | 44 | 44 | 44 | 44 | 0 | 3 | 6.8% | 0.628 | 0.272 | 0.315 |
| alloca | 2 | 2 | 2 | 2 | 0 | 0 | 0.0% | 0.688 | 0.385 | 0.385 |
| inlined-frame | 12 | 12 | 12 | 12 | 0 | 0 | 0.0% | 0.789 | 0.272 | 0.301 |
| i64 | 82 | 82 | 82 | 82 | 6 | 18 | 22.0% | 0.531 | 0.218 | 0.266 |
| float | 14 | 14 | 14 | 14 | 2 | 2 | 14.3% | 0.539 | 0.268 | 0.286 |
| bulk-memory | 23 | 23 | 23 | 23 | 0 | 4 | 17.4% | 0.536 | 0.255 | 0.262 |
| select | 63 | 63 | 63 | 63 | 4 | 10 | 15.9% | 0.600 | 0.255 | 0.317 |

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
| libc/1169 | 65 | 34 | 20 | 0.588 | 20 | 0.588 | leaf i64 |
| sqlite/1184 | 414 | 215 | 155 | 0.721 | 125 | 0.581 | leaf loop frame i64 |
| openssl/2526 | 2088 | 1109 | 845 | 0.762 | 631 | 0.569 | loop frame alloca i64 bulk-memory select |
| openssl/920 | 985 | 529 | 344 | 0.650 | 299 | 0.565 | leaf loop select |
| compiler-rt/907 | 1236 | 588 | 379 | 0.645 | 326 | 0.554 | frame i64 select |
