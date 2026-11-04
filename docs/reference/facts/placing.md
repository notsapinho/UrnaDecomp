# Facts: where a function goes

What the evidence says of a function's file, tree and neighbours, beyond the record that names them: what a stub's place
is worth, a class with no file of its own, what a stretch's label says, how to read link neighbours and the data, an
error enum's codes, how to lay out a file and the headers a class needs, how to find a slot's callers, and a band's
order against landed members, two objects and a record.
`docs/how-to-decompile.md` steps 1 to 3 rely on these, and its rules are there; this page holds their cases. Commands
run from the repository root, at 0b5f410 where a number moves, and at 182dc6c1 where a section says so.

## P1. What a stub's place is worth

A stub marked `placement: link order` has no record that gives it a line: its file comes from its class's vtable
or vptr. A stub in a tree's `unplaced.cpp` has no evidence for any file. In `src/ecourna/` every stub is one of these
two kinds, since most ecourna functions that have records are written, so the record leads to code, not to a stub.

A stub can sit over code we have: `stubs.py` cannot see a non-virtual function that has no record. And a stub can go
while its function is unwritten: a function whose only records are an inline member of a header another unit writes
loses its stub at that unit's step 9, since the record's line is then code of ours. The vota states' slot-7
`ProcessInput`s hold `CInteractiveForm<…>::Read()`, so search them by that record (`awk -F'\t' '$2 ~
/cinteractiveform.h$/ && $3==57 {print $6}' ledger/source-locations.tsv`), not by their stubs.

A stub is not always a TSE source to write. Its tree follows its callers' component, so a library's code that TSE calls
gets one: the 7-Zip LZMA encoder (410, 2603, 3419, 4941) has stubs in `src/uenux2/unplaced.cpp`, and libc++'s 2547 and
3335 (owner `libcxx`, called by 5360 and 7741) in `src/ecourna/unplaced.cpp`. Read the row's `owner` in
`ledger/functions.tsv` (column 4) first: a library there means the library's build, not a source, and the row lands with
its caller (182dc6c1):

```sh
awk -F'\t' '$1==410 || $1==2134 || $1==2199 || $1==2546 || $1==2547 || $1==2578 {print $1, $4, $5}' ledger/functions.tsv
# 410 7zip comum
# 2134 - ecourna
# 2199 boost ecourna
# 2546 libcxx ecourna
# 2547 libcxx ecourna
# 2578 - comum
```

The owner is a lead, not a verdict. It reads a library for a TSE function whose code is mostly the library's, inlined:
2199 is `ecourna::api::util::CStringUtils::FindRegex`, written in `src/ecourna/api/util/cstringutils.cpp` and matched,
owner `boost`; the records and the symbol file decide. A row with no owner can be a library's code too: 2134 calls
libc++'s path parser (2546), and 2578 and 2579 are libc++.a's `algorithm.o`, `std::__partially_sorted_swap` over
`unsigned` and `unsigned char` (1506 and 1507 are the `__sort3` that call them). libc++ declares `extern template` the
`__sort<__less<T>&, T*>` of every arithmetic `T` and defines them in the library, so a `std::sort` over such a `T*`
with the default order calls the library's copies, which land with that caller at the library's flags and need no
source (2578 matched with 11212's sort: `awk '$1==2578' splat/matched.txt`). A sort over another type, or with a
comparator of its own (`__introsort` over `filesystem::path`), instantiates in the caller's TU and lands with it. And
`owner` can read `app` for a library function whose callers are the library's own code:

```sh
awk -F'\t' '$1==5009 || $1==9586 || $1==2602 || $1==2170 {print $1, $4, $5}' ledger/functions.tsv
# 2170 7zip -
# 2602 7zip -
# 5009 app ecourna
# 9586 app ecourna
```

5009's stub is in `src/ecourna/unplaced.cpp`, labelled by its cluster's neighbour `cwasminputmt.cpp`. Its one caller,
9586, calls 7-Zip's 2602 and 2170, and its body is 7-Zip's `SplitString(const UString &, UStringVector &)` (a
`CObjectVector` cleared, a split at the code 32, `CRecordVector`'s `size + size/4 + 1` growth): read the callers'
callees' owners and the body's shape before a cluster label.

A stub can stand for a body binaryen merged in the target, which no source writes. 2302 (483 B, `unplaced.cpp`,
`placement: link order`) had five callers, thunks of 17 bytes that differ in the two constants they pass, a format
literal's begin and end, and its neighbours in the index are merge bodies:

```sh
cd asmlift-wasm && pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3272 | /usr/bin/grep 'f2302'
#   f2302(p0, p1, 234577, 234519);
cd .. && awk -F'\t' '$1>=2299 && $1<=2304 {print $1, substr($2, 1, 16), $5}' splat/scan.tsv
# 2299 byn$mgfn-shared$ match
# …
# 2302 byn$mgfn-shared$ match
```

Its callers (3272, 4537, 4541, 4542, 4546) are log members that format one name each; it matched once they were
written and our link formed the same merge (`src/units/README.md` "Pending members", the merge-thunk bullet). A body
whose callers are all thunks that pass it their `this` and one constant each is such a merge of whole functions, and
its first parameter, which it never reads, is theirs: 6018 (`f6018(p0, 7)` in 10787, `f6018(p0, 11)` in 10792, among
the merge bodies 6007 to 6065) matched with the slots written whole and no helper.

A stub in `unplaced.cpp` has no evidence for any file only while no file is named after its class: `stubs.py` puts a
class's stubs in `<class in lower case>.cpp` of the tree as soon as that file exists, so a unit that creates
`cwasmscreen.cpp` for another class's members sees `simulador::CWasmScreen`'s stubs move into it at step 9.

The tree of an `unplaced.cpp` stub is no more evidence than its file: `stubs.py` takes it from the function's component
(`tree_of` in `tools/round/stubs.py`), which says who calls the function. Decide the tree, and so the flags, from the
callers' records and from the landing pads: a call that can throw while a local with a destructor is alive goes through
`invoke_*` in ecourna's and the ASN.1 runtime's code and directly in uenux2's (count `import:invoke_` in the `fn`
readout, not `invoke_`, which libc++'s `std::__invoke` matches too; [app-flags.md](../app-flags.md) "Exceptions"). 5449
has group `ecourna`, because it calls ecourna's `CStringUtils::ToByte`; it calls it with a `substr` temporary alive and
no `invoke_`, and its callers are `api::EncodeTime` (3643, `ctime.cpp`) and `api::CDateTime`'s constructor (5475,
`cdatetime.cpp`): uenux2 code, which unit 24 writes in `src/uenux2/src/api/util/ctime.cpp`. The other way, a row
stubbed in a uenux2 tree whose own frame has a landing pad, its cleanup through `invoke_*` and `__resumeException`, is
not uenux2's code: 501 (a message queue's push under a lock) is an `-fexceptions` TU's copy of an inline member, most
likely the executable TU's ([levels.md](levels.md) §V1). It is no body to match from a uenux2 object: the header's
inline member (`api::CPriorityMessageQueue<api::SMessage>::Insert`, `api/ipc/cmessagequeue.h`) is written for its uenux2
callers, and their copy read `differs` until a tree root at that TU's rule, `src/app/roots_messagequeue.cpp`, held the
instance ahead of them (`src/units/269-uenux2-cmessagequeue-insert.mk`).

## P2. A class with no file of its own, or out of its upstream file

Read the class's vtable and typeinfo in the data before you create the file the class's name gives, not from
`ledger/vtables.json` alone, which misses classes that have a vtable ([units.md](units.md) §U12 counts them, finds a
vtable by its typeinfo and reads its words). Three shapes, and a call that places its caller:

- **Two classes in one object.** A typeinfo of class A after the vtable of class B, with A's vtable between B's
  vtable and B's typeinfo, puts both in one object: `simulador::CWasmImageSurfaceOps`'s vtable (1528980) and typeinfo
  (1529060) lie between `simulador::CWasmScreen`'s vtable (1528816) and typeinfo (1529080). Its members are in
  `mock/app/simulador/wasm/cwasmscreen.cpp`, the header at how-to step 3's rule 4 path (unit 69).
- **A class with its key function in another class's file.** `comum::CRdvPosicionadorVota`'s vtable and typeinfos lie
  inside `crdvvota.cpp`'s run of the data, and a copy kept from a user would come after `comum::CRdvVota`'s own typeinfo
  and its members after the file's external functions; here they come before. A small class one file constructs can be
  defined there: its member goes into that file, and the landed unit that compiles it grows (unit 13).
- **A class out of its upstream file.** The reverse: a fork can move a class out of the file upstream keeps it in, and
  the data show it. `ASN1::DataLengthCounter` is in upstream's `BEREncoder.cxx`, and `PEREncoder`'s vtable (1151416)
  lies between `PrimitiveChecker`'s (1151276) and `DataLengthCounter`'s (1151548) in `ledger/vtables.json`'s address
  order, so the target's `BEREncoder` object does not hold it. The data separate it from `BEREncoder` only;
  `PEREncoder.cxx`'s end gives the same module, so its file name is chosen. The sign that sent the search there: a call
  the target keeps and clang inlines at a low cost, with no flag to explain it, means the callee is in another TU. An
  out-of-line constructor or destructor is the exception: at `-fPIC` its call stays beside the definition, with no
  remark ([codegen.md](codegen.md) §C6), so it is no sign at uenux2's flags. A second sign needs no inlining: with the
  callee's body in its TU, clang can drop work the caller does after the call on what it passed. 3745 and 5727
  (`NomeArquivoEleitores` and `…TTE`) test the long bit of both their temporary strings before freeing them; written in
  `cnomearquivo.cpp` beside 3772, the callee they keep a call to, ours tested one (`17 over 80 rows`, 12 deleted), and
  in a TU of their own both matched (unit 279). A target caller that keeps such a test where ours drops it is in another
  TU than its callee.
- **A call of another file's internal function.** With no LTO, only that file's TU can call a function of internal
  linkage (a `(anonymous namespace)::` or `static` name in a record), so a direct call of one puts the call site in that
  TU: the caller is defined there, or binaryen inlined into it a function defined there. 5971, `vota::(anonymous
  namespace)::CriaTituloExtratoRDV()` (`iniciovotacao/cgeradorresumozeresima.cpp:43`), is called by 11943 and 11946
  alone (`awk -F'\t' '$2==5971 {print $1}' ledger/callgraph.tsv | sort -u`), the `StartState`s of two zeresima bases.
  Read the caller's size and look for a one-caller function of that file to tell the two apart, and say which in the
  fragment.

## P3. What a stretch's label says

The `unplaced.cpp` comment over a cluster, `// link-order cluster 255 · uses=1 · neighbours' file
uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversorhasharquivo.cpp`, is that stretch's `probable_file` in
`ledger/tu-clusters.tsv`. Its label (column `label_kinds`) says where the name comes from
([link-order.md](../link-order.md) §7.5): `source_location` and `class-record` from a record of another
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

When the band and the data name different directories, the data win: they have no digit scramble, and a class's
vtable, its virtual members and its data come from one object whether it has a key function or not. Taking the band is
a choice the fragment names with both neighbours. `comum::asn::CConversorCodigoCargoConsulta`'s band puts 11591 and
11592 beside `app/comum/asn/cconversorcabecalhoentidade.cpp`'s functions, and its vtable, typeinfos and `theInfo`
(1555728 to 1555820) lie between two `app/comum/md/` files' records (unit 126 took the band and says so).

**What each order shows.** Three orders place code, and a comment says which one it rests on and what is a reading
([../link-order.md](../link-order.md) §2 has the rule; these are the measurements behind it):

- *Between objects*, the data: each object's vtables, typeinfos and records lie in link-line order (L7 item 15). That
  is evidence of the objects' order.
- *Inside one object*, the code: the use band's reverse index order against `names.tsv`'s `ld_index` (how-to step 3,
  "The order of two members") is evidence of the order clang emitted the functions, which follows the definitions only
  as [reading.md](reading.md) §R8 and §R9 say.
- *Inside one object*, the data: clang creates each object's data when its code first needs it, and the link keeps that
  order. A record comes with its function's body (§R8); a vtable with the first constructor or destructor that stores
  it; a typeinfo with its first `typeid` or vtable; an internal constant where the first function that reads it is
  emitted, and a global or a static data member at its first mention, not at its definition (`ctelasvota.cpp` defines
  `FONTE_TITULO`, `FONTE_INSTRUCAO_TESTE_TECLADO` and `FONTE_AGUARDE` on lines 176 to 178, and its object holds them as
  segments 3, 30 and 5, the second after `TelaTesteTeclado`'s data, its only reader, and `CTelasVota::s_mutex` before
  `s_instancia`, in `GetInst`'s order: `wasm-objdump -x -j Data
  build/out/app/uenux2/src/app/vota/eleitor/comum/ctelasvota.cpp.o | /usr/bin/grep 'segment\['`). So constants the
  key function's code reads come before the vtable, typeinfo and typeinfo name of its class, and constants only a
  deferred (internal) function reads come after them. Two probes at the uenux2 flags, `ext.cpp` (`K::f` reads two
  `SFont` constants) and `int.cpp` (an anonymous-namespace `g`, kept by a pointer, reads them and `K::f` calls it):

      // ext.cpp                                         // int.cpp: the same head, then
      struct SFont { int a, b; };                        namespace { const SFont F1{20, 0}; const SFont F2{30, 0};
      void use(const SFont&);                                        void g() { use(F1); use(F2); } }
      struct K { virtual ~K(); virtual void f(); };      K::~K() {}
      const SFont F1{20, 0}; const SFont F2{30, 0};      void K::f() { g(); }
      K::~K() {}                                         void (*keep)() = g;
      void K::f() { use(F1); use(F2); }

      P=build/out/placing-probe; for v in ext int; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/$v.cpp -o /work/$P/$v.o; printf '%s: ' $v; wasm-objdump -x -j Data $P/$v.o | /usr/bin/grep -oE '<\.(rodata|data)[^>]*>' | sed -E 's/<\.(rodata|data)(\.rel\.ro)?\.//; s/>//' | tr '\n' ' '; echo; done
        ext: _ZL2F1 _ZL2F2 _ZTV1K _ZTI1K _ZTS1K
        int: keep _ZTV1K _ZTI1K _ZTS1K _ZN12_GLOBAL__N_12F1E _ZN12_GLOBAL__N_12F2E

So two forms that give one object's code can give its data in two orders, and the target's run tells them apart:
`carregaarquivo.cpp`'s entity reader (1937) at the head of the file, between two instances or at its end gives the same
143 functions with the object-local numbers masked, and only "between" gives the target's data order
([link-order.md](link-order.md) §L7 item 15 prints the target's run). That our object's data order equals the target's
under one form is a measurement (the object's `wasm-objdump -x -j Data` segment order against the target's addresses);
that the original code was in that order is a reading, which the comment marks as one wherever it is restated (1937's
reader; 7667, whose tree root's builder follows `push<ITextToSpeech>`'s record 1526348 because `ITextToSpeech`'s vtable,
1526520, follows it).

A constant between two classes' typeinfo names belongs most directly to the file of the name that follows it, or to
the file before it when only file-internal code reads it: 1255's fonts (@540572, @540580) between
`N5comum18CRegistrarMesariosE` (@540542) and `N5comum18CPedeTituloMesarioE` (@540588) fit either, a choice. A callee
binaryen inlined across TUs has its records where the object that defined it out of line puts its data, which names
its file: 11582's writer's records (@1599428 on) lie right after `comum::asn::CConversorVersoesArquivos`'s vtable
(@1599288), 42 KB from the recorder's own (@1557240), so the writer is the converter's `.cpp`'s (unit 145's
`asn::GravaArquivo`), and a template of it in the recorder's header would be inlined by clang there instead. For a
linkonce callee, the kept copy's records are its first emitting object's.

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

A class your bodies need complete only to call a virtual slot through a pointer (a `std::shared_ptr` member whose
`Slot2()` you call, a control block that deletes through the destructor's slot) gets its head alone: the class, the base
clause RTTI gives and that slot, with a comment that no member is reconstructed, as
`src/uenux2/src/api/hwil/ifingerprepare.h` does for its control block's call of the deleting destructor. Its
`sizeof` is then wrong, so nothing may construct it; the first unit that needs a member adds the data members and the
records' declarations as above. A head a body returns or passes by value is not enough: the wasm signature follows the
class's layout, so an empty class comes back in nothing and a class of one scalar as that scalar (§R3 of
[reading.md](reading.md)). `comum::asn::CConversorEntidadeBU`'s inherited `DoDesconverte` (10272, `(i32 i32 i32)->()`)
lost its result pointer with `md::CEntidadeBU` declared `class CEntidadeBU {};`, scored `179 over 183` rows and no
longer merged into 731. Such a member waits for enough of the layout to give its signature, not for all of it: with a
head of three members (the entity header at +0, the phase at +20, the urna at +24), any layout returned in memory,
10272 matches (fragment 159 says so).

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
level, and writes no gap over a run of blank lines with no record below it. When the caller is a pending member, a
slot of a vtable our link holds, it has no stub (how-to step 9), so the line stays blank with nothing over it: name the
record and its function in the source's header comment and the `-pending.cpp` header (unit 123's
`crelatoriotesteimpressora.cpp`, line 173 for 11188).

Blank means blank. `stubs.py` takes any text on a record's line, a closing brace or a comment, for that function's
code: it drops the stub at step 9 and `stubs.py --check` passes. A `} // namespace vota` on line 80 of
`ctelascargo.cpp`, `CTelasCargo::GetTela`'s record (4135), took its stub; an edit above a record inside a class body
moved line 51 of `cpaperformbuilder.h` onto a comment and took 11006's. After step 9, list the file's recorded
functions against its stubs:

```sh
f=src/uenux2/src/app/vota/eleitor/comum/ctelascargo.cpp
awk -F'\t' -v f="${f#src/uenux2/}" 'index($2, f) {print $3, $6}' ledger/source-locations.tsv | sort -n
LC_ALL=C /usr/bin/grep -n '^// f' $f
```

On `main` the file is stub-only, and each of its three recorded functions (6718, 2386, 4135) has its stub. A recorded
function that is neither written in the file nor stubbed there is such a case, or a match or a pending member (check
`splat/matched.txt` and the `-pending.cpp` headers). A record past the file's last line needs
no padding: the stub goes after the end, and whoever writes that function lays out the lines up to it.
`src/uenux2/src/app/comum/dados/cfotos.cpp` is 32 lines, its records of 3755 are lines 39 and 51, and f3755's stub is
line 30 (`LC_ALL=C /usr/bin/grep -n '^// f3755 ' <file>`; bbf27ac1); `stubs.py --check` passes. A function in a slot of
a vtable our link holds has no stub at all (how-to step 9), so such an example holds only for a function no linked
vtable holds. A record inside a class body (a template
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

## P9. A band's order against landed members, two objects and a record

How-to step 3 ("The order of two members") holds a reviewer to the band's order inside one object. Three cases the rule
alone does not settle:

- **Landed members already out of order.** Run the check over every matched member of the object in the band. A new
  member goes where it adds no inverted pair; when no place keeps the order with all of them, put it where it adds the
  fewest, consistent with other lanes' new members, run the check over every band of the file (a move for one band can
  break another: 3272 and 3279), and name the pairs that stay inverted in the fragment, or fix the old pairs in the same
  commit with the splat build. Unit 197's `CLogVota` members 4546, 4542, 4541 and 4537 sit right after 4551, which
  keeps the band's order with 4556, 4551 and 4511 and leaves 12 pairs against 4535, 4529 and 4522, which unit 156 had
  already put out of order.
- **A run across two objects of files you chose.** A run of consecutive indices in one band orders the objects as well:
  arrange the definitions so the run reads in link order across them where a form with the same code exists, and say
  in the fragment which part of the order the run fixes. The uses-2 run 5558 down to 5552 spans
  `capplicationcontext.cpp.o` and `capplicationcontextstack.cpp.o` (unit 193).
- **A recorded function bounds the order.** The code the band puts above a recorded function has to fit in the lines
  above its record, since a gap is blank lines only and `stubs.py` writes no `#line` that goes back. Where it does not
  fit, the band's order is not the file's, and the file's comment says so: in unit 193, `Actions` (47 lines) ahead of
  the guard's constructor, whose record is at line 45 of `capplicationcontextstack.cpp`, would pass it.
