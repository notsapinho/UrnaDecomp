# Facts: what a source form compiles to

Probes of source forms whose code the target shows: the order of a function's stores (a constructor's among them,
and what it says of the class that holds a member), what an object's disassembly does not settle, a switch over
virtual members, and when a member's body is inlined. `docs/how-to-decompile.md` step 3 relies on these;
[reading.md](reading.md) holds what a target body says about declarations (parameters, destructors, linkage). Each probe
compiles with the uenux2 flags (`-O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing`, `docs/reference/app-flags.md`) in
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
spellings move a function within the object). A load that only moves across a stretch with no store can also be one
binaryen sinks at link; when a form's object differs only there, link both before calling it evidence.

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
