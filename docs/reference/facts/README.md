# Measured facts

The facts this project relies on, each with the measurement or command that establishes it. Code and docs cite
these files for the evidence behind a rule; read the section a rule cites before changing what the rule protects.

Cite a fact as `docs/reference/facts/<file>.md §<id>`, for example `docs/reference/facts/link-order.md §L1`.

| file | ids | what it covers |
| --- | --- | --- |
| [toolchain.md](toolchain.md) | T1–T8 | the emsdk release, the stock image's paths, the link line, EM_JS and the packager, export order, `-DNDEBUG`, comparing bodies across links, candidate compiles |
| [link-order.md](link-order.md) | L1–L7 | the function-order law and its mechanism, the band walk, ordinal recovery, the recovered link line, TU slices, traps (the `ordinal` column is an estimate; data order is link order) |
| [app-flags.md](app-flags.md) | F1–F9 | compile flags of ecourna and uenux2 TUs, per-TU `-fPIC`, source idioms the target forced, flag-measuring traps |
| [libraries.md](libraries.md) | B1–B9 | SQLite, libcrypto, 7-Zip, RHVoice, Boost, zlib: versions, flags, root sets, the compile-diff method |
| [asn1.md](asn1.md) | A0–A4 | the ASN.1 runtime's lineage and flags, the `Modulo*` schema read from the target's data |
| [splat.md](splat.md) | S1–S8 | the splat symbol maps, their coverage, matches that verify but are wrong, the operand kinds the shifted link gives, twins in our link (also by a folded parameter), a twin class's name and vtable-slot names, what every landing changes besides its matches |
| [units.md](units.md) | U1–U10 | a unit's companion files: roots declarations and stand-ins, `make_shared` roots, the matches companion objects supply, pending members in the generated files, template-default traps, what rebuilds a companion object and the header lists a fragment sees, pure slots, a base's typeinfo, a member inline in the original |
| [reading.md](reading.md) | R1–R13 | what a target body says about its source: dead arguments, `this` returns, one-scalar returns, `final`, the D0's shape and the destructor's form, key functions and base typeinfo, pure slots, linkage and placement from record order, code wasm-opt inlined, an unqualified type's scope, a class passed by value, a `std::format` throw's constants |
| [workflow.md](workflow.md) | W1–W17 | Node 24, the lone and whole-link tries, a cloned build/out, build-at's directory, lost matches against the merge base, committing git rm'd paths, check_encoding and the index, Latin-1 pipes, zsh, withdrawing a match, pnpm test, comparing objects across a header edit, stubs at a merge, what a header rebuilds and which objects a worktree built, a match line both branches add, a header two branches add |
| [tool-traps.md](tool-traps.md) | X1–X10 | exported roots and inlining, probe links, zsh, fetching from the TSE site, callers of `std::to_string` at depth 2, `try-tu.sh --single` and exceptions, uenux2 record paths, a variant header through `--flags`, a leaf function scored alone, a try outside `build/out/try/` |
| [codegen.md](codegen.md) | C1–C3 | what a source form compiles to: the order of the stores (a delegating constructor's too), a switch over consecutive virtual members, an in-class member against an `inline` one |
