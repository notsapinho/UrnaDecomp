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
Unit 23's roots declare the `api::CMovie` constructor `int (int, int, int)` and drop the result in both callers, and
5526 matches. Declared `void`, the same try links with a warning and loses the constructor:

```sh
mkdir -p build/out/units-facts
sed 's/^int w5526_root_0(int, int, int)/void w5526_root_0(int, int, int)/' src/units/23-uenux2-cmovie-roots.cpp > build/out/units-facts/void-roots.cpp
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
one caller, and the function they both call is inlined into the survivor. Unit 23's second caller passes `bloco + 12`;
passing `bloco`, as the first passes `filme`, makes the two bodies the same:

```sh
sed 's/w5526_root_0(bloco + 12, quadros, tamanho)/w5526_root_0(bloco, quadros, tamanho)/' src/units/23-uenux2-cmovie-roots.cpp > build/out/units-facts/same-roots.cpp
TMPDIR=/tmp tools/round/try-tu.sh --name units-same-roots src/uenux2/src/api/gui/cmovie.cpp \
  --roots build/out/units-facts/same-roots.cpp --targets build/out/units-facts/t5526.txt --skip-units 23-uenux2-cmovie.mk
/usr/bin/grep -E 'CMovie|CriaFilme' build/out/try/units-same-roots/wasm-named/vota_web/vota_web_wasm.js.symbols
# 4605:(anonymous namespace)::CriaFilme(int, int, int)
```

The plain link has three functions there (`/usr/bin/grep -E 'CMovie|CriaFilme' build/out/wasm-map/vota_web/names.tsv`:
the constructor's C2 and both stand-ins); the try link keeps one stand-in and no constructor.

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
and `ctextfieldmultiline.cpp.o`; `CImageField`'s D2 comes from `app/29-uenux2-cimagefield-pending.o`, where the vtable
is emitted (U4). The constructor itself does not need `make_shared`: the target builds a CMovie inside a
`make_shared` block too (unit 23's roots header, fn 1593), and unit 23's `__asm__`-label stand-ins match 5526.

## U4. The matches compiled in a companion object

The match lines whose symbol a unit's `-roots.o` or `-pending.o` defines (`names.tsv`'s object column):

```sh
awk 'NR==FNR { if (FNR>1 && $3 ~ /app\/[0-9][0-9]-.*-(roots|pending)\.o$/) r[$2]=$3; next } ($2 in r) {print $1, r[$2]}' \
  FS='\t' build/out/wasm-map/vota_web/names.tsv FS=' ' splat/matched.txt
```

prints 17 lines at 9271d74. Each is code a landed header defines, never a stand-in's own body:

- the D0 and D2 of `__shared_ptr_emplace<T>` from the roots of units 14, 27, 28 and 29 (U3);
- `api::IScreen::GetFontMetrics` (8938), the inline default of a virtual member, which unit 19's roots emit and
  address-take;
- the implicit destructors of `comum::CSigVerifier` (11178, 11176), `api::CImageField` (11099, 11098) and
  `api::CTextFieldMT` (10933, 10932), and `IFormField<IScreenMT>::GetTypeName` (11051) and the
  `IFormFieldBase<IScreenMT>` destructor (11052), from the pending objects of units 26, 29 and 30. The pending member
  there is the class's key function (its first non-inline virtual member), so the vtable is emitted in the pending
  object, and with it every implicit or inline member the vtable names. Those bodies are the compiler's code for the
  class definition. When the key function lands in the class's source, they move with the vtable under the same
  symbols.

The census pairs whose function of ours comes from a unit's roots object (`ledger/functions.tsv` `best_index`):

```sh
awk -F'\t' 'NR==FNR { if (FNR>1) obj[$1]=$3; next } FNR>1 && $6=="skeleton" && obj[$7] ~ /app\/[0-9][0-9]-.*-roots\.o$/ {print $1, $7, $10, obj[$7]}' \
  build/out/wasm-map/vota_web/names.tsv ledger/functions.tsv
```

prints 8 pairs at 9271d74, all of them `__shared_ptr_emplace<T>` destructors.

## U5. How a pending member shows in the symbol file and the scan

`make -C src splat-symbols` names the function in a slot of a vtable both links name (`evidence:vtable`,
`docs/reference/splat.md` §2), and a pending member's slot holds its trap. So when the trap is a function of its own
in our link, the symbol file names the target function after the trap's declaration, and the scan lists it as
`differs` against the trap, with the `-pending.o` as its object. A trap is one `unreachable`, and binaryen merges the
traps of one wasm type into one body, which then sits in the slots of several of our vtables: those votes disagree,
so no name is given and the member stays `no-candidate`.

```sh
awk -F'\t' '$1==9130 || $1==9133 || $1==10931 || $1==11097 || $1==11366 || $1==11442 || $1==11646 {print $1, $5, $11}' splat/scan.tsv
# 9130 no-candidate -
# 9133 no-candidate -
# 10931 no-candidate -
# 11097 no-candidate -
# 11366 differs app/17-uenux2-cconversororigemconfiguracao-pending.o
# 11442 differs app/36-uenux2-cvisitantefoto-pending.o
# 11646 differs app/35-uenux2-iinterfaceinit-pending.o
/usr/bin/grep -cE 'func:(11442|11366|11646);.*evidence:vtable' splat/symbol_addrs.txt
# 3
```

Which case a trap is shows in the plain link: the functions of the pending objects other than destructors, with the
number of table slots that hold each:

```sh
python3 -I -c "
import sys; sys.path.insert(0, 'tools/extract'); import wasmmod
d = wasmmod.Module('build/out/wasm/vota_web/vota_web_wasm.wasm')._elem()
for line in open('build/out/wasm-map/vota_web/names.tsv'):
    i, name, obj = line.split('\t')[:3]
    if obj.endswith('-pending.o') and 'D0Ev' not in name and 'D2Ev' not in name:
        print(i, len([k for k, v in d.items() if v == int(i)]), name[:70], obj.split('/')[-1])
"
# 708 14 _ZNK3api19CTextFieldMultiLine4DrawERNS_7IScreenE 14-uenux2-ctextfieldmultiline-pending.o
# 5038 2 _ZNK7ecourna3app5dados3asn22CConversorHorariosUrna10DoConverteERKNS1_1 15-ecourna-cconversorhorariosurna-pending.o
# 10496 1 _ZN5comum3asn14CVisitanteFoto5visitEiRKNSt3__212basic_stringIcNS2_11ch 36-uenux2-cvisitantefoto-pending.o
# 10497 1 _ZN5comum14IInterfaceInit17CurrentBootDeviceEv 35-uenux2-iinterfaceinit-pending.o
# 10510 1 _ZNK3api10IFormFieldINS_9IScreenMTEE11GetTypeNameEv 30-uenux2-ctextfieldmt-pending.o
# 10546 1 _ZNK5comum3asn28CConversorOrigemConfiguracao13DoDesconverteERKN23Modul 17-uenux2-cconversororigemconfiguracao-pending.o
```

Unit 14's `Draw` trap is one body in 14 table slots: binaryen merged the pending traps of its wasm type into it, and
the merged ones have no name in `names.tsv` (`/usr/bin/grep -c CTextFieldDoubleLine4Draw
build/out/wasm-map/vota_web/names.tsv` prints 0). 9133's trap shares its body with 9130's (unit 16). None of them gets
a name. The traps of 11366 (`(i32 i32)->(i32)`, an enum by value), 11442 and 11646 are alone in their slot, so each
is named after its trap. 10510 is no trap: it is `IFormField<IScreenMT>::GetTypeName`, matched as 11051 (U4). So the
name the symbol file gives 11442, `visit(int, const std::string&, AbstractData*, unsigned, unsigned)`, is the one
`src/asn1/asn1.h` declares, not its records' (`awk -F'\t' '$6 ~ /(^|,)11442(,|$)/ {print $5}'
ledger/source-locations.tsv | sort -u`).

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
Counted with `make -n` at 9271d74:

```sh
for f in src/units/26-uenux2-csigverifier.mk src/units/27-uenux2-ctextfield.mk src/units/19-uenux2-iscreen.mk; do
  printf '%s ' $f; make -n -C src link -W $PWD/$f | /usr/bin/grep -c 'em++.* -c '; done
# src/units/26-uenux2-csigverifier.mk 1     (its pending rule names the fragment)
# src/units/27-uenux2-ctextfield.mk 0       (neither of its companion rules does)
# src/units/19-uenux2-iscreen.mk 1          (its roots rule does)
for h in src/asn1/asn1.h src/asn1/asn1_useful.h; do
  printf '%s ' $h; make -n -C src link -W $PWD/$h | /usr/bin/grep -c -- '-o [^ ]*36-uenux2-cvisitantefoto-pending.o'; done
# src/asn1/asn1.h 1
# src/asn1/asn1_useful.h 0                  (asn1.h includes it; the rule lists asn1.h only)
make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -c -- '-o [^ ]*cvisitantefoto.cpp.o'
# 0                                         (the generic uenux2 rule depends on no src/asn1 header)
```

## U8. A slot that holds `__cxa_pure_virtual` is a pure member the class declares

`comum::IInterfaceInit`'s target vtable is `[5898, 325, 11646, 12143, 12143, 12143, 12143, 12143]`
(`ledger/vtables.json`), with 12143 named `__cxa_pure_virtual` (`/usr/bin/grep -F '= func:12143;' splat/symbol_addrs.txt`)
and slot 1, 325, the trap clang gives an abstract class's deleting destructor. Unit 35 declares the five pure members
at slots 3 to 7 (named after their slot or their callers, `src/uenux2/src/app/comum/iinterfaceinit.h` says which), and
the symbol file gives our vtable the target's size: `/usr/bin/grep -F '_ZTVN5comum14IInterfaceInitE' splat/symbol_addrs.txt`
prints `… size:0x28 …`. Without them the class is concrete: clang gives a concrete class a deleting destructor with a
body where the target's slot 1 is the trap, and the vtable loses the five slots.
