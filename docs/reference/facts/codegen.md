# Facts: what a source form compiles to

Probes of source forms whose code the target shows: the order of a function's stores (a constructor's among them, and
what it says of the class that holds a member), what an object's disassembly does not settle and how to compare two
forms, a switch over virtual members, when a member's body is inlined, the order of a caller and its callee, what the
source's named values, a TU's first emissions and an inlined callee do to a frame and which temporaries share a slot, a
C1 or D1 call `-fPIC` keeps,
`-Oz`'s subtract of 0x100000, how many copies binaryen merges, what `new T()` clears, what a caller's temporaries say of
a parameter's form, a throw path's blocks, where its pad lies and what a `try` block is without exceptions, a loop clang
turns twice, a store in each arm of a branch or case, a condition's test order, what orders a function's blocks, and the
loads a declaration decides.
`docs/how-to-decompile.md` steps 1 to 5 and 9 rely on these; [reading.md](reading.md) holds what a target body says
about declarations (parameters, destructors, linkage). Each probe compiles with the uenux2 flags of its time, `-O2 -fPIC
-std=c++20 -DNDEBUG -fno-strict-aliasing`, or `-O3` where it says so (the tree builds at `-O3 -std=c++23` since,
[app-flags.md](app-flags.md); the probes marked bbf27ac1 or 182dc6c1 and C10's at those flags, each command giving its
own), in the pinned image, from the repository root, and writes only under `build/out/codegen-facts/`. `wasm-objdump` is
the host's (wabt); `em++` and `/emsdk/upstream/bin/llvm-nm` are the image's (a bare `llvm-nm` is not on its PATH). A
variant built through make instead, as an object of the tree, is removed by name before each make, and the make's output
must hold one compile line for it: make 3.81 compares whole seconds ([workflow.md](workflow.md) §W26).

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

**Where the reversal stops.** It is measured on stores whose values are loads, into one object. A store of a parameter
among stores of constants comes after them whatever the source's order: the three assignments of a state's
`StartState` in each of their six orders, at uenux2's `-O3`:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/stores.cpp <<'EOF'
struct F { virtual void s0(); virtual void s1(); virtual void Slot2(); };
struct S { virtual ~S(); S* m_next; char m_pad[20]; int m_t; bool m_b; F* m_form; void Start(); };
#define N m_next = this;
#define B m_b = true;
#define T m_t = 0;
void S::Start() { ORDER m_form->Slot2(); }
EOF
for o in 'N B T' 'N T B' 'B N T' 'B T N' 'T N B' 'T B N'; do n=$(echo $o | tr -d ' ')
  TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing "-DORDER=$o" -c /work/$P/stores.cpp -o /work/$P/stores-$n.o
  printf '%s: ' $n; wasm-objdump -d $P/stores-$n.o | sed -n '/<_ZN1S5StartEv>:/,/^$/p' | /usr/bin/grep -oE 'i32\.store8? [0-9] [0-9]+|call_indirect' | tr '\n' ';'; echo; done
# NBT: i32.store8 0 32;i32.store 2 28;i32.store 2 4;call_indirect;
# NTB: i32.store8 0 32;i32.store 2 28;i32.store 2 4;call_indirect;
# BNT: i32.store 2 28;i32.store8 0 32;i32.store 2 4;call_indirect;
# BTN: i32.store 2 28;i32.store8 0 32;i32.store 2 4;call_indirect;
# TNB: i32.store8 0 32;i32.store 2 28;i32.store 2 4;call_indirect;
# TBN: i32.store8 0 32;i32.store 2 28;i32.store 2 4;call_indirect;
```

The `this` store (+4) is last in every one, and 10490
(`CPedeAnoNascimentoSemBiometria::StartState`) stores +4 first, so its order is no evidence of a source order. Stores
into different temporaries that feed one call can come out in an order neither the source's nor its reverse explains:
3673's interval of 600 for `CreateTimer`, under six spellings of the argument (unit 120's fragment). Stores of
constants alone keep no source order either: 10405 (`CSuspensaoAutomaticaEleitor::ProcessTick`) written
`m_bSinalizado = true; m_contagem = 0;` (a byte at +24, an i64 at +16) stored the i64 first (`14 over 82`), and the
other way round matched (`7 over 78`, operand rows only; unit 152's fragment). Only a whole-link score decides such a
pair's source order.

**Store runs, and a branch binaryen folds.** Stores into one buffer can keep one order over every source order: 10967's
`CBmpConversor::CreateBitmapHeader` stored its header highest offset first in each order measured, so the target's two
descending runs (+2 +0, then +46 down to +6) meant a block boundary in clang's object where the target has no branch.
A test of an argument every caller passes as one constant makes one: it ends a block in the object and leaves no code
once binaryen inlines the callee and folds it. Its paths also decide what dead-store elimination trims: a zero fill
before it is trimmed past later stores only when no path from the fill reads memory first (a throw, a call or a return
there kept 1072 bytes from +6, the target's 1024 from +54). Measure candidate tests with the callee's object and a
second TU that passes the constant, linked at the build's link flags, then in the whole link (unit 22's fragment).

A zeroing the size of a `memset` (a `std::string`'s or a `std::vector`'s 12 bytes, an `i64` and an `i32` store) keeps
no source order either: it follows the constants the function used before it, since the backend reuses a constant
register for the store of 0. 6035 and 6036 (the external and internal flash's `uenux.db` paths) come from one form,
`(CPath::GetPathTrab(o) / "uenux.db").string()`, and differ only in `o`, 1 against 0 (e7d03612, from `asmlift-wasm/`):

```sh
for i in 6035 6036; do printf '%s: ' $i; pnpm --silent wasm fn ../target/vota_web_wasm.wasm $i 2>/dev/null | /usr/bin/grep -E '^[0-9a-f]+ +i(32|64)\.(store|const)' | awk '{print $2, ($3 ~ /align/ ? $4 : $3)}' | sed -n 3,7p | tr '\n' ';'; echo; done
# 6035: i32.const 1;i64.const 0;i64.store offset=8;i32.const 0;i32.store offset=16;
# 6036: i32.const 0;i32.const 0;i32.store offset=16;i64.const 0;i64.store offset=8;
```

Compare such an order only between bodies that pass the same constants before it (unit 381's fragment).

**A store's `align=` hint.** Two 16-bit values read before two adjacent 16-bit stores are joined by the backend into one
32-bit load and store at the first store's alignment; each stored right after its own load stays two `i32.store16`.
Probe `align.cpp` (182dc6c1): an `SPoint` of two `short`s at +52 of `M`, from `Src`'s +6 and +8, copied through a
`memcpy` into a local (0), read into two locals and built (1), or stored field by field (2):

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' '#include <cstring>' 'struct SPoint { short x, y; };' 'struct M { char pad[52]; SPoint p; };' 'struct Src { short pad[3]; short w, h; };' '#if FORM == 0' 'void F(M& m, const Src& s) { SPoint t; std::memcpy(&t, &s.w, 4); m.p = t; }' '#elif FORM == 1' 'void F(M& m, const Src& s) { const short w = s.w; const short h = s.h; m.p = SPoint{w, h}; }' '#else' 'void F(M& m, const Src& s) { m.p.x = s.w; m.p.y = s.h; }' '#endif' > $P/align.cpp
for f in 0 1 2; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/$P/align.cpp -o /work/$P/align-$f.o
  printf 'FORM=%s: ' $f; wasm-objdump -d $P/align-$f.o | awk '/<_Z1FR1MRK3Src>:/ {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -oE 'i32\.(load|store)(16_s|16_u|16)? [0-9] [0-9]+' | tr '\n' ';'; echo; done
# FORM=0: i32.load 1 6;i32.store 1 52;
# FORM=1: i32.load 1 6;i32.store 1 52;
# FORM=2: i32.load16_u 1 6;i32.store16 1 52;i32.load16_u 1 8;i32.store16 1 54;
```

A 32-bit store at a 4-byte alignment (`i32.store 2 52`) is a whole-object copy into an object whose alloca LLVM raised
to 4. 8605 (`CWasmResource::GetMovie`) holds the 2-byte form, and unit 127's fragment lists the forms that give it.

**Seven ways a form comparison lies.**

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
  length, when you do not map them: a longer name can cross an alignment step and move every later data address
  ([tool-traps.md](tool-traps.md) §X12 has the case and the count to take before reading such a diff).
- **A copy's base name names its dynamic initializer.** A TU with one (a static whose constructor runs at start-up,
  such as a singleton's `s_instance`) names it `_GLOBAL__sub_I_<base name>`, which no prefix map rewrites, so a copy
  under another name differs in that symbol and every offset after it. Keep the base name, in a directory of its own:

  ```sh
  P=build/out/codegen-facts; printf '%s\n' 'struct X { X(); };' 'X x;' > $P/ginit.cpp; cp $P/ginit.cpp $P/ginit-copy.cpp
  for b in ginit ginit-copy; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/$b.cpp -o /work/$P/$b.o
    wasm-objdump -x $P/$b.o | /usr/bin/grep -o '_GLOBAL__sub_I_[A-Za-z_.-]*' | sort -u; done
  # _GLOBAL__sub_I_ginit.cpp
  # _GLOBAL__sub_I_ginit_copy.cpp
  ```
- **The object renumbers and renames.** A slice by a C2 or D2 name is empty on both sides, which compares equal, and
  ` (type N)` and `env.` change with no code change: [tool-traps.md](tool-traps.md) §X12 has each, and the counts to
  read before a 0.
- **The edit may sit in a callee.** A template or helper is its own symbol in the object even when wasm-opt inlines it
  at link, so the caller compares `SAME`, with rows, while the edit moved `decodeTime` beside it. List the object's
  symbols first (`wasm-objdump -x <object>`), and compare the symbol the edit is in.
- **A compare's operand order is the link's.** binaryen can swap the operands of a symmetric compare, so an object that
  equals the target's rows says nothing. 995's `tag == makePrimitive(obj.getTag())` differs in the object and matches at
  link; swapping the source to equal the object gave `36 over 165 rows`. Read operand order in a link only. A compare
  of a load against a `local.get` flips at each `optimize-instructions` run (binaryen's `canonicalize` puts the get on
  the right, then the higher node id), so the link keeps clang's order when the function's runs are even: read the
  `icmp`'s operands in clang's IR (`-S -emit-llvm`), where LLVM's complexity rule sets them (a phi before a cast) and
  the source's order between equals (13550's current post, compared field by field as a pair, unit 391's fragment).
- **A load can sink.** A load that only moves across a stretch with no store can be one binaryen sinks at link; when a
  form's object differs only there, link both before calling it evidence.
- **A mask can go at link.** clang writes an `i32.and` with 65535 over a 16-bit result it returns zero-extended, and
  binaryen drops it when every value it masks is already that narrow, so a form whose object adds only such a mask
  gives the same module (1078, `CLocal::GetSecaoID`, scores the same over both forms of comum's ID types). A probe and a
  link of it:

  ```sh
  P=build/out/codegen-facts
  printf '%s\n' 'struct L { unsigned short m_id; bool m_ok; };' 'extern "C" unsigned short GetId(const L* l) { return l->m_ok ? l->m_id : 0; }' > $P/mask.cpp
  TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/mask.cpp -o /work/$P/mask.o
  TMPDIR=/tmp build/docker-build.sh em++ -Oz --no-entry -Wl,--export=GetId /work/$P/mask.o -o /work/$P/mask.wasm
  for f in $P/mask.o $P/mask.wasm; do wasm-objdump -d $f | sed -n '/<GetId>:/,/^$/p' | /usr/bin/grep -c 'i32.const 65535'; done
  # 1
  # 0
  ```

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

## C3. An in-class member stays out of line in the object; one declared `inline` gets a higher threshold

A member function defined in its class is inline but has no inline hint, and clang leaves a larger one out of line in
each object, a weak function; binaryen then inlines it only where it has one call site in the whole link
(`docs/reference/facts/tool-traps.md` §X1). The same member defined with the `inline` keyword gets the hint, which
raises the cost up to which clang inlines it in each object (the end of this section). The hint is LLVM's `inlinehint`
attribute; [reading.md](reading.md) §R5 shows it on a
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

The hint is a threshold, not a promise: a member that costs more stays out of line with the keyword or without it.
`-Rpass=inline -Rpass-missed=inline` on the caller's compile prints each call's cost and threshold:

```sh
P=build/out/codegen-facts; mkdir -p $P
c12=$(for i in 1 2 3 4 5 6 7 8 9 10 11 12; do printf 'e(x + %s); ' $i; done); c16="$c12$(for i in 13 14 15 16; do printf 'e(x + %s); ' $i; done)"
printf '%s\n' 'void e(int);' "struct S { void InClass(int x) { $c12 } inline void Hinted(int x); inline void Large(int x); };" "void S::Hinted(int x) { $c12 }" "void S::Large(int x) { $c16 }" 'void Use(S& s, int x) { s.InClass(x); s.InClass(x + 1); s.Hinted(x); s.Hinted(x + 1); s.Large(x); s.Large(x + 1); }' > $P/hint.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -Rpass=inline -Rpass-missed=inline -c /work/$P/hint.cpp -o /work/$P/hint.o 2>&1 | /usr/bin/grep -oE "'[A-Za-z_0-9]+' (not )?inlined into '[A-Za-z_0-9]+'.*\(cost=[0-9]+, threshold=[0-9]+\)" | sort | uniq -c
#    2 '_ZN1S5LargeEi' not inlined into '_Z3UseR1Si' because too costly to inline (cost=600, threshold=487)
#    2 '_ZN1S6HintedEi' inlined into '_Z3UseR1Si' with (cost=440, threshold=487)
#    2 '_ZN1S7InClassEi' not inlined into '_Z3UseR1Si' because too costly to inline (cost=440, threshold=375)
```

The thresholds move with the call site; in ecourna's converter of identities the unhinted one is 250, and 9116's
`CIdentificadorEleitor::Cria` costs 470 there (the remark on `cconversoridentificadoreleitor.cpp`'s compile), above
the hinted 325: `inline` decides no byte of it. Read the remark before writing the keyword.

## C4. The order of a caller and its callee decides what binaryen makes of them

When two bodies differ in locals, in what a pointer folds into, or in the blocks binaryen leaves around an inlined
callee's tail, the order of the caller and the functions binaryen inlines into it can be the cause, with no difference
in the object. Either order can be the target's, so try the other one, and again after each fix that moves rows other
than locals: the better order can flip. Quote an order's score with the state of the source it was measured on. The
other order is the two swapped with the rest in place: a caller moved to the top of its file passes every function
between, and each place can give other rows (5480, `api::CIniFile::Carrega`, scored 1184 first in its file and 1096
above `SetKey`, and matched right above `Interpreta`, the callee binaryen inlines into it: unit 379's fragment), so try
each place between the two and read the object's function list at each, since a callee that stays a call moves with
its caller ([reading.md](reading.md) §R9). Order reaches a body only through what binaryen inlines into it (a reading:
each case below inlines one): when every call of the body in `wasm-dis` of `r02-stripped.wasm` (below) is still a call
in the output, no order moves its locals, and the remainder is in the object (below, "Local numbers can come from
clang's object too"; 11876 kept its 18 calls, and eleven places in the module and five renumberings of its input
locals each scored `96 over 448` on a replay at ee244e6e). Why, binaryen's source in the image does not show; the
effect is measured, the caller first in these:

- **Across objects.** `api::IImpressoraRelatorios::SetStyle` (10881) differs in local numbers only with
  `eueprintererror.cpp` before `iimpressorarelatorios.cpp` in its fragment's sources, `34 over 189`, and matches with the
  caller's object first, `15 over 185`, all operand rows; the objects between them are free (unit 80's fragment). The
  three setters 11242 holds kept a `block … br 0` around their tails, `939 over 4456` (58 rows inserted, 73 deleted),
  until unit 155's two objects linked after unit 93's builder and unit 89's `clocal.cpp.o`: `230 over 4398`, none
  inserted (unit 155's fragment).
- **Inside one `.cpp`.** 3830 and the three functions it inlines: `379 over 1191`, `130 over 1178`, and with the caller
  first `81 over 1168`, a match, where the first order also keeps a pointer argument in a local that the last folds into
  the loads (unit 95's fragment). 11405 goes from `34 over 247` to `24 over 244` with `DoConverte` and `DoDesconverte`
  above their helpers (unit 93's), and 5745 from `47 over 298` to `29 over 293` (unit 110's).

The callee first, in these:

- **Inside one `.cpp`.** `CConversorVoto::DoConverte` (11355) above its static helper `ConverteTipo` scores `55 over
  329` (7 rows inserted, 7 deleted), and below it matches (unit 124's fragment). 3819's three helpers scored better
  after it (`653 over 2007` against `764 over 2041`) until one source fix, after which the helpers first gave `40 over
  1954` and then the match (unit 200's fragment).
- **Across objects.** `CConversorDadosCandidato::DoDesconverte` (11450) linked ahead of `util.cpp` scores `108 over
  1389`, the inlined `Utils::DesconverteSexo`'s result copied to another local, and after it matches (units 96 and 124).

A body that holds a chain inlined from several objects can need the order of all of them, not one swap: 4454 holds
five functions of four objects of unit 13's list and is unit 197's; the data's order of them all (`awk -F'\t' '$2 ~
/crdvvota\.cpp$|md\/rdv\/|celeitorvotando\.cpp$/ {print $1, $2}' ledger/source-locations.tsv | sort -n`:
`celeitorvotando.cpp`, `crdvvota.cpp`, then `md/rdv/` in name order) took it from `958 over 2759` to `562 over 2719` in
two steps. The two axes are one question when the chain spans a `.cpp` and another object: try each definition order
with each object order, not each alone. 2772 (`CQRCodeImagePaper`'s constructor, which holds its file's `MontaImagem`
and `cstringutils.cpp`'s `SetBit` inlined) scored `97 over 696` with `MontaImagem` above it and with its object before
`cstringutils.cpp.o`, each alone, and `44 over 689`, every row an operand, with both (on a replay, below, then the
link; unit 296's fragment). A library's objects are the same question: zlib's `crc32` (893) is a 14-byte call of
`crc32_z`, and with
zlib's objects ahead of minizip's our link kept `crc32` with `crc32_z` inlined (a block result where the target has `if
… return`); with minizip's first it keeps `crc32_z` whole, and eleven rows matched ([libraries.md](libraries.md) §B8,
fragment 06).

**Only orders a source can give count.** Objects take their list order; inside one `.cpp` a function takes its place at
the TU's first mention of it (how-to step 3, "The order of two members"), not at its definition; a template instance its
first user's place; a linkonce function's copy is the first object's on the link line that instantiates it. Two source
orders whose first mentions agree compile to one object, so `cmp` the objects before linking an order: 11419's three
members written `DoDesconverte`, `LeChave`, `Decifra` give the tree's object for `DoDesconverte`, `Decifra`, `LeChave`
byte for byte, as `DoDesconverte` mentions `Decifra` and `Decifra` `LeChave` (unit 335). The target's copy of a linkonce
callee names its object by its record, which follows that object's own records and vtables: 10273 holds
`IConversorASN<CodigoCargoConsulta, unsigned char>::Converte`, whose record (1556668) lies after
`app/comum/asn/util.cpp`'s run, an object that links after the caller in ours, and an explicit instantiation in the tree
root `src/app/roots_iconversorasn.cpp` holds that copy ahead of both (`831 over 5399` to a match, unit 321's fragment).

**Local numbers can come from clang's object too.** Read the object's locals for each form before linking: 11172's
object already held the target's swap of two loop variables, parameters dead by then that clang's register coloring
reused (`-mllvm -print-before=wasm-reg-coloring` on the TU's compile line shows their uses), and the application's test
nested in an outer `if`, not joined by `&&`, gave the target's (unit 179's fragment). Which values clang grouped shows
in three steps: align the two `pnpm wasm fn` readouts and list, per local, the other side's local at each use (where
one local of a side meets two of the other, the groups differ); on a replay (below), exchange two of the input's
locals over the stretch where their values live, which names the target's groups before any source is tried (11876:
`27 over 444`, every local row the target's); and `-mllvm -print-before=wasm-reg-coloring -mllvm
-print-after=wasm-reg-coloring` shows which register each value, `ARGUMENT_i32 0` among them, was merged into, with
`-mllvm -print-machine-bfi -mllvm -print-bfi-func-name=<mangled>` the block frequencies the colouring weighs (a reading
of LLVM's source: registers by summed use frequency, each into the first colour it does not overlap). Judge a form by
the group a value lands in, not by one local's index. And whether a member binaryen
inlines is static moves the caller's locals with the same instructions: 12040 (`CMostraQRCodeCertificado::StartState`)
scores `204 over 873` with its `CTelasVota` screen builder a `const` member under every order tried, and `47 over 853`,
every row an operand, with it static and called through the same `GetInst()` (scratch links of `link.cmd` with the
objects swapped, [workflow.md](workflow.md) §W13 "One variant object"); 12055 goes from `279 over 2368` to `201 over
2364` the same way. That dead-argument elimination drops the unused `this` before the inlining is a reading.

A function with no record has a free line to do this with, and a function with records may move while each throw stays
on its record's line. Say in the fragment that the order is measured. A function binaryen inlined into every caller has
no target index, so no band or ordinal places it, and when no record or data of its own names its file, the file is
free too: a measured order of it against its caller, in a whole link or a replay of the link's `wasm-opt` (below), is
the evidence for a TU linked before or after the caller's, and the fragment says the file is a choice and what was
measured (`vota::SorteiaTeclasTesteTeclado` in `ctesteteclado.cpp` after 11805's StartState, unit 217's fragment). The
same body can show a source form only here: `std::map<char, T>::find` in 5658 scores `25 over 92`, two locals swapped,
with `label.at(0)` as the argument or bound to a `const char&`, and `12 over 91` with `const char token`.

**Which place a moved object takes.** The target's data give the objects' order ([placing.md](placing.md) §P4). When a
move lands and which places count is `src/units/README.md` "Names"' rule; among those places that give the bytes, take
the one with the fewest objects out of the data's order against the moved one. Count over every object with target
data, not a window, which can flip the answer, and with the objects that have records and no vtable: ranked by their
vtables alone, the wrong place can win (a new report file's two places counted 202 and 205 by vtables, 268 and 241 with
records, fragment 372). This ranks each object of the plain link line by the lowest target address the symbol file
gives its vtables and typeinfos (`.data.rel.ro._ZT[VI]` in our map) or, with none, by its source's lowest `.cpp` record,
and counts at each place given, the object `x` moved before or after another (c3a97777):

```sh
python3 -I - /citensmenuvota.cpp.o here after:/ctelasvota.cpp.o <<'END'
import re, sys
# usage: python3 -I - <X suffix> <place>... [names] [bss]   place: here | before:<suffix> | after:<suffix>
xs, places = sys.argv[1], [a for a in sys.argv[2:] if a not in ('names', 'bss')]
order = list(dict.fromkeys(w for w in open('build/out/wasm/vota_web/link.cmd').read().split() if w.endswith('.o')))
t = {p[0]: int(p[2].rstrip(';'), 0) for p in (l.split() for l in open('splat/symbol_addrs.txt', encoding='latin-1'))
     if len(p) >= 3 and p[1] == '=' and re.fullmatch(r'0x[0-9a-f]+;', p[2])}
seg = r'\.bss\.([^)]*)' if 'bss' in sys.argv else r'\.data\.rel\.ro\.(_ZT[VI][^)]*)'
vt, rec = {}, {}
for l in open('build/out/wasm-map/vota_web/vota_web_wasm.map', encoding='latin-1'):
    m = re.search(r'(\S+?):\(' + seg + r'\)$', l)
    if m and m.group(2) in t: vt[m.group(1)] = min(vt.get(m.group(1), 1 << 40), t[m.group(2)])
for l in open('ledger/source-locations.tsv', encoding='latin-1'):
    p = l.split('\t'); f = p[1] if len(p) > 1 else ''
    if 'bss' in sys.argv or not p[0].isdigit() or not f.endswith('.cpp'): continue
    if f.startswith('/home/rubio/tse/uenux2/'): o = 'app/uenux2/' + f[23:] + '.o'
    elif '/src/ecourna/' in f: o = 'app/ecourna/' + f.split('/src/ecourna/', 1)[1].replace('/', '_') + '.o'
    else: continue
    rec[o] = min(rec.get(o, 1 << 40), int(p[0]))
both = {**rec, **vt}
X = [o for o in order if o.endswith(xs)]; assert len(X) == 1, X; X = X[0]
for spec in places:
    seq = order if spec == 'here' else [o for o in order if o != X]
    if spec != 'here':
        how, ys = spec.split(':', 1); Y = [o for o in seq if o.endswith(ys)]; assert len(Y) == 1, Y
        seq.insert(seq.index(Y[0]) + (how == 'after'), X)
    pos = {o: i for i, o in enumerate(seq)}
    for name, r in ((('bss', vt),) if 'bss' in sys.argv else (('vtables-only', vt), ('record-aware', both))):
        if X not in r: print(spec, name, 'skipped:', X, 'has no rank here'); continue
        out = sorted((pos[o], o) for o in seq if o != X and o in r and (pos[o] < pos[X]) != (r[o] < r[X]))
        print(spec, name, len(out), 'objects out of the data order against', X, 'at', pos[X], hex(r[X]))
        if 'names' in sys.argv and name != 'vtables-only': print('\n'.join(f'  {p} {hex(both[o])} {o}' for p, o in out))
END
# here vtables-only 57 objects out of the data order against app/uenux2/src/app/vota/operador/outrasopcoes/citensmenuvota.cpp.o at 29 0x177e34
# here record-aware 121 objects out of the data order against app/uenux2/src/app/vota/operador/outrasopcoes/citensmenuvota.cpp.o at 29 0x177e34
# after:/ctelasvota.cpp.o vtables-only 83 objects out of the data order against app/uenux2/src/app/vota/operador/outrasopcoes/citensmenuvota.cpp.o at 85 0x177e34
# after:/ctelasvota.cpp.o record-aware 158 objects out of the data order against app/uenux2/src/app/vota/operador/outrasopcoes/citensmenuvota.cpp.o at 85 0x177e34
```

Take the record-aware count. With `names` added, it lists the record-aware objects of each place with their positions
and target addresses: those listed at one place and not at the other are the pairs the move inverts or restores, and
for a file at two places they are the objects linked between them. A count the moved object has no rank for prints
`skipped`: one with records and no vtable has the record-aware line alone (`cqrcodeimagepaper.cpp.o` at c3a97777, 341
in unit 296's list and 332 before `cstringutils.cpp.o`). One whose only named data are `.bss` statics (a singleton's)
has neither: with `bss` the script ranks every object by its `.bss` names alone, records left out, and counts that
segment (`cestadoaudio.cpp.o`, 43 at the head of unit 110's list, 45 after `celeitores.cpp.o`); never mix it with the
other two. A place is a position between two objects: inside a list weighed, count every position (`before:` each of its
objects, `after:` the last), since the list's head can invert fewer pairs than the place beside a data neighbour (unit
159's two files: 273 at the head of unit 225's list, 276 beside `cvisitanteeleitor.cpp.o`, at 525b5b8a). Count on the
plain `build/out/wasm/vota_web/link.cmd` of the committed state: a home-made count over a link line that holds a variant
object under another path drops that object's pairs with no message (unit 278's move counted 478 and 31 so, against 515
and 33 over the plain line). The count reads which objects' data the symbol file names, so it moves as later landings
name data, with no object moving (unit 278's move: 515 agree and 33 inverted at b3b6d4bb, 537 and 39 on the merged link
at fac8e5ce); `src/units/README.md` "Names" says what a fragment states with it and when a landing counts again. Confirm
the chosen place with a scratch link of the plain `link.cmd` with the object moved ([workflow.md](workflow.md) §W13,
"One variant object"). The target's `.rodata` (`_ZTS` names, strings) orders apart, so never mix the two segments
([link-order.md](link-order.md) §L7 item 15 reads one object's run). A destination neighbour that is itself out of the
data's order with the objects crossed makes every crossed pair an inversion: `citensmenuvota.cpp` moved after
`ctelasvota.cpp`, its data neighbour, inverted more than it restored, with 6599 at `306 over 2151` either way, so it
stayed in unit 102's list. A function moved between two files that stay in place reorders no object: its code and the
linkonce data it emits change object, so read the target's neighbours of that data (§P4) and of the function in its band
(how-to step 3, rule 5), not a count over our order. 3675 (`api::AddInputMenuField`) emits
`__shared_ptr_emplace<api::CInputMenuField>`'s control block, whose vtable (1579316) follows
`cinteractiveformbuilder.cpp`'s own block (1579276), and its band puts it between `cframedtext.cpp`'s 3676 and
`cmtformbuilder.cpp`'s 3674. A new file whose data neighbours already sit out of the data's order in our link goes
between them where they are adjacent; `src/units/README.md` "Names" says which places a new file weighs and what its
fragment names.

**Trying orders on binaryen alone.** A relink costs about 40 s an order, and a chain of several inlined functions has
many. The link's own `wasm-opt -Oz` step can run alone instead: `link-map` writes it as line 3 of
`build/out/wasm-map/vota_web/replay.sh`, on `r02-stripped.wasm` beside it, and its last `wasm-opt` as line 7. Run on
copies, with both outputs and the symbol map moved to scratch (3c1ef19d, 6 s):

```sh
P=build/out/codegen-facts/replay; mkdir -p $P
sed -n 3p build/out/wasm-map/vota_web/replay.sh | sed 's#wasm-map/vota_web/r05\.#codegen-facts/replay/r05.#g' > $P/oz.sh
sed -n 7p build/out/wasm-map/vota_web/replay.sh | sed -e 's#--minify-imports-and-exports-and-modules ##' -e 's#wasm-map/vota_web/r10-named\.wasm -o wasm-map/vota_web/r13-named\.wasm#codegen-facts/replay/r05.wasm -o codegen-facts/replay/r13.wasm#' > $P/last.sh
TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && $(cat $P/oz.sh) && $(cat $P/last.sh)"
cmp $P/r05.wasm build/out/wasm-map/vota_web/r05.wasm && echo same
# same
```

`r05.wasm` is the link's byte for byte, before metadce and the last `wasm-opt`, which change throw sites and locals
(1150 scored `67 over 779` on `r05.wasm`, a copy of `new`'s result kept in a local, against the link's `65 over 777`),
so score `r13.wasm`: it gives the link's own scores, and keeps the imports' names, which the minify step left to the
glue (`pnpm wasm score` reads a minified name from a `.js` beside the module, and a module with none reads every throw's
import call as a differing row). Find the function through the symbol map, whose lines are `<index>:<input index>`: the
left counts the imports, as `pnpm wasm` does, and the right is the input's defined-function index, `names.tsv`'s
`ld_index` (its `post_oz_index` counts no imports). From `asmlift-wasm/`, 10689 against our
`CEscolheOpcao::ProcessInput` (`ld_index` 5765):

```sh
pnpm --silent wasm score ../target/vota_web_wasm.wasm 10689 ../build/out/codegen-facts/replay/r13.wasm $(awk -F: '$2==5765 {print $1}' ../build/out/codegen-facts/replay/r05.symbols) | /usr/bin/grep '^score'
# score 173 over 1348 rows (same 1175, replaced 165 [165 operand-only], inserted 5, deleted 3)     (the link's; r05.wasm gives 189 over 1364)
```

Then change the input and run it again: patch one function's bytes, add `--skip-pass=<pass>` (`rse`,
`inlining-optimizing`) to `oz.sh`, or move functions in the text. `wasm-dis` of `r02-stripped.wasm` calls each defined
function `$<ld_index>`, and a function binaryen inlined, which `names.tsv` does not list, has that index too: its
ordinal among the map's code inputs, `awk -v s=_ZN4vota14CConfirmaAudio '/ CODE$/ {c=1; next} c && / [A-Z]+$/ {exit} c
&& /:\(/ {if (index($0, s)) print n, $NF; n++}' build/out/wasm-map/vota_web/vota_web_wasm.map` prints `GetInst`'s 5662
beside the members `names.tsv` keeps. Assemble the edited text with `-g`, which keeps each `$N` and so the symbol map's
right column; without it the map names each function by its new position. The unedited round trip gives `r05.wasm` byte
for byte:

```sh
sed 's#wasm-map/vota_web/r02-stripped\.wasm#codegen-facts/replay/in.wasm#' $P/oz.sh > $P/oz-in.sh
TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && /emsdk/upstream/bin/wasm-dis wasm-map/vota_web/r02-stripped.wasm -o codegen-facts/replay/in.wat && /emsdk/upstream/bin/wasm-as --all-features -g codegen-facts/replay/in.wat -o codegen-facts/replay/in.wasm && $(cat $P/oz-in.sh)"
cmp $P/r05.wasm build/out/wasm-map/vota_web/r05.wasm && echo same
# same
```

`-Oz` runs its function passes over every function first, then `--dae-optimizing` and `--inlining-optimizing`, which run
them again, `precompute-propagate` first, on each function they changed. So a caller's locals can be decided in the
first round, before any inlining (13550's zero sets: `rse` drops them there from a value in a local of its own and keeps
them from one in a reused local), and `--skip-pass` takes a pass out of every round. A function extracted with its
callees and replayed with plain `--inlining` is no replay: two forms of 13550 scored 293 and 345 rows off so, against
the link's 99 and 297. Replay the whole module. A text written with `-g` after `coalesce-locals` does not assemble
again: the name section keeps the old local names, two locals print as one, and `wasm-as` stops on `local names must be
unique`; drop the name section's local names (subsection 2) before `wasm-dis`.

Compare two replays function by function with `pnpm wasm score`, never by their raw code bytes: two modules with other
function counts renumber every `call` past the difference, and a body with no change of its own differs. 652's eight
inlined functions took the target's locals with `GetInst` above the constructor and the dispatcher above both screen
builders, which one source change and one relink confirmed (`144 over 2051`, all operands); patching LLVM's local
numbers in 10689's callee left the output unchanged, so binaryen, not the object, decides 10689's locals.

A replay shows the end state only. To see in which pass and which round a function's locals form, build binaryen at
the image's commit (b9c72894, [toolchain.md](../toolchain.md)) with a print added after each function pass, and run it
in place of the image's `wasm-opt`. The image has cmake, make and g++ (the Mac mini's host has no cmake); the build
takes about five minutes at `-j4`, and its `-Oz` gives the link's `r05.wasm` byte for byte, which is the check to run
before reading a trace (b3236f02's link, 10 s):

```sh
git clone -q --filter=blob:none https://github.com/WebAssembly/binaryen.git build/out/binaryen && git -C build/out/binaryen checkout -q b9c72894
TMPDIR=/tmp build/docker-build.sh sh -c 'cd /work/build/out/binaryen && mkdir -p out && cd out && cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_FUZZTEST=OFF -DBUILD_STATIC_LIB=ON -DENABLE_WERROR=OFF && make -j4 wasm-opt wasm-as wasm-dis'
P=build/out/codegen-facts/replay; mkdir -p $P
sed -n 3p build/out/wasm-map/vota_web/replay.sh | sed -e 's#^/emsdk/upstream/bin/wasm-opt#binaryen/out/bin/wasm-opt#' -e 's#wasm-map/vota_web/r05\.#codegen-facts/replay/native-r05.#g' > $P/oz-native.sh
TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && $(cat $P/oz-native.sh)"
cmp $P/native-r05.wasm build/out/wasm-map/vota_web/r05.wasm && echo same
# same
```

The print itself is a patch to binaryen's pass runner (one function, named in the environment, printed after every
function pass of every nested runner) and to coalesce-locals (its locals, copies, interferences, order and choice);
it is not in the tree yet. A trace of 13550 showed the round-1 decision of its locals and a compare's flips (§C1)
that no replay could.

## C5. A frame's offsets: which values the source names, and what a TU emitted first

The first local or temporary the source creates takes the highest offset, so which value is a named local moves the
frame. `api::CDateTime::FormatCurrentDate` (5472) keeps its `CDateTime` at +16 and the `CDate` copy at +8, which a
named `CDateTime` gives and a temporary does not:

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/frame.cpp <<'EOF'
#include <string>
struct CDate { int d[2]; ~CDate(); std::string Format(const char*) const; };
struct CDateTime { long long t; int x[2]; ~CDateTime(); CDate GetData() const; };
CDateTime Now();
std::string Temp(const char* f) { return Now().GetData().Format(f); }
std::string Named(const char* f) { const CDateTime agora = Now(); const CDate data = agora.GetData(); return data.Format(f); }
EOF
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/$P/frame.cpp -o /work/$P/frame.o
wasm-objdump -d $P/frame.o | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | awk '/ func\[/ {printf "%s%s", (n++ ? "\n" : ""), $3} /^i32.const/ {c=$2} /call .*D1Ev/ {printf " %s +%s", ($3 ~ /CDateTime/ ? "CDateTime" : "CDate"), c} END {print ""}'
# <_Z4TempPKc>: CDate +24 CDateTime +8
# <_Z5NamedPKc>: CDate +8 CDateTime +16
```

(Each destructor's `this` is the frame offset of its object.) In the whole link 5472 and 5473 match with the named
local (`src/uenux2/src/api/util/cdatetime.cpp`).

Created means allocated, not evaluated: in `b.Move(Corner(a.Adjust()))` the temporary for `Corner`'s result is created
before the one for `Adjust`'s, which is evaluated first, so a call's result sits above its argument, where named locals
follow their declarations (2770, `CInputMenuField`'s, has the rectangle at +4 below the point at +12):

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' 'struct SPoint { short x, y; SPoint(short a, short b) : x(a), y(b) {} };' 'struct SRect { short l, t, r, b; SRect Adjust() const; void Move(const SPoint&); };' 'static SPoint Corner(const SRect& r) { return SPoint(r.l, r.b); }' 'void Temp(SRect& a, SRect& b) { b.Move(Corner(a.Adjust())); }' 'void Named(SRect& a, SRect& b) { const SRect r = a.Adjust(); b.Move(SPoint(r.l, r.b)); }' > $P/nested.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -c /work/$P/nested.cpp -o /work/$P/nested.o
wasm-objdump -d $P/nested.o | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | awk '/ func\[/ {printf "%s%s", (n++ ? "\n" : ""), $3} /^i32.const/ {c=$2} /call .*Adjust/ {printf " SRect +%s", c} /call .*Move/ {printf " SPoint +%s", c} END {print ""}'
# <_Z4TempR5SRectS0_>: SRect +4 SPoint +12
# <_Z5NamedR5SRectS0_>: SRect +8 SPoint +4
```

So a value above the one it is built from can be such a nested call, with no named local, before it is an inlined
helper's locals (below).

That order is each function's before clang's inlining: a callee clang inlines brings its locals in above the caller's
own, though the caller creates its own first. A loop's temporary written in place sits below two locals made before
the loop, and the same loop in a helper clang inlines puts it above them (bbf27ac1):

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/inlframe.cpp <<'EOF'
struct Item { int w[13]; Item(int); ~Item(); };
struct List { int w[4]; List(); ~List(); void Add(const Item&); };
struct Conv { int w[2]; Conv(); ~Conv(); };
static inline void Fill(List& l, int n) { for (int i = 0; i < n; i++) { Item t(i); l.Add(t); } }
void Loop(int n) { List l; Conv c; for (int i = 0; i < n; i++) { Item t(i); l.Add(t); } }
void Inlined(int n) { List l; Conv c; Fill(l, n); }
EOF
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/inlframe.cpp -o /work/$P/inlframe.o
wasm-objdump -d $P/inlframe.o | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | awk '/ func\[/ {printf "%s%s", (n++ ? "\n" : ""), $3} /^i32.const/ {c=$2} /call .*(List|Conv|Item)C1/ {s=$0; sub(/.*_ZN[0-9]/, "", s); sub(/C1.*/, "", s); printf " %s +%s", s, c} END {print ""}'
# <_Z4Loopi>: List +64 Conv +56 Item +4
# <_Z7Inlinedi>: List +12 Conv +4 Item +28
```

11394 (`comum::asn::CConversorEstadoGeralGap::DoConverte`) keeps its loop's 52-byte temporary at +28, above the
converter at +24 and the list at +4 that it creates before the loop: the second shape, a callee clang inlined (an
algorithm, a lambda or a helper), not a declaration order. Such a helper is a reading of the target's frame, not
scaffolding: write it with its name and linkage marked chosen, citing this section (2383's file-static helper in
`ctelasvota.cpp`, unit 110's fragment, the only form measured with the target's allocation order).

**Which temporaries share a slot.** Stack colouring merges only slots that carry lifetime markers. A call's result the
source drops, written as a statement of the function, gets an alloca with none, so it keeps a slot of its own for the
whole function; the same calls in a callee clang inlines get markers, and their slots merge (e7d03612):

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' 'struct SF { void* p; void* c; ~SF(); };' 'struct B { SF Add(int); };' 'static inline void Rect(B& b, int i) { b.Add(i); }' 'void Stmt(B& b) { b.Add(1); b.Add(2); b.Add(3); }' 'void Named(B& b) { SF a = b.Add(1); SF c = b.Add(2); }' 'void Helper(B& b) { Rect(b, 1); Rect(b, 2); Rect(b, 3); }' > $P/dropped.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/$P/dropped.cpp -o /work/$P/dropped.ll && awk '/^define/ {f=$0; sub(/.*@/, "", f); sub(/\(.*/, "", f)} /alloca/ {a[f]++} /llvm.lifetime.start/ {l[f]++} END {for (f in a) print f, "allocas", a[f], "lifetime starts", l[f]+0}' $P/dropped.ll | sort
# _Z4StmtR1B allocas 3 lifetime starts 0
# _Z5NamedR1B allocas 2 lifetime starts 3
# _Z6HelperR1B allocas 3 lifetime starts 3
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/dropped.cpp -o /work/$P/dropped.o && wasm-objdump -d $P/dropped.o | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | awk '/ func\[/ {printf "%s%s", (n++ ? "\n" : ""), $3} /global.get 0/ {g=1} g && /^i32.const/ {printf " frame %s", $2; g=0} END {print ""}'
# <_Z4StmtR1B>: frame 32
# <_Z5NamedR1B>: frame 16
# <_Z6HelperR1B>: frame 16
```

So a frame larger than the target's, with every dropped result in a slot of its own, points at calls the target made
inside a helper clang inlined: 3064 (`CTelasVota::CriaTelaVotoCargoSemCandidato`) and the footers 1102 and 1190 took the
target's offsets only with their adders in internal helpers, a `void` one for 1102's and 1190's rectangles (unit 378's
fragment). The argument temporary of a by-value class parameter has no marker either, so it keeps a slot of its own,
below the slots allocated before the call, where a full-expression temporary of the same type shares one: 6734's map
moved into its base `CDataMap` takes the target's frame (864, the map at +76) through a setter that takes it by value,
and 848, every offset above it 16 lower, as `m_registros = Container(std::move(registros));` (fragment 386). The
probe, as above (c3a97777):

```sh
P=build/out/codegen-facts; mkdir -p $P
printf '%s\n' '#include <map>' 'struct D { std::map<int, int> m; void Set(std::map<int, int> v) { m = std::move(v); } };' 'void ByValue(D& d, std::map<int, int>& r) { d.Set(std::move(r)); }' 'void Temp(D& d, std::map<int, int>& r) { d.m = std::map<int, int>(std::move(r)); }' > $P/byvalue.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/$P/byvalue.cpp -o /work/$P/byvalue.ll && awk '/^define/ {f=$0; sub(/.*@/, "", f); sub(/\(.*/, "", f)} /alloca/ {a[f]++} /llvm.lifetime.start/ {l[f]++} END {for (f in a) print f, "allocas", a[f], "lifetime starts", l[f]+0}' $P/byvalue.ll | sort | /usr/bin/grep -E 'ByValue|Temp' | sed 's/R1DR[^ ]*//'
# _Z4Temp allocas 4 lifetime starts 2
# _Z7ByValue allocas 4 lifetime starts 0
```

Which of the marked slots merge follows how much of the body the helper holds. A result dropped in a helper clang
inlines carries the inliner's lifetime markers, which in the IR span the whole inlined body (`lifetime.start` before
the helper's first call, `.end` after its last release), while the stack colouring counts it live from its first use
to the helper's return; so the helper's extent decides which marked temporaries merge into its slot. 11891's message
(`api::MostraMensagemTemporaria`, unit 171's fragment) took the target's slots with its whole body in a helper of
internal linkage (`ExibeMensagemTemporaria`): the text field's dropped result outlives `""` and the form and shares
the slot of the second `SPoint`, whose range ends before that result's first use; written as statements of the
function, the second `SPoint` shares the form's slot. A helper around part of the body gives other pairs: with both
adders in it the form shares the text field's slot, with `AddTextField` alone the second `SPoint`'s (and `""` the text
field's), object probes at 836481cb. Read which temporaries carry markers in the TU's IR (`-S -emit-llvm`, as above)
before trying forms for such a remainder, and say in a note that lists a helper form how much of the body it held.

What a TU emitted first decides an inlined template's stack slots too. `CPolySingleton<T>::set` (4879 for
`api::ITimerScheduler`, 4890 for `api::ISystemDateTime`) inlines `std::format`, whose parts are `always_inline`, and
differed from the target in frame offsets alone at 4487d6b, while 10876, the same template over another class, matched. The source
of `set` is not the cause. One line that makes the TU emit `instance()`'s format code first, above `GetInst`, gives
every frame offset of the target's (at 4487d6b, a variant object in a copy of the link, [workflow.md](workflow.md)
§W13):

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
kinds re-points both 4879 and 4890 `IDENTICAL`. The line only steers the compiler, so it never lands: the two rows stayed
`differs` until a TU that emits a format body before them held the instance: fn 8302's
(`src/units/188-uenux2-simulador.mk`), from whose object both match now. Which TU's copy the target keeps, its
records say: `awk -F'\t' '$2 ~ /cpolysingletonlist.h/ && $3==129 {print $1, $6}' ledger/source-locations.tsv` lists
4879's record, 1531292, right after 8302's, 1531180, in another object's run. That clang declares a callee at its first
mention, so that the inlined parts' allocas come in another order, is the reading; the scores are the measurement.

What the TU emits *after* the function moves those slots too. 1937's reader (`comum::CLeitorASN::LeBiometriaEleitor`,
which inlines `legravaentidade.h`'s `LeEntidadeBiometria`) has the target's 576-byte frame slots in the TU with
`CConversorCabecalhoPacote`'s `Desconverte` or a `CarregaArquivo` instance after it, as with
`ReadFromFile<CabecalhoPacote>` ahead of it; alone in its TU, or with that `ReadFromFile` after it, most slots are 8
bytes lower and the second throw's packed format string sits at +488 where the target's is at +136. So another instance
of the templates the function shares, before it or after it, can move its slots: compare the variants on objects before
reading an order into it (unit 280's `carregaarquivo.cpp` gives the target's slots at the head of the file, between its
instances and at its end).

**A frame larger than what its code addresses.** Count the frame bytes the target's instructions address (the folded
readout's frame offsets and the addresses passed on) against the objects the code shows:

- **An unused run right above an object in its slot** can be a larger object whose extra member folds away. 1695
  (`api::CApplication::GetContexto`) copies a 52-byte, 4-aligned `CApplicationContext` to +0 of an 80-byte frame, with
  +52..+56 unused under the next object; eleven orders of plain locals, two flags and two header variants gave +4, +24,
  +28 or the result, never +0. A `std::optional<CApplicationContext>`, 56 bytes, declared where the plain local was and
  read only through `*`, gives +0 and the target's function, the flag's store and test folded away (`13 over 140`, all
  operands; unit 171's fragment lists the five forms that give the same object). No other wrapper was measured.
- **Bytes no instruction addresses at all,** more than every object of ours with its alignment, are objects whose code
  the target lost after clang laid out the frame (binaryen removed it: §R1's folding is one way). 5821
  (`comum::CGravadorWSQ::CompactaWsq`) has a 160-byte frame whose instructions address 76 bytes (`pnpm --silent wasm fn
  ../target/vota_web_wasm.wasm 5821 | sed -n '/folded readout/,$p'`: +64..+75, +88..+99, +104, +148..+159), and ours
  holds the same four slots in 80: no order of the source gives the other 84, and the body waits until that code is
  known (unit 122's fragment).
- **A result passed by value whose type is larger than the part the caller reads.** The caller allocates the callee's
  whole object, so the frame gives its size. 5635 (`CEstadoGeral::RecuperarCertificado`) passes +12 of a 48-byte frame
  as slot 10's result and reads only the vector at its head (`pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5635 |
  sed -n '/folded readout/,$p' | sed -n 4,13p`): with the vector alone as the result type every frame offset is 8 lower
  (`20 over 121`), and a struct of the vector and 24 more bytes gives the target's 48 and +12 (`11 over 121`, all
  operands).

**A frame short by one object's slot, the slots above it shifted.** Stack colouring gave two objects one slot where the
target keeps them apart: a slot with one lifetime-start marker is coloured from its first use. 653
(`api::CInteractiveFormBuilder::AddLabeledInputControl`) was 528 bytes in every form of its loop and the target's 544
with `-mllvm -stackcoloring-lifetime-start-on-first-use=false` (or `-mllvm -no-stack-coloring`) on its compile line,
which says the target's frame is the conservative one; the source form is a branch on the function's `bool` inside the
loop, which clang unswitches, so the lambda's message has two lifetime starts, and binaryen drops the dead copy of the
loop once the `bool` folds (unit 120's fragment). Compile with the flag before hunting an order for a short frame.

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
alone). So a caller's reload after such a call says nothing of the callee's TU. What the caller does with the
constructor's returned `this` does: a call of the C1 alias of a C2 its own TU defines drops the result, and a call of a
C1 defined in another TU uses it (bbf27ac1's flags, at 3c1ef19d):

    P=build/out/codegen-facts; printf '%s\n' 'struct P { int a, b; P(int); };' '#if DEF' 'P::P(int x) : a(x), b(2 * x) {}' '#endif' 'void Use(P*);' 'void Make(int x) { Use(new P(x)); }' > $P/ctorthis.cpp
    for d in 1 0; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -DDEF=$d -c /work/$P/ctorthis.cpp -o /work/$P/ctorthis-$d.o; printf 'DEF=%s: ' $d; wasm-objdump -d $P/ctorthis-$d.o | awk '/<_Z4Makei>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | /usr/bin/grep -A1 -E '^call [0-9]+ <(env\.)?_ZN1PC[12]' | tr '\n' ';'; echo; done
      DEF=1: call 2 <_ZN1PC1Ei>;drop;
      DEF=0: call 1 <env._ZN1PC1Ei>;call 2 <env._Z3UseP1P>;

binaryen inlines either into a one-caller site and keeps what the object did: the result read after the inlined code
(a `local.tee` or `local.set` of the block's value, or the value passed on) says the constructor is another TU's, in
its own file or its class's. 3614 keeps 2738's result (`pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3614 |
/usr/bin/grep -A1 'call 2738'` prints `local.tee 0` after the call), and so do 10425's four calls of 2733 (unit 142,
which gives 2733 a file of its own) and 5702's inlined `CMinuciasCompactadas` constructor (unit 335: `637 over 1382`
in the caller's TU, a match in a TU of its own). binaryen may still inline or remove the
callee in the link. Which of the two names an object's call holds, the disassembly does not say
([tool-traps.md](tool-traps.md) §X11).

This holds for the C1 and D1 aliases only. A delegating constructor calls the other constructor's C2, which is no
alias, so clang inlines it in their TU; a function that returns the object built by its complete constructor calls the
C1, which stays a call (bbf27ac1):

    P=build/out/codegen-facts; mkdir -p $P
    printf '%s\n' '#include <string>' 'struct Ctx { std::string a, b, c; bool e; Ctx(std::string, std::string, std::string, bool); Ctx(std::string, std::string); static Ctx Cria(std::string, std::string); };' 'Ctx::Ctx(std::string a, std::string b, std::string c, bool e) : a(std::move(a)), b(std::move(b)), c(std::move(c)), e(e) {}' 'Ctx::Ctx(std::string a, std::string b) : Ctx(std::move(a), std::move(b), {}, false) {}' 'Ctx Ctx::Cria(std::string a, std::string b) { return Ctx(std::move(a), std::move(b), {}, false); }' > $P/delegate.cpp
    TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -c /work/$P/delegate.cpp -o /work/$P/delegate.o
    wasm-objdump -d $P/delegate.o | awk '/ func\[/ {f=$3; sub(/E.*/, "", f); n[f]=0; o[++k]=f} / call [0-9]+ <_ZN3CtxC[12]/ {n[f]++} END {for (i=1; i<=k; i++) print o[i], n[o[i]], "constructor calls"}'
      <_ZN3CtxC1 0 constructor calls          (the four-member constructor)
      <_ZN3CtxC1 0 constructor calls          (the delegating one)
      <_ZN3Ctx4Cria 1 constructor calls

So a target caller that moves its arguments out and keeps a call of the complete constructor, whose `this` result no
caller reads, is the second form: 3682 and 5558 call 5557, `(i32 i32 i32 i32 i32 i32)->()` (`pnpm --silent wasm fn
../target/vota_web_wasm.wasm 5557 | head -1`). Whether it is a member is how-to step 3's member rule.

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

## C9. What `new T()` clears before the base constructor says how the constructors are declared

A `GetInst` or a `StartState` that builds an object holds its constructor inlined, and the stores before the base
constructor's call are then the evidence. A value-initialized object is cleared first: a complete object with no
user-provided constructor at `operator new`'s alignment over `sizeof`, a base that a user-provided constructor
value-initializes (`D() : B() {}`) at the base's alignment over the base's data size, and nothing when that constructor
default-initializes it. With `A` a vptr, a pointer and three `bool`s (11 bytes of data, `sizeof` 12):

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/newinit.cpp <<'EOF2'
struct A { virtual ~A(); void* p; bool b1, b2, b3; A(int e = 0); };
struct B : A {};
struct D final : B {
#if FORM == 1
    D() : B() {}
#elif FORM == 2
    D() {}
#endif
};
A* make() { return new D(); }
EOF2
for f in 0 1 2; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/$P/newinit.cpp -o /work/$P/newinit-$f.o
  printf 'FORM=%s: ' $f; wasm-objdump -d $P/newinit-$f.o | sed -n '/<_Z4makev>:/,$p' | /usr/bin/grep -oE '(i32|i64)\.store8? [0-9] [0-9]+|call [0-9]+ <env\._ZN1AC2Ei>' | awk '{print} /_ZN1AC2Ei/ {exit}' | tr '\n' ';'; echo; done
# FORM=0: i32.store 2 8;i64.store 3 0;call 1 <env._ZN1AC2Ei>;
# FORM=1: i32.store 0 7;i64.store 2 0;call 1 <env._ZN1AC2Ei>;
# FORM=2: call 1 <env._ZN1AC2Ei>;
```

(`wasm-objdump` prints a store's alignment as a power of two, then its offset.) The second is the target's 10327
(`comum::CGestorDadoMesario::StartState`): `i32.store align=0 offset=7` and `i64.store align=2 offset=0` before `call
224`, `CAppState`'s constructor, with 0. So the state's constructor is user-provided and value-initializes its base,
and the base's default constructor is not user-provided down to the class whose constructor the code calls, which must
be callable with no argument (a default argument, as here, or an inline delegating `A()` give the same stores). Unit 135
writes it so. A constructor defined out of the class keeps a call of its C1 in the TU instead (unit 104).

Zero stores before the vptr do not by themselves mean value-initialization. An out-of-line user-provided constructor
that binaryen inlined into its one caller clears its members in its own order and at the type's alignment from its
first member, with the vptr stored among them: 11523 zeroes the new `comum::md::CVisitanteEleitor` at +56, then +4 to
+52 with 4-byte-aligned `i64` stores, the vptr, then +52, not +0 at 8-byte alignment as the first shape does; the
constructor alone in its TU gives that order, and an inline one puts the vptr store after +56 (unit 225's fragment,
`cvisitanteeleitor.cpp`).

## C10. A caller's temporaries tell a by-value class parameter from a reference

A caller that builds two temporary arguments, one of them a class the callee takes by value or by reference, stores
them in another order and slot for each form. With `std::function<void()>` by value its capture comes first and each
call's temporary takes a new slot; with `const std::function<void()>&` the interval comes first and the next call
reuses the slots (bbf27ac1; `+N` a store at frame offset N, `v@+N` an `i64` constant stored there, `|` a call):

```sh
P=build/out/codegen-facts; mkdir -p $P
cat > $P/paramform.cpp <<'EOF2'
#include <functional>
struct Ms { long long v; };
struct IScheduler { virtual void Create(const Ms&, ARG) = 0; };
void Use(IScheduler* s, int* p) { s->Create(Ms{1000}, [p] { *p = 1; }); s->Create(Ms{2000}, [p] { *p = 2; }); }
EOF2
for a in byvalue cref; do T='std::function<void()>'; [ $a = cref ] && T='const std::function<void()>&'
  TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG "-DARG=$T" -c /work/$P/paramform.cpp -o /work/$P/paramform-$a.o; done
for a in byvalue cref; do printf '%s:' $a; wasm-objdump -d $P/paramform-$a.o | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | awk '/ func\[/ {f=$3} f !~ /_Z3Use/ {next} /^i64\.const/ {k=$2} /^i64\.store/ {printf " %s@+%s", k, $3} /^i32\.store/ {printf " +%s", $3} /^call_indirect/ && ++c % 2 == 0 {printf " |"} END {print ""}'; done
# byvalue: +36 1000@+56 +32 +48 | +12 2000@+56 +8 +24 |
# cref: 1000@+24 +4 +0 +16 | 2000@+24 +4 +0 +16 |
```

`ITimerScheduler`'s slot 0 has the second shape: fns 2024 and 5904 store the interval's temporary before the
`std::function`'s, and 5904 reuses the `std::function`'s slot for its next temporary, so the callback is a reference
(`src/uenux2/src/api/util/itimerscheduler.h`, where `&&`, giving the same object, is the form not chosen).

Two more caller-side signs, at the tree's flags (182dc6c1):

- **A small struct built from constants is stored twice.** By value, the caller stores the temporary at the higher
  offset and the `byval` copy below it, the same word in both, and passes the copy; by `const &`, one store whose
  address is passed. 7707 stores 328020 (`SPoint{340, 5}`) at +12 and +8 and passes +8 to 4620, and 13550 the same with
  `{320, 30}`, so `DesenhaDescricaoModo` takes its `api::SPoint` by value (unit 165):

  ```sh
  P=build/out/codegen-facts; printf '%s\n' 'struct SPoint { short x, y; };' 'struct IScreen;' '#if BYVALUE' 'void D(IScreen&, SPoint);' '#else' 'void D(IScreen&, const SPoint&);' '#endif' 'void F(IScreen& s) { D(s, SPoint{340, 5}); }' > $P/byval2.cpp
  for b in 1 0; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -DBYVALUE=$b -c /work/$P/byval2.cpp -o /work/$P/byval2-$b.o; printf 'BYVALUE=%s: ' $b; wasm-objdump -d $P/byval2-$b.o | awk '/<_Z1FR7IScreen>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -E 'i32.const|i32.store|call' | tr '\n' ';'; echo; done
  # BYVALUE=1: i32.const 16;i32.const 328020;i32.store 2 8;i32.const 328020;i32.store 1 12;i32.const 8;call 0 <env._Z1DR7IScreen6SPoint>;i32.const 16;
  # BYVALUE=0: i32.const 16;i32.const 328020;i32.store 1 12;i32.const 12;call 0 <env._Z1DR7IScreenRK6SPoint>;i32.const 16;
  ```
- **A by-value class argument's temporary keeps a slot of its own,** and a later temporary cannot reuse it, while one
  bound to a reference parameter can share its slot with a later object (its lifetime is marked; a reading). So a
  caller frame larger than the target's by such a temporary, the slots above it shifted, reads as by-value where the
  target's parameter is a reference: `main` (10307) is 96 bytes over `simulador::Inicializa`'s `std::function` by value
  and 80, the target's, by `const&` (units 188 and 170). A probe, a `std::function` then a string temporary:

  ```sh
  P=build/out/codegen-facts; printf '%s\n' '#include <functional>' '#include <string>' '#if BYVALUE' 'void Init(std::function<void()> f);' '#else' 'void Init(const std::function<void()>& f);' '#endif' 'void Run(const std::string&);' 'int Main(int* p) { Init([p] { *p = 1; }); Run(std::string("abcdefghijklmnopqrstuvwxyz0123")); return 0; }' > $P/byval3.cpp
  for b in 1 0; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -DBYVALUE=$b -c /work/$P/byval3.cpp -o /work/$P/byval3-$b.o; printf 'BYVALUE=%s frame: ' $b; wasm-objdump -d $P/byval3-$b.o | awk '/<_Z4MainPi>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -m1 -A1 'global.get 0' | tail -1; done
  # BYVALUE=1 frame: i32.const 48
  # BYVALUE=0 frame: i32.const 32
  ```

A copy is the other sign, and it says less. A caller that passes an lvalue of the parameter's own type with no copy
rules out by-value. A copy made just before the call is a by-value parameter or a temporary a conversion binds to a
`const &`: 2890 copies a `std::filesystem::path` into a string before calling `api::IPaper`'s slot 8, which `const
std::string&`, `std::string` and `std::filesystem::path` by value all give (how-to step 2).

## C11. A throw path's blocks follow the named locals in scope at each call that can throw

Rows that differ only where the exception paths sit (an `unreachable` after `__cxa_throw` in a block of its own or
shared, a call's catch block shared with the function's or one of its own), every other row an operand, come from which
named locals are in scope at each call that can throw. clang pushes a named local's lifetime-end cleanup when the local
is declared, before its initializer runs, so `if (const unsigned long erro = ERR_get_error(); …)` gives that call a
landing pad of its own (`invoke @ERR_get_error … unwind label %151`, where `EVP_DecryptUpdate`'s unwinds to `%87`, in
the TU's `-S -emit-llvm`), and SROA later removes the marker but not the pad. `CAesCipher`'s `SetKey`, `Encrypt` and
`Decrypt` (9494, 9493, 9491) matched with the key's size held in a named local before its test, and with `erro`
declared among the function's locals and assigned in the test, after the IV's first call; three places of that
declaration were measured and gave one wasm (unit 11's fragment, where `CSha::Reset` and `Finish`, 5177 and 3518, show
the same). `-Xclang -disable-lifetime-markers` on a probe compile shows whether a form's difference is this.

Where a pad is laid out against the normal path is a separate question: two forms with the same pads in the IR can order
them apart. A converter that returns the object it builds puts its last constructor's pad before the normal path when
the result goes through a named local (`T t(...); return t;`), and after it when it returns the prvalue (`return
T(...);`): 9106 (`CConversorComparecimentoMesario::DoDeconverte`) scored `47 over 225`, 4 rows inserted and 13 deleted,
the other way, and matched so (unit 09's fragment), as 9216 did (unit 105's). Read the object's lines after the
constructor's `call invoke_*` for each form before linking.

A TU built without `-fexceptions` (every uenux2 TU; emcc then compiles with `-fignore-exceptions`,
[app-flags.md](app-flags.md)) has no pads: a `try` block compiles as a plain block scope and its handlers leave no
code or data, so a form that rests on where a scope ends has the `try` block as a same-bytes form (3829's response
vector, unit 95's fragment):

```sh
P=build/out/codegen-facts; printf '%s\n' '#include <exception>' '#include <string>' '#include <vector>' 'void Send(std::vector<char>&);' 'std::string F() {' '#if TRY' '    try {' '#else' '    {' '#endif' '        std::vector<char> v(8);' '        Send(v);' '#if TRY' '    } catch (const std::exception& e) { return e.what(); }' '#else' '    }' '#endif' '    return "";' '}' > $P/tryblock.cpp
for x in '' -fexceptions; do for t in 0 1; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG $x -DTRY=$t -c /work/$P/tryblock.cpp -o /work/$P/tryblock-$t.o; done
  printf '%s: ' "${x:-no -fexceptions}"; cmp -s $P/tryblock-0.o $P/tryblock-1.o && echo same || echo differ; done
# no -fexceptions: same
# -fexceptions: differ
```

## C12. A loop clang turns twice: in the caller and in a helper it inlines

A loop the target carries a value through (a loop variable the next pass computes) or whose exits it threads (a `select`
folded into the exits), where every form written in the caller's own body keeps a reload or a select, can need its
search in a function of its own that clang inlines. In the caller, LoopRotate turns the loop once before GVN and
JumpThreading and once in the late pipeline, after the last JumpThreading; in a helper the first turn happens in the
helper's own pipeline and the second in the caller's, before its JumpThreading. 5497
(`api::CTextFieldMultiLine::GetTextLines`) stayed at best `143 over 925` over fifteen in-place forms of its two loops,
and with the space search in `UltimoEspaco`, which takes the line as a parameter, scored `40 over 910`, all operands,
then matched (unit 14's fragment). Where a loop's shape is made shows with `-mllvm
-print-after=loop-rotate,inline,jump-threading -mllvm -filter-print-funcs=<mangled>` (or `-print-after-all`) on the TU's
compile line from `make -n -C src link -W $PWD/<tu>`, `-c … -o <scratch>.o`, the dumps on stderr.

## C13. A member stored in each arm of a two-way branch

10737 (`vota::CFimAquisicaoVotos::StartState`) stores one member in each arm of an if/else (`i32.store offset=4` then
`br 1` in the first, another at the end of the second), and every form tried at the tree's flags joined the two stores
after the branch; `-mllvm -print-after-all -mllvm -filter-print-funcs=<mangled>` names the pass, MergedLoadStoreMotion
(unit 104's fragment lists the forms; written so, the row read `16 over 41`). 5400 has the same shape, and 10511 the
joined one, in the target. The join is not general: a switch's cases keep their stores apart (11848), and so do two
arms that each store a call's result:

```sh
P=build/out/codegen-facts; printf '%s\n' 'struct S { int pad; void* m_next; };' 'void* A(); void* B(); void* C();' 'void If(S& s, int c) { if (c == 2) s.m_next = A(); else s.m_next = B(); }' 'void Sw(S& s, int c) { switch (c) { case 1: s.m_next = A(); break; case 2: s.m_next = B(); break; default: s.m_next = C(); } }' > $P/arms2.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/arms2.cpp -o /work/$P/arms2.o
for f in _Z2IfR1Si _Z2SwR1Si; do printf '%s: ' $f; wasm-objdump -d $P/arms2.o | awk -v f="<$f>:" '$0 ~ f {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -c 'i32.store 2 4'; done
# _Z2IfR1Si: 2
# _Z2SwR1Si: 3
```

The switch keeps them apart because each case stores once. With two stores per case (a `std::shared_ptr` result
written field by field, the empty case's two nulls among them) the SimplifyCFG after TailCallElim sinks them into one
tail with phis, and one 8-byte copy per case stays apart again, two `i32` stores per case and an `i64.store` of 0 on
the empty path, the shape the target's 9116 (`CConversorIdentificadorEleitor::DoDeconverte`) holds:

```sh
P=build/out/codegen-facts; printf '%s\n' 'struct S2 { void* a; void* b; };' 'void* A(); void* B(); void* C();' 'void One(S2& s, int c) { switch (c) { case 1: s.b = A(); break; case 2: s.b = B(); break; default: s.b = C(); } }' 'void Two(S2& s, int c) { switch (c) { case 1: { void* x = A(); s.a = (char*)x + 12; s.b = x; } break; case 2: { void* x = B(); s.a = (char*)x + 12; s.b = x; } break; default: s.a = nullptr; s.b = nullptr; } }' 'void Copy(S2& s, int c) { switch (c) { case 1: { void* x = A(); S2 t{(char*)x + 12, x}; __builtin_memcpy(&s, &t, 8); } break; case 2: { void* x = B(); S2 t{(char*)x + 12, x}; __builtin_memcpy(&s, &t, 8); } break; default: { S2 t{}; __builtin_memcpy(&s, &t, 8); } } }' > $P/cases.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/cases.cpp -o /work/$P/cases.o
for f in _Z3OneR2S2i _Z3TwoR2S2i _Z4CopyR2S2i; do printf '%s: ' $f; wasm-objdump -d $P/cases.o | awk -v f="<$f>:" '$0 ~ f {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -oE 'i(32|64)\.store [0-9] [0-9]+' | tr '\n' ';'; echo; done
# _Z3OneR2S2i: i32.store 2 4;i32.store 2 4;i32.store 2 4;
# _Z3TwoR2S2i: i32.store 2 4;i32.store 2 0;
# _Z4CopyR2S2i: i32.store 2 4;i32.store 2 0;i32.store 2 4;i32.store 2 0;i64.store 2 0;
```

So count the stores each arm or case takes, and read the arms' contents, before spending links on the shape. What keeps
10737's two stores apart in the target is
explained by a call in each arm that binaryen inlines afterwards (a reading: the form that matches; no frame or record
shows the call): clang does not join two calls of an out-of-line setter, and with `comum::CAppState::SetNextState` (out
of line in `cappstate.cpp`) called in both arms the row matches. Unit 61's fragment has the measurements, and the replay
of the link's own `wasm-opt -Oz` (§C4) that first showed it.

## C14. A condition's test order

An `&&`/`||` chain written as an `if`'s condition can come out with its tests reordered: Reassociate orders an `or` of
two compares by rank, a compare of the value defined earlier first. For 10797 (`CControladorRegistraMesariosVota`'s
slot 5) eight spellings written in the condition, in either order, gave one test order, not the target's; the same
chain computed into a `bool` value first, a named `const bool` tested after or a lambda's return with either capture,
kept the source's order (unit 119's fragment has the forms and their objects). Compile both before reading a test order
as the source's.

## C15. What orders a function's blocks: the branch folder, then CFG Sort over the IR's order

No block-placement pass runs for wasm32: the backend's pipeline has `WebAssembly CFG Sort` and `CFG Stackify` and no
`Branch Probability Basic Block Placement` (bbf27ac1's flags, at 3c1ef19d):

```sh
P=build/out/codegen-facts; printf '%s\n' 'int f(int x) { return x ? x * 3 : 1; }' > $P/passes.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -mllvm -debug-pass=Structure -c /work/$P/passes.cpp -o /work/$P/passes.o 2>&1 | /usr/bin/grep -i -E 'placement|cfg sort|cfg stackify' | sort | uniq -c
#    1       WebAssembly CFG Sort
#    1       WebAssembly CFG Stackify
```

CFG Sort keeps each loop's blocks together and otherwise follows the machine blocks' numbers, which are the IR's order,
so a block placed elsewhere than the target's (a throw last against right after a loop) moves with a form that changes
the IR's block order, not with branch weights or an inverted test. 11411's `GetInscricoesEleitor` has its "Inscrição não
encontrada" throw right after the identities' loop with the copy written as a range-for, and last, as the target has it,
with `std::transform` after the same emptiness test; inverting the test, or `size() == 0`, changed nothing (unit 310's
fragment). `-mllvm -print-after-all -mllvm -filter-print-funcs=<mangled>` on the TU's compile line shows the machine
blocks before and after the sort.

Before CFG Sort, the branch folder (`branch-folder`, "Control Flow Optimizer") moves a block with no successors (a
throw, a return) to the function's end when its layout predecessor branches to the block after it (`if (!r) throw …;`
inside a loop: LLVM's `BranchFolder::OptimizeBlock`, read, not measured case by case). So a throw last against inside
a loop can be the branch folder's with the IR order already the target's; read it before looking for an IR order:

```sh
P=build/out/codegen-facts; printf '%s\n' '#include <stdexcept>' 'int* Find(int** v, int n, int k) {' '    for (int i = 0; i < n; ++i)' '        if (v[i][0] == k) {' '            if (!v[i][1]) throw std::runtime_error("vazio");' '            return v[i];' '        }' '    return nullptr;' '}' > $P/bfold.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -mllvm -print-before=branch-folder -mllvm -print-after=branch-folder -mllvm -filter-print-funcs=_Z4FindPPiii -c /work/$P/bfold.cpp -o /work/$P/bfold.o 2> $P/bfold.txt
awk '/IR Dump/ {print; next} /^bb\./ {b=$1} /__cxa_throw/ {print "  throw in", b} /^# End machine code/ {print "  last block", b}' $P/bfold.txt
# # *** IR Dump Before Control Flow Optimizer (branch-folder) ***:
#   throw in bb.5
#   last block bb.6
# # *** IR Dump After Control Flow Optimizer (branch-folder) ***:
#   throw in bb.7
#   last block bb.7
```

The throw stays put when the block after it is not its predecessor's branch target: 1721
(`IForm<IScreen>::FindFieldAs<CTextField>`) keeps its throw inside the loop, as the target does, only when the success
path's release of the field comes before the throw in the IR (a probe statement in the then-block does it, no form
found yet: unit 37's fragment).

## C16. Loads a declaration decides: a struct copy as one wide load, a string's alignment

A small class copied from a global comes out as one `i64.load` and shifts when it comes through a function that returns
it by value, and as one load per field read when the copy is a local initialized from the global, at 3c1ef19d:

```sh
P=build/out/codegen-facts; printf '%s\n' 'struct SRect { short left, top, right, bottom; };' 'struct App { static SRect s_area; };' 'void Draw(int, int);' 'static SRect Area() { return App::s_area; }' 'void Copy() { const SRect a = App::s_area; Draw(a.left, a.bottom); }' 'void ByValue() { const SRect a = Area(); Draw(a.left, a.bottom); }' > $P/wide.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/wide.cpp -o /work/$P/wide.o
for f in _Z4Copyv _Z7ByValuev; do printf '%s: ' $f; wasm-objdump -d $P/wide.o | awk -v f="<$f>:" '$0 ~ f {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | /usr/bin/grep -oE '^(i64|i32)\.load[0-9_a-z]* [0-9]+ [0-9]+|^i64\.shr_u' | tr '\n' ';'; echo; done
# _Z4Copyv: i32.load16_s 1 0;i32.load16_s 1 6;
# _Z7ByValuev: i64.load 1 0;
```

12055 reads `CApplication::s_areaTela` so, and holds it from a file-local by-value helper (unit 37's fragment).

A string's bytes copied into a `std::string` are loaded at the alignment of what holds them: a literal at 1
(`i64.load align=0`), a named `char` array at 8 or more (`align=3`), which also puts the array at a 16-byte aligned
address in the data (a reading of clang's large-array rule). So `align=3` loads of a text the target holds at an address
divisible by 16 say a named array, not a literal (at 3c1ef19d):

```sh
P=build/out/codegen-facts; printf '%s\n' '#include <string>' 'void Use(const std::string&);' 'namespace { const char TEXTO[] = "Erro no teste do teclado"; }' 'void Named() { Use(TEXTO); }' 'void Literal() { Use("Falha no teste do teclado"); }' > $P/align.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing -c /work/$P/align.cpp -o /work/$P/align.o
for f in _Z5Namedv _Z7Literalv; do printf '%s: ' $f; wasm-objdump -d $P/align.o | awk -v f="<$f>:" '$0 ~ f {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | /usr/bin/grep -oE '^i64\.load [0-9]+ [0-9]+' | tr '\n' ';'; echo; done
# _Z5Namedv: i64.load 3 16;i64.load 3 8;i64.load 3 0;
# _Z7Literalv: i64.load 0 16;i64.load 0 8;i64.load 0 0;
```

11812's three texts (@475072, @475104, @475152) are named arrays in `ctelasvota.cpp`'s anonymous namespace for that
reason (`ctelasvota.h`'s comment over the class has the scores). Two equal texts in one TU are one constant, so a probe
of the two forms needs two texts.

## C17. A 16-bit value passed to an `int`: `extend16_s` only with a second 16-bit use

A 16-bit value (a `TPosition`, `short`) computed from `int`s and passed to an `int` parameter comes out as a shift pair,
`i32.shl` and `i32.shr_s` by 16 (instcombine turns the narrowing and the extension into shifts and folds the shift into
a one-use add), and as `i32.extend16_s` only when the 16-bit value has a second use at 16 bits, at c3a97777:

```sh
P=build/out/codegen-facts; printf '%s\n' 'void UseInt(int); void UseShort(short);' 'void Once(int a, int b) { UseInt(static_cast<short>(a - b + 1)); }' 'void Twice(int a, int b) { const short w = a - b + 1; UseInt(w); UseShort(w); }' > $P/ext16.cpp
TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++23 -DNDEBUG -c /work/$P/ext16.cpp -o /work/$P/ext16.o
for f in _Z4Onceii _Z5Twiceii; do printf '%s: ' $f; wasm-objdump -d $P/ext16.o | awk -v f="<$f>:" '$0 ~ f {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | /usr/bin/grep -oE '^i32\.(extend16_s|shl|shr_s)' | tr '\n' ';'; echo; done
# _Z4Onceii: i32.shl;i32.shr_s;
# _Z5Twiceii: i32.extend16_s;
```

The same shift pair comes from a `TPosition` local, `++` or `+= 1` on one, two `int` uses, `std::abs(a - b) + 1` and
`std::to_string` of it, at every level from `-O1` to `-Oz`, and the target holds no such pair. A maximum less a minimum
of one block folds into an absolute difference, `select(a > b, a - b, b - a)`. So the target's
`extend16_s(sub(max, min) + 1)` in `simulador::CWasmScreen::DrawText` (9104) and `extend16_s(abs(x1 - x2) + 1)` into
`std::to_string(int)` in `Refresh` (9018) come from neither a value used once as an `int` nor one computed before the
branch; an external helper with `TPosition` parameters would give them, but clang inlines it (cost 230 against 250),
and no form has given them (unit 69's `-pending.cpp`).
