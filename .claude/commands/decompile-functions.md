---
description: Run a decompilation round on urna, from picking target functions to landed, independently verified splat matches, with one worktree per lane, a message board and a doc-friction log
argument-hint: <index> [<index> ...] | <count> <component> | <count> tse [agents=<N>] [round=<NAME>]
---

Arguments: **$ARGUMENTS**

- `<index> [<index> …]`: the target function indices to match, one lane each (`9132 9131`).
- `<count> <component>`: how many functions to match from that component (`2 ecourna`); the PICK stage chooses
  them. The component names are the `group` column of `splat/scan.tsv` (`docs/status.md` "By component").
- `<count> tse`: how many functions to match from TSE's own code, the origin "TSE code" of `docs/status.md` "By
  origin" (`vota`, `comum`, `api`, `simulador`, `vota-web`, `ecourna`, `asn1-modules`, `ASN1`). PICK chooses across
  all of them, and the lanes may come from different trees. A request in words ("3 functions from the TSE's own
  code") is this form. The other origins are not: upstream library rows are fixed by flags, roots and link order,
  not by writing C++ (how-to "Library functions").
- `agents=<N>`: how many agents may run at once. **The default is 2.** Raise it only when the user says so.
- `round=<NAME>`: the round's handle, used in post names and agent handles (default `DECOMP<n>`, with `<n>` one
  more than the highest such number among the board folders in `$HOME/.cache/urna-board/`).

If `$ARGUMENTS` names neither indices nor a count with a component or `tse`, ask the user which functions or which
component and how many before doing anything else. Do not choose the component yourself.

**You are the coordinator**: the top-level session. You create the board and the worktrees, launch every stage as
its own subagent, own the urna checkout's `main` and are the only one who talks to the user. This file adds no
decompiling method of its own. How to decompile one function is
[docs/how-to-decompile.md](../../docs/how-to-decompile.md), and how several agents share a checkout and a board is
[docs/agents.md](../../docs/agents.md). Do not restate them in briefs. Link to them, so a docs fix reaches the next
round.

The round has six stages, each run by its own agent:

| stage | agents | where | writes |
| --- | --- | --- | --- |
| 0. board | you | `$HOME/.cache/urna-board/<run-id>` | the board |
| 1. PICK | 1 | the urna checkout, read-only | a pick post |
| 2. MATCH | 1 per lane | the lane's worktree | the lane's branch |
| 3. VERIFY | 1 per lane, not the matcher | the lane's worktree, on the lane's machine, read-only | a verdict post |
| 4. LAND | 1 per batch of confirmed lanes | the urna checkout's `main` | merge commits on `main` |
| 5. DOCS | 1, or 2 split by file and 1 to reconcile them | a worktree each | a docs branch |

Never run more than `agents` (default 2) of them at once, counting every stage. Two whole links at once take
about 7 minutes each against one minute alone (how-to step 5), so a third agent mostly makes the other two slower.
A lane's VERIFY may start as soon as its MATCH returns, while the other lane is still matching, and LAND may take
the confirmed lanes in batches while others still match. DOCS runs every second round, on the friction posts since the
last DOCS stage, alongside the next round: no lane waits for it. A round on two machines follows [docs/agents.md](../../docs/agents.md) "Two machines": Stage 0 runs on
each, a lane matches and verifies on one machine, its build being there, and LAND runs on one.

A delegate tool reports an agent as finished when it ends its turn, even with a build still running. So every brief
carries rule 9, and a stage's result is its post, not its last message.

---

## The rules every agent is held to

Put this list in every brief, word for word. It is the standard a match is judged by.

1. **Docs only.** Learn how to decompile only from the repository's documentation, read from your own checkout:
   `README.md`, `docs/getting-started.md`, `docs/how-to-decompile.md`, `docs/glossary.md`, `docs/agents.md`,
   `docs/reference/**`, `src/README.md`, `src/units/README.md`, `tools/README.md`, `asmlift-wasm/README.md`, and
   the code they point to. When a doc is silent, wrong or ambiguous, resolve it the best way you can **and** post a
   friction entry (below).
2. **The exact splat check is the only verdict.** A match counts when `TMPDIR=/tmp make -C src splat` prints the
   target's sha256 `8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2` with it in
   `splat/matched.txt`: byte-identical after re-pointing. No blinding, no census tier, no score.
3. **The real function under its real name.** The body is plausible original C++ for that function: the name the
   evidence gives (records, RTTI, vtable slot), the project's real classes and headers, source types, Latin-1 TSE
   sources, every `std::source_location` throw on its record's line through the existing gap and `#line`
   mechanism.
4. **No lifter scaffolding** in a source that lands: no `volatile` stores, no empty `asm` barriers, no
   `may_alias` casts, no `goto` a loop or an `if` would express (how-to step 3).
5. **Stand-ins add only what the docs sanction.** A `-roots.cpp` reaches a function the way the target does, and
   a `-pending.cpp` holds trapping members (and what their vtable brings), as `src/units/README.md` "Companion files"
   says. Nothing else changes to make a match land.
6. **Generated files are regenerated, never edited**: stubs and gaps, `splat/scan.tsv`, `splat/symbol_addrs.txt`
   above its hand-edit marker, the status blocks of `docs/status.md` and `README.md` and the waffles
   `docs/img/progress-*.svg`, `ledger/functions.tsv`. The commands that write them are how-to steps
   7 to 9.
7. **House rules** ([docs/agents.md](../../docs/agents.md)): `TMPDIR=/tmp` on every docker command, no wildcard
   `rm`, no `git stash`, `/usr/bin/grep` over the Latin-1 sources, never push. Commit messages end with the
   co-author trailer your session's instructions give.
8. **The board**: read its `README.md` and `inbox/` at the start of your stage (the inbox is the user's word and
   outranks your brief), post a `rounds/` claim of the paths you own before editing, and post what you learned as
   `facts/` and `traps/`, with the command behind every number.
9. **Stay in your turn.** Run a long build in the foreground or wait for it, and end your turn only when your stage's
   post is written.

### The friction log

The round exists to make the docs right for the next contributor, so every friction is a deliverable. A friction
is any point where a doc in rule 1 was missing, wrong, ambiguous or misleading. Each one is its own post,
`board/friction/<stamp>-<HANDLE>-<slug>.md`, with:

- **doc**: the path and the section (or line);
- **expected**: what the doc led you to expect;
- **happened**: the command you ran and what it printed;
- **resolved**: what you did instead, and the doc change you suggest.

Post it when you hit it, not at the end of your stage.

---

## Stage 0: the board and the lanes (you)

1. **Check the checkout.** In the urna checkout, `git status --porcelain` must print nothing and
   `make -n -C src link` must say `Nothing to be done`: the lanes clone its build outputs and mtimes, so a dirty
   tree or a stale link is copied into every lane. If either fails, tell the user and stop.
2. **Create the board** at `$HOME/.cache/urna-board/<run-id>-<ROUND>`, where `<run-id>` is the output of
   `date -u +%Y%m%dT%H%M%SZ`. It is outside the repository and never named in a commit or a doc. Print its
   absolute path to the user in your first message: it is their handle on the round if this session dies.
   Create, folders first:

   ```
   board/facts/  board/traps/  board/rounds/  board/friction/  queue/  inbox/ack/  shared/
   README.md     INDEX.md
   ```

   `README.md` states the round's purpose, then the board rules of [docs/agents.md](../../docs/agents.md) "The
   message board" and "Working in one shared checkout", and the friction format above. `INDEX.md` starts as one
   header line.
3. **Write the user's request into `inbox/`** as `<stamp>-USER-request.md`, verbatim, marked as transcribed by
   you. Every later word of the user's that changes the round goes there too, before you act on it.
4. **Run PICK** (Stage 1) when the arguments give a component; when they give indices, PICK still checks each one
   (stub, file, callees) and assigns files, but chooses nothing.
5. **Assign each lane a fragment number** before any matcher starts: the next free number after the highest in
   `src/units/`, read as a number (`100-` sorts between `10-` and `11-`), one per lane in lane order (A 15, B 16). Two lanes that each take "the next free
   number" collide ([src/units/README.md](../../src/units/README.md) "Names"). A lane whose target lives in a file a
   landed unit already compiles takes no number: it extends that unit's fragment ("Landing a unit" item 2 there), and
   its brief names the fragment it extends. Two lanes may extend one unit that compiles unrelated classes' sources
   (unit 110), each with its own source and its own paragraph of the fragment: the pick names the pair, and the landing
   takes both hunks.
6. **Create one worktree per lane**, from the urna checkout's root, branch `decomp/<lane>` from `main`, as a
   sibling directory of the checkout:

   ```sh
   LANE=ecourna-a                                    # one name per lane
   W="$(cd .. && pwd)/urna-worktrees/$LANE"
   git worktree add -b "decomp/$LANE" "$W" main
   # tracked files: copy the checkout's mtimes, or the first link recompiles everything (docs/agents.md)
   git ls-files -z | while IFS= read -r -d '' f; do touch -h -r "$f" "$W/$f"; done
   # every ignored input (build/out, build/dump, build/probe/target.fns.jsonl, third_party/*, target/fs,
   # the node_modules of asmlift-wasm and its packages), cloned with its timestamps
   git ls-files -z --others --ignored --exclude-standard --directory | while IFS= read -r -d '' p; do
     p=${p%/}
     case "$p" in *.DS_Store|*__pycache__) continue ;; esac
     [ -e "$W/$p" ] && continue                      # already inside a directory cloned above
     mkdir -p "$W/$(dirname "$p")"
     cp -cpR "$p" "$W/$p"                            # APFS clone; on Linux: cp -a --reflink=auto
   done
   [ -d "$W/build/out/verify" ] && mv "$W/build/out/verify" "$W/build/out/verify-cloned"   # another stage's scratch
   make -n -C "$W/src" link                          # must print: Nothing to be done for `link'
   ```

   It takes about a minute, and the clones share disk blocks with the checkout (its `build/out/` alone is
   gigabytes). Anything but `Nothing to be done` means the lane would rebuild from scratch: find out why before
   launching its matcher. Do not launch an agent into a worktree another agent is using.

   Cut a lane only while no LAND holds `main`. During a landing the checkout holds a merge in progress and a
   `build/out/` built from it, so step 1's two checks fail, and the clone would copy that state into the lane. Cut
   the next lanes between batches, from the commit the batch's result post names, once step 1's checks pass on it.
   A lane that already has commits (a branch fetched on another machine) is not cut this way, since `git worktree
   add -b` starts it at `main`: use `tools/round/build-at.sh <the branch's commit> <dir>`, which touches the files
   that differ so make rebuilds what depends on them, then `git -C <dir> switch -c decomp/<lane>`.

   A lane that builds on another lane's unlanded work is cut the same way, from that lane's commit once its verdict is
   CONFIRMED, and lands after it. Its base is that commit: the brief names it, and the commands written with
   `git merge-base main HEAD` take it literally, since that command then gives the older commit `main` shares. A lane
   that needs two or more lanes' unlanded work has no such base: it is cut from `main` once they have landed, in a later
   batch, and until then the pick lists its rows with the lanes they wait for.

---

## Stage 1: PICK (one agent, read-only)

Brief: the rules above, the board path, the arguments and the lane names. It changes no tracked file. It returns,
and posts as `rounds/<stamp>-<ROUND>-PICK-pick.md`, one target per lane with its evidence, and its frictions.

How to pick, from [how-to-decompile.md](../../docs/how-to-decompile.md) step 1:

- **The pool.** A function not decompiled yet has a stub in its tree, so start from the stubs and join the scan
  (`src/ecourna` for `ecourna`; `src/uenux2` for `vota`, `comum`, `api`, `simulador`, `vota-web`; `src/asn1` for
  `ASN1` and `asn1-modules`; all three for `tse`). Go by the tree that holds the stub, not by the `group` column
  (step 1 explains why they differ):

  ```sh
  python3 -I -B tools/round/pick_pool.py src/ecourna    # src/uenux2, src/asn1, or --tse; index, verdict, size, group, stub
  python3 -I -B tools/round/pick_pool.py --differs      # the TSE differs rows (how-to step 1)
  ```

  The first lists the stubs of 40 to 600 B, smallest first; a pick by class reads them all (`--min 0 --max 1000000`
  gives 1511 rows for `--tse` at 4487d6b, against 757). The `differs` rows of TSE code (the second) are the other pool:
  a body of ours exists and the work is fixing its C++. It lists the rows a batch still landing matches too; drop them
  with the board's in-flight list, `python3 -I -B tools/round/pick_pool.py --differs | cut -f1 | sort | comm -23 -
  <(sort <board>/shared/inflight-indices.txt)`. The static destructors of a class's statics are in no pool:
  a 10-B or 12-B body with no stub and no reader but the table, whose `.bss` address names its singleton, so it goes
  to the lane of that class. A third pool is in neither listing: the pending members of landed units. They have no
  stub; a trap `splat-symbols` names by its slot reads `differs` with the `-pending.o` as its object, and one no
  evidence names (binaryen merged it with other traps) reads `no-candidate` with object `-` (how-to step 9), so the
  scan's object column misses those. The class's vtable and layout are already on `main`, so a whole
  class can be taken at once. Each `src/units/*-pending.cpp`
  header names its members and what each waits for (`ls src/units/*-pending.cpp`). The scan's
  `unresolved` rows are in neither (`tools/round/pick_pool.py`'s docstring has the command that lists the TSE ones):
  a body of ours calls something no target function is named for, which the row's `detail` names, and how-to step 1
  tells the three cases apart. Across both, the rows whose frame differs from the target's have a route of their own
  (a helper, a merged or an aligned slot, a larger object): `docs/reference/facts/codegen.md` §C5, "Finding the rows
  whose frame differs", lists every written TSE row whose frame setups differ (9 at ea98137f, 4 s), which `score`
  counts as one operand row.

  A row with no stub and no class of its own (group `app`, `libc++` or `unknown`, or a lambda's `__func` slot) is no
  target by itself: it goes to the lane of its unmatched callers when they are all in one lane, a `__func` slot to the
  lane of a function that builds it (below), and is counted there; otherwise it is in no lane, unless a lead needs it
  as a callee (a call, an `invoke_*` slot, a function pointer it passes or stores): then it goes to one of those
  leads' lanes, the pick says which, and the other lanes that need it wait for that one or measure with a copy they
  drop at the landing (11975, slot 1632, which 11946 and 12110 pass). The executable TU's
  copies (`-Oz`, landing pads, no stub: 388, 518, 679, 1091) are picked like any other row: their source is that TU
  (unit 170) or a tree root at `VOTA_WEB_CXXFLAGS`, and a copy whose shape depends on a reader (a destructor's kept
  `this`, `docs/reference/facts/reading.md` §R2) needs that reader in the link.

  A batch still landing moves the pool of a pick whose base is before it. Count as resolved what its branches match or
  name over their own merge base with the pick's base (`git show <branch>:splat/symbol_addrs.txt` against `git show
  "$(git merge-base <base> <branch>)":splat/symbol_addrs.txt`; for a branch on the other machine, the board's in-flight
  list and the lane's result post), less the names the pick's base removed since that merge base: those are the base's
  decision, not the branch's gain (11157, whose stand-in calls the base removed by the user's decision). The rows they
  write or trap without matching (their diff removes
  the row's stub, or adds the member to a `-pending.cpp`) are out of the pool until they land, and the pick says which
  lane would take them after; a row a pending comment only mentions is not taken. A member a lane's result reports as
  not attempted, whose row its branch leaves as it was, is in the pool again once that result is posted, unless the
  round's in-flight list keeps it: then the pick lists the rows that need it as waiting for its release.

  A lane that matched nothing is parked: its branch is kept, and its fragment there is the record of the forms it
  tried. A pick that gives a parked row again reads that fragment (`git show <branch>:src/units/<n>.mk`) and names in
  the brief a route it did not try. A branch on the other machine is read there (`ssh <host> "git -C <checkout> show
  <branch>:src/units/<n>.mk"`, [docs/agents.md](../../docs/agents.md) "Two machines") or the coordinator copies the
  committed fragment into `shared/`; a board archive of an earlier draft is no record, so a parked lane's result names
  every form it tried. A `differs` row whose fragment says it waits for an order, a flag or a rule is re-read against
  the current docs: a rule changed since can have opened its route (10210's note waited for "renumbering landed
  units", which the units README's list moves now allow).

  A hub that holds many functions with no target index of their own over several files (12098) can be prepared: a pick
  may give lanes before the hub's that write those functions in their real files (how-to step 5, "A body with no
  index"), expecting no match. Such a branch is kept as a prepared branch, not a parked one; the coordinator merges
  the prepared branches into the base of the hub's lane, which the pick that plans them names, and their code lands
  with that lane's match, or with a match of their own lane.

  Claude Code replaces a `$` followed by a digit in this file with one of the command's argument words before the
  session reads it (a dollar and 0 become the first word; Claude Code's skills docs, "Available string substitutions"), fenced code
  included, so the file holds no such text, and a query belongs in a script, not here:
  `/usr/bin/grep -nE '\$[0-9]' .claude/commands/decompile-functions.md` must print nothing.
- **Every callee must resolve.** Read each candidate with `pnpm wasm fn` and lift it with `pnpm wasm lift … --check`
  (how-to steps 2 and 3). `fn` does not name the function behind an `invoke_*` table slot; the lift does
  (`/* &fN */`). Neither names a function pointer passed as a plain argument (a thread routine, a callback) or stored
  (a `std::function` built from a function pointer holds the slot beside its `__func` vptr: 12040 stores 1529, which
  is 12039): `fn` lists its slot among the strings referenced, and the element section names it
  (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[4527\]'` prints
  `- elem[4527] = ref.func:10255`, the routine 1684 passes to `IThreadImpl::Create`). A slot can also lie inside a
  literal, which `fn` lists as a tail, `(+N into M)`, and an integer can equal a slot: read each word by its use
  (`docs/reference/facts/reading.md` §R23). Count a slot as a callee, and put it
  in the same lane. A callee resolves when it is matched (`/usr/bin/grep -E '^N ' splat/matched.txt` prints a line) or
  named (`/usr/bin/grep -F '= func:N;' splat/symbol_addrs.txt` prints one). A callee the lane writes, which the link
  keeps, resolves only when its own callees do: wasm-ld stops on an undefined symbol that live code calls. So follow
  every callee the lane writes down to code our link defines, and count that closure as the lane's core: 5359 (47 B)
  calls 5360 (9613 B), so 11620's lane writes both. A large function at the bottom of it is written, plausibly at
  least, or the lead stays pending (`src/units/README.md` "Pending members"). A slot of a lambda's
  `std::__function::__func` vtable is written with the function that builds the lambda, the one whose body stores that
  vtable's vptr (`pnpm wasm fn` of it shows the `i32.const`): count that builder as the slot's callee, since the
  closure type is local to it. binaryen merges identical slot bodies, so one row can be a slot of several `__func`
  vtables (`ledger/vtables.json` lists it in each, 2881 in four): any one of their builders gives it a body of ours,
  so it waits for the first of them, not for all. A call of the row itself, or a cycle of rows the lane writes
  together, blocks nothing:
  the name comes from a caller's vote once the caller matches (how-to step 1, "The row's own symbol"), so the row goes
  in its caller's lane. A function whose callees are unnamed
  needs those first, with two kinds of exception. One is a callee the candidate's own TU instantiates, which step 8
  names by `call` evidence once the candidate is paired (`docs/reference/splat.md` §2). Its signs: no stub, owner `-`,
  a body of library calls shaped like a header member (183 is `std::filesystem::path::operator/=`). A body that also
  fits a TSE accessor (1555, a copy of the `std::string` at `this`+0, matched as `std::filesystem::path::string()`) is
  told by the type its callers' `this` has, read from their other calls on that object. The other is a library
  function (its owner a library in `ledger/functions.tsv`) with no line in `build/out/wasm-map/vota_web/names.tsv`:
  our link holds it inlined into the one caller it gives it (how-to step 1, "Inlined into the one caller our link
  gives it"), or no object pulls it yet. The candidate's call gives it its second call site, or pulls the archive
  member in, and the toolchain alone decides its match: 6222, libc++abi's `__cxa_demangle`, inlined into 212 until
  5521 was written. Read its target callers (`pnpm wasm fn <target> <index>`) and the link's objects for its symbol,
  not `names.tsv` alone; the pick lists it with the lane as a library row. A merge thunk of a stub-less
  TSE body is work, not one (412). A `CBaseError<E, SErrorLimits{…}>`
  constructor is one, even when the target's is a binaryen merge thunk: 1889, `push f710(p0, p1, p2, p3, 1528452)`,
  is named `evidence:call by:1684,10250`. A name only the candidate's own call votes for is self-voted, and the match
  holds once another match calls the same function (splat.md §3): 10250 matched when 1684 landed. It holds only where
  our link merges the same bodies binaryen merged in the target. 2294 is the body of five such constructors (its
  callers 170, 210, 235, 255 and 331, `pnpm wasm fn ../target/vota_web_wasm.wasm 2294`; 170's is
  `CBaseError<comum::EUeComumDadosError, {7800, 8600}>`, by the vptr 1528096 it passes): it matched with 210, 235, 255
  and 331, whose objects give our link the same merge, and 170 still differs (`splat/scan.tsv`'s rows at ea98137f). A
  pick past such a body before any of its callers matches is a measurement, and the pick post says so. The name that
  resolves can be
  a *twin*'s, which a caller of another instantiation with the same body still resolves to (how-to step 3, "A callee
  can be a twin", 760 under 11361). A callee written and `differs` resolves for a lane that writes two of its callers
  from two target bodies that are pairs themselves (anchored by a record or vptr, or named by an anchored caller):
  their `call` votes name it, and the two hold each other (`docs/reference/splat.md` §3); the pick names the two, and
  they land together. A caller with no record, vptr or census pair votes for nothing (1255 over 502).
- **And every data operand.** A row with a body of ours already (the scan's `ours`, or a symbol of its name in
  `names.tsv` when it reads `no-candidate`) also needs each data object it reads: from `asmlift-wasm/`, `pnpm wasm
  splat-remap <target> <plain> sym:<its symbol> --against <row>` prints no `no target symbol` for it. Such an object
  resolves when a matched or lane-written reader votes for it, or a hand line names it (how-to step 9); else the row
  waits with it (1558 and 3923 on `__format_spec`'s 2-byte field sets). The same remap lists our calls and table slots
  that have no target function (`has no target function`), which the callee bullet, reading the target's call graph,
  does not see: read each against the target's call at that offset (how-to step 1, "The third verdict") before
  counting the row as ready. The remap reads the symbol file alone, so a callee only `splat/matched.txt` names prints
  so too and is resolved: look its symbol up in `splat/scan.tsv` first (3771's three calls of 208,
  `ASN1::trace_invalid`, `match` with no symbol-file line; `docs/reference/facts/workflow.md` §W28). A row with no
  body of ours is read from its target piece:
  - its `.bss` operands, the constants past the target's last data segment
    (`wasm-objdump -x -j Data target/vota_web_wasm.wasm | /usr/bin/grep -E 'segment\[' | tail -1` ends at 1811674), each
    grepped in the pieces (`/usr/bin/grep -rlE 'i32\.const <addr>($|[^0-9])' build/out/splat/pieces/asm`). An object
    that only the row reads, with no static destructor or other reader, rules the row out (`docs/reference/splat.md` §3,
    12134's buffers). An address only the row loads can be a field of a named object: look for a
    `splat/symbol_addrs.txt` line whose address and `size:` cover it before calling it lone (11620's 1838592 is
    `CPath::s_pathFlash` + 16). An object the row and its exit destructor alone read is named by the row's own vote,
    which an anchor or a `vtable` pair casts only when the two bodies are the same opcodes (`docs/reference/splat.md`
    §2): the row, the object and the destructor land together, and a row written one remainder off stays `unresolved` on
    it (7160). The row's unit's pending notes are the other place to read first;
  - its literals' tails. Most `(+N into M)` lines `pnpm wasm fn` lists are integers in the data range (a size, a
    multiple of an element's size: §R23) or a tail's start, which re-points by content. A loaded end
    pointer (`M + len` among its operands, `len` from
    `ledger/strings.tsv`) waits for the host's writer when no code of our link holds the host and its text is not in
    our plain wasm (11253, 11254 and 8168 waited so for 10425's `"-{:02}-{:02}"`, 8963). One whose host our link holds
    can still read `string tail occurs N times` (2725), which only the written row's scan shows: list it as a risk.
- **And every row has a keeper.** A row lands only if our link keeps it: a caller, a store of its vtable's vptr, or
  a function that passes its table slot, each matched, written, in the lane, or a roots stand-in (an external
  function; a vtable through a sink). A template copy the caller's TU instantiates, or a helper with internal linkage
  (its record names `(anonymous namespace)::`, which no roots TU can name), whose callers are all unwritten waits for
  them, under their lane. A library's own instance (libc++'s `extern template` copies) is a library function: a roots
  stand-in for its unwritten caller brings it (`docs/reference/facts/placing.md` §P1). A function passed by its slot
  is kept by the passer: the slot's `i32.const` in the passer's
  piece (`/usr/bin/grep -rlE 'i32\.const <slot>($|[^0-9])' build/out/splat/pieces/asm`), checked in the element
  section and used as a slot (an `invoke_*` first argument, a `call_indirect` operand, a stored function pointer the
  code calls), since an integer can equal a slot: 11852 stores `2594` beside `2582` as a value and keeps no 11423, whose
  keeper is its class's vptr store (`docs/reference/facts/reading.md` §R20), and a size before `call 137` or a stored
  word whose slot's function does not fit the class is no slot either (§R23). A
  static's exit destructor (10 to 14 B,
  its only reference its table slot, which `__cxa_atexit` gets at run time) has no keeper a search sees:
  `wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'ref\.func:10682$'` prints `elem[3848]`, and
  no piece holds `i32.const 3848`. It lands with the lane whose match reads the static, and counts there.
- **A flag not decided.** The user decided three: uenux2 at `-std=c++23` and the executable TU at its own rule
  (`VOTA_WEB_CXXFLAGS`), both in `src/Makefile` (`docs/reference/facts/levels.md` §V3, §V1), and strict aliasing by
  directory and file in uenux2, landed as the directories and files `UENUX2_TBAA_DIRS` lists and the files
  `UENUX2_NOTBAA_FILES` keeps out of them (`docs/reference/facts/app-flags.md` §F6): a lane reports a measurement that
  would move a directory or a file, and does not move it, and the user decides each file. A measurement of several
  forms or flags in one worktree removes the object before each make and reads one compile line in its log
  (`docs/reference/facts/workflow.md` §W26: make 3.81 compares whole seconds). Every other flag stays the
  user's to decide: a member whose body needs one (a no-stub row goes by its callers' tree, not its group) is listed
  as waiting for that decision, not as expected.
- **The stub may sit over code we have**: search our sources for the class before choosing (step 1).
- **The name and the file**: from the records, the vtable slot, `ledger/vtables.json` and `ledger/classes.json`;
  for an `unplaced.cpp` stub, the file rules of how-to step 3.
- **Lanes must not overlap.** A lane takes a whole class or family where it can: its vtable, its file, its pending
  members and its statics' destructors. Different classes and different files, so no two lanes edit one file or emit
  one vtable. A member that loads another file's constant (a font, a table) holds that file's code, inlined: list the
  readers of each candidate's data operands (the grep above) and put the members that read one file's constants in
  the lane that owns that file (eleven state classes read `ctelasvota.cpp`'s fonts). When a member's two ties name two
  lanes (it holds one lane's file's code inlined and calls a callee another lane writes), it goes to the lane of the
  callee, as a member that waits for the file owner's landing, and the pick says so (11884 holds `cinputmenufield.cpp`'s
  two `SetFormatString` and calls 5953). A stand-in in another unit's `-roots.cpp` that stands for a lane's lead is
  not that lane's file: the lane measures with it in place and lists in its result the stand-ins that stand for its
  lead, and LAND removes them once the lead is in the link (Stage 4). A header
  several lanes need (a shared enum, a type a record names) is listed in the pick post, with one copy on the board's
  `shared/` that every lane takes byte for byte.

Check the pick yourself before launching the matchers: each target's stub is where the post says, and no two lanes
share a file.

---

## Stage 2: MATCH (one agent per lane)

Brief: the rules above, the board path, the lane's handle (`<ROUND>-A`), the absolute worktree path and branch,
the target index (and any stretch target), its fragment number, and the PICK post's evidence **as hypotheses**.

The matcher works only in its worktree and follows [how-to-decompile.md](../../docs/how-to-decompile.md) steps 1
to 10 as written, including steps 6 to 10 in the worktree: link, census, symbols, match, the splat build, the
checks, and one commit on its branch. It never touches the urna checkout's `main` and never merges. A fix `main` gained
since the cut that the lane needs to build (a link recipe) it may take for the build only, and so may its VERIFY:
`git cherry-pick --no-commit <fix>`, undone as [docs/agents.md](../../docs/agents.md) "House rules" says, keeping
the file's old mtime with `touch -r` both ways, or every object that names it recompiles.

It returns, and posts as a `rounds/` result: the verdict (matched, or not matchable yet and why), the commit(s), the
splat build's sha256 and match count, the matches added and lost against the branch's base, the files it owns,
its stretch target's state, and the number of friction posts. A target that cannot be matched yet is a result:
post the blocker as a `facts/` post (which callee, which codegen) and leave it pending. Nothing lands from a lane
without a match: its branch is kept, and code that moves no row into `match` (a member moved out of a trap, written
code with no index) lands with a match of its own lane or of the lane whose base takes the branch (Stage 1). Its
measurements still belong in the fragments: its result names, per fragment, the note lines to add (a spent route on a
row's note, a route that matched a twin row), and the next landing that touches that fragment writes them in its
comments commit (how-to step 5, "A written body that does not match yet"). Nor does
anything land from a lane whose change costs a row its base matches, unless the user decides that loss lands: it
posts the loss as a `facts/` post, and how-to step 9 says what that post holds, on which branch alone the change may be
committed, and how a loss the user lands is committed.

Count the matches by target index, not by line. `git diff main -- splat/matched.txt` shows the added lines, but a
line removed there is not always a lost match: a twin whose surviving name moved is removed under its old symbol and
added back under the new one. The lost matches are the indices the branch's base matches and the branch does not,
which the `comm` of [how-to-decompile.md](../../docs/how-to-decompile.md) step 10 ("A twin whose name moved") prints
when it is run against `git show "$(git merge-base main HEAD)":splat/matched.txt`. Against a `main` that moved since
the branch started, the same `comm` also prints every match `main` gained since, which are not the lane's to lose.

---

## Stage 3: VERIFY (one agent per lane, independent)

A different agent from the matcher, given only: the rules above, the board path, the worktree, the branch, the
commit range, the target index and the match line. Not the matcher's transcript. Its job is to refute the match.
It changes no tracked file, works in scratch under `build/out/verify/` (ignored), and posts a verdict,
**CONFIRMED** or **REFUTED** with the check that failed. It judges by the docs of the branch's base, and where `main`
has changed them since (`git diff "$(git merge-base main HEAD)" main -- docs src/README.md src/units/README.md`), by
`main`'s too, since the branch lands under them; the verdict says which text it read. Below, `<base>` is the commit the
branch started from, `git merge-base main HEAD` for a branch cut from `main`:

1. **Fresh objects.** A `build/out/verify/` that exists before your stage is another stage's (a clone of the
   checkout's, or a verify of the lane the worktree was cut from): move it aside by name first. Move aside, by name
   (into `build/out/verify/old-objs/`), every object the lane built: `find build/out/app -name '*.o' -newer .git`
   lists them, since the worktree's `.git` file dates from its creation and the cloned objects keep the checkout's
   older mtimes. Objects outside `build/out/app/` rebuild too: a fragment's rule can make library objects depend on
   it (an edit of fragment 06, a comment included, recompiles the 13 zlib objects under `build/out/zlib/O3pic/`), so
   `make -n -C src link | /usr/bin/grep -oE ' -o [^ ]+\.o'` before the build lists every object it compiles, and
   each is copied and compared the same way. A header the lane added or edited rebuilds every object of
   its tree and the companions that name its directory, not only the unit's (`src/units/README.md` "What a fragment
   holds" item 3; `docs/reference/facts/workflow.md` §W15), and `-newer <header>` misses an object built before that
   header's last edit. Compile them with the object list, `TMPDIR=/tmp make -C src -j<n> $(make -s -C src
   print-LINK_OBJS)` (left to `splat`, they compile one at a time: [docs/agents.md](../../docs/agents.md) "Shared build
   outputs"), check that it compiled exactly those objects, run `TMPDIR=/tmp make -C src splat` with no `-j`, and `cmp`
   each object with its old copy, looping over that list, never over `old-objs/`. A stale object means the source edits
   never rebuilt. An object that does not come back is a deleted file's: `cmp` is owed for the objects the link names.
2. **The splat build** prints the target's sha256, and no index the branch's base matches is lost (how-to step 10's
   `comm`, against `<base>`). A
   line removed and its index added back under another symbol is a twin rename: check that the old symbol is gone
   from the link (`build/out/wasm-map/vota_web/names.tsv`) and the new one is a byte-identical body in the final link
   (two D0s that pass different sizes to sized delete differ in their objects and are one function there), or the
   other alias of one constructor or destructor (how-to step 10). Compare the
   range's `splat/scan.tsv` with the base's on the index and verdict columns: only the lane's matches, and verdicts
   with a reason in the range, may move. The symbol of `unresolved` and `differs` rows among identical bodies, and
   some lines of the symbol file, change at every landing whatever the unit
   (`docs/reference/facts/splat.md` §S8 lists them and the commands that separate them out).
3. **The blanked-target check**, as [docs/reference/splat.md](../../docs/reference/splat.md) "Reviewing a match"
   describes: for each target index the lane matched, from `asmlift-wasm/`,
   `pnpm --silent wasm splat-review ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm <index> -o ../build/out/verify/<index>`.
   It blanks the matched piece in a copy of the split, assembles it with our body two ways, and prints whether each
   gives the target's sha256. The match's own bytes are the gate: the command exits non-zero only when they fail.
   Report the preferred-readings way too, but a match whose operands need the target's choice (splat.md §3) fails it
   legitimately, and the command lists each reading the target body picked. Say which way gave which result.
4. **The checks**: `make -C src stubs-check`, `python3 -I -B tools/round/status.py --check`,
   `python3 -I -B tools/round/stubs.py --check`, `python3 -I -B tools/round/check_encoding.py`,
   `TMPDIR=/tmp make -C src check-srcloc` after `TMPDIR=/tmp make -C src link-map` on the last link (an older map
   reads other objects' linkonce copies as wrong records: how-to step 10), with no wrong record of a matched function
   (its records that only
   unmatched functions load are the base's unless they sit in an object the range rebuilds or on a line of a file it
   edits: compare the list per object, [docs/reference/facts/tool-traps.md](../../docs/reference/facts/tool-traps.md)
   §X7), and from `asmlift-wasm/` `TMPDIR=/tmp pnpm test:bench`. The last one fails when the lane compiles an object
   with a flag set that no setup of `asmlift-wasm/benchmark/dataset/setups.json` has (how-to step 4, "When only a flag
   closes the gap"); every other check passes on such a lane. Run `TMPDIR=/tmp pnpm test` too, alone, after every
   build in the worktree has finished: it skips its real-link tests while `build/out/` is being rewritten and still
   exits 0, so read its `skipped` count, and a failure the base has as well is not the lane's.
5. **Generated files are what the generators write.** Re-running `make -C src splat-symbols` leaves
   `git status` clean. A rescan changes `splat/scan.tsv` in two ways only: the `source` column, to `symbol`, of a new
   match the scan found by content or by the census's pair and of a match line step 9 renamed to a twin, and the
   `detail` of a new match the first scan found after trying another candidate. A new match step 8 already named is
   `symbol` from the start, and the rescan leaves its line alone (`docs/reference/splat.md` "Reviewing a match").
   Restore anything a re-run rewrote with `git checkout -- <file>`, and report it.
6. **The source**, against rules 3 to 5: the real mangled name and where its evidence comes from (a name no record,
   slot or RTTI gives is marked as chosen), real classes, no scaffolding in the landed TSE files, Latin-1, throws on
   their record lines, and roots and pending files in the shapes `src/units/README.md` sanctions. A match compiled in
   a `-roots.o` or `-pending.o`, and a census pair with a roots stand-in, are checked as
   [docs/reference/splat.md](../../docs/reference/splat.md) "Reviewing a match" says, and so is each hand line the
   range adds to the symbol file: removed, scanned twice beside a control, then built.

A REFUTED lane does not land. A refutation on comment or doc text alone, every check passing, you fix yourself, with
the verdict's replacement text, as a commit on the lane's branch, and say so in the landing's brief and your report.
Send any other finding back to the lane's matcher once, as a new MATCH run, then to a new VERIFY, which is narrow: the
refuted points and the range since the commit the first verdict judged, with the first verdict's other checks
standing. A second refutation on text alone you fix the same way; any other goes to the user.

---

## Stage 4: LAND (one agent per batch, on `main`)

Brief: the rules above, the board path, the batch's CONFIRMED lanes in landing order, each with the commit its verdict
confirmed, and the match count and commit of `main` before the batch. Land in batches as the verdicts arrive: each
batch is a LAND stage of its own, and it touches no lane its brief does not name. It posts a `rounds/` claim of `main`
first, naming the lanes, their commits and the worktrees it will remove, and keeps its logs under `build/out/land/`. A
batch that meets a lost match stops before committing that merge and posts it. A real-link test case that reads a
number or a premise the merge moved is no toolkit fix: it changes to read the rule in the merge commit (step 2). A
toolkit fix the merge needs is a commit of its own on `main`, with a VERIFY of its own before the push, and the batch
then goes on from there: a merge already staged when the need shows is aborted (`git merge --abort`, everything staged
first: `docs/reference/facts/workflow.md` §W22), the fix committed on `main`, and the lane merged again. A row lost to
one link's data layout, the cause shown (how-to step 9's four cases), may wait for the next lane of the batch: land
that lane first, retry, stop if the row is still out, and say so at the top of the result.
First compare the objects around it with the target's data order: a residue that comes from an object's place on the
link line, which the target's data put elsewhere, is fixed by that place
(`docs/reference/facts/link-order.md` §L3), not waited out.

The commit to land is the one the verdict confirmed. A lane branch's tip can differ from it: a pause can leave the
worktree on another branch (`wip/<lane>`), and the lane branch then points at an older commit. Check
`git -C <worktree> rev-parse HEAD` against the verdict, merge by commit id, and move no branch. A WIP commit never
lands ("Pausing and resuming" below).

1. **The first lane** fast-forwards when `main` has not moved: `git merge --ff-only <commit>`. Its matches were
   measured on this `main`, so nothing needs to be rerun. When `main` moved only by a merge commit whose tree is the
   lane's base (a pull request's merge: `git diff --quiet <base> main` exits 0), `--ff-only` fails: merge with
   `git merge --no-ff --no-commit <commit>`. The merge's tree is then the lane's tip (`git diff --cached --stat
   <commit>` prints nothing), so nothing is regenerated: link, run the splat build and the checks, and commit.
2. **Each later lane** merges with `git merge --no-ff --no-commit <commit>` and resolves the conflicts as
   [how-to-decompile.md](../../docs/how-to-decompile.md) step 10 "Landing onto a moved main" says, then runs steps 6
   to 10 again on the merge (link, census, symbols, match, build, checks) and commits it all as the merge commit. The
   checks are step 3's, `pnpm test` among them (about 200 s on the Mac mini), run on each merge, so that a case that
   reads a number the merge moved changes in that merge commit (`docs/reference/facts/workflow.md` §W12). Every
   check passes at that commit but one case: a lane that adds or retires a benchmark setup leaves the merge failing
   `pnpm test:bench` until the re-selection, a commit of its own after it (`asmlift-wasm/benchmark/README.md`
   "Re-selecting"), and the merge's message says so. A
   merge commit takes no pathspec (`docs/reference/facts/workflow.md` §W18): stage everything, check that `git status
   --short` shows no unstaged or untracked line, and commit with a bare `git commit -F -`. That is safe only because
   LAND owns the whole checkout. Do not pick generated lines by hand. How-to step 10 has the rest: no `make -C src
   stubs` on the merge before step 9, each index once in `splat/matched.txt`, both sides' hand edits with one line per
   name, and which side of a twin's line to keep, with the check after step 9. A stand-in, or a call of one, whose
   every target caller is now in the link goes in the merge, or in a code commit of its own right after the batch's
   merges that names each removal and its link, and a roots file with its last stand-in; one whose callers
   landed in part keeps one call per caller still waiting, its comment saying which, unless a link without it moves
   no row. Removals that go for one reason share one variant link (`src/units/README.md` "Companion files", "Finding the
   idle ones", which says how to find them call by call and over the whole tip). One idle since before the batch is
   named in the result and goes in a commit of its own.
3. **Check the landing**: `TMPDIR=/tmp make -C src splat` prints sha256
   `8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2`, the match count is the old count plus every
   lane's matches, and no index of the old `main` is lost (how-to step 10's `comm`, with `<old main>` for `main`). The
   matches `docs/reference/facts/splat.md` §S10 lists are held up by the link, not by a source: run its check at every
   merge, and stop if one left `match`. A merged link can add matches no lane had: a name that moved, a vtable the
   merged link places by content, or a body the scan pairs by content once the lanes' matches leave one unmatched target body equal
   to it (`content` in the scan's `source` column). Such an extra, and any whose readings say `address same-content`
   or `table slot copy`, can carry the name of another function of the same content. Check its name against the
   functions around its index in `splat/matched.txt` and the data that point at it, and correct the line by hand when
   they disagree (§S11; how-to step 9). List the extras, with why, as a `facts/` post. Then
   run the checks of VERIFY step 4, and from `asmlift-wasm/` `pnpm test`, `pnpm typecheck` and `pnpm test:bench`.
4. **Clean up**, which is not optional: no worktree outlives its lane. Read the inbox again first. Then, for each lane
   of the batch and each lane dropped since the last batch:
   - copy what the board cites to its `shared/from-<worktree>/`, and check that nothing is lost, as
     [docs/agents.md](../../docs/agents.md) "Worktrees" says, since `git worktree remove` deletes the ignored `build/out/`;
   - run `git worktree remove <worktree>`.

   Keep the branches. Never push. The result post quotes `git worktree list`. A worktree on the other machine of a
   two-machine round is removed there.

---

## Stage 5: DOCS (every second round, in worktrees of its own)

It runs alongside the next round, and no lane waits for it: its docs land on `main` while lanes run, and each lane is
judged by its base's docs and landed under `main`'s ([docs/agents.md](../../docs/agents.md) "Working in one shared
checkout"). Brief: the rules above, the board paths, the docs it may
edit (rule 1's list, the help text of the tools they describe, and this command file), and the cut-off: every
`board/friction/` post since the last DOCS stage. It reads
each one, every post that corrects it, and the verdicts that judged a doc question, and changes the docs so the next
contributor does not hit it. It runs every command it writes into a doc, as written, before committing. A pass that
changes a rule greps the fragments for the old rule's wording and lists the notes to reword as a follow-up (fragments
are code comments, a landing's to change).
Facts that an edited doc depends on move into `docs/reference/facts/` (no doc cites the board). A fix that needs code
(a Makefile rule, a tool option) is not made here: it is listed as a follow-up for the user. It checks that the
relative links of every edited doc resolve and that `status.py --check`, `stubs.py --check` and
`check_encoding.py` still pass, commits on a `docs/…` branch of its own worktree, and posts its result: the commits,
and for each friction post the doc change that answers it, or why none does.

With many posts, split the docs in two parts by file, one agent each in its own worktree from the same commit, and
give each post to the part whose file it names first, and each part a block of the follow-up numbers, so their two lists
do not collide. A third agent then merges the two branches, gives each fact one
home, and re-runs what the two halves disagree on. Its branch is what the coordinator opens a pull request for, and
the DOCS worktrees are removed as Stage 4 step 4 removes a lane's, the branches kept.

Its result states its cut-off, and it continues the follow-up list of the DOCS stage before it, with what landed marked
done.

---

## Pausing and resuming

When the user stops the round, stop launching agents. Each running agent commits what it has as one WIP commit on
its lane branch (never `git stash`), or on a `wip/<lane>` branch, and posts where it stands. A WIP commit never lands
and is no verdict's range. To resume, continue the same agent where it can be continued (its context is intact), or
brief a new one with the lane's brief and the post of where it stood. Either way it reads the inbox first. It turns
the WIP commit into its result commit (`git commit --amend`) or resets its branch to its base and commits again, and
says in its claim when it rebased onto a newer `main`. Its result names the commit, which VERIFY and LAND then use by
id (Stage 4).

One coordinator owns `main` at a time. To hand a round to a coordinator on the other machine, the owner writes one
`HANDBACK:` line, and the next owner checks Stage 0 step 1 before it starts anything
([docs/agents.md](../../docs/agents.md) "Two machines").

---

## What to report

When the round ends, or when the user stops it (then stop launching agents, let running ones finish, and report
what exists), tell the user:

- **per target**: the verdict (matched, pending and why, refuted), the VERIFY verdict and which blanked-target
  ways it ran, and the lane's commits;
- **the landing**: how each lane merged (fast-forward or merge commit), the conflicts and how each was resolved,
  the regeneration and how long the link took, the splat build's sha256, the match count before and after, every
  new match including those no lane had, and that none was lost;
- **the checks** and their results;
- **the friction log**: how many posts, and the DOCS commit; the follow-ups that need code;
- **what is left**: the worktrees removed, with `git worktree list` quoted, which shows only the urna checkout at the
  round's end; the branches kept; that nothing was pushed; and the board's path.

---

## Example: `2 ecourna`

- **PICK** starts from the ecourna stubs (`pick_pool.py src/ecourna`). Of the small ones, those whose callees all
  resolve are mostly template instantiations and the `CConversor*` ASN.1 converter hooks. It gives lane A 9132
  `CConversorHorariosUrna::DoDeconverte` (134 B) and lane B 9131 `CConversorMunicipioZona::DoConverte` (54 B), with
  9130, B's sibling slot, as B's stretch goal, and you assign the fragment numbers 15 and 16.
- **MATCH A** writes the `CHorariosUrna` data class (its out-of-line constructor gives the target's 32-byte frame)
  and the converter in `app/dados/asn/`, with a `-pending.cpp` for 9133 and a `-roots.cpp` for the vtable. Its
  scan also matches 9218 (`CConversorCabecalhoEntidade::DoDeconverte`), a body the lane did not write: the match
  found by content confirms a callee's name, which resolves another function. The lane reports both matches.
  **MATCH B** matches 9131. Its stretch goal 9130 stays pending: it needs constructor thunks that binaryen merged and
  that have no names yet, which the lane reports as a `facts/` post.
- **VERIFY** confirms both lanes, the blanked-target check included.
- **LAND** fast-forwards lane A and merges lane B. The merge conflicts in every generated file,
  and is resolved as how-to step 10 "Landing onto a moved main" says. After the
  regeneration the splat build prints the target's sha256 with every lane's matches plus 6122, a libc++ function
  that neither lane had: the merged link drops a self-voted vtable name, and the vtable is then placed by its
  content. No match is lost.
- **DOCS** answers each friction post with a doc change, and lists as follow-ups the fixes that need code (a
  Makefile rule, a tool command).
