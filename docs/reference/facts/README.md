# Measured facts

The facts this project relies on, each with the measurement or command that establishes it. Code and docs cite
these files for the evidence behind a rule; read the section a rule cites before changing what the rule protects.

Cite a fact as `docs/reference/facts/<file>.md §<id>`, for example `docs/reference/facts/link-order.md §L1`.

| file | ids | what it covers |
| --- | --- | --- |
| [toolchain.md](toolchain.md) | T1–T8 | the emsdk release, the stock image's paths, the link line, EM_JS and the packager, export order, `-DNDEBUG`, comparing bodies across links, candidate compiles |
| [link-order.md](link-order.md) | L1–L7 | the function-order law and its mechanism, the band walk, ordinal recovery, the recovered link line, TU slices |
| [app-flags.md](app-flags.md) | F1–F9 | compile flags of ecourna and uenux2 TUs, per-TU `-fPIC`, source idioms the target forced, flag-measuring traps |
| [libraries.md](libraries.md) | B1–B9 | SQLite, libcrypto, 7-Zip, RHVoice, Boost, zlib: versions, flags, root sets, the compile-diff method |
| [asn1.md](asn1.md) | A0–A4 | the ASN.1 runtime's lineage and flags, the `Modulo*` schema read from the target's data |
| [splat.md](splat.md) | S1–S7 | the splat symbol maps, their coverage, matches that verify but are wrong, the operand kinds the shifted link gives, twins in our link, a twin class's name and vtable-slot names |
| [units.md](units.md) | U1–U8 | a unit's companion files: roots declarations and stand-ins, `make_shared` roots, the matches companion objects supply, pending members in the generated files, template-default traps, what rebuilds a companion object, pure slots |
| [reading.md](reading.md) | R1–R11 | what a target body says about its source: dead arguments, `this` returns, one-scalar returns, `final`, the D0's shape, key functions, pure slots, linkage and placement from record order, code wasm-opt inlined, an unqualified type's scope |
| [workflow.md](workflow.md) | W1–W13 | Node 24, the lone and whole-link tries, a cloned build/out, build-at's directory, lost matches against the merge base, committing git rm'd paths, check_encoding after step 9, Latin-1 pipes, zsh, withdrawing a match, pnpm test, comparing objects across a header edit |
| [tool-traps.md](tool-traps.md) | X1–X7 | exported roots and inlining, probe links, zsh, fetching from the TSE site, callers of `std::to_string` at depth 2, `try-tu.sh --single` and exceptions, uenux2 record paths |
