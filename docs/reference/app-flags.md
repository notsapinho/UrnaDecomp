# Compile flags of the TSE application code

The two TSE trees in the target, **uenux2** (the application) and **ecourna** (a conan package of shared classes),
were compiled with different flags. This page gives the flags the build uses, where each one is set and the
evidence for it, and the source-level facts that come with them. A flag is decided by compiling the
reconstructed units with and without it and scoring them against the target, and by where the target's data sits when that
shows it, as for `-fPIC`; the per-flag measurements are in
[facts/app-flags.md](facts/app-flags.md) (§F1–§F9). The libraries' flags are in [toolchain.md](toolchain.md) §3.

## The flags

| tree | sources | flags | set in | evidence |
| --- | --- | --- | --- | --- |
| uenux2 | `src/uenux2/` | `-O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing`, no `-fexceptions` | `UENUX2_CXXFLAGS` in `src/Makefile` | facts §F6 (PIC and aliasing); the level, measured on the whole tree: [facts/levels.md](facts/levels.md) §V3; `-std=c++23` is not taken; `-std` and `-DNDEBUG` are ecourna's measurement (§F1), carried over; exceptions below |
| the executable TU, `wasm/vota_web/vota_web_wasm.cpp` | `src/uenux2/wasm/vota_web/` (unit 170, in part), first on the link line | `-Oz -fexceptions -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing` | `VOTA_WEB_CXXFLAGS` in `src/Makefile` (setup `vota-web`) | [facts/levels.md](facts/levels.md) §V1: the inline members of a class whose typeinfo sits in its data are its copies, and each flag is measured on the whole link; `-std=c++23` matches more there and is the user's decision |
| ecourna | `src/ecourna/` | `-O3 -fexceptions -std=c++20 -DNDEBUG`, no `-fPIC` | `ECOURNA_CXXFLAGS` in `src/Makefile` | facts §F1, §F5 |
| ecourna, every unit | | `+ -fno-strict-aliasing -fno-delete-null-pointer-checks -fno-strict-overflow` | `src/mk/ecourna-flags.mk` | facts §F2, §F3, §F4 |
| the stand-in and roots TUs (`src/app/`, `src/web/`, the units' `-roots.cpp`), but for `src/app/roots_cbasetype.cpp` and unit 113's roots, at `UENUX2_CXXFLAGS` | | `APP_CXXFLAGS` = `UENUX2_CXXFLAGS` at `-O2` and without `-fno-strict-aliasing`; `APP_CFLAGS` for the generated C roots | `src/Makefile` | they stand in for app code; the library templates they instantiate win the link, and the target's copies have TBAA (facts §F6) |

Both trees also take a `-ffile-prefix-map` that puts the original build directory into their `std::source_location`
records (below). `make -C src print-ECOURNA_CXXFLAGS` and `print-UENUX2_CXXFLAGS` print the values in effect;
`tools/round/try-tu.sh` compiles each candidate with the flags of the component its path is in.

Flags that make no difference on the units measured: `-std=gnu++20` vs `-std=c++20`; `-DNDEBUG` on the units (none has
an `assert`; the flag is pinned by the missing `__assert_fail` import, [facts/toolchain.md](facts/toolchain.md) §T6).
`-ffunction-sections -fdata-sections`, tried together with `-fvisibility=hidden` in a test whose method is not
recorded, changed 11 bytes of one libc helper and nothing of the units. Visibility on its own does change ecourna:
with `ECOURNA_EXTRA=-fvisibility=default` all 82 of its objects differ and 4 matches break
([facts/app-flags.md](facts/app-flags.md) §F5, §F9 item 9). `-std=c++23` is excluded for ecourna: it changes
`EncodeBase64(...).substr(0, 8)` in function 3703 through C++23's rvalue `substr() &&` overload. uenux2 takes
`-std=c++20` from that ecourna measurement; its own function 8799 differs at the tree's flags and matches with
`-std=c++23`, which the tree has not taken ([facts/levels.md](facts/levels.md) §V3). `-std=c++17` does not
compile the code (`std::source_location` and class-type template parameters are C++20).

## The error records are `std::source_location`, not a macro

The `__FILE__`-looking paths and `__PRETTY_FUNCTION__`-looking texts are **not macro output**. Every ecourna exception
constructor takes `std::source_location local = std::source_location::current()` (C++20); clang materialises one
16-byte record per call site — `{file_name, function_name, line, column}` — and the code passes the record's address as
the 4th constructor argument. `ledger/source-locations.tsv` (`tools/extract/source_locations.py`) lists the 1,939 records with
the functions that load them (1,910 referenced; the rest sit in code binaryen inlined/merged). `function_name()` is the
pretty-function text, so the declaration spelling matters: `std::string EncodeBase64(const std::vector<uebyte>&)` must
be written with `std::string` and `uebyte`, as the record shows `std::string ecourna::api::security::EncodeBase64(const std::vector<uebyte> &)`.

Class layout recovered from functions 1143/1011/710/4636/11562 (sizes confirmed by `__cxa_allocate_exception(40)`):

```
namespace ecourna::api::exception {
struct SErrorLimits { int minimo; int maximo; };               // NTTP of class type: C++20 (mangled XtlNS1_12SErrorLimitsELi1325ELi1725EEE)
class CError : public std::exception {                         // 40 bytes
  int m_codigo;                     // +4
  std::string m_mensagem;           // +8
  std::source_location m_local;     // +20  (one pointer to the record)
  unsigned m_reservado;             // +24  never written by the ctor
  std::string m_descricao;          // +28  what(): "<function_name>:<line>:<codigo> - <mensagem>", built inside try{}catch(...){}
};
template <typename E, SErrorLimits L> class CBaseError : public CError {
  CBaseError(E codigo, std::string mensagem, std::source_location local = std::source_location::current());
};}
```
`throw CSecurityError(1325, "Vetor de dados vazio.")` compiles to `__cxa_allocate_exception(40)`, `std::string(const
char*)`, the ctor through `invoke_iiiii` (ecourna, -fexceptions) or a direct call (uenux2), then `__cxa_throw(obj,
typeinfo, D0-slot)`. The 31 `Assert (<condition>)` strings are the uenux2 assert macro: `"Assert (" #cond ")"` with a
per-site code in the `api::EUeAssertError` range {3400,4200} (3409, 3449, 3467 …), thrown the same way. There is no
log macro: nothing in the target calls a logger with `__FILE__`/`__LINE__`.

## Path mechanism

`-ffile-prefix-map=/work/src/ecourna=/home/rubio/.conan2/p/b/libecea1da310e5107/b/src/ecourna` (or
`-fmacro-prefix-map`) gives an object byte-identical to compiling the file at the real path (checked with `cmp` on three
objects, and `strings` on `source_location::file_name()`). The build runs from `/work` (the urna root mounted by
`build/docker-build.sh`), so no extra mounts are needed; the ecourna include root is `-Isrc` (`#include
"ecourna/api/..."`, matching the package's `b/src` layout). uenux2 has `/work/src/uenux2` and `src/uenux2` mapped to
`/home/rubio/tse/uenux2`, and a third map, `src/ecourna` to the conan package's installed headers `…/p/include/ecourna`,
for an ecourna header a uenux2 object or a stand-in includes (`UENUX2_PREFIX_MAP` in `src/Makefile`; facts §F6,
[facts/tool-traps.md](facts/tool-traps.md) §X7).

## Exceptions: the uenux2 library trees are throw-only

Of the 808 functions that load a uenux2 `src/` record, 24 call an `invoke_*` import, and each of those is a binaryen-merged or
cross-TU-inlined body that also carries ecourna records or an `api/pattern/*.h` template the wasm TU instantiated. Per directory:
`src/api/gui` 0 of 39 files, `src/api/ipc` 0/4, `src/api/util` 1/14 (the 4.4 KB merged `CSystem::Rename`), `src/app/comum` 26/183,
`src/app/vota` 4/75 — all merged bodies. `wasm/vota_web/vota_web_wasm.cpp` and `mock/app/comum/cappinfobuilder.cpp` do have landing
pads and catch handlers (`fn 6023`: `new T()` with a cleanup pad, `fn 1561`: the IGenericFactory default `Create` throw — their records sit
in that TU's data). So: `src/api` and `src/app` were compiled **without `-fexceptions`** (emcc's default, clang `-fignore-exceptions`:
`throw` compiles to a direct `__cxa_throw`, no landing pads — not `-fno-exceptions`, which rejects the `throw` statements these TUs
contain), the executable TU with `-fexceptions` ([facts/levels.md](facts/levels.md) §V1). 707 functions of the whole
target call an `invoke_*` import.

The `mock/` tree splits the same way, by file. The record-bearing functions of `mock/app/simulador/wasm/` call no
`invoke_*` (9655 in `cwasmthread.cpp`, 3876 in `cwasmclp.cpp`), while both of `mock/app/comum/cappinfobuilder.cpp`
do (10243: 18 calls, 10212: 62); [facts/app-flags.md](facts/app-flags.md) §F6 has the command. The generic uenux2 rule
compiles all of `mock/` with `UENUX2_CXXFLAGS`, which is right for `mock/app/simulador/wasm/`; a unit in
`mock/app/comum/` measures its exception flag first.

## Measuring a flag

The probe links the reconstructed ecourna units with a given flag set and scores them pair by pair:

```
tools/round/appflags/probe.sh <name> "<ecourna CXXFLAGS>" ["<driver CXXFLAGS>"]   # build/out/appflags/<name>/x.{wasm,js,js.symbols}, ~10 s
tools/round/appflags/compare.sh <name> [--full <target fn>]                      # scores tools/round/appflags/pairs.tsv, depth 0 (APPFLAGS_DEPTH=2 for callee-aware)
tools/round/appflags/variants.sh tools/round/appflags/variants/trim.cpp "<flags>"     # V1..Vn source variants of one function, one link each
```
`pairs.tsv` maps target indices to demangled symbol-map substrings; `callee:<substring>` names the first callee of a
thunk (binaryen's merged bodies carry no name). `score_pairs.ts` normalises both modules once (depth 0: every call is
`call fn:?`, because two different links never share callee fingerprints) and picks, among same-named hits, the one
with the target's signature (D0/D2 destructors share a demangled name).
