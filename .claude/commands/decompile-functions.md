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
  a body of ours exists and the work is fixing its C++. The static destructors of a class's statics are in no pool:
  a 10-B or 12-B body with no stub and no reader but the table, whose `.bss` address names its singleton, so it goes
  to the lane of that class. A third pool is in neither listing: the pending members of landed units. They have no stub, each row is `no-candidate` or `differs` with
  the `-pending.o` as its object (how-to step 9), and the class's vtable and layout are already on `main`, so a whole
  class can be taken at once. Each `src/units/*-pending.cpp`
  header names its members and what each waits for (`ls src/units/*-pending.cpp`). The scan's
  `unresolved` rows are in neither (`tools/round/pick_pool.py`'s docstring has the command that lists the TSE ones):
  a body of ours calls something no target function is named for, which the row's `detail` names, and how-to step 1
  tells the three cases apart.

  A batch still landing moves the pool of a pick whose base is before it. Count as resolved what its branches match or
  name (`git show <branch>:splat/symbol_addrs.txt`). The rows they write or trap without matching (their diff removes
  the row's stub, or adds the member to a `-pending.cpp`) are out of the pool until they land, and the pick says which
  lane would take them after; a row a pending comment only mentions is not taken.

  Claude Code replaces a `$` followed by a digit in this file with one of the command's argument words before the
  session reads it (a dollar and 0 become the first word; Claude Code's skills docs, "Available string substitutions"), fenced code
  included, so the file holds no such text, and a query belongs in a script, not here:
  `/usr/bin/grep -nE '\$[0-9]' .claude/commands/decompile-functions.md` must print nothing.
- **Every callee must resolve.** Read each candidate with `pnpm wasm fn` and lift it with `pnpm wasm lift … --check`
  (how-to steps 2 and 3). `fn` does not name the function behind an `invoke_*` table slot; the lift does
  (`/* &fN */`). Neither names a function pointer passed as a plain argument (a thread routine, a callback): `fn`
  lists its slot among the strings referenced, and the element section names it
  (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[4527\]'` prints
  `- elem[4527] = ref.func:10255`, the routine 1684 passes to `IThreadImpl::Create`). Count it as a callee, and put it
  in the same lane. A callee resolves when it is matched (`/usr/bin/grep -E '^N ' splat/matched.txt` prints a line) or
  named (`/usr/bin/grep -F '= func:N;' splat/symbol_addrs.txt` prints one). A slot of a lambda's
  `std::__function::__func` vtable is written with the function that builds the lambda, the one whose body stores that
  vtable's vptr (`pnpm wasm fn` of it shows the `i32.const`): count that builder as the slot's callee, since the
  closure type is local to it. A call of the row itself, or a cycle of rows the lane writes together, blocks nothing:
  the name comes from a caller's vote once the caller matches (how-to step 1, "The row's own symbol"), so the row goes
  in its caller's lane. A function whose callees are unnamed
  needs those first, with one kind of exception: a callee the candidate's own TU instantiates, which step 8 names by
  `call` evidence once the candidate is paired (`docs/reference/splat.md` §2). Its signs: no stub, owner `-`, a body of
  library calls shaped like a header member (183 is `std::filesystem::path::operator/=`). A merge thunk of a stub-less
  TSE body is work, not one (412). A `CBaseError<E, SErrorLimits{…}>`
  constructor is one, even when the target's is a binaryen merge thunk: 1889, `push f710(p0, p1, p2, p3, 1528452)`,
  is named `evidence:call by:1684,10250`. A name only the candidate's own call votes for is self-voted, and the match
  holds once another match calls the same function (splat.md §3): 10250 matched when 1684 landed. It holds only where
  our link merges the same bodies binaryen merged in the target. 2294 is the body of five such constructors (its
  callers 170, 210, 235, 255 and 331, `pnpm wasm fn ../target/vota_web_wasm.wasm 2294`; 170's is
  `CBaseError<comum::EUeComumDadosError, {7800, 8600}>`, by the vptr 1528096 it passes), and no caller of those five
  is matched yet: a pick past one of them is a measurement, and the pick post says so. The name that resolves can be
  a *twin*'s: binaryen merges byte-identical bodies and keeps one
  name, so 760, matched as `vector<pair<unsigned long, unsigned long>>::push_back`, is also the `push_back` of
  another vector of an 8-byte element in the target: 11361, `CConversorSituacoesEleicoes`'s converter, which builds a
  `vector<CSituacoesEleicoes>`, calls 760 (`pnpm wasm fn ../target/vota_web_wasm.wasm 11361` shows `call 760`). A
  caller that uses that other instantiation still resolves when its body is the same (how-to step 3, "A callee can
  be a twin").
- **A flag not decided.** The user decided three: uenux2 at `-std=c++23` and the executable TU at its own rule
  (`VOTA_WEB_CXXFLAGS`), both in `src/Makefile` (`docs/reference/facts/levels.md` §V3, §V1), and strict aliasing per
  directory in uenux2, which lands as a split only when the split gains rows and loses no match (none has yet). Every
  other flag stays the user's to decide: a member whose body needs one (a no-stub row goes by its callers' tree, not
  its group) is listed as waiting for that decision, not as expected.
- **The stub may sit over code we have**: search our sources for the class before choosing (step 1).
- **The name and the file**: from the records, the vtable slot, `ledger/vtables.json` and `ledger/classes.json`;
  for an `unplaced.cpp` stub, the file rules of how-to step 3.
- **Lanes must not overlap.** A lane takes a whole class or family where it can: its vtable, its file, its pending
  members and its statics' destructors. Different classes and different files, so no two lanes edit one file or emit
  one vtable. A header
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
without a match.

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

1. **Fresh objects.** Move aside, by name (into `build/out/verify/old-objs/`), every object the lane built:
   `find build/out/app -name '*.o' -newer .git` lists them, since the worktree's `.git` file dates from its creation
   and the cloned objects keep the checkout's older mtimes. A header the lane added or edited rebuilds every object of
   its tree and the companions that name its directory, not only the unit's (`src/units/README.md` "What a fragment
   holds" item 3; `docs/reference/facts/workflow.md` §W15), and `-newer <header>` misses an object built before that
   header's last edit. Run `TMPDIR=/tmp make -C src splat`, with no `-j`, check that it compiled exactly those objects, and `cmp`
   each with its old copy. A stale object means the source edits never rebuilt. An object that does not come back is a
   deleted file's: `cmp` is owed for the objects the link names.
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
   `TMPDIR=/tmp make -C src check-srcloc` with no wrong record of a matched function (its records that only
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
batch that meets a lost match stops before committing that merge and posts it. A toolkit fix the merge needs is a commit
of its own on `main`, with a VERIFY of its own before the push, and the batch then goes on from there: a merge already
staged when the need shows is aborted (`git merge --abort`, everything staged first: `docs/reference/facts/workflow.md`
§W22), the fix committed on `main`, and the lane merged again. A row lost to
one link's data layout, the cause shown (how-to step 9's cases: an object at 0x100000, a string's closing NUL read as
a table slot),
may wait for the next lane of the batch: land that lane first, retry, stop if the row is still out, and say so at the
top of the result.

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
   to 10 again on the merge (link, census, symbols, match, build, checks) and commits it all as the merge commit. Every
   check passes at that commit but one case: a lane that adds or retires a benchmark setup leaves the merge failing
   `pnpm test:bench` until the re-selection, a commit of its own after it (`asmlift-wasm/benchmark/README.md`
   "Re-selecting"), and the merge's message says so. A
   merge commit takes no pathspec (`docs/reference/facts/workflow.md` §W18): stage everything, check that `git status
   --short` shows no unstaged or untracked line, and commit with a bare `git commit -F -`. That is safe only because
   LAND owns the whole checkout. Do not pick generated lines by hand. How-to step 10 has the rest: no `make -C src
   stubs` on the merge before step 9, each index once in `splat/matched.txt`, both sides' hand edits with one line per
   name, and which side of a twin's line to keep, with the check after step 9. A stand-in whose every target caller is
   now in the link goes in the merge; one whose callers landed in part stays, with its comment saying which still wait,
   unless a link without it moves no row (`src/units/README.md` "Companion files").
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
contributor does not hit it. It runs every command it writes into a doc, as written, before committing.
Facts that an edited doc depends on move into `docs/reference/facts/` (no doc cites the board). A fix that needs code
(a Makefile rule, a tool option) is not made here: it is listed as a follow-up for the user. It checks that the
relative links of every edited doc resolve and that `status.py --check`, `stubs.py --check` and
`check_encoding.py` still pass, commits on a `docs/…` branch of its own worktree, and posts its result: the commits,
and for each friction post the doc change that answers it, or why none does.

With many posts, split the docs in two parts by file, one agent each in its own worktree from the same commit, and
give each post to the part whose file it names first. A third agent then merges the two branches, gives each fact one
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
