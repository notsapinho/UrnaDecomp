# How to decompile a function

This page walks one target function from its disassembly to a match in `splat/matched.txt`. It assumes a working
checkout: the pinned image built, `asmlift-wasm/` installed and the skeleton linked once
([getting-started.md](getting-started.md)). Terms in *italics* are defined in the [glossary](glossary.md).

Commands run from the repository root, except `pnpm wasm …`, which runs from `asmlift-wasm/`. Every command that
compiles goes through docker and needs `TMPDIR=/tmp` on macOS, because docker cannot mount the default
`/var/folders` temp directory; the commands below carry it. Every command that runs the toolkit needs Node 24 first
on PATH: `pnpm wasm …`, `tools/round/try-tu.sh` and the census and splat make targets of steps 7 to 10. Under a newer
Node they stop with `Abort trap: 6` and nothing else ([getting-started.md](getting-started.md) §1,
[facts/workflow.md](reference/facts/workflow.md) §W1).

The example throughout is target function 1931, `comum::CRdvVota::Candidato`, which landed as
`src/units/13-uenux2-crdvvota.mk`. It is already matched, so repeating it needs the landed copy out of the way
(step 5 says how).

To match several functions at once with Claude Code, run `/decompile-functions`
([.claude/commands/decompile-functions.md](../.claude/commands/decompile-functions.md)): it runs this loop in one
worktree per function, verifies each match with a second agent, lands the matches as step 10 says, deletes each
worktree once its lane is landed or dropped ([agents.md](agents.md) "Worktrees"), and collects where this page fell
short.

## The loop at a glance

| step | command | done when |
| --- | --- | --- |
| 1. pick | `splat/scan.tsv`, `ledger/source-locations.tsv` | you have a target index and know its source file |
| 2. read | `pnpm wasm fn` / `pnpm wasm bundle` | you know what it calls, loads and belongs to |
| 3. lift | `pnpm wasm lift … --check` | you have compilable C++ to rewrite |
| 4. iterate alone | `tools/round/try-tu.sh --single` | the body is close enough to try in the whole program (a function that throws with `std::format` skips to step 5: step 4 says why) |
| 5. conclude in the whole link | `tools/round/try-tu.sh <tu> --targets …` | the report pairs the target function with your symbol, or `splat-remap` against the try link says `IDENTICAL` |
| 6. land | sources under `src/`, a fragment in `src/units/` and its row in the README's table, `make -C src link` | the skeleton links with the unit |
| 7. census | `make -C src census` | `ledger/functions.tsv` and its snapshot are rewritten |
| 8. symbols | `make -C src splat-symbols` | the symbol file names the unit's new functions and data |
| 9. match | `make -C src splat-match` | `git diff splat/matched.txt` shows your function, and its stub is gone |
| 10. build and commit | `make -C src splat`, `git commit` | the build prints the target's sha256 with the new match count |

Steps 6 to 10 run in this order, and this page is the one place that states it. Each step reads what the one
before it wrote: the census pairs the new link with the target; the symbol file and the scan take names and
candidates from that census (`ledger/functions.tsv`); the new matches come from the scan; the build verifies every match.

## 1. Pick a function

A *function index* counts imports first: the target's imports are 0–135, so its first defined function is 136
([the subject](glossary.md#the-subject)).

The work list is `splat/scan.tsv`, committed with every new match: one row per target function with its verdict
against our current link ([status.md](status.md) "What is left" counts them). Its columns:

| column | holds |
| --- | --- |
| `index` | the target function index |
| `symbol` | the name of our candidate body, or the target's own symbol when there is no candidate |
| `ours` | the candidate's function index in our plain link, `-` when there is none |
| `source` | how the scan found the candidate: `symbol` (the symbol file names it), `ledger` (the census paired it) or `content` (its re-pointed bytes are the target's) |
| `verdict` | `match`, `differs`, `unresolved` or `no-candidate` ([scan verdicts](glossary.md#the-splat-build)) |
| `detail` | for `differs`, the first instruction that differs on both sides, with what our operand resolves to; for `unresolved`, the operand with no target counterpart |
| `size` | the target body's size in bytes |
| `ledger_kind` | the census *tier* of the target function's best pair |
| `group` | its component, else its owner (`app`, `unknown`) |
| `tried` | how many candidates the scan re-pointed |
| `object` | the input our candidate is compiled from, as the link map names it |

Start with TSE code: its `differs` rows have a body of ours already, and the work is C++ (the components are
listed in [status.md](status.md) "By component"):

```sh
python3 -I -B tools/round/pick_pool.py --differs | less     # index, symbol, detail, size, group, object; smallest first
```

It keeps the `differs` rows of TSE groups whose body was compiled from `src/uenux2`, `src/ecourna` or `src/asn1`
(the `object` column). The group alone would also list library bodies that only TSE code calls, since `group` says
who uses a function (below): over a third of the TSE-group `differs` rows are not TSE code but RHVoice, OpenSSL,
7-Zip and libc++ bodies, binaryen's merged ones and the `src/app` stand-ins', and they are most of the smallest.

Two kinds of row the filter keeps are not a TSE source to fix. A standard-library template a TSE object instantiates
is libc++'s code, and what differs is which copy binaryen keeps or merges ([Library functions](#library-functions)):

```sh
python3 -I -B tools/round/pick_pool.py --differs | awk -F'\t' '$2 ~ /^_ZNSt3__2/ {print $1, $5, $6}'
# 2125 vota app/ecourna/app_dados_processoeleitoral_cconfiguracaomunicipios.cpp.o
# 244 comum app/asn1/BERDecoderPartial.o
# 3517 ecourna app/ecourna/api_compression_icompressor.cpp.o
```

And a row whose symbol names another class than the target's vtable is a body the census paired from a sibling
class, one vptr apart: 10919 and 10918 are listed as `_ZN3api20CTextFieldDoubleLineD2Ev` and `…D0Ev`, but they are
slots 0 and 1 of `api::CTextFieldPaper`'s vtable and have their stubs in `ctextfieldpaper.cpp` (the slot table below
shows it). That function is unwritten.

The other pool is the functions not written yet, which have a comment stub in their tree:

```sh
python3 -I -B tools/round/pick_pool.py src/ecourna      # or src/uenux2, src/asn1, --tse for all three; --min/--max in B
```

It prints `index verdict size group file:line` for each stub of 40 to 600 B, smallest first. Their verdict is mostly
`no-candidate`: the scan found no body of ours for it, as the symbol file names none, the census paired none, and no
unmatched body of ours re-points into it. `no-candidate` is not the same as unwritten. A function can be written and
still have no body in our link, two ways:

- **Compiled and dropped.** Nothing in our link reaches it, so wasm-ld leaves it out. Target 2767,
  `ecourna::api::io::CFile::Flush`, is defined at line 82 of `src/ecourna/api/io/cfile.cpp`, whose object the link
  holds, and its three target callers (5736, 5737, 7174) are not written: `awk -F'\t' '$1==2767 {print $1, $5}'
  splat/scan.tsv` prints `2767 no-candidate`, and `LC_ALL=C /usr/bin/grep -c CFile5Flush
  build/out/wasm-map/vota_web/names.tsv` prints 0. A whole unit can sit so: what its objects define minus the link's
  names (`wasm-objdump -x -j linking <object>` against column 2 of `names.tsv`) lists them. Such a function pairs once a
  caller lands or the unit's `-roots.cpp` reaches it the way the target does (step 6).
- **Inlined into the one caller our link gives it.** binaryen inlines a function with one call site (step 3), so it
  has no index of ours until a second caller lands. A library function is the usual case: libc's `round` (2953) was
  `no-candidate` while one RHVoice function called it, and became a match, with no source of its own, when a TSE unit
  added a second caller. Look for its call in the object of a caller the scan already names.

The stubs tell these apart from an unwritten function. `tools/round/stubs.py` writes no stub for a function it finds
code of ours for, and `python3 -I -B tools/round/stubs.py --report` counts those by reason; a body the census paired
counts only when its symbol names the function's own class ([src/README.md](../src/README.md) "Stubs" has the rule). So a
`no-candidate` row with a stub is usually unwritten. A row without one usually has code to fix, or is a pending
member (steps 5 and 9), or one of the two kinds above.

The `group` column is the function's *component*, and a component says who uses a function, not where its code
lives. 238 uenux2 functions are in group `ecourna`, because they throw ecourna's `CBaseError<…>` template with a
uenux2 enum (`1708 comum::CCargos::Next`, for one); their stubs are in `src/uenux2/`. Go by the tree that holds
the stub, not by the group ([component and owner](glossary.md#component-and-owner)). A TSE function that loads no
string, vptr or typeinfo has group `app`, and `stubs.py` writes stubs for the TSE components only, so it is in neither
pool: it reaches you as a callee or a table slot of a TSE function you read (step 2). 10255, the thread routine
`api::CThread::Start` passes by table slot, was found that way (`awk -F'\t' '$1==10255 {print $1, $5, $9}'
splat/scan.tsv` prints `10255 match app`).

The third verdict with work left, `unresolved`, is in neither pool: 817 rows at ee595de, 237 of them compiled from a
TSE tree. Each has a body of ours, and its `detail` names the operand that has no target counterpart:

```sh
awk -F'\t' 'NR>1 && $5=="unresolved" && $11 ~ /^app\/(uenux2|ecourna|asn1)\// {print $1, $7, $6}' splat/scan.tsv | sort -k2 -n | less
```

A callee that "has no target function" is one of two things. Either the target inlined it everywhere, and the
source defines it where ours keeps it out of line: 9484, `ecourna::api::security::ISymmetricCipher`'s destructor,
calls `CAesKey`'s destructor, which `src/ecourna/api/security/isymmetriccipher.cpp` line 9 defines out of line, and
the target has no such function. Or it is a `byn$mgfn-shared$` body: binaryen merged the function with others of its
shape (*mgfn*), and the target merged another set, so the fix is to write the missing members of the target's set,
which can belong to another component. 9597 and 9810, two RHVoice destructors, call such a body of ours; the target's,
3904, has a third caller, 12014, a destructor of `api::CSubReport` (`pnpm wasm fn ../target/vota_web_wasm.wasm 3904`
prints `;; callers (3): 9597 9810 12014`), so the library rows wait for that TSE class.

A `differs` row of a library component is a different job: see [Library functions](#library-functions) below
before taking one.

Then find the function's source file. The target's `std::source_location` records usually name the file, its line
and the full signature:

```sh
awk -F'\t' '$6 ~ /(^|,)1931(,|$)/ {print $2, $3, $5}' ledger/source-locations.tsv
```

The path under `/home/rubio/tse/uenux2/` or `…/libecea1da310e5107/b/src/ecourna/` is where the file goes under
`src/uenux2/` or `src/ecourna/`, and that tree's flags compile it; the *component* (`ledger/func-attribution.tsv`)
can name another tree ([component and owner](glossary.md#component-and-owner)).

A TSE function not decompiled yet usually has a *stub* in that tree, a generated comment where the evidence says the
function sat ([src/README.md](../src/README.md) "Stubs"). Find it by its index:

```sh
LC_ALL=C grep -rn '^// f7010 ' src/uenux2 src/ecourna src/asn1     # the files are Latin-1: LC_ALL=C reads them as bytes
# src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:11:// f7010 · 683 B · unmatched · name unknown
```

(In an agent's shell `grep` can be a shell function that prints nothing here; `/usr/bin/grep` is the real one.)

The line under it is the stub's signature. It names the function only when `splat/symbol_addrs.txt` does; today
no stub does, so each reads `f<index>(<wasm types>)`. Get the name from the records (the `awk` above), from the
vtable slot the `fn` readout gives (step 2), or from `ledger/vtables.json`. A record names the function that holds
the throw, and that can be an inlined callee: f7010 has records for both `CVotacaoStateAudio::ProcessTick` and
`CVotacaoStateAudio::IniciarEsperaFimAudio`, so one of the two is inlined into it. A slot that a base class fills
with a default of its own has no record, but its overriders in the same slot of the derived classes' vtables may have
one, and that names the slot. For a base and a slot number, the records of every derived class's function there:

```sh
python3 -I -c "import json,csv,sys; vt=json.load(open('ledger/vtables.json')); cl={c['name']:c for c in json.load(open('ledger/classes.json'))['classes']}; base,k=sys.argv[1],int(sys.argv[2]); d=lambda n: n in cl and bool(cl[n]['bases']) and (cl[n]['bases'][0]['name']==base or d(cl[n]['bases'][0]['name'])); fs={e['functions'][k] for e in vt if d(e['class']) and len(e['functions'])>k}; [print(r[5], r[4]) for r in csv.reader(open('ledger/source-locations.tsv'), delimiter='\t') if len(r)>5 and any(f.isdigit() and int(f) in fs for f in r[5].split(','))]" comum::CAppState 3
# 7352 virtual bool vota::CEleitorVotando::NeedChangeState()
# 11858 virtual bool vota::CDefineRotaPosReinicio::NeedChangeState()
```

`comum::CAppState`'s slot 3 (7480) is `NeedChangeState`. Take a `virtual` record only: a non-virtual name there is a
callee inlined into the overrider. When none of these names the function, step 3's "Names no evidence gives" says how
to choose a name and mark it.

A class's virtual members are its vtable's slots, and a member's stub can sit in the file of a function inlined into
it, so a file's stubs miss some of them. Each slot of a class, with its scan verdict, the scan's symbol and its stub:

```sh
python3 -I -c "import json, sys; [print(n, f) for e in json.load(open('ledger/vtables.json')) if e['class'] == sys.argv[1] for n, f in enumerate(e['functions'])]" 'api::CTextFieldPaper' |
  while read n f; do printf '%s\t%s\t%s\t%s\n' $n $f "$(awk -F'\t' -v f=$f '$1==f {print $5, $2}' splat/scan.tsv)" \
    "$(LC_ALL=C /usr/bin/grep -rn "^// f$f " src/uenux2 src/ecourna src/asn1 | LC_ALL=C cut -d: -f1,2)"; done
# 0	10919	differs _ZN3api20CTextFieldDoubleLineD2Ev	src/uenux2/src/api/gui/ctextfieldpaper.cpp:8
# 1	10918	differs _ZN3api20CTextFieldDoubleLineD0Ev	src/uenux2/src/api/gui/ctextfieldpaper.cpp:11
# 2	10920	no-candidate -	src/uenux2/src/api/gui/ctextfieldpaper.cpp:5
# 3	218	match _ZN12_GLOBAL__N_112probe_client4doneEv
# …
# 7	11014	no-candidate -	src/uenux2/unplaced.cpp:3478
```

A slot can hold a body many classes share: 218 here is one empty `(i32)->()` function that fills 126 slots of the
target's table (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -c 'ref.func:218$'`). A slot that
is `no-candidate` with no stub is usually a pending member of a landed unit (step 9).

A stub marked `placement: link order` has no record that gives it a line: its file comes from its class's vtable
or vptr. A stub in a tree's `unplaced.cpp` has no evidence for any file (step 3 says where its code goes then).
In `src/ecourna/` every stub is one of these two kinds. Most ecourna functions that have records are written
already, so the record leads to code, not to a stub. A stub can also sit over code we have: `stubs.py` cannot see
a non-virtual function that has no record. The stub f5158 in `src/ecourna/unplaced.cpp` is
`ecourna::api::util::CStringUtils::ToLower(std::string&)`, which `src/units/12-ecourna-api-sql-sqlite-externs.cpp`
defines (its header comment names fn 5158); the scan's row is a census pair with that body, `unresolved` on a static
of ours. Before you write a stub's function, read its `fn` readout and search our sources, the units' companion files
included, for that class's constructor, destructor or method.

A stub in `unplaced.cpp` has no evidence for any file only while no file is named after its class: `stubs.py` puts a
class's stubs in `<class in lower case>.cpp` of the tree as soon as that file exists, so a unit that creates
`cwasmscreen.cpp` for another class's members sees `simulador::CWasmScreen`'s stubs move into it at step 9. The tree
of an `unplaced.cpp` stub is no more evidence than its file: `stubs.py` takes it from the function's component
(`tree_of` in `tools/round/stubs.py`), which says who calls the function (below). Decide the tree, and so the flags,
from the callers' records and from the landing pads: a call that can throw while a local with a destructor is alive
goes through `invoke_*` in ecourna's and the ASN.1 runtime's code and directly in uenux2's (`grep -c invoke_` of the `fn`
readout, [reference/app-flags.md](reference/app-flags.md) "Exceptions"). 5449 is in `src/ecourna/unplaced.cpp`, group
`ecourna`, because it calls ecourna's `CStringUtils::ToByte`; it calls it with a `substr` temporary alive and no
`invoke_`, and its callers are `api::EncodeTime` (3643, `ctime.cpp`) and `api::CDateTime`'s constructor (5475,
`cdatetime.cpp`): uenux2 code, which unit 24 writes in `src/uenux2/src/api/util/ctime.cpp`.

A stub is only a comment: the target's bytes never enter the build, and there is no `INCLUDE_ASM`
([reference/include-asm.md](reference/include-asm.md) says why). Until your C++ replaces it, the function's bytes
come from its piece in the splat build.

## 2. Read it

```sh
cd asmlift-wasm
pnpm wasm fn ../target/vota_web_wasm.wasm 1931
```

`fn` prints the disassembly, a *folded readout* (the stack replayed into expressions), the strings it loads, its
callers and callees with their components and best pairs, and the vtable class and slot it fills
([the toolkit](glossary.md#the-toolkit)). The "strings referenced" list reads every `i32.const` in the data range
as a pointer, so an error code can show up as a string (1931's `4725` is an error code, not "Tipo de
identificador…"). A call made inside a `try` goes through an emscripten `invoke_<sig>` import whose first argument
is a table slot, and `fn` lists such a slot as a string too, with only `import:invoke_…` among the callees. The
lifter (step 3) names the function behind each slot: `invoke_iii(6708 /* &f339 */, …)`. A function pointer passed as
a plain argument (a thread routine, a comparator, a callback) is a table slot as well, and neither `fn` nor the lift
names it: 1684, `api::CThread::Start`, passes 4527 to `IThreadImpl::Create`, and `fn` lists `4527 (+22 into 4505)
"Falha ao obter valor do semáforo: {}"`. An `invoke` says the callee could throw when emscripten made the call, which
is before binaryen simplified it: a callee whose final body cannot throw had a call that could, such as a
`std::mutex::lock()` ([facts/reading.md](reference/facts/reading.md) §R15). The element section gives the function
behind a slot, and it counts among the callees:

```sh
wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[4527\] '
#   - elem[4527] = ref.func:10255
```

`ledger/callgraph.tsv` holds direct calls only, so it misses such a callee too. `pnpm wasm bundle`
writes the same readout for a list of functions into `ledger/bundles/<name>.md`, which is how to read a whole
class at once. `ledger/classes.json` and `ledger/vtables.json` give the class's RTTI name, bases and virtual slots,
the starting point for its layout. They do not say whether the class is `final` or its destructor out of line; step
5 reads both from the destructors' bytes. `fn` lists a function's direct callers; the functions that store a class's
vptr (`vptr` in `ledger/vtables.json`, the vtable's address plus 8) are found in the split's pieces after a splat
build, constant loads only (an address computed from a base is missed):

```sh
/usr/bin/grep -rlE 'i32\.const 1599000($|[^0-9])' build/out/splat/pieces/asm     # comum::asn::CConversorHashArquivo's vptr
# build/out/splat/pieces/asm/comum/10266.wat
```

A throw that builds its message with `std::format` stores two i64 constants that spell the call
([facts/reading.md](reference/facts/reading.md) §R13): `(length << 32) | address` of the format string, whose text
`ledger/strings.tsv` has at that address, and the argument types packed 5 bits each, the first argument lowest, as
libc++'s `__arg_t` numbers them (3 `int`, 6 `unsigned`, 12 `const char*`, 13 a string). 11050 stores
`103079218254`, `24 << 32 | 3150`, the 24 bytes `"Operação desconhecida {}"` at 3150, and `3`: one `int`.

A by-value member whose type no header of ours defines needs that header before the class compiles: write it with
the data members at the offsets the bodies give and declarations only of the members a record names, say in its
comment that the layout is all that is recovered, and claim it like any new file ([agents.md](agents.md)); the type's
own `.cpp` stays a stub file until its functions are written. A member of that type whose code a function you write
holds inlined is the exception: define it in the header, named as step 3 says when no record names it, since the
bytes are then its evidence and the function cannot be written without it. When the target holds that code inlined in
two functions, write it so that clang inlines it (step 3, "Code binaryen inlined from another function").

A type with a vptr is a second exception. A destructor you write that inlines the member's destructor stores the
member's vptr, so the member's vtable must link, and each of its slots needs a definition. Define in the class a slot
whose target body you can read (`api::CFixedText`'s two `IText` overrides are one-line reads, 1139 and 1661, in
`src/uenux2/src/api/gui/cfixedtext.h`), and trap the others in the `-pending.cpp` ("A member inline in the original" in
[src/units/README.md](../src/units/README.md)). With the slots declared only, the object references an undefined
`_ZTVN3api10CFixedTextE`.

A class your bodies need complete only to call a base's virtual slot through a pointer (a `std::shared_ptr` member
whose `Slot2()` you call) gets its head alone: the class and the base clause RTTI gives, with a comment that no member
is reconstructed, as `src/uenux2/src/api/gui/cinteractiveform.h` does. Its `sizeof` is then wrong, so nothing may
construct it; the first unit that needs a member adds the data members and the records' declarations as above.

The wasm parameters follow the C++ ABI. A member function takes `this` first. A function that returns a class by
value returns nothing in wasm and takes the address of the result as a hidden parameter before everything else, so
target 9131, `MunicipioZona CConversorMunicipioZona::DoConverte(const CMunicipioZona&) const`, has the wasm type
`(i32 i32 i32)->()`: `p0` is the result, `p1` is `this`, `p2` is the argument. A trivially copyable class that holds
one scalar is the exception: it comes back as that scalar, so 3641, `CTime CTime::operator-(int) const` with `CTime`
one `size_t`, is `(i32 i32)->(i32)`. A class passed by value is likewise the address of a copy the caller makes,
unless it is one scalar: a by-value `std::unique_ptr` is the raw pointer. libc++'s `std::shared_ptr` is trivial-ABI
in this build, so the callee owns the copy, and a constructor that moves one into a member copies its two words and
writes nothing back (5587, `comum::CParteCargos`'s), where a `&&` parameter would be nulled and a `const &` one's
count incremented. Read a parameter's form from what the callee writes to it. When the callee writes nothing (an
empty override), only its callers show the form, and only in part: a copy a caller makes just before the call is a
by-value parameter or a temporary that a conversion binds to a `const &` (a `std::filesystem::path` or a literal
passed for a `const std::string&`), so find the argument's own type before reading the copy. 2890 copies a
`std::filesystem::path` into a string before calling `api::IPaper`'s slot 8 (`pnpm wasm fn ../target/vota_web_wasm.wasm
2890`), which `const std::string&`, `std::string` and `std::filesystem::path` by value all give. Only a missing copy,
for an lvalue of the parameter's own type, rules out by-value; mark what is left as chosen. binaryen changes the type
further ([facts/reading.md](reference/facts/reading.md) §R1–R3, §R12):

- its dead-argument elimination removes a parameter every caller passes as the same constant and puts the constant
  in the body: the record of 5890, `void comum::ValidarUE(IInterfaceSavd &, ESavdAplic, const std::string &)`, has
  three parameters and the wasm type `(i32 i32)->()` two. So a constant the body stores can be an argument of the
  source; write the parameter, and give the roots callers that constant (step 6).
- a constructor and a non-deleting destructor return `this` in the object, and the same pass drops a result no caller
  read: 5526, the `api::CMovie` constructor, is `(i32 i32 i32)->()` in the target and `(i32, i32, i32) -> i32` in
  our object. A stub's `void` is the target's type, so it says nothing of the source's result; a roots file declares
  such a function with the object's `int` result (`src/units/README.md` "Companion files").

For a virtual function, take the signature from the base class that declares the slot (the `fn` header names the
vtable class and slot), and from the overrider's records where they disagree: a header of ours is a reconstruction
too. `src/asn1/asn1.h` line 3206 declares `virtual int visit(int index, const ASN1_STD string& path, AbstractData*
data, unsigned position, unsigned length) = 0`, while 11442's record reads `virtual
ASN1::IAbstractVisitor::EVisitorResult comum::asn::CVisitanteFoto::visit(int, const std::string &, ASN1::AbstractData &,
size_t, size_t)` (`awk -F'\t' '$6 ~ /(^|,)11442(,|$)/ {print $5}' ledger/source-locations.tsv | head -1`). An override
spelled as the record does not override the header's slot, and one spelled as the header has a name the record
contradicts. Fix the header when no other active stage claims it, even one every unit of a tree compiles: claim it,
keep the objects the edit rebuilds and compare them afterwards ([agents.md](agents.md) "Shared build outputs"), and
check that its matched users still verify (step 10). When another stage holds it, keep the member pending (step 5) and
report the difference.

For the ASN.1 converters there are two bases, and the namespace of the base's RTTI name in `ledger/classes.json`
says which: ecourna's
`ecourna::api::asn::IConversorASN<ENTIDADE, DADO>` in `src/ecourna/api/asn/iconversorasn.hpp` (slot 3 is
`DoDeconverte`), and comum's `comum::asn::IConversorASN<ENTIDADE, DADO>` in
`src/uenux2/src/app/comum/asn/iconversorasn.h` (slot 3 is `DoDesconverte`). Slot 2 is `DoConverte` in both.

## 3. Start from the lifter

```sh
TMPDIR=/tmp pnpm wasm lift ../target/vota_web_wasm.wasm 1931 -o /tmp/lift --check
```

This writes `/tmp/lift/1931.cpp`, which `em++` compiles. It is a starting point, not code to commit. Rewrite it
into plausible original source: the project's real classes and headers, source types for integers and pointers,
no `volatile` stores, no empty `asm` barriers, no `goto` that a loop or an `if` would express. Save the result where
it will land, at the path the `std::source_location` record names: here
`src/uenux2/src/app/comum/dados/crdvvota.cpp`. Its path then tells `try-tu.sh` its component and flags.
`asmlift-wasm/README.md` "lift" lists each workaround the lifter emits and how to take it back out. A function whose
file a landed unit already compiles goes into that file, and the unit grows (step 6). A unit whose matches are all
code the compiler writes from a header, emitted in a companion object (an inline default of a virtual member the
roots file takes the address of, an implicit destructor emitted with the vtable in the `-pending.cpp`), has no source
of its own: unit 19 matches `api::IScreen::GetFontMetrics` from its roots object and its fragment holds that rule
only. The file the class's records name then stays a stub file; `src/units/README.md` "What a fragment holds" says
what such a fragment holds.

**A form chosen for the code it gives.** The lift keeps the target's order of loads and stores, and the source has
to give it back. That order is evidence of the source's form ([facts/codegen.md](reference/facts/codegen.md) §C1):
stores whose values were all read first come out in the reverse of the source's order. A lift whose stores run
backwards over a struct (+6, +4, +2, +0 in 11067, `api::CLineField::Rect`) comes from values read into locals before
the aggregate is built; a constructor that moves every argument out before its first store into the object and
stores the vptr last (3660, `api::CSubReport`'s) delegates to a constructor that takes them by value again. A call
through `vtable[N + 4*x]` after an unsigned range check of `x` is a `switch` whose cases call consecutive virtual
slots, its `default` the code under the check (§C2, 11050); write the switch, not a table of member pointers. Such
a form is source when it is ordinary C++ in the project's types: a local that holds a value the function reads, an
order of evaluation, a temporary, a delegating constructor. A construct whose only purpose is to steer the compiler
is scaffolding and never lands: `volatile`, an `asm` barrier, an attribute, a `may_alias` cast, a `goto`. When a form
stands in for a header that is not the original's (an aggregate where the target has a constructor), say so in the
fragment's header comment.

An order is evidence only where the forms you compare give different orders in the target function's own shape:
compile both there. The vptr store before a member's says the base's constructor sets the member, the other way the
derived class's, and in some call shapes both layouts give one order (§C1, "Which class holds a member"); two
assignments that meet after a branch keep the source's order only between equal costs (§C1). Four near-identical runs
in a lift can be one loop the target's level unrolled: `simulador::CWasmScreenMT::Refresh` (8746) is a range-for over
four lines, and four explicit appends give another block placement ([facts/levels.md](reference/facts/levels.md) §V3,
unit 78's fragment). An inlined library algorithm leaves no name: its body is evidence of what it computes (a search's
direction, a halving), not of the call, so write `std::upper_bound` when it is the plain way to say it and list the
hand-written loop that gives the same bytes beside it (unit 13's fragment does).

To measure "the same bytes" for one function of a TU, compare that function's disassembly between the two objects
with the object-local numbers masked: the `call` and `global.get` indices, and every `i32.const` added to
`global.get __memory_base`, an offset into the object's own data that moves when another member's literal does
(§C1, "What the object shows and what it does not"). `cmp` of two objects compares the whole TU, and a variant of one
member then fails it. Change one occurrence per variant: a text substitution that matches twice rewrites another
member too.

The lifter names a callee from the ledger's pairs, not from the symbol file, so a callee can be `extern "C" …
f219(…)` although `splat/symbol_addrs.txt` names it (`_ZN4ASN18SEQUENCEC2EPKv = func:219;`, the
`ASN1::SEQUENCE` constructor). Look a callee up there by `func:<index>;` before you guess.

**A callee can be a twin.** binaryen merges byte-identical functions, in the target and in our link alike, and keeps
one name for the body. So a callee's name in `splat/matched.txt` or the symbol file can be another function's that
compiles to the same bytes: 760 is matched as `std::vector<std::pair<unsigned long, unsigned long>>::push_back(&&)`,
and in the target it is also the `push_back` of another vector of an 8-byte element: 11361, the converter of
`comum::asn::CConversorSituacoesEleicoes`, which builds a `std::vector<comum::md::CSituacoesEleicoes>`, calls 760
(`pnpm wasm fn ../target/vota_web_wasm.wasm 11361`, from `asmlift-wasm/`, shows `call 760` at +0x93). Write the call your source
makes. If your instantiation compiles to the same bytes, our link merges it into the matched body and the call
re-points to the target's function; if it does not, the target has no such body and the caller cannot match
with that call. When your object comes first in the link, its symbol becomes the survivor's name and the existing
match line has to follow it (step 10, "A twin whose name moved"; [facts/splat.md](reference/facts/splat.md) §S6).

**Code binaryen inlined from another function.** The lift writes inlined code in place, whether clang inlined it
(the source defined it in the class or in the header) or wasm-opt did (the source defined a separate function, which
had one caller in the link and so has no target index of its own). These signs say wasm-opt
([facts/reading.md](reference/facts/reading.md) §R10): a second stack-pointer prologue inside the body (`l3 =
i32.sub(g0, 32); g0 = l3;` in 3641, `operator+=` inlined into `operator-`), or for a callee that calls nothing a
second `i32.sub(g0, N)` with no `g0 =` after it (2073), so look for the second read of `g0`, not the second write;
byte arguments loaded with `i32.load8_u` into locals before the stores that use them, as for a call
(`comum::md::CSituacoesEleicoes`'s constructor inside 11361); a value read back from the frame right after it was
stored (8533), which clang would have forwarded unless a call it could not see into stood between; and a by-value
`std::shared_ptr` copied word by word out of a frame temporary into the object (11946). Write such a function out of
line and leave it unrooted, so that it has one caller in our link too: as a member in its class's `.cpp` when it reads
the class's state, else as a free function in the namespace of its caller's class, in a `.cpp` you choose and name
as chosen. When clang would inline it or read its attributes in the caller's TU (any small function), it must be in
another TU than its caller: 8533's tone sequences are in `api/hwil/ibeep.cpp`, its caller in `cwasmbeep.cpp`.

A caller whose inlined callee has an inlining of its own pending (a constructor inlined into a constructor, both
inlined into a member) can depend on the order of the two objects in the link: with the callee's object first,
binaryen's inliner took the inner callee into the caller one round later, and the caller's locals came out otherwise
(why, binaryen's source in the image does not show). `api::IImpressoraRelatorios::SetStyle` (10881) differs from the
target in local numbers only with `eueprintererror.cpp` before `iimpressorarelatorios.cpp` in its fragment's sources,
and matches with the caller's object first; the objects between them are free. So when two bodies differ in locals only, try one link with the
caller's object ahead of the callee's before hunting a source form, and say in the fragment that the order is
measured (unit 80's fragment does).

binaryen inlines a function with one call site only, so the same inlined code in
two target functions means clang inlined it in at least one TU: an observer's detach (a lock over an erase of the
observer, `call 736` and `call 150`) is inlined in both 2778 and 5902, the destructors of `api::CDSImageField` and
`comum::CInfoMTLCD`. Write such a member so that clang inlines it, with the `inline` keyword, which raises the cost
up to which clang inlines (§R5); a form clang leaves out of line matches only while it has one caller, and drifts when
the second lands ([facts/codegen.md](reference/facts/codegen.md) §C3 links such a detach both ways, with one caller and
with two).

**When no record names the file**, as for every stub in `unplaced.cpp`, choose the path the way the landed
units do, and say why in the fragment's header comment (step 6):

1. a header of the class that already exists names the directory (`src/ecourna/app/dados/asn/resultadournacadastro/`
   for `CConversorDadosComparecimentoCifrado`);
2. else the directory of the objects linked beside a function only the class's own object defines: a constructor
   or a member defined out of line, the key function. Read its neighbours in link order (below) and take the
   stretches of `ledger/tu-clusters.tsv` among them whose label is a record's. The vtable's slots, the inline members
   and, for a class with no key function, the destructors are linkonce: the link keeps the copy of the first object
   that emits them, often a user's. `api::CSubReport`'s slots 12008-12014 sit in stretch 603 among
   `app/vota/eleitor/` files, while its constructor 3660 sits among `api/gui/` ones. Read this on every band where the
   class has such a function. It wins over the namespace and over rule 3: `api::CTextFieldUpdateMT`'s out-of-line D0,
   `Draw`, `Show` and `Hide` sit beside `app/vota/operador/` objects in both its bands, outside `api/gui/`'s runs, so
   unit 51 puts the class in `app/vota/operador/comum/`, though no record names an `api::` class under `app/`;
3. else the directory where the class's family has records or landed sources: the ecourna `CConversor*` converters
   are in `app/dados/asn/` (or its subdirectory for their family), and the data classes they build in
   `app/dados/`; a comum converter is in the subdirectory of `app/comum/dados/asn/` that mirrors its data class's
   directory under `app/comum/dados/md/` (`asn/` itself for a data class in `md/`). When that directory's own files
   run in name order in the data and the class is not where its name sorts, the directory is a choice against the
   data: say so in the fragment, with the two neighbours (unit 63's `md/cregra*.cpp`);
4. the file name is the class name in lower case (`cconversormunicipiozona.cpp`, `cmunicipiozona.hpp`). A class
   whose only records are in another class's file has no evidence for its header: `vota::IQRCodeBUDS`'s only
   record is its constructor's, in `cmostraqrcodebu.cpp` (`LC_ALL=C /usr/bin/grep -n cmostraqrcodebu
   ledger/source-locations.tsv`). Declare it in that file's header or in its own lower-case header beside it, and
   mark the path as chosen ("Names no evidence gives", below).

Before you create the file rule 4 names, read the class's vtable and typeinfo in the data (the listing below): the
class may have no file of its own. Two shapes:

- **Two classes in one object.** A typeinfo of class A after the vtable of class B, with A's vtable between B's
  vtable and B's typeinfo, puts both in one object: `simulador::CWasmImageSurfaceOps`'s vtable (1528980) and typeinfo
  (1529060) lie between `simulador::CWasmScreen`'s vtable (1528816) and typeinfo (1529080). Its members are in
  `mock/app/simulador/wasm/cwasmscreen.cpp`, the header at rule 4's path (unit 69).
- **A class with its key function in another class's file.** `comum::CRdvPosicionadorVota`'s vtable and typeinfos lie
  inside `crdvvota.cpp`'s run of the data, and a copy kept from a user would come after `comum::CRdvVota`'s own typeinfo
  and its members after the file's external functions; here they come before. A small class one file constructs can be
  defined there: its member goes into that file, and the landed unit that compiles it grows (unit 13).

The `unplaced.cpp` comment over a cluster, `// link-order cluster 255 · uses=1 · neighbours' file
uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversorhasharquivo.cpp`, is that stretch's `probable_file` in
`ledger/tu-clusters.tsv`. Its label (column `label_kinds`) says where the name comes from
([reference/tu-slices.md](reference/tu-slices.md)): `source_location` and `class-record` from a record of another
function in the stretch, `class-convention` from the tool's guess when none has one, the namespace's directory and
the class name in lower case. A stretch can hold unlabelled functions of other classes, so a record's label can be
another class's file: f3660, `api::CSubReport`'s constructor, sits under `neighbours' file
uenux2/src/api/gui/ctextfielddoubleline.cpp`, the label of stretch 984 from 3659's record. Take the file name from the
comment only when its label is a `class-convention` guess for this class, and confirm even that from the data (above:
stretch 499 guesses `crdvposicionadorvota.cpp`, which does not exist in the target); otherwise rule 4 names the file,
and the comment gives the directory at most. The directory comes from the stretches beside it that have records:

```sh
awk -F'\t' 'NR>1 && $1>=253 && $1<=263 {print $1, $10, $11}' ledger/tu-clusters.tsv
# 253 uenux2/src/api/uelog/cescritorlog.cpp source_location:2
# 254 uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversorentidadehashes.cpp class-convention:2
# 255 uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversorhasharquivo.cpp class-convention:2
# 256 uenux2/src/app/comum/gravadores/asn/cconversorenvelopegenerico.cpp source_location:1
# 257 uenux2/src/app/comum/gravadores/md/cenvelopegenerico.cpp source_location:1
# …
# 263 uenux2/src/app/comum/gravadores/asn/cconversorcorrespresultado.cpp source_location:2
```

The guess puts most comum converters in one directory: 18 of the 19 comum converter cluster comments in
`src/uenux2/unplaced.cpp` say `dados/asn/estadoaplicacao` (`LC_ALL=C /usr/bin/grep -h "neighbours' file
uenux2/src/app/comum/.*cconversor" src/uenux2/unplaced.cpp | LC_ALL=C sed -E "s|.*neighbours' file
uenux2/src/app/comum/||; s|/[^/]*$||" | sort | uniq -c`). Stretch 255's recorded neighbours are
`app/comum/gravadores/` files, so `comum::asn::CConversorHashArquivo` (10267) goes in `app/comum/gravadores/asn/`, as
commit 1d026c9 (branch `decomp/decomp3-h`) lands it.

Read a function's link neighbours by band position. Inside one band (one `uses` value of `ledger/ordinals.tsv`) the
target's index runs in reverse link order ([glossary](glossary.md#link-order), *order law*), so the indices next to it
in its band, and the stretches they fall in, are its neighbours, except where a function of another digit zone sorts
in between (a 3- or 2-digit ordinal sorts right after the 4-digit ones it begins), which the ledger cannot single out
for an unanchored function. Never compare two functions by the `ordinal` column: for 3,232 of the 3,270 TSE functions
it is the middle of a window thousands of ranks wide, it steps through 3- and 2-digit values from one index to the
next whatever the functions are (stretch 853's 5909 to 5913 read 4301, 4300, 430, 43 and 4299), and 3,476 values are
shared: 4303 is the estimate of 5907, of `api::CTextFieldUpdateMT`'s D0 10549 and of 10945 in `api/gui/`'s
`CTextFieldBlinking` stretch ([facts/link-order.md](reference/facts/link-order.md) §L7 item 14). The neighbours of
5913 (`comum::CMenuBase`'s slot 2) in its band, `uses` 2:

```sh
awk -F'\t' 'NR>1 && $2==2 && $1>=5908 && $1<=5918 {printf "%s ", $1} END {print ""}' ledger/ordinals.tsv
# 5908 5909 5910 5911 5912 5913 5914 5915 5916 5917 5918
```

then each neighbour's records or stub: `awk -F'\t' '$6 ~ /(^|,)5914(,|$)/ {print $2}' ledger/source-locations.tsv`
prints `/home/rubio/tse/uenux2/src/app/comum/informacao/cinformacaoeleicao.cpp`. Confirm them from the data, which has
no digit scramble: a TU's vtables, typeinfos and `std::source_location` records lie in link-line order, object by
object, so the records and vtables at the addresses around the class's vtable (`ledger/vtables.json` `address`) are its
object's neighbours' ([facts/link-order.md](reference/facts/link-order.md) §L7 item 15 lists them in address order).
`comum::CMenuBase`'s vtable (1550924) follows a record of `app/comum/informacao/cinformacaoeleicao.cpp` and four
`comum::CItem*` vtables. A vtable or typeinfo of a class with no key function is a copy in its first user's object, as
its linkonce functions are (rule 2).

When the recorded neighbours on the two sides name different directories, compare file names only where the data
show a run in name order. `app/comum/`'s own files run carquivosresultado, carquivossavd, cinfomtlcd, cpacotearquivos,
cpath, iinterfaceinit, iinterfacesavd in data order, and `comum::CAppState`'s vtable lies just before
`carquivosresultado.cpp`'s first record, where `cappstate.cpp` sorts. `app/vota/operador/`'s subdirectories run
outrasopcoes, leidentidade, justificativa, comum, confirmaidentidade, aguardaeleitor, and there a name that sorts
between two neighbours supports nothing. Name order is a heuristic for the link line, not a rule: `api/gui/`'s band-1
run has `ctextfieldmt.cpp` before `ctextfielddoubleline.cpp`.

When unrecorded objects lie between the two recorded sides, the data do not place the boundary: take the adjacent side
and call it a choice. `vota::CEleitorVotouNaoVotou`'s vtable (1592928) has four unrecorded vtables between it and
`confirmaidentidade/`'s last record (1592596) and none between it and `aguardaeleitor/`'s first (1593044), so unit
71 puts it in `aguardaeleitor/` and says so. A form or screen type a class's records or members name can rule a tree
out: every `CInteractiveForm<IScreen, IInputKbd>` record lies among `app/vota/eleitor/` records, and none of
`<IScreenMT, IInputMT>` does.

**Keep every throw on its record's line.** A decompiled function's `std::source_location` records are bytes of the
target, so each throw site must sit at the line and column its record gives; above it, blank lines and *gaps* hold
the place of the code not written yet. A gap is a generated comment and a `#line`,
`// (original lines 9-16: content not recovered)` over `#line 17`, that stands for a run of blank lines
([src/README.md](../src/README.md) "Gaps"). The compiler numbers lines through each `#line`, so an error or warning
below a gap names the line of TSE's file, not the line an editor shows. If the file holds stubs or gaps, turn them
back into blank lines before editing it: `python3 -I -B tools/round/stubs.py --strip <file>` moves no line. Write the
function where the stub or the gap was, delete the blank lines it replaces, add some where a throw would land too
early. `make -C src stubs` (step 9 runs it) writes the stubs and gaps again around it, each gap comment over the
blank lines that are left, and `TMPDIR=/tmp make -C src check-srcloc` (after a link) lists every record of ours that
is not the target's. It passes with records that only unmatched functions load, and the tree has some of those
already (21 at 7bf701e, in nine landed objects), so check your unit's own objects with `--strict`, which fails on
those too (step 10).

The record's function name is bytes of the target too: clang's pretty-function text, with the typedef names and
qualifiers the source spelled. Spell the definition's return and parameter types as the record does. 3663's record
(`awk -F'\t' '$6 ~ /(^|,)3663(,|$)/ {print $5}' ledger/source-locations.tsv`) reads `static void
api::CBmpConversor::InvertColors(unsigned char *, const int, const int)`, so its definition takes `unsigned char*`
and `const int` by value, although the same tree spells bytes `uebyte` elsewhere; 144 records do spell `uebyte`
(`cut -f5 ledger/source-locations.tsv | /usr/bin/grep -c uebyte`). [reference/app-flags.md](reference/app-flags.md)
"The error records are std::source_location, not a macro" has the background.

**What a record's place says.** The record's text shows `static` only for a static member: a file-static free
function's record reads like an external one's. Its linkage is in the order of its file's records, because clang
emits an external function where the file defines it and defers internal, `inline` and template functions to the
end of the translation unit ([facts/reading.md](reference/facts/reading.md) §R8):

```sh
awk -F'\t' '$2 ~ /api\/util\/csystem\.cpp/ {print $1, $3, $5}' ledger/source-locations.tsv | sort -n
# 1584628 236 static std::string api::CSystem::TemporaryPath(const std::string &)
# …
# 1584900 1024 void api::truncate(int, off_t, const std::string &)
# 1584916 1039 static void api::CSystem::ZeroFill(const std::string &)
# 1584932 64 bool api::ExistResource(struct stat &, const std::string &)
# 1584948 916 std::string api::(anonymous namespace)::PrepareReplace(…)
```

`api::truncate` (line 1024) sits in line order among the members: external. `api::ExistResource` (line 64) comes
after line 1039, with the anonymous-namespace helpers: file-static. Its symbol is the internal
`_ZN3apiL13ExistResource…`, no header declares it, and it stays out of line only once callers in csystem.cpp keep it
there; until then it cannot land. A caller in another file in `ledger/callgraph.tsv` is binaryen inlining across
translation units, not a call in the source. A member with no record is placed by its use band in the same way:
inside one band of `ledger/ordinals.tsv` (column `uses`, which counts table entries and exports as well as calls;
`ledger/functions.tsv`'s `uses` does not) the index runs in reverse link order, so a member among the file's
external functions is defined in the `.cpp` at that place, and one after all of them is the file's last function, or
inline or implicit (§R9: `comum::IInterfaceInit`'s destructor 5898 precedes line 148's function). That holds for a
member nothing earlier in the file calls: an inline or static function an external one calls sits right after that
caller in the object. A member whose body binaryen keeps once for several classes has no place in its class's band,
so its line is a choice, and the fragment says so (§R9).

The record's order needs a record. A function with no record and a caller in another file is read from that caller's
body: a call in the caller's own code, or in code binaryen inlined from another function of the caller's file, makes
it external; only code inlined from the callee's own file fits a file-static callee (§R8, with 5449, where no byte says
which, so its linkage is a choice).

**Names no evidence gives.** A record gives a function's qualified name and how its types are spelled, a vtable slot
or RTTI gives a class's name, the typeinfo of `CBaseError<E, SErrorLimits{lo, hi}>` an error enum's name, namespace
and limits, and the throw its code. Nothing gives an enumerator's name, a parameter's, a data member's, the scope of a
type a record prints unqualified (`std::vector<CMovieFrame>` is the same text for `api::CMovieFrame` and
`::CMovieFrame`, which mangle differently: §R11), the path of a header no record names, the order in which a class
declares its out-of-line virtual members, or the name of a function no record, slot or RTTI names: a callback passed
by table slot, a pure slot no caller names, a function each of whose records belongs to an inlined callee. A member
never waits for such a name: write it under a chosen one. Choose it from what the evidence shows of its role: the
body's shape and its callers (a `this` returned on a fresh object is a constructor; a copy of `*this` changed by a
compound operator and returned is the matching binary operator), an error's message, a pure slot's callers, else its
slot (`Slot3`). Put a type
in the namespace of the class that uses it, and make a function a member only when it reads private state. Then mark
the choice where it is declared, as `src/uenux2/src/api/gui/eueguierror.h` does for each enumerator (`the name is
chosen from its message, "Dado de entrada nulo": no evidence names it`), and list the chosen names, paths and
linkages in the fragment's header comment with any other choice that gives the same bytes (a free `operator-` for a
member one). Parameter and local names need no mark: no record holds one. The symbol file then names the function by
`pair-*` or `srcloc-anchor` evidence, which says that our body is the target's, not what the function was called.

A slot's callers are not in `ledger/callgraph.tsv`, which holds direct calls. Search the folded readout of each
function that holds an instance for the vtable load, `i32.load[i32.load[<local>]+<4 × slot>]`, anywhere in a line, not
for `table[…]`: an argument with a side effect between the load and the call splits the two. 2890 calls `api::IPaper`'s
slot 8 so:

```sh
pnpm --silent wasm fn ../target/vota_web_wasm.wasm 2890 | sed -n '/folded readout/,$p' | /usr/bin/grep -n -E 'i32.load\[i32.load\[l5\]\+32\]|table\[p0\]'
# 174:      p0 = i32.load[i32.load[l5]+32];
# 176:      table[p0](l5, i32.add(l2, 136), l3, i32.add(l2, 8), i32.add(l2, 32), i32.add(l2, 20));
```

"No caller" means that every holder of the instance was followed and that search found none. Only then is `Slot8` the
name.

What a body does not decide is a choice like a name, and the fragment says which form you wrote:

- **A data member's name and type.** Mark the names in the class header's comment. When the bodies give only a width
  (a 32-bit store of 0 and 1 that nothing reads), take the plainest type of that width (`int`, not a `bool`, which
  stores 8 bits), and say that the type is chosen too.
- **A parameter's or a result's type.** It is evidence only as far as the body uses it: a value the body only returns
  or forwards is one wasm word, and a reference and a pointer to a class compile alike. Say in one line of the
  fragment which types are chosen, instead of listing alternatives no one could finish.
- **A class no evidence names that a body only calls through.** Declare it beside the interface that takes it, with
  virtual members up to the slot the body calls, named from its role, and say that the class and its members are
  chosen (`api::IImageSurfaceSource` in `src/uenux2/src/api/gui/iimagesurfaceops.h`).
- **A body's spelling the bytes do not decide**, such as a call of a member clang inlines against its statements
  written in place: say which you wrote and that the other gives the same bytes.
- **The declaration order of out-of-line virtual members.** Records or the band can show several members out of line
  in one file, and the target does not hold which is declared first. Declare the destructor first, so that the class's
  own `.cpp` emits the vtable and not the `-pending.cpp`, and list the order among the choices (step 5).
- **Two slots of one class that hold one target function.** Both are members, since the vtable needs two, and they
  are one function only after binaryen. The match line takes the first in link order whatever the two are called
  (`vota::impl::CInformacaoThreadOperador`'s slots 4 and 6 are both 2683, matched as `Slot4` although slot 6 has
  callers and a role), so a name in `splat/matched.txt` is not ranked by evidence: the header has the role.

A type a record names but no evidence fills gets its name and its size only. The record of
`api::CTextFieldPaper::CTextFieldPaper(const SharedIText &, IPaper::EStyle)` names a nested enum, and no target code
tests its values; `src/uenux2/src/api/gui/ipaper.h` declares `enum EStyle {};` with a comment that the callers pass 1
and 2 and that the enumerators are not recovered. Invent enumerators only where the code shows what a value does, and
mark them as chosen.

**A stub-only file.** A file the evidence names that does not exist yet holds its stubs only, written from line 2
on, not at their records' lines ([src/README.md](../src/README.md) "Stubs"). `--strip` leaves next to nothing of
it, so there is no "where the stub was": lay the file out yourself so that each throw lands on its record's line,
with blank lines where the original lines are unknown. Blank, not comments of your own: those lines stand for text
nobody has, and a comment written as TSE's documentation (a Portuguese Doxygen block over a function) reads as
recovered text. Notes about the reconstruction (which target functions the file holds, which names are chosen) go
in a header comment at the top that says plainly it is the reconstruction's, as the first three lines of
`src/uenux2/src/api/util/cgenerictags.cpp` do. Before step 9 writes gaps into it, `awk 'NR==<line>' <file>`
prints the line a record names; after a `--strip` of a file that has gaps, it does again
(`awk 'NR==60' <file>` prints `InvertColors`' throw in the stripped `src/uenux2/src/api/gui/cbmpconversor.cpp`).

A record of a function you do not write (a constructor its only caller inlines) keeps its line blank. Put the
functions you write after it, or before it where the evidence says so, and say in the fragment's header comment that
their lines are a choice. Step 9 then puts that caller's stub over the record's line when that line is at namespace
level, and writes no gap over a run of blank lines with no record below it. A record inside a class body (a template
member defined in its class) keeps a gap, and the stub goes after the end of the file marked `placement: link order`,
though a record names the function: `stubs.py` takes only blank lines outside every function and class
(`LC_ALL=C /usr/bin/grep -n '^// f316 ' src/uenux2/src/api/ipc/cmessagequeue.h`).
`src/uenux2/src/api/gui/cstepsprogressbar.cpp` (unit 41) has one record, line
428, of the constructor that 13550 inlines; its gap ends at `#line 425`, f13550's stub takes lines 425 to 428, and the
unit's functions follow. `src/uenux2/src/api/gui/cprogressbar.cpp` (unit 40) keeps lines 4 to 77 blank around its
constructor's records at 52, 58 and 67, with its destructor at 78, and that run stays blank:

```sh
awk 'NR==52||NR==58||NR==67||NR==78 {print NR": ["$0"]"}' src/uenux2/src/api/gui/cprogressbar.cpp
# 52: []
# 58: []
# 67: []
# 78: [CProgressBar::~CProgressBar() = default;]
```

**Save TSE sources as Latin-1.** TSE's files are ISO-8859-1, and their string literals are bytes of the target: an
editor that saves `"inválido"` as UTF-8 changes the data the census and the splat scan compare. `.editorconfig`
declares the charset for `src/uenux2/` and `src/ecourna/` (with the few exceptions it lists), and CI's
`tools/round/check_encoding.py` fails on a file that was re-encoded. Write a new file in Latin-1 too when its
strings have accents.

The target's own bytes decide a file's charset. One TSE literal is UTF-8 there, `"Turno inválido."` of
`src/ecourna/app/dados/asn/cconversorturno.cpp`, which `.editorconfig`'s UTF-8 section lists: `awk -F'\t' 'NR>1 &&
$3=="utf8" {print $1, $2, $4}' ledger/strings.tsv` prints it at 367628, with four rows of binary data. A literal of
the wrong charset shows on a TSE row of the scan as `an address of ours: string not in the target`. That section's
other file, `src/ecourna/app/dados/iidentificadoreleitor.cpp`, is no precedent: its literal is Latin-1 in the target
(`awk -F'\t' '$1==377803 {print $1, $3}' ledger/strings.tsv`), and the file goes back to Latin-1 when its constructor
9256 is written. A search for a string's users has to look for `i64.const` too: a `std::format` string of non-PIC
ecourna code is loaded packed, `(len << 32) | addr`.

The compile line in the lifted file's header is the flag set of the tree the function's code comes from, and the
line under it says what decided (`liftFlags` in `asmlift-wasm/src/lift.ts`): the function's `std::source_location`
records when they name one tree (a path under `/home/rubio/tse/uenux2/` is uenux2, one under the conan package's
`…/b/src/ecourna/` is ecourna), else the tree whose file holds its stub (`src/uenux2`, `src/ecourna`, `src/asn1`),
else its *component*. The component says which code calls a function, not where it is written, so a uenux2 function
in group `ecourna` (step 1) still gets uenux2's flags from its record. After
`TMPDIR=/tmp pnpm wasm lift ../target/vota_web_wasm.wasm 1260 -o /tmp/lift` (1260 is `api::CDirReader::NextEntry`,
group `ecourna`), `head -3 /tmp/lift/1260.cpp` prints:

```
// wasm function 1260
// em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing
// uenux2's flags: a std::source_location record names /home/rubio/tse/uenux2/src/api/util/cdirreader.cpp
```

A function with no record and no stub outside `unplaced.cpp`, or whose records name both trees, gets its component's
flags, and the third line says so (`component ecourna's flags: no record or stub names its tree`). The lifter's flags
are a copy, with no flag a unit's fragment adds. The next steps use `try-tu.sh`, which reads the flags from
`src/Makefile` by the source's path; trust those.

## 4. Iterate on the function alone

```sh
TMPDIR=/tmp tools/round/try-tu.sh --single 1931 --extract export:_ZNK5comum8CRdvVota9CandidatoEhjh \
  src/uenux2/src/app/comum/dados/crdvvota.cpp
```

This compiles your translation unit with the flags of the *compile setup* its component uses, links the one function
alone through the toolkit's *rank adapter*, and scores it against the target: about 7 s on an idle machine, minutes
under heavy load. The flags come from the recipe `src/Makefile` has for the object the file would become. A file
outside `src/` needs `--component` with the directory under `src/` it would land in (`uenux2/src/app/comum/dados`,
`ecourna/app/dados`, `asn1`, …). `--print-flags` shows the compile command without running it.

`--single` compiles every TU as a copy, tracked ones too, so a TU that includes the header beside it by a bare quoted
name (`#include "cwasmwebsound.h"` in `mock/app/simulador/wasm/`) stops with `file not found`: pass that directory
with `--flags "-iquote /work/<dir>"`. A whole-link try and `--symbols` compile a TU at its tracked path in place, and
copy one outside `src/` or under `--component` into `build/out/try/<name>/src/`. There a quoted `#include` of a
header beside a scratch variant finds the tracked header of that name instead (or none). Pass the variant headers'
directory with `--flags "-iquote /work/<dir>"`, the headers under it at their tree paths. Not `-I`: try-tu puts
`--flags` after the tree's `-I` paths, so a variant of a tracked header passed with `-I` loses to the tracked one, also
when another tracked header includes it, and the try measures the tracked form with no word said. A header the
tracked TU includes by a bare name beside it wins over `-iquote` too, since the including file's directory is searched
first: copy the TU out of `src/` and pass the copy with `--component`. Check that the try's object holds what only the
variant gives (`--symbols`, or `llvm-nm` on `build/out/try/<name>/obj/<tu>.o`;
[facts/tool-traps.md](reference/facts/tool-traps.md) §X8, [facts/workflow.md](reference/facts/workflow.md) §W2 item 3).

The lone compile and link is one `em++` with `-fexceptions`, as the build's link is. Its level is not the link's:
the TU's own `-O2` or `-O3` comes after the template's `-Oz`, and em++ takes the last, so binaryen runs at that level
([facts/tool-traps.md](reference/facts/tool-traps.md) §X6, [facts/workflow.md](reference/facts/workflow.md) §W2 item
5). uenux2 code is compiled without `-fexceptions` (no landing pads,
[facts/app-flags.md](reference/facts/app-flags.md) §F6), so for a TU whose own flags lack it `--single` adds
`-fignore-exceptions`, and the `flags:` line it prints ends with it: its throw sites call `__cxa_throw` directly, as in
the build, instead of growing `call import:invoke_…` and `__resumeException` rows
([facts/tool-traps.md](reference/facts/tool-traps.md) §X6).

Several TUs after `--single` are rival candidates, ranked against each other, not one program: a callee defined
in a second TU stays an import (`call import:<symbol>`), and the second TU is dropped when it does not define the
`--extract` symbol. A body that is identical up to such a call is ready for step 5.

The lone link turns undefined functions into imports, but not undefined data. A TU that uses a data object
defined elsewhere (an ASN.1 entity's `theInfo`, a vtable or typeinfo of another class) fails with
`wasm-ld: error: … undefined symbol: …`. Let the linker leave them unresolved:

```sh
TMPDIR=/tmp tools/round/try-tu.sh --single 9131 \
  --extract export:_ZNK7ecourna3app5dados3asn23CConversorMunicipioZona10DoConverteERKNS1_14CMunicipioZonaE \
  --flags '-Wl,--unresolved-symbols=ignore-all' src/ecourna/app/dados/asn/cconversormunicipiozona.cpp
# score 3 over 20 rows (same 17, replaced 3 [3 operand-only], inserted 0, deleted 0)
```

The rows that differ only in an operand are the unresolved data address (`i32.const 0`), the callee as an import,
and our own data addresses. They are expected in a lone link, and target 9131 is matched.

`--extract export:<symbol>` takes the function's mangled symbol. To find it, compile the TU and list what it
defines:

```sh
TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/app/comum/dados/crdvvota.cpp
# _ZNK5comum8CRdvVota9CandidatoEhjh	comum::CRdvVota::Candidato(unsigned char, unsigned int, unsigned char) const
```

Each line is the mangled symbol and its demangled form; pick the one whose demangled form is the target function's
signature (the `std::source_location` record, or the ledger's `best_name`). A symbol the link already references is
also in `build/out/wasm/vota_web/symbols.{mangled,demangled}.txt`, two line-aligned lists `make -C src link` writes,
of the link's inputs, which include what the link drops or merges.
`--symbols` lists functions and weak data only, so a class's own vtable and typeinfo, strong data, are not in it. The
object it compiled stays at `build/out/try/<name>/obj/<tu>.o` (`<name>` is the first TU's base name unless `--name`
gives one), and `llvm-nm` there says whether the TU emits the vtable (step 5):

```sh
TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/app/comum/iinterfaceinit.cpp
TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only build/out/try/iinterfaceinit/obj/iinterfaceinit.o | /usr/bin/grep _ZTV
# 00000000 D _ZTVN5comum14IInterfaceInitE
```

A function linked alone gets different inlining and dead-argument decisions from the same function inside the
program, so a score of 0 here is a reason to try the whole link, not a match. The reverse holds too: target 1931 is
matched, yet its body linked alone still differs from the target's. Even a function with no callee and no argument
to drop can come out differently: 11067, `api::CLineField::Rect`, matches as written and scores 9 alone, because the
whole link computes each compare once and keeps it for two `select`s, and the lone link computes it twice
([facts/tool-traps.md](reference/facts/tool-traps.md) §X9). Read a lone score for the store order, which binaryen
keeps, and rank the forms that differ in anything else in the whole link: the lone link's binaryen also leaves
instruction kinds and the order of loads where the build's does not
([facts/workflow.md](reference/facts/workflow.md) §W2 item 5).

**When the lone score is noise.** These differences come from the lone link itself
([facts/workflow.md](reference/facts/workflow.md) §W2):

- **Callees the program shares are inlined.** A throw that builds its message with `std::format` instantiates
  libc++'s formatting code in the TU, and alone each piece has one caller, so binaryen inlines them all. 5468,
  `api::CGenericTags::TagSize`, is matched as written and scores `10836 over 10850 rows (same 14, replaced 214 [25
  operand-only], inserted 10622, deleted 0)` alone. Go to step 5 at once, or read the object, the compiler's code
  before binaryen, which keeps those calls:

  ```sh
  TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/api/util/cgenerictags.cpp
  wasm-objdump -d build/out/try/cgenerictags/obj/cgenerictags.o | awk '/func\[.*TagSize/{p=1; next} p&&/func\[/{exit} p'
  ```

  and set it beside `pnpm wasm fn`'s disassembly of the target (both open with the same 480-byte frame).
- **Library callees resolve to the toolchain's libraries, not the build's.** `std::mutex::~mutex` is a 45-byte body
  in the target (150, matched), and the lone link drops the call to it: 3907's destructor scores `4 over 53 rows (…
  deleted 4)`, the four rows of `this + 20` and the call, while its object calls `env._ZNSt3__25mutexD1Ev` and the
  whole link matches. A row deleted at a library call is that.
- **A destroyed `std::string` inlines `free`.** Alone, `operator delete` resolves to emscripten's `free`, which then
  has one caller and comes inline whole: hundreds of inserted rows after an `i32.load8_s offset=11 … i32.lt_s` test.
  11272 scores `821 over 1054 rows` as written and `49 over 299 rows` with `--flags '-Wl,--export=free'`, which keeps
  it a call.
- **Instruction kinds and load order at the lone level.** At `-Oz` binaryen joins two `br_if` to one label into an
  `i32.or` (10957, matched, has the `i32.or`; its lone body has two `br_if` for every spelling of the test), and it can
  reorder independent loads (5527). A lone row of either kind is no reason to change the C++.

**When only a flag closes the gap.** A body that differs in a way no C++ form you can find explains (a load the
target repeats, a branch where ours has a `select`) may need a flag its tree's set lacks. When what differs is what is
inlined, first ask clang: `-Rpass=inline -Rpass-missed=inline` on the compile prints each call site's cost and
threshold, so it says at once whether a form of the caller can change the decision
([facts/levels.md](reference/facts/levels.md) §V2). Try a flag with `--flags`
here, then find out whether the flag is the tree's: a flag is decided for a whole tree, on a site no source change
can explain, never on the one function that needs it. A member whose target copy is the executable TU's (its class has
no key function and that TU's data hold its vtable) has that TU's flags, `-Oz -fexceptions`, whichever tree's header
defines it (§V1). [facts/app-flags.md](reference/facts/app-flags.md) §F9 item
8 has a trap here (a reload that an out-of-line call gives as well), and §F6 the evidence for uenux2's
`-fno-strict-aliasing`. A flag set changes in `src/Makefile` (or `src/mk/ecourna-flags.mk`) with its evidence in that facts
file, and every match must still verify in a private link with it (§F9 item 6 has the command; to measure taking a flag
away, take it off the line, since an override is not the same: §F9 item 9). A flag can look per file when it is not: `-fno-PIC` was set file by file until the
target's data showed no file of ecourna apart from the rest (§F5). So before you call evidence per TU, look at what the
whole tree's data and code say. A fragment may carry a target-specific flag only where the evidence is
per TU, and then the objects' flag set must be a setup of
`asmlift-wasm/benchmark/dataset/setups.json`, as `asn1-eh` is for the ASN.1 TUs that throw: `pnpm bench setups --check` fails on an
object that compiles with flags no setup has ([asmlift-wasm/benchmark/README.md](../asmlift-wasm/benchmark/README.md)
"The compile setups"). If neither holds, keep the source as written when it gives the target's rows at the flags that
close the gap: its row stays `differs`, and the fragment's header says so with the measurement (step 5, "A written
body that does not match yet"). Report it. A flag is not a reason to replace a right body with a trap.

## 5. Conclude in the whole link

```sh
echo 1931 > /tmp/targets.txt
TMPDIR=/tmp tools/round/try-tu.sh src/uenux2/src/app/comum/dados/crdvvota.cpp src/uenux2/src/app/comum/dados/md/rdv \
  --targets /tmp/targets.txt --skip-units 13-uenux2-crdvvota.mk
```

A directory stands for the `.cpp` files in it. This links the whole *skeleton* with your TUs, keeps their functions
alive with a generated *roots TU*, runs the census against the target and writes `build/out/try/<name>/report.md`:
per target function in `--targets`, its tier before and after and the first rows that still differ. It takes about
a minute on an idle machine (57 s at a load average of 40) and never writes `ledger/`; two whole links running at
once take about seven minutes each. `--skip-units <fragment>.mk` leaves a landed unit out of the link so its TUs can be
tried again; it leaves out all of the unit's sources and companion files, so pass every one of them (here
`crdvvota.cpp` and the `md/rdv` files it calls). A new function needs it too when its file is one a landed unit
already compiles: without it the link holds that object twice (`wasm-ld: error: duplicate symbol:
api::CThread::~CThread()` for a try of `src/uenux2/src/api/ipc/cthread.cpp`, unit 18's source;
[facts/workflow.md](reference/facts/workflow.md) §W3). Pass the unit's other files and its roots file with your
function added; the function extends that unit (step 6).

When your sources, the fragment and its companions are already where they land, steps 6 to 9 measure the same pairing
on the real link, from one link instead of two: step 7's `moved:` list and step 9's match lines replace the try's
report. A separate try is for comparing variants without touching the tree (`--skip-units <your fragment>.mk`).

**A class with virtual members.** The TU that defines a class's first non-inline virtual member emits its vtable,
and the vtable needs every virtual member defined. A member you have not written goes in a `-pending.cpp` with a
trapping body (`src/units/README.md` "Pending members"), and the vtable needs a root that takes its address. The
class's typeinfo names each base's typeinfo, and a base with a virtual member defined out of line emits its typeinfo
only with that member, so a base whose key function no unit defines leaves the link with `undefined symbol: typeinfo
for <base>` even when the class overrides every slot of it ([facts/units.md](reference/facts/units.md) §U9,
[facts/reading.md](reference/facts/reading.md) §R6); "Pending members" says what to define then. try-tu
has no compile rule for a path under `src/units/`, so pass `--component` with the directory the class lands in;
it puts every TU of the run there, with that directory's flags. The roots file goes through `--roots`. Here is the
landed unit 16 tried again:

```sh
echo 9131 > /tmp/targets.txt
TMPDIR=/tmp tools/round/try-tu.sh --name munzona --component ecourna/app/dados/asn \
  src/ecourna/app/dados/asn/cconversormunicipiozona.cpp src/units/16-ecourna-cconversormunicipiozona-pending.cpp \
  --roots src/units/16-ecourna-cconversormunicipiozona-roots.cpp --targets /tmp/targets.txt \
  --skip-units 16-ecourna-cconversormunicipiozona.mk
```

Because `--component` moves every TU, it also moves the `std::source_location` paths of a TU from another
directory. Use it when the TUs share a directory's flags and the moved ones have no records.

Every route above takes a `<tu.cpp>`, so a unit with no source of its own (its matches come from its roots or pending
object, step 3) has none for a header variant. Compile that companion against the variant with `-iquote`, put the
object in a clone of `build/out/app`, and link with the clone as `APP`: no other object recompiles, and the link map
and `splat-remap` read it as any private link
([facts/workflow.md](reference/facts/workflow.md) §W13, "One variant object in the whole link"). Check the overlay
first: the unchanged header through the same `-iquote` must give an object `cmp`-equal to the landed one.

**A written body that does not match yet.** A body that is right apart from something outside it stays in the landed
file: a callee not written, a flag its tree does not have, a data object or a literal it waits for. Its row stays
`differs` or `unresolved`, which is an ordinary state of a TSE object. Show the cause with a link or a compile that holds
what the body waits for, and say what it waits for, with that measurement, in the fragment's header and its README
row. `ModeloAbreviado` (8168, unit 75) is `differs` until the literal it shares a tail with is in the link, and with that
literal in a scratch link `splat-remap` prints `IDENTICAL`; it prints that for 8746 and 8799 (unit 78) at `-O3
-std=c++23` ([facts/levels.md](reference/facts/levels.md) §V3), and `api::ITextToSpeech::SetVoice` (11518, unit 82)
gives the target's rows at the executable TU's flags (§V1). A trap in a
`-pending.cpp` is right for a member that cannot be written yet (a callee or a type the tree lacks), that cannot match
until other code lands (a merge thunk: `src/units/README.md` "Pending members"), or whose real body would cost a match:
`return "CProgressBar";` compiles to the target's 10975 and stays a trap because the real body would drift matched 9696
(unit 40). A member the compiler writes from the class
definition has no body to trap at all (an implicit destructor), so there the class stays as it is and the fragment
says what differs. Do not replace a right body with a trap to clear a row.

**The destructors say how the class is declared.** Read the D2 and D0 in the vtable's slots 0 and 1 before you write
the class head. The D2's bytes are the same in every form of the destructor, so a D2 that matches settles nothing; the
D0's shape decides ([facts/reading.md](reference/facts/reading.md) §R4–R7):

- A D0 that holds the D2's body and then frees `this` (11176, 12049) belongs to a destructor with the inline hint:
  implicit, or declared `inline`, in the class (`inline virtual ~X() = default;`) or after it in the header (`inline
  X::~X() = default;`), which give the same object. Leave it implicit when the class has a base; declare it `inline`
  when it must be declared, as in a class with no base, whose destructor is virtual only when declared so. An
  in-class destructor without `inline` gives this shape only for a cheap D2: `vota::IQRCodeBUDS`, a class with no
  base, declares `virtual ~IQRCodeBUDS() = default;`, and its D0 12049 holds the 116-B D2.
- A D0 that frees what the D2 returns, `f136(f5531(p0))` (10 B, 11086), belongs to a destructor that is not out of
  line and whose D2 was too costly to inline: defined in the class without `inline` (`= default` or `{}`), or, above the
  hinted cost as well, implicit or `inline` (5590, `f136(f2876(p0))`, over `comum::CParteCandidatos`'s five
  `shared_ptr` members; §R5). Only a smaller D2 tells those forms apart: compare them in the class's own shape, and list
  the ones that give the same object. The same shape around a base's D2 (9388 calls 5898, `comum::IInterfaceInit`'s)
  belongs to a class with no member of its own, whose slot 0 holds that out-of-line base D2.
- A D0 that calls the D2 and then frees `this`, `f5709(p0); f136(p0);` with a `drop` between them (13 B, 11443),
  belongs to a destructor defined out of line: define it in the `.cpp`, where it is the key function unless another
  virtual member is out of line before it. When records or the band show other virtual members out of line in the same
  file, the target does not hold which is declared first: declare the destructor first, so that the class's own `.cpp`
  emits the vtable rather than the `-pending.cpp`, and list the order among the choices (step 3).
- A derived class's D2 inlines its base's destructor unless the base's is defined out of line, which it calls. So a
  base destructor out of line shows as a `call` in every derived D2, and an inline one as the base's vptr store and
  member frees after the derived class's own. That store is there only when the base destructor's body makes a call;
  without it, the base's destructor may still be empty, `= default`, or do anything that calls nothing (§R4).
- A D2 that destroys members and does not begin with its class's own vptr store (11178 begins with its strings, not
  with `i32.store[p0] = <vptr>`) belongs to a `final` class: write `final`. A vptr stored further on is a base's,
  where the base's inlined destructor begins; `final` leaves that store in place. A class whose destructor destroys
  nothing has one of binaryen's shared bodies there and no store to read; when the target builds it with
  `std::make_shared`, an empty `__on_zero_shared` (slot 2 of `__shared_ptr_emplace<T>` is the shared 218) says `T` or its
  destructor is `final` (§R4).
- A class whose virtual members are all inline (an implicit or in-class destructor, nothing else out of line) has no
  key function: only a TU that uses its vtable emits the vtable, D2 and D0. One that defines a constructor does, and
  so does one that emits a derived class's destructor that inlines this one, since it stores this class's vptr. When
  neither is written, write a constructor as well, at its record's line; the target may have inlined it everywhere,
  and our link then drops it. When no reconstructed TU can do it, the roots file does, in an `optnone` function: it
  builds an object where the constructor is written (unit 67) and calls the destructor by its qualified name where it
  cannot be (unit 64). `src/units/README.md` "A class with no key function" has the shape, §R6 the mechanism.
- When the destructors are shared bodies, or the class has no vtable in the target, they say nothing of a key
  function, and a missing vtable does not either: wasm-ld drops one nothing references. Read where the typeinfo lies:
  a copy in a user's object (inside a TU that only uses the class, or no later than its earliest derived class's
  typeinfo) means no key function, and one well after it, among other objects' records, means one member is out of
  line. Which member is a choice (§R6).
- A slot that holds `__cxa_pure_virtual` (12143) is a pure member: declare it `= 0` at its slot even when no evidence
  names it (step 3, "Names no evidence gives"), so the class stays abstract. An abstract class's D0 is a trap (its
  slot 1 holds 325, `unreachable`); without the pure members the vtable is shorter and the D0 a real body the target
  does not have. `comum::IInterfaceInit`'s vtable is 0x28 bytes with its five pure slots, and a probe of that shape
  without them gives 0x14.

The report's census *tiers* are diagnostics ([pairing and progress](glossary.md#pairing-and-progress)). A target function
paired with your symbol is worth landing and checking with the splat scan at any tier: most matched functions pair
only at `addr` ([status.md](status.md) "Diagnostics: the census tiers"). No tier is a match. The example shows both
sides of that: the report says `1931 343 B app/comum: none → none`, because a caller of `std::to_string` pairs at
`none` at depth 2 however exact its body is ([facts/tool-traps.md](reference/facts/tool-traps.md) §X5), and 1931 is
matched all the same. The unit-16 run above prints `9131 54 B app/ecourna: none → none` too, for a body that is
the target's once re-pointed.

**When the report pairs nothing, re-point against the try link.** Map it once, relink it with the data and the
table moved to learn what each of its constants is (the *operand kinds*, [reference/splat.md](reference/splat.md)
§3), then run `splat-remap` ([reference/splat.md](reference/splat.md) "Matching a function") on its wasm:

```sh
TMPDIR=/tmp tools/round/link-map.sh build/out/try/munzona/wasm/vota_web     # about 20 s
TMPDIR=/tmp tools/round/link-kinds.sh build/out/try/munzona/wasm/vota_web   # about 40 s
cd asmlift-wasm
pnpm --silent wasm splat-kinds ../build/out/try/munzona/wasm/vota_web/vota_web_wasm.wasm
pnpm --silent wasm splat-remap ../target/vota_web_wasm.wasm ../build/out/try/munzona/wasm/vota_web/vota_web_wasm.wasm \
  sym:_ZNK7ecourna3app5dados3asn23CConversorMunicipioZona10DoConverteERKNS1_14CMunicipioZonaE --against 9131
# ours 10517: re-pointed, 54 bytes; rewritten {"address":2,"func":1}; soft 0; operand kinds verified
# target 9131: IDENTICAL (2 ambiguous operands read as address content-repointed)
```

`link-kinds.sh` refuses a try link whose objects were rebuilt after it was linked: run it right after `try-tu.sh`.
Give `--name` a plain name: the try goes to `build/out/try/<name>/`, and `link-map.sh` and `link-kinds.sh` look for the
path they are given, spelled as it is, in the link's `link.cmd` (line 28 of `tools/round/link-map.sh`, line 50 of
`link-kinds.sh`), so a try put elsewhere with `--name ../<dir>` is found only under the spelling
`build/out/try/../<dir>/wasm/vota_web` ([facts/tool-traps.md](reference/facts/tool-traps.md) §X10).
To skip the two kind steps, pass `--no-kinds` to `splat-remap`; it then says `KIND-UNVERIFIED (no operand-kind
table)` and offers every operand every reading its value suggests. `IDENTICAL` there is the
signal to land. `splat-remap` reads the committed symbol file and none of the matches, so
`differs` or `UNRESOLVED` can still turn into a match once steps 8 and 9 add names; the scan in step 9 decides.
One `UNRESOLVED` no name fixes: a call into `byn$mgfn-shared$…`, which means binaryen merged your function with
others of its shape in the try link (*mgfn*), and the target did not merge that set. Our body is then a short thunk
where the target's is a whole body, and the shared body's callers (`pnpm wasm fn <try wasm> <its index>`) name the
partners. It matches once the partners have the target's shapes, or once it merges with the target's set (step 1,
`unresolved` rows; `src/units/README.md` "Pending members" has a member that waits so).
The `ours` index is the function's index in the try link; `pnpm wasm fn` on the try link's wasm with that index
shows its body beside the target's.

`UNRESOLVED` lists the operands it cannot re-point and compares nothing after them, so it does not say the rest of
the body is the target's. Score the two bodies row by row: a body names can turn into a match differs in operand rows
only, as every match does against our plain link:

```sh
cd asmlift-wasm
pnpm --silent wasm score ../target/vota_web_wasm.wasm 9131 ../build/out/wasm/vota_web/vota_web_wasm.wasm $(awk -F'\t' '$1==9131 {print $3}' ../splat/scan.tsv)
# score 3 over 20 rows (same 17, replaced 3 [3 operand-only], inserted 0, deleted 0)
```

(For a try link, pass its wasm and the `ours` index `splat-remap` printed.) And an operand whose function can be
named only through that operand stays unresolved: a callback passed by table slot gets a `table` name only from a
caller with a census pair or an anchor, not from one the symbol file names by `vtable` evidence alone
([reference/splat.md](reference/splat.md) §2).

A TSE TU's `std::source_location` records name the target's files in a try link too: every uenux2 and ecourna
compile runs from the source's `/work/src/…` path, which the tree's `-ffile-prefix-map` rewrites to
`/home/rubio/tse/uenux2/…` or the conan path (`--print-flags` shows the compile line;
[facts/tool-traps.md](reference/facts/tool-traps.md) §X7).

## 6. Land the unit

1. Keep the sources at the paths the `std::source_location` records name, or that step 3 chose.
2. Write the fragment `src/units/<NN>-<component>-<what>.mk` with the next free `NN`, named by content: the source
   directory the files share, or the class. `src/units/README.md` describes what a fragment holds, its naming
   scheme, and the *roots*, *pending* and *externs* companion files. The generic rules make each object depend on
   its own source and on every header of its tree, so a fragment needs a compile rule of its own only for other
   flags ("What a fragment holds" item 3). A rule of your own compiles the TSE source from its
   `/work/src/…` path, as the generic rules do, so the tree's `-ffile-prefix-map` rewrites the file name its
   `std::source_location` records hold; a relative path is never rewritten, and
   `TMPDIR=/tmp make -C src check-srcloc` then fails with `UNMAPPED` and the record. Add the fragment's row to the
   table in `src/units/README.md`. A function whose file a landed unit already compiles takes no new fragment: it
   extends that unit, its sources, companion files, fragment header comment and README row (`src/units/README.md`
   "Landing a unit").
3. If nothing in the skeleton calls the unit yet, add a `-roots.cpp` that reaches each function the way the target
   does (address taken, the function's or, for a member the target reaches only through its vtable, the vtable's;
   at least two call sites, from two callers or one that calls it twice, counting the reconstructed ones; or none
   so it inlines; `src/units/README.md` "Companion files").
4. Link: `TMPDIR=/tmp make -C src link`. Do not pass `-j` to the link: its two outputs share one recipe. make does
   not rebuild an object whose flags changed but whose prerequisites did not. To see whether an edit of a source
   recompiles anything, count the compiles make would run:
   `make -n -C src link -W $PWD/<source> | /usr/bin/grep -c 'em++.* -c '` (0 means the link would keep the old
   object). Name the file with `-W`: a whole-link try (step 5) runs the same make first and compiles every stale
   object into the shared `build/out/app/`, so after a try a plain `make -n -C src link` counts 0 for edits it has
   already compiled ([facts/workflow.md](reference/facts/workflow.md) §W3).

## 7. Census

```sh
TMPDIR=/tmp make -C src census
```

This rewrites `ledger/functions.tsv` and saves a new snapshot in `ledger/history/` (about a minute). It prints
the paths of its reports; the target functions whose census tier moved are under `moved:` in
`build/out/census/progress.md`. Commit the new snapshot and `git rm` the previous one by name
(`ledger/README.md`); step 10's commit names the removed one after `--`. Expect thousands of changed lines in
`ledger/functions.tsv` for a small unit: its `best_index` column holds our function indices, and every function
after the unit's place in the link shifts. The census also re-picks a pair among byte-identical bodies of ours once
the indices shift, so `best_name` changes on rows that have nothing to do with the unit, and step 9 carries that into
the scan (step 9 says how to check it; [facts/splat.md](reference/facts/splat.md) §S8). The next three steps read this
census.

Read the pairs with your roots file before step 8. A stand-in caller can compile to a target function's body (`int
B(int p) { return D2(p); }` is any derived class's destructor that adds no member), the census then pairs that target
function with the stand-in, and step 9 would match it under the stand-in's name. Every census pair with a function a
unit's roots object defines, once the link map is this link's (step 8 makes it too; about 20 s):

```sh
TMPDIR=/tmp make -C src link-map
awk -F'\t' 'NR==FNR { if (FNR>1) obj[$1]=$3; next } FNR>1 && $6=="skeleton" && obj[$7] ~ /app\/[0-9]+-.*-roots\.o$/ {print $1, $8, $10}' build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv
# 9409 addr std::__2::__shared_ptr_emplace<api::CImageField, std::__2::allocator<api::CImageField>>::~__shared_ptr_emplace()
# …
```

A `__shared_ptr_emplace<T>` or `__shared_ptr_pointer<T*, …>` member is what a control-block root is meant to emit
(`src/units/README.md` "Companion files"); a `(anonymous namespace)::` name of your roots file is a stand-in, so give
it a body no target function has. A third kind is a real member under its real name: a roots object that emits a
header's inline code pairs so (`api::COptionValidation::isValid`, unit 67; [facts/units.md](reference/facts/units.md)
§U4 counts them). That is expected for a function your unit claims; for any other
target function read its scan row after step 9, since a `match` there is a function you did not mean to claim.

## 8. Symbols

```sh
TMPDIR=/tmp make -C src splat-symbols
git diff --stat splat/symbol_addrs.txt
```

The *symbol file* names target functions and data from evidence that includes the census's unique pairs, so a new
unit's functions and data get their names here. Run it after every landing that adds functions or data, and read
the diff: a name that moves can break existing matches (step 10 would say so). It also re-picks the arbitrary name
of byte-identical *twins*, drops and restores the `pair-addr` lines of matched functions the census pairs by address,
moves an `evidence:table` name between functions, and re-places data placed by its content (`g_MidAlloc` and
`g_BigAlloc` moved with unit 41), so expect churn in lines that have nothing to do with your unit
([facts/splat.md](reference/facts/splat.md) §S8); keep it, do not pick lines by hand. Lines below the hand-edit marker
survive; never add one whose only evidence is the match it enables ([reference/splat.md](reference/splat.md) §2).

## 9. Match

```sh
TMPDIR=/tmp make -C src splat-match
git diff splat/matched.txt
```

`splat-match` scans every target function, re-points each candidate body of ours into the target's index and
address spaces, appends every new byte-identical match to `splat/matched.txt` as `<target index> <our symbol>`
(and renames a listed match whose symbol left our link to its twin: step 10, "A twin whose name moved"), rewrites
`splat/scan.tsv`, regenerates the progress numbers (`make -C src status`: the status blocks of `docs/status.md`, the
README's `status:headline` block and the six waffles `docs/img/progress-{origins,tse,components}-{light,dark}.svg`,
printing `wrote <file>` for each one it changes), and rewrites the stubs and gaps (`make -C src stubs`): a function
with a match or a body of ours has no stub, so yours goes, and a stub-only file whose last stub goes is removed. A
pending member's stub goes too, although its body is only a trap: `stubs.py` counts a function in a slot of a vtable
our link holds as code of ours. The scan lists a pending member one of two ways. When binaryen merged its trap with
another trap of the same wasm type, the slot gets no name and the row stays `no-candidate` (9133 and 9130, units 15's
and 16's; 11366, unit 17's, since a later unit's trap of its type merged with it). When the trap is a function of its
own, step 8 names the target function after the trap by `vtable` evidence, and the row is `differs` with the
`-pending.o` as its object (11442, unit 36's):

```sh
awk -F'\t' '$1==9130 || $1==9133 || $1==11366 || $1==11442 {print $1, $4, $5, $11}' splat/scan.tsv
# 9130 - no-candidate -
# 9133 - no-candidate -
# 11366 - no-candidate -
# 11442 symbol differs app/36-uenux2-cvisitantefoto-pending.o
```

So declare a trap with the member's real signature, its record's, since that name can reach
`splat/symbol_addrs.txt`; when a landed base header forces another one (step 2), say so in the `-pending.cpp`
header. That header is the only note that the member is left to do, so name it there (a written body that does not
match yet has its note in the fragment instead: step 5). When the member's stub was the
last of a stub-only file (a file only an inlined callee's records name), the file goes too: name that file and its
record lines in the header as well, since writing the member writes the file again.

For one function, `pnpm wasm splat-remap` shows the comparison directly;
[reference/splat.md](reference/splat.md) "Matching a function" has the command and explains `IDENTICAL`, unresolved
operands and the first differing byte. It applies none of the matches, so it can say `differs` for a function the
scan matches.

`splat-match` also reports a listed line whose function the symbol file names only after other functions of our
link: the body verifies, but the evidence says another function sits there, as with 11611, matched as
`wrapexcept<bad_weekday>::rethrow` while the target's `wrapexcept<bad_month>` vtable holds it
([facts/splat.md](reference/facts/splat.md) §S7). It changes nothing; find which side is right, and correct the
match line by hand when the evidence is. A second name beside the matched one is not reported, so read step 8's
`git diff splat/symbol_addrs.txt` for a `func:N` that gained a name, and for a matched index that lost its line: a
vtable slot your unit fills with a body that is not the target's (a defaulted or implicit member of an earlier unit)
votes that slot's index onto the body, and the function the body is matched as can lose its line
(`_ZN7RHVoice6clientD2Ev = func:174;` went so, with `api::IScreen`'s `~IScreen() = default`). The match stands, and the
range says why. Two kinds of line move at every landing whatever
the unit, and are not evidence. A matched index gains an `evidence:table` name while the function that name belongs
to loses its `vtable` line, if it had one: a constant both bodies hold reads as a table slot once our read-only data moved (7530,
matched as `ossl_ec_GFp_simple_cmp`, gains a `visitExtensionRoot` name and loses it again as units land; 615 does the
same). And the `pair-addr` line of one matched SQLite function drops out as the one the last landing dropped comes
back. [facts/splat.md](reference/facts/splat.md) §S8 lists them, with the command that prints a landing's lines
without its own matches. The match lines are right and the lines are generated; keep the file as step 8 wrote it. A
gained name on another index is the range's to explain.

The scan changes rows that are not yours as well: the census's re-picked pairs change the `symbol` and `object` columns
(30 rows of 36-byte `__cxx_global_array_dtor` copies with unit 41), and now and then a verdict moves between
`unresolved`, `no-candidate` and `differs` ([facts/splat.md](reference/facts/splat.md) §S8). Read the verdicts against
the commit your branch started from: no row may leave `match`, and every row that turns `match` must be yours, with
two exceptions below:

```sh
join -t "$(printf '\t')" <(git show "$(git merge-base main HEAD)":splat/scan.tsv | cut -f1,5 | sort) <(cut -f1,5 splat/scan.tsv | sort) | awk -F'\t' '$2 != $3'
```

It prints `<index> <verdict before> <verdict now>` for each row that moved; on an unchanged tree it prints nothing.

A row of another unit can turn `match` for a reason you can name:

- **A name your unit released.** A row that was `unresolved self-voted` waited for its callee's name to have a voter
  besides itself ([reference/splat.md](reference/splat.md) "No circular evidence"). A unit that adds another use of the
  name releases it, and the row matches: 5483, `api::CIniKey::operator=` (unit 01), turned `match` when five throws of
  a later unit gave `CBaseError<EUeIoError>`'s constructor other callers. The match belongs to the unit that holds the
  body; say which in the commit message.
- **A body the content pass pairs.** The pass pairs one of our unused bodies with a target body it equals when no
  other unmatched target body equals it, by locals and opcodes, not by wasm type, so a small or empty body pairs as soon
  as another match removes its last twin. Among bodies alike, the name can be the wrong one, and the build cannot tell
  ([facts/splat.md](reference/facts/splat.md) §S11 has the cases). A row whose detail reads `address same-content` or
  `table slot copy`, or whose `source` is `content`, is checked against what calls or points at the function and against
  its neighbours in `splat/matched.txt`; correct the line by hand when they disagree.

A match the scan found by body has `content` in the `source` column of `splat/scan.tsv`. Once the match names the
function, a later scan writes `symbol` there, so a rescan of the committed state differs from the committed
`scan.tsv` in one such line per new match the scan found by content, and a renamed twin's row can go from `ledger` to
`symbol` the same way. A new match that step 8 had already named
(`evidence:srcloc-anchor`, `pair-*`, `call`, …) has `symbol` from the start, and then a rescan changes nothing: on an
unchanged tree `TMPDIR=/tmp make -C src splat-match` ends with `0 files written` and `git status` shows nothing.
Neither is drift; commit what the generator writes.

An edit after this step that leaves the plain link byte-identical (a comment; `shasum -a 256
build/out/wasm/vota_web/vota_web_wasm.wasm` before and after the link) changes nothing steps 7 and 8 read: run
`splat-match`, which writes back any stubs you stripped, then `splat`. Any other edit goes back to step 6.

A *match* is a promise that the build keeps producing that body. Never edit a piece, and never add a symbol-file
hand edit whose only evidence is the match it enables: a name whose only use is to make a function match proves
nothing. A generated `vote:1 by:<index>` data line is that same shape, and the rule lets it through: the name's only
evidence is the one body that voted, and the build's check is that body's bytes and the object's (one byte for
`api::CSystem::s_dorme`, which 8461 alone votes for). Say in the fragment what else ties the operand to the object (the
other readers of the address), so a reviewer can weigh it.

## 10. Build and commit

```sh
TMPDIR=/tmp make -C src splat
```

The build substitutes our bytes for every matched function, prints the meter and fails unless the module's sha256 is
the target's, `8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2`. If an existing match breaks
(*drift*), the build names it and the first differing instruction; fix the source until it verifies again
([reference/splat.md](reference/splat.md) "The drift rule").

It also fails when a match is *kind-unverified* (the shifted link cannot say what its constants are), and names
each one with the reason. Read it before anything else ([reference/splat.md](reference/splat.md) "Reviewing a
match"); raising `SPLAT_MAX_KIND_UNVERIFIED` in `src/mk/splat-sub.mk` is a decision for review, with the reason
written beside it. The *review warnings* list the literals of matches that may be a target number copied into the
source. For a TSE function, check that each one of yours is a number its source has a reason to hold.

The review's blanked-target check blanks the function's piece, not what the symbol file already took from it. So a
data name held only by this match's own vote (`evidence:vote:1 by:<this index>`) passes both ways, and for that operand
the check shows no more than the byte comparison does. To see what the name carries, review on a copy of the symbol
file without its line (from `asmlift-wasm/`):

```sh
mkdir -p ../build/out/review-probe
/usr/bin/grep -v '_ZN3api7CSystem7s_dormeE' ../splat/symbol_addrs.txt > ../build/out/review-probe/symbols-no-dorme.txt
pnpm --silent wasm splat-review ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm 8461 -o ../build/out/review-probe/8461-nosym --symbols ../build/out/review-probe/symbols-no-dorme.txt
# preferred readings:    UNRESOLVED: +0x37 i32.const 1235768: an address of ours: _ZN3api7CSystem7s_dormeE (.data) has no target symbol; too little content to place by its re-pointed bytes
```

**A twin whose name moved** is the one break that is not drift. When your unit brings in a body byte-identical to a
matched one (another class's deleting destructor, another instantiation), binaryen keeps the first in link order,
and if yours comes first, the matched symbol leaves our link. A build run before `splat-match` says `function 246
matched to _ZN21ModuloTiposEleitorais4FotoD0Ev: our link has no function _ZN21ModuloTiposEleitorais4FotoD0Ev`. Step
9's `splat-match` repairs it: when a listed symbol is missing from our link and the scan matches the same index under
another symbol (the survivor, whose body re-points into the target's bytes), it rewrites that line in place and
prints the rename:

```
…/splat/matched.txt: 0 matches added, 1 renamed
  line 7218: function 246 renamed _ZN21ModuloTiposEleitorais4FotoD0Ev → _ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev: …
```

Any other missing symbol is left as written and printed (`… left as written, so the splat build fails on it`): that
one is drift or a deleted function, and yours to fix. Say in the commit message which lines were renamed
([facts/splat.md](reference/facts/splat.md) §S6). To see whether a symbol is in the link, read
`build/out/wasm-map/vota_web/names.tsv`, not step 4's `symbols.{mangled,demangled}.txt`: those list every symbol of
every input, kept or merged away.

A unit can also make two functions it never touches into twins, through their callers. binaryen's dead-argument
elimination folds a parameter every caller passes as the same constant (step 2), and a new caller that passes
another value keeps it. `std::mutex::unlock` is a `()->()` body of 47 B in our link at ee595de, its only callers
passing one mutex, beside `std::mutex::~mutex`, `(i32)->()` and 45 B, which is matched as 150; the target's 150 is
both. The first `lock_guard` over a member mutex keeps `unlock`'s parameter, the two bodies become one, and step 9
renames line `150 _ZNSt3__25mutexD2Ev` to `150 _ZNSt3__25mutex6unlockEv` (commit ad74d47;
[facts/splat.md](reference/facts/splat.md) §S6). A rename line that names no symbol of yours is that.

`git diff splat/matched.txt` shows each rename as a `-` and a `+` line with the same index at the same place, and
`git diff --word-diff splat/matched.txt` as one line,
`246 [-_ZN21ModuloTiposEleitorais4FotoD0Ev-]{+_ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev+}`: a
rename, not a lost match. So count lost matches by index, not by line, against the commit your branch started from.
Against a `main` that moved since, the count also lists every match `main` gained, which are not yours to lose
([facts/workflow.md](reference/facts/workflow.md) §W6):

```sh
comm -23 <(git show "$(git merge-base main HEAD)":splat/matched.txt | cut -d' ' -f1 | sort) <(cut -d' ' -f1 splat/matched.txt | sort)    # prints nothing when none is lost
```

After merging `main` in ("Landing onto a moved main", below), run it with `main` in place of
`"$(git merge-base main HEAD)"`: it must print nothing then too.

**Withdrawing a match.** When you take a matched function back out of the source on purpose (a match a review
refuted), delete its line from `splat/matched.txt` by hand (a list people edit; `splat/scan.tsv` is generated) and run
step 9 again. While the line is there, `splat-match` fails after the scan: `status.py` prints `splat/scan.tsv has 7428
match rows but splat/matched.txt has 7429 matches (scan only: [], matched.txt only: [9130])`, having already rewritten
the status files the new scan changed, and `stubs.py` does not run, so the function's stub does not come back
([facts/workflow.md](reference/facts/workflow.md) §W11).

Commit in one commit: the sources, the fragment and its companion files, the fragment's row in
`src/units/README.md`, the ledger files the census rewrote (the new snapshot, and the previous one step 7 removed),
`splat/symbol_addrs.txt`, `splat/matched.txt`, `splat/scan.tsv`, the status files step 9 wrote (`README.md`,
`docs/status.md`, `docs/img/progress-*.svg`) and the stub and gap files it rewrote (`git status src/`). A stub-only
file step 9 removed shows as ` D` there: `git rm` it before the checks below, because `check_encoding.py` reads the
index and stops with `FileNotFoundError` on a tracked file that is gone
([facts/workflow.md](reference/facts/workflow.md) §W8). `git add` refuses a path already removed with `git rm`
(`fatal: pathspec '…' did not match any files`, and it adds nothing), so name the removed paths after `git commit --`
only (§W7):

```sh
git rm -q <each stub-only file step 9 removed>
git add <the sources, fragment, companion, ledger, splat and status files>
# the checks below
git commit -F - -- <the same files> ledger/history/<the previous snapshot> <the removed stub files> <<'EOF'
<subject>

<body>
EOF
git log -1 --stat
```

CI checks that the match list, the scan and the status files agree (`python3 -I -B tools/round/status.py --check`)
and that every stub is the one the evidence gives and every gap the one the generator writes
(`python3 -I -B tools/round/stubs.py --check`, also `make -C src stubs-check`). Run both after the `git add` and
before the commit, with:

- `python3 -I -B tools/round/check_encoding.py` (step 3), which checks the files `git ls-files` lists: a new header
  or source is checked only once it is added ([facts/workflow.md](reference/facts/workflow.md) §W8);
- `python3 -I -B tools/round/check_srcloc.py --strict <the objects of the files you wrote or changed>` (a new unit's
  objects, all of them), which must report 0 records that are
  not the target's (`build/out/app/uenux2/src/api/util/cgenerictags.cpp.o build/out/app/33-uenux2-cgenerictags-roots.o`
  for unit 33: `1 source_location records in 2 objects (1 files): 1 are records of the target; …`). A landed unit's
  other objects can hold records of unmatched functions that were already off, so `--strict` over a whole landed unit
  may never pass; show those objects unchanged instead (the object comparison of [agents.md](agents.md) "Shared build
  outputs");
- from `asmlift-wasm/`, `TMPDIR=/tmp pnpm test:bench`: the benchmark's tests check that every object compiles with
  the flags of a setup in `asmlift-wasm/benchmark/dataset/setups.json`, which a flag added in a fragment breaks while
  every other check passes ([src/units/README.md](../src/units/README.md) "What a fragment holds"). A flag change that
  moves an object a frozen dataset row names to another setup fails it too (`… now compiles under setup …, the row says
  …`): that takes a re-selection of the dataset in a commit of its own
  ([asmlift-wasm/benchmark/README.md](../asmlift-wasm/benchmark/README.md) "Re-selecting");
- from `asmlift-wasm/`, `TMPDIR=/tmp pnpm test`, alone in the checkout: beside a census or `splat-match` its
  real-link cases skip and it still exits 0, so read the count, `195 passed (195)`. Every case passes on `main` since
  04a718a ([facts/workflow.md](reference/facts/workflow.md) §W12), so a failing one is your branch's to explain: run
  it on the commit your branch started from to see whether it fails there too. One failure is not a fault: a right
  record the target holds twice (a header-inline function two TUs inline) fails `splat-symbols.test.ts`'s record case
  with `expected 'source_location record ambiguous'`; check it with `check_srcloc.py --strict` (§W12). And `4 skipped`
  means the `emscripten/emsdk:6.0.0` tag is missing (§W12).

**Landing onto a moved main.** When another unit landed after your branch started, merging conflicts in generated
files and in the census snapshot, which both branches renamed. Resolve only the files people write:
`src/units/README.md` keeps one row per fragment, both sides' new rows in fragment order. Git joins changes to adjacent
rows into one hunk that holds every row on both sides, so "keep both" gives a row twice with one copy stale: for a row
both sides hold, keep the side that changed it from the merge base (`git show :1:src/units/README.md`), and resolve a
row both sides changed by hand ([facts/workflow.md](reference/facts/workflow.md) §W20). `splat/matched.txt` keeps both
branches' match lines (step 10 checks every one again), each index once. Two units can match the same function (a
base's destructor both bring in: 11013, `api::IFormFieldBase<api::IPaper>`'s, came with two units), and a second line
for an index stops the splat build with `Error: match list line N: function 11013 is already matched on line M`; git
may join the two additions, keep both or mark a conflict, depending on where each side put its line. Two branches can
also each have renamed one twin to its own class, a one-line conflict on the index. Keep either side's line: the
merged link does not exist yet, and step 9 renames the line to the survivor when the kept symbol left it. After step 9,
`cut -f2 build/out/wasm-map/vota_web/names.tsv | /usr/bin/grep -c -x -F <symbol>` prints 1 for a kept symbol. Count that
match once, and check that none is left twice ([facts/workflow.md](reference/facts/workflow.md) §W16):

```sh
/usr/bin/grep -v '^#' splat/matched.txt | cut -d' ' -f1 | sort | uniq -d     # prints nothing when no index is listed twice
```

The stub file keeps both branches' removals; a conflict inside a `// <stubs>` run can take either side, since stubs
are comments and step 9 writes them again. Do not run `make -C src stubs` on the merge before step 9: until steps 7
and 8 rewrite the census and the symbol file and step 9 the scan, they are one side's, so the generator puts back
the stubs of the other side's matches and pending members and recreates, untracked, the stub-only files that side
removed. Step 9's `splat-match` runs it on the new scan and writes back what the merge holds
([facts/workflow.md](reference/facts/workflow.md) §W14). Every other generated file takes one side whole, with
`git checkout HEAD -- <file>` (it stages that side), conflicted or not: a `git add` of a conflicted file stages its
conflict markers. `splat/symbol_addrs.txt` is half generated, and a side taken whole keeps only that side's hand
edits, which step 8 cannot bring back, so first compare what each side holds below its hand-edit marker and carry over
by hand any line only the other side has.

The census snapshot conflicts as a rename/rename when your base's snapshot is still the one `main` renamed (`DD` on the
old name, `AU` and `UA` on the two new ones), and git has already merged both snapshots into your side's name, markers
included. Keep one name and drop the others from the index:

```sh
git checkout HEAD -- ledger/history/<your snapshot>
git rm -q --cached ledger/history/<the old snapshot>
git rm -q ledger/history/<the other branch's snapshot>
```

When `main` has replaced that snapshot since, it is a rename/delete instead: `git status --short -- ledger/history`
lists only the branch's snapshot, `DU`, left in the tree, and `main`'s is in no conflict. Remove the branch's, `git rm
-q -f ledger/history/<the branch's snapshot>` ([facts/workflow.md](reference/facts/workflow.md) §W19).

A header your unit needs that `main` gained after your branch started is an add/add conflict: create it from `main`'s
text (`git show main:<path> > <path>`) and only add to it, so the merge is one hunk, and say so in the commit. A
header that is not on `main` yet but on a branch that lands before yours: copy it from that branch byte for byte
(`git show <branch>:<path> > <path>`), claim it, and do not edit it. git merges an add/add of one blob with no
conflict (`git hash-object <path>` and `git rev-parse <branch>:<path>` print the same id;
[facts/workflow.md](reference/facts/workflow.md) §W17). If that branch changes the file before it lands, take
`main`'s text at the merge, as above. While the owner has not committed it, measure with a stand-in under `-iquote`
(step 4) and do not commit one: a copy of a working file is not the blob the branch will hold. Copy from the branch
only, and compare `git hash-object` with the branch's blob after step 9, since the generator rewrites a header's stub
run.

Your branch was written against the docs of the commit it started from. When `main`'s docs changed since, read your
unit's choices against `main`'s docs too before the merge (`git diff "$(git merge-base main HEAD)" main -- docs
src/README.md src/units/README.md`), since the merge lands under them.

Then run steps 6 to 10 again on the merge: link, census (`git rm` the snapshot you kept, add the new one), symbols,
match, build and the checks, and count lost matches against `main`. Some matches rest on the whole link and not on a
source, so a merge that touches none of them can drop them: after step 9 run the check of
[facts/splat.md](reference/facts/splat.md) §S10, which lists them, and stop if one left `match`. Commit it all as the
merge commit. A merge commit takes no pathspec (`fatal: cannot do a partial commit during a merge`): stage everything,
read `git status --short`, and commit with a bare `git commit -F -`, owning the checkout while you do, since nothing
else may be staged ([facts/workflow.md](reference/facts/workflow.md) §W18). Two branches that each took "the next free
NN" collide too; `src/units/README.md` "Names" says how to avoid that.

## Library functions

Most `differs` rows belong to upstream libraries (OpenSSL, SQLite, libc++, 7-Zip, RHVoice, …). We do not write
their C++: it is built from the library's own sources at the version `third_party/MANIFEST.md` pins. When such a row
differs, the code is usually right and something around it is not. The scan's `detail` column says which:

| `detail` says | what is usually wrong | how to look into it |
| --- | --- | --- |
| `an address of ours: … (.data) has no target symbol`, `… (.bss) has no target symbol` | the symbol file has no name for a data object the body uses, and its content does not place it either: what follows the `;` says why its re-pointed bytes did not (not in the target, several places of a writable object, too little content); a `.bss` object is zeros, so only a name places it | find independent evidence for that object (RTTI, a unique string or content, a census pair) and see whether `make -C src splat-symbols` picks it up; [reference/splat.md](reference/splat.md) §2 lists the evidence kinds and §3 how content places an object |
| `a table slot of ours: X has no target function` | the shifted link says the operand is a pointer to our function X, and the symbol file names no target function for X | the same as a callee with no target function: X's own match or name comes first (step 8) |
| `a table slot of ours: the target function fills N slots` | in a kind-unverified function, the operand may be a pointer to a function the target's table holds in more than 64 slots (binaryen's merged empty function fills 126); without its kind, re-pointing offers a function's slots only up to 64 | the source is not at fault: the check cannot re-point such an operand ([reference/splat.md](reference/splat.md) §3 "Operand kinds") |
| `the address resolves (symbol)/(string) to another place` | our data sits elsewhere: a different string merge, a missing or extra object, or another version's constants | compare the two strings or objects at the addresses the detail prints; check the version evidence in `third_party/MANIFEST.md` |
| `target i32.const N \| ours i32.const M` with small numbers | a table slot: the function-pointer table holds functions in another order, because another set of functions is address-taken | the roots TUs (`src/app/roots*.cpp`, the units' `-roots.cpp`) and the link order decide the table; [reference/link-order.md](reference/link-order.md) |
| `target call X \| ours call Y` | the callee resolves to another target function: a callee without a name, a twin, or an inlining difference | `pnpm wasm splat-remap … --against <index>` prints how every operand resolves |
| `the locals`, or an instruction that differs in kind | codegen: the compile flags (`-O` level, `-fPIC`, `-DNDEBUG`), the library version, or inlining | the library's flags and their evidence are in `docs/reference/facts/libraries.md` and `tools/libs/<lib>/census.json`; a root that exports or calls a function once changes what binaryen inlines ([facts/tool-traps.md](reference/facts/tool-traps.md) §X1); two bodies that differ in local numbers alone can come from the order of a caller's and its callee's objects (step 3, "Code binaryen inlined from another function") |
| `read-only object: bytes not in the target` | our constant data is not the target's: another version or another configuration (`#define`s) | `tools/libs/discriminate.py` lists the target functions that tell two builds apart |

To compare the two bodies side by side, read the target with `pnpm wasm fn ../target/vota_web_wasm.wasm <index>`
and ours with `pnpm wasm fn ../build/out/wasm/vota_web/vota_web_wasm.wasm <ours>` (the scan's `ours` column). A fix
to a library row is a change of flags, roots, link order or symbol evidence, so it can move many rows at once, and
it is checked the same way: link, census, symbols, match, splat build. If you are new to the project, start with
TSE functions; the library rows need the background in [reference/toolchain.md](reference/toolchain.md) and
`docs/reference/facts/`.
