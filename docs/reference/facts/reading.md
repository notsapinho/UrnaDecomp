# Reading the source from the target's bytes

What a target body says about the C++ that compiled to it, beyond the name its `std::source_location` record gives:
the parameters a wasm type hides, how a class returns or takes a class by value, how a destructor is declared and
whether its class is `final`, whether a class is abstract, a free function's linkage, code binaryen inlined from
another function, and the format string and argument types of a `std::format` throw. `docs/how-to-decompile.md` steps
2, 3 and 5 rely on these. What a source form compiles to (the order of a body's stores, a switch over virtual slots,
an in-class member against an `inline` one) is in [codegen.md](codegen.md).

The probes are short TUs compiled by the pinned em++ with uenux2's flags, `-O2 -fPIC -std=c++20 -DNDEBUG
-fno-strict-aliasing` (`docs/reference/facts/app-flags.md` §F6); their sources are given in full. R1–R3 and R7–R11
were measured under `build/out/DOCS-A/probe/` of a checkout at 7bf701e, R4–R6, R12 and R13 under
`build/out/DOCS2-A/probe/` at ee595de. Readouts are `pnpm --silent wasm fn ../target/vota_web_wasm.wasm <index>`, run
from `asmlift-wasm/` with Node 24 first on PATH ([workflow.md](workflow.md) §W1).

## R1. A parameter every caller passes as the same constant is gone from the wasm type

binaryen's dead-argument elimination removes a parameter that every call site passes as the same constant and puts
the constant into the body. So a wasm type can have fewer parameters than the C++ function, and a constant the body
stores can be an argument of the source. `comum::ValidarUE` has three parameters in its record and two in wasm:

    awk -F'\t' '$6 ~ /(^|,)5890(,|$)/ {print $5}' ledger/source-locations.tsv
      void comum::ValidarUE(IInterfaceSavd &, ESavdAplic, const std::string &)
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5890 | sed -n 1p
      ;; function 5890 (i32 i32)->() locals(i32 i32 i32 i32 i32 i64) body@0x30b794 size 717 instrs 310

Unit 26 writes `comum::CSigVerifier`'s constructor (1540) with the `ESavdAplic` parameter the target folded, and
its roots callers pass the constant, so the source invents no enumerator for it (`src/units/26-uenux2-csigverifier-roots.cpp`).

## R2. A constructor returns `this` in the object; the target's `void` is a result no caller used

In the WebAssembly C++ ABI a constructor and a non-deleting destructor return `this`. The target's `()` result is
dead-argument elimination dropping a return value no caller read. `api::CMovie`'s constructor:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5526 | sed -n 1p
      ;; function 5526 (i32 i32 i32)->() locals(i32) body@0x2adfce size 148 instrs 62
    wasm-objdump -x -j Function build/out/app/uenux2/src/api/gui/cmovie.cpp.o | /usr/bin/grep CMovieC1
      - func[9] sig=0 <_ZN3api6CMovieC1ENSt3__26vectorINS_11CMovieFrameENS1_9allocatorIS3_EEEERKNS_6SPointE>
    wasm-objdump -x -j Type build/out/app/uenux2/src/api/gui/cmovie.cpp.o | /usr/bin/grep 'type\[0\]'
      - type[0] (i32, i32, i32) -> i32

A stub's `void` (`src/README.md` "Stubs") is the target's type, so it says nothing here, and a roots file that
declares such a constructor must give it the object's `int` result (`src/units/README.md` "Companion files").

## R3. A trivially copyable class of one scalar is returned as that scalar

clang's WebAssembly ABI (no multivalue) returns a trivially copyable class whose only element is one scalar as that
scalar. Every other class returned by value goes through a hidden first parameter that holds the result's address,
and the function returns nothing. `api::CTime` holds one `size_t` (`src/uenux2/src/api/util/ctime.h`, `size_t
m_segundos;`), and `CTime CTime::operator-(int) const` is `(i32 i32)->(i32)` on both sides:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3641 | sed -n 1p
      ;; function 3641 (i32 i32)->(i32) locals(i32 i32) body@0x1b32fa size 286 instrs 132
    awk -F'\t' '$2=="_ZNK3api5CTimemiEi" {print $1}' build/out/wasm-map/vota_web/names.tsv      # 3755
    pnpm --silent wasm fn ../build/out/wasm/vota_web/vota_web_wasm.wasm 3755 | sed -n 1p
      ;; function 3755 (i32 i32)->(i32) locals(i32 i32) body@0x1be03b size 283 instrs 132

3641 is matched (`awk '$1==3641' splat/matched.txt` prints `3641 _ZNK3api5CTimemiEi`).

## R4. A destructor that destroys members and does not begin with its class's vptr store is a `final` class's

clang stores the class's vptr at the start of a destructor so that virtual calls from it reach this class's
members. It skips the store when no derived class can exist: the class (or the destructor) is `final`. Probe
`dtor.cpp`:

    #include <string>
    struct B { virtual ~B() = default; };
    // out of line: declared here, defined below
    struct Ool : B { ~Ool() override; std::string s; };
    Ool::~Ool() = default;
    // defined in the class, and a constructor in this TU (so the vtable is emitted)
    struct Inl : B { Inl(); ~Inl() override = default; std::string s; };
    Inl::Inl() {}
    // final, out of line
    struct Fin final : B { ~Fin() override; std::string s; };
    Fin::~Fin() = default;
    // defined in the class, no constructor in this TU: only a non-virtual member
    struct NoCtor : B { ~NoCtor() override = default; int f(); std::string s; };
    int NoCtor::f() { return 1; }

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/DOCS-A/probe/dtor.cpp -o build/out/DOCS-A/probe/dtor.o
    wasm-objdump -d build/out/DOCS-A/probe/dtor.o | awk '/D2Ev>:|D1Ev>:/ {print; n=6; next} n-- > 0' | /usr/bin/grep -E 'func\[|i32.store|GOT'
      0000c3 func[1] <_ZN3OolD1Ev>:
       0000c6: 23 80 80 80 80 00          | global.get 0 <GOT.mem._ZTV3Ool>
       0000cf: 36 02 00                   | i32.store 2 0
      000131 func[4] <_ZN3FinD1Ev>:
      000175 func[7] <_ZN3InlD2Ev>:
       000178: 23 81 80 80 80 00          | global.get 1 <GOT.mem._ZTV3Inl>
       000181: 36 02 00                   | i32.store 2 0

The target's `comum::CSigVerifier` D2 frees three strings and stores nothing at `[p0]`, and the class is `final` in
`src/uenux2/src/app/comum/relatorios/csigverifier.h` (unit 26):

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11178 | sed -n '/folded readout/,$p'
      function f11178(i32 p0) -> (i32) {
        if (i32.lt_s(i32.load8_s[p0+43], 0)) {
          i32.load[p0+40];
          f136(i32.load[p0+32]);
        }
        …                       # the same for +31/+20 and +19/+8
        push p0;
      }

`final` removes only the class's own store. A derived class's D2 that inlines its base's destructor stores the
base's vptr where the base's part begins, `final` or not, and a class with no member of its own has no D2 of its own
(its slot 0 holds the base's). Probe `dtorbase.cpp`:

    // What a derived class's implicit destructor does with its base's, and what final changes.
    #include <string>
    struct P { virtual ~P(); virtual void key(); std::string t; };    // P::~P() is out of line, in another .cpp
    struct Q : P { std::string s; void key() override; };
    struct P2 { virtual ~P2() = default; virtual void f() = 0; std::string t; };   // no key function: every virtual member is inline or pure
    struct Q2 : P2 { std::string s; void f() override; };
    struct Q3 final : P2 { std::string s; void f() override; };
    struct Q4 : P2 { void f() override; };                            // no member of its own
    void Q::key() {}
    void Q2::f() {}
    void Q3::f() {}
    void Q4::f() {}

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/DOCS2-A/probe/dtorbase.cpp -o /work/build/out/DOCS2-A/probe/dtorbase.o
    for s in _ZN1QD2Ev _ZN2Q2D2Ev _ZN2Q3D2Ev; do printf '%s: ' $s; wasm-objdump -d build/out/DOCS2-A/probe/dtorbase.o | awk -v s="<$s>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -E 'call |GOT.mem' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | tr '\n' ';'; echo; done
      _ZN1QD2Ev: global.get 0 <GOT.mem._ZTV1Q>;call 0 <env._ZdlPvm>;call 1 <env._ZN1PD2Ev>;
      _ZN2Q2D2Ev: global.get 1 <GOT.mem._ZTV2Q2>;call 0 <env._ZdlPvm>;global.get 2 <GOT.mem._ZTV2P2>;call 0 <env._ZdlPvm>;
      _ZN2Q3D2Ev: call 0 <env._ZdlPvm>;global.get 2 <GOT.mem._ZTV2P2>;call 0 <env._ZdlPvm>;

`Q3`'s D2 begins with its string and stores `P2`'s vptr before `P2`'s string; `Q2`'s stores its own vptr first. `Q`
calls `P`'s out-of-line D2 instead of inlining it (R5). The symbols (R6 reads them too):

    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/DOCS2-A/probe/dtorbase.o | /usr/bin/grep -E 'D[012]Ev|_ZTV'
               U _ZN1PD2Ev
      0000004a W _ZN1QD0Ev
      0000000d W _ZN1QD2Ev
      0000029d W _ZN2P2D0Ev
      00000227 W _ZN2P2D2Ev
      …                                   # Q2's and Q3's D0 and D2
      0000025e W _ZN2Q4D0Ev               # no _ZN2Q4D2Ev
      00000000 D _ZTV1Q
      0000009c W _ZTV2P2
      …                                   # D _ZTV2Q2, _ZTV2Q3, _ZTV2Q4, and two U typeinfo vtables

## R5. The D0's shape gives the destructor's form; the D2 is the same in every form

clang emits a virtual destructor in one of three shapes, and only the deleting destructor (D0) shows which. Probe
`dtorform.cpp`, one class whose destructor is written six ways (`key()` is the key function, so every form emits the
vtable):

    // One class, its destructor written six ways (FORM 0-5); key() is the key function, so every form emits the vtable.
    #include <memory>
    #include <string>
    #include <vector>
    struct B { virtual ~B() = default; virtual void key(); };
    struct X : B {
        std::vector<std::shared_ptr<int>> v;
        std::string s;
        void key() override;
    #if FORM == 1
        ~X() override = default;          // in the class
    #elif FORM == 2
        ~X() override {}                  // in the class, braces
    #elif FORM == 3
        inline ~X() override = default;   // in the class, inline
    #elif FORM == 4 || FORM == 5
        ~X() override;                    // declared only
    #endif                                // FORM 0: implicit
    };
    #if FORM == 4
    inline X::~X() = default;             // after the class, inline (a header's form)
    #elif FORM == 5
    X::~X() = default;                    // out of line, in the .cpp
    #endif
    void X::key() {}

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 2 3 4 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/DOCS2-A/probe/dtorform.cpp -o /work/build/out/DOCS2-A/probe/dtorform-$f.o; done'
    for f in 0 1 2 3 4 5; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/DOCS2-A/probe/dtorform-$f.o | awk '/<_ZN1XD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} END {print n " lines, calls at depth 0:" c}'; done
      FORM 0: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 1: 5 lines, calls at depth 0: <_ZN1XD2Ev> <env._ZdlPvm>
      FORM 2: 5 lines, calls at depth 0: <_ZN1XD2Ev> <env._ZdlPvm>
      FORM 3: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 4: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 5: 7 lines, calls at depth 0: <_ZN1XD1Ev> <env._ZdlPvm>
    cmp build/out/DOCS2-A/probe/dtorform-0.o build/out/DOCS2-A/probe/dtorform-3.o && cmp build/out/DOCS2-A/probe/dtorform-3.o build/out/DOCS2-A/probe/dtorform-4.o && cmp build/out/DOCS2-A/probe/dtorform-1.o build/out/DOCS2-A/probe/dtorform-2.o && echo 'FORM 0 = 3 = 4, FORM 1 = 2'
      FORM 0 = 3 = 4, FORM 1 = 2

| form | D0 | in the target |
| --- | --- | --- |
| implicit, or declared `inline` (in the class, or `inline X::~X() = default;` after it: the same object) | the D2's body inlined, then `operator delete` | 11176 (82 B, `comum::CSigVerifier`, implicit, unit 26) |
| in the class without `inline` (`= default` or `{}`: the same object) | `call D2` and `operator delete` of its result | `f136(f5531(p0))`, 11086 (10 B, `api::CImageFieldUpdate`, unit 43) |
| out of line in the `.cpp` | `call D1` (D2's alias), `drop`, `operator delete(this)` | `f5709(p0); f136(p0);`, 11443 (13 B, `comum::asn::CVisitanteFoto`, unit 36) |

What separates the first two rows is the inline hint. Only an implicit destructor and one declared `inline` carry it
before optimization:

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 3 4 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -S -emit-llvm -Xclang -disable-llvm-passes /work/build/out/DOCS2-A/probe/dtorform.cpp -o /work/build/out/DOCS2-A/probe/dtorform-$f.ll; done'
    for f in 0 1 3 4 5; do a=$(/usr/bin/grep -E '^define .*@_ZN1XD2Ev\(' build/out/DOCS2-A/probe/dtorform-$f.ll | /usr/bin/grep -oE '#[0-9]+'); printf 'FORM %s: %s\n' $f "$(/usr/bin/grep -E "^attributes $a " build/out/DOCS2-A/probe/dtorform-$f.ll | /usr/bin/grep -oE 'inlinehint' || echo no inlinehint)"; done
      FORM 0: inlinehint
      FORM 1: no inlinehint
      FORM 3: inlinehint
      FORM 4: inlinehint
      FORM 5: no inlinehint

The hint raises the cost up to which LLVM inlines the D2 into the D0. So an in-class destructor without `inline`
still holds a cheap D2's body: `vota::IQRCodeBUDS` declares `virtual ~IQRCodeBUDS() = default;` in
`src/uenux2/src/app/vota/eleitor/fimvotacao/cmostraqrcodebu.h`, and its D0 12049 (119 B) holds the 116-B D2 12050.
The probe's D2, a vector of `shared_ptr` and a string, is above that cost and below the hinted one;
`api::CImageFieldUpdate`'s (5531, 175 B) is above the first, since 11086 calls it.

A class with no base (a root class) has a virtual destructor only by declaring it, so the implicit form is not open
to it. Probe `dtorroot.cpp`, the same members in a root class `R`:

    // A class with no base: its destructor is virtual only when declared so.
    #include <memory>
    #include <string>
    #include <vector>
    struct R {
        std::vector<std::shared_ptr<int>> v;
        std::string s;
        virtual void key();
    #if FORM == 1
        virtual ~R() = default;           // in the class
    #elif FORM == 3
        inline virtual ~R() = default;    // in the class, inline
    #elif FORM == 5
        virtual ~R();                     // out of line, below
    #endif
    };
    #if FORM == 5
    R::~R() = default;
    #endif
    void R::key() {}

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 1 3 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/DOCS2-A/probe/dtorroot.cpp -o /work/build/out/DOCS2-A/probe/dtorroot-$f.o; done'
    for f in 1 3 5; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/DOCS2-A/probe/dtorroot-$f.o | awk '/<_ZN1RD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} END {print n " lines, calls at depth 0:" c}'; done
      FORM 1: 5 lines, calls at depth 0: <_ZN1RD2Ev> <env._ZdlPvm>
      FORM 3: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 5: 7 lines, calls at depth 0: <_ZN1RD1Ev> <env._ZdlPvm>

So a root class whose D0 holds a D2 too costly for the plain in-class form declares it `inline`.

The D2 is the same in every form: its body differs only in the object-local type index of a `call_indirect`.

    for f in 0 1 5; do wasm-objdump -d build/out/DOCS2-A/probe/dtorform-$f.o | awk '/<_ZN1XD[12]Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //; s/(call|global.get) [0-9]+ /\1 /' > build/out/DOCS2-A/probe/d2-$f.txt; done
    diff build/out/DOCS2-A/probe/d2-0.txt build/out/DOCS2-A/probe/d2-1.txt && echo 'D2: FORM 0 = 1'
      D2: FORM 0 = 1
    diff build/out/DOCS2-A/probe/d2-0.txt build/out/DOCS2-A/probe/d2-5.txt
      58c58
      <         call_indirect 0 <env.__indirect_function_table> (type 0)
      ---
      >         call_indirect 0 <env.__indirect_function_table> (type 2)

So a D2 that matches settles nothing about the form; a derived class's D2 does, since it inlines a base destructor
with the hint or defined in the class and calls one defined out of line (R4's `Q`). A class with no member of its own
has the base's D2 in its slot (R4's `Q4`). When that D2 is out of line, the class's D0 is the 10-B shape around it:
`simulador::CWasmInit`'s vtable starts `[5898, 9388]`, 5898 being `comum::IInterfaceInit`'s out-of-line D2 (R9), and
9388 is `f136(f5898(p0))`. Whether the destructor is out of line decides the key function, and so the TU that emits
the vtable, the D2 and the D0 (R6). The target's readouts:

    for i in 11176 11086 11443 12049 12050; do pnpm --silent wasm fn ../target/vota_web_wasm.wasm $i | /usr/bin/grep -m1 '^;; function'; done
      ;; function 11176 (i32)->() locals() body@0x4e5988 size 82 instrs 39
      ;; function 11086 (i32)->() locals() body@0x4e2967 size 10 instrs 4
      ;; function 11443 (i32)->() locals() body@0x5090b9 size 13 instrs 6
      ;; function 12049 (i32)->() locals(i32 i32 i32) body@0x53d30c size 119 instrs 57
      ;; function 12050 (i32)->(i32) locals(i32 i32 i32) body@0x53d384 size 116 instrs 56
    awk '$1==11176 || $1==11086 || $1==11443 || $1==12049' splat/matched.txt      # from the repository root
      11176 _ZN5comum12CSigVerifierD0Ev
      11443 _ZN5comum3asn14CVisitanteFotoD0Ev
      12049 _ZN4vota11IQRCodeBUDSD0Ev
      11086 _ZN3api17CImageFieldUpdateD0Ev

## R6. A class whose only virtual members are inline has no key function: only a TU that uses its vtable emits it

With no non-inline virtual member, the vtable, D2 and D0 are linkonce_odr, emitted only by a TU that references the
vtable, which a constructor defined there does. In the probe of R4, `NoCtor` (destructor in the class, one
non-virtual member defined) gets nothing; `Inl` (the same with a constructor defined) gets a weak vtable:

    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only /work/build/out/DOCS-A/probe/dtor.o | /usr/bin/grep -E '_ZTV|NoCtor'
      000000ae T _ZN6NoCtor1fEv
      00000040 D _ZTV3Fin
      00000010 W _ZTV3Inl
      00000000 D _ZTV3Ool

A derived class's destructor that inlines this one references the vtable too, since it stores this class's vptr
(R4). In `dtorbase.cpp`, `P2` has an inline destructor and a pure slot, and no constructor anywhere; `Q2`'s and
`Q3`'s destructors give the object `P2`'s vtable, D2 and D0, all weak (`W _ZTV2P2`, `W _ZN2P2D2Ev`, `W _ZN2P2D0Ev`
in R4's `llvm-nm`).

So to land such a class's destructors in the form the target's D0 shows (R5, in the class), a TU must also define a
constructor, at its record's line, or emit a derived class's destructor that inlines this one; the target may have
inlined the constructor everywhere, and our link then drops it as unreferenced. The out-of-line form emits them
without either but gives a D0 that calls the D2 (R5).

The typeinfo follows the same rule, and a derived class's typeinfo names its base's. So a TU that emits a derived
class's vtable needs the base's typeinfo from the TU of the base's key function, when the base has one, even if the
derived class overrides every slot. Probe `typeinfo.cpp`:

    // A derived class's typeinfo names its base's: emitted here only when the base has no key function.
    struct KeyBase { virtual ~KeyBase(); virtual void f(); };          // key function ~KeyBase(), defined in another .cpp
    struct InlBase { virtual ~InlBase() = default; virtual void f() {} };  // every virtual member inline: no key function
    struct D1 : KeyBase { void f() override; };
    struct D2 : InlBase { void f() override; };
    void D1::f() {}
    void D2::f() {}

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/DOCS2-A/probe/typeinfo.cpp -o /work/build/out/DOCS2-A/probe/typeinfo.o
    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/DOCS2-A/probe/typeinfo.o | /usr/bin/grep -E '_ZT[IV][0-9]'
      0000004c D _ZTI2D1
      00000014 D _ZTI2D2
      00000024 W _ZTI7InlBase
               U _ZTI7KeyBase
      00000038 D _ZTV2D1
      00000000 D _ZTV2D2

A link that keeps `D1`'s vtable and has no TU that defines `KeyBase`'s key function stops on `undefined symbol:
typeinfo for KeyBase`, and on `KeyBase`'s destructor as well when it is out of line, since `D1`'s calls it (R4's `Q`).
[units.md](units.md) §U9 has that link and the one that passes, and `src/units/README.md` "Pending members" says what
a unit defines then.

## R7. A slot that holds `__cxa_pure_virtual` is a pure member, and dropping it makes the class concrete

The target names `__cxa_pure_virtual` as function 12143 (`/usr/bin/grep -F '= func:12143;' splat/symbol_addrs.txt`
prints `__cxa_pure_virtual = func:12143; // size:0xc evidence:pair-addr`). An abstract class's D0 is a trap:

    python3 -I -c "import json; [print(e['class'], e['vptr'], e['functions']) for e in json.load(open('ledger/vtables.json')) if e['class']=='comum::IInterfaceInit']"
      comum::IInterfaceInit 1552160 [5898, 325, 11646, 12143, 12143, 12143, 12143, 12143]
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 325 | sed -n '/disassembly/,$p' | head -3
      000001  unreachable                                      | unreachable
      000002  end                                              | end

Probe `pure.cpp`, an abstract class beside the same class without its five pure members:

    struct Abs { virtual ~Abs(); virtual void f(); virtual void p1() = 0; virtual void p2() = 0; virtual void p3() = 0; virtual void p4() = 0; virtual void p5() = 0; };
    Abs::~Abs() {}
    void Abs::f() {}
    struct Con { virtual ~Con(); virtual void f(); };
    Con::~Con() {}
    void Con::f() {}

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/DOCS-A/probe/pure.cpp -o /work/build/out/DOCS-A/probe/pure.o
    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm -S --defined-only /work/build/out/DOCS-A/probe/pure.o | /usr/bin/grep -E '_ZTV|D0Ev'
      00000006 00000004 T _ZN3AbsD0Ev
      00000012 00000016 T _ZN3ConD0Ev
      00000000 00000028 D _ZTV3Abs
      00000038 00000014 D _ZTV3Con
    wasm-objdump -d build/out/DOCS-A/probe/pure.o | awk '/D0Ev>:/ {print; n=4; next} n-- > 0'
      0000bb func[3] <_ZN3AbsD0Ev>:
       0000bc: 00                         | unreachable
       …
      0000c7 func[6] <_ZN3ConD0Ev>:
       0000c8: 20 00                      | local.get 0
       0000ca: 10 85 80 80 80 00          | call 5 <_ZN3ConD1Ev>

So the pure members belong in the class at their slots even when no evidence names them: without them the vtable is
0x14 bytes instead of 0x28 and the D0 is a real body the target does not have. Unit 35 declares IInterfaceInit's
five, and its vtable is the target's size: `/usr/bin/grep -n 'IInterfaceInitE ' splat/symbol_addrs.txt` prints
`_ZTVN5comum14IInterfaceInitE = 0x17af18; // type:data size:0x28 …`, and `build/out/wasm-map/vota_web/vota_web_wasm.map`
gives our `_ZTVN5comum14IInterfaceInitE` size 28 (hex).

## R8. A free function's record does not show `static`; its place in its file's run of records shows its linkage

clang prints `static` in a record only for a static member function: a file-static free function's record reads like
an external one's. Its linkage is in the order of the records. clang emits an external, non-inline, non-template
function where the file defines it, and defers every other function (internal linkage, `inline`, template
instantiations, lambdas) to the end of the translation unit; a function's records are created when its body is
emitted, and the link keeps each object's order. Probe `order_ext.cpp`, and `order_static.cpp` the same with `static
void a()`:

    #include <source_location>
    void use(const std::source_location &);
    void a() { use(std::source_location::current()); }
    void b() { use(std::source_location::current()); a(); }
    void c() { use(std::source_location::current()); a(); }

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/build/out/DOCS-A/probe/<v>.cpp -o /work/build/out/DOCS-A/probe/<v>.ll
    /usr/bin/grep -oE 'i32 [345], i32 [0-9]+ \}' build/out/DOCS-A/probe/<v>.ll | awk '{print $2}' | tr -d ',' | tr '\n' ' '
      order_ext:    3 4 5                 # the records' lines, in module order
      order_static: 4 5 3

In the target, `api/util/csystem.cpp`'s run (address, line, function):

    awk -F'\t' '$2 ~ /api\/util\/csystem\.cpp/ {print $1, $3, $5}' ledger/source-locations.tsv | sort -n
      1584628 236 static std::string api::CSystem::TemporaryPath(const std::string &)
      …                                   # static members at lines 243 to 745, in line order
      1584900 1024 void api::truncate(int, off_t, const std::string &)
      1584916 1039 static void api::CSystem::ZeroFill(const std::string &)
      1584932 64 bool api::ExistResource(struct stat &, const std::string &)
      1584948 916 std::string api::(anonymous namespace)::PrepareReplace(…)
      …                                   # 922 928, then ReplaceResource (anonymous namespace) 954 962

`api::truncate` (line 1024) sits in line order among the eagerly emitted functions: external. `api::ExistResource`
(line 64) comes after the last of them, at the head of the deferred anonymous-namespace helpers: file-static, so its
symbol is the internal `_ZN3apiL13ExistResource…`, no header declares it, and it stays out of line only when callers
in its own file keep it there. A caller of it from another file in `ledger/callgraph.tsv` is binaryen inlining across
translation units, not a call in the source.

## R9. A member with no record: its place in its use band says whether the `.cpp` defines it

`ledger/ordinals.tsv` column `uses` is the band key binaryen's `reorder-functions` sorted by (direct call sites plus
table entries plus exports); inside a band the index runs in reverse link order within a digit zone
(`docs/reference/link-order.md` section 1). `ledger/functions.tsv`'s `uses` and the `fn` header count direct calls
only, so they can put an address-taken function one band lower. `comum::IInterfaceInit`'s destructor 5898 has no
record:

    awk -F'\t' '$1>=5893 && $1<=5900 {print $1, $2}' ledger/ordinals.tsv
      5893 2 / 5894 2 / 5895 2 / 5896 2 / 5897 2 / 5898 2 / 5899 2 / 5900 2       (one per line)
    awk -F'\t' '$6 ~ /(^|,)(5894|5896|5897)(,|$)/ {print $6, $3, $5}' ledger/source-locations.tsv
      5897 148 bool comum::IInterfaceInit::IsMRMontadoSemHabilitar()
      5896 159 void comum::IInterfaceInit::MontarMRSemHabilitar()
      …
      5894 522 void comum::IInterfaceInit::DesligarUrna()

So 5898 comes before line 148's function in the object. An inline or implicit destructor, which only the vtable
references, is emitted after the TU's external functions, after 5894. 5898 is defined in `iinterfaceinit.cpp`
above line 148, as unit 35 writes it.

## R10. Code binaryen inlined from an out-of-line function of the source

A body can hold code that was a separate function in the object, which wasm-opt inlined into its only caller; that
function then has no target index of its own, and the source defines it out of line, unrooted
(`src/units/README.md` "Companion files"). Two tells in a readout:

- **A second stack-pointer prologue inside the body.** clang merges an inlined callee's frame into the caller's;
  binaryen keeps the callee's own. In `api::CTime::operator-(int) const` (3641) the `if (p1 < 0)` arm opens a
  frame of its own, `operator+=`'s:

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 3641 | sed -n '/folded readout/,/^}/p' | /usr/bin/grep -n 'g0'
        4:  l2 = i32.sub(g0, 16);
        5:  g0 = l2;
        11:        l3 = i32.sub(g0, 32);
        12:        g0 = l3;
        29:              g0 = i32.add(l3, 32);
        44:    g0 = i32.add(l2, 16);

- **Byte arguments widened as for a call and held in locals before the stores.** clang zero-extends a `uebyte`
  argument of an out-of-line call (`i32.load8_u`); a constructor clang inlines stores what it loads at once. In
  `comum::asn::CConversorSituacoesEleicoes::DoDesconverte` (11361) the `comum::md::CSituacoesEleicoes` constructor's
  arguments are loaded into locals, its `this` is `l4 + 8`, and the stores follow:

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11361 | sed -n '/folded readout/,/^}/p' | /usr/bin/grep -n 'load8_u\|store8\|l3 = \|i32.store\[l3\]'
        16:        l7 = i32.load8_u[i32.load[p1+8]+8];
        17:        l8 = i32.load8_u[i32.load[p1+12]+8];
        18:        l3 = i32.add(l4, 8);
        19:        i32.store8[l3+6] = i32.load8_u[i32.load[p1+16]+8];
        20:        i32.store8[l3+5] = l8;
        21:        i32.store8[l3+4] = l7;
        22:        i32.store[l3] = l6;

  Unit 47 (commit 9159e6c, branch `decomp/decomp3-i`) defines that constructor out of line in
  `md/processoeleitoral/csituacoeseleicoes.cpp` and matches 11361 (`git show 9159e6c:splat/matched.txt | awk
  '$1==11361'`).

## R11. A record fixes the function's qualified name and its types' spelling, not the scope of a type it prints unqualified

clang's function-name text spells a parameter type as the source wrote it. A type written unqualified prints the
same from any scope, while the scope is part of the mangled name. Probe `scope.cpp`:

    #include <source_location>
    #include <vector>
    void use(const std::source_location &);
    struct GFrame {};
    namespace api {
    struct CMovieFrame {};
    struct A { A(std::vector<CMovieFrame>); };
    A::A(std::vector<CMovieFrame>) { use(std::source_location::current()); }
    struct B { B(std::vector<GFrame>); };
    B::B(std::vector<GFrame>) { use(std::source_location::current()); }
    struct C { struct GFrame {}; C(std::vector<GFrame>); };
    C::C(std::vector<GFrame>) { use(std::source_location::current()); }
    }

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/build/out/DOCS-A/probe/scope.cpp -o /work/build/out/DOCS-A/probe/scope.ll
    /usr/bin/grep -oE 'c"api::[ABC]::[ABC]\([^"]*\\00"' build/out/DOCS-A/probe/scope.ll
      c"api::A::A(std::vector<CMovieFrame>)\00"
      c"api::B::B(std::vector<GFrame>)\00"
      c"api::C::C(std::vector<GFrame>)\00"
    /usr/bin/grep -oE 'define [^@]*@_ZN3api1[ABC]C2E[A-Za-z0-9_]+' build/out/DOCS-A/probe/scope.ll | sed 's/.*@//'
      _ZN3api1AC2ENSt3__26vectorINS_11CMovieFrameENS1_9allocatorIS3_EEEE
      _ZN3api1BC2ENSt3__26vectorI6GFrameNS1_9allocatorIS3_EEEE
      _ZN3api1CC2ENSt3__26vectorINS0_6GFrameENS1_9allocatorIS3_EEEE

B's global `GFrame` and C's nested one give the same text and two symbols. `api::CMovie`'s record,
`api::CMovie::CMovie(std::vector<CMovieFrame>, const SPoint &)` (`awk -F'\t' '$6 ~ /(^|,)5526(,|$)/ {print $5}'
ledger/source-locations.tsv`), leaves `CMovieFrame`'s scope open in the same way, and no RTTI or vtable names the type
(`/usr/bin/grep -c CMovieFrame ledger/classes.json ledger/vtables.json` prints 0 for both). Unit 23 puts it in `api`,
the namespace of `CMovie`.

## R12. A class passed by value is the address of a copy, unless it is one scalar; libc++'s smart pointers are trivial-ABI here

clang's WebAssembly ABI passes a class argument by value as the address of a copy the caller makes, except a
trivially copyable (or trivial-ABI) class of one scalar, which travels as that scalar (R3 is the same rule for a
result). The pinned libc++ is ABI v2 (`std::__2`), which marks `std::shared_ptr` and `std::unique_ptr` trivial-ABI: the
callee owns the copy and destroys it, so a parameter moved into a member leaves nothing to write back. Probe
`byvalue.cpp`:

    // Three ways to pass a std::shared_ptr into a constructor, and two for a std::unique_ptr.
    #include <memory>
    struct I { virtual ~I(); };
    struct Val { virtual ~Val(); Val(std::shared_ptr<I> a, std::shared_ptr<I> b); std::shared_ptr<I> m_a, m_b; };
    Val::Val(std::shared_ptr<I> a, std::shared_ptr<I> b) : m_a(std::move(a)), m_b(std::move(b)) {}
    struct RRef { virtual ~RRef(); RRef(std::shared_ptr<I> &&a, std::shared_ptr<I> &&b); std::shared_ptr<I> m_a, m_b; };
    RRef::RRef(std::shared_ptr<I> &&a, std::shared_ptr<I> &&b) : m_a(std::move(a)), m_b(std::move(b)) {}
    struct CRef { virtual ~CRef(); CRef(const std::shared_ptr<I> &a, const std::shared_ptr<I> &b); std::shared_ptr<I> m_a, m_b; };
    CRef::CRef(const std::shared_ptr<I> &a, const std::shared_ptr<I> &b) : m_a(a), m_b(b) {}
    struct UVal { virtual ~UVal(); UVal(std::unique_ptr<I> a); std::unique_ptr<I> m_a; };
    UVal::UVal(std::unique_ptr<I> a) : m_a(std::move(a)) {}
    struct URef { virtual ~URef(); URef(std::unique_ptr<I> &&a); std::unique_ptr<I> m_a; };
    URef::URef(std::unique_ptr<I> &&a) : m_a(std::move(a)) {}

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/DOCS2-A/probe/byvalue.cpp -o /work/build/out/DOCS2-A/probe/byvalue.o
    wasm-objdump -d build/out/DOCS2-A/probe/byvalue.o | awk '/ func\[/ {name=$3} /store/ {c[name]++} END {for (k in c) print c[k], k}' | sort -k2
      5 <_ZN3ValC1ENSt3__210shared_ptrI1IEES3_>:                           # the vptr and four words copied
      7 <_ZN4CRefC1ERKNSt3__210shared_ptrI1IEES5_>:                        # and a count increment per source
      7 <_ZN4RRefC1EONSt3__210shared_ptrI1IEES4_>:                         # and an i64.store 0 per source
      3 <_ZN4URefC1EONSt3__210unique_ptrI1INS0_14default_deleteIS2_EEEE>:
      2 <_ZN4UValC1ENSt3__210unique_ptrI1INS0_14default_deleteIS2_EEEE>:
    for s in _ZN4UValC1 _ZN4URefC1; do printf '%s: ' $s; wasm-objdump -d build/out/DOCS2-A/probe/byvalue.o | awk -v s="<$s" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -vE '^$|^end$|^local\[' | tr '\n' ';'; echo; done
      _ZN4UValC1: local.get 0;local.get 1;i32.store 2 4;local.get 0;global.get 3 <GOT.mem._ZTV4UVal>;i32.const 8;i32.add;i32.store 2 0;local.get 0;
      _ZN4URefC1: local.get 0;global.get 4 <GOT.mem._ZTV4URef>;i32.const 8;i32.add;i32.store 2 0;local.get 1;i32.load 2 0;local.set 2;local.get 1;i32.const 0;i32.store 2 0;local.get 0;local.get 2;i32.store 2 4;local.get 0;

The by-value `unique_ptr` parameter is the raw pointer (`p1` stored at +4); the `&&` one is an address, loaded and
nulled. `comum::CParteCargos`'s constructor 5587 is `Val`'s shape, the vptr store and four copied words:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5587 | sed -n '/folded readout/,/^}/p'
      ;; --- folded readout (approximate)
      function f5587(i32 p0, i32 p1, i32 p2) -> (i32) {
        i32.store[p0] = 1576564;
        i32.store[p0+4] = i32.load[p1];
        i32.store[p0+8] = i32.load[p1+4];
        i32.store[p0+12] = i32.load[p2];
        i32.store[p0+16] = i32.load[p2+4];
        push p0;
      }

## R13. A `std::format` throw spells its format string and argument types in two i64 constants

A uenux2 throw that builds its message with `std::format` stores two i64 constants into the format call's
arguments: `(length << 32) | address` of the format string (its `string_view`), and the argument types packed 5 bits
each, the first argument lowest (libc++'s `__packed_arg_t_bits`). The type codes are libc++'s `__arg_t`, counted from
0:

    TMPDIR=/tmp build/docker-build.sh sh -c 'sed -n 61,79p /emsdk/upstream/emscripten/cache/sysroot/include/c++/v1/__format/format_arg.h'
      enum class __arg_t : uint8_t {
        __none,
        __boolean,
        __char_type,
        __int,
        __long_long,
        __i128, // extension
        __unsigned,
        __unsigned_long_long,
        __u128, // extension
        __float,
        __double,
        __long_double,
        __const_char_type_ptr,
        __string_view,
        __ptr,
        __handle
      };
    TMPDIR=/tmp build/docker-build.sh sh -c 'grep -n "__packed_arg_t_bits =" /emsdk/upstream/emscripten/cache/sysroot/include/c++/v1/__format/format_arg.h'
      80:inline constexpr unsigned __packed_arg_t_bits = 5;

`api::CSystem::GetFileSize` (2759, matched) and `api::CLedFieldMT::Draw` (11050):

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 2759 | /usr/bin/grep -E 'i64.store\[l[0-9]+\+(24|16)\]'
        i64.store[l1+24] = 180388633521;
        i64.store[l1+16] = 397;
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11050 | /usr/bin/grep -E 'i64.store\[l[0-9]+\+(24|16)\]'
        i64.store[l2+16] = 3;
        i64.store[l2+24] = 103079218254;
    python3 -I -B -c "print(180388633521 >> 32, 180388633521 & 0xffffffff, [(397 >> (5*i)) & 31 for i in range(2)], 103079218254 >> 32, 103079218254 & 0xffffffff)"
      42 7089 [13, 12] 24 3150
    awk -F'\t' '$1==7089 || $1==3150 {print $1, $2, $4}' ledger/strings.tsv      # from the repository root
      3150 24 Operação desconhecida {}
      7089 42 Falha ao obter tamanho do arquivo [{}]: {}

So 2759 formats a `std::string` (13, `__string_view`) and a `const char*` (12), and 11050 one `int` (3). The code is
the type `std::format` sees after its own conversions, not the variable's: `std::format` has no formatter for an
enum, so the source casts one, and the code is the cast's type.
