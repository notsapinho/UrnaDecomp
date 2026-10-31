# Facts: where a function goes

What the evidence says of a function's file, tree and neighbours, beyond the record that names them: what a stub's place
is worth, a class with no file of its own, what a stretch's label says, how to read link neighbours and the data, an
error enum's codes, how to lay out a file and the headers a class needs, and how to find a slot's callers.
`docs/how-to-decompile.md` steps 1 to 3 rely on these, and its rules are there; this page holds their cases. Commands
run from the repository root, at 0b5f410 where a number moves.

## P1. What a stub's place is worth

A stub marked `placement: link order` has no record that gives it a line: its file comes from its class's vtable
or vptr. A stub in a tree's `unplaced.cpp` has no evidence for any file. In `src/ecourna/` every stub is one of these
two kinds, since most ecourna functions that have records are written, so the record leads to code, not to a stub.

A stub can sit over code we have: `stubs.py` cannot see a non-virtual function that has no record. The stub f5158 in
`src/ecourna/unplaced.cpp` is `ecourna::api::util::CStringUtils::ToLower(std::string&)`, which
`src/units/12-ecourna-api-sql-sqlite-externs.cpp` defines (its header comment names fn 5158); the scan's row is a census
pair with that body, `unresolved` on a static of ours.

A stub in `unplaced.cpp` has no evidence for any file only while no file is named after its class: `stubs.py` puts a
class's stubs in `<class in lower case>.cpp` of the tree as soon as that file exists, so a unit that creates
`cwasmscreen.cpp` for another class's members sees `simulador::CWasmScreen`'s stubs move into it at step 9.

The tree of an `unplaced.cpp` stub is no more evidence than its file: `stubs.py` takes it from the function's component
(`tree_of` in `tools/round/stubs.py`), which says who calls the function. Decide the tree, and so the flags, from the
callers' records and from the landing pads: a call that can throw while a local with a destructor is alive goes through
`invoke_*` in ecourna's and the ASN.1 runtime's code and directly in uenux2's (`grep -c invoke_` of the `fn` readout,
[app-flags.md](../app-flags.md) "Exceptions"). 5449 has group `ecourna`, because it calls ecourna's
`CStringUtils::ToByte`; it calls it with a `substr` temporary alive and no `invoke_`, and its callers are
`api::EncodeTime` (3643, `ctime.cpp`) and `api::CDateTime`'s constructor (5475, `cdatetime.cpp`): uenux2 code, which unit
24 writes in `src/uenux2/src/api/util/ctime.cpp`.

## P2. A class with no file of its own, or out of its upstream file

Read the class's vtable and typeinfo in the data before you create the file the class's name gives. Three shapes:

- **Two classes in one object.** A typeinfo of class A after the vtable of class B, with A's vtable between B's
  vtable and B's typeinfo, puts both in one object: `simulador::CWasmImageSurfaceOps`'s vtable (1528980) and typeinfo
  (1529060) lie between `simulador::CWasmScreen`'s vtable (1528816) and typeinfo (1529080). Its members are in
  `mock/app/simulador/wasm/cwasmscreen.cpp`, the header at how-to step 3's rule 4 path (unit 69).
- **A class with its key function in another class's file.** `comum::CRdvPosicionadorVota`'s vtable and typeinfos lie
  inside `crdvvota.cpp`'s run of the data, and a copy kept from a user would come after `comum::CRdvVota`'s own typeinfo
  and its members after the file's external functions; here they come before. A small class one file constructs can be
  defined there: its member goes into that file, and the landed unit that compiles it grows (unit 13).
- **A class out of its upstream file.** The reverse: a fork can move a class out of the file upstream keeps it in, and
  the data show it. `ASN1::DataLengthCounter` is in upstream's `BEREncoder.cxx`, and `PEREncoder`'s vtable (1151416) lies
  between `PrimitiveChecker`'s (1151276) and `DataLengthCounter`'s (1151548) in `ledger/vtables.json`'s address order, so
  the target's `BEREncoder` object does not hold it. The data separate it from `BEREncoder` only; `PEREncoder.cxx`'s end
  gives the same module, so its file name is chosen. The sign that sent the search there: a call the target keeps and
  clang inlines at a low cost, with no flag to explain it, means the callee is in another TU.

## P3. What a stretch's label says

The `unplaced.cpp` comment over a cluster, `// link-order cluster 255 · uses=1 · neighbours' file
uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversorhasharquivo.cpp`, is that stretch's `probable_file` in
`ledger/tu-clusters.tsv`. Its label (column `label_kinds`) says where the name comes from
([tu-slices.md](../tu-slices.md)): `source_location` and `class-record` from a record of another
function in the stretch, `class-convention` from the tool's guess when none has one, the namespace's directory and
the class name in lower case. A stretch can hold unlabelled functions of other classes, so a record's label can be
another class's file: `api::CSubReport`'s constructor 3660 sits in stretch 984, labelled
`uenux2/src/api/gui/ctextfielddoubleline.cpp` from 3659's record (`awk -F'\t' 'NR>1 && $1==984 {print $10, $11}'
ledger/tu-clusters.tsv`). Take the file name from the comment only when its label is a `class-convention` guess for this
class, and confirm even that from the data (above: stretch 499 guesses `crdvposicionadorvota.cpp`, which does not exist in
the target); otherwise the class's own name gives the file, and the comment gives the directory at most. The directory
comes from the stretches beside it that have records:

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

The guess puts most comum converters in one directory: 14 of the 15 comum converter cluster comments in
`src/uenux2/unplaced.cpp` say `dados/asn/estadoaplicacao` (`LC_ALL=C /usr/bin/grep -h "neighbours' file
uenux2/src/app/comum/.*cconversor" src/uenux2/unplaced.cpp | LC_ALL=C sed -E "s|.*neighbours' file
uenux2/src/app/comum/||; s|/[^/]*$||" | sort | uniq -c`). Stretch 255's recorded neighbours are
`app/comum/gravadores/` files, so `comum::asn::CConversorHashArquivo` (10267) goes in `app/comum/gravadores/asn/`.

## P4. Link neighbours by band position, confirmed from the data

Read a function's link neighbours by band position. Inside one band (one `uses` value of `ledger/ordinals.tsv`) the
target's index runs in reverse link order ([glossary](../../glossary.md#link-order), *order law*), so the indices next
to it in its band, and the stretches they fall in, are its neighbours, except where a function of another digit zone
sorts in between (a 3- or 2-digit ordinal sorts right after the 4-digit ones it begins), which the ledger cannot single
out for an unanchored function. Never compare two functions by the `ordinal` column: for 3,232 of the 3,270 TSE
functions it is the middle of a window thousands of ranks wide, it steps through 3- and 2-digit values from one index to
the next whatever the functions are (stretch 853's 5909 to 5913 read 4301, 4300, 430, 43 and 4299), and 3,476 values are
shared: 4303 is the estimate of 5907, of `api::CTextFieldUpdateMT`'s D0 10549 and of 10945 in `api/gui/`'s
`CTextFieldBlinking` stretch ([link-order.md](link-order.md) §L7 item 14). The neighbours of 5913 (`comum::CMenuBase`'s
slot 2) in its band, `uses` 2:

```sh
awk -F'\t' 'NR>1 && $2==2 && $1>=5908 && $1<=5918 {printf "%s ", $1} END {print ""}' ledger/ordinals.tsv
# 5908 5909 5910 5911 5912 5913 5914 5915 5916 5917 5918
```

then each neighbour's records or stub: `awk -F'\t' '$6 ~ /(^|,)5914(,|$)/ {print $2}' ledger/source-locations.tsv`
prints `/home/rubio/tse/uenux2/src/app/comum/informacao/cinformacaoeleicao.cpp`. Confirm them from the data, which has
no digit scramble: a TU's vtables, typeinfos and `std::source_location` records lie in link-line order, object by
object, so the records and vtables at the addresses around the class's vtable (`ledger/vtables.json` `address`) are its
object's neighbours' ([link-order.md](link-order.md) §L7 item 15 lists them in address order).
`comum::CMenuBase`'s vtable (1550924) follows a record of `app/comum/informacao/cinformacaoeleicao.cpp` and four
`comum::CItem*` vtables. A vtable or typeinfo of a class with no key function is a copy in its first user's object, as
its linkonce functions are (how-to step 3, rule 2).

## P5. When the two sides disagree

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

## P6. An error enum's codes

A shared enum generated from the codes the target passes misses every thrower binaryen
merged: a merge thunk passes the code to the shared body as a constant parameter, and the body's constructor call has no
constant to read. 3724 is `f6029(p0, 124, 1571724, 362126, 8013)`, and 8013 is in no `f170` call
(`pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3724`, from `asmlift-wasm/`). So read the `i32.const` arguments of
each thunk of a `byn$mgfn-shared` body whose parameter reaches the error constructor's code argument too. A code the list
missed is a `static_cast<E>(8013)` at the throw, and the shared header stays one blob.

## P7. Declaring what a class needs, and laying out a file

A by-value member whose type no header of ours defines needs that header before the class compiles: write it with the
data members at the offsets the bodies give and declarations only of the members a record names, say in its comment that
the layout is all that is recovered, and claim it like any new file ([agents.md](../../agents.md)); the type's own
`.cpp` stays a stub file until its functions are written. A member of that type whose code a function you write holds
inlined is the exception: define it in the header, named as how-to step 3 says when no record names it, since the bytes
are then its evidence and the function cannot be written without it. When the target holds that code inlined in two
functions, write it so that clang inlines it (how-to step 3, "Code binaryen inlined from another function").

A type with a vptr is a second exception. A destructor you write that inlines the member's destructor stores the
member's vptr, so the member's vtable must link, and each of its slots needs a definition. Define in the class a slot
whose target body you can read (`api::CFixedText`'s two `IText` overrides are one-line reads, 1139 and 1661, in
`src/uenux2/src/api/gui/cfixedtext.h`), and trap the others in the `-pending.cpp` ("A member inline in the original" in
[src/units/README.md](../../../src/units/README.md)). With the slots declared only, the object references an undefined
`_ZTVN3api10CFixedTextE`.

A class your bodies need complete only to call a base's virtual slot through a pointer (a `std::shared_ptr` member
whose `Slot2()` you call) gets its head alone: the class and the base clause RTTI gives, with a comment that no member
is reconstructed, as `src/uenux2/src/api/gui/cinteractiveform.h` does. Its `sizeof` is then wrong, so nothing may
construct it; the first unit that needs a member adds the data members and the records' declarations as above.

**A stub-only file.** A file the evidence names that does not exist yet holds its stubs only, written from line 2
on, not at their records' lines ([src/README.md](../../../src/README.md) "Stubs"). `--strip` leaves next to nothing of
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

## P8. A slot's callers

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
