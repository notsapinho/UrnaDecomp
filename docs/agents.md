# Running several agents on this repository

Rules for a run in which several agents work on urna at once, coordinated through a message board. Each rule is
here because breaking it costs a run time or gives a wrong number. A single person or a single agent working alone
needs only "House rules" and "Shared build outputs".

## The message board

The board is a folder **outside** the repository, created for one run; the run's brief names it. It has:

| folder | holds |
| --- | --- |
| `board/facts/` | what is true of the repo, the target or a tool, with the command that shows it |
| `board/traps/` | commands or files that give a plausible wrong answer |
| `board/rounds/` | a stage's claim (the paths it owns) and its result |
| `board/friction/` | one post per point where a doc was missing, wrong, ambiguous or misleading |
| `queue/` | requests to the coordinator (blocked on something outside one's area, a question the board does not answer); the reply is `<same name>.reply.md` |
| `inbox/` | the user's notes; the coordinator acknowledges each in `inbox/ack/` |
| `shared/` | files posts cite, copied out of removed worktrees, and headers lanes publish for each other |

- A post is `<stamp>-<HANDLE>-<slug>.md`, with `<stamp>` the output of `date -u +%Y%m%d-%H%M%SZ` **run as a
  command**. It opens with `from:`, `date:`, `tags:`, and `corrects: <file>` when it corrects another post.
- Posts are append-only: never edit or delete one; correct it with a new post. Before acting on a post, look for
  posts that correct it (`grep -rl "corrects: <filename>" board/`).
- Append one line per post to `INDEX.md` with `printf '%s\n' "<path>  <hook>" >> INDEX.md`, nothing else ("Two
  machines" has the second machine's file).
- A number is posted with the command that produced it, or not at all. Post what you learned, not status.
- The inbox is the user's word and outranks every brief. Every agent reads it at the start of each stage, again
  before a step that cannot be undone (a `git worktree remove`, a merge onto `main`) and before posting its result: a
  note that arrives during a stage outranks the brief from then on. Only the user (or the coordinator transcribing the
  user, marked as such) writes there.
- The board is not part of the repository and does not outlive the run. Before a run ends, move every fact a
  tracked file depends on into `docs/reference/facts/` and cite it there: code and docs never cite a board post.
  Nor do they name a round, a lane or an agent handle, which mean nothing once the run is over: say what a file
  waits for in the tree's terms (`api/util/itimer.h defines it`, a header that is not in this tree yet), not who is
  making it.

## An agent's turn

A delegated agent that ends its turn reports as finished, whatever is still running. So run a long step in the
foreground, and end a turn only when the stage's post is written. A registered background wait does not keep a turn
alive either: a landing whose turn ended while its merge steps ran in the background read as done with nothing
committed.

A command the harness's shell parser cannot rule out stops at a permission prompt, and in a delegated agent nobody is
there to approve it. Such a stall prints nothing, so it reads as an agent that is quiet, and a verifier stalled for two
hours looks like one that is thinking. Write anything beyond a plain command to a script file with the file tool and
run it with one short command: no zsh array or `${(@f)…}` expansion, no heredoc chained with other commands, no
`eval`. A coordinator that sees no post and no new file for a long while asks the agent where it stands.

## Working in one shared checkout

- **Claim before editing.** Post a `rounds/` claim listing the files or directories you own. Do not edit a path
  another active stage claimed; file a `queue/` request instead. A header you derive from is one you depend on, claimed
  or not: when another stage claims it, read that claim's layout and link against it before you commit, since a base's
  moved member breaks your matches at the merge and no check shows it earlier.
- **A type no lane owns.** Before you declare a type a record names, look for it on the other lanes' branches: no check
  sees two definitions until the first TU that includes both stops on a redefinition. `for b in $(git branch --list
  'decomp/*' --format='%(refname:short)'); do LC_ALL=C git grep -n -E 'class <T>|enum( class)? <T>' "$b" --
  'src/uenux2/*.h'; done` lists them; take the first one byte for byte (`docs/how-to-decompile.md` step 10). A type
  several lanes of a round need is the pick's to generate whole, once, for every lane to copy as one blob, names marked
  as chosen, so that an add/add merges clean ([facts/workflow.md](reference/facts/workflow.md) §W17). An error enum read
  from the target's codes needs the merge thunks too ([facts/placing.md](reference/facts/placing.md) §P6).
- **Commit only your own paths**: `git add <paths> && git commit -m "…" -- <paths>`. The `-- <paths>` keeps other
  agents' staged changes out of your commit. A path you removed with `git rm` (a stub
  file step 9 deleted) goes after `--` only: `git add` refuses it, and then adds nothing at all
  ([facts/workflow.md](reference/facts/workflow.md) §W7; `docs/how-to-decompile.md` step 10 has the whole command).
  Read `git log -1 --stat` after every commit.
- **Keep scratch in your own worktree**, under `build/out/<handle>/` (ignored), and pass a commit message with
  `git commit -F -` and a heredoc. A folder every agent sees (the session's scratchpad, a fixed `/tmp/<name>`) holds
  another agent's file of the same name by the time you read it back: a commit message written there was replaced
  that way before a retry committed it.
- A branch follows the docs of the commit it started from, and a reviewer of it says which version it judged by.
  When `main`'s docs change while the branch runs (a docs pass runs alongside a round, and no lane waits for it:
  `.claude/commands/decompile-functions.md` Stage 5), its landing reads the branch's choices against `main`'s docs too,
  since the merge lands under them (`docs/how-to-decompile.md` step 10, "Landing onto a moved main"). Read `main`'s
  text with `git show main:<path>`, not from another checkout.
- If `.git/index.lock` exists, wait and retry. Remove it only when it is older than ten minutes and no git process
  runs.
- Never `git stash` (the stash is shared with every checkout of the repository); use a WIP commit. Never push
  unless the user asks.
- A fresh `git worktree add` gives every tracked file today's mtime, so the first link recompiles everything.
  Copy the mtimes from a clean checkout at the same commit
  (`git ls-files -z | while IFS= read -r -d '' f; do touch -h -r "$f" "<new>/$f"; done`), then
  `make -n -C src link` should report nothing to do. That check cannot see a `build/out/` cloned from a checkout
  at another commit: a link that holds units this tree lacks is still newer than every object this tree lists, so
  make keeps it ([facts/workflow.md](reference/facts/workflow.md) §W4). Clone build outputs only from a checkout at
  the same commit, or use `tools/round/build-at.sh` (below); when in doubt, delete
  `build/out/wasm/vota_web/vota_web_wasm.wasm` and `build/out/wasm-named/vota_web/vota_web_wasm.wasm` by name and
  link again.

## Worktrees

One worktree per lane, for as long as the lane runs, and no longer: leftover worktrees hold gigabytes and confuse
the next run.

- **Delete a worktree as soon as its lane is landed or dropped. Keep the branch.** `git worktree remove <worktree>`
  deletes the directory and leaves the branch. Before it, check that nothing is lost: `git -C <worktree> status
  --porcelain` prints nothing, and for a landed lane `git merge-base --is-ancestor <commit> main` exits 0, with
  `<commit>` the one that landed, which need not be the branch's tip. A dropped lane's branch keeps its commits, so
  commit what is worth having first.
- **Copy out what the board cites first.** The clean-up check sees tracked and untracked files only, and the worktree's
  ignored `build/out/` goes with it, with every script and log a post names. Copy the worktree's scratch roots to the
  board's `shared/from-<lane>/`, which the coordinator copies between machines, each file of 5 MB or less, and write
  what stayed out and why in a `SKIPPED.txt` there. A private clone or `APP` tree under a scratch root is thousands of
  small files that each pass the limit, and its commit and script make it again: copy its logs and row lists, leave the
  tree out, and name it in `SKIPPED.txt`. Keep a verifier's logs one level above any tree it makes. Name the new path in your result. Check the copy against the names the
  lane's posts give, relative ones too: a posts' search for `build/out/…` misses `p/run.sh` under "in build/out/<handle>/"
  and still reports nothing unresolved. A script worth keeping past the run belongs in `tools/`.
- **At a round's end `git worktree list` shows only the main checkout.** Read it before you report the round.

## Two machines

A round can run on two machines. Each has its own checkout, its own worktrees and its own copy of the board, at the
same paths on both, and its own limit of agents. Size the limit to the machine's CPUs and memory, the census's 3.4 GB
each included: 8 agents on 12 CPUs and 24 GB, 4 on 8 CPUs and 12 GB.

- **One index per machine.** Agents on the first machine append to `INDEX.md`, and agents on the second to
  `INDEX-<machine>.md`, so the two copies never overwrite each other. A post's stamp and handle make its name unique,
  so posts from both machines merge with no conflict.
- **The coordinator copies the board,** both ways, adding and updating and never deleting, in a loop for as long as
  agents run (every two minutes worked). A post from the other machine is on yours only after the next copy, and the
  inbox and `shared/` travel the same way.

  ```sh
  rsync -au <board>/ <host>:<board>/
  rsync -au <host>:<board>/ <board>/
  ```

- **What lanes share goes through the board.** A branch is on its own machine until the coordinator fetches it, so
  `git show <branch>:<path>` fails on the other. A header a lane publishes for others goes into the board's `shared/`,
  and a lane that needs one from the other machine takes it from there.
- **Lanes never push.** A lane commits on its branch in its own machine's checkout, and its VERIFY runs on that machine,
  on the lane's worktree.
- **One machine lands.** The coordinator fetches the other machine's branches over ssh, then merges each confirmed
  commit by its id as usual:

  ```sh
  git fetch <host>:<checkout> decomp/<lane>:decomp/<lane>
  ```

- **One coordinator owns `main`.** A second machine can carry on when the first goes offline, and then it has a
  coordinator of its own. Two must never own `main` at once. The one that hands over finishes or stops what it holds and
  starts nothing new. It writes the line `HANDBACK: <origin's main>, <matches>, <its pull requests>, <what is left>` in
  its state file and a `rounds/` post, when `origin` holds its work and its worktrees are gone. The other starts no
  landing until it reads that line and the inbox, then takes `main` from `origin` and runs Stage 0 step 1's checks
  (`.claude/commands/decompile-functions.md`). A worktree's `build/out/` stays on its machine, so the first link after a
  move recompiles what the commits changed.
- **A worktree is deleted on the machine that holds it,** as "Worktrees" says, cited files included. At a round's end
  `git worktree list` shows only the main checkout on both machines.

## Shared build outputs

- `build/out/` is shared. Every link rewrites `build/out/wasm/vota_web/vota_web_wasm.wasm`; freeze a copy of the
  module before deriving a table or an anchor file from it.
- Measure a flag set in a **private link**: `make -C src link APP=build/out/<name>/app OUT=… OUT_NAMED=…`
  (`APP` moves every app object, so the first private link rebuilds them all). Never write the shared
  `build/out/app/…` objects with experimental flags: an object rule depends on the Makefile's mtime, not on the
  flag value, so the object would survive into everyone's link. Add the flag with `UENUX2_EXTRA=…` (or
  `ECOURNA_EXTRA=…`), never a command-line `UENUX2_CXXFLAGS`, which drops the fragments' target-specific additions
  and reaches the stand-ins. [facts/app-flags.md](reference/facts/app-flags.md) §F9 item 6 has the command and the
  splat check of such a link. To measure one variant object in the whole link (a companion file against an overlay
  header, a source with one more flag), clone the objects with their mtimes (`cp -Rp build/out/app
  build/out/<handle>/app`), replace that one object, and pass the clone as `APP`: `make -n` then counts 0 compiles
  against the 347 of a fresh `APP` ([facts/workflow.md](reference/facts/workflow.md) §W13). A header overlay for the
  whole link needs `APP_CXXFLAGS` passed too, since `UENUX2_EXTRA` does not reach the roots, and a variant's scan reads
  the committed symbol file (both §W13). `make` compares times, not paths: an override such as `RHVOICE_DIR=<dir>`
  over an existing link whose inputs are older relinks nothing, and the census and scan then measure the old link, so
  delete the two link outputs by name first, or use a private `OUT`.
- A flag change in a `src/units/*.mk` fragment does not rebuild stale objects: touch the sources. An edit of a
  source or a header does: each object depends on its own source and on every header of its tree. A comment edit in a
  fragment rebuilds that fragment's companions and `roots_asn1.o`, whose rules name it.
- `-j` goes on the object list only, never on `link` or `splat` ([facts/workflow.md](reference/facts/workflow.md) §W21).
- Two units landing in one run each need their own fragment number: the coordinator assigns them before the
  matchers start, and the unit that lands second re-runs link, census, symbols, match and the splat build on top of
  the first (`docs/how-to-decompile.md` step 10, "Landing onto a moved main").
- An edit to a header, or a new header, recompiles every object of its tree, whether it includes the header or not
  (the generic rules depend on every header there), the tree's roots object, and the companions whose rules name it:
  164 compiles for `src/uenux2/src/api/util/cdatetime.h`, 189 for a new header in `src/uenux2/src/api/gui/`, at 0b5f410
  ([facts/workflow.md](reference/facts/workflow.md) §W15). A half-finished edit breaks every other agent's link
  until it is fixed. Keep shared headers compiling at every commit. The splat build checks only the
  matched functions of those units; to show that a restructure left them as they were (a vtable, an inline member a
  parallel lane builds on), list the objects the edit will rebuild, keep a copy of them before the first link or try,
  and compare each after relinking ([facts/workflow.md](reference/facts/workflow.md) §W13):

  ```sh
  make -n -C src link -W $PWD/<header> | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//' > build/out/<handle>/rebuilt.txt
  while read o; do [ ! -f "$o" ] || echo "$o"; done < build/out/<handle>/rebuilt.txt > build/out/<handle>/existing.txt
  tar -cf build/out/<handle>/before.tar -T build/out/<handle>/existing.txt
  # edit the header, then TMPDIR=/tmp make -C src link
  while read o; do tar -xOf build/out/<handle>/before.tar "$o" 2>/dev/null | cmp -s - "$o" || echo "DIFFER $o"; done < build/out/<handle>/rebuilt.txt
  ```

  The list names the objects of sources a unit adds too; they are not built yet, so the filter keeps them out of the
  archive (`tar -T` would report each one and exit 1), and the loop prints `DIFFER` for them, which is right. An object
  that is not in the list compares equal with itself and proves nothing, and the list can miss one: a fragment, a
  companion that holds a header its rule omits, and an edit of an `src/asn1` module header
  ([facts/workflow.md](reference/facts/workflow.md) §W15 has the check). A reviewer with no copy from before the edit
  compiles the base's objects from `git archive <commit> src` in scratch
  ([facts/workflow.md](reference/facts/workflow.md) §W13). Before a link, the same list taken for each file a unit added
  or changed, fragments too, gives, as their union, what the unit's edits will rebuild. To check a unit's objects fresh
  afterwards (move them aside, rebuild, compare), move aside every object its worktree built: `find build/out/app -name
  '*.o' -newer .git`, run in the worktree, lists them, since the worktree's `.git` file dates from its creation and a
  cloned `build/out/` keeps older mtimes ([facts/workflow.md](reference/facts/workflow.md) §W15). `find build/out/app
  -newer <header>` compares with the header's last edit and misses an object of the unit built before it. Rebuild with
  `TMPDIR=/tmp make -C src splat`, serially; an object listed that does not come back is a deleted file's.
- A header your unit needs that `main` gained after your branch started: start your copy from `main`'s text and only
  add to it. One that a branch landing before yours adds: copy it from that branch byte for byte, claim it, and do
  not edit it (`docs/how-to-decompile.md` step 10, "Landing onto a moved main").
- Every agent's link recompiles on the same machine. With a dozen agents the load average passes 130 and one
  compile of eight objects takes six minutes; size the fan-out to the machine, and prefer a lone compile
  (`tools/round/try-tu.sh --single`) or a library probe for questions that do not need the whole link.
- A splat build or scan runs the toolkit's **working tree** (`asmlift-wasm/`). If another agent is editing the
  toolkit, a measurement can depend on code nobody committed; measure against a committed tree (`git archive
  <commit> asmlift-wasm | tar -x -C <dir>`) when that matters.
- To build an earlier commit, run `tools/round/build-at.sh <commit> <dir>` from a checkout whose build is current, then
  `TMPDIR=/tmp make -C <dir>/src splat` (a test on that commit needs this too:
  [facts/workflow.md](reference/facts/workflow.md) §W12). `<dir>` is a new directory outside the checkout, a sibling of
  the worktree (`../<worktree>-base`): the script clones the checkout's whole `build/out/` into it, so a `<dir>` under
  `build/out/` would hold a copy of itself ([facts/workflow.md](reference/facts/workflow.md) §W5). A `cmp` against the
  base's objects means something only for the objects the base's build rebuilt; every other one is a clone of yours. A
  bare `git worktree add` or `git archive` of the commit cannot build: it lacks every ignored input (`third_party/*`,
  `target/fs/`, `asmlift-wasm/node_modules/`, the library outputs under `build/out/`; without node_modules the split
  fails right after `splat-split` with no message), and every file gets a time newer than any object, so the first link
  recompiles everything. The script clones those inputs in, copies this checkout's mtimes, and touches the files the
  commit has differently, so make rebuilds exactly what depends on them; it prints how many objects the link will
  recompile. Remove the tree with `git worktree remove <dir>`. To compare a few objects with an earlier commit you need
  no tree: `git archive <commit> src` into scratch and the compile lines of `make -n` there
  ([facts/workflow.md](reference/facts/workflow.md) §W13).
- `make -C src splat-symbols` after a new link re-picks the arbitrary name of byte-identical twins, so two runs'
  symbol files conflict on such lines: regenerate after merging rather than pick a side. `splat-scan` and
  `splat-match` can disagree on a count; trust the splat build's verification, and read `git diff
  splat/matched.txt` for lines that a data change matched by accident.

## House rules

- Never delete with a wildcard (`rm -f ./*` and the like). Name each file, or move files into a `stale/` folder;
  `git rm <name>` is fine.
- Run docker-backed commands with `TMPDIR=/tmp` on macOS: docker cannot mount the default `/var/folders` temp
  directory.
- Never byte-compare an `--emit-symbol-map` build with the target: the map changes the function order of an -Oz
  link ([facts/link-order.md §L1](reference/facts/link-order.md)).
- Run the Python tools with `python3 -I -B`: `-B` keeps `__pycache__` out of the tree.
- In zsh, pass flag lists as arrays ([facts/tool-traps.md §X3](reference/facts/tool-traps.md)). zsh does not split an
  unquoted `$list` into words, and it expands an unquoted glob in an argument (`--include=*.hpp` fails with "no
  matches found"): quote it. It also reads `:` after a bare parameter as a modifier, so `git show $rev:path` fails
  with `bad substitution`: write `"${rev}:path"`; in an unquoted heredoc the same stops after the file was truncated. A
  word that starts with `=` is a command's path: `echo ======` fails with `===== not found`. `for i in $L` runs once,
  over the whole list, and `em++ $F` passes the flags as one argument: write `${=L}` and `${=F}`. Each of these ends
  with no output that reads like a result, so check that a file was written before you count it
  ([facts/workflow.md](reference/facts/workflow.md) §W10).
- In an agent's shell, `grep` can be a shell function that prints nothing for a search over the Latin-1 sources, with
  `LC_ALL=C` in front too, and exits as if nothing matched, so a negative from it is no evidence.
  Use `/usr/bin/grep` (or `command grep`) there. Run every text tool of a pipe over those sources or a stub line
  under `LC_ALL=C` (`sed`, `cut`, `tr`, `awk` with a regex, `git grep`), or convert with `iconv -f latin1 -t utf-8`
  first: in a UTF-8 locale macOS `sed` and `cut` stop with `illegal byte sequence` at a stub's middle dot, and
  `git grep` prints nothing ([facts/workflow.md](reference/facts/workflow.md) §W9).
- Run `pnpm test` (from `asmlift-wasm/`) alone in a checkout: beside a census or `splat-match` its real-link cases
  skip and it still exits 0. Read the count ([facts/workflow.md](reference/facts/workflow.md) §W12).
- The official progress check is `TMPDIR=/tmp make -C src splat`: it must print the target's sha256. A stage that
  touches sources, fragments or flags runs `TMPDIR=/tmp make -C src link` and then the splat build before it
  commits.
