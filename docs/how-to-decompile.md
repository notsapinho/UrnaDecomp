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
| 7. census | `make -C src census` | `ledger/functions.tsv` is rewritten |
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
7-Zip and libc++ bodies, binaryen's merged ones and the `src/app` stand-ins', and they are most of the smallest. It
also drops a TSE body whose group is a library's, `app` or `unknown` (3392, group `7zip`, was `api::CLp`'s constructor's
one unnamed callee): `awk -F'\t' 'NR>1 && $5=="differs" && $11 ~ /^app\/(uenux2|ecourna|asn1)\// && $9 !~
/^(vota|comum|api|simulador|vota-web|ecourna|asn1-modules|ASN1)$/ {print $1, $9, $11}' splat/scan.tsv` lists those
rows, mostly library templates compiled in a TSE object (142 at 182dc6c1).

Two kinds of row the filter keeps are not a TSE source to fix. A standard-library template a TSE object instantiates
is libc++'s code, and what differs is which copy binaryen keeps or merges ([Library functions](#library-functions)):

```sh
python3 -I -B tools/round/pick_pool.py --differs | awk -F'\t' '$2 ~ /^_ZNSt3__2/ {print $1, $5, $6}'
# 2499 vota app/uenux2/src/app/comum/carquivossavd.cpp.o        (at 182dc6c1)
# 2839 comum app/uenux2/src/app/comum/carquivossavd.cpp.o
# …
```

And a row whose symbol names another class than the target's vtable holding the index is a body the census paired from a
sibling class, one vptr apart, and its function is unwritten (10370, slot 0 of `api::CDataTextFmt<comum::(anonymous
namespace)::CComparecimentoMesariosDS>`'s vtable, was such a row until it was written). The vtable and slot that hold an
index: `python3 -I -c "import json,sys; i=int(sys.argv[1]); [print(e['class'], n) for e in
json.load(open('ledger/vtables.json')) for n, f in enumerate(e['functions']) if f == i]" 10370`.

The other pool is the functions not written yet, which have a comment stub in their tree:

```sh
python3 -I -B tools/round/pick_pool.py src/ecourna      # or src/uenux2, src/asn1, --tse for all three; --min/--max in B
```

It prints `index verdict size group file:line` for each stub of 40 to 600 B, smallest first. Their verdict is mostly
`no-candidate`: the scan found no body of ours for it, as the symbol file names none, the census paired none, and no
unmatched body of ours re-points into it. `no-candidate` is not the same as unwritten. A function can be written and
still have no body in our link, two ways:

- **Compiled and dropped.** Nothing in our link reaches it, so wasm-ld leaves it out, though its object is on the link
  line: its symbol is not in `build/out/wasm-map/vota_web/names.tsv`. A whole unit can sit so: what its objects define
  minus the link's names (`wasm-objdump -x -j linking <object>` against column 2 of `names.tsv`) lists them. Such a
  function pairs once a caller lands or the unit's `-roots.cpp` reaches it the way the target does (step 6).
- **Inlined into the one caller our link gives it.** binaryen inlines a function with one call site (step 3), so it
  has no index of ours until a second caller lands. A library function is the usual case: libc's `round` (2953) was
  `no-candidate` while one RHVoice function called it, and became a match, with no source of its own, when a TSE unit
  added a second caller. Look for its call in the object of a caller the scan already names.
- **Written, and nothing names it.** The scan finds a body through the symbol file, the census or its content, so a
  body it cannot name reads `no-candidate` with its object in the link, and only the fragment says it exists. 5660 (unit 89,
  `md::CCandidatura`'s constructor) was such a body, until its callee 2870 got the second caller the target gives it
  (unit 232's roots stand in for it) and both matched. A right body can read so too: 5658's definition under a `using` printed a short type
  in its record, so the record anchored nothing, and the row said `no symbol and no ledger pair` until the definition
  spelled the type in full (step 3). Run `check_srcloc.py --strict` on the unit's objects (step 10) before you read
  such a row.

The stubs tell these apart from an unwritten function. `tools/round/stubs.py` writes no stub for a function it finds
code of ours for, and `python3 -I -B tools/round/stubs.py --report` counts those by reason; a body the census paired
counts only when its symbol names the function's own class ([src/README.md](../src/README.md) "Stubs" has the rule). So a
`no-candidate` row with a stub is usually unwritten. A row without one usually has code to fix, or is a pending
member (steps 5 and 9), or one of the two kinds above. Three kinds break the rule, and
[facts/placing.md](reference/facts/placing.md) §P1 shows how to tell each: a function whose only records are an inline
member of a header another unit writes loses its stub unwritten; a library's code that TSE calls keeps a stub though no
TSE source writes it (its `owner` reads `app` when the library's own code is every caller); and so does a body binaryen
merged in the target, whose callers are thunks that pass it constants: write the thunks' functions.

The `group` column is the function's *component*, and a component says who uses a function, not where its code
lives: 238 uenux2 functions are in group `ecourna`, because they throw ecourna's `CBaseError<…>` template with a uenux2
enum, and their stubs are in `src/uenux2/`. Go by the tree that holds the stub, not by the group
([component and owner](glossary.md#component-and-owner)). A TSE function that loads no string, vptr or typeinfo has group
`app`, and `stubs.py` writes stubs for the TSE components only, so it is in neither pool: it reaches you as a callee or a
table slot of a TSE function you read, as 10255 does, the thread routine `api::CThread::Start` passes by table slot.
The attribution goes by neighbours, not by code, so `group` and `owner` can also name a library for a TSE body with no
stub: 1190 (`sqlite`) builds the screen that loads "CONFIRA O SEU VOTO", and its callers 1767, 3067, 6616, 6681 and 7787
are TSE code. Read an unmatched row of a library group whose callers are all TSE with `pnpm wasm fn` before ruling it
out.

A static object's destructor is in no pool and no reader reaches it: a `__cxx_global_array_dtor` is a 10- or 12-B body
that destroys one address, and only its table slot refers to it, which `__cxa_atexit` gets. 11550 is `f150(1838756)`,
slot 2365 (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'ref\.func:11550$'`), and
`/usr/bin/grep -rlE 'i32\.const 2365($|[^0-9])' build/out/splat/pieces/asm` prints nothing. The same search for
`1838756` lists 11550 and 187, the singleton that uses the object, so the row lands with that class's lane, and only
with a match that uses the object: the destructor's own vote for a `.bss` name is self-voted
([reference/splat.md](reference/splat.md) "No circular evidence"), and 11550 holds because 187 matches. An address one
row alone loads can be a field of a larger object loaded by its start elsewhere: look for a symbol-file line whose
address and `size:` cover it before calling it an object only that row reads (11620 alone loads 1838592, which is
`comum::CPath::s_pathFlash` plus 16: `/usr/bin/grep -n ' = 0x1c0df0;' splat/symbol_addrs.txt` gives its `size:0x18`).
When the readers inline a `GetInst`, that match is often another class's large slot, and the destructor waits for it. A
hand line may name the object instead when the reader's body, read without either match, ties the address to the class
(step 9, "Hand edits"): 10340 and 10341, `CMesarioRegistrado`'s `s_mutex` and `s_inst`, landed before their one reader
10337 (`IGestorDadoMesario::StartState`, which holds `CMesarioRegistrado::GetInst` inlined), which differs
(`/usr/bin/grep -n 'CMesarioRegistrado6s_instE' splat/symbol_addrs.txt`).

The third verdict with work left, `unresolved`, is in neither pool: 489 rows at 182dc6c1, 69 of them compiled from a
TSE tree. Each has a body of ours, and its `detail` names the operand that has no target counterpart:

```sh
awk -F'\t' 'NR>1 && $5=="unresolved" && $11 ~ /^app\/(uenux2|ecourna|asn1)\// {print $1, $7, $6}' splat/scan.tsv | sort -k2 -n | less
```

The detail's "has no target function" means that no target function is named for that callee. It is one of four
things. The examples are rows at 4487d6b, and a landing can match them; `awk -F'\t' 'NR>1 && $5=="unresolved" && $6 ~
/has no target function/ {print $1, $7, $6}' splat/scan.tsv` lists today's.

- **The target inlined it everywhere,** and the source defines it where ours keeps it out of line: 9604,
  `uenux_wasm_web_sound_wait_finished`, calls a `__tree` member of ours at +0xa5, and the target's 9604 holds no call at
  all (`pnpm wasm fn` lists none).
- **A `byn$mgfn-shared$` body:** binaryen merged the function with others of its shape (*mgfn*), and the target merged
  another set, so the fix is to write the missing members of the target's set, which can belong to another component.
  The shared body's callers (`pnpm wasm fn <wasm> <its index>`) name the members on each side, and a small body forms
  only from three or four of them ([facts/codegen.md](reference/facts/codegen.md) §C8). 3627, a
  `CPolySingletonList::has<…>` thunk of 11 B, calls such a body of ours, and the target's 3627 is `push f1166(p0,
  463836)`, a thunk into the target's own set. When both links form the same merge, the shared body's name is the
  callee, and step 9's hand edits say when it takes a line. The same thunk can read `no-candidate` with its symbol in
  our link, when our link merged a set the target lacks: score it against the target's body.
- **The row's own symbol:** the body is recursive and waits for a name, since an unnamed function has none to re-point
  its own call through. 1159, `__tree<unsigned, CVotosCargos>::destroy`, calls itself twice. The name comes from a
  caller (`;; callers (6): 1159 5734 7787 11349 11486 11487`), and the census's pair among twins can be another
  instantiation than the callers'.
- **The target has it as a function of its own, and nothing has named it.** 11378 says `call 4085:
  _ZN5comum2md10CMunicipioC2E… has no target function`, and the target's call at that offset is `call 3712`, which no
  line of the symbol file names (`/usr/bin/grep -F '= func:3712;' splat/symbol_addrs.txt` prints nothing). Read the
  target's `call` at the same offset with `pnpm wasm fn` on both bodies, or score them: a body that differs in operand
  rows only is this case. 11378 is `score 3 over 72 rows (… [3 operand-only] …)`. Step 8 says how such a name comes.

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

A record's function column (6) is empty when the code that loaded it is gone, as for 29 rows (`awk -F'\t' 'NR>1 && $6==""
{n++} END {print n}' ledger/source-locations.tsv`). The search by index then prints nothing, though the throw's literal
stays in the data and `check-srcloc` still holds it to its line. For a class whose bodies look emptied, search by file:
`api::CPosixRWMutex`'s constructor 10245 has three such throws (`awk -F'\t' '$2 ~ /cposixrwmutex/ {print $1, $3, "[" $6
"]"}' ledger/source-locations.tsv`). Such a record can also be a test of an argument binaryen folded (step 2), whose
message is among the strings no function loads ([facts/reading.md](reference/facts/reading.md) §R1 finds it).

A TSE function not decompiled yet usually has a *stub* in that tree, a generated comment where the evidence says the
function sat ([src/README.md](../src/README.md) "Stubs"). Find it by its index:

```sh
LC_ALL=C /usr/bin/grep -rn '^// f6734 ' src/uenux2 src/ecourna src/asn1 | iconv -f latin1 -t utf-8     # the files are Latin-1
# src/uenux2/src/app/comum/dados/celeitores.cpp:106:// f6734 · 6461 B · unmatched · name unknown      (at e7d03612)
```

(Use `/usr/bin/grep`: in an agent's shell `grep` can be a shell function that prints nothing and exits as if nothing
matched, with `LC_ALL=C` or without, so a negative from it is no evidence.)

The line under it is the stub's signature. It names the function only when `splat/symbol_addrs.txt` does; today no stub
does, so each reads `f<index>(<wasm types>)`. Get the name from the records (the `awk` above), from the vtable slot the
`fn` readout gives (step 2), or from `ledger/vtables.json`. A record names the function that holds the throw, and that
can be an inlined callee: f1455's stub had records for both `CVotacaoStateAudio::PlayFile` and
`CVotacaoStateAudio::PlayKey`, so one of the two is inlined into it, and 1455 matched as PlayKey. The function is the
one whose code holds no second prologue (step 3, "Code binaryen inlined from another function"): 2767's records name
`CFile::Flush` (`cfile.cpp:145`) and `CEncryptedFile::Save` (`cencryptedfile.cpp:88`), Flush's code sits behind a second
prologue, and 2767 is Save. When every record lies behind a second prologue, none is the row's: it has no record of its
own, its stub's file is a callee's, and it takes a name as "Names no evidence gives" says (step 3) and a place from what
only its code creates (rule 5): 4625's four records are `cpacotearquivos.cpp`'s, each behind a prologue, and the one
store of `comum::CInterfaceMensagemVazia`'s vptr (1532504) puts it before `votadefs.cpp`'s first record, where that
class's vtable copy lies (`/usr/bin/grep -rlE 'i32\.const 1532504($|[^0-9])' build/out/splat/pieces/asm` prints only its
piece). A slot that a base class fills with a default of its own has no record, but its overriders in the same slot of
the derived classes' vtables may have one, and that names the slot. For a base and a slot number, the records of every
derived class's function there:

```sh
python3 -I -c "import json,csv,sys; vt=json.load(open('ledger/vtables.json')); cl={c['name']:c for c in json.load(open('ledger/classes.json'))['classes']}; base,k=sys.argv[1],int(sys.argv[2]); d=lambda n: n in cl and bool(cl[n]['bases']) and (cl[n]['bases'][0]['name']==base or d(cl[n]['bases'][0]['name'])); fs={e['functions'][k] for e in vt if d(e['class']) and len(e['functions'])>k}; [print(r[5], r[4]) for r in csv.reader(open('ledger/source-locations.tsv'), delimiter='\t') if len(r)>5 and any(f.isdigit() and int(f) in fs for f in r[5].split(','))]" comum::CAppState 3
# 7352 virtual bool vota::CEleitorVotando::NeedChangeState()
# 11858 virtual bool vota::CDefineRotaPosReinicio::NeedChangeState()
```

`comum::CAppState`'s slot 3 (7480) is `NeedChangeState`. Take a `virtual` record only: a non-virtual name there is a
callee inlined into the overrider. A log text can spell a member too: search `ledger/strings.tsv` for `<Class>::`, the
overriders' classes included. `CWasmSavd::RecebeMensagem - mensagem de tamanho invalido` names `comum::IInterfaceSavd`'s
slot 3, as a chosen name, since a string cannot tell the overrider from a private callee inlined into it. When none of
these names the function, step 3's "Names no evidence gives" says how to choose a name and mark it.

A class's virtual members are its vtable's slots, and a member's stub can sit in the file of a function inlined into
it, so a file's stubs miss some of them. Each slot of a class, with its scan verdict, the scan's symbol and its stub:

```sh
python3 -I -c "import json, sys; [print(n, f) for e in json.load(open('ledger/vtables.json')) if e['class'] == sys.argv[1] for n, f in enumerate(e['functions'])]" 'vota::CImprimindoBEHB' |
  while read n f; do printf '%s\t%s\t%s\t%s\n' $n $f "$(awk -F'\t' -v f=$f '$1==f {print $5, $2}' splat/scan.tsv)" \
    "$(LC_ALL=C /usr/bin/grep -rn "^// f$f " src/uenux2 src/ecourna src/asn1 | LC_ALL=C cut -d: -f1,2)"; done
# 1	144	match _ZN9simulador23CFingerPrepareSimuladorD0Ev        (at 182dc6c1)
# 2	12074	no-candidate -	src/uenux2/src/app/vota/eleitor/fimvotacao/cimprimindobehb.cpp:2
# 3	7480	match _ZN5comum9CAppState15NeedChangeStateEv
# …
# 5	218	match _ZN9simulador23CFingerPrepareSimulador7PreparaEv
```

A slot can hold a body many classes share, and the scan names it after one of them: 218 here is one empty
`(i32)->()` function that fills 126 slots of the target's table (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm |
/usr/bin/grep -c 'ref.func:218$'`). A slot that is `no-candidate` with no stub is usually a pending member of a landed
unit (step 9).

A stub marked `placement: link order` has no record that gives it a line, and one in a tree's `unplaced.cpp` has no
evidence for any file: step 3 says where its code goes then. Neither its file nor its tree is evidence on its own, and
a stub can sit over code we have, since `stubs.py` cannot see a non-virtual function that has no record. So before you
write a stub's function, read its `fn` readout and search our sources, the units' companion files included, for that
class's constructor, destructor or method, and decide the tree from the callers' records and the landing pads
([facts/placing.md](reference/facts/placing.md) §P1).

A stub is only a comment: the target's bytes never enter the build, and there is no `INCLUDE_ASM`
([reference/include-asm.md](reference/include-asm.md) says why). Until your C++ replaces it, the function's bytes
come from its piece in the splat build.

## 2. Read it

```sh
cd asmlift-wasm
pnpm wasm fn ../target/vota_web_wasm.wasm 1931
```

`fn` prints the disassembly, a *folded readout* (the stack replayed into expressions), the strings it loads, its callers
and callees with their components and best pairs, and the vtable class and slot it fills ([the
toolkit](glossary.md#the-toolkit)). The "strings referenced" list reads every `i32.const` in the data range as a
pointer, so an error code can show up as a string (1931's `4725` is an error code, not "Tipo de identificador…"), and
so can an allocation's size, a multiple of an element's size or a table slot that falls inside a literal
([facts/reading.md](reference/facts/reading.md) §R23 reads each by its use). The
readout is approximate in order too: it hoists a `local.tee` and a call out of a nested expression, so a value a later
`tee` overwrites reads as the new one (8827 passes the old `p1` as its fourth argument, and the readout prints the new),
and a call printed as a statement can come after writes the disassembly has first (995). The compiler also reuses a
parameter's local on a path that ends in a throw, so a `p0 = …` line does not mean that a later `p0` sees that value
(6734 writes local 0 six times, and its `i32.store8[p0+1]` reads the parameter). Read an order from the disassembly, or
from `pnpm wasm score` against your body, and follow a path to its `unreachable` there when a claim rests on a value.

A piece's file name and the `;; <name>` after a `call` in it are the census's pick among bodies that tie, not the
symbol file's name ([reference/splat.md](reference/splat.md) §1): take a name from `splat/symbol_addrs.txt` or
`splat/matched.txt`, and a thunk's from the slot it passes. A call made inside a `try` goes through an emscripten
`invoke_<sig>` import whose first argument is a table slot, and `fn` lists such a slot as a string too, with only
`import:invoke_…` among the callees. The lifter (step 3) names the function behind each slot: `invoke_iii(6708 /* &f339
*/, …)`. A function pointer passed as a plain argument (a thread routine, a comparator, a callback) is a table slot as
well, and neither `fn` nor the lift names it: 1684, `api::CThread::Start`, passes 4527 to `IThreadImpl::Create`, and
`fn` lists `4527 (+22 into 4505) "Falha ao obter valor do semáforo: {}"`. So is one a function stores: a
`std::function` built from a function pointer stores the slot beside its `__func` vptr (12040 stores 1529, and
`elem[1529]` is 12039). Read every `i32.const` that `fn` lists among the strings against the element section, whatever
reads it; `ledger/callgraph.tsv` holds direct calls only. An `invoke` says the callee could throw when
emscripten made the call, which is before binaryen simplified it: a callee whose final body cannot throw had a call that
could, such as a `std::mutex::lock()` ([facts/reading.md](reference/facts/reading.md) §R15). The element section gives
the function behind a slot, and it counts among the callees:

```sh
wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[4527\] '
#   - elem[4527] = ref.func:10255
```

One function can fill several slots, each a symbol of its own, so look up every slot of a merge thunk's family
([facts/reading.md](reference/facts/reading.md) §R16). A constant equal to a slot number can be an integer: read it in
the shifted link, not the plain one (§R18), and by the parameter or member that takes it (§R23).

`ledger/callgraph.tsv` holds direct calls only, so it misses such a callee too. `pnpm wasm bundle`
writes the same readout for a list of functions into `ledger/bundles/<name>.md`, which is how to read a whole
class at once. `ledger/classes.json` and `ledger/vtables.json` give the class's RTTI name, bases and virtual slots,
the starting point for its layout. They do not say whether the class is `final` or its destructor out of line; step
5 reads both from the destructors' bytes. `vtables.json` misses classes that have a vtable, so a missing row is no
evidence: [facts/units.md](reference/facts/units.md) §U12 finds a vtable by its typeinfo and reads its words.
`classes.json` misses some too, and `fn` then names no vtable class for a slot the function fills; and a row can run
past its vtable into the next object's words. Read a slot's vtable in the data when either can be the case
([facts/reading.md](reference/facts/reading.md) §R20). `fn`
lists a function's direct callers; the functions that store a class's
vptr (`vptr` in `ledger/vtables.json`, the vtable's address plus 8) are found in the split's pieces after a splat
build, constant loads only (an address computed from a base is missed):

```sh
/usr/bin/grep -rlE 'i32\.const 1599000($|[^0-9])' build/out/splat/pieces/asm     # comum::asn::CConversorHashArquivo's vptr
# build/out/splat/pieces/asm/comum/10266.wat
```

A throw that builds its message with `std::format` stores two i64 constants that spell the call
([facts/reading.md](reference/facts/reading.md) §R13): `(length << 32) | address` of the format string, whose text
`ledger/strings.tsv` has at that address, and the argument types packed 5 bits each, the first argument lowest, as
libc++'s `__arg_t` numbers them (3 `int`, 6 `unsigned`, 12 `const char*`, 13 a string). 11050 stores `103079218254`, `24
<< 32 | 3150`, the 24 bytes `"Operação desconhecida {}"` at 3150, and `3`: one `int`. An enum with a formatter of its
own is code 15, with a table slot beside the value, and a site has three shapes, of which one depends on the level
(§R13).

A by-value member whose type no header of ours defines needs that header before the class compiles: write the data members
at the offsets the bodies give and declarations only of the members a record names, say that the layout is all that is
recovered, and claim it like any new file. A member whose code a function you write holds inlined is defined there, and
a type with a vptr needs its vtable to link; a class your bodies need complete only to call a base's slot gets its head
alone ([facts/placing.md](reference/facts/placing.md) §P7 has the three cases).

The wasm parameters follow the C++ ABI ([facts/reading.md](reference/facts/reading.md) §R1–R3, §R12). A member function
takes `this` first. A function that returns a class by value takes the result's address as a hidden first parameter, so
target 9131, `MunicipioZona CConversorMunicipioZona::DoConverte(const CMunicipioZona&) const`, is `(i32 i32 i32)->()`.
A trivially copyable class that holds one scalar comes back as that scalar (3641, `CTime CTime::operator-(int) const`,
is `(i32 i32)->(i32)`). A class passed by value is the address of a copy the caller makes, unless it is one scalar: a
by-value `std::unique_ptr` is the raw pointer. libc++'s `std::shared_ptr` is trivial-ABI in this build, so the callee owns
the copy, and a constructor that moves one into a member copies its two words and writes nothing back (5587), where a
`&&` parameter would be nulled and a `const &` one's count incremented. Read a parameter's form from what the callee
writes to it. When the callee writes nothing (an empty override), only its callers show the form, and only in part: a
missing copy of an lvalue of the parameter's own type rules out by-value, and the order of two temporaries' stores
tells the forms apart, while a copy says little; a small struct built from constants is stored twice, and a by-value
class temporary keeps a frame slot of its own ([facts/codegen.md](reference/facts/codegen.md) §C10 has the cases, with
5904's `std::function` callback, a reference). Mark what is left as chosen. binaryen changes the type further:

- its dead-argument elimination removes a parameter every caller passes as the same constant and puts the constant
  in the body: 5890's record has three parameters and its wasm type two. So a constant the body stores, or passes to a
  call, can be an argument of the source; write the parameter, marked as a reading unless a record shows it, and give
  the roots callers that constant (step 6). A record no function loads (step 1) can be the throw of a test of that
  argument: write the test at the record's line (§R1). The pass runs before binaryen's inlining, so a constant that
  inlined code produced stays a parameter: measure the callee's wasm type in the link before choosing the caller's form
  (§R1, §R18). §R1 has two more signs of a folded parameter: a callee clang inlines only when the caller writes the
  constant (921 over Store), and a body with the constant in place whose parameterized form equals another body (2262).
- a constructor and a non-deleting destructor return `this` in the object, and the same pass drops a result no caller
  read. A stub's `void` is the target's type, so it says nothing of the source's result; a roots file declares such a
  function with the object's `int` result (`src/units/README.md` "Companion files").
- a body one row off the target, a `drop` after a call or a constant before it, is the callee's signature, which differs
  between the links, so the caller's source is right: the callee is in one table and not the other, or the reader of its
  result is code inlined into a function both links hold, such as a static initializer (§R18).

For a virtual function, take the signature from the base class that declares the slot (the `fn` header names the
vtable class and slot), and from the overrider's records where they disagree: a header of ours is a reconstruction
too. An override spelled as the record does not override a header that differs, and one spelled as the header has a name
the record contradicts. Fix the header when no other active stage claims it,
even one every unit of a tree compiles: claim it, keep the objects the edit rebuilds and compare them afterwards
([agents.md](agents.md) "Shared build outputs"), and check that its matched users still verify (step 10). When another
stage holds it, keep the member pending (step 5) and report the difference. One exception: a declaration change of a
non-virtual inline member there (a setter that returns the item for a chained call) that leaves every other object
`cmp`-equal to the base's goes in your commit as a hunk apart from that stage's, named in your result with the matches
that rest on it (11888's `CMenuItem& SetDado` in `cinputmenufield.h`, unit 104); anything more waits for that stage.

For the ASN.1 converters there are two bases, and the namespace of the base's RTTI name in `ledger/classes.json`
says which: ecourna's
`ecourna::api::asn::IConversorASN<ENTIDADE, DADO>` in `src/ecourna/api/asn/iconversorasn.hpp` (slot 3 is
`DoDeconverte`), and comum's `comum::asn::IConversorASN<ENTIDADE, DADO>` in
`src/uenux2/src/app/comum/asn/iconversorasn.h` (slot 3 is `DoDesconverte`). Slot 2 is `DoConverte` in both. A field
the converter sets through a temporary of the field's type (its constructor's call and a vptr store before the
store) is a setter that takes `x::const_reference`, which the generated modules choose per field: change the module
([facts/asn1.md](reference/facts/asn1.md) §A3). So is a field whose holder (`entidade.set_carga()`) the target loads
before the call that computes the value, since a member call evaluates its object before its argument and an
assignment its right side first: write `x.set_f(value)` (11399; §A3 has both signs).

## 3. Start from the lifter

```sh
TMPDIR=/tmp pnpm wasm lift ../target/vota_web_wasm.wasm 1931 -o ../build/out/lift --check
```

This writes `build/out/lift/1931.cpp`, which `em++` compiles. It is a starting point, not code to commit. Rewrite it
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

**A form chosen for the code it gives.** The lift keeps the target's order of loads and stores, and the source has to
give it back. That order is evidence of the source's form ([facts/codegen.md](reference/facts/codegen.md) §C1): stores
whose values were all read first come out in the reverse of the source's order (a zeroing the size of a `memset`
excepted: its order follows the constants used before it, §C1). A lift whose stores run backwards over a struct (+6, +4,
+2, +0 in 11067, `api::CLineField::Rect`) comes from values read into locals before the aggregate is built; a
constructor that moves every argument out before its first store into the object and stores the vptr last (3660,
`api::CSubReport`'s) delegates to a constructor that takes them by value again, unless that callee stays a call with no
`this` result: then it is a function that returns the object its complete constructor builds (3682 and 5558 over 5557,
§C6). A call through `vtable[N + 4*x]` after an unsigned range check of `x` is a `switch` whose cases call consecutive
virtual slots, its `default` the code under the check (§C2, 11050); write the switch, not a table of member pointers.
Such a form is source when it is ordinary C++ in the project's types: a local that holds a value the function reads, an
order of evaluation, a temporary, a delegating constructor. A construct whose only purpose is to steer the compiler is
scaffolding and never lands: `volatile`, an `asm` barrier, an attribute, a `may_alias` cast, a `goto`. An ordinary type
the function uses only for the code it gives is source only where the target shows the object it stands for: 1695's
always-engaged `std::optional<CApplicationContext>` is the 56-byte object its frame holds (§C5), a type TSE uses
elsewhere, marked chosen among the forms that give the same object (unit 171). When a form stands in for a header that
is not the original's (an aggregate where the target has a constructor), say so in the fragment's header comment. A
function the target holds inlined at every use is a form too when only a call there gives the measured code (a predicate
or a setter over a member): write it as a member of the class it reads, its name and membership chosen, and give the
in-place forms' scores; a lambda or a helper written only to steer a choice the target's bytes do not show is
scaffolding (`CEstadoGeralVota::IsFimAquisicaoMarcado` for 10734, unit 93; `CAppState::SetNextState`, unit 61). A
helper whose existence the frame shows (its locals above the caller's, or dropped results sharing slots,
[facts/codegen.md](reference/facts/codegen.md) §C5) is a reading of the target: write it with its name and linkage
marked chosen (2383's file-static helper, unit 110). A value the target computes ahead of code of an earlier statement
(before a copy's branches or a release) was a local declared above it (12055's layout values, unit 37). And a form that
is ill-formed with no diagnostic required but compiles to the same code in every TU may land when it is the only one
measured to give the bytes, its comment naming the rule it breaks and the forms measured that keep it: an
internal-linkage helper a header template calls (`ReadWholeFile` in `src/ecourna/api/io/asn/serialization.hpp`, for 2280
and 11419).

An order is evidence only where the forms you compare give different orders in the target function's own shape:
compile both there. The vptr store before a member's says the base's constructor sets the member, the other way the
derived class's, and in some call shapes both layouts give one order (§C1, "Which class holds a member"); two
assignments that meet after a branch keep the source's order only between equal costs (§C1). Four near-identical runs
in a lift can be one loop the target's level unrolled: `simulador::CWasmScreenMT::Refresh` (8746) is a range-for over
four lines, and four explicit appends give another block placement ([facts/levels.md](reference/facts/levels.md) §V3,
unit 78's fragment). An inlined library algorithm leaves no name: its body is evidence of what it computes (a search's
direction, a halving), not of the call, so write `std::upper_bound` when it is the plain way to say it and list the
hand-written loop that gives the same bytes beside it (unit 13's fragment does). When only the loop gives the target's
bytes (clang keeps the library body out of line where the target has it inlined), the loop is scaffolding: write the
call, leave the row `differs`, and put both measurements in the fragment (unit 137's `CPrng::GetInt`, 9500). That
case copies a library function's own code; an ordinary expression for the same value is a source form, written when
only it gives the bytes and listed with the call's score (10451's conditional, where `std::min` gives `llvm.umin`, unit
221).

To measure "the same bytes" for one function of a TU, compare that function's disassembly between the two objects with
the object-local numbers masked, against a control compiled beside the variants under a name of the same length, not the
landed object, and count the lines each cut takes before reading a 0
([facts/tool-traps.md](reference/facts/tool-traps.md) §X12 has the masks, the control, and a name of another length
that moves data addresses alone). Mask with Python, or `[[:<:]]` in `sed`: macOS `sed` has no `\b`
([facts/workflow.md](reference/facts/workflow.md) §W9). `cmp` of two objects compares the whole TU, and a variant of one
member then fails it. Change one occurrence per variant: a text substitution that matches twice rewrites another member
too. [facts/codegen.md](reference/facts/codegen.md) §C1 lists the other ways such a comparison lies (a copy's path moves
every offset, the edit can sit in a callee, a compare's operand order is the link's).

The lifter names a callee from the ledger's pairs, not from the symbol file, so a callee can be `extern "C" …
f219(…)` although `splat/symbol_addrs.txt` names it (`_ZN4ASN18SEQUENCEC2EPKv = func:219;`, the
`ASN1::SEQUENCE` constructor). Look a callee up there by `func:<index>;` before you guess.

**A callee can be a twin.** binaryen merges byte-identical functions, in the target and in our link alike, and keeps one
name for the body. So a callee's name in `splat/matched.txt` or the symbol file can be another function's that compiles
to the same bytes: 760 is matched as `std::vector<std::pair<unsigned long, unsigned long>>::push_back(&&)`, and in the
target it is also the `push_back` of another vector of an 8-byte element: 11361, the converter of
`comum::asn::CConversorSituacoesEleicoes`, which builds a `std::vector<comum::md::CSituacoesEleicoes>`, calls 760 (`pnpm
wasm fn ../target/vota_web_wasm.wasm 11361`, from `asmlift-wasm/`, shows `call 760` at +0x93). Write the call your
source makes. If your instantiation compiles to the same bytes, our link merges it into the matched body and the call
re-points to the target's function; if it does not, the target has no such body and the caller cannot match with that
call. When your object comes first in the link, its symbol becomes the survivor's name and the existing match line has
to follow it (step 10, "A twin whose name moved"; [facts/splat.md](reference/facts/splat.md) §S6).

Two cases go the other way. **An instance of yours can take a library's match.** A template your source instantiates is
a copy that links ahead of the library's, compiled at your tree's flags. `FillPath` calls `std::vector<double>::insert`,
so `cwasmscreen.cpp.o`, ahead of the RHVoice objects, defined `__insert_with_size` with `-fno-strict-aliasing`, its
directory's flag then. The target's 2662 has TBAA, its body changed, and `splat-match` stopped with `matched.txt only:
[2209, 2662, 5255]`. A unit's roots file cannot fix it, since those link after uenux2's: a tree root,
`src/app/roots_uenux2.cpp`, links ahead of both trees and keeps the right copy, an explicit instantiation whose callees'
rows you read afterwards, since it brings their copies too (`src/units/README.md` "Companion files" has the tree roots'
rules). The root compiles at the flags of the object whose copy the target keeps, which can be another tree's than the
template user's ("Companion files" says when, and what a root at flags no root has takes).
**Our link can merge what the target keeps apart.** 305 and 608 are two functions in the target, kept apart by the table
slots of their landing pads, and were one body in ours, so 3387 read `target call 608 | ours call 305` until the
executable TU's own copies, with those pads, linked first (unit 170). No source form of the caller fixes that: a
spelling that differs on purpose is scaffolding. Leave the row `differs`, with the measurement in the fragment. The
same merge can take a match you hold: a body twin-matched under another instantiation's symbol leaves `match` when
the link gains the target's own instantiation and the two differ in a constant only (`splat-match` stops on
`matched.txt only`). Give the link the target's copy of the other instantiation from the tree root whose flags give
it, so the two stop merging (9531, `vector<path>::__init_with_size`, against `vector<string>`'s 5585 from
`roots_coderenv.cpp`). And where the target holds two bodies of what our link would make one symbol, one per tree, the
second user's source spells another instantiation, since a root keeps one copy of one symbol: uenux2's
`assign(v.begin(), v.end())` took the ASN.1 runtime's `__assign_with_size` (3476) and five matches, and
`assign(v.data(), v.data() + v.size())` gives uenux2's own, 5704 (`src/asn1/asn1.h`, `CoderEnv::setVisitors`). After a
new user of a library template the runtime also instantiates, `llvm-nm` the new object for the symbols the runtime's
match lines name.

**Code binaryen inlined from another function.** The lift writes inlined code in place, whether clang inlined it (the
source defined it in the class or in the header) or wasm-opt did (the source defined a separate function, which had one
caller in the link and so has no target index of its own). These signs say wasm-opt, each in
[facts/reading.md](reference/facts/reading.md) §R10 with its case: a second stack-pointer prologue inside the body (in a
leaf, an `i32.sub(g0, N)` with no `g0 =` after it), or a frameless caller's statements ahead of the only one; arguments
widened as for a call and held in locals (`i32.load8_u`, `i64.load32_u` narrowed only at a call); a value read back
right after it was stored, a by-value `std::shared_ptr` copied word by word out of a frame temporary; a test of the
caller's `std::string` temporary after a constructor that is no call; an outer `block` left with `br 1` where ours
returns, an `if (result i32) … else 0 end` tested again or carried across the epilogue; an inlined constructor's
returned `this` held in a second local (5856), or used after its code where a call of the C1 its own TU defines drops
it, which says the constructor is another TU's (§C6; 2733, 2738, 5702: rule 2 below counts it); a prologue in each arm
of a branch (two one-caller functions, 5604's ORLC setters); a member's address added once to `this` after the
prologue, the loads at small offsets from that local (5665's accessor).

A frameless callee leaves none of them, but one that returns an object or takes one by reference keeps its loads and
stores of it through a local that holds the object's frame address; a prologue is the frame of the function around the
code, not always the one whose records the code holds (§R10, "Whose frame a prologue is", has both). When ours holds
inline a function the target calls from several places, and the caller's object keeps it out of line, binaryen inlined
it into the one caller our link gives it: a roots stand-in that gives it the target's call sites is the fix, not a
question for clang. A body that differs in local numbers alone can be such a callee (try it out of line before a source
form), a leaf whose result binaryen dropped after the locals were laid out (§R10 has 728, 3890 and 3510), the caller's
and callee's order, the object's own locals, or an inlined member's being static (§C4 has the last three); §R10 has one
remainder none of these closes (a parameter copied before a loop) and a zero set the order moved. Write such a function
out of line and leave it unrooted, so that it has one caller in our link too, and in another TU than its caller when
clang would inline it or read its attributes there (8533's tone sequences); "Names no evidence gives" below says which
class and namespace it takes, §R10's last paragraph which tree, and §C4 how a measured order picks its file when no
record or data names one. Linkage decides clang's inlining in the same TU: an internal function with one call there is
always inlined, so code behind a frame of its own is an external function's, another TU's, or an internal one's with a
second caller the link dropped (§R10 has unit 135's builders, 5455's `ReplaceDir` and unit 71's `MontaTela`). A template
instance takes internal linkage from an argument that has it (a lambda of a function that is not inline, a type in an
anonymous namespace), so the rule reaches its one-call helpers: a `std::sort` with a lambda holds its helpers in one
frame (four parameters), one with `std::less<>`, an `operator<` or a function pointer in frames of their own (five;
3762 against 5769, unit 383's fragment). One shared
frame is what both linkages give under clang's threshold, and the linkage can still change the caller's code: compile
both (5652's ids helper, §R10). A target function whose body is a library inline member's, called out of line from
several TUs, is a function of the project's that holds it (1922, §R10), and a member that writes its class's state where
clang would inline it in the class's `.cpp` goes in a `.cpp` of its own (5400, §R10's last paragraph). A callee's
records lie in the data of the object that defined it, which names its file
([facts/placing.md](reference/facts/placing.md) §P4).

The order of a caller and its callee can decide what binaryen makes of them. When two bodies differ in locals, a
pointer stays in a local where the target folds it, or a value the caller passes to an inlined callee is computed inside
the callee's code where the target computes it at the inline site, before the callee's prologue (11888's screen's
`bool`, unit 104's fragment), try the other order of the caller and its callee, the data's first, before hunting a
source form: in the link for two objects, and in the `.cpp` for one, where a function with no record has a free line and
records leave room. Either order can be the target's, and the target's data give the objects' order (§P4): when both
orders give the bytes, keep the data's, and a body that holds a chain inlined from several objects can need the order of
all of them (4454), and a chain over a `.cpp` and another object each definition order tried with each object order
(2772).
Try both orders again after each fix: the better one can flip (3819). §C4 has the method, the orders
a source can give, and a way to try module orders on the link's own binaryen input without relinking. Say in the
fragment that the order is measured. Two objects' order is their units' lists' order, so a file, a landed one too, whose
order against another unit's file decides a body moves into that unit's list
([src/units/README.md](../src/units/README.md) "Names"), and a new file whose order decides no byte takes the place of
fewest inverted pairs among those "Names" weighs, which can be another unit's list (and says what to do when that
list's fragment is another stage's). Rows that differ in frame offsets alone come from which values the source names:
the first local or temporary it creates takes the highest offset, so a named local against a temporary moves them (5472
and 5473 match with the `CDateTime` a named local). A callee clang inlines brings its locals in above the caller's own,
so a temporary above locals the source must create before it points at an inlined helper, algorithm or lambda (11394's
loop temporary above its list and converter). They can also come from what else the TU instantiates, before the function
or after it: an inlined `always_inline` template takes its stack slots from the instances the TU shares, and the copy
the target keeps can be another TU's; read where the target's record of the copy lies first. A frame larger than what
its code addresses holds a wrapper whose extra member folded away, objects whose code is gone, or a by-value result
larger than what the caller reads; a frame short by one object's slot is stack colouring (all §C5).
[facts/codegen.md](reference/facts/codegen.md) also has what decides a throw path's blocks and where its pad lies
(§C11), a loop's shape (§C12), a store in each arm of a branch (§C13), a condition's test order (§C14), what orders a
function's blocks (§C15) and the loads a declaration decides (§C16).

binaryen inlines a function with one call site only (counted after the first duplicate-function-elimination and before
merge-similar-functions and the second, so two functions identical in the objects are one by then:
[facts/tool-traps.md](reference/facts/tool-traps.md) §X1, with two exceptions in §R10: a body of a few instructions is
inlined into every caller, and two bodies identical in the objects are one only when their callees are), so the same
inlined code in two target functions means clang inlined it in at least one TU (an observer's detach in both 2778 and
5902). Write such a member with the `inline` keyword, which raises the cost up to which clang inlines (§R5): a form
clang leaves out of line matches only while it has one caller. The copies can differ, one clang's and one binaryen's,
which the result pointer shows (3829 and 3830): measure `inline` before writing it
([facts/codegen.md](reference/facts/codegen.md) §C3 has both cases). And a body of ours with a `call` where the target
has a second prologue can be a merge with a twin that only a root keeps alive, so look for that twin before a source
form. The other way, a new call of a member binaryen inlines into its one caller keeps it out of line and takes that
caller's match: before calling from new code a member another unit's notes say binaryen inlines, link and look for it in
`names.tsv` (`CThreadVota::IniciaContexto` and `GetEstado` called from `CThreadOperador::Run` showed up there as
functions, and unit 165's 4705 and 4713 match with them inlined).

**When no record names the file**, as for every stub in `unplaced.cpp`, choose the path the way the landed
units do, and say why in the fragment's header comment (step 6):

1. a header of the class that already exists names the directory (`src/ecourna/app/dados/asn/resultadournacadastro/`
   for `CConversorDadosComparecimentoCifrado`), when evidence gave its path: a header whose path an earlier unit chose
   names nothing, and moves beside the source rule 2 places; when rule 2 places its classes in two directories, or a
   class's members in another class's file (§P2), it stays, its path marked chosen with the place it is not beside;
2. else the directory of the objects linked beside a function only the class's own object defines: a constructor or a
   member defined out of line, the key function. A constructor counts only when its class's object shows it out of
   line (a record, the key function beside it, or a caller that keeps its returned `this`, which only a call into
   another TU gives: §C6): an inline one's linkonce copy is kept from its first user and names that user's directory
   (2738 sits among vota operador objects, unit 221; 3614 keeps its result). Read its
   neighbours in link order and take the stretches of
   `ledger/tu-clusters.tsv` among them whose label is a record's. The vtable's slots, the inline members and, for a
   class with no key function, the destructors are linkonce: the link keeps the copy of the first object that emits
   them, often a user's. This wins over the namespace and over rule 3: `api::CTextFieldUpdateMT`'s out-of-line members
   sit beside `app/vota/operador/` objects, so unit 51 puts the class in `app/vota/operador/comum/`, though no record
   names an `api::` class under `app/`;

3. else the directory where the class's family has records or landed sources: the ecourna `CConversor*` converters
   are in `app/dados/asn/` (or its subdirectory for their family), and the data classes they build in
   `app/dados/`; a comum converter is in the subdirectory of `app/comum/dados/asn/` that mirrors its data class's
   directory under `app/comum/dados/md/` (`asn/` itself for a data class in `md/`). When that directory's own files
   run in name order in the data and the class is not where its name sorts, the directory is a choice against the
   data: say so in the fragment, with the two neighbours (unit 63's `md/cregra*.cpp`);
4. the file name is the class name in lower case (`cconversormunicipiozona.cpp`, `cmunicipiozona.hpp`). A class
   whose only records are in another class's file has no evidence for its header: declare it in that file's header or in
   its own lower-case header beside it, and mark the path as chosen ("Names no evidence gives", below);
5. a free function with a target index of its own and no record or class goes by its use band when its band
   neighbours are functions one object alone defines: a file of its namespace whose object links there, read in the
   data's record order, and not a caller's file the band contradicts (1487 and 1488 in `votadefs.cpp`, above
   `EhTreinamento`). A caller, or the one function that passes its table slot, gives only a reason, which decides where
   the neighbours are linkonce copies kept from their first user (10539, which only 1150 passes by slot, sits among a
   lambda's `__func` slots and is written in 1150's file). Where the band's neighbours are other digit zones', the data
   only its code creates place it (4625, step 1). The fragment names both places.

Before you create the file rule 4 names, run `git ls-files <path>`: it can be a tracked stub-only file, whose records
name the class and members you have not read (`git status` showing ` M` on a file you think is new is the sign). Read
the class's vtable and typeinfo in the data too: the class may share an object
with another, have its key function in another class's file, or have left the file upstream gave it
([facts/placing.md](reference/facts/placing.md) §P2). The `unplaced.cpp` comment over a cluster is a stretch's label,
and its file name counts only as a `class-convention` guess for this class (§P3). Read a function's link neighbours by
band position, never by the `ordinal` column, and confirm them from the data, which has no digit scramble; when the two
name different directories, the data win (§P4). When the recorded neighbours on two sides disagree, compare file names
only where the data show a run in name order, and when unrecorded objects lie between them take the adjacent side and
call it a choice (§P5). A function that calls an `EM_JS` import is placed by the glue's order
([facts/link-order.md](reference/facts/link-order.md) §L7 item 16), and a call of another file's internal function puts
the call site in that file's TU (§P2).

**Keep every throw on its record's line.** A decompiled function's `std::source_location` records are bytes of the
target, so each throw site must sit at the line and column its record gives; above it, blank lines and *gaps* hold the
place of the code not written yet. A gap is a generated comment and a `#line` that stands for a run of blank lines
([src/README.md](../src/README.md) "Gaps": its form, the `#line` numbering, and how a line added or deleted above a
record moves it and shows). If the file holds stubs or gaps, turn them back into blank lines before editing it: `python3
-I -B tools/round/stubs.py --strip <file>` moves no line of a file step 9 wrote. Strip first, then edit: on a file
edited since, it pads each gap's run so that the line after it lands on the gap's `#line`, which absorbs lines added
above, so read the throws' lines after it before deleting any. Once stripped, the file has no `#line` left: a line you
then delete or add moves every record below it until you put the count back, and `make -C src stubs` does not move it
back (two statics moved below a `GetInst` by deleting their lines took the constructor's `instance()` record three
lines up). Write the function where the stub or the gap was, delete the blank lines it replaces, add some where a throw
would land too early, delete one blank line of the run below for each line you add above it (an `#include` above all),
and compare every record's line with the stripped file before the link. Before writing a member, check in the stripped
file that the lines its record needs above it are blank: a landed function's tail can hold them. The lines of a landed
function after its last record are a layout of ours, and may be re-laid out to make room for a later record when that
function's code is shown unchanged (its disassembly compared by function, object-local numbers masked, against the
base's object), and the fragment says so (3655's tail in `cinputmenufield.cpp` made room for `SetFormatString`'s record
156, unit 84's fragment). A `throw` is not
the only maker: a default argument's records (`CPolySingleton<T>::instance()`'s `std::source_location`) sit on lines
`/throw/` does not find, so list each record's line, column and functions (`f=<file>; awk -F'\t' -v f="${f#src/uenux2/}"
'index($2, f) {print $3, $4, $6}' ledger/source-locations.tsv | sort -n`) and read each line (`awk 'NR==<line>' $f`).
Lines above a file's first record that are ours (includes, a header comment) are a layout of ours: when no blank run is
left there, a new include takes the place of the blank line after the file's own header's include (the blank after
`namespace … {` stays), and the fragment says so. `make -C src stubs` (step 9 runs it) writes the stubs and
gaps again around it, each gap comment over the blank lines that are left, and `TMPDIR=/tmp make -C src check-srcloc`
(after `make -C src link-map` on the last link, which the splat build runs and a bare relink does not: a map older
than the wasm keeps every linkonce copy's record, which then fails as `MOVED`) lists every record of ours that is not
the target's.
It passes with records that only unmatched functions load, and the tree has some of those already (12 at 0b5f410), so
check your unit's own objects with `--strict`, which fails on those too (step 10).

A record that no `throw` makes fixes a column too: a default argument's records the start of the call that takes it,
so a long column reads as an initializer, and a macro's records the invocation's closing `)`, so a column that grows by
one per character of a class name is a macro that takes the name once. The column fixes the length; how it is shared
out is a choice ([facts/reading.md](reference/facts/reading.md) §R19).

The record's function name is bytes of the target too: clang's pretty-function text, with the typedef names and
qualifiers the source spelled. Spell the definition's return and parameter types as the record does. 3663's record
(`awk -F'\t' '$6 ~ /(^|,)3663(,|$)/ {print $5}' ledger/source-locations.tsv`) reads `static void
api::CBmpConversor::InvertColors(unsigned char *, const int, const int)`, so its definition takes `unsigned char*`
and `const int` by value, although the same tree spells bytes `uebyte` elsewhere; 144 records do spell `uebyte`
(`cut -f5 ledger/source-locations.tsv | /usr/bin/grep -c uebyte`). A `using` in the `.cpp`, or a template's `TEntidade`,
changes that text with no other sign, and the function then gets no `srcloc-anchor`: spell the type as the record does.
[reference/app-flags.md](reference/app-flags.md) "The error records are std::source_location, not a macro" has the
background.

**What a record's place says.** The record's text shows `static` only for a static member: a file-static free
function's record reads like an external one's. Its linkage is in the order of its file's records, because clang emits
an external function where the file defines it and defers internal, `inline` and template functions to the end of the
TU (`api::truncate` and `api::ExistResource` in `csystem.cpp`, [facts/reading.md](reference/facts/reading.md) §R8). A
file-static function stays out of line only once callers in its file keep it there; until then it cannot land. A
caller in another file in `ledger/callgraph.tsv` is binaryen inlining across TUs, and a function with no record and
such a caller is read from that caller's body (§R8, with 5449). A function-local static's guard shows linkage as well
(§R17). When none of these shows a record-less function's linkage and its callers are all its own file's, unwritten,
the linkage is a choice: write it external, so that a roots file can give it its call sites, and say in the fragment
what the file's recorded helpers show (690, `vota::MensagemErroCargo`, beside `ctelasvota.cpp`'s anonymous helpers).
A chosen line is a namespace too: records of one `(anonymous namespace)` on an unbroken run of lines read as one block
(a reading), so put an external function outside such a run, or say in the fragment that its line lies inside one.

A member with no record is placed by its use band in the same way: inside one band of `ledger/ordinals.tsv` (column
`uses`, which counts table entries and exports as well as calls; `ledger/functions.tsv`'s `uses` does not) the index
runs in reverse link order, but an index's neighbour can be another digit zone's function: print the run's `ordinal`
column and drop a value with another number of digits before naming a file (`awk -F'\t' '$1>=5864 && $1<=5869 {print
$1, $2, $5}' ledger/ordinals.tsv` puts 5867, ordinal 434, between 5866's 4340 and 5868's 4339:
[facts/link-order.md](reference/facts/link-order.md) §L1, consequence 1). So a member
among the file's external functions is defined in the `.cpp` at that place, and one after all of them is the file's
last function, or inline or implicit, when nothing earlier in the file calls it; one after a deferred function the
file emits (a linkonce vtable's slot) is another object's, since clang emits deferred functions after every external
one; and a body binaryen keeps once for several classes sits at the place of the copy it kept, the first in link order,
so it places no neighbour before you say whose copy that is, and its own line is a choice (§R9 has 3872, 3873 and
3874).

**The order of two members.** Inside one use band and one object, a higher target index must have a lower `ld_index` in
`build/out/wasm-map/vota_web/names.tsv` ([reference/splat.md](reference/splat.md) "Reviewing a match" holds a reviewer
to it). Compare `ld_index`, not the scan's `ours`: `ours` follows the final order, whose digit zones sort as text (`998`
above `1002`, [facts/link-order.md](reference/facts/link-order.md) §L1), so a pair across ordinal 999 and 1000 reads the
wrong way round.

```sh
for i in 5742 5743; do s=$(awk -v i=$i '$1==i {print $2}' splat/matched.txt); printf '%s %s\n' $i "$(awk -F'\t' -v s="${s%%@*}" -v o="${s#*@}" '$2==s && (o==s || $3==o) {print $4}' build/out/wasm-map/vota_web/names.tsv)"; done
# 5742 2642
# 5743 2637
```

A match line of a local symbol is `<name>@<object>` (a static's `__cxx_global_array_dtor`), and `names.tsv` holds the
name and the object in two columns; the `${s%%@*}` split is for those. A static's destructor is emitted where the
static is defined, so its row places the statics against the members (7070 and 7122 in `cthreadeleitor.cpp.o`). Its
storage takes its place in the object's data at its first mention, which can be a function above the definition: read
the statics' target addresses too before moving a definition (`CInfoMTLCD`'s `s_mutex` below `s_inst`,
[facts/placing.md](reference/facts/placing.md) §P4).

Run the check over every matched member of the object in the band, not only yours;
[facts/placing.md](reference/facts/placing.md) §P9 says where a new member goes when the landed ones are already
inverted, how to tell the pairs a range added from the base's, how to count in a file that emits many instances, what to
do when the band reads as an unwritten caller's mentions, what a run across two objects of files you chose orders, and
how a recorded function bounds the order.

An inverted pair is two definitions swapped only when no earlier function of the TU can mention either: a function takes
its place at its first mention, not at its definition (a callee sits between its two constructors in three objects of
unit 89, and 5693 and 5694 read inverted because `DoDesconverte` mentions 5694 first), in the code clang emits after its
own inlining ([facts/reading.md](reference/facts/reading.md) §R9 has the case and the object's function list to read
for each order you try); a function first mentioned above its definition does not carry its own callees there, which
take their places at its definition (§R9). Such a swap gives the
same bytes, so it is a question of source order, not of a match. A linkonce instance (a control block's member, a
template's member) counts the same way: it takes its place at its first mention, so a run of consecutive target indices
in one band gives the order of the definitions that mention them, and a row far from the run may be another TU's copy,
which says nothing.

**Names no evidence gives.** A record gives a function's qualified name and how its types are spelled, a vtable slot or
RTTI gives a class's name, the typeinfo of `CBaseError<E, SErrorLimits{lo, hi}>` an error enum's name, namespace and
limits, and the throw its code. Nothing gives an enumerator's name, a parameter's, a data member's, the scope of a type
a record prints unqualified (`std::vector<CMovieFrame>` is the same text for `api::CMovieFrame` and `::CMovieFrame`,
which mangle differently: §R11) unless a typeinfo name spells it (a local class's or a lambda's mangles its function's
whole signature, §R11), the path of a header no record names, the order in which a class declares its out-of-line
virtual members, the enclosing member's `const` in a lambda's or local class's record (its symbol mangles it, §R11), or
the name of a function no record, slot or RTTI names: a callback passed by table slot, a pure slot no caller names, a
function each of whose records belongs to an inlined callee, or a second copy that duplicate-function-elimination
would join with the first (X1): a one-caller callee the target keeps out of line under two identical callers was two
functions that differ until dead-argument elimination, so write the second as such a function, a member that does not
read `this`, with its call sites, its evidence and its choices marked (1255's `IPedeTituloMesario::GetTelaEleitor`,
unit 247). A member never waits for such a name: write it under a chosen one. Choose it from what the evidence shows of
its role: the body's shape and its callers (a `this` returned on a fresh object is a constructor; a copy of `*this`
changed by a compound operator and returned is the matching binary operator), an error's message, a log text that spells
`Class::Member` (step 1), a pure slot's callers, else its slot (`Slot3`). Before you choose a class for an object,
follow `this` from the callers to the next functions that take it, and read their vptr stores, their strings and their
callees' records: "no evidence" may be said of the object only then. 5622 and 5623 have no record, slot or RTTI of their
own, and their callers hand the same object to 5604, whose lambda 2791 has the record
`comum::CCabecalhoQRCodeBuilder::preBuild()`. For a static object, read every function that loads its address: a type a
record names whose objects such a function builds or fills from this one, with the same size, constructor and elements,
is the class to take, or the fragment says why not (4454 fills `md::CCedula`s from the votes object at 1833300). A
template argument is a name too, a class's or a member function's, and it ends up in a match's symbol, where no check
sees it: before you write a container's key or element type as chosen, read the records of the class's other members, of
its base's and of the functions that take the object (`awk -F'\t' '$5 ~ /<Class>/' ledger/source-locations.tsv`, and
`<Class>::` in `ledger/strings.tsv`). Put a type in the namespace of the class that uses it. Make a function a member
when it reads private state, helps a singleton class, or reaches the object only through the members of the class whose
own `.cpp` its place is (5180, `CFile::Write`, calls `RawWrite` on `this`). A class whose records name static members
only, more than one, and no data member (`api::CSystem`: `LC_ALL=C awk -F'\t' '$5 ~ /^static .*api::CSystem::/'
ledger/source-locations.tsv | wc -l` prints 18) permits a static member and does not require one: in its file the form
of the file's landed functions is the default. Otherwise it is a free function: one binaryen inlined, with no index of
its own, in the namespace of its caller's class (§R10 has the cases); one with an index in the namespace of the file its
place gives (rule 5 above: `api::GetFreeSpace`, whose one caller is `vota::CThreadMonitor::Run`); one of another tree,
as ecourna's code is to uenux2, in its own directory's namespace. Membership and a namespace no record, slot or RTTI
shows are choices like a name: mark them, with the reason and the form that gives the same bytes (a free function that
takes the object by reference). A chosen overload set of a landed header can make a later source's plain call pick
another function than the target's: rename the chosen overload (a header change, measured on its callers' objects) or
spell the call apart (`std::as_const`, unit 230), marked as forced by a chosen name. Look for a type a record names, or
a static data object another lane's classes read, on the other lanes' branches first ([agents.md](agents.md) "A type no
lane owns"). Then mark the choice where it is declared, as `src/uenux2/src/api/gui/eueguierror.h` does for each
enumerator (`the name is chosen from its message, "Dado de entrada nulo": no evidence names it`), except in a gap's
lines, where no comment of ours goes ([src/README.md](../src/README.md) "Gaps"): there the fragment's header holds the
mark and names the line, and the gap's other lines stay blank. List the chosen
names, paths and linkages in the fragment's header comment with any other choice that gives the same bytes (a free
`operator-` for a member one). Parameter and local names need no mark: no record holds one. The symbol file then names
the function by `pair-*` or `srcloc-anchor` evidence, which says that our body is the target's, not what the function
was called.

A slot's callers are not in `ledger/callgraph.tsv`, which holds direct calls: search the folded readout of each function
that holds an instance for the vtable load ([facts/placing.md](reference/facts/placing.md) §P8). "No caller" means that
every holder of the instance was followed and that search found none. Only then is `Slot8` the name.

What a body does not decide is a choice like a name, and the fragment says which form you wrote:

- **A data member's name and type.** Mark the names in the class header's comment. When the bodies give only a width
  (a 32-bit store of 0 and 1 that nothing reads), take the plainest type of that width (`int`, not a `bool`, which
  stores 8 bits), and say that the type is chosen too. A width is all they give only once every target function that
  loads or stores the object was read, written or not (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
  build/out/splat/pieces/asm` lists a static's): a compare with a value above 1, an increment or an index rules out a
  `bool`, and a byte's sign shows only where the value is widened ([facts/reading.md](reference/facts/reading.md)
  §R14). Its access shows nowhere: a reader in another class that loads it shows only that it is reachable there,
  through an inline accessor or as a public member, so when the member rule above makes a function a member because it
  writes such state, list the access and the membership among the choices (`md::CCedula::m_votos`).
- **A pointer's or reference's declared class.** A virtual member the target calls through it with `call_indirect`, on
  an object of a class whose bodies the target calls directly elsewhere (a `final` class, step 5), says the declared
  class is a base; a direct call says `final` or a known dynamic type (`CGeradorBUQRCode`'s `+400` is a `const CRdv&`
  holding a `CRdvVota`, §R4). A reference against a pointer is a choice.
- **A parameter's or a result's type.** It is evidence only as far as the body uses it: a value the body only returns
  or forwards is one wasm word, and a reference and a pointer to a class compile alike. Say in one line of the
  fragment which types are chosen, instead of listing alternatives no one could finish.
- **An enum's underlying type.** A compare shows its signedness: an enum with no fixed type whose values fit in `int`
  promotes to `int` and compares signed, so an `i32.gt_u` on it means a fixed unsigned type (`: unsigned int`, a
  spelling chosen) or an unsigned parameter (5892, [facts/reading.md](reference/facts/reading.md) §R14).
- **A class no evidence names that a body only calls through.** Declare it beside the interface that takes it, with
  virtual members up to the slot the body calls, named from its role, and say that the class and its members are
  chosen (`api::IImageSurfaceSource` in `src/uenux2/src/api/gui/iimagesurfaceops.h`).
- **A body's spelling the bytes do not decide**, such as a call of a member clang inlines against its statements
  written in place: say which you wrote and that the other gives the same bytes.
- **The declaration order of out-of-line virtual members.** Records or the band can show several members out of line
  in one file, and the target does not hold which is declared first. Declare the destructor first, so that the class's
  own `.cpp` emits the vtable and not the `-pending.cpp`, a trapped destructor too (`src/units/README.md` "Pending
  members"), and list the order among the choices.
- **Two slots of one class that hold one target function.** Both are members, since the vtable needs two. The match line
  takes the first in link order whatever the two are called, so a name in `splat/matched.txt` is not ranked by evidence:
  the header has the role.

**A comment says what was measured.** Each claim in a header, a fragment or a hand line is one of three kinds, and says
which: evidence (a record, a slot, the target's rows), with what shows it; a measurement, with the form it was measured
against (`unsigned int m_tipo` gives a `cmp`-equal object, so the unsignedness is evidence and the enum a choice); or a
reading, marked as one (why a form gives the bytes, which TU holds a copy, that a line is needed). A form the bytes
leave open is a choice even when it is the likely one, and what the target's bytes fix is evidence even when no record
names it: a width a body stores is not chosen. A reading stated as evidence is wrong text in a landed file, however
right the bytes are.

A type a record names but no evidence fills gets its name and its size only. The record of
`api::CTextFieldPaper::CTextFieldPaper(const SharedIText &, IPaper::EStyle)` names a nested enum, and no target code
tests its values; `src/uenux2/src/api/gui/ipaper.h` declares `enum EStyle {};` with a comment that the callers pass 1
and 2 and that the enumerators are not recovered. Invent enumerators only where the code shows what a value does, and
mark them as chosen.

**A stub-only file, and a record you do not write.** A file the evidence names that does not exist yet holds its stubs
only, written from line 2 on, not at their records' lines ([src/README.md](../src/README.md) "Stubs"). `--strip` leaves
next to nothing of it, so lay the file out yourself so that each throw lands on its record's line, with blank lines
where the original lines are unknown. Blank, not comments of your own: a comment written as TSE's documentation reads as
recovered text. Notes about the reconstruction go in a header comment at the top that says plainly it is the
reconstruction's. A record of a function you do not write keeps its line blank, a closing brace and a comment included:
`stubs.py` reads any text on a record's line as that function's code, drops its stub, and `--check` passes. An edit
above such a line moves it, so read each one after the edit (`awk 'NR==<line>' <file>`). Put the functions you write
after it, or before it where the evidence says so, and say in the fragment's header comment that their lines are a
choice. Step 9 then puts that caller's stub over the record's line, unless the caller is a pending member, which has no
stub (step 9): then the fragment and the `-pending.cpp` header say what the blank line is for
([facts/placing.md](reference/facts/placing.md) §P7 has the cases, the check after step 9, and what a class body does).

**Save TSE sources as Latin-1.** TSE's files are ISO-8859-1, and their string literals are bytes of the target: an
editor that saves `"inválido"` as UTF-8 changes the data the census and the splat scan compare. Compare a literal with
`ledger/strings.tsv`'s length (column 2) and charset (column 3), never with its text (column 4), which is UTF-8 whatever
the target's bytes are: 377803 reads `60 latin1` (`awk -F'\t' '$1==377803 {print $2, $3}' ledger/strings.tsv`) and its
text is 64 bytes. `.editorconfig` declares the charset for `src/uenux2/` and `src/ecourna/` (with the few exceptions it
lists), and CI's `tools/round/check_encoding.py` fails on a file that was re-encoded. It declares none for the fragments
and companions yet, which are of both kinds (17 fragments Latin-1, the rest UTF-8): keep a fragment's bytes in the
charset it has (`file src/units/<name>.mk` says `ISO-8859 text` or `UTF-8 text`), and quote a literal there in it. Write
a new file in Latin-1 too when its strings or comments have accents. An editor or agent tool writes UTF-8, so one `§` in
a comment fails the check, and it shows only after `git add`: cite a facts section there without the sign
(`docs/reference/facts/reading.md R14`).

The target's own bytes decide a file's charset. One TSE literal is UTF-8 there, `"Turno inválido."` of
`src/ecourna/app/dados/asn/cconversorturno.cpp`, which `.editorconfig`'s UTF-8 section lists: `awk -F'\t' 'NR>1 &&
$3=="utf8" {print $1, $2, $4}' ledger/strings.tsv` prints it at 367628, with four rows of binary data. A literal of
the wrong charset shows on a TSE row of the scan as `an address of ours: string not in the target`, except a short one:
a literal that initializes a short `std::string` (22 bytes or fewer) can be stored as its characters, `i64.const` and
`i32.const` immediates with no address, and a wrong letter then shows only as an operand row of `score`. Decode a TSE
body's wide constants as little-endian bytes (`python3 -c "print((2322291580548048214).to_bytes(8, 'little'))"` prints
`b'Vers\xe3o: '`, 12055's Latin-1 `Versão: `) and compare them with the source's text. That section's
other file, `src/ecourna/app/dados/iidentificadoreleitor.cpp`, is no precedent: its literal is Latin-1 in the target
(`awk -F'\t' '$1==377803 {print $1, $3}' ledger/strings.tsv`), and the file goes back to Latin-1 when its constructor
9256 is written. A search for a string's users has to look for `i64.const` too: a `std::format` string of non-PIC
ecourna code is loaded packed, `(len << 32) | addr`.

The compile line in the lifted file's header is the flag set of the tree the function's code comes from, and the
line under it says what decided (`liftFlags` in `asmlift-wasm/src/lift.ts`): the function's `std::source_location`
records when they name one tree, else the tree whose file holds its stub, else its *component*, which says which code
calls a function, not where it is written. The lifter's flags are a copy, with no flag a unit's fragment adds. The next
steps use `try-tu.sh`, which reads the flags from `src/Makefile` by the source's path; trust those.

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
with `--flags "-iquote /work/<dir>"`. To try a variant of a tracked header, pass its directory the same way, the headers
under it at their tree paths, and not with `-I`, which loses to the tracked header with no word said. A header a TU at
its tracked path includes by a bare name wins over `-iquote` too, so copy that TU out of `src/` and pass the copy with
`--component`. Then check that the try's object holds what only the variant gives (`--symbols`, or `llvm-nm` on
`build/out/try/<name>/obj/<tu>.o`; [facts/workflow.md](reference/facts/workflow.md) §W2 item 3).

The lone compile and link is one `em++` with `-fexceptions`, as the build's link is, but binaryen runs at the TU's own
level, not `-Oz` (§W2 item 5). For a TU whose flags lack `-fexceptions`, `--single` adds `-fignore-exceptions`, and the
`flags:` line it prints ends with it, so its throw sites call `__cxa_throw` directly, as in the build
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

`--extract export:<symbol>` takes the function's mangled symbol. To find it, compile the TU and list what it defines:

```sh
TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/app/comum/dados/crdvvota.cpp
# _ZNK5comum8CRdvVota9CandidatoEhjh	comum::CRdvVota::Candidato(unsigned char, unsigned int, unsigned char) const
```

Each line is the mangled symbol and its demangled form; pick the one whose demangled form is the target function's
signature (the `std::source_location` record, or the ledger's `best_name`). `--symbols` lists the functions and weak
data the object exports, not a class's own vtable and typeinfo nor a local symbol (`try-tu.sh`'s help says which). The
object it compiled stays at `build/out/try/<name>/obj/<tu>.o`: `wasm-objdump -d` there shows the local symbols, and
`llvm-nm` whether the TU emits the vtable ([facts/workflow.md](reference/facts/workflow.md) §W2 has the command). A
function of internal linkage (file-static, or in an anonymous namespace) cannot be extracted: `--extract
export:_ZN4vota12_GLOBAL__N_1…` stops with `undefined exported symbol`. Compare its forms on the objects (step 3, "To
measure the same bytes"), or in the whole link (step 5).

A function linked alone gets different inlining and dead-argument decisions from the same function inside the program,
so a score of 0 here is a reason to try the whole link, not a match. The reverse holds too: target 1931 is matched, yet
its body linked alone still differs from the target's, and even a function with no callee can come out differently
(11067 matches as written and scores 9 alone, [facts/tool-traps.md](reference/facts/tool-traps.md) §X9). Read a lone
score for the store order, which binaryen keeps, and rank the forms that differ in anything else in the whole link.
The lone link keeps no wasm, only the object of a `--symbols` run, clang's code before binaryen.

**When the lone score is noise.** These come from the lone link itself
([facts/workflow.md](reference/facts/workflow.md) §W2 has each measured, with its case):

- **Callees the program shares are inlined** (a `std::format` throw's pieces: 5468 matches and scores `10836 over
  10850 rows` alone): go to step 5, or read the object after a `--symbols` run beside `pnpm wasm fn`'s target body.
- **Library callees resolve to the toolchain's libraries**: a row deleted at a library call is that (3907).
- **A destroyed `std::string` inlines `free`**: hundreds of inserted rows after an `i32.load8_s offset=11` test;
  `--flags '-Wl,--export=free'` keeps it out (11272).
- **Instruction kinds and load order at the lone level** (two `br_if` joined into an `i32.or`, independent loads
  reordered) are no reason to change the C++.
- **A Latin-1 literal is re-encoded**, each accented byte as three, and an accented character literal stops the
  compile: try a copy with `\x` escapes.
- **Forms that differ in a stack slot score alike** when callees are inlined around them (4407): read the frame stores
  in the object, or rank them in the whole link.

**When only a flag closes the gap.** A body that differs in a way no C++ form you can find explains (a load the target
repeats, a branch where ours has a `select`) may need a flag its tree's set lacks. When what differs is what is inlined,
first ask clang: `-Rpass=inline -Rpass-missed=inline` on the compile prints each call site's cost and threshold, so it
says at once whether a form of the caller can change the decision ([facts/levels.md](reference/facts/levels.md) §V2).
Through `try-tu.sh --symbols --flags '-Rpass=inline -Rpass-missed=inline'` (a level added to the same `--flags`) the
remarks go to `build/out/try/<name>/obj/<tu>.o.log`. The remark flags change what clang inlines elsewhere in the TU,
so read the object's code from a compile without them; §V2 also has the hot call sites of `-O3` and what no remark
shows (a loop held twice, a call the target keeps that clang inlines at a low cost). A caller that keeps work after a
call on what it passed where ours drops it is in another TU than its callee, with no inlining involved
([facts/placing.md](reference/facts/placing.md) §P2). Where neither a flag nor an inlining decision is involved, `-mllvm
-print-after=loop-rotate,jump-threading -mllvm -filter-print-funcs=<mangled>` on the TU's compile line shows which pass
made a loop's or a branch's shape ([facts/codegen.md](reference/facts/codegen.md) §C12). A member whose target copy is
the executable TU's has that TU's flags, `-Oz -fexceptions`, whichever tree's header defines it (§V1), and which flags a
linkonce copy has is measured with a probe object first on the link line, which `try-tu.sh` has no route to (§V4).

Try a flag with `--flags` here, then find out whether the flag is the tree's: a flag is decided for a whole tree, on a
site no source change can explain, never on the one function that needs it.
[facts/app-flags.md](reference/facts/app-flags.md) §F9 item 8 has a trap here (a reload that an out-of-line call gives
as well), and §F6 the evidence for uenux2's strict aliasing by directory and file; a body that differs only by strict
aliasing is [facts/levels.md](reference/facts/levels.md) §V5's case. A flag set changes in `src/Makefile` (or
`src/mk/ecourna-flags.mk`) with its evidence in that facts file, and every match must still verify in a private link
with it (§F9 item 6 has the command; to measure taking a flag away, take it off the line, since an override is not the
same: §F9 item 9). A level change also makes text false, sentences that call the old level the tree's and conditions
written on the new one: search for both ([facts/levels.md](reference/facts/levels.md) §V3 has the search) and rewrite
them when the change lands. A flag that changes libc++'s ABI tag also changes which object owns each inline symbol, so
a harmless-looking flag can move a match. A flag can look per file when it is not: `-fno-PIC` was set file by file until
the target's data showed no file of ecourna apart from the rest (§F5). So before you call evidence per TU, look at what
the whole tree's data and code say. A fragment may carry a target-specific flag only where the evidence is per TU, and
then the objects' flag set must be a setup of `asmlift-wasm/benchmark/dataset/setups.json`: `pnpm bench setups --check`
fails on an object that compiles with flags no setup has
([asmlift-wasm/benchmark/README.md](../asmlift-wasm/benchmark/README.md) "The compile setups"). If neither holds, keep
the source as written when it gives the target's rows at the flags that close the gap: its row stays `differs`, and the
fragment's header says so with the measurement (step 5, "A written body that does not match yet"). Report it. A flag is
not a reason to replace a right body with a trap.

A companion object is no way round a flag either. TSE code a roots file emits to match must give the target's function
at its tree's flags, not only at `APP_CXXFLAGS`: the tree of the object whose copy the target keeps, which is not
always the header's. A copy that matches only at a set its tree lacks falls when a tree object first instantiates the
template, and its line cannot be withdrawn while the copy links. `src/units/README.md` "Companion files" says which
tree, how to show the flags agree, and how such a copy leaves (5725); in uenux2 a directory's flags are its own, so it
also says what a companion compiled with `$(UENUX2_CXXFLAGS)` owes in a directory that drops `-fno-strict-aliasing`
([facts/levels.md](reference/facts/levels.md) §V5 has the measurement).

## 5. Conclude in the whole link

```sh
mkdir -p build/out/try; echo 1931 > build/out/try/targets.txt
TMPDIR=/tmp tools/round/try-tu.sh src/uenux2/src/app/comum/dados/crdvvota.cpp src/uenux2/src/app/comum/dados/md/rdv \
  --targets build/out/try/targets.txt --skip-units 13-uenux2-crdvvota.mk
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
function added; the function extends that unit (step 6). try-tu names objects by the TU's base name, so two files of one
base name in a unit need copies under distinct names, and a try's objects link after both trees, so a linkonce copy that
must come first needs an overlay on a landed object (both §W3).

When your sources, the fragment and its companions are already where they land, steps 6 to 9 measure the same pairing on
the real link, from one link instead of two (in a loop that edits a source and relinks, remove its object before each
make and read one compile line in the make's output: make compares whole seconds,
[facts/workflow.md](reference/facts/workflow.md) §W26, which also has the `-o` that iterates on a header without
rebuilding its tree): step 9's match lines replace the try's report, and step 7's `moved:` list helps only for tier
changes. A throw through a merge thunk and a `std::format` caller stay at `none` at depth 2, so an empty `moved:` says
nothing (a unit of 17 printed `moved: 0 functions`, then step 9 added 16 matches). Read `pnpm wasm score <target>
<index> <link> <ours>` per function, with `ours` from `names.tsv` once `TMPDIR=/tmp make -C src link-map` has mapped
this link: neither `link` nor `census` writes the map, and an older one's indices are shifted. The score reads the two
modules and their glue, not the symbol file, so steps 7 to 9 leave it as it is
([facts/workflow.md](reference/facts/workflow.md) §W28). A score a note gives is this command's, at its default depth; a
count taken with `--depth 0` says so beside it (9515's `23 over 459 rows` is `19 over 459` at depth 0). A separate try
is for comparing variants without touching the tree (`--skip-units <your fragment>.mk`). It keeps every function of its
TUs alive, so a function the target holds inlined by binaryen in its one caller gets a second caller there and stays out
of line (11905's helper: `1845 over 2153` in the try against `183 over 2146` in the tree): compare such a TU's variants
in the plain link ([facts/workflow.md](reference/facts/workflow.md) §W13, "One variant object in the whole link"), the
object removed before each variant's make (§W26).

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
echo 9131 > build/out/try/targets.txt
TMPDIR=/tmp tools/round/try-tu.sh --name munzona --component ecourna/app/dados/asn \
  src/ecourna/app/dados/asn/cconversormunicipiozona.cpp src/units/16-ecourna-cconversormunicipiozona-pending.cpp \
  --roots src/units/16-ecourna-cconversormunicipiozona-roots.cpp --targets build/out/try/targets.txt \
  --skip-units 16-ecourna-cconversormunicipiozona.mk
```

Because `--component` moves every TU, it also moves the `std::source_location` paths of a TU from another
directory. Use it when the TUs share a directory's flags and the moved ones have no records.

A unit with no source of its own (its matches come from its roots or pending object, step 3) has no `<tu.cpp>` for a
header variant. Compile that companion against the variant with `-iquote`, put the object in a clone of `build/out/app`,
and link with the clone as `APP` ([facts/workflow.md](reference/facts/workflow.md) §W13). Check the overlay first: the
unchanged header through the same `-iquote` must give an object `cmp`-equal to the landed one.

**A written body that does not match yet.** A body that is right apart from something outside it stays in the landed
file: a callee not written, a flag its tree does not have, a data object or a literal it waits for. Its row stays
`differs` or `unresolved`, or `no-candidate` when nothing names it, which is an ordinary state of a TSE object. Show the
cause with a link or a compile that holds what the body waits for, and say what it waits for, with that measurement, in
the fragment's header and its README row: for a `no-candidate` row the fragment is the only note. A form measured on the
body in another unit's fragment is cited in the body's own fragment too, so a pick reads one note (the setter measured
on 10380 in unit 61's fragment, cited in unit 135's). A body whose only
remainder is a flag its tree lacks lands so too, a new unit when its file is new (5482, unit 175), so that the flag's
landing matches it (`api::ITextToSpeech::SetVoice`, 11518, unit 82, gives the target's rows at the executable TU's
flags: [facts/levels.md](reference/facts/levels.md) §V1). When the flag alone is not enough (the body also needs an
unwritten caller of an instance the flag shapes), the body stays unwritten when nothing needs it, with both measurements
in the fragment (5869 waited so in unit 227's, until unit 268 wrote it with the flag and a stand-in for its callee's
other caller: that fragment's "The flag"). A callee that is written but has no name yet, or that only an unlanded
branch names, is something outside the body too: a body measured right lands written, not as a trap (11861 over 3648,
unit 138).
`ModeloAbreviado` (8168, unit 75) was `differs` until the literal it shares a tail with was in the link (it matched when
unit 142 wrote 10425, which holds it), and with that literal in a scratch link `splat-remap` printed `IDENTICAL`, once
code the link keeps references the literal and its
bytes are in the wasm ([facts/workflow.md](reference/facts/workflow.md) §W13). `splat-remap` applies no match line and
no self-vote rule, so a callee only `splat/matched.txt` names reads `UNRESOLVED` there, and a `.bss` name only the
body's own vote holds leaves the row `unresolved self-voted` once the literal lands (652's `s_inst`; §W28). Such a row
can read `unresolved` instead, `an address of ours: string tail occurs N times` (the table under "Library functions"):
1161 matched so, its body unchanged, once 11973, which holds the longer literal, was written.

A body whose remainder you cannot explain stays unwritten when nothing needs it: no trap, since nothing needs one. Take
it out and put the measurement in the fragment. Step 9 writes its stub back, unless its group is no TSE component:
`stubs.py` writes none for `app` or for a TSE function the attribution files under a library (3683, a lambda of
`CApplication::EnterLoopBeeping` with its record in `capplication.cpp`, is `libc++`: `awk -F'\t' '$1==3683 {print $5,
$9}' splat/scan.tsv` prints `no-candidate libc++`), and the fragment is then its only note. It stays written, its row as
it is, when something needs it: a vtable slot whose written body is one remainder off (a trap would only hide it: 10490,
unit 142, matched once a call of the setter gave its store order; one no measured form comes close to is trapped,
below), a matched caller, a caller that is written and right but does not match yet (3648 over 5477 and 5478, unit 125),
or a match that only it brings into the link (502's lambda members 11107 to 11109, unit 31). The fragment says what is
measured and that the remainder is not explained. A caller then holds only on evidence for the callee's name that does
not rest on the callee's bytes matching: until unit 28 matched it, 5499 (`CTextFieldDoubleLine::GetTextLines`) was
`differs`, and its callers 10929 and 10931 matched through 10929's `call` vote, which 10929's own record anchors
(`evidence:call by:10929`). A differing callee's own records anchor nothing (`srcloc-anchor` pairs equal opcodes only,
position by position: a callee whose remainder is local numbers alone still anchors, though `pnpm wasm score` counts a
swapped pair of `local.get`s as one row inserted and one deleted, 6599's `vptr-anchor`), so when no other caller votes,
its name takes a `callers+content` hand line resting on records only it loads (3771 under 2787; step 9, "Hand edits"),
or the caller stays `unresolved self-voted`.

A member right by construction (a singleton's `GetInst`) that the target holds inlined in one unwritten caller may be
written, unrooted, or wait for that caller; the fragment says which. Written, it is compared with nothing
([reference/splat.md](reference/splat.md) "Reviewing a match" says how to read it by hand), and its statics' exit
destructors are not matched until that caller's match names the objects: they read `no-candidate`, or `differs` or
`unresolved` with source `ledger` on a census pair with another object's destructor of the same shape, which a landing
can move (`awk -F'\t' 'NR>1 && $4=="ledger" && $5!="match" && $2 ~ /cxx_global_array_dtor/' splat/scan.tsv | wc -l`
prints 41 at 3c1ef19d).

A trap in a `-pending.cpp` is right only where `src/units/README.md` "Pending members" says (a member that cannot be
written yet, one that cannot match until other code lands, one whose real body would cost a match; an out-of-line
destructor that needs a type the tree lacks; never an implicit member), and never in place of a right body to clear a
row. A member a constructor would bring waits for the unit that writes that constructor, unless a builder the link
drops can emit it (`src/units/README.md` "A control block"). A
function whose target code ends at a call that always throws while the source went on (parameters dead-argument
elimination would have dropped, records of callees no function loads) cannot be written past that call, since its
callees' bodies are not in the target. No form of such a function is sanctioned (that is the user's decision), so
it stays unwritten and its callers pending (5568, `CApplication::ShowExceptionMsg`, whose `std::async` throws, over
7709 and 7710).

**The destructors say how the class is declared.** Read the D2 and D0 in the vtable's slots 0 and 1 before you write
the class head. The D2's bytes are the same in every form of the destructor, so a D2 that matches settles nothing; the
D0's shape decides ([facts/reading.md](reference/facts/reading.md) §R4–R7 have each case with its measurement):

- **A D0 that holds the D2's body and then frees `this`** (11176) belongs to a destructor with the inline hint:
  implicit, or declared `inline` in the class or after it in the header, which give the same object. Leave it implicit
  when the class has a base; declare it `inline` when it must be declared, as in a class with no base, whose destructor
  is virtual only when declared so, and after the type its body needs when that type's header includes this one (§R5).
  An in-class destructor without `inline` gives this shape only for a cheap D2 (12049).
- **A D0 that frees what the D2 returns,** `f136(f5531(p0))` (11086), belongs to a destructor that is not out of line
  and whose D2 was too costly to inline: defined in the class without `inline`, or, above the hinted cost as well,
  implicit or `inline` (5590). Only a smaller D2 tells those forms apart: compare them in the class's own shape, and list
  the ones that give the same object. Around a base's D2 (9388 calls 5898) it belongs to a class with no member whose
  destruction emits code, its destructor implicit or defined in the class, which can still hold scalars: read its size
  from the allocation (§R4, §R5).
- **A D0 that calls the D2 and then frees `this`,** `f5709(p0); f136(p0);` with a `drop` between them (11443),
  belongs to a destructor defined out of line: define it in the `.cpp`, where it is the key function unless another
  virtual member is out of line before it, and declare it first among those (step 3, "What a body does not decide").
  With no member whose destruction emits code, slot 0 can hold the base's D2 under it (3609 over 1378) or a D2 of one
  call of the base's (884 over 1035, §R5).
- **These shapes are uenux2's, at `-fPIC`**, where a call of the D1 alias stays a call in its own TU (§C6). In
  ecourna's code an out-of-line destructor over an out-of-line base can take the in-class row's shape (3491), and
  there, as for a class with no D0, a caller that keeps the call decides (§R5).
- **The shapes are those of the destructor's own TU.** A `delete` elsewhere (a control block's `__on_zero_shared`)
  frees the D2's result where its TU only declares the destructor and `this` where it defines it, so a target body of
  the second kind was compiled in the destructor's TU, which a roots file cannot give (11263 over 5614, unit 121). An
  explicit instantiation of a class template gives the out-of-line shape whatever the form (§R5).
- **A derived class's D2** inlines its base's destructor unless that is out of line, or above the threshold for its
  form, when it calls it (a weak copy in the second case). An inline base shows as its vptr store and member frees
  after the derived class's own, the store only when the base destructor's body makes a call (§R4).
- **A D2 that destroys members and does not begin with its class's own vptr store** (11178) belongs to a `final` class:
  write `final`; a vptr stored further on is a base's. A class whose destructor destroys nothing has one of binaryen's
  shared bodies there, and an empty `__on_zero_shared` of its `std::make_shared` block (the shared 218 in slot 2) says
  `T` or its destructor is `final` (§R4).
- **A class whose virtual members are all inline** has no key function: only a TU that uses its vtable emits the vtable,
  D2 and D0, one that defines a constructor or emits a derived class's destructor that inlines this one. When neither
  is written, write a constructor at its record's line (the target may have inlined it everywhere), or let the roots
  file emit them from an `optnone` function (§R6 has the mechanism, `src/units/README.md` "A class with no key
  function" the shape, [facts/units.md](reference/facts/units.md) §U13 what such a root emits).
- **When the destructors are shared bodies,** or the class has no vtable in the target, they say nothing of a key
  function, and a missing vtable does not either: read where the typeinfo lies. A copy in a user's object, inside a TU
  that only uses the class or no later than its earliest derived class's typeinfo, means no key function, and one well
  after it, among other objects' records, means one member is out of line; which member is a choice (§R6).
- **A slot that holds `__cxa_pure_virtual`** (12143) is a pure member: declare it `= 0` at its slot even when no evidence
  names it, so the class stays abstract; its D0 is then a trap (slot 1 holds 325, `unreachable`), where without the pure
  members the vtable is shorter and the D0 a real body the target does not have (§R7).

What a `new T()` clears before the base constructor runs says how the constructors are declared too: the whole
object with no user-provided constructor, the base's data for `D() : B() {}`, nothing for `D() {}`
([facts/codegen.md](reference/facts/codegen.md) §C9 has the stores, with 10327, unit 135).

The report's census *tiers* are diagnostics ([pairing and progress](glossary.md#pairing-and-progress)). A target function
paired with your symbol is worth landing and checking with the splat scan at any tier, and no tier is a match: the
example's report says `1931 343 B app/comum: none → none`, because a caller of `std::to_string` pairs at `none` at depth 2
however exact its body is ([facts/tool-traps.md](reference/facts/tool-traps.md) §X5), and 1931 is matched all the same.

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

`link-kinds.sh` refuses a try link whose objects were rebuilt after it was linked, so run it right after `try-tu.sh`, and
give `--name` a plain name ([facts/tool-traps.md](reference/facts/tool-traps.md) §X10). With more than three newer
objects the refusal is an exit status of 141 and no message.

To skip the two kind steps, pass `--no-kinds` to `splat-remap`; it then says `KIND-UNVERIFIED (no operand-kind
table)` and offers every operand every reading its value suggests. `IDENTICAL` there is the
signal to land. `splat-remap` reads the committed symbol file and none of the matches, so
`differs` or `UNRESOLVED` can still turn into a match once steps 8 and 9 add names; the scan in step 9 decides.
One `UNRESOLVED` no name fixes: a call into `byn$mgfn-shared$…`, which means binaryen merged your function with
others of its shape in the try link (*mgfn*), and the target did not merge that set. When the target merged the same
set, a name for the shared body does fix it (step 9, "Hand edits"). Our body is then a short thunk
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

(For a try link, pass its wasm and the `ours` index `splat-remap` printed.) `operand-only` counts every immediate (a
frame offset, an `offset=`, a local's index, the header row), so a score with no row inserted or deleted can still be a
wrong frame, signature, layout or slot, which no name fixes. Read the operands that are no call and no data address:
`pnpm --silent wasm score … | /usr/bin/grep '~' | /usr/bin/grep -v -E 'call fn:|data:'` prints nothing for a body that
waits only for names ([facts/workflow.md](reference/facts/workflow.md) §W28 lists what counts, the rows it prints that
are no fault, and the slots it drops). A wrong frame costs more once a record anchors the body at step 8: its differing
small constants vote as table slots ([facts/splat.md](reference/facts/splat.md) §S8 item 1). A callback passed by table
slot gets a `table` name only from a caller with a census pair or an anchor, not from one named by `vtable` alone
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
   "Landing a unit", which says what to check in the file's functions nothing linked before). A lane that writes
   members into several landed units' files may keep their notes and caller stand-ins in a fragment of its own that
   names each file's unit, and must when a file's unit's companions are another stage's claim (unit 325's members of
   units 119, 123, 246 and 317).
3. If nothing in the skeleton calls the unit yet, add a `-roots.cpp` that reaches each function the way the target
   does (address taken, the function's or, for a member the target reaches only through its vtable, the vtable's;
   at least two call sites, from two callers or one that calls it twice, counting the reconstructed ones and not a
   twin's, whose callers leave with it (step 10); or none so it inlines; `src/units/README.md` "Companion files"). A
   stand-in's comment names the target callers it stands for, and it goes when all of them are in the link ("Companion
   files" has the rule, step 10 the check at a landing).
4. Link: `TMPDIR=/tmp make -C src link`. Never pass `-j` to `link` or `splat`: their two outputs share one recipe, so
   `-j` runs it twice and can leave a corrupt named wasm that `make` then calls up to date
   ([facts/workflow.md](reference/facts/workflow.md) §W21). To compile the objects faster, pass `-j` to the object list,
   then link serially: `TMPDIR=/tmp make -C src -j4 $(make -s -C src print-LINK_OBJS)`. make does not rebuild an object
   whose flags changed but whose prerequisites did not. To see whether an edit of a source recompiles anything, count
   the compiles make would run: `make -n -C src link -W $PWD/<source> | /usr/bin/grep -c -E '(em\+\+|emcc) .* -c '` (0
   means the link would keep the old object; two tree roots, `sqlite_roots.o` and `openssl_roots.o`, compile with
   `emcc`, so a pattern of `em++` alone counts two short). Name the file with `-W`: a whole-link try (step 5) runs the
   same make first and compiles every stale object into the shared `build/out/app/`, so after a try a plain `make -n -C
   src link` counts 0 for edits it has already compiled ([facts/workflow.md](reference/facts/workflow.md) §W3). When the
   object is stale for another reason (its own source edited), hold that source old with `-o $PWD/<source>` beside the
   `-W` (§W26).

## 7. Census

```sh
TMPDIR=/tmp make -C src census
```

This rewrites `ledger/functions.tsv` (about a minute). It prints the paths of its reports; the target functions
whose census tier moved since the committed ledger are under `moved:` in `build/out/census/progress.md`. Expect
thousands of changed lines in
`ledger/functions.tsv` for a small unit: its `best_index` column holds our function indices, and every function
after the unit's place in the link shifts. The census also re-picks a pair among bodies of ours that tie once the
indices shift, byte-identical ones and ones identical with addresses masked (the `addr` tier: OpenSSL's 7-byte
`return <params>` getters), so `best_name` changes on rows that have nothing to do with the unit, and step 9 carries
that into the scan (step 9 says how to check it; [facts/splat.md](reference/facts/splat.md) §S8). A scan row's symbol is
`names.tsv`'s name at the census's `best_index`, which inside such a family can differ from `best_name`. The next three
steps read this census.

Read the pairs with your roots file before step 8. A stand-in caller can compile to a target function's body (`int
B(int p) { return D2(p); }` is any derived class's destructor that adds no member), the census then pairs that target
function with the stand-in, and step 9 would match it under the stand-in's name. Every census pair with a function a
unit's roots object defines, once the link map is this link's (step 8 makes it too; about 20 s):

```sh
TMPDIR=/tmp make -C src link-map
awk -F'\t' 'NR==FNR { if (FNR>1) obj[$1]=$3; next } FNR>1 && $6=="skeleton" && obj[$7] ~ /app\/[0-9]+-.*-roots\.o$/ {print $1, $8, $10}' build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv
# 1954 shape bool api::CPolySingletonList::has<vota::IQRCodeBUDS>(api::TPolySingletonsInfo const&)      (130 lines at 182dc6c1)
# …
# 5966 fingerprint std::__2::__shared_ptr_emplace<comum::CParteCandidatosMajoritarios, …>::__on_zero_shared()
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

The *symbol file* names target functions and data from evidence that includes the census's unique pairs, so a new unit's
functions and data get their names here. Run it after every landing that adds functions or data, and read the diff: a
name that moves can break existing matches (step 10 would say so). It also re-picks the arbitrary name of byte-identical
*twins*, drops and restores the `pair-addr` lines of matched functions the census pairs by address, moves an
`evidence:table` name between functions, and re-places data placed by its content (`g_MidAlloc` and `g_BigAlloc` moved
with unit 41), so expect churn in lines that have nothing to do with your unit
([facts/splat.md](reference/facts/splat.md) §S8); keep it, do not pick lines by hand. Lines below the hand-edit marker
survive, and `N hand edits kept` is the one line that says so: read it after every run. N counts the section's entries,
not its comment lines (`sed -n '/^# ---- hand edits below this line/,$p' splat/symbol_addrs.txt | tail -n +2 |
/usr/bin/grep -v '^#' | /usr/bin/grep -c .` gives the same number). The file is UTF-8, and a script that opens it as
Latin-1 and dies leaves it truncated, after which the next run regenerates from what is left and prints a smaller N;
recover with `git checkout HEAD -- splat/symbol_addrs.txt`. Add a hand edit only as step 9 says. Step 8 runs `make -C
src link-kinds` first when the shifted link or its table is stale: the generator reads the operand kinds of our data
([reference/splat.md](reference/splat.md) §3). Steps 7 to 9 fit Node's default heap; a run that stops with `JavaScript
heap out of memory` has written nothing, and goes again with `NODE_OPTIONS=--max-old-space-size=8000`
([facts/workflow.md](reference/facts/workflow.md) §W1).

## 9. Match

```sh
TMPDIR=/tmp make -C src splat-match
git diff splat/matched.txt
```

`splat-match` scans every target function, re-points each candidate body of ours into the target's index and address
spaces, appends every new byte-identical match to `splat/matched.txt` as `<target index> <our symbol>` (and renames a
listed match whose symbol left our link to its twin: step 10, "A twin whose name moved"), rewrites `splat/scan.tsv`,
regenerates the progress numbers (`make -C src status`: the status blocks of `docs/status.md`, the README's
`status:headline` block and the six waffles `docs/img/progress-{origins,tse,components}-{light,dark}.svg`, printing
`wrote <file>` for each one it changes), and rewrites the stubs and gaps (`make -C src stubs`): a function with a match
or a body of ours has no stub, so yours goes, and a stub-only file whose last stub goes is removed. A pending member's
stub goes too, although its body is only a trap, and so do the stubs of slots a class's first written member never
mentions: such a row is still `no-candidate` or `differs` on the `-pending.o`, so the `-pending.cpp` header is the only
note that the member is left to do (a written body that does not match yet has its note in the fragment: step 5).
`src/units/README.md` "Pending members" has the rule, the two ways the scan lists a trap (7481 until it was written,
10841), why a trap is
declared with its record's signature, and what the header names when a stub-only file goes with the stub.

For one function, `pnpm wasm splat-remap` shows the comparison directly;
[reference/splat.md](reference/splat.md) "Matching a function" has the command and explains `IDENTICAL`, unresolved
operands and the first differing byte. It applies none of the matches, so it can say `differs` for a function the
scan matches. It reads the map of the link it is given, so after a link whose sources have moved on, map that wasm as
it stands with `TMPDIR=/tmp tools/round/link-map.sh build/out/wasm/vota_web`, which runs no make: `make -C src link-map`
would relink the restored sources and lose the wasm under test.

`splat-match` also reports a listed line whose function the symbol file names only after other functions of our link:
the body verifies, but the evidence says another function sits there, as when 11611's line named
`wrapexcept<bad_weekday>::rethrow` while the target's `wrapexcept<bad_month>` vtable holds it
([facts/splat.md](reference/facts/splat.md) §S7). It changes nothing; find which side is right, and correct the match
line by hand when the evidence is. Both sides can be right: the target merged two functions into one body that our
link keeps apart. A match of that index then drops the other name ([reference/splat.md](reference/splat.md) §3), its
callers leave `match`, and `status.py` stops step 9 on `matched.txt only:`; withdrawing the match does not help, since
the content pass adds it back. Add an `evidence:merged-body` hand line of the other name, whose comment cites what
[reference/splat.md](reference/splat.md) §2 asks (our own body not equal by `pnpm wasm score`, and a caller the line
does not rescue); without one, or when our source is wrong, fix the source or withdraw the callers with a reason. The
report goes on printing that line, as expected.

A second name beside the matched one is not reported, so read step 8's `git diff splat/symbol_addrs.txt` for a `func:N`
that gained a name, and for a matched index that lost its line: a vtable slot your unit fills with a body that is not
the target's (a defaulted or implicit member of an earlier unit) votes that slot's index onto the body, and the function
the body is matched as can lose its line; and a unit that gives a second holder of an anchored operand the target's
shape makes two pairs of one shape, which anchor nothing, so the first holder's anchor line goes (576's `vptr-anchor`
when 886 became the target's thunk). The match stands, and the range says why. Other lines move at every landing
whatever the unit and are not evidence (an anchor on a round address, a `pair-addr` line that drops as another comes
back, a stray `table` name from a string's closing NUL, below): [facts/splat.md](reference/facts/splat.md) §S8
lists them, with the command that prints a landing's lines without its own matches. Keep the file as step 8 wrote it.
A gained name on another index is the range's to explain.

The scan changes rows that are not yours as well: the census's re-picked pairs change the `symbol` and `object` columns
(30 rows of 36-byte `__cxx_global_array_dtor` copies with unit 41), and now and then a verdict moves between
`unresolved`, `no-candidate` and `differs` ([facts/splat.md](reference/facts/splat.md) §S8). Read the verdicts against
the commit your branch started from, `BASE`: no row may leave `match`, and every row that turns `match` must be yours,
with two exceptions below. For a branch cut from `main`, `BASE=$(git merge-base main HEAD)`; for one cut from another
lane's commit, write that commit, since after a fast-forward the merge base is older and hides what you lost.

```sh
join -t "$(printf '\t')" <(git show "${BASE}:splat/scan.tsv" | cut -f1,5 | sort) <(cut -f1,5 splat/scan.tsv | sort) | awk -F'\t' '$2 != $3'
```

It prints `<index> <verdict before> <verdict now>` for each row that moved; on an unchanged tree it prints nothing. A
scan never removes a match line, so only the rows show a loss: count rows, not lines, after a scan you run by hand
([reference/splat.md](reference/splat.md) "Reviewing a match").

`splat/scan.tsv has N match rows but splat/matched.txt has M matches (… matched.txt only: [i, j])` from `status.py` is a
lost match, not a stale scan, though its advice reads so: running `splat-match` again changes nothing, unless the pass
printed `N renamed`, when the list can be the renamed rows' callers read before the renames applied, and the second pass
step 10 asks for ("A twin whose name moved") decides. The list shows
five indices at most (`tools/round/status.py` line 302), so read the `join` above for all of them. The row left `match`
while its line stayed, and `status.py` stops before `stubs.py`. A body need not have changed. Better evidence can do it:
a stronger pair demotes an anchor's name, so a data name becomes `self-voted` and the anchor's call votes go (matching
181 took 8979, 9074, 9083, 9108 and 9111 out so: [facts/splat.md](reference/facts/splat.md) §S8, the seventh kind), and
a new anchor whose small constants differ from the target's votes them as table slots, the rows that leave all naming
one slot in their detail (§S8 item 1). `git diff splat/symbol_addrs.txt` shows each evidence change. Fix it with the
name's own evidence, not by withdrawing a line. A change that costs a match does not land, a brief that asks for its
state recorded included, unless the user decides it lands: a stand-in or call that stands for no caller the target
shows goes whatever it costs ([src/units/README.md](../src/units/README.md) "Companion files", unit 100's 433 and
11157). Otherwise the lane posts the loss as a `facts/` post (the rows the `join` moves and what would bring each back),
and commits that state only on a branch the coordinator asks for to weigh it, a measurement that never lands. Either
way the commit removes exactly the lines of the rows the `join` moves from `match`, runs step 9 again so `status.py` and
`stubs.py` run, and names the indices in its message (`comm -23` against the base lists them); a loss that lands also
says in the fragment what each row waits for. A row can also leave
because an instance of yours took the symbol (step 3), a stronger name moved (below), a line you added above a record of
a matched function moved the record (step 3; [src/README.md](../src/README.md) "Gaps" has the sign, and `TMPDIR=/tmp
make -C src check-srcloc` lists it), or an edit of a header or a signature changed what another unit's object
instantiates, so a linkonce copy the link took from it now comes from another object or none (unit 253's `-Oz` copies of
857, 1249, 2240, 9872 and 10145 after `IServicoEstado::Salva` took `const ESTADO&`): read `names.tsv`'s object column
for the lost rows' symbols against the base's link, and that object's function list before and after. A displaced copy
takes along the callees only it reached: when your object's instance of a library template links ahead of another
object's, the other copy's out-of-line callees can lose their last caller, and their matches go (11616's
`parse_iso_time` took five `vector<std::string>` helpers so). List the base object's relocations of the displaced copy's
callees (`wasm-objdump -d -r <the base's object>`), and give the lost rows' target callers a stand-in. And with no
source at fault, for one link's data layout, in four cases:

- **An object at address 0x100000.** `-Oz` writes the add of that address as a subtract, so a body that adds it reads
  `differs` with `i32.const -1048576` on our side ([facts/codegen.md](reference/facts/codegen.md) §C7).
- **A constant at a string's closing NUL that equals a table slot of ours.** Step 8 reads a constant whose two values
  address one string as an address, but not the empty string at a NUL, which the target holds in too many places, so a
  pair that passes it still votes the function in our slot onto the target's slot. A name that gets two contradicting
  votes goes, and a matched caller that needs it reads `unresolved` on `a table slot of ours: <name> has no target
  function`. It is this case when the caller's body did not change, the name's line left in `git diff
  splat/symbol_addrs.txt`, our slot of the name is the address of a string's NUL in our data, and a matched pair
  passes that constant on both sides ([facts/splat.md](reference/facts/splat.md) §S8 item 1 traces a `table` line).
- **A folded array base inside the `.bss` object before the array.** A new pair whose constant is an array's base less a
  folded index (`&a[i - 2]` as `a - 48`) votes the name of whatever our layout puts there; when the array's alignment
  pads differently in the two links (our residue mod 8 or 16 against the target's), the vote contradicts the name's
  other voters, the name goes, and the matches that read that object fall. It shows as one more `dataVoteConflicts` in
  step 8's summary and a data name gone from `git diff splat/symbol_addrs.txt` whose `by:` list holds the lost rows, and
  withdrawing the new pair's line does not help (12936's `staticMutexes - 48` took `sqlite3BuiltinFunctions` from 962
  and 2352).
- **A table slot below 1024 that another object's edit moves.** Our slots follow the objects' first mentions of
  function addresses ([facts/placing.md](reference/facts/placing.md) §P4), and the census's `addr` tier compares a
  constant below 1024 as a literal, so a seed pair that passed it falls to `shape` and its votes go: an edit of the
  executable TU moved an invoke's slot from 3 to 4, and the ten rows that rest on 988's pair (`locale::classic`) left
  `match`. Compare `wasm-objdump -x -j Elem` slots 1 to 5 with the base's link's, and keep the object's first function
  references in their order ([facts/splat.md](reference/facts/splat.md) §S10 item 28 has the check).

Before calling a residue chance, compare the run the object sits in with the target's: the object our link puts right
before the library's first `.bss`, `.data` and `.rodata` object, against the target's (the symbol file's `type:data`
names by address). Data order is link order, so where the target's data put the library elsewhere on the link line, its
place there is evidence ([facts/link-order.md](reference/facts/link-order.md) §L3 has SQLite's between OpenSSL's and
libc's in each segment, and the residue it fixed). Only a residue the two orders agree on is chance. The next landing
that moves the data clears it. Never add or drop a string to move it, and add no hand line for the lost name: its only
evidence is the lost row's operand ("Hand edits", below). A lane whose own link loses a match of its base so stops and
reports it; at a landing, land the next lane first and retry (step 10). A small integer in a data object that equals a
table slot of ours is not such a case: the operand-kind table reads it as the integer it is
([reference/splat.md](reference/splat.md) §3). Nor is a whole string whose address equals a table slot of ours, where
the target's constant addresses the same string: step 8 reads it as an address.

The scan's first pass can also leave a new match `match` that the build's fixed point refuses: `make -C src splat` then
stops on `UNCONFIRMED: self-voted`. Read it as `unresolved self-voted`: the callee's name has no voter but the match,
and neither state of the line passes both checks ([facts/splat.md](reference/facts/splat.md) §S14 has why). Make the
callee's name hold, by matching what it waits for (1166 held once 13974 matched, which confirmed 1322), or keep the
code that brings the row out of the link until it does (3526 and 9518 waited so for 2393 and 2688).

A row of another unit can turn `match` for a reason you can name:

- **A name your unit released.** A row that was `unresolved self-voted` waited for its callee's name to have a voter
  besides itself ([reference/splat.md](reference/splat.md) "No circular evidence"). A unit that adds another use of the
  name releases it, and the row matches: 5483, `api::CIniKey::operator=` (unit 01), turned `match` when five throws of
  a later unit gave `CBaseError<EUeIoError>`'s constructor other callers. The match belongs to the unit that holds the
  body; say which in the commit message. When the voter that releases it is no match (the census pair of an
  `unresolved` row: 7049's holds eight OpenSSL rows so), the row rests on the whole link: add it, with its voter, to
  [facts/splat.md](reference/facts/splat.md) §S10's list in the same commit (item 20 is 7049's).
- **A body the content pass pairs.** The pass pairs one of our bodies that no match holds yet (called or not) with a
  target body it equals when no other unmatched target body equals it, by locals and opcodes, not by wasm type, so a
  small or empty body pairs as soon as another match removes its last twin. Among bodies alike, the name can be the
  wrong one, and the build cannot tell ([facts/splat.md](reference/facts/splat.md) §S11 has the cases). A row whose
  detail reads `address same-content` or `table slot copy`, or whose `source` is `content`, is checked against what
  calls or points at the function and against the matches of its neighbouring target indices (`awk '$1==<i-1> ||
  $1==<i+1>' splat/matched.txt`, and their link order, step 3: the file runs in landing order, so a new line's own
  neighbours say nothing). Among thunks that differ only in a vtable constant, the line goes on the object whose vtable
  holds the target index (step 1's vtable command). Correct the line by hand when they disagree; a corrected line
  stands only when a re-run of steps 7 to 9 keeps it (`0 matches added, 0 renamed`, nothing written). When the function
  the data name is in no unit yet, no correction holds, since the census pairs the index with our body: write the real
  function (a member of the class the data give, often a thunk over a shared body), whose vtable then names the index
  (§S11 has the crossed thunks and 10604's case, §S12 a record the target holds more than once).
- **A literal your unit brings.** A written row that waited for a literal it shares a tail with (step 5) matches when
  your unit adds the longer literal (12621 with 11973's). The match is the body's unit's.
- **A flag change.** Every row a flag turns `match` belongs to the unit that holds the body, whose fragment and README
  row say what it waited for: the flag's commit edits those notes, comment lines only, and the link stays
  byte-identical (below).
- **A body binaryen treats otherwise.** Code your unit brings can give one of the body's callees more call sites, so
  binaryen stops inlining it there (5445, `CTimer::~CTimer`, once `future.o`'s members came with a unit's
  `std::async`). The match is the body's unit's; show it with a link that swaps your unit's objects back to the base's.
  Such a row rests on the whole link: add it to [facts/splat.md](reference/facts/splat.md) §S10's list, with the objects
  whose swap back loses it, in the same commit (item 27: 4689, a libc++ `~__split_buffer`, kept the target's unused
  load once a range moved the module).
- **Data at the target's own address.** Step 8 casts no vote for an address both layouts share, so when your objects
  move a data object to the target's address, a data name only one row voted for goes, and that row, `unresolved
  self-voted` on it before, matches by content. It rests on the whole link: add it to
  [facts/splat.md](reference/facts/splat.md) §S10's list in the same commit, and a landing that moves that data takes it
  out again, a data-layout loss (above): §S10 item 31 has such a row, OpenSSL's `provider_activate` (3138), which its
  lane's link matched while our `core_dispatch_` sat at 0x199290 as the target's does, and which is out on this tree.

A match the scan found by its body or by the census's pair has `content` or `ledger` in the `source` column of
`splat/scan.tsv`, in the first scan only. Once the match names the function, a later scan writes `symbol` there, so a
rescan of the committed state differs from the committed `scan.tsv` in one such line per new match the scan found that
way (its `detail` can shorten too: [reference/splat.md](reference/splat.md) "Reviewing a match"), and a renamed twin's
row can go from `ledger` to `symbol` the same way. Commit the rescan's file ([reference/splat.md](reference/splat.md)
"Reviewing a match"): a reviewer's rescan of the committed state then changes nothing, and the check that survives is a
new match the scan found by its body or by the census's pair: for each index `i` that `comm -13 <(cut -d' ' -f1 <old
matched.txt> | sort) <(cut -d' ' -f1 splat/matched.txt | sort)` prints, `/usr/bin/grep -c -E "= func:$i;"
splat/symbol_addrs.txt` prints 0 for such a match and 1 or more for one step 8 named (below), whose row reads `symbol`
from the first scan. Search by index, not by symbol: a thunk's symbol also ends the name of the merge
body binaryen named after it (`byn$mgfn-shared$<the thunk's name> = func:3884;` for 2744). A new match that step 8 had
already named (`evidence:srcloc-anchor`, `pair-*`, `call`, …) has `symbol` from the start, and then a rescan changes
nothing: on an unchanged tree `TMPDIR=/tmp make -C src splat-match` ends with `0 files written` and `git status` shows
nothing. Neither is drift; commit what the generator writes.

An edit after this step that leaves the plain link byte-identical (a comment; `shasum -a 256
build/out/wasm/vota_web/vota_web_wasm.wasm` before and after the link) changes nothing steps 7 and 8 read: run
`splat-match`, which writes back any stubs you stripped, then `splat`. Any other edit goes back to step 6. Step 9 itself
rewrites the stubs and gaps of your sources, so the next target that needs the link (step 8 again, for a hand line)
recompiles them and relinks: when `shasum -a 256` of the wasm is the same before and after, the census need not run
again. When one of them is a header (`git status` lists it), every object of its tree is stale again, and `make -C src
splat` compiles them one at a time, for most of an hour: count `make -n -C src link | /usr/bin/grep -c -E '(em\+\+|emcc)
.* -c '` after step 9, compile with `-j` on the object list first (step 6 item 4: 162 objects in 53 s at `-j8`), and
compare the wasm's sha256 with the census's link before `splat`. A comment in `src/Makefile` recompiles every app
object, since each depends on it (`make -n -C src link -W $PWD/src/Makefile | /usr/bin/grep -c 'em++.* -c '` prints 725
at bbf27ac1): compile them with `-j` on the object list first (step 6 item 4), then link.

**Hand edits.** A *match* is a promise that the build keeps producing that body. Never edit a piece, and never add a
symbol-file hand edit whose only evidence is the match it enables: a name whose only use is to make a function match
proves nothing. A hand edit is allowed when no generated route reaches a name and evidence outside the match gives it: a
callee whose callers in the link are all named by `vtable` (those cast no votes) and whose other callers are not written
(3613's line: its one target caller besides itself, 10409, is named by `vtable`), a callee with one caller that can
land, a merge body's own callee, a `.bss` object, a `.data` or read-only object too small for its bytes to place, or a
small pointer that no vote reaches, led by the target functions other than the match that read or write it, its static
destructor among them, a thunk into a shared body too; a data object the match alone touches has no such
evidence and takes no hand line. [reference/splat.md](reference/splat.md) §2 has the kinds,
what each rests on and what each comment must cite (a line with one caller's, and one that carries every caller it
names, above all: §3's self-vote rule does not read hand lines), and §3 "No circular evidence" the data object only the
match touches.

A verifier weighs each line by removing it, on copies of the symbol file and the match list: "Reviewing a match" there
has the two removals (the hand line alone out decides), the scan run twice beside a control that drops the same match
lines and keeps every name, `splat-build` on the copies after it, since the scan can add back a match the build's fixed
point refuses, and what removing one line at a time cannot show. Run the same on a hand line before you add it. A line
no removal shows carrying anything goes: a line a generated one has caught up with (the `awk` there, which is no
removal: "Reviewing a match" says which of those stay), and a `func:` line for a body the content
pass finds alone. Then weigh the lines you keep again on the file you commit. After a landing, weigh every hand line
whose function or matched callers your new matches touch, with a generated twin or not: the `awk` lists only the
caught-up ones, and 3764's `callers+content` line carried nothing once the executable TU's copy re-pointed. A line names
a new match's index, or the function a new match calls: the searches by the new indices and by their callees
([facts/workflow.md](reference/facts/workflow.md) §W23) list both. Weigh too every hand line whose generated twin the
range changed: a link-order move or a removed stand-in changes a twin's evidence with no match touching it
(`ESCAPES.2`'s twin gained 14478's vote in a landing none of whose matches reads it, and its line then carried
nothing). This lists them against
the base (at c3a97777 against 76661cb7, 1692's and 5769's):

```sh
git diff -U0 "${BASE}" -- splat/symbol_addrs.txt | sed -n 's/^+\([^+# ][^ ]*\) = .*/\1/p' | sort -u > build/out/<handle>/twins.txt
awk '/^# ---- hand edits below/ {h=1; next} h && !/^#/ && NF {print $1}' splat/symbol_addrs.txt | sort -u | comm -12 - build/out/<handle>/twins.txt
```

A line found idle for a cause your landing did not
bring (its symbol gone from our link, a body merged elsewhere: 543's `merged-body` line for
`vector<ASN1::AbstractData*>::push_back`) goes in a commit of its own with the docs that cite it, after a `queue/` post;
your commit keeps it. A caught-up line is not such a case: a range whose match touches it removes it
([reference/splat.md](reference/splat.md) "Reviewing a match"), unless a doc cites it as an example: then it goes in a
commit of its own with that doc (9c5ede00). A
merge body's own name, `byn$mgfn-shared$<first member>` (`@<object>` after an internal one), is one our link derives: it
is no evidence of the target, it moves with link order, and step 9 renames a match line to the new one. It earns a hand
line only when the removal shows rows that fall without it, and a landing that moves the first member rewrites that
line's name from `names.tsv`'s `<binaryen>` row (2924's held its three thunks until 2924 matched:
[facts/splat.md](reference/facts/splat.md) §S10 item 2).

A data name is the same question: a generated `vote:1 by:<index>` line rests on the one body that voted, and the
build checks only that body's bytes and the object's. [reference/splat.md](reference/splat.md) §3 "No circular
evidence" says what else the fragment names to tie the operand to the object, and "Reviewing a match" what a reviewer
runs when that body is no match.

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

The review's blanked-target check blanks the function's piece, not what the symbol file already took from it, so a
data name held only by this match's own vote (`evidence:vote:1 by:<this index>`) passes both ways. Review on copies
without the name's line, and a function's match line too ([reference/splat.md](reference/splat.md) "Reviewing a match"
has the command, on 8461).

**A twin whose name moved** is the one break that is not drift. When your unit brings in a body byte-identical to a
matched one (another class's deleting destructor, another instantiation), binaryen keeps the first copy that is still
a function when it merges twins, usually the first in link order, and if yours comes first, the matched symbol leaves
our link. A copy binaryen inlined into every caller first is gone, so a later object's twin can survive (2769,
`vector<unsigned char>::__vallocate`, kept from asn1's `AVNEncoder.o` as `vector<char>`'s although the executable TU's
copy links first). A build run before `splat-match` says `function 246
matched to _ZN21ModuloTiposEleitorais4FotoD0Ev: our link has no function _ZN21ModuloTiposEleitorais4FotoD0Ev`. Step
9's `splat-match` repairs it: when a listed symbol is missing from our link and the scan matches the same index under
another symbol (the survivor, whose body re-points into the target's bytes), it rewrites that line in place and
prints the rename:

```
…/splat/matched.txt: 0 matches added, 1 renamed
  line 7218: function 246 renamed _ZN21ModuloTiposEleitorais4FotoD0Ev → _ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev: …
```

A signature you change on a matched function moves its symbol the same way, and steps 8 and 9 rename the line. Any
other missing symbol is left as written and printed (`… left as written, so the splat build fails on it`): the body no
longer re-points, so it is drift or a deleted function, and yours to fix. Say in the commit message which lines were
renamed ([facts/splat.md](reference/facts/splat.md) §S6). After a step 9 that prints `N renamed` with N above 0, run
`TMPDIR=/tmp make -C src splat-match` once more and commit what it writes: its scan ran on the list before its own
renames, so the renamed rows (and their callers') read `content` or `ledger` in the `source` column until the next
pass; a renamed row whose survivor already had step 8's line (a `pair-*` line step 8 moved to it) reads `symbol` at
once, and the second pass writes nothing. When step 9 rewrote a header's gaps (`git status` lists it), compile the
object list with `-j` first (step 6 item 4): the second pass otherwise recompiles the tree serially (607 objects in
22 minutes). To see whether a symbol is in the link, read
`build/out/wasm-map/vota_web/names.tsv`, not step 4's `symbols.{mangled,demangled}.txt`: those list every symbol of
every input, kept or merged away.

A rename can also move a line to a function that is no twin of the old one (3548, 3549 and 5268,
[facts/splat.md](reference/facts/splat.md) §S6). The count by index reads no name, so check a survivor's name against
the target body or its callers.

Some cases look like a rename and are not one ([facts/splat.md](reference/facts/splat.md) §S6 and §S11 have each). One
symbol on two lines (`cut -d' ' -f2 splat/matched.txt | /usr/bin/grep -v '^#' | sort | uniq -d` prints it) is one of
two:

- **A new line among bodies of the same content.** Its row reads `address same-content` or `table slot copy`, or its
  `source` is `content`, the build passes, and the scan's `symbol` column names the same symbol for both indices. Fix
  the new line from the data that point at it, then run step 9 again until it adds nothing, and check each addition
  the same way (§S11 has the case, 13334, and the command that reads an OpenSSL function's dispatch table).
- **A symbol that stays while its body moves.** The build stops with `no longer verifies`; edit the old index's line to
  the survivor the scan's `symbol` column gives, and look for a hand line that names the old symbol below the marker
  (`/usr/bin/grep -n '<symbol> = ' splat/symbol_addrs.txt`): one the move makes name another body goes, after the
  removal check of [reference/splat.md](reference/splat.md) "Reviewing a match" (three `pair-depth0` lines of
  `__parse_*<const char*>` pinned 3524, 5186 and 5188 to the wrong bodies).

The others: an alias, C1 and C2 (D1 and D2) on one function; twins whose objects differ, which you compare in the
final link; and an instance of yours of a matched name that is another body, which nothing renames: edit its line to
the name step 8 gives the index. A local symbol is one of these: clang numbers every internal symbol of a TU with one
counter (`__cxx_global_array_dtor.N`, `.L.str.N`, a default argument's `.L.constant.N`), so a static with an exit
destructor or a function added above the statics' initializers shifts their names while every name stays in the link
(`cinputmenufield.cpp.o`'s `.34` to `.40` became `.45` to `.48` for two new setters), and a header edit does so in
objects whose files you did not touch (an inline variable, a template's statics: 66 objects for one header move). Step
9 renames only the lines whose old name left, and reports the others as `the body verifies, the evidence says another
function` although the listed body is another one; one symbol then sits on two lines (`uniq -d` above). The report can
be missing too, and the first sign the build's `no longer verify` on those indices (or `UNCONFIRMED` on a reader of the
static): after any edit of a file or header whose objects hold matched static destructors, run the `uniq -d` above
before `make -C src splat`. A new number can also equal a name another object's match line holds unqualified, and step
9 then renames that line to `<name>@<object>` (`2 matches added, 1 renamed` for `locale.o`'s 7753): the rename is
right. Edit each line `uniq -d` lists to step 8's name, and run that check and the build before trusting
`splat-match`'s summary.

A merge can also unmake a twin. A matched body whose second and third call sites were a twin's loses them when the
other side drops that twin (a library rebuilt without landing pads), binaryen inlines it into its last caller, and that
caller's row leaves `match` with every name that voted through it. The sign is a matched symbol gone from `names.tsv`
with no rename. Give the function the call sites the target gives it in a roots file (step 6, item 3). A merge can
take away the last reader of a callee's result too ([facts/reading.md](reference/facts/reading.md) §R18, the other
direction), in an object neither side's unit owns: every caller that kept a `drop` after the call then differs by that
row. The callers' source is right: withdraw their lines (below) and write which target readers they wait for
([facts/splat.md](reference/facts/splat.md) §S10 item 17 has such rows, 6043, 11585, 11621 and 11622 over 857).

A unit can also make two functions it never touches into twins: a new caller that passes another value keeps a
parameter dead-argument elimination had folded (step 2), and two bodies become one (`std::mutex::unlock` and `~mutex`,
the target's 150; [facts/splat.md](reference/facts/splat.md) §S6). A rename line that names no symbol of yours is that.

`git diff splat/matched.txt` shows each rename as a `-` and a `+` line with the same index at the same place, and
`git diff --word-diff splat/matched.txt` as one line,
`246 [-_ZN21ModuloTiposEleitorais4FotoD0Ev-]{+_ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev+}`: a
rename, not a lost match. So count lost matches by index, not by line, against the commit your branch started from.
Against a `main` that moved since, the count also lists every match `main` gained, which are not yours to lose
([facts/workflow.md](reference/facts/workflow.md) §W6):

```sh
comm -23 <(git show "${BASE}:splat/matched.txt" | cut -d' ' -f1 | sort) <(cut -d' ' -f1 splat/matched.txt | sort)    # prints nothing when none is lost
```

`BASE` is step 9's. This compares the list only: a match whose line stayed while its row left `match` is not in it, so
read step 9's `join` and `status.py`'s `matched.txt only:` as well. After merging `main` in ("Landing onto a moved main",
below), run it with `main` for `BASE`: it must print nothing then too.

**Withdrawing a match.** When you take a matched function back out of the source on purpose (a match a review
refuted), delete its line from `splat/matched.txt` by hand (a list people edit; `splat/scan.tsv` is generated) and run
step 9 again. While the line is there, `splat-match` fails after the scan: `status.py` prints `splat/scan.tsv has 7428
match rows but splat/matched.txt has 7429 matches (scan only: [], matched.txt only: [9130])`, having already rewritten
the status files the new scan changed, and `stubs.py` does not run, so the function's stub does not come back
([facts/workflow.md](reference/facts/workflow.md) §W11). A withdrawal that takes functions out of an object can take out
what a fragment's forms were measured on: run each "differs" the fragment lists for that object again on the new
tree, and move a form that now gives the same bytes to that list, naming the function that still shows the difference.

Your new matches, and the functions your unit writes that do not match, can make other units' notes false: a callee
"with no name", a member that "waits for" one, a stand-in whose callers are now all in the link, a hand line's "our body
differs", a doc's example. Search for them as a landing does ([facts/workflow.md](reference/facts/workflow.md) §W23 has
the eight kinds and a search for each) and fix them in your commit, comment lines only, after a claim of those files,
with two exceptions. A stand-in or sink your unit makes idle goes in your commit, code and comment, call by call; one
idle since an earlier landing, or in a file another stage holds, goes as `src/units/README.md` "Finding the idle ones"
says. And a hand line whose function your match now names by a generated line is yours to weigh (the caught-up `awk` of
"Reviewing a match" first). A file another active stage claims, or a sentence an unlanded branch has changed whatever
its stage (`git diff <base> <branch> -- <file>`), is left to the landing and named in your result with the indices that
make it stale. A lane whose branch has not landed is such a stage, on either machine; when its branch is not on yours,
take the files and line ranges its result names outside its unit. A gap step 9 writes and a README row are yours to
commit even where such a branch changes the same lines: name them in the result as conflicts the landing resolves (it
runs step 9 again after the merge), and put a paragraph you add away from where the branch adds its own.

Commit in one commit: the sources, the fragment and its companion files, the fragment's row in
`src/units/README.md`, the `ledger/functions.tsv` the census rewrote,
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
git commit -F - -- <the same files> <the removed stub files> <<'EOF'
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
- `python3 -I -B tools/round/check_srcloc.py --strict <the objects of your unit's sources, whichever fragment's list
  compiles them (src/units/README.md "Names"), its companions, and every object whose code your matches hold,
  binaryen's inlining included>`, after `make -C src link-map` on the last link (an
  older map, after any relink, counts other objects' linkonce copies as wrong records:
  [facts/tool-traps.md](reference/facts/tool-traps.md) §X7). A unit of header code matches from other units' objects:
  `names.tsv`'s object column names one per new match line, but a binaryen merge's (`<binaryen>`), whose records are in
  the objects it merges, and a file no unit compiles has no object (a missing one stops the tool): leave both out. It
  must report 0 records that are not the target's
  (`build/out/app/uenux2/src/api/util/cgenerictags.cpp.o` for unit 33, whose source unit 95's list compiles: `9
  source_location records in 1 objects (1 files): 9 are records of the target; …`). A landed unit's other objects can
  hold records of unmatched functions that were already off, so `--strict` over a whole landed unit may never pass;
  show those objects unchanged instead (the object comparison of [agents.md](agents.md) "Shared build outputs"). An
  object of a landed unit that yours extends passes when `--strict` lists the same off records on it as on the base's
  object ([facts/workflow.md](reference/facts/workflow.md) §W13 compiles that) and no new one;
- from `asmlift-wasm/`, `TMPDIR=/tmp pnpm test:bench`: the benchmark's tests check that every object compiles with
  the flags of a setup in `asmlift-wasm/benchmark/dataset/setups.json`, which a flag added in a fragment breaks while
  every other check passes ([src/units/README.md](../src/units/README.md) "What a fragment holds"), and that the frozen
  dataset agrees with the tree. A setup's flags changed, a row's object moved to another setup, a symbol a row names
  renamed, or a setup added or retired fails it until a re-selection, a commit of its own after the change
  ([asmlift-wasm/benchmark/README.md](../asmlift-wasm/benchmark/README.md) "Re-selecting";
  [facts/workflow.md](reference/facts/workflow.md) §W25 names each failure). CI runs it with only the `third_party/`
  trees it fetches, so a fragment that reads another adds that fetch in the same commit
  ([facts/libraries.md](reference/facts/libraries.md) §B11 item 2);
- from `asmlift-wasm/`, `TMPDIR=/tmp pnpm test`, alone in the checkout: beside a census or `splat-match` its real-link
  cases skip and it still exits 0, so read the count: every case passed and none skipped. A failing case is your
  branch's only if the commit it started from passes it: [facts/workflow.md](reference/facts/workflow.md) §W12 lists
  the cases any landing can move, the commands that build that commit, and two readings that are no failure (`4
  skipped` without the `emscripten/emsdk:6.0.0` tag; `Errors N errors`, each `Timeout calling "onTaskUpdate"`, which
  you report as the harness's). A new test gated on
  `build/out/` skips in CI, so it raises that suite's budget in `.github/CI.md` "Skipped tests" and
  `.github/workflows/ci.yml` in the same commit. A lane does not edit the toolkit's tests to land a match: a member
  whose match needs a function a case reads out of our link stays unwritten, and the fragment says why
  ([asmlift-wasm/README.md](../asmlift-wasm/README.md) "Tests" names those cases).

**Landing onto a moved main.** When another unit landed after your branch started, merging conflicts in generated files.
Resolve only the files people write: `src/units/README.md` keeps one row per fragment, both sides' new rows in the
table's numeric order (100 after 99), and of a row both sides hold the side that changed it from the merge base, by hand
when both did: git joins adjacent rows into one hunk, so "keep both" gives a row twice
([facts/workflow.md](reference/facts/workflow.md) §W20). Its prose can conflict too: keep
both sides' sentences. Some joins pass every conflict check and are wrong:
[facts/workflow.md](reference/facts/workflow.md) §W27 has a count both sides changed to the same text, a companion each
side took a different member out of, a gap line, a carried hand line and a trial merge. A `git add` clears a file's
conflict state whatever it holds, so before step 6 `git diff --cached -G '^<<<<<<< ' --name-only` must print nothing;
`git diff --name-only --diff-filter=U` prints nothing once the file is added. `splat/matched.txt` keeps both branches'
match lines (step 10 checks every one again), each index once. Two units can match the same function (a base's
destructor both bring in: 11013, `api::IFormFieldBase<api::IPaper>`'s, came with two units), and a second line for an
index stops step 8, whose `kinds.json` rule reads the list, with `Error: match list line N: function 11013 is already
matched on line M`; git may join the two additions, keep both or mark a conflict, depending on where each side put its
line, so check the resolved list before step 7 (the `uniq -d` below). Two branches can also each
have renamed one twin to its own class, a one-line conflict on the index. Keep either side's line: the merged link does
not exist yet, and step 9 renames the line to the survivor when the kept symbol left it. After step 9, `awk -F'\t' -v
s='<symbol>' '$2 == s || $2 "@" $3 == s' build/out/wasm-map/vota_web/names.tsv | wc -l` prints 1 for a kept symbol, a
local `name@object` line's too, whose name and object are two columns there. Count that match once, and check that none
is left twice ([facts/workflow.md](reference/facts/workflow.md) §W16):

```sh
/usr/bin/grep -v '^#' splat/matched.txt | cut -d' ' -f1 | sort | uniq -d     # prints nothing when no index is listed twice
```

The stub file keeps both branches' removals; a conflict inside a `// <stubs>` run can take either side, since stubs are
comments and step 9 writes them again, as it does a gap line's numbers (§W27). Do not run `make -C src stubs` on the
merge before step 9: until steps 7 and 8 rewrite the census and the symbol file and step 9 the scan, they are one
side's, so the generator puts back the stubs of the other side's matches and pending members and recreates, untracked,
the stub-only files that side removed. Step 9's `splat-match` runs it on the new scan and writes back what the merge
holds ([facts/workflow.md](reference/facts/workflow.md) §W14). Every other generated file takes one side whole, with
`git checkout HEAD -- <file>` (it stages that side), conflicted or not: a `git add` of a conflicted file stages its
conflict markers. A generated directory taken so keeps the files only the other side added: `git rm` them, as for
`asmlift-wasm/benchmark/dataset/selection-inputs/`, whose extra files fail `pnpm test:bench`. A lane's selected dataset
(under `asmlift-wasm/benchmark/`, `dataset/rows.json`, the `dataset/selection*` files and `results/baseline.*`) never
lands over `main`'s: take `main`'s, keep both sides' setups in `dataset/setups.json`, and re-select once after the last
merge, in a commit of its own, when a row needs it, and always when a merged lane added or retired a setup, whose merge
commit fails `test:bench` until then ([asmlift-wasm/benchmark/README.md](../asmlift-wasm/benchmark/README.md)
"Re-selecting"). `splat/symbol_addrs.txt` is half generated, and a side taken whole keeps only that side's hand edits,
which step 8 cannot bring back, so first compare what each side holds below its hand-edit marker, carry over by hand
any line only the other side has, and drop the lines the other side removed, with the comments it rewrote: `git
merge-file` of the three sections from the marker down (the base's, the side taken, the other side's), each written to
a file, gives both at once (§W27). A name both sides hold keeps one line, with the stronger evidence or the larger voter
set: two lines for one name pass every check. Take a side once, before carrying hand lines, and after step 8 check `N
hand edits kept` against the parent's count plus the lines carried (§W27).

A header your unit needs that `main` gained after your branch started is an add/add conflict: create it from `main`'s
text (`git show main:<path> > <path>`) and only add to it, so the merge is one hunk, and say so in the commit. A
header that is not on `main` yet but on a branch that lands before yours: copy it from that branch byte for byte
(`git show <branch>:<path> > <path>`), claim it, and do not edit it. git merges an add/add of one blob with no
conflict (`git hash-object <path>` and `git rev-parse <branch>:<path>` print the same id;
[facts/workflow.md](reference/facts/workflow.md) §W17). If that branch changes the file before it lands, take
`main`'s text at the merge, as above. A header on `main` whose new lines your rows need from such a branch is the same
case: take that branch's whole committed blob, so both sides make one change, and put lines of your own in a hunk
apart (below). While the owner has not committed it, measure with a stand-in under `-iquote`
(step 4) and do not commit one: a copy of a working file is not the blob the branch will hold. Copy from the branch
only, and compare `git hash-object` with the branch's blob after step 9, since the generator rewrites a header's stub
run. When your rows need lines in a file such a branch creates, do not create it on your branch: post the lines and
their measurement for the landing, which adds them once that branch has landed. A header on `main` that an unlanded
branch changes: start from `main`'s text, add only, in a hunk apart from the branch's (`git diff` of both against the
merge base shows them), and keep what rests on your lines in a commit of their own, so a landing can take the rest
alone: that commit has its own generated files, steps 6 to 10 run on the state before it, and when a brief asks for
one commit, name in the result the lines and the matches that rest on the header instead. `git merge-file -p <yours>
<base> <theirs>` on the three blobs, each written to a file first (on `<(…)` it prints nothing: §W27), prints no
`<<<<<<<` when they join.

Your branch was written against the docs of the commit it started from. When `main`'s docs changed since, read your
unit's choices against `main`'s docs too before the merge (`git diff "$(git merge-base main HEAD)" main -- docs
src/README.md src/units/README.md`), since the merge lands under them.

Then run steps 6 to 10 again on the merge: link, census, symbols,
match, build and the checks, and count lost matches against `main`. A flag change measured on an older base is
measured again there: a row of the lane that no longer matches on the merge is withdrawn ("Withdrawing a match",
above), never tuned back, and the commit says which. A merge can fail to compile where neither side's
text is in conflict: [facts/workflow.md](reference/facts/workflow.md) §W24 has the four ways met so far, each with its
error and its fix (a header that reaches a library path, a changed signature, one name declared two ways, one member
added on both sides). One that joins a side's gap with lines the other side added above it stops step 9 in `stubs.py`
(`lines added above the gap comment reach past the gap`): [src/README.md](../src/README.md) "Gaps" says what moves.

Some matches rest on the whole link and not on a source, so a merge that touches none of them can drop them: after step
9 run the check of [facts/splat.md](reference/facts/splat.md) §S10, which lists them, and stop if one left `match`. A
row lost to one link's data layout, with the cause shown (step 9's four cases), is the one loss a batch may wait out:
land the next lane first, which moves the data, and retry the merge; stop if the row is still out. Read each roots
file's reasons again too, since a stand-in beside its real caller can pass every check (one that calls what the target
inlines into that caller unmatches it instead: `src/units/README.md` "Companion files"): a stand-in, or a call of one,
whose every target caller is now in the link goes in this merge, before these steps, and one whose callers landed in
part stays (`src/units/README.md` "Companion files" has the rule, its cases, the per-callee search and where one found
after the merge commit goes, "Finding the idle ones"). A caller's call in our link is found by the callee's `ours` index
(for 5103, ours 5303 at bbf27ac1, `wasm-objdump -d build/out/wasm/vota_web/vota_web_wasm.wasm | awk -v c=5303 '/ func\[/
{f=$2} $0 ~ " call " c "( |$)" {print f}' | sort -u` prints `func[10515]:`, 9052's, and `func[10667]:`). A stand-in can
also stand for references that are no call (an address taken in a static constructor, or for a vtable slot), and other
units' notes can name a function the merge matched as one that waits: run the searches of
[facts/workflow.md](reference/facts/workflow.md) §W23, whose kinds a search by the new indices misses (an address root,
a sink, a caller list, a removed stand-in's name), and fix what is stale in the merge or a comments-only commit after
it. A stale note in a hunk that a branch of a later batch changes, or on a line next to one it changes, is left to that
branch's landing and named in the result: git joins adjacent lines into one hunk. Commit it all as the merge commit. A
merge commit takes no pathspec (`fatal: cannot do a partial commit during a merge`): stage everything, read `git status
--short`, and commit with a bare `git commit -F -`, owning the checkout while you do, since nothing else may be staged
([facts/workflow.md](reference/facts/workflow.md) §W18). To leave a merge after step 9, `git merge --abort` needs
everything staged first (§W22). Two branches that each took "the next free NN" collide too; `src/units/README.md`
"Names" says how to avoid that.

## Library functions

Most `differs` rows belong to upstream libraries (OpenSSL, SQLite, libc++, 7-Zip, RHVoice, …). We do not write
their C++: it is built from the library's own sources at the version `third_party/MANIFEST.md` pins. When such a row
differs, the code is usually right and something around it is not. The scan's `detail` column says which:

| `detail` says | what is usually wrong | how to look into it |
| --- | --- | --- |
| `an address of ours: … (.data) has no target symbol`, `… (.bss) has no target symbol` | the symbol file has no name for a data object the body uses, and its content does not place it either: what follows the `;` says why its re-pointed bytes did not (not in the target, several places of a writable object, too little content); a `.bss` object is zeros, so only a name places it | find independent evidence for that object (RTTI, a unique string or content, a census pair) and see whether `make -C src splat-symbols` picks it up; [reference/splat.md](reference/splat.md) §2 lists the evidence kinds and §3 how content places an object. The object named is our candidate's, and the census pairs identical bodies in any order, so for a body that only loads the address (a static destructor above all) the target's constant says which object it is: 9383 read `target … i32.const 1911891 \| ours … i32.const 1912015` while our candidate was another object's static destructor (it matches since its own object's copy is in the link) |
| `… re-pointed bytes occur 65+ times` on a row whose body did not change | a pointer word of the object resolves nowhere (the function or object of ours it points at has no target name, or the shifted link moved the word by neither shift), so it reads as anything and the pattern fits too many places. A word the shifted link shows is an integer keeps its bytes, so a small integer that equals a slot of ours (an ASN.1 tag) is not the cause | print the object's words with their kinds (`data` in `build/out/wasm-kinds/vota_web/kinds.json`), and `wasm-objdump -x -j Elem` for a slot; the pointer's own name comes first (step 8), and a `content` hand edit of the object on its own evidence holds it meanwhile (step 9, "A body need not have changed") |
| `a table slot of ours: X has no target function` | the shifted link says the operand is a pointer to our function X, and the symbol file names no target function for X | the same as a callee with no target function: X's own match or name comes first (step 8) |
| `a table slot of ours: the target function fills N slots` | in a kind-unverified function, the operand may be a pointer to a function the target's table holds in more than 64 slots (binaryen's merged empty function fills 126); without its kind, re-pointing offers a function's slots only up to 64 | the source is not at fault: the check cannot re-point such an operand ([reference/splat.md](reference/splat.md) §3 "Operand kinds") |
| `the address resolves (symbol)/(string) to another place` | our data sits elsewhere: a different string merge, a missing or extra object, or another version's constants | compare the two strings or objects at the addresses the detail prints; check the version evidence in `third_party/MANIFEST.md` |
| `target i32.const N \| ours i32.const M` with small numbers | a table slot: the function-pointer table holds functions in another order, because another set of functions is address-taken | the roots TUs (`src/app/roots*.cpp`, the units' `-roots.cpp`) and the link order decide the table; [reference/link-order.md](reference/link-order.md) |
| `target call X \| ours call Y` | the callee resolves to another target function: a callee without a name, a twin, or an inlining difference | `pnpm wasm splat-remap … --against <index>` prints how every operand resolves |
| `the locals`, or an instruction that differs in kind | codegen: the compile flags (`-O` level, `-fPIC`, `-DNDEBUG`), the library version, or inlining | the library's flags and their evidence are in `docs/reference/facts/libraries.md` and `tools/libs/<lib>/census.json`; a root that exports or calls a function once changes what binaryen inlines ([facts/tool-traps.md](reference/facts/tool-traps.md) §X1); two bodies that differ in local numbers alone can come from the order of a caller and its callee (step 3, "Code binaryen inlined from another function"), and so can a body whose early return is `if … return` in one link and a block result in the other: the order of the library's objects decides which of a thunk and its callee binaryen keeps (zlib's `crc32`, 893, [facts/codegen.md](reference/facts/codegen.md) §C4), so read the target's use bands before trying flags. The scan stops at the first difference, and the locals come first, so this says nothing of the rest of the body: compare sizes and run `pnpm wasm score` |
| `an address of ours: string tail occurs N times` | the operand is a string's end pointer, and our link holds as a string of its own what the target holds as the tail of a longer literal, so the end resolves only to the empty tail | the case of a literal that waits for the one it shares a tail with (step 5, 1161's): link a scratch object that holds the longer literal and keeps it |
| `an address of ours: 0x… is in no data object of ours` | an array base with a constant index folded in (`lengthTableBits[mode][version - 1]` as `lengthTableBits - 4 + …`) lies in the padding before the array, in both links, and the scan places only an address inside an object; one that lands inside the object before the array votes that object's name onto the target's address | the scan cannot place it yet (2218, 2718 and 3595, libqrencode's; [reference/splat.md](reference/splat.md) §3, [facts/libraries.md](reference/facts/libraries.md) §B10): leave the row, and check a `vote:1` `.bss` line its body casts against the target's layout before trusting it |
| `read-only object: bytes not in the target` | our constant data is not the target's: another version or another configuration (`#define`s) | `tools/libs/discriminate.py` lists the target functions that tell two builds apart |

A C function with no TSE record, a data table of a known format and a TSE caller can be a library the manifest does not
list, with a stub in a tree's `unplaced.cpp` all the same: 5349, 5350 and 5352 read as `api::CPosixRWMutex`'s and are
libqrencode's. The step then is to pin that library, not to write it under `src/ecourna/`:
[facts/libraries.md](reference/facts/libraries.md) §B11 lists what that takes (its fetch, CI's too, its objects, a
benchmark setup of its own, a stand-in for its unwritten TSE callers), and §B9 and §B10 how its version and flags are
judged, in the whole link.

A library function your unit's source calls pulls its archive member into the link, and the member's other functions
that then match land with your unit (5374 inlines `directory_iterator`'s constructor, and ten functions of
`libc++.a(directory_iterator.o)` match). Check that the target's own code reaches that member too (its constructor,
`__increment` and `operator*` are the target's 3373, 3372 and 2574), and weigh a member the content pass names by its
target callers and by who passes its table slot on both sides (`/usr/bin/grep -rlE 'i32\.const <slot>($|[^0-9])'
build/out/splat/pieces/asm`), since such functions are often reached only through `invoke_*`. And libc++ declares
`extern template` instantiations its library defines (`__sort<__less<T>&, T*>` for every arithmetic `T`, in
`algorithm.o`): a `std::sort` over an `unsigned*` with the default order brings `algorithm.o`'s copies at the library's
flags, which match with no source of ours (2578 and 2579, [facts/placing.md](reference/facts/placing.md) §P1).

To compare the two bodies side by side, read the target with `pnpm wasm fn ../target/vota_web_wasm.wasm <index>`
and ours with `pnpm wasm fn ../build/out/wasm/vota_web/vota_web_wasm.wasm <ours>` (the scan's `ours` column). A fix
to a library row is a change of flags, roots, link order or symbol evidence, so it can move many rows at once, and
it is checked the same way: link, census, symbols, match, splat build. A library source differs from its pinned tag
only where the target shows it without reading a match (a body thousands of bytes longer than ours, a signature no
upstream commit changed), through an overlay in the library's build script that leaves the checkout clean, with the
other forms listed in the fragment and a line in `third_party/MANIFEST.md` (RHVoice's `str_hts_engine_impl.cpp`). If you are new to the project, start with
TSE functions; the library rows need the background in [reference/toolchain.md](reference/toolchain.md) and
`docs/reference/facts/`.
