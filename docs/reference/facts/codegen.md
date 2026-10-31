# Facts: what a source form compiles to

Probes of source forms whose code the target shows: the order of a function's stores (a constructor's among them,
and what it says of the class that holds a member), what an object's disassembly does not settle and how to compare
two forms, a switch over virtual members, when a member's body is inlined, the order of a caller and its callee, what
a TU emitted first does to a frame, a C1 or D1 call `-fPIC` keeps, `-Oz`'s subtract of 0x100000, and how many copies
binaryen merges. `docs/how-to-decompile.md` steps 1 to 5 and 9 rely on these;
[reading.md](reading.md) holds what a target body says about declarations (parameters, destructors, linkage). Each probe
compiles with the uenux2 flags of the time, at `-O2` (`-O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing`; the tree builds
at `-O3` since, `docs/reference/app-flags.md`) in
the pinned image, from the repository root, and writes only under `build/out/codegen-facts/`. `wasm-objdump` is the
host's (wabt); `em++` and `llvm-nm` are the image's.

## C1. The stores follow the loads: values read first are stored in reverse

With no `volatile`, the backend schedules a function's stores: it keeps the order of stores that depend on one
another and schedules independent ones last to first. When the source reads every value before the first store (into
locals, or into the parameters of a call clang inlined), the independent stores come out in the reverse of the order
the source writes them; when it reads between stores, the order follows the reads. So the stores' order says where
the source read its values. A rectangle built from two points, by value, both ways:

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' '#include <algorithm>' 'typedef short TPosition;' 'struct SPoint { TPosition x, y; };' 'struct SRect { TPosition left, top, right, bottom; };' \
  'struct CLinha { SPoint m_inicio; SPoint m_fim; };' > $P/rect.h
printf '%s\n' '#include "rect.h"' 'SRect Rect(const CLinha& l)' '{' \
  '    return SRect{std::min(l.m_inicio.x, l.m_fim.x), std::min(l.m_inicio.y, l.m_fim.y),' \
  '                 std::max(l.m_inicio.x, l.m_fim.x), std::max(l.m_inicio.y, l.m_fim.y)};' '}' > $P/direct.cpp
printf '%s\n' '#include "rect.h"' 'SRect Rect(const CLinha& l)' '{' '    const TPosition x1 = l.m_inicio.x;' '    const TPosition y1 = l.m_inicio.y;' \
  '    const TPosition x2 = l.m_fim.x;' '    const TPosition y2 = l.m_fim.y;' \
  '    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};' '}' > $P/locals.cpp
for f in direct locals; do TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$f.cpp -o /work/$P/$f.o
  printf '%s: ' $f; wasm-objdump -d $P/$f.o | /usr/bin/grep -oE 'i32\.(load16_s|store16) 1 [0-9]+' | sed -E 's/i32\.load16_s 1 /ld /; s/i32\.store16 1 /st /' | tr '\n' ' '; echo; done
# direct: ld 4 ld 0 st 0 ld 2 ld 6 st 4 st 6 st 2
# locals: ld 4 ld 0 ld 2 ld 6 st 6 st 4 st 2 st 0
```

The aggregate is built in member order both times. Read into locals first, it is stored `+6, +4, +2, +0`, the
order target 11067 (`api::CLineField::Rect`) has, its coordinates at +24 to +30 of the object (from `asmlift-wasm/`,
Node 24 first on PATH):

```sh
pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11067 | /usr/bin/grep -E '^[0-9a-f]+ +i32\.(load16_s|store16)' | awk '{print $2, $4}' | tr '\n' ';'; echo
# i32.load16_s offset=28;i32.load16_s offset=24;i32.load16_s offset=26;i32.load16_s offset=30;i32.store16 offset=6;i32.store16 offset=4;i32.store16 offset=2;i32.store16 offset=0;
```

A constructor's arguments are values read first in the same way when it delegates. Two by-value strings moved into
members, by a plain constructor and by one that delegates to a constructor taking them by value again:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/ctor.cpp <<'EOF'
#include <string>
struct Plain {
    virtual ~Plain();
    Plain(std::string t, std::string s, bool h);
    std::string m_t, m_s;
    bool m_h;
};
Plain::Plain(std::string t, std::string s, bool h) : m_t(std::move(t)), m_s(std::move(s)), m_h(h) {}
struct Deleg {
    virtual ~Deleg();
    Deleg(std::string t, std::string s, bool h);
    Deleg(std::string t, std::string s, int p, bool h);
    std::string m_t, m_s;
    int m_p;
    bool m_h;
};
Deleg::Deleg(std::string t, std::string s, bool h) : Deleg(std::move(t), std::move(s), 0, h) {}
Deleg::Deleg(std::string t, std::string s, int p, bool h) : m_t(std::move(t)), m_s(std::move(s)), m_p(p), m_h(h) {}
EOF
TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/ctor.cpp -o /work/$P/ctor.o
for s in _ZN5PlainC1 _ZN5DelegC1ENSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEES6_b; do printf '%s: ' $s
  wasm-objdump -d $P/ctor.o | awk -v s="<$s" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' |
    /usr/bin/grep -E 'load|store|GOT' | awk '{print $1, $3}' | tr '\n' ';'; echo; done
# _ZN5PlainC1: global.get <GOT.mem._ZTV5Plain>;i32.store 0;i32.load 8;i32.store 12;i64.load 0;i64.store 4;i64.store 0;i32.store 8;i32.load 8;i32.store 24;i64.load 0;i64.store 16;i64.store 0;i32.store 8;i32.store8 28;
# _ZN5DelegC1E…S6_b: i64.load 0;i64.store 0;i32.load 8;i32.store 8;i64.load 0;i64.store 0;i32.load 8;i32.store 8;i32.store8 32;i32.store 28;i32.store 24;i64.store 16;i32.store 12;i64.store 4;global.get <GOT.mem._ZTV5Deleg>;i32.store 0;
```

`Plain` stores the vptr first and each member as it moves its argument (a by-value argument may alias `this`, so the
moves stay ordered). `Deleg` moves both arguments out (the loads and the zeroing stores into them) before any store
into the object, then stores the members last to first and the vptr last: the moves went into the inner
constructor's parameters, which clang inlined into values. Target 3660 (`api::CSubReport`'s constructor) has
`Deleg`'s shape, with one more member set (+28):

```sh
pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3660 | sed -n '/folded readout/,/^}/p' | /usr/bin/grep -E 'store|load'
#   l4 = i64.load[p1];
#   i64.store[p1] = 0;
#   …                                 # the same for p1+8, p2, p2+8
#   i32.store8[p0+36] = p3;
#   i64.store[p0+28] = 0;
#   i32.store[p0+24] = p1;
#   i64.store[p0+16] = l5;
#   i32.store[p0+12] = l6;
#   i64.store[p0+4] = l4;
#   i32.store[p0] = 1543180;
```

binaryen keeps the object's store order, so the object's disassembly shows it, and a lone link (`try-tu.sh
--single`) shows it too ([tool-traps.md](tool-traps.md) §X9).

**Which class holds a member.** The vptr store is a store like the others. A member that the base's constructor sets
is stored before the derived class's vptr in the source, so the reversal puts the vptr first; a member the derived
class's mem-initializer sets comes after its vptr, so it is stored first. The order therefore says which class holds
the member, which `ledger/classes.json` cannot, but only in a call shape where the two layouts differ. Probe
`basemember.cpp` (bb6f018), a field class with a base that holds its alignment or not, built from a literal and from a
by-value copy of a string:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/basemember.cpp <<'EOF'
// The vptr store against a member's: the member set by the base's constructor or by the derived class's.
#include <string>
struct IText {
    virtual ~IText();
    virtual int Alinhamento() const;
#if BASE
    explicit IText(int al) : m_al(al) {}
    int m_al;
#endif
};
struct CFixed final : IText {
#if BASE
    CFixed(std::string t, int al) : IText(al), m_t(std::move(t)) {}
#else
    CFixed(std::string t, int al) : m_al(al), m_t(std::move(t)) {}
    int m_al;
#endif
    std::string m_t;
};
IText *Literal() { return new CFixed("texto", 2); }                         // a literal
IText *Copy(const std::string &s) { return new CFixed(s, 2); }              // a by-value copy of a string
EOF
TMPDIR=/tmp build/docker-build.sh sh -c 'for b in 0 1; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DBASE=$b -c /work/build/out/codegen-facts/basemember.cpp -o /work/build/out/codegen-facts/basemember-$b.o; done'
for b in 0 1; do for f in _Z7Literalv _Z4CopyRKNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE; do printf 'BASE=%s %s: ' $b ${f:0:12}; wasm-objdump -d $P/basemember-$b.o | awk -v s="<$f>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk '/^global.get .*GOT.mem._ZTV/ {print "vptr"} /^i32.store 2 4$/ {print "+4"}' | tr '\n' ' '; echo; done; done
# BASE=0 _Z7Literalv: +4 vptr
# BASE=0 _Z4CopyRKNSt: +4 vptr
# BASE=1 _Z7Literalv: vptr +4
# BASE=1 _Z4CopyRKNSt: +4 vptr
```

From a literal the two layouts store in opposite orders; from a by-value copy of a string both store +4 first. The
target's `api::CFixedText` sites 10934 and 10548 store the vptr first, so `api::IText` holds the alignment
(`src/uenux2/src/api/gui/itext.h`), and 10958, which stores +4 first, is the copy's shape and says nothing. Before
reading a store order as evidence, compile both forms in the target function's own call shape.

**Assignments that meet after a branch.** The same reversal holds for two independent assignments of equal cost that
are read only after the branches join, and not across costs: in `simulador::CWasmImageSurfaceOps::ImageRect` (9289,
unit 69), the cases that assign two divides or two subtractions run in reverse of the source, and the cases that mix
a subtraction and a divide keep the divide last whichever order the source writes (the fragment
`src/units/69-uenux2-cwasmimagesurfaceops.mk` lists the forms measured). So such an order is evidence only between
equals.

**What the object shows and what it does not.** The object's store order is the module's, but two forms whose objects
differ can still give the same function: an `i32.const` added to `global.get __memory_base` is an offset into the
object's own literal data, which moves when the literals' order does and which the link's string merge replaces.
Probe `literals.cpp`, one choice written with its condition negated:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/literals.cpp <<'EOF'
// The same choice written with its condition negated: the object's literal offsets move, the code does not.
const char *Situacao(bool votou) {
#if NEG
    return !votou ? "Nao votou" : "Votou";
#else
    return votou ? "Votou" : "Nao votou";
#endif
}
EOF
TMPDIR=/tmp build/docker-build.sh sh -c 'for n in 0 1; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DNEG=$n -c /work/build/out/codegen-facts/literals.cpp -o /work/build/out/codegen-facts/literals-$n.o; done'
for n in 0 1; do wasm-objdump -d $P/literals-$n.o | awk '/<_Z8Situacaob>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' > $P/literals-$n.txt; done
paste -d'|' $P/literals-0.txt $P/literals-1.txt
# global.get 0 <env.__memory_base>|global.get 0 <env.__memory_base>
# i32.const 0|i32.const 10
# i32.const 6|i32.const 0
# local.get 0|local.get 0
# select|select
# i32.add|i32.add
# end|end
```

Mask those offsets (and the object-local `call` and `global.get` indices) before calling two objects different, and
compare function by function, not with `cmp` of the whole object ([reading.md](reading.md) §R5 has a template whose
spellings move a function within the object). A function that throws often reads `__memory_base` once into a local, and
adds each offset to the local: `local.get 0; i32.const 220; i32.add`, with no `global.get` beside the constant. Mask
that `i32.const` as well, and a function that differs on one row per record it loads has not changed.

**Five ways a form comparison lies.**

- **A copy's path moves every offset.** A record holds its file name, so a copy under another path has other offsets in
  every later row, and a variant compares as different with nothing changed. Compile the copy with
  `-ffile-prefix-map=/work/<the copy>=/home/rubio/tse/uenux2/<its tracked path>`, after the tree's flags. The unchanged
  copy is then `cmp`-equal to the landed object (0b5f410, with `F` the compile line of `make -n -C src link -W`):

  ```sh
  P=build/out/codegen-facts; cp src/uenux2/src/api/util/ctime.cpp $P/ctime-copy.cpp
  F='-O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -ffile-prefix-map=/work/src/uenux2=/home/rubio/tse/uenux2 -ffile-prefix-map=src/uenux2=/home/rubio/tse/uenux2 -Isrc -Isrc/uenux2/src -Isrc/asn1'
  TMPDIR=/tmp build/docker-build.sh sh -c "em++ $F -ffile-prefix-map=/work/$P/ctime-copy.cpp=/home/rubio/tse/uenux2/src/api/util/ctime.cpp -c /work/$P/ctime-copy.cpp -o /work/$P/ctime-mapped.o 2>/dev/null"
  cmp $P/ctime-mapped.o build/out/app/uenux2/src/api/util/ctime.cpp.o && echo same
  # same
  ```

  Without the flag the same `cmp` differs. Compile every variant of a comparison from one directory, with one name
  length, when you do not map them.
- **A constructor's C2 and a destructor's D2 compare zero rows.** `wasm-objdump -d` names one body by its `C1` or `D1`
  symbol, so a slice on `…C2…` is empty on both sides, and two empty lists compare equal. Treat 0 rows as a failed
  comparison, never as equal.
- **The edit may sit in a callee.** A template or helper is its own symbol in the object even when wasm-opt inlines it
  at link, so the caller compares `SAME`, with rows, while the edit moved `decodeTime` beside it. List the object's
  symbols first (`wasm-objdump -x <object>`), and compare the symbol the edit is in.
- **A compare's operand order is the link's.** binaryen can swap the operands of a symmetric compare, so an object that
  equals the target's rows says nothing. 995's `tag == makePrimitive(obj.getTag())` differs in the object and matches at
  link; swapping the source to equal the object gave `36 over 165 rows`. Read operand order in a link only.
- **A load can sink.** A load that only moves across a stretch with no store can be one binaryen sinks at link; when a
  form's object differs only there, link both before calling it evidence.

## C2. A switch whose cases call consecutive virtual members is one call through a computed slot

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' 'struct ITela {' '    virtual ~ITela();' '    virtual void Limpa();' '    virtual void Desenha(int, int, int);' \
  '    virtual void Led0();' '    virtual void Led1();' '    virtual void Led2();' '    virtual void Led3();' '};' \
  '[[noreturn]] void Falha(unsigned);' 'void Acende(ITela& t, unsigned led)' '{' '    switch (led) {' \
  '    case 0: t.Led0(); break;' '    case 1: t.Led1(); break;' '    case 2: t.Led2(); break;' '    case 3: t.Led3(); break;' \
  '    default: Falha(led);' '    }' '}' > $P/switch.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/switch.cpp -o /work/$P/switch.o
wasm-objdump -d $P/switch.o | sed -n '/<_Z6AcendeR5ITelaj>:/,/^$/p' | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | /usr/bin/grep -v '^$' | tr '\n' ';' | sed 's/;/; /g'; echo
# … block; local.get 1; i32.const 4; i32.lt_u; br_if 0; local.get 1; call 0 <env._Z5Falhaj>; unreachable; end;
#   local.get 0; local.get 0; i32.load 2 0; local.get 1; i32.const 2; i32.shl; i32.add; i32.load 2 16;
#   call_indirect 0 <env.__indirect_function_table> (type 1); end;
```

LLVM sinks the four identical calls into one `call_indirect` through `vtable + (led << 2) + 16`: the unsigned range
check `led < 4` is the `default:`, and 16 is the first case's slot (`Led0`, slot 4) times 4. No table of member
pointers is involved. A lift that shows such a computed slot (`*(int32_t*)((char*)*(int32_t*)p1 + (l3 << 2) + 32)`
after `(uint32_t)l3 >= 4u` in target 11050) reads as a switch over the members of slots 8 to 11. 11050 is
`api::CLedFieldMT::Draw`, the calls `api::IScreenMT`'s slots 8 to 11, and its `default` the `std::format` throw of
[reading.md](reading.md) §R13:

```sh
pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11050 | /usr/bin/grep -E 'i32.ge_u|table\['     # from asmlift-wasm/
# ;; vtable api::CLedFieldMT slot 2 (vtable @1579684, table[3276])
# 000016  i32.ge_u                                         | i32.ge_u
#   if (i32.ge_u(l3, 4)) {
#   table[i32.load[i32.add(i32.load[p1], i32.shl(l3, 2))+32]](p1);
```

## C3. An in-class member stays out of line in the object; one declared `inline` is inlined there

A member function defined in its class is inline but has no inline hint, and clang leaves a larger one out of line in
each object, a weak function; binaryen then inlines it only where it has one call site in the whole link
(`docs/reference/facts/tool-traps.md` §X1). The same member defined with the `inline` keyword gets the hint, and clang
inlines it in each object. The hint is LLVM's `inlinehint` attribute; [reading.md](reading.md) §R5 shows it on a
destructor, where it decides the deleting destructor's shape. An observer list's detach, in the class and
`inline`-specified, with one and two callers:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/obs.h <<'EOF'
#include <algorithm>
#include <mutex>
#include <vector>
template <typename T>
class IObservable {
public:
    void Detach(T* o)
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        m_observadores.erase(std::remove(m_observadores.begin(), m_observadores.end(), o), m_observadores.end());
    }
private:
    std::vector<T*> m_observadores;
    std::mutex m_mutex;
};
EOF
cat > $P/obs-inline.h <<'EOF'
#include <algorithm>
#include <mutex>
#include <vector>
template <typename T>
class IObservable {
public:
    void Detach(T* o);
private:
    std::vector<T*> m_observadores;
    std::mutex m_mutex;
};
template <typename T>
inline void IObservable<T>::Detach(T* o)
{
    std::lock_guard<std::mutex> trava(m_mutex);
    m_observadores.erase(std::remove(m_observadores.begin(), m_observadores.end(), o), m_observadores.end());
}
EOF
for h in obs obs-inline; do for u in A B; do
  printf '%s\n' "#include \"$h.h\"" 'struct CObservador;' "extern IObservable<CObservador> g_$u;" "void Solta$u(CObservador* p) { g_$u.Detach(p); }" > $P/$h-$u.cpp
  TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$h-$u.cpp -o /work/$P/$h-$u.o; done; done
for h in obs obs-inline; do printf '%s: ' $h; TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only $P/$h-A.o | /usr/bin/grep -c Detach; done
# obs: 1
# obs-inline: 0
printf '%s\n' '#include "obs.h"' 'struct CObservador;' 'IObservable<CObservador> g_A, g_B;' 'void SoltaA(CObservador*);' 'void SoltaB(CObservador*);' \
  'int main(int, char** argv) { SoltaA((CObservador*)argv[0]); SoltaB((CObservador*)argv[1]); return 0; }' > $P/main2.cpp
sed -e '/SoltaB(CObservador\*);/d' -e 's/ SoltaB((CObservador\*)argv\[1\]);//' $P/main2.cpp > $P/main1.cpp
for m in main1 main2; do TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$m.cpp -o /work/$P/$m.o; done
for h in obs obs-inline; do
  TMPDIR=/tmp build/docker-build.sh em++ -Oz /work/$P/main1.o /work/$P/$h-A.o -o /work/$P/$h-1.js --emit-symbol-map
  TMPDIR=/tmp build/docker-build.sh em++ -Oz /work/$P/main2.o /work/$P/$h-A.o /work/$P/$h-B.o -o /work/$P/$h-2.js --emit-symbol-map
  for n in 1 2; do printf '%s, %s caller(s): ' $h $n; /usr/bin/grep -c Detach $P/$h-$n.js.symbols; done
done
# obs, 1 caller(s): 0
# obs, 2 caller(s): 1
# obs-inline, 1 caller(s): 0
# obs-inline, 2 caller(s): 0
```

So the in-class form gives an inlined detach only while one function in the whole link calls it, and a second caller
leaves it out of line in both. When the target holds the same inlined code in two functions, a form clang inlines in
each TU is the one that keeps matching both; a form only binaryen inlines matches until the second caller lands.

The two copies need not be alike, and then this does not apply. `comum::IInterfaceSavd::ConverteHeader`'s loop is in
3829 and 3830: 3830 keeps the result pointer in a local through the loop (`l5 = i32.add(l4, 52); i32.store[l5+4] = 0`),
and 3829 folds it into the offsets (`i32.store[l5+24] = 0`), so one is binaryen's inlining and the other clang's. The
out-of-line form matches 3830 at `81 over 1168`, all operand-only, the `inline` form gives `166 over 1188`, and a scratch
second call site keeps the call at `227 over 1172`. So measure `inline` before writing it, and re-read the form when the
second caller lands (unit 95's fragment).

## C4. The order of a caller and its callee decides what binaryen makes of them

When two bodies differ in locals, or in what a pointer folds into, the order of the caller and the function binaryen
inlines into it can be the cause, with no difference in the object. A caller first gives binaryen's inliner another
round. Why, binaryen's source in the image does not show; the effect is measured:

- **Across objects.** `api::IImpressoraRelatorios::SetStyle` (10881) differs in local numbers only with
  `eueprintererror.cpp` before `iimpressorarelatorios.cpp` in its fragment's sources, `34 over 189`, and matches with the
  caller's object first, `15 over 185`, all operand rows; the objects between them are free (unit 80's fragment).
- **Inside one `.cpp`.** Only the order of the definitions moves. 3830 and the three functions it inlines: `379 over
  1191`, `130 over 1178`, and with the caller first `81 over 1168`, a match, where the first order also keeps a pointer
  argument in a local that the last folds into the loads (unit 95's fragment). 11405 goes from `34 over 247` to `24 over
  244` with `DoConverte` and `DoDesconverte` above their helpers (unit 93's), and 5745 from `47 over 298` to `29 over 293`
  (unit 110's).

A function with no record has a free line to do this with, and a function with records may move while each throw stays
on its record's line. Say in the fragment that the order is measured.

The same body can show a source form only here: `std::map<char, T>::find` in 5658 scores `25 over 92`, two locals
swapped, with `label.at(0)` as the argument or bound to a `const char&`, and `12 over 91` with `const char token`.

## C5. What a TU emitted first decides an inlined template's stack slots

`CPolySingleton<T>::set` (4879 for `api::ITimerScheduler`, 4890 for `api::ISystemDateTime`) inlines `std::format`,
whose parts are `always_inline`, and differs from the target in frame offsets alone, while 10876, the same template
over another class, matches. The source of `set` is not the cause. One line that makes the TU emit `instance()`'s format
code first, above `GetInst`, gives every frame offset of the target's (at 4487d6b, a variant object in a copy of the
link, [workflow.md](workflow.md) §W13):

    V=build/out/codegen-facts/frame; mkdir -p $V/src/uenux2/src/api/util $V/obj $V/wasm/f
    LC_ALL=C sed 's|^#line 18$|template class CPolySingleton<ITimerScheduler>;\n#line 18|' src/uenux2/src/api/util/itimerscheduler.cpp > $V/src/uenux2/src/api/util/itimerscheduler.cpp
    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -ffile-prefix-map=/work/$V/src/uenux2=/home/rubio/tse/uenux2 -Isrc -Isrc/uenux2/src -Isrc/asn1 -c /work/$V/src/uenux2/src/api/util/itimerscheduler.cpp -o $V/obj/its.o
    sed -e "s# app/uenux2/src/api/util/itimerscheduler.cpp.o # codegen-facts/frame/obj/its.o #" -e "s# -o wasm/vota_web/vota_web_wasm.js # -o codegen-facts/frame/wasm/f/vota_web_wasm.js #" build/out/wasm/vota_web/link.cmd > $V/wasm/f/link.cmd
    TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && $(cat $V/wasm/f/link.cmd)" > $V/wasm/f/link.log 2>&1
    cd asmlift-wasm
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 4879 ../build/out/wasm/vota_web/vota_web_wasm.wasm 2843 | /usr/bin/grep '^score'
      score 146 over 895 rows (same 749, replaced 146 [141 operand-only], inserted 0, deleted 0)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 4879 ../build/out/codegen-facts/frame/wasm/f/vota_web_wasm.wasm 2843 | /usr/bin/grep '^score'
      score 64 over 895 rows (same 831, replaced 64 [64 operand-only], inserted 0, deleted 0)

The 64 rows left are operands a full link re-points (the variant has no kinds table here); a private link with its own
kinds re-points both 4879 and 4890 `IDENTICAL`. The line only steers the compiler, so it never lands: the two rows stay
`differs` until a TU that emits a format body before them holds the instance. Which TU's copy the target keeps, its
records say: `awk -F'\t' '$2 ~ /cpolysingletonlist.h/ && $3==129 {print $1, $6}' ledger/source-locations.tsv` lists
4879's record, 1531292, right after 8302's, 1531180, in another object's run. That clang declares a callee at its first
mention, so that the inlined parts' allocas come in another order, is the reading; the scores are the measurement.

## C6. At `-fPIC` a call of an out-of-line C1 or D1 stays a call in its own TU, and no remark says so

Probe `ctorcall.cpp`, compiled at uenux2's flags, with `-fvisibility=hidden` added, and without `-fPIC`:

    // An out-of-line constructor and destructor, a plain function of the same cost, and their callers, all in one TU.
    struct T { T(); ~T(); int a[5]; };
    T::T() : a{1, 2, 3, 4, 5} {}
    T::~T() { a[0] = 0; }
    int Use() { T t; return t.a[1]; }
    int G(int* a) { a[0] = 0; return a[1]; }
    int UseG(int* a) { return G(a) + 1; }

    TMPDIR=/tmp build/docker-build.sh sh -c 'cd /work/build/out/codegen-facts; for v in "pic -fPIC" "hidden -fPIC -fvisibility=hidden" "nopic"; do set -- $v; n=$1; shift; em++ -O2 "$@" -std=c++20 -DNDEBUG -fno-strict-aliasing -Rpass=inline -Rpass-missed=inline -c ctorcall.cpp -o ctorcall-$n.o 2> ctorcall-$n.rpass; done'
    for n in pic hidden nopic; do printf '%s: inlined' $n; /usr/bin/grep -oE "'_Z[A-Za-z0-9_]+' inlined into" build/out/codegen-facts/ctorcall-$n.rpass | cut -d"'" -f2 | sed 's/^/ /' | tr -d '\n'; printf '; calls'; wasm-objdump -d build/out/codegen-facts/ctorcall-$n.o | /usr/bin/grep -oE 'call [0-9]+ <_Z[^>]+>' | cut -d' ' -f3 | sed 's/^/ /' | tr -d '\n'; echo; done
      pic: inlined _Z1GPi; calls <_ZN1TC1Ev> <_ZN1TD1Ev>
      hidden: inlined _ZN1TC2Ev _ZN1TD2Ev _Z1GPi; calls
      nopic: inlined _ZN1TC2Ev _ZN1TD2Ev _Z1GPi; calls
    /usr/bin/grep -oE "'_ZN1T[CD]2Ev' inlined into '_Z3Usev' with \(cost=-?[0-9]+, threshold=[0-9]+\)" build/out/codegen-facts/ctorcall-nopic.rpass
      '_ZN1TC2Ev' inlined into '_Z3Usev' with (cost=-30, threshold=337)
      '_ZN1TD2Ev' inlined into '_Z3Usev' with (cost=-35, threshold=337)

So at uenux2's flags a constructor or destructor of a cheap body, defined out of line beside its only caller, stays a
call of C1 or D1 and neither remark names it, while a plain function of the same cost beside it is inlined. Hidden
visibility, or no `-fPIC` (ecourna's flags), inlines all three at a cost below zero. What keeps the call is the C1 or D1
alias at the default visibility `-fPIC` gives ([app-flags.md](app-flags.md) §F5 has the same on a D1, by visibility
alone). So a caller's reload after such a call says nothing of the callee's TU. binaryen may still inline or remove the
callee in the link. Which of the two names an object's call holds, the disassembly does not say
([tool-traps.md](tool-traps.md) §X11).

## C7. `-Oz` turns an add of 0x100000 into a subtract

binaryen at `-Oz` writes `x + 1048576` as `x - (-1048576)`, since the negative constant's LEB is one byte shorter (3
bytes against 4), and leaves any other address alone:

    mkdir -p build/out/codegen-facts && printf '(module (memory 1) (func (export "f") (param i32) (result i32) (i32.add (local.get 0) (i32.const 1048576))) (func (export "g") (param i32) (result i32) (i32.add (local.get 0) (i32.const 1048580))))' > build/out/codegen-facts/add.wat
    TMPDIR=/tmp build/docker-build.sh sh -c '/emsdk/upstream/bin/wasm-opt /work/build/out/codegen-facts/add.wat -Oz -S -o - | grep -E "i32\.(add|sub)|i32\.const"'
        (i32.sub
         (i32.const -1048576)
        (i32.add
         (i32.const 1048580)

So a body that adds the address of an object our link puts exactly at 0x100000 has `i32.const -1048576; i32.sub` where
the target has `i32.const <address>; i32.add`, and its row reads `differs`: OpenSSL's `table_select` (4505) left
`match` on one merge's link when `k25519Precomp` started there. The shifted link's address is no power of two, so
`splat-kinds` sees nothing. Below 2^20 the positive constant is as short, so inside our data only this one address does
it, one object per link at most. What starts there, and the rows it hits (both print nothing at 4487d6b, where
`k25519Precomp` lies at 0x108c80):

    awk '$1 == "100000"' build/out/wasm-map/vota_web/vota_web_wasm.map
    awk -F'\t' '$5=="differs" && $6 ~ /ours [^|]*i32\.const -1048576/ {print $1}' splat/scan.tsv

No source is at fault, and moving data on purpose is tuning (`src/units/README.md` "Companion files", the order of a
roots file's lines): the next landing that moves the data clears it, and can bring it back on another object.

## C8. How many copies `--merge-similar-functions` needs

binaryen merges functions that differ in constants into one shared body only when enough of them share the shape. A
static pointer's destructor, `N` copies that differ in the address, with a D2 call before the free (`m`) or without
(`t`):

    mkdir -p build/out/codegen-facts && cat > build/out/codegen-facts/mgfn.py <<'EOF'
    # N copies of a static pointer's destructor, differing in the address only; "m" calls a D2 before the free, "t" does not.
    import sys
    kind, n = sys.argv[1], int(sys.argv[2])
    d2 = kind == 'm'
    print('(module')
    if d2:
        print(' (import "e" "d2" (func $d2 (param i32) (result i32)))')
    print(' (import "e" "free" (func $free (param i32)))')
    print(' (memory 1)')
    for i in range(n):
        a = 1000 + 8 * i
        call = '(drop (call $d2 (local.get 0))) ' if d2 else ''
        print(f' (func $f{i} (export "f{i}") (param i32)')
        print(f'  (local.set 0 (i32.load (i32.const {a})))')
        print(f'  (i32.store (i32.const {a}) (i32.const 0))')
        print(f'  (if (local.get 0) (then {call}(call $free (local.get 0)))))')
    print(')')
    EOF
    for k in m t; do for n in 2 3 4 5; do python3 -I -B build/out/codegen-facts/mgfn.py $k $n > build/out/codegen-facts/$k$n.wat; done; done
    TMPDIR=/tmp build/docker-build.sh sh -c 'cd /work/build/out/codegen-facts; for k in m t; do printf "%s:" $k; for n in 2 3 4 5; do printf " N=%s %s" $n $(/emsdk/upstream/bin/wasm-opt --enable-bulk-memory $k$n.wat --merge-similar-functions -S -o - | grep -c "func .byn.mgfn-shared"); done; echo; done'
      m: N=2 0 N=3 1 N=4 1 N=5 1
      t: N=2 0 N=3 0 N=4 1 N=5 1

`m` is fn 389's shape and `t` fn 349's (`pnpm --silent wasm fn ../target/vota_web_wasm.wasm 389` lists `call 244` and
`call 136`, 349's `call 136` alone): three copies form 389's shared body and four 349's, and two form neither, so two
singletons of a kind leave their destructors whole bodies where the target has 12-B thunks. The whole link agrees: unit
104's third member, `vota::CQuerReimprimirZeresima`, is what formed fn 389. A large body can merge from two (1565). The
target's callers give no bound on what forms the body in our link (389 has 49), and the members need not be matched:
count our link's copies before reading a thunk's `unresolved` row.
