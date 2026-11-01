# Facts: unit fragments and their companion files

What the rules of `src/units/README.md` ("What a fragment holds", "Companion files") rest on: what a roots TU's
declarations and stand-ins do to the link, which bodies a companion object supplies, how a pending member shows in
the generated files, and what rebuilds a companion object. Each command runs from the repository root of a checkout
whose build is current (`make -n -C src link` says `Nothing to be done`), with Node 24 first on `PATH` for the ones
that run the toolkit; the try links write only under `build/out/try/<name>/`.

## U1. A roots TU declares a constructor as returning `int`: the object's signature, not the target's

In the WebAssembly C++ ABI a constructor and a non-deleting destructor return `this`. The target's type for 5526,
`(i32 i32 i32)->()` (`pnpm wasm fn ../target/vota_web_wasm.wasm 5526`, from `asmlift-wasm/`), is binaryen's
dead-argument elimination removing a result no caller used.
At 1885fb2c, unit 23's roots declared the `api::CMovie` constructor `int (int, int, int)` and dropped the result in both
their callers, and 5526 matched (one of the two went when unit 127 wrote a real caller, 8605). Declared `void`, the same
try, on a checkout at that commit, links with a warning and loses the constructor:

```sh
mkdir -p build/out/units-facts
git show 1885fb2c:src/units/23-uenux2-cmovie-roots.cpp | sed 's/^int w5526_root_0(int, int, int)/void w5526_root_0(int, int, int)/' > build/out/units-facts/void-roots.cpp
printf '5526\n' > build/out/units-facts/t5526.txt
TMPDIR=/tmp tools/round/try-tu.sh --name units-void-roots src/uenux2/src/api/gui/cmovie.cpp \
  --roots build/out/units-facts/void-roots.cpp --targets build/out/units-facts/t5526.txt --skip-units 23-uenux2-cmovie.mk
# wasm-ld: warning: function signature mismatch: _ZN3api6CMovieC1ENSt3__26vectorINS_11CMovieFrameENS1_9allocatorIS3_EEEERKNS_6SPointE
/usr/bin/grep -E 'CMovie|CriaFilme' build/out/try/units-void-roots/wasm-named/vota_web/vota_web_wasm.js.symbols
# 1960:signature_mismatch:api::CMovie::CMovie(std::__2::vector<api::CMovieFrame, std::__2::allocator<api::CMovieFrame>>, api::SPoint const&)
```

wasm-ld routes both calls to a trap stub named `signature_mismatch:<symbol>`, and the constructor leaves the link
(the grep finds no other CMovie function). The warning prints twice among the link's other lines, so it is easy to
miss.

## U2. Stand-in callers must differ from each other and from every target function

**Identical stand-ins merge.** binaryen merges byte-identical functions, so two stand-ins with the same body become
one caller, and the function they both call is inlined into the survivor. At 1885fb2c unit 23's second caller passed
`bloco + 12`; passing `bloco`, as the first passed `filme`, made the two bodies the same (on a checkout at that commit):

```sh
git show 1885fb2c:src/units/23-uenux2-cmovie-roots.cpp | sed 's/w5526_root_0(bloco + 12, quadros, tamanho)/w5526_root_0(bloco, quadros, tamanho)/' > build/out/units-facts/same-roots.cpp
TMPDIR=/tmp tools/round/try-tu.sh --name units-same-roots src/uenux2/src/api/gui/cmovie.cpp \
  --roots build/out/units-facts/same-roots.cpp --targets build/out/units-facts/t5526.txt --skip-units 23-uenux2-cmovie.mk
/usr/bin/grep -E 'CMovie|CriaFilme' build/out/try/units-same-roots/wasm-named/vota_web/vota_web_wasm.js.symbols
# 4605:(anonymous namespace)::CriaFilme(int, int, int)
```

The plain link had three functions there (`/usr/bin/grep -E 'CMovie|CriaFilme' build/out/wasm-map/vota_web/names.tsv`:
the constructor's C2 and both stand-ins); the try link kept one stand-in and no constructor.

**A stand-in that only forwards is a target function.** `int B(int p) { return D2(p); }` compiles to
`local.get 0; call D2; end`, the D2 of a derived class that adds no member: vota::CAssinadorVota's 7766 (7 B, a call of
1007) is exactly that. Unit 34's second stand-in destroys two objects instead. Written as a forwarder:

```sh
python3 -I -B -c "import sys; s=open(sys.argv[1]).read(); s=s.replace('void DestroiAssinadoresB(int primeiro, int segundo)\n{\n    w1007_root_0(primeiro);\n    w1007_root_0(segundo);\n}', 'int DestroiAssinadorB(int assinador)\n{\n    return w1007_root_0(assinador);\n}').replace('&DestroiAssinadoresB', '&DestroiAssinadorB'); open(sys.argv[2], 'w').write(s)" src/units/34-uenux2-cassinador-roots.cpp build/out/units-facts/return-roots.cpp
printf '7766\n1007\n4694\n' > build/out/units-facts/t7766.txt
TMPDIR=/tmp tools/round/try-tu.sh --name units-return-roots src/uenux2/src/app/comum/gravadores/cassinador.cpp \
  --roots build/out/units-facts/return-roots.cpp --targets build/out/units-facts/t7766.txt --skip-units 34-uenux2-cassinador.mk
# moved: 1 functions (1 up, 0 down or sideways)
#     7766       7 B app      none → addr/1
# 7766 7 B app/vota: none → addr/1 skeleton:10568 (anonymous namespace)::DestroiAssinadorB(int)
#     score 1 over 4 rows (same 3, replaced 1 [1 operand-only], inserted 0, deleted 0)
```

The one row that differs is the call, which step 8 names once 1007 is named; the splat scan would then match 7766
under the stand-in's name, and the splat build would verify it. The census's `moved:` list is where such a pair
shows first.

## U3. A roots TU that calls `std::make_shared<T>` matches `__shared_ptr_emplace<T>`'s destructors

Units 14, 27, 28 and 29 include their class's header and build it with `std::make_shared`, as the target's callers
do. That instantiates the control block `__shared_ptr_emplace<T>` in the roots object, and its D0 and D2 are the
target's: they match from there. The class's own inline members, which the roots instantiate too, stay the unit
object's, because the unit's sources come before `EXTRA_OBJS` on the link line (`LINK_OBJS` in `src/Makefile`) and
the first object that defines a linkonce function supplies it:

```sh
awk -F'\t' '$2 ~ /shared_ptr_emplaceIN3api(10CTextField|11CImageField|19CTextFieldMultiLine|20CTextFieldDoubleLine)ENS_9allocator.*D[02]Ev$|^_ZN3api(10CTextField|11CImageField|19CTextFieldMultiLine|20CTextFieldDoubleLine)D2Ev$/ {print $1, $2, $3}' build/out/wasm-map/vota_web/names.tsv
```

prints the eight emplace D0 and D2 with `app/14-…-roots.o`, `app/27-…-roots.o`, `app/28-…-roots.o` and
`app/29-…-roots.o`, and the classes' D2 with `app/uenux2/src/api/gui/ctextfield.cpp.o`, `ctextfielddoubleline.cpp.o`
and `ctextfieldmultiline.cpp.o`; `CImageField`'s D2 comes from `app/uenux2/src/api/gui/cimagefield.cpp.o`, where the vtable
is emitted (U4). The constructor itself does not need `make_shared`: the target builds a CMovie inside a
`make_shared` block too (unit 23's roots header, fn 1593), and unit 23's `__asm__`-label stand-ins match 5526.

The target builds some classes with `std::shared_ptr<U>(new T)` instead: the builder stores the vptr of
`__shared_ptr_pointer<T*, …>` (the vtable's address + 8) into a block of its own. 3768 and 7787 store
`CSqlConnection`'s, 11523 `CFileSeeder`'s:

```sh
python3 -I -c "
import json
for e in json.load(open('ledger/vtables.json')):
    if e['class'].startswith(('std::__2::__shared_ptr_pointer<api::CFileSeeder*', 'std::__2::__shared_ptr_pointer<ecourna::api::sql::sqlite::CSqlConnection*')): print(e['address'] + 8, e['functions'], e['class'][:60])"
# 1559008 [174, 144, 11539, 11538, 144] std::__2::__shared_ptr_pointer<ecourna::api::sql::sqlite::CS
# 1564560 [174, 144, 172, 11427, 144] std::__2::__shared_ptr_pointer<api::CFileSeeder*, std::__2::
(cd asmlift-wasm && for f in 11523 3768 7787; do printf '%s ' $f; pnpm --silent wasm fn ../target/vota_web_wasm.wasm $f 2>/dev/null | sed -n '/folded readout/,$p' | /usr/bin/grep -c -E '= (1564560|1559008);'; done)
# 11523 1
# 3768 1
# 7787 3
```

A roots file that builds the same `std::shared_ptr` stores the same vtable, and that template's members match from
the roots object as the `make_shared` ones do: `__get_deleter`, and for `CSqlConnection` `__on_zero_shared`. The
control-block members the roots objects supply, by kind, at 0b5f410:

```sh
awk 'NR==FNR { if (FNR>1 && $3 ~ /app\/[0-9]+-.*-roots\.o$/) r[$2]=$3; next } ($2 in r) && $2 ~ /__shared_ptr_(emplace|pointer)/ {k = ($2 ~ /emplace/) ? "emplace" : "pointer"; m = ($2 ~ /D0Ev$/) ? "D0" : ($2 ~ /D2Ev$/) ? "D2" : ($2 ~ /__on_zero_shared/) ? "__on_zero_shared" : ($2 ~ /__get_deleter/) ? "__get_deleter" : "other"; n[k " " m]++} END {for (x in n) print n[x], x}' \
  FS='\t' build/out/wasm-map/vota_web/names.tsv FS=' ' splat/matched.txt | sort -k2
# 31 emplace D0
# 31 emplace D2
# 5 emplace __on_zero_shared
# 22 pointer __get_deleter
```

`__on_zero_shared` of `__shared_ptr_emplace<T>` is a target function of its own only for some classes: of unit 77's
parts, the ones declared `final` have one (5966, 5969, 11958), and `CParteCargos` and `CParteEleitores` share 411 in
slot 2 (`ledger/vtables.json`).

A block's census pair is arbitrary among blocks alike but for the vptr: the D2s and D0s differ only there, so the census
takes any of them. At 4487d6b it pairs 9483, matched as `CTrng`'s block's D2, with ours 10211, `CMenuValidation`'s, whose
D2 the match list gives 10892 (`awk -F'\t' '$1==9483 {print $7, $10}' ledger/functions.tsv`). The check on a pair is its
kind. The index comes from the vtable line: each match is slot 0 or 1 of its class's vptr in `ledger/vtables.json`,
`evidence:vtable`.

## U4. The matches compiled in a companion object

The match lines whose symbol a unit's `-roots.o` or `-pending.o` defines (`names.tsv`'s object column):

```sh
awk 'NR==FNR { if (FNR>1 && $3 ~ /app\/[0-9]+-.*-(roots|pending)\.o$/) r[$2]=$3; next } ($2 in r) {print $1, r[$2]}' \
  FS='\t' build/out/wasm-map/vota_web/names.tsv FS=' ' splat/matched.txt
```

prints 218 lines at 0b5f410. Each is code a landed header defines, never a stand-in's own body:

```sh
awk 'NR==FNR { if (FNR>1 && $3 ~ /app\/[0-9]+-.*-(roots|pending)\.o$/) r[$2]=$3; next } ($2 in r) {k = (r[$2] ~ /pending/) ? "pending" : ($2 ~ /__shared_ptr_(emplace|pointer)/) ? "roots, control block" : "roots, other"; n[k]++} END {for (x in n) print n[x], x}' \
  FS='\t' build/out/wasm-map/vota_web/names.tsv FS=' ' splat/matched.txt | sort -k2
# 25 pending
# 89 roots, control block
# 104 roots, other
```

The tree roots, `src/app/roots_*.o`, have no `-roots.o` suffix, so that filter misses them. They hold 162 match lines at
0b5f410, and the same rule applies: code a landed header or a library defines, compiled at `APP_CXXFLAGS` like a
fragment's roots, except `roots_cbasetype.o` and `roots_vector.o`, at `UENUX2_CXXFLAGS` (`src/units/README.md` "Companion
files"):

```sh
awk 'NR==FNR { if (FNR>1 && $3 ~ /app\/roots_[a-z0-9]+\.o$/) r[$2]=$3; next } ($2 in r) {n[r[$2]]++} END {for (x in n) print n[x], x}' \
  FS='\t' build/out/wasm-map/vota_web/names.tsv FS=' ' splat/matched.txt | sort -rn
# 71 app/roots_boost.o
# 63 app/roots_rhvoice.o
# 10 app/roots_ecourna.o
# 9 app/roots_uenux2.o
# 9 app/roots_7zip.o
```

- the members of the control blocks the roots files build, from units 12, 14, 28, 29, 58, 65, 77, 78, 79,
  83, 84, 90 and 92 (U3);
- code of a header the roots files emit in the shapes of `src/units/README.md` "Companion files": an inline default
  of a virtual member (`api::IScreen::GetFontMetrics`, 8938, unit 19), and the members of classes and class templates
  with no key function that the roots build (units 67, 75, 79, 83, 92 and 100);
- the implicit and inline members of a class whose key function is pending, from the pending objects of units 26,
  29, 58, 59, 60, 62, 77 and 79. The pending member there is the class's key function (its first
  non-inline virtual member), so the vtable is emitted in the pending object, and with it every implicit or inline
  member the vtable names. Those bodies are the compiler's code for the class definition. When the key function lands
  in the class's source, they move with the vtable under the same symbols: unit 30's moved to `ctextfieldmt.cpp.o`
  when its `Draw` landed, and its pending file went.

The census pairs whose function of ours comes from a unit's roots object (`ledger/functions.tsv` `best_index`):

```sh
awk -F'\t' 'NR==FNR { if (FNR>1) obj[$1]=$3; next } FNR>1 && $6=="skeleton" && obj[$7] ~ /app\/[0-9]+-.*-roots\.o$/ {print $1, $7, $10, obj[$7]}' \
  build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv
```

prints 162 pairs at 0b5f410: 89 control-block members and 73 members of the headers the roots emit, none an
`(anonymous namespace)` stand-in:

```sh
awk -F'\t' 'NR==FNR { if (FNR>1) obj[$1]=$3; next } FNR>1 && $6=="skeleton" && obj[$7] ~ /app\/[0-9]+-.*-roots\.o$/ {print ($10 ~ /^\(anonymous/) ? "stand-in" : ($10 ~ /__shared_ptr_(emplace|pointer)/) ? "control block" : "header member"}' \
  build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv | sort | uniq -c
#   89 control block
#   73 header member
```

Neither command sees a stand-in that binaryen merged with another: the merged body's object in `names.tsv` is
`<binaryen>`, and its name is `byn$mgfn-shared$` and the first member's symbol. A roots file's stand-ins live in an
anonymous namespace, so search for that prefix as well, leaving out libc++abi's demangler, which lives in one too. At
0b5f410 five such bodies exist, and none is matched or paired (the indices move with the link):

```sh
awk -F'\t' '$3=="<binaryen>" && $2 ~ /^byn\$mgfn-shared\$_ZNK?12_GLOBAL__N_1/ && $2 !~ /itanium_demangle/ {print $1, substr($2, 1, 60)}' build/out/wasm-map/vota_web/names.tsv
# 1103 byn$mgfn-shared$_ZN12_GLOBAL__N_111CompartilhaIN3api5ITextEN
# 5131 byn$mgfn-shared$_ZN12_GLOBAL__N_118TextoCompartilhadoEPFNSt3
# 5132 byn$mgfn-shared$_ZN12_GLOBAL__N_112TextoFormatoEPFNSt3__212b
# 5135 byn$mgfn-shared$_ZN12_GLOBAL__N_121CriaParteMajoritariosENSt
# 5136 byn$mgfn-shared$_ZN12_GLOBAL__N_119CriaParteCandidatosENSt3_
/usr/bin/grep -E 'byn\$mgfn-shared\$_ZNK?12_GLOBAL__N_1' splat/matched.txt | /usr/bin/grep -cv itanium_demangle
# 0
awk -F'\t' 'NR==FNR { if ($3=="<binaryen>" && $2 ~ /^byn\$mgfn-shared\$_ZNK?12_GLOBAL__N_1/ && $2 !~ /itanium_demangle/) b[$1]; next } FNR>1 && $6=="skeleton" && ($7 in b)' build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv | wc -l
# 0
```

## U5. How a pending member shows in the symbol file and the scan

`make -C src splat-symbols` names the function in a slot of a vtable both links name (`evidence:vtable`,
`docs/reference/splat.md` §2), and a pending member's slot holds its trap. So when the trap is a function of its own
in our link, the symbol file names the target function after the trap's declaration, and the scan lists it as
`differs` against the trap, with the `-pending.o` as its object. A trap is one `unreachable`, and binaryen merges the
traps of one wasm type into one body, which then sits in the slots of several of our vtables: those votes disagree,
so no name is given and the member stays `no-candidate`.

```sh
awk -F'\t' '$1==11442 || $1==11469 || $1==11470 {print $1, $5, $11}' splat/scan.tsv     # at 4487d6b
# 11442 differs app/36-uenux2-cvisitantefoto-pending.o
# 11469 no-candidate -
# 11470 no-candidate -
/usr/bin/grep -cE 'func:11442;.*evidence:vtable' splat/symbol_addrs.txt
# 1
```

Which case a trap is shows in the plain link: the functions of the pending objects other than destructors, with the
number of table slots that hold each (at 4487d6b; the indices move with the link, and the objects with the landings):

```sh
python3 -I -c "
import sys; sys.path.insert(0, 'tools/extract'); import wasmmod
d = wasmmod.Module('build/out/wasm/vota_web/vota_web_wasm.wasm')._elem()
for line in open('build/out/wasm-map/vota_web/names.tsv'):
    i, name, obj = line.split('\t')[:3]
    if obj.endswith('-pending.o') and 'D0Ev' not in name and 'D2Ev' not in name:
        print(i, len([k for k, v in d.items() if v == int(i)]), name[:70], obj.split('/')[-1])
"
# 508 25 _ZN3api15CAjusteDataHora6AjustaERKNS_9CDateTimeE 101-uenux2-api-util-singletons-pending.o
# 962 11 _ZNK5comum3asn22CConversorHorarioVerao10DoConverteERKNS_2md13CHorarioV 107-uenux2-iconversorasn-pending.o
# 1596 6 _ZN4vota29CItemVisualizarCandidatosVota5Slot2Ev 102-uenux2-control-blocks-pending.o
# 3176 3 _ZN3api15CTimerScheduler11CreateTimerERKNSt3__26chrono8durationIxNS1_5 101-uenux2-api-util-singletons-pending.o
# 10346 1 _ZN5comum3asn14CVisitanteFoto5visitEiRKNSt3__212basic_stringIcNS2_11ch 36-uenux2-cvisitantefoto-pending.o
```

Unit 101's `Ajusta` trap is one body in 25 table slots: binaryen merged the pending traps of its wasm type into it, and
the merged ones have no name in `names.tsv`. None of them gets a name. The trap of 11442 was alone in its slot, so it
was named after its trap. Which case a member is can change in a function its unit never touched. A trap a
unit adds merges with one of its wasm type and takes that member's name and `differs` row. A member that lands leaves its
partner alone again: 11366 (unit 17) shared a body in two slots with 10900 (unit 84), and 10900 turned `differs` when
11366 matched. The name the symbol file gave 11442, `visit(int, const std::string&, AbstractData*, unsigned, unsigned)`,
was the one `src/asn1/asn1.h` declared, not its records' (`awk -F'\t' '$6 ~ /(^|,)11442(,|$)/ {print $5}'
ledger/source-locations.tsv | sort -u`). asn1.h declares the records' form since, and 11442 matches (unit 36).

## U6. An explicit specialization's trap beats the class template's instantiation without a word

A virtual member a class inherits from a class template, not overridden, is that template's member; when the
template's definition is not recovered, a `-pending.cpp` defines that one instantiation as an explicit specialization
with a trapping body. An explicit specialization is an ordinary (strong) definition, and the member the template's
definition instantiates is a linkonce (weak) one, so the link keeps the trap and says nothing:

```sh
mkdir -p build/out/units-facts/spec
printf '%s\n' 'template <class T> struct IBase {' '    virtual ~IBase() {}' '    virtual int Valor() const;' '};' \
  'template <class T> int IBase<T>::Valor() const { return 1; }' > build/out/units-facts/spec/t.h
printf '%s\n' '#include "t.h"' 'struct CDerivada : IBase<int> {};' 'int Usa(const IBase<int>& b) { return b.Valor(); }' \
  'int main() { CDerivada d; return Usa(d); }' > build/out/units-facts/spec/a.cpp
printf '%s\n' '#include "t.h"' 'template <> int IBase<int>::Valor() const { __builtin_trap(); }' > build/out/units-facts/spec/p.cpp
for f in a p; do TMPDIR=/tmp build/docker-build.sh em++ -O0 -std=c++20 -c /work/build/out/units-facts/spec/$f.cpp -o /work/build/out/units-facts/spec/$f.o; done
TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/units-facts/spec/a.o build/out/units-facts/spec/p.o | /usr/bin/grep Valor
# 000001c1 W _ZNK5IBaseIiE5ValorEv
# 00000001 T _ZNK5IBaseIiE5ValorEv
TMPDIR=/tmp build/docker-build.sh em++ -O0 /work/build/out/units-facts/spec/a.o /work/build/out/units-facts/spec/p.o -o /work/build/out/units-facts/spec/ap.js; echo $?
# 0  (and nothing else printed)
node build/out/units-facts/spec/ap.js 2>&1 | /usr/bin/grep -m1 RuntimeError
# RuntimeError: unreachable
```

So a specialization left in a `-pending.cpp` after the template's definition is written keeps trapping in the
vtable, and no link error points at it.

## U7. What rebuilds a companion object

A fragment's own rules name their prerequisites by hand, unlike the generic rules of `src/Makefile`, which depend on
every header of their tree (`ECOURNA_HDRS`, and `UENUX2_HDRS`, which holds the uenux2 and the ecourna headers).
The objects an edit of a fragment rebuilds, at 4487d6b (name them: `roots_asn1.o` rebuilds on any fragment, so a count
says nothing, and a companion's compile line does not end in `.o`):

```sh
for f in 26-uenux2-csigverifier 30-uenux2-ctextfieldmt 19-uenux2-iscreen; do
  echo "$f:"; make -n -C src link -W "$PWD/src/units/$f.mk" | /usr/bin/grep 'em++.* -c ' | /usr/bin/grep -oE -- '-o [^ ]+'; done
# 26-uenux2-csigverifier:
# -o build/out/app/26-uenux2-csigverifier-pending.o     (its pending rule names the fragment; its roots rule does not)
# -o build/out/app/asn1/roots_asn1.o
# 30-uenux2-ctextfieldmt:
# -o build/out/app/asn1/roots_asn1.o                    (its roots rule does not name it)
# 19-uenux2-iscreen:
# -o build/out/app/19-uenux2-iscreen-roots.o            (its roots rule does)
# -o build/out/app/asn1/roots_asn1.o
for h in src/asn1/asn1.h src/asn1/asn1_useful.h; do
  printf '%s ' $h; make -n -C src link -W $PWD/$h | /usr/bin/grep -c -- '-o [^ ]*36-uenux2-cvisitantefoto-pending.o'; done
# src/asn1/asn1.h 1
# src/asn1/asn1_useful.h 0                  (asn1.h includes it; the rule lists asn1.h only)
make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -c -- '-o [^ ]*cvisitantefoto.cpp.o'
# 0                                         (the generic uenux2 rule depends on no src/asn1 header)
```

So an edit of `src/asn1/asn1.h` rebuilds the ASN.1 runtime, the objects whose rules name `src/asn1` and the companions
that name it, and misses the other objects that include it. At 4487d6b the rebuild list holds 135 objects, 24 of them
uenux2's, and not unit 15's `cconversorhorariosurna.cpp.o`, whose rule names its fragment and the ecourna headers only,
though the source includes `asn1.h`:

```sh
make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -c 'em++.* -c '
# 135
make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -oE -- '-o [^ ]+\.o' | /usr/bin/grep -c 'app/uenux2/'
# 24
make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -c -- '-o [^ ]*cconversorhorariosurna.cpp.o'
# 0
TMPDIR=/tmp build/docker-build.sh sh -c "$(tools/round/try-tu.sh --print-flags src/ecourna/app/dados/asn/cconversorhorariosurna.cpp | sed -E 's/^[^:]*: //; s/ -c / -M /')" | tr ' ' '\n' | /usr/bin/grep -c '^src/asn1/asn1\.h$'
# 1
```

The objects of the link that hold a symbol of the `ASN1` namespace and that edit leaves alone, each a candidate to
link stale, are the ones to move aside by name before the rebuild: [workflow.md](workflow.md) §W15 has the byte search
that lists them (8 at 4487d6b, unit 15's converter among them), and its pattern for a module header.

The two header lists are empty inside a fragment. `src/Makefile` reads the fragments before it sets them, and make
expands a rule's prerequisites when it reads the rule (GNU Make 3.81, this machine's `make`):

```sh
/usr/bin/grep -nE '^-include .*units|^(UENUX2|ECOURNA)_HDRS :=' src/Makefile | cut -c1-60
# 126:-include $(filter-out $(addprefix $(ROOT)/src/units/,$(S
# 132:ECOURNA_HDRS := $(shell find $(ROOT)/src/ecourna -name '
# 144:UENUX2_HDRS := $(shell find $(ROOT)/src/uenux2 -name '*.
(mkdir -p build/out/units-facts/mk && cd build/out/units-facts/mk && printf 'include frag.mk\nHDRS := a.h b.h\n' > probe.mk && printf 't: $(HDRS)\n\t@echo "prereqs=[$^]"\n' > frag.mk && touch a.h b.h && make -f probe.mk t)
# prereqs=[]
```

The generic rules depend on every header of their tree, so a header edit, or a new header, rebuilds the whole tree,
included or not, with the companions whose rules name the header's directory: [workflow.md](workflow.md) §W15 counts
it and says how to list the objects a lane rebuilt.

## U8. A slot that holds `__cxa_pure_virtual` is a pure member the class declares

`comum::IInterfaceInit`'s target vtable is `[5898, 325, 11646, 12143, 12143, 12143, 12143, 12143]`
(`ledger/vtables.json`), with 12143 named `__cxa_pure_virtual` (`/usr/bin/grep -F '= func:12143;' splat/symbol_addrs.txt`)
and slot 1, 325, the trap clang gives an abstract class's deleting destructor. Unit 35 declares the five pure members
at slots 3 to 7 (named after their slot or their callers, `src/uenux2/src/app/comum/iinterfaceinit.h` says which), and
the symbol file gives our vtable the target's size: `/usr/bin/grep -F '_ZTVN5comum14IInterfaceInitE' splat/symbol_addrs.txt`
prints `… size:0x28 …`. Without them the class is concrete: clang gives a concrete class a deleting destructor with a
body where the target's slot 1 is the trap, and the vtable loses the five slots.

## U9. A class's typeinfo needs its base's, which only the base's key function emits

A derived class's typeinfo names its base's typeinfo. A base with a virtual member defined out of line emits its
typeinfo (and its vtable) only in the TU of its key function, so a class that overrides every slot of its base still
needs that TU; a base with no key function has its typeinfo emitted, weak, by every TU that needs it
([reading.md](reading.md) §R6). A probe: `IBase` with two out-of-line virtual members and no data member, `CDerived`
overriding both, and a `main` that builds a `CDerived`:

```sh
P=build/out/units-facts/typeinfo; mkdir -p $P
printf '%s\n' 'struct IBase {' '    virtual ~IBase() = default;' '    virtual int Slot2() const;' '    virtual int Slot3() const;' '};' \
  'struct CDerived final : IBase {' '    int Slot2() const override;' '    int Slot3() const override;' '};' > $P/h.h
printf '%s\n' '#include "h.h"' 'int CDerived::Slot2() const { __builtin_trap(); }' 'int CDerived::Slot3() const { __builtin_trap(); }' > $P/derived.cpp
{ cat $P/derived.cpp; printf '%s\n' 'int IBase::Slot2() const { __builtin_trap(); }' 'int IBase::Slot3() const { __builtin_trap(); }'; } > $P/base-too.cpp
printf '%s\n' '#include "h.h"' 'int main(int argc, char**) { IBase* p = new CDerived; int r = argc > 5 ? p->Slot2() : 0; delete p; return r; }' > $P/main.cpp
for f in derived base-too main; do TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$f.cpp -o /work/$P/$f.o; done
TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm $P/derived.o | /usr/bin/grep 5IBase
# 00000009 W _ZN5IBaseD2Ev
#          U _ZTI5IBase
TMPDIR=/tmp build/docker-build.sh em++ -Oz /work/$P/main.o /work/$P/derived.o -o /work/$P/a.js 2>&1 | /usr/bin/grep 'wasm-ld: error'
# wasm-ld: error: /work/build/out/units-facts/typeinfo/derived.o: undefined symbol: typeinfo for IBase
TMPDIR=/tmp build/docker-build.sh em++ -Oz /work/$P/main.o /work/$P/base-too.o -o /work/$P/b.js -Wl,--Map=/work/$P/b.map
/usr/bin/grep -oE '_ZTV5IBase|_ZTI5IBase|_ZNK5IBase5Slot[23]Ev' $P/b.map | sort | uniq -c
#    1 _ZTI5IBase
```

With the base's members defined as traps beside the class's (`base-too.cpp`), the object emits the base's vtable and
typeinfo (`D`), and the link keeps only the typeinfo: nothing stores the base's vptr, so its vtable and the two traps
are dropped. A target function whose slot is in a vtable the link drops keeps its stub (`src/README.md` "Stubs").

## U10. A member inline in the original, trapped as a key function: the same inline code, another object

A class with no key function emits its vtable, weak, in every TU that uses it; a trap for one of its virtual members
makes that member the key function, and the vtable strong in the trap's TU. A probe: `CRelatorio` with an inline
`TemParte` and `ImprimeParte`, either declared only and trapped (`pending.cpp`) or inline (`user.cpp`, which builds
one):

```sh
P=build/out/units-facts/nokey; mkdir -p $P
printf '%s\n' 'struct IParte {' '    virtual ~IParte() = default;' '    virtual void Imprime() const = 0;' '};' 'struct CRelatorio {' \
  '    virtual ~CRelatorio() = default;' '    virtual bool TemParte() const { return m_parte != nullptr; }' \
  '    virtual void ImprimeParte() const;' '    IParte* m_parte = nullptr;' '    int m_n = 0;' '};' > $P/pending.h
sed 's/virtual void ImprimeParte() const;/virtual void ImprimeParte() const { m_parte->Imprime(); }/' $P/pending.h > $P/inline.h
printf '%s\n' '#include "pending.h"' 'void CRelatorio::ImprimeParte() const { __builtin_trap(); }' > $P/pending.cpp
printf '%s\n' '#include "inline.h"' 'CRelatorio* Cria() { return new CRelatorio; }' > $P/user.cpp
for f in pending user; do TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$f.cpp -o /work/$P/$f.o; done
TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only $P/pending.o $P/user.o | /usr/bin/grep -E '_ZTV|:$'
# build/out/units-facts/nokey/pending.o:
# 00000000 D _ZTV10CRelatorio
# build/out/units-facts/nokey/user.o:
# 00000000 W _ZTV10CRelatorio
for o in pending user; do wasm-objdump -d $P/$o.o | awk '/ func\[/ {n=$3} /^ [0-9a-f]+:/ {sub(/^ [0-9a-f]+:[^|]*\| /, ""); sub(/call [0-9]+ /, "call "); b[n]=b[n] $0 "; "} END {for (n in b) print n, b[n]}' | sort > $P/$o.bodies; done
diff $P/pending.bodies $P/user.bodies | /usr/bin/grep -oE '^[<>] <[^>]*>'
# > <_Z4Criav>
# < <_ZNK10CRelatorio12ImprimeParteEv>
# > <_ZNK10CRelatorio12ImprimeParteEv>
```

The bodies, with object-local call indices dropped, differ only in `ImprimeParte` (the trap against the inline body)
and the user's own function: `TemParte`, the D2 and the D0 are the same code from either object. So a trap that
stands for an inline member decides which object of ours emits the vtable's members, not their bytes.

## U11. Who reaches a function through an `invoke_*` table slot

`ledger/callgraph.tsv` holds direct calls only, so a function an `invoke_*` thunk calls has no caller there, and
`pnpm wasm fn` lists its table slots without their users. The disassembly prints an import by its minified name
(`call 8 <a.i>`), and `ledger/import-names.json` gives the real one. A use of slot S is an `i32.const S` whose next call
is an `invoke_*` import:

```sh
python3 -I - target/vota_web_wasm.wasm 448 <<'END'
import json, re, subprocess, sys
wasm, slot = sys.argv[1], sys.argv[2]
names = json.load(open('ledger/import-names.json'))
invoke = {n for n, real in names.items() if real.startswith('invoke_')}
f, last = None, None
for line in subprocess.run(['wasm-objdump', '-d', wasm], capture_output=True, text=True).stdout.splitlines():
    if m := re.search(r' func\[(\d+)\]', line): f, last = m[1], None
    elif m := re.search(r'\| *i32\.const (\d+)$', line): last = m[1]
    elif (m := re.search(r'\| *call \d+ <a\.(\S+)>', line)) and last == slot and m[1] in invoke:
        print('func', f, '->', names[m[1]]); last = None
    elif '| call' in line: last = None
END
# func 1525 -> invoke_iii
# func 9256 -> invoke_iii
# func 9259 -> invoke_iii
# func 9538 -> invoke_iii
# func 9543 -> invoke_iii
# func 10205 -> invoke_iiiii
```

Slot 448 holds 5632 (`wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[448\] '`), which
takes four parameters and returns one, so only `invoke_iiiii` fits: 10205 is its caller. The other five pass 448 as
an integer that happens to equal the slot.

## U12. A class with no row in `ledger/vtables.json` can have a vtable

The extraction misses classes: 406 of the 2162 classes of `ledger/classes.json` have no row, and some of them have a
vtable in the target, `ASN1::GeneralizedTime` and `ecourna::app::dados::asn::CConversorConfiguracaoMunicipio` among
them. So no row is no evidence of no vtable.

```sh
python3 -I -c "import json; c=json.load(open('ledger/classes.json'))['classes']; n={e['class'] for e in json.load(open('ledger/vtables.json'))}; print(len(c), sum(x['name'] not in n for x in c))"
# 2162 406
```

A vtable is a zero offset-to-top word, then the typeinfo's address, then the slots, and its address point is 8 bytes
in. So the words equal to a class's typeinfo after a zero word find it. `ASN1::GeneralizedTime`'s typeinfo is 1149228
(`_ZTIN4ASN115GeneralizedTimeE = 0x11892c` in `splat/symbol_addrs.txt`):

```sh
python3 -I - target/vota_web_wasm.wasm 1149228 <<'END'
import struct, sys
sys.path.insert(0, 'tools/extract'); import wasmmod
base, img = wasmmod.Module(sys.argv[1]).memory_image(); t = int(sys.argv[2])
for o in range(4, len(img) - 3, 4):
    if struct.unpack_from('<I', img, o)[0] == t and struct.unpack_from('<I', img, o - 4)[0] == 0:
        print('vtable', base + o - 4, 'address point', base + o + 4)
END
# vtable 1149192 address point 1149200
```

The words from the address point less 8 are the offset to top, the typeinfo and the slots, which `wasm-objdump -x -j
Elem target/vota_web_wasm.wasm` resolves to functions ([asn1.md](asn1.md) §A9 lists these). `tools/libs/memimg.py`
writes the memory image, from address 0, to its second argument:

```sh
mkdir -p build/out/units-facts && python3 -I -B tools/libs/memimg.py target/vota_web_wasm.wasm build/out/units-facts/mem.bin > /dev/null
python3 -I -c "import struct; d=open('build/out/units-facts/mem.bin','rb').read(); print(struct.unpack('<6I', d[1149200-8:1149200+16]))"
# (0, 1149228, 2299, 7110, 7111, 7112)
```

The same read at a vptr a constructor stores gives the class's typeinfo, and so its name. A class missing its row gets
no `vtable` evidence for its slots, so its members wait for a census pair or a hand edit.
