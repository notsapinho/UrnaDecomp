# Reading the source from the target's bytes

What a target body says about the C++ that compiled to it, beyond the name its `std::source_location` record gives:
the parameters a wasm type hides, how a class returns or takes a class by value, how a destructor is declared and
whether its class is `final`, whether a class is abstract or has a key function, a free function's linkage, code
binaryen inlined from another function, the format string, argument types and shape of a `std::format` throw, a
`bool`'s reads and a byte's sign, an `invoke` around a callee that cannot throw, several table slots of one function, a
local static's guard, one row more than the target at a call, where a record's line and column fall when no `throw`
makes it, and a slot's vtable read from the data. `docs/how-to-decompile.md` steps 2, 3 and 5 rely on these. What a
source form compiles to (the order of a body's stores, a switch over virtual slots, an in-class member against an
`inline` one) is in [codegen.md](codegen.md).

The probes are short TUs compiled by the pinned em++ with uenux2's flags of the time, `-O2 -fPIC -std=c++20 -DNDEBUG
-fno-strict-aliasing`, or `-O3` where they say so (the tree's level since: [app-flags.md](app-flags.md) §F6); their
sources are given in full, and each runs under `build/out/reading-probe/`. R1–R3 and R7–R11 were measured at 7bf701e,
R4–R6, R12 and R13 at ee595de, and the parts marked bb6f018 (R14 and R15 among them) at bb6f018; every probe prints the
same at 0b5f410, where R13's shapes and R16–R18 were measured, and the parts marked 4487d6b and R19 at 4487d6b; the
`-O3` probes and R20 at c1b2630. Readouts are `pnpm --silent wasm fn ../target/vota_web_wasm.wasm <index>`, run from
`asmlift-wasm/` with Node 24 first on PATH ([workflow.md](workflow.md) §W1).

## R1. A parameter every caller passes as the same constant is gone from the wasm type

binaryen's dead-argument elimination removes a parameter that every call site passes as the same constant and puts
the constant into the body. So a wasm type can have fewer parameters than the C++ function, and a constant the body
stores can be an argument of the source (R18 is the same pass seen from the caller). `comum::ValidarUE` has three parameters in its record and two in wasm:

    awk -F'\t' '$6 ~ /(^|,)5890(,|$)/ {print $5}' ledger/source-locations.tsv
      void comum::ValidarUE(IInterfaceSavd &, ESavdAplic, const std::string &)
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5890 | sed -n 1p
      ;; function 5890 (i32 i32)->() locals(i32 i32 i32 i32 i32 i64) body@0x30b794 size 717 instrs 310

Unit 26 writes `comum::CSigVerifier`'s constructor (1540) with the `ESavdAplic` parameter the target folded, and
its roots callers pass the constant, so the source invents no enumerator for it (`src/units/26-uenux2-csigverifier-roots.cpp`).

A test of the folded argument goes with it, and its throw's record stays in the data with no function loading it
(column 6 empty in `ledger/source-locations.tsv`). `cidentificacaosecao.cpp:33:19` and
`cidentificacaournacontingencia.cpp:32:19` belong to the constructors of 5887 and 5888, which call `f5886(p0, 49, p1,
p2)` and `f5886(p0, 50, p1, p2)`: each tested the urn type its callers all pass. Write the test at the record's line,
with every caller and stand-in passing the constant (unit 143). Its message is among the strings no function loads:
find the text, then check that no target piece holds its address and, for a `std::format` string, no packed `i64.const`
either (R13):

```sh
awk -F'\t' '$4 ~ /urna de se/' ledger/strings.tsv
# 361994	33	latin1	Tipo inválido para urna de seção.
/usr/bin/grep -rlE 'i32\.const 361994($|[^0-9])' build/out/splat/pieces/asm      # prints nothing
```

Which throw holds which such literal is then the only choice (`src/uenux2/src/api/ipc/posix/cposixrwmutex.cpp`).

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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/dtor.cpp -o build/out/reading-probe/dtor.o
    wasm-objdump -d build/out/reading-probe/dtor.o | awk '/D2Ev>:|D1Ev>:/ {print; n=6; next} n-- > 0' | /usr/bin/grep -E 'func\[|i32.store|GOT'
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
(its slot 0 holds the base's), with its destructor implicit or defined in the class: over a base D2 in another object,
the implicit form, `~D() override = default;` and `~D() override {}` compile to one object (R5, "A derived class with no
member of its own"). Probe `dtorbase.cpp`:

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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/dtorbase.cpp -o /work/build/out/reading-probe/dtorbase.o
    for s in _ZN1QD2Ev _ZN2Q2D2Ev _ZN2Q3D2Ev; do printf '%s: ' $s; wasm-objdump -d build/out/reading-probe/dtorbase.o | awk -v s="<$s>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -E 'call |GOT.mem' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| *//' | tr '\n' ';'; echo; done
      _ZN1QD2Ev: global.get 0 <GOT.mem._ZTV1Q>;call 0 <env._ZdlPvm>;call 1 <env._ZN1PD2Ev>;
      _ZN2Q2D2Ev: global.get 1 <GOT.mem._ZTV2Q2>;call 0 <env._ZdlPvm>;global.get 2 <GOT.mem._ZTV2P2>;call 0 <env._ZdlPvm>;
      _ZN2Q3D2Ev: call 0 <env._ZdlPvm>;global.get 2 <GOT.mem._ZTV2P2>;call 0 <env._ZdlPvm>;

`Q3`'s D2 begins with its string and stores `P2`'s vptr before `P2`'s string; `Q2`'s stores its own vptr first. `Q`
calls `P`'s out-of-line D2 instead of inlining it (R5). The symbols (R6 reads them too):

    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/reading-probe/dtorbase.o | /usr/bin/grep -E 'D[012]Ev|_ZTV'
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

The base's vptr store says less than the class's own. clang marks a destructor's `this` dead on return, so LLVM
deletes the store of an inlined base destructor when nothing after it can read the vptr: only a call in the base
destructor's body keeps it. Probe `basevptr.cpp` (bb6f018):

    // Whether a derived class's destructor keeps the vptr store of the base destructor it inlines.
    #include <string>
    void hook();
    struct Base {
    #if FORM == 0
        virtual ~Base() = default;            // empty
    #elif FORM == 1
        virtual ~Base() { (void)0; }          // a body that does nothing
    #elif FORM == 2
        virtual ~Base() { hook(); }           // a body that makes a call
    #endif
        virtual void f();
    };
    struct Derived : Base { ~Derived() override; void f() override; std::string s; };
    Derived::~Derived() = default;
    void Derived::f() {}

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 2; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/reading-probe/basevptr.cpp -o /work/build/out/reading-probe/basevptr-$f.o; done'
    for f in 0 1 2; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/reading-probe/basevptr-$f.o | awk '/<_ZN7DerivedD1Ev>:/ {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -oE 'GOT\.mem\._ZTV[0-9A-Za-z]+|call [0-9]+ <[^>]+>' | sed -E 's/call [0-9]+ //' | tr '\n' ' '; echo; done
      FORM 0: GOT.mem._ZTV7Derived <env._ZdlPvm>
      FORM 1: GOT.mem._ZTV7Derived <env._ZdlPvm>
      FORM 2: GOT.mem._ZTV7Derived <env._ZdlPvm> GOT.mem._ZTV4Base <env._Z4hookv>

So a derived D2 without the base's vptr store says that the base destructor's body makes no call, not that it is
empty, inline or `= default`, and that form is a choice (unit 62's fragment says so of `api::CEscritorLog` under
`simulador::CWasmLogd`'s 8318).

**`final` where the D2 holds nothing to read.** A class whose destructor destroys nothing has one of binaryen's
shared bodies in slot 0 (174, `return this`), which shows no store at all. When the target builds the class with
`std::make_shared`, its control block shows it instead: `__shared_ptr_emplace<T>`'s slot 2, `__on_zero_shared`,
destroys `T` through `T`'s vtable unless `T` or its destructor is `final`, and then the call devirtualizes to the
empty destructor and the slot holds the shared empty body 218:

    python3 -I -c "import json; [print(e['class'], e['functions']) for e in json.load(open('ledger/vtables.json')) if 'CEsperaAudio' in e['class']]"
      std::__2::__shared_ptr_emplace<api::CEsperaAudio, std::__2::allocator<api::CEsperaAudio> > [9506, 9501, 218, 519, 144]
      api::CEsperaAudio [174, 144, 9509, 2683]
      std::__2::__shared_ptr_emplace<simulador::(anonymous namespace)::CEsperaAudioWasm, …> [9490, 9481, 9472, 519, 144]
      simulador::(anonymous namespace)::CEsperaAudioWasm [9459, 9448, 2680, 9445]

Probe `onzero.cpp`:

    // What std::make_shared's control block does on the last release, for a class whose destructor does nothing.
    #include <memory>
    struct I { virtual ~I() = default; virtual void f() = 0; };
    struct T FINAL : I { void f() override; };
    void T::f() {}
    std::shared_ptr<I> Make() { return std::make_shared<T>(); }

    TMPDIR=/tmp build/docker-build.sh sh -c 'em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFINAL= -c /work/build/out/reading-probe/onzero.cpp -o /work/build/out/reading-probe/onzero-open.o && em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFINAL=final -c /work/build/out/reading-probe/onzero.cpp -o /work/build/out/reading-probe/onzero-final.o'
    for v in open final; do printf '%s: ' $v; wasm-objdump -d build/out/reading-probe/onzero-$v.o | awk '/__on_zero_shared/ && / func\[/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -vE '^$' | tr '\n' ';'; echo; done
      open: local.get 0;i32.const 12;i32.add;local.get 0;i32.load 2 12;i32.load 2 0;call_indirect 0 <env.__indirect_function_table> (type 1);drop;end;local.get 0;i32.const 16;call 1 <env._ZdlPvm>;end;
      final: end;local.get 0;i32.const 16;call 1 <env._ZdlPvm>;end;

(The second body each prints is `__on_zero_shared_weak`.) `api::CEsperaAudio` is `final` in
`src/uenux2/src/api/audio/cesperaaudio.h`; `CEsperaAudioWasm`'s slot 2, 9472, is a body of its own.

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

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 2 3 4 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/reading-probe/dtorform.cpp -o /work/build/out/reading-probe/dtorform-$f.o; done'
    for f in 0 1 2 3 4 5; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/reading-probe/dtorform-$f.o | awk '/<_ZN1XD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} END {print n " lines, calls at depth 0:" c}'; done
      FORM 0: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 1: 5 lines, calls at depth 0: <_ZN1XD2Ev> <env._ZdlPvm>
      FORM 2: 5 lines, calls at depth 0: <_ZN1XD2Ev> <env._ZdlPvm>
      FORM 3: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 4: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 5: 7 lines, calls at depth 0: <_ZN1XD1Ev> <env._ZdlPvm>
    cmp build/out/reading-probe/dtorform-0.o build/out/reading-probe/dtorform-3.o && cmp build/out/reading-probe/dtorform-3.o build/out/reading-probe/dtorform-4.o && cmp build/out/reading-probe/dtorform-1.o build/out/reading-probe/dtorform-2.o && echo 'FORM 0 = 3 = 4, FORM 1 = 2'
      FORM 0 = 3 = 4, FORM 1 = 2

| form | D0 | in the target |
| --- | --- | --- |
| implicit, or declared `inline` (in the class, or `inline X::~X() = default;` after it: the same object) | the D2's body inlined, then `operator delete` | 11176 (82 B, `comum::CSigVerifier`, implicit, unit 26) |
| in the class without `inline` (`= default` or `{}`: the same object) | `call D2` and `operator delete` of its result | `f136(f5531(p0))`, 11086 (10 B, `api::CImageFieldUpdate`, unit 43) |
| out of line in the `.cpp` | `call D1` (D2's alias), `drop`, `operator delete(this)` | `f5709(p0); f136(p0);`, 11443 (13 B, `comum::asn::CVisitanteFoto`, unit 36) |

These shapes are `-fPIC`'s, uenux2's. Without `-fPIC`, ecourna's flags, the third row's D0 can take the second row's
shape. Probe `dtorpic.cpp`, a `final` class whose out-of-line destructor has only an out-of-line base's to call:

    // A final class with an out-of-line destructor over a base whose destructor is out of line in another object.
    #include <memory>
    #include <string>
    struct B {
        B(int, const std::string&);
        virtual ~B();
        virtual std::string F() const = 0;
        int t;
        std::string n;
    };
    struct D final : B {
        explicit D(const std::string&);
        ~D() override;
        std::string F() const override;
    };
    D::D(const std::string& s) : B(1, s) {}
    D::~D() = default;
    std::string D::F() const { return n; }
    std::shared_ptr<B> Make(const std::string& s) { return std::make_shared<D>(s); }

    TMPDIR=/tmp build/docker-build.sh sh -c 'cd /work/build/out/reading-probe; em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c dtorpic.cpp -o dtorpic-pic.o; em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c dtorpic.cpp -o dtorpic-pic3.o; em++ -O2 -std=c++20 -DNDEBUG -fno-strict-aliasing -c dtorpic.cpp -o dtorpic-nopic.o; em++ -O3 -fexceptions -std=c++20 -DNDEBUG -fno-strict-aliasing -c dtorpic.cpp -o dtorpic-nopic3.o'
    for v in pic pic3 nopic nopic3; do printf '%s D0: ' $v; wasm-objdump -d build/out/reading-probe/dtorpic-$v.o | awk '/<_ZN1DD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^(call|drop)/ {c = c " " $1 " " $3} END {print n " lines:" c}'; done
      pic D0: 7 lines: call <_ZN1DD1Ev> drop  call <env._ZdlPvm>
      pic3 D0: 7 lines: call <_ZN1DD1Ev> drop  call <env._ZdlPvm>
      nopic D0: 5 lines: call <env._ZN1BD2Ev> call <env._ZdlPvm>
      nopic3 D0: 5 lines: call <env._ZN1BD2Ev> call <env._ZdlPvm>

So the level does not decide it, `-fPIC` does. In ecourna's code `f136(f778(p0))` (3491, 10 B, `CNumeroCPF`'s) is
that out-of-line form, its D1 one call of the base's D2: read the classes' other destructors (the D1 and the control
block's `__on_zero_shared`) before taking it for the in-class form. What `-fPIC` keeps is the call of the D1 alias, at
the default visibility it gives ([codegen.md](codegen.md) §C6 measures it against a plain function and hidden
visibility). `wasm-objdump -d -r` names such a call D2 whichever alias it holds; the symbol table says which
([tool-traps.md](tool-traps.md) §X11).

A class with no D0 (no vtable, or no destructor slot in it) shows the form in a caller instead: at `-fPIC` a caller in
the destructor's own TU keeps a call of an out-of-line D1 (C6), where an implicit or in-class destructor of a small
body is inlined. `comum::CCargos`'s exit destructor calls `~CCargos` (5805) so, which `ccargos.cpp` defines `= default`.

What separates the first two rows is the inline hint. Only an implicit destructor and one declared `inline` carry it
before optimization:

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 3 4 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -S -emit-llvm -Xclang -disable-llvm-passes /work/build/out/reading-probe/dtorform.cpp -o /work/build/out/reading-probe/dtorform-$f.ll; done'
    for f in 0 1 3 4 5; do a=$(/usr/bin/grep -E '^define .*@_ZN1XD2Ev\(' build/out/reading-probe/dtorform-$f.ll | /usr/bin/grep -oE '#[0-9]+'); printf 'FORM %s: %s\n' $f "$(/usr/bin/grep -E "^attributes $a " build/out/reading-probe/dtorform-$f.ll | /usr/bin/grep -oE 'inlinehint' || echo no inlinehint)"; done
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

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 1 3 5; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/reading-probe/dtorroot.cpp -o /work/build/out/reading-probe/dtorroot-$f.o; done'
    for f in 1 3 5; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/reading-probe/dtorroot-$f.o | awk '/<_ZN1RD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} END {print n " lines, calls at depth 0:" c}'; done
      FORM 1: 5 lines, calls at depth 0: <_ZN1RD2Ev> <env._ZdlPvm>
      FORM 3: 87 lines, calls at depth 0: <env._ZdlPvm>
      FORM 5: 7 lines, calls at depth 0: <_ZN1RD1Ev> <env._ZdlPvm>

So a root class whose D0 holds a D2 too costly for the plain in-class form declares it `inline`.

The hint raises the threshold, not without limit (LLVM's remarks give 325 against 225: [levels.md](levels.md) §V2).
Above it an implicit destructor gives the in-class shape as well, a D0 that calls the D2, so that shape alone does not
separate the two forms. Probe `dtorcost.cpp` (bb6f018), two `final` classes of three
and five `std::shared_ptr` members:

    // An implicit (hinted) destructor whose D2 costs more than the hinted threshold: the D0 calls the D2 as the in-class form does.
    #include <memory>
    struct B { virtual ~B() = default; virtual void key(); };
    struct C3 final : B { std::shared_ptr<int> a, b, c; void key() override; DTOR(C3) };
    struct C5 final : B { std::shared_ptr<int> a, b, c, d, e; void key() override; DTOR(C5) };
    void C3::key() {}
    void C5::key() {}

    TMPDIR=/tmp build/docker-build.sh sh -c 'em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing "-DDTOR(X)=" -c /work/build/out/reading-probe/dtorcost.cpp -o /work/build/out/reading-probe/dtorcost-implicit.o && em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing "-DDTOR(X)=~X() override = default;" -c /work/build/out/reading-probe/dtorcost.cpp -o /work/build/out/reading-probe/dtorcost-inclass.o'
    for v in implicit inclass; do for c in C3 C5; do printf '%s %s D0: ' $v $c; wasm-objdump -d build/out/reading-probe/dtorcost-$v.o | awk -v s="<_ZN2${c}D0Ev>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} END {print n " lines, calls:" c}'; done; done
      implicit C3 D0: 74 lines, calls: <env._ZdlPvm>
      implicit C5 D0: 5 lines, calls: <_ZN2C5D2Ev> <env._ZdlPvm>
      inclass C3 D0: 74 lines, calls: <env._ZdlPvm>
      inclass C5 D0: 5 lines, calls: <_ZN2C5D2Ev> <env._ZdlPvm>
    cmp build/out/reading-probe/dtorcost-implicit.o build/out/reading-probe/dtorcost-inclass.o && echo same
      same

A `final` class's D2 has no vptr store to cost, so the plain threshold holds its three-pointer D2 too, and for such a
class the two forms are one object at both sizes. `comum::CParteCandidatos`, `final` with five `shared_ptr` members
and an implicit destructor (unit 77), has the 10-B D0 5590, `f136(f2876(p0))`, over its 256-B D2. Only the out-of-line form's D0 (`call D1`, `drop`, free) stays
apart; between the other two, compare the forms in the class's own shape.

In a class template the two in-class spellings, `= default` and `{}`, give the same bodies, and in the small case
below the same object; in `api::CPriorityMessageQueue<T>` (unit 64) `{}` moves the D0 later in the object, which
changes no byte of the link's functions (the fragment's measurement). Probe `dtortmpl.cpp`:

    // A class template's destructor written `= default` or `{}` in the class, under implicit instantiation.
    #include <string>
    struct B { virtual ~B() = default; virtual void f() = 0; };
    template <class T> struct Q : B {
        T t;
        std::string s;
        void f() override { s += 'x'; }
    #if FORM == 1
        ~Q() override = default;
    #else
        ~Q() override {}
    #endif
    };
    B *make() { return new Q<int>; }

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 1 2; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/reading-probe/dtortmpl.cpp -o /work/build/out/reading-probe/dtortmpl-$f.o; done'
    cmp build/out/reading-probe/dtortmpl-1.o build/out/reading-probe/dtortmpl-2.o && echo same
      same

So compare such forms by function, not by `cmp` of the object.

The D2 is the same in every form: its body differs only in the object-local type index of a `call_indirect`.

    for f in 0 1 5; do wasm-objdump -d build/out/reading-probe/dtorform-$f.o | awk '/<_ZN1XD[12]Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //; s/(call|global.get) [0-9]+ /\1 /' > build/out/reading-probe/d2-$f.txt; done
    diff build/out/reading-probe/d2-0.txt build/out/reading-probe/d2-1.txt && echo 'D2: FORM 0 = 1'
      D2: FORM 0 = 1
    diff build/out/reading-probe/d2-0.txt build/out/reading-probe/d2-5.txt
      58c58
      <         call_indirect 0 <env.__indirect_function_table> (type 0)
      ---
      >         call_indirect 0 <env.__indirect_function_table> (type 2)

So a D2 that matches settles nothing about the form; a derived class's D2 does, since it inlines a base destructor
with the hint or defined in the class and calls one defined out of line (R4's `Q`). A class with no member of its own
has the base's D2 in its slot (R4's `Q4`). When that D2 is out of line, the class's D0 is the 10-B shape around it:
`simulador::CWasmInit`'s vtable starts `[5898, 9388]`, 5898 being `comum::IInterfaceInit`'s out-of-line D2 (R9), and
9388 is `f136(f5898(p0))`. Whether the destructor is out of line decides the key function, and so the TU that emits
the vtable, the D2 and the D0 (R6). A derived class with no member of its own, whose destructor is out of line, is
below. The target's readouts:

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

"No member of its own" here means no member whose destruction emits code: a class can hold scalars and still show these
shapes. `vota::CThreadMonitor`'s vtable starts `[2126, 10227]`, its base's D2 and `f2126(p0); f136(p0)`, and its
singleton 1898 allocates 48 bytes and stores a byte at +36 and an i64 at +40 (`pnpm --silent wasm fn
../target/vota_web_wasm.wasm 1898`): read the size from the allocation, not from the slots.

**A derived class with no member of its own.** Its D0 and its slot 0 together say where each destructor is. Probe
`d0.cpp` (0b5f410), `B` with two `shared_ptr` members, `BASE` where `B`'s destructor is (0 out of line in another TU,
1 in the class, 3 out of line in this TU), `DER` where `D`'s is (0 implicit, 2 out of line here):

    // A derived destructor over its base's: BASE 0 out of line in another TU, 1 in the class, 3 out of line here; DER 0 implicit, 2 out of line here.
    #include <memory>
    struct R { virtual ~R(); virtual void key(); };
    struct B : R {
        std::shared_ptr<int> a, b;
    #if BASE == 1
        ~B() override = default;
    #else
        ~B() override;
    #endif
        void key() override;
    };
    #if BASE == 3
    B::~B() = default;
    #endif
    struct D : B {
    #if DER == 2
        ~D() override;
    #endif
        void key() override;
    };
    #if DER == 2
    D::~D() = default;
    #endif
    void D::key() {}

    TMPDIR=/tmp build/docker-build.sh sh -c 'for b in 0 1 3; do for d in 0 2; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DBASE=$b -DDER=$d -c /work/build/out/reading-probe/d0.cpp -o /work/build/out/reading-probe/d0-$b-$d.o; done; done'
    for b in 0 1 3; do for d in 0 2; do printf 'BASE %s DER %s D0: ' $b $d; wasm-objdump -d build/out/reading-probe/d0-$b-$d.o | awk '/<_ZN1DD0Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} /^call/ {c = c " " $3} /^drop/ {c = c " drop"} END {print n " lines:" c}'; done; done
      BASE 0 DER 0 D0: 5 lines: <env._ZN1BD2Ev> <env._ZdlPvm>
      BASE 0 DER 2 D0: 7 lines: <_ZN1DD1Ev> drop <env._ZdlPvm>
      BASE 1 DER 0 D0: 57 lines: <env._ZN1RD2Ev> <env._ZdlPvm>
      BASE 1 DER 2 D0: 7 lines: <_ZN1DD1Ev> drop <env._ZdlPvm>
      BASE 3 DER 0 D0: 57 lines: <env._ZN1RD2Ev> <env._ZdlPvm>
      BASE 3 DER 2 D0: 7 lines: <_ZN1DD2Ev> drop <env._ZdlPvm>
    for b in 0 1 3; do printf 'BASE %s DER 2: ' $b; TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only build/out/reading-probe/d0-$b-2.o | /usr/bin/grep -E '_ZN1[BD]D[12]Ev' | tr -s ' ' | cut -d' ' -f1,3 | tr '\n' ';'; echo; done
      BASE 0 DER 2: 00000001 _ZN1DD1Ev;00000001 _ZN1DD2Ev;
      BASE 1 DER 2: 00000001 _ZN1DD1Ev;00000001 _ZN1DD2Ev;
      BASE 3 DER 2: 00000001 _ZN1BD1Ev;00000001 _ZN1BD2Ev;00000001 _ZN1DD1Ev;00000001 _ZN1DD2Ev;
    for b in 0 1; do printf 'BASE %s DER 2, D1: ' $b; wasm-objdump -d build/out/reading-probe/d0-$b-2.o | awk '/<_ZN1DD1Ev>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | awk 'NF {n++} END {print n " lines"}'; done
      BASE 0 DER 2, D1: 3 lines
      BASE 1 DER 2, D1: 55 lines

| the base's destructor, the derived one out of line | the derived D2 | in the target |
| --- | --- | --- |
| out of line, in another object | one call of the base's D2 | 884 (7 B) over 1035, `vota::CCandidatoInapto` over `CVotacaoStateAudio` |
| inline or in the class | the base's body, which binaryen's duplicate-function elimination merges with the base's own D2, so slot 0 holds the base's D2 under a D0 with a `drop` | 3609 (13 B) over 1378, `comum::CPedeTituloMesarioInicial` over `IPedeTituloMesario`; 5946 over 1559 |
| out of line, in the same TU | no body: an alias of the base's, and the D0 has the same `drop` shape | not told from the row above by any byte: only the classes' files do |

The last two rows need the files: 3609's class is not in its base's object, since each derived class's vtable lies just
before its own records and the base's before its file's (`ledger/vtables.json`, `ledger/source-locations.tsv`). With the
derived destructor implicit and the base's out of line, `splat-remap` stops at 3609's `drop`.

The fourth form, a derived destructor not out of line over a base D2 in another object, has the 10-B shape above, and
the three ways to write it give one object (at uenux2's `-O3`, a `final` class template or a plain class alike):

```sh
P=build/out/reading-probe; mkdir -p $P
printf '%s\n' 'struct B { virtual ~B(); int b; };' 'struct D : B {' '#if FORM == 1' '    ~D() override = default;' '#elif FORM == 2' '    ~D() override {}' '#endif' '};' 'B* make() { return new D(); }' > $P/slot0.cpp
for f in 0 1 2; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/$P/slot0.cpp -o /work/$P/slot0-$f.o; done
for f in 1 2; do cmp -s $P/slot0-0.o $P/slot0-$f.o && echo "FORM 0 = $f"; done
# FORM 0 = 1
# FORM 0 = 2
```

So the base's D2 in slot 0 says the derived destructor is not out of line, not which of the three it is.

**The shape is the destructor's own TU's.** A D0 is compiled where the destructor is defined. A `delete` elsewhere (a
control block's `__on_zero_shared`, a `unique_ptr` release) frees what the destructor returns when its TU only declares
the destructor, and frees `this` after the call, the out-of-line D0's shape, when the TU defines it:

```sh
printf '%s\n' 'struct S { ~S(); int a[14]; };' '#if DEF' 'S::~S() = default;' '#endif' 'void del(S* p) { delete p; }' > $P/del.cpp
for d in 0 1; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DDEF=$d -c /work/$P/del.cpp -o /work/$P/del-$d.o
  printf 'DEF=%s: ' $d; wasm-objdump -d $P/del-$d.o | sed -n '/<_Z3delP1S>:/,$p' | sed -E 's/^ [0-9a-f]+:[^|]*\| *//' | /usr/bin/grep -E '^(call|drop|local.get 0)' | tr '\n' ';'; echo; done
# DEF=0: local.get 0;local.get 0;call 0 <env._ZN1SD1Ev>;call 1 <env._ZdlPvm>;
# DEF=1: local.get 0;local.get 0;call 1 <_ZN1SD1Ev>;drop;local.get 0;call 0 <env._ZdlPvm>;
```

The target's 11263, `__shared_ptr_pointer<comum::CCalculaCV*, …>::__on_zero_shared`, is `f5614(p); f136(p)`: compiled
in the TU of `CCalculaCV`'s out-of-line destructor, which a roots file's control block cannot give, since it only
declares the destructor (unit 121's fragment).

**An explicit instantiation decides nothing of the form.** For a class template the shapes above are those of an
implicit instantiation. An explicit instantiation definition (`template struct T<1>;`) gives the out-of-line D0, a call
of the D2 then `drop` and a free of `this`, both with the destructor `{}` in the class and with it declared there and
`= default` after it:

```sh
cat > $P/tmpl.cpp <<'EOF'
#include <string>
#include <vector>
struct I { virtual ~I(); };
template <int N> struct T : I {
    T() {}
#if FORM == 1
    ~T() override;
#else
    ~T() override {}
#endif
    std::string a, b;
    std::vector<int> v;
};
#if FORM == 1
template <int N> T<N>::~T() = default;
#endif
#if EXPLICIT
template struct T<1>;
#else
I* make() { return new T<1>(); }
#endif
EOF
for e in 0 1; do for f in 0 1; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DEXPLICIT=$e -DFORM=$f -c /work/$P/tmpl.cpp -o /work/$P/tmpl-$e$f.o
  printf 'EXPLICIT=%s FORM=%s: ' $e $f; wasm-objdump -d $P/tmpl-$e$f.o | sed -n '/<_ZN1TILi1EED0Ev>:/,/^ *[0-9a-f]* func\[/p' | /usr/bin/grep -c -E 'call [0-9]+ <_ZN1TILi1EED1Ev>'; done; done
# EXPLICIT=0 FORM=0: 0
# EXPLICIT=0 FORM=1: 0
# EXPLICIT=1 FORM=0: 1
# EXPLICIT=1 FORM=1: 1
```

(Implicitly instantiated, this D0 holds the D2's body.) So a target D0 of the in-class shapes is an implicit
instantiation's copy, in a user's TU or one with no explicit instantiation, and an explicit instantiation in the
class's `.cpp` cannot give it.

A base destructor in the class without `inline` is inlined only under the plain threshold (225, [levels.md](levels.md)
§V2). `CVotacaoStateAudio`'s D2 is 180 B: `CProporcionalBranco`'s out-of-line destructor over the in-class form stays
one call, of a weak copy, and `inline` gives 85 lines. So "defined in the class" does not always show as the base's
body.

## R6. A class whose only virtual members are inline has no key function: only a TU that uses its vtable emits it

With no non-inline virtual member, the vtable, D2 and D0 are linkonce_odr, emitted only by a TU that references the
vtable, which a constructor defined there does. In the probe of R4, `NoCtor` (destructor in the class, one
non-virtual member defined) gets nothing; `Inl` (the same with a constructor defined) gets a weak vtable:

    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only /work/build/out/reading-probe/dtor.o | /usr/bin/grep -E '_ZTV|NoCtor'
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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/typeinfo.cpp -o /work/build/out/reading-probe/typeinfo.o
    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm build/out/reading-probe/typeinfo.o | /usr/bin/grep -E '_ZT[IV][0-9]'
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

**Reading the target for a key function.** When the destructors are shared bodies (slot 0 the shared `return this`
174, slot 1 the trap 325 of an abstract class), the D0 says nothing, and a missing vtable says nothing either: wasm-ld
drops a vtable nothing references, whichever object emitted it. Where the typeinfo lies does say it, by which object
holds it. wasm-ld keeps the first object's copy of a linkonce typeinfo, so a class with no key function has its
typeinfo in the object of a TU that uses it: no later than its earliest derived class's typeinfo, or inside the data of
a TU that uses the class without deriving from it. A typeinfo well after the earliest derived one, among other objects'
records, is the copy of the object that defines the key function. Both kinds, at bb6f018:

    python3 -I -c "
    import json, sys
    c = {x['name']: x for x in json.load(open('ledger/classes.json'))['classes']}
    def derives(n, b): return any(e['name'] == b or derives(e['name'], b) for e in c.get(n, {}).get('bases', []))
    b = sys.argv[1]; t = c[b]['typeinfo']
    d = sorted((x['typeinfo'], n) for n, x in c.items() if derives(n, b) and x.get('typeinfo'))
    print(b, t, 'derived', len(d), 'first', d[0], 'below', sum(1 for a, _ in d if a < t))
    " comum::CAppState
      comum::CAppState 1551284 derived 198 first (1533000, 'vota::CAguardaMensagem') below 105

`comum::CAppState`'s typeinfo lies 18284 B after its earliest derived class's, with 105 derived typeinfos and other
files' records below it, so it is the copy of its own object, which has an out-of-line virtual member (unit 61 chooses
the destructor). `api::ITextToSpeech`'s and `api::ISound`'s lie inside the executable TU's data, between that file's
records ([levels.md](levels.md) §V1 has the command): copies, so neither class has a key function. Adjacency to the
class's own vtable is not the test: `api::IScreen`'s vtable lies right after `simulador::CWasmScreen`'s typeinfo, and
its own typeinfo 2312 B later.

**Emitting the destructors of a class with no key function.** A TU emits the vtable, D2 and D0 of such a class when it
references the vtable: a constructor defined there, a derived class's destructor that inlines this one, or a call of the
destructor by its qualified name when it destroys something (its D2 then stores the vptr; one that destroys nothing is
the base's D2 to clang, and nothing names the vtable: [units.md](units.md) §U13). The last needs neither constructor nor
derived class: `src/units/92-uenux2-iinputfield-roots.cpp` calls
`campo.api::CMaskedTextField<api::CFramedText>::~CMaskedTextField()` from an `optnone` function. A class that declares
no constructor has an implicit one, so `new T` in such a function emits them as well, while no constructor is declared,
and building the object does the same where a constructor is written (unit 67). `src/units/README.md` "A class with no
key function" says what a roots file may do with this.

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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/pure.cpp -o /work/build/out/reading-probe/pure.o
    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm -S --defined-only /work/build/out/reading-probe/pure.o | /usr/bin/grep -E '_ZTV|D0Ev'
      00000006 00000004 T _ZN3AbsD0Ev
      00000012 00000016 T _ZN3ConD0Ev
      00000000 00000028 D _ZTV3Abs
      00000038 00000014 D _ZTV3Con
    wasm-objdump -d build/out/reading-probe/pure.o | awk '/D0Ev>:/ {print; n=4; next} n-- > 0'
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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/build/out/reading-probe/<v>.cpp -o /work/build/out/reading-probe/<v>.ll
    /usr/bin/grep -oE 'i32 [345], i32 [0-9]+ \}' build/out/reading-probe/<v>.ll | awk '{print $2}' | tr -d ',' | tr '\n' ' '
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

That last sentence is for a function its records show file-static. For a function with no record, a caller in
another file is read by where the call sits in that caller. A call in the caller's own code, or in code binaryen
inlined from another function of the caller's file (R10), is a call across files: the callee is external. Only a call
inside code inlined from the callee's own file fits a file-static callee. 5449 has no record and two callers,
`api::EncodeTime` (3643, `ctime.cpp`) and `api::CDateTime::CDateTime(const std::string &)` (5475, `cdatetime.cpp`):

    awk -F'\t' '$2==5449 || $2==5479 {print $1, $2}' ledger/callgraph.tsv
      3643 5449
      3649 5479
      5475 5479
      5475 5449
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5475 | sed -n '/folded readout/,$p' | /usr/bin/grep -n -E 'i32.sub\(g0|f5479|f5449|f3643|f3649'
      4:  l2 = i32.sub(g0, 32);
      11:        l3 = i32.sub(g0, 32);
      45:                if (i32.eqz(f5479(l4))) br 0;
      71:                l5 = f5449(i32.add(l3, 8));
      102:        i64.store[l7] = i64.load[f3649(l2, l4)];
      132:        i32.store[l8] = i32.load[f3643(l2, i32.add(l2, 8))];

5475 calls 5449 inside a second frame, a date-and-time check binaryen inlined, which also calls `CDate`'s check 5479,
and later calls the `CTime` and `CDate` string constructors (3643's caller and 3649) itself. Which file defined that
check, no byte says: in `cdatetime.cpp` it makes 5449 external, in `ctime.cpp` a file-static 5449 gives the same bytes
(its symbol becomes `_ZN3apiL11IsValidTime…`). Unit 24 declares it in `ctime.h`, external, as a choice
(`src/uenux2/src/api/util/ctime.h` line 15).

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

Three limits to this reading:

- **After all of them is two places.** A member after every other member of its file in the band is inline or
  implicit, or the file's last function: the DAOs' slot 2 comes after their other members and before the base's
  template defaults (`awk -F'\t' 'NR>1 && $1>=11467 && $1<=11473 {printf "%s(%s) ", $1, $2} END {print ""}'
  ledger/ordinals.tsv` prints `11467(1) … 11473(1)`, read downwards: slots 3, 5, 6, 7, 8, then 2, then the default 4),
  and its merge-thunk body cannot tell which.
- **A deferred function sits after its first caller in the object, not at its end.** clang creates a function in the
  module where it is first referenced, and emits the body (and its records, R8) at the end of the TU; the object's
  function order is the module's. Probe `deferorder.cpp` (bb6f018):

      // A file-static function: its record is emitted after the external functions' (R8), its body sits after its first caller.
      #include <source_location>
      void use(const std::source_location &);
      static __attribute__((noinline)) void h() { use(std::source_location::current()); }
      void a() { use(std::source_location::current()); }
      void b() { use(std::source_location::current()); h(); }
      void c() { use(std::source_location::current()); h(); }

      TMPDIR=/tmp build/docker-build.sh sh -c 'em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/build/out/reading-probe/deferorder.cpp -o /work/build/out/reading-probe/deferorder.ll && em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/deferorder.cpp -o /work/build/out/reading-probe/deferorder.o'
      /usr/bin/grep -oE 'i32 [4-7], i32 [0-9]+ \}' build/out/reading-probe/deferorder.ll | awk '{print $2}' | tr -d ',' | tr '\n' ' '
        5 6 7 4                                   # the records' lines: h's last
      wasm-objdump -d build/out/reading-probe/deferorder.o | /usr/bin/grep -oE 'func\[[0-9]+\] <[^>]+>' | tr '\n' ' '
        func[1] <_Z1av> func[2] <_Z1bv> func[3] <_ZL1hv> func[4] <_Z1cv>

  So the band reading holds for a member nothing earlier in the file calls, such as a destructor only the vtable
  references; an inline or static function that an external one calls sits among the external ones.
- **A shared body has no band place.** A member whose target body binaryen keeps once for several classes counts
  every class's table slots in its `uses`, so it sits in another band than its class's other members: `awk -F'\t'
  '$1==2241 || $1==5527 {print $1, $2}' ledger/ordinals.tsv` prints `2241 5` and `5527 2` for the `Move` that five
  and two field classes share, while each class's other members are in band 1. Its line in its file is a choice.

## R10. Code binaryen inlined from an out-of-line function of the source

A body can hold code that was a separate function in the object, which wasm-opt inlined into its only caller; that
function then has no target index of its own, and the source defines it out of line, unrooted
(`src/units/README.md` "Companion files"). The tells in a readout:

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

The first tell has a variant, and there are two more (bb6f018):

- **A leaf callee's frame is not written back.** A callee that makes no call and whose frame fits LLVM's red zone
  reads the stack pointer and never stores it, so its prologue is a second `i32.sub(g0, N)` with no `g0 =` after it.
  `api::CPriorityMessageQueue<api::SMessage>::Remove` (2073) holds `std::priority_queue::pop` so (unit 64 leaves `pop`
  out of line and matches 2073):

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 2073 | sed -n '/folded readout/,$p' | /usr/bin/grep -n 'g0'
        4:  l10 = i32.sub(g0, 16);
        5:  g0 = l10;
        17:      l4 = i32.sub(g0, 16);
        118:    g0 = i32.add(l10, 16);

- **A value read back right after it was stored.** clang forwards a stored value to a later load unless a call it
  cannot see into stands between; binaryen inlining that call afterwards leaves the reload. `simulador::CWasmBeep`'s
  slot 2 (8533) stores a local vector's begin and end into its frame and loads begin again at once:

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 8533 | sed -n '/folded readout/,$p' | sed -n 6,13p
          l2 = f137(16);
          i32.store[l3+4] = l2;
          l4 = i32.add(l2, 16);
          i32.store[l3+12] = l4;
          i64.store[l2+8] = 42949675160;
          i64.store[l2] = 42949675260;
          i32.store[l3+8] = l4;
          l2 = i32.load[l3+4];

  The vector was filled by a function clang did not inline: a builder returning it by value, which clang inlines
  when it sits in the caller's TU (any small function), so it is in another one. Unit 72 puts the tone sequences in
  `src/uenux2/src/api/hwil/ibeep.cpp` and matches 8533 (`awk '$1==8533' splat/matched.txt`).
- **A by-value `std::shared_ptr` copied word by word out of a frame temporary.** A constructor that clang inlines
  stores its by-value `shared_ptr` arguments straight from the caller's values; one binaryen inlined keeps the
  argument's temporary and reads it back into the object. `comum::CParteCandidatosMajoritarios`'s constructor inside
  11946:

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11946 | /usr/bin/grep -A4 'i32.store\[l13\] = 1576416'
          i32.store[l13] = 1576416;
          i32.store[l8+16] = i32.load[l2+192];
          i32.store[l8+20] = i32.load[l2+196];
          i32.store[l8+24] = i32.load[l2+184];
          i32.store[l8+28] = i32.load[l2+188];

  Unit 77 defines the comum constructors out of line, by value, one caller each.

Three more signs. Each was read on a body that differed, and moving the callee out of line closed it; at 4487d6b
`awk -F'\t' '$1==9145 || $1==728 || $1==3890 || $1==5181 {print $1, $5}' splat/scan.tsv` prints `match` for the first
three and `unresolved` for 5181, which waits for a name:

- **An outer `block` that opens where the arguments are set and is left with `br 1` where clang would `return`.**
  binaryen wraps an inlined callee in a block and sets its parameters inside it. 9145 holds it from its first row, and
  matches with `CTituloRelatorio`'s constructor out of line (unit 106).
- **An `if (result i32) … else 0 end` tested again with `i32.eqz; br_if`,** which clang, inlining, folds into one
  branch. `CSynchronizer::Sync` out of line took 5181 to one row from the target.
  The same value carried across the epilogue to the return is the sign too: 11198
  (`CRelatorioTesteImpressora::EstaEmHorarioVerao`) holds `a <= x && x < b` so, where the compares written in the
  caller keep the result in a local read after the epilogue (`14 over 40`); in an out-of-line `CHorarioVerao::Contem`
  of another TU it matches (unit 147).
- **Statements ahead of the body's only prologue.** A caller with no frame of its own keeps its code before the frame
  of a callee binaryen inlined into it:

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 10380 | sed -n '/folded readout/,/^}/p' | sed -n 4,5p
          i32.store[p0+4] = p0;
          l2 = i32.sub(g0, 16);

  Written as one function, 10380's prologue comes first (`117 over 203`); with the store in a frameless `StartState`
  and the switch in an out-of-line member it calls, the store comes first (`42 over 174`, unit 135's fragment).
- **A narrow value widened to a parameter's type and held.** Beside bytes, a 32-bit member read as `i64.load32_u` into
  a local, kept across other code and narrowed only at a call: clang folds such an extend and narrow inside one
  function. 11825 (`CEsperaRetestar::StartState`) matches its rows only with an out-of-line `CDateTime::operator+(time_t)
  const` in `cdatetime.cpp` (`6 over 62` against `30 over 64` written in place, unit 138's fragment):

      pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11825 | sed -n '/folded readout/,/^}/p' | /usr/bin/grep -n 'load32_u\|wrap_i64'
        10:  l4 = i64.load32_u[p0+40];
        14:  f2233(l3, i32.wrap_i64(l4));

- **An argument temporary tested after a constructor that is no call.** When clang inlines a constructor it sees, it
  knows that a `std::string` moved from is empty and drops the temporary's test, and joins a copy's test with the
  temporary's destruction. A test of the caller's temporary (its byte at +11, then `free`) after the constructor's code
  says binaryen inlined it: `comum::md::CSuplencia`'s constructor in 11359 scores `18 over 195` in the class and `10
  over 195`, operand-only, out of line in `csuplencia.cpp`, and `CDadosCandidato`'s two in 11450 the same (unit 124).
- **Locals alone.** A body that differs from the target in local numbers only, whose callee has no frame, shows none of
  the signs above: binaryen re-optimizes the caller after inlining. 728 and 3890 match with a field's constructor moved
  from its header to its `.cpp`. Try such a callee out of line, unrooted, before a source form, beside
  [codegen.md](codegen.md) §C4's order.

Such a function is a member in its class's `.cpp` when it reads the class's state; one that reads none (8533's tone
sequences) is a free function, and its file is a choice as long as it is not the caller's TU.

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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -S -emit-llvm /work/build/out/reading-probe/scope.cpp -o /work/build/out/reading-probe/scope.ll
    /usr/bin/grep -oE 'c"api::[ABC]::[ABC]\([^"]*\\00"' build/out/reading-probe/scope.ll
      c"api::A::A(std::vector<CMovieFrame>)\00"
      c"api::B::B(std::vector<GFrame>)\00"
      c"api::C::C(std::vector<GFrame>)\00"
    /usr/bin/grep -oE 'define [^@]*@_ZN3api1[ABC]C2E[A-Za-z0-9_]+' build/out/reading-probe/scope.ll | sed 's/.*@//'
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

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/byvalue.cpp -o /work/build/out/reading-probe/byvalue.o
    wasm-objdump -d build/out/reading-probe/byvalue.o | awk '/ func\[/ {name=$3} /store/ {c[name]++} END {for (k in c) print c[k], k}' | sort -k2
      5 <_ZN3ValC1ENSt3__210shared_ptrI1IEES3_>:                           # the vptr and four words copied
      7 <_ZN4CRefC1ERKNSt3__210shared_ptrI1IEES5_>:                        # and a count increment per source
      7 <_ZN4RRefC1EONSt3__210shared_ptrI1IEES4_>:                         # and an i64.store 0 per source
      3 <_ZN4URefC1EONSt3__210unique_ptrI1INS0_14default_deleteIS2_EEEE>:
      2 <_ZN4UValC1ENSt3__210unique_ptrI1INS0_14default_deleteIS2_EEEE>:
    for s in _ZN4UValC1 _ZN4URefC1; do printf '%s: ' $s; wasm-objdump -d build/out/reading-probe/byvalue.o | awk -v s="<$s" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -vE '^$|^end$|^local\[' | tr '\n' ';'; echo; done
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
the type `std::format` sees after its own conversions, not the variable's. An enum cast to an integer shows the cast's
code. An enum with a `std::formatter` of its own shows 15, `__handle`: 1712 stores the value's address at +48 and a
table slot, its format function, at +52:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 1712 | /usr/bin/grep -E 'i64.store\[l2\+64\]|i32.store\[l2\+(48|52)\]'
          i32.store[l2+52] = 2285;
          i32.store[l2+48] = p1;
          i64.store[l2+64] = 15;
    wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[(2285|2289)\] '      # from the repository root
      - elem[2285] = ref.func:536
      - elem[2289] = ref.func:1711

`fn` lists such a slot as a string ("2285 (+4 into 2281)"), and it is a callee no direct-call table lists. 536 is
`formatter<unsigned int>` (`i32.ge_u(p0, 128)`) in 31 slots, and 1711 `formatter<int>` in 7, so the handle says which of
the two the value goes through, not the enum's underlying type: `: int` with a formatter that casts to `unsigned`
gives 536's rows. The slot needs a target name, so a body that alone votes for it stays `unresolved self-voted` until a
second holder matches.

**A site has three shapes**, and only one depends on the level. Probe `fmtsite.cpp` (0b5f410), unconditional throws of
36, 37, 74 and 75 bytes of literal and one conditional throw of 44:

    python3 -I -c "print('#include <format>\n#include <string>'); [print(f'void F{n}(int v) {{ throw std::format(\"{\"x\"*(n-2)}{{}}\", v); }}') for n in (36, 37, 74, 75)]; print('void C(int v) { if (v > 3) throw std::format(\"' + 'x' * 42 + '{}\", v); }')" > build/out/reading-probe/fmtsite.cpp
    TMPDIR=/tmp build/docker-build.sh sh -c 'for l in O2 O3; do em++ -$l -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/fmtsite.cpp -o /work/build/out/reading-probe/fmtsite-$l.o; done'
    for l in O2 O3; do wasm-objdump -d build/out/reading-probe/fmtsite-$l.o | awk -v l=$l '/ func\[/ {n=$3} /br_table/ {b[n]++} /__try_constant_folding/ {c[n]++} END {for (s in b) print l, s, "loop"; for (s in c) print l, s, "call"}' | /usr/bin/grep -E '_Z[0-9]+[FC]' | sort; done
      O2 <_Z1Ci>: call
      O2 <_Z3F37i>: loop
      O2 <_Z3F74i>: loop
      O2 <_Z3F75i>: loop
      O3 <_Z1Ci>: call
      O3 <_Z3F75i>: loop

- A conditional throw is a cold site: it keeps `call 154` (`__try_constant_folding`) at both levels, so a `call 154` says nothing of the level.
- An unconditional throw is folded up to the loop unroller's limit, 36 bytes at `-O2` and 74 at `-O3`: no call and no loop.
- Past the limit it keeps a `br_table` loop, the search of the literal for a brace.

A statement that only builds a string, a log message, is a site of the same kind: run unconditionally, it folds and
loops at the same limits (4487d6b):

    python3 -I -c "print('#include <format>\n#include <string>'); [print(f'std::string G{n}(int v) {{ return std::format(\"{\"x\"*(n-2)}{{}}\", v); }}') for n in (36, 40, 74, 75)]" > build/out/reading-probe/fmtplain.cpp
    TMPDIR=/tmp build/docker-build.sh sh -c 'for l in O2 O3; do em++ -$l -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/fmtplain.cpp -o /work/build/out/reading-probe/fmtplain-$l.o; done'
    for l in O2 O3; do wasm-objdump -d build/out/reading-probe/fmtplain-$l.o | awk -v l=$l '/ func\[/ {n=$3} /br_table/ {b[n]++} END {for (s in b) print l, s, "loop"}' | /usr/bin/grep -E '_Z[0-9]+G' | sort; done
      O2 <_Z3G40i>: loop
      O2 <_Z3G74i>: loop
      O2 <_Z3G75i>: loop
      O3 <_Z3G75i>: loop

The target has all three, and the 37 to 74 bytes between the limits with no loop are the level's evidence
([levels.md](levels.md) §V3):

    for i in 1712 731 10772; do printf '%s: ' $i; pnpm --silent wasm fn ../target/vota_web_wasm.wasm $i | sed -n '/disassembly/,/folded readout/p' | awk '/call 154( |$)/ {c++} /br_table/ {b++} END {print "call 154:", c+0, "br_table:", b+0}'; done
      1712: call 154: 1 br_table: 0
      731: call 154: 0 br_table: 0
      10772: call 154: 0 br_table: 4

## R14. A `bool` tested in a condition can read as a compare with 1; a loop tells a `bool` from a byte

LLVM tests a `bool` by its value 0 or 1, so a read in a condition can be `i32.load8_u; i32.const 1; i32.eq` (or
`i32.ne`) as often as a bare `br_if` on the byte, and that `1` is no literal of the source. One read says nothing of the
type: a byte compared with 1 gives the same rows. A loop that tests a global at its entry and on its back edge does
tell them apart. Probe `boolread.cpp` (bb6f018):

    // How a one-byte global's reads look in a loop: the first test and the back edge.
    #if FORM == 0
    extern bool g;
    #define TEST g
    #elif FORM == 1
    extern unsigned char g;
    #define TEST (g == 1)
    #else
    extern unsigned char g;
    #define TEST (g != 0)
    #endif
    void work();
    void Loop() { while (TEST) work(); }

    TMPDIR=/tmp build/docker-build.sh sh -c 'for f in 0 1 2; do em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DFORM=$f -c /work/build/out/reading-probe/boolread.cpp -o /work/build/out/reading-probe/boolread-$f.o; done'
    for f in 0 1 2; do printf 'FORM %s: ' $f; wasm-objdump -d build/out/reading-probe/boolread-$f.o | awk '/<_Z4Loopv>:/ {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -E 'load8|i32.const 1$|i32.eq|i32.ne|br_if|eqz' | tr -s ' ' | tr '\n' ';'; echo; done
      FORM 0:  i32.load8_u 0 0; i32.const 1; i32.ne; br_if 0; i32.load8_u 0 0; br_if 0;
      FORM 1:  i32.load8_u 0 0; i32.const 1; i32.ne; br_if 0; i32.load8_u 0 0; i32.const 1; i32.eq; br_if 0;
      FORM 2:  i32.load8_u 0 0; i32.eqz; br_if 0; i32.load8_u 0 0; br_if 0;

Only the `bool` compares at the entry and tests bare on the back edge. The byte at 1584624
(`_ZN3api7CSystem7s_dormeE` in `splat/symbol_addrs.txt`) is read so by fn 5446, the one reader with a loop:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5446 | sed -n '/folded readout/,$p' | /usr/bin/grep -n '1584624'
      7:    if (i32.ne(i32.load8_u[1584624], 1)) br 0;
      17:      if (i32.load8_u[1584624]) br 0;

so it is a `bool`; a reader with one test, such as fn 8461, cannot say.

Read every function that loads or stores the byte, written or not (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
build/out/splat/pieces/asm` lists a static's), before calling its type a width only: a compare with a value above 1, an
increment or an index rules out a `bool`. The byte at 0x1d1fbc (1908668) is one: 10465 loops until it is 4, increments
it, and indexes a table of finger codes with it, so it is no `bool`.

**A byte's sign shows only where it is widened.** An equality test, an increment and a truncating store load the byte
with `i32.load8_u` whether it is `signed char` or `uint8_t`; an index loads it with `i32.load8_s` for `signed char`:

```sh
P=build/out/reading-probe; mkdir -p $P
printf '%s\n' '#include <cstdint>' '#if SIGNED' 'typedef signed char T;' '#else' 'typedef std::uint8_t T;' '#endif' 'extern T s;' 'extern int g_tabela[];' '[[noreturn]] void Lanca();' 'void Usa(int);' 'void Avanca() { if (s != 4) s = s + 1; else Lanca(); }' 'void Indexa() { Usa(g_tabela[s]); }' > $P/sign.cpp
for s in 0 1; do TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -DSIGNED=$s -c /work/$P/sign.cpp -o /work/$P/sign-$s.o
  for f in _Z6Avancav _Z6Indexav; do printf 'SIGNED=%s %s: ' $s $f; wasm-objdump -d $P/sign-$s.o | sed -n "/<$f>:/,\$p" | /usr/bin/grep -m1 -oE 'i32\.load8_[su]'; done; done
# SIGNED=0 _Z6Avancav: i32.load8_u
# SIGNED=0 _Z6Indexav: i32.load8_u
# SIGNED=1 _Z6Avancav: i32.load8_u
# SIGNED=1 _Z6Indexav: i32.load8_s
```

So 10465's increment and its bound of 4 say nothing of the sign; its index load (`i32.load8_u` before the shift, at
+0xe90) and 10425's (+0x209) say unsigned.

## R15. An `invoke` around a callee that cannot throw: the callee had a call that might, which a later pass removed

emscripten turns a call inside a `try` (or a cleanup scope) into an `invoke_*` when the callee may throw at the time
its pass runs, before binaryen inlines and simplifies. So an `invoke` whose callee cannot throw in the final module
says that the callee's source held a call that could, which optimisation then removed. `CSqlConnection::Prepare`
(9460) reaches the `CSqlStatement` constructor (9430) through `invoke_iiii` with table slot 6338, and the
constructor's body calls only `sqlite3_bind_parameter_count` (6536):

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 9460 | sed -n '/folded readout/,$p' | /usr/bin/grep 'invoke_iiii(6338'
              p2 = invoke_iiii(6338, l4, p1, i32.load[l3+92]);
    wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[6338\] '      # from the repository root
      - elem[6338] = ref.func:9430
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 9430 | sed -n '/folded readout/,$p' | sed -n 3,8p
        i32.store8[p0+12] = 0;
        i32.store[p0+8] = p2;
        i32.store[p0+4] = p1;
        i32.store[p0] = 1116948;
        i32.store[p0+16] = f6536(i32.load[p0+8]);
        push p0;

A `std::mutex::lock()` in the constructor gives both: `pthread_mutex_lock` may throw through `std::system_error` when
the invoke is made, and in this single-threaded build it is a stub that returns 0, so the throw path and the call
vanish. `src/ecourna/api/sql/sqlite/csqlstatement.cpp` (unit 12) locks a file-level mutex there, and 9430 and 9460
match (`awk '$1==9430 || $1==9460' splat/matched.txt`). The reverse case, a direct call inside a cleanup scope, is
[app-flags.md](app-flags.md) §F9 item 5.

## R16. Several table slots of one function are several symbols of identical code

wasm-ld gives each address-taken symbol its own slot before binaryen merges bodies, so one final function in several
slots was several source functions. A merge body that takes a slot as a parameter calls an instantiation-specific
callee. `CBaseError`'s constructor thunks each pass one slot to the shared 2294, and all five slots are one function:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 170 | /usr/bin/grep -E 'push f2294'
        push f2294(p0, p1, p2, p3, 1528096, 469);
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 2379 | /usr/bin/grep -E '^;; table'
      ;; table slots 144, 159, 469, 477, 483

So step 2's lookup of one slot is not the whole reading. 2379 sits between `CBaseError`'s constructor and `CError`'s and
stores no vptr, so five slots mean one such function per enum: the delegating template constructor of
`src/ecourna/api/exception/cerror.hpp` (unit 94's fragment has the forms measured).

## R17. A function-local static's guard says whether the variable has internal linkage

A guard read as a plain byte belongs to a static with internal linkage, and one read with `i32.const 1; i32.and` to one
that does not. So a function with no record shows its linkage here. Probe `guard.cpp`:

    // A function-local static's guard, in an inline function and in a static one.
    struct T { T(); int v; };
    inline T& Inline() { static T t; return t; }
    static __attribute__((noinline)) T& Interno() { static T t; return t; }
    int Le() { return Inline().v + Interno().v; }

    TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -c /work/build/out/reading-probe/guard.cpp -o /work/build/out/reading-probe/guard.o
    for f in _Z2Lev _ZL7Internov; do printf '%s: ' $f; wasm-objdump -d build/out/reading-probe/guard.o | awk -v s="<$f>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | sed -E 's/^ *[0-9a-f]+: [0-9a-f ]+\| //' | /usr/bin/grep -E -A2 'load8_u' | /usr/bin/grep -vE '^--' | tr -s ' ' | tr '\n' ';'; echo; done
      _Z2Lev:  i32.load8_u 0 0; i32.const 1; i32.and;
      _ZL7Internov:  i32.load8_u 0 0; br_if 0; global.get 0 <env.__memory_base>;

11265 reads its guard as `i32.eqz(i32.load8_u[1832596])`, so `api::polySingletonsInfoPadrao` is a `static` function of a
`.cpp`, though the pointer to it reads from a header (unit 100, `src/uenux2/src/api/pattern/cpolysingletonlist.cpp`).

## R18. One row more than the target at a call is the callee's signature, not the caller

Dead-argument elimination (R1, R2) leaves alone a function the table holds. So a body whose only structural row is a
`drop` after a call, or a constant argument before it, has a right source: the callee lost its result or a parameter in
the target and kept it in ours, because something of ours takes its address. 208 and 2653 hold one such `drop`:

    pnpm --silent wasm score ../target/vota_web_wasm.wasm 208 ../build/out/wasm/vota_web/vota_web_wasm.wasm 796 | /usr/bin/grep -E '^score|> drop'
      score 19 over 116 rows (same 97, replaced 18 [18 operand-only], inserted 1, deleted 0)
                                                               > drop
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 2567 | /usr/bin/grep -E '^;; (function|table)'
      ;; function 2567 (i32 i32)->() locals(i32 i32) body@0x13627b size 383 instrs 167
    pnpm --silent wasm fn ../build/out/wasm/vota_web/vota_web_wasm.wasm 3190 | /usr/bin/grep -E '^;; (function|table)'
      ;; function 3190 (i32 i32)->(i32) locals(i32 i32) body@0x18397c size 389 instrs 168
      ;; table slots 7473

The callee has no slot in the target and slot 7473 in ours. Find what holds the slot: `ours` numbers are the link's at
0b5f410, and the commands read it as it stands.

    wasm-objdump -d build/out/wasm-kinds/vota_web/vota_web_wasm.wasm | awk '/ func\[/ {f=$2} / i32\.const 27473$/ {print f}'     # from the repository root
      func[7739]:
    awk -F'\t' '$1==7739 {print $2}' build/out/wasm-map/vota_web/names.tsv
      _ZNK7RHVoice8userdict19stressed_syl_number8describeEv

Fix the reference, not the caller: a roots address goes out of the roots (unit 87's exclusions took 5067 out, and 181
and 339 matched); a library's `invoke` is a library flag question.

The other direction: the target keeps a result that ours dropped, our callee `(i32 i32)->()` against the target's
`(i32 i32)->(i32)`, and neither side's table holds the callee. Then one target caller reads the result, and that
caller is in the target's table and not reachable in ours. 276 is `string::assign(const char*)`'s body, called at 79
sites, and one of them reads the result:

    wasm-objdump -d target/vota_web_wasm.wasm | awk '/ func\[/ {f=$2} p && !/drop/ {print f} {p = / call 276$/}' | sort | uniq -c
       1 func[12979]:

12979 is a 9-byte forwarder whose only reference is table slot 168 (`pnpm wasm fn`'s `;; table slots 168`). Taking its
address in a roots file (unit 103) gives ours the result.

## R19. A record's line and column where no `throw` makes it

A `std::source_location` record from a default argument holds the start of the call expression that takes the default,
and one made inside a macro expansion holds the line and column of the invocation's closing `)`. Probe `reccol.cpp`
(4487d6b):

    // Where a std::source_location record's line and column fall.
    #include <source_location>
    struct S { static S& inst(std::source_location l = std::source_location::current()); void f(); };
    #define INST(C) S& C##Get() { return S::inst(); }
    void Plain() {
        S::inst().f();
        auto& v = S::inst();
        v.f();
    }
    INST(CCargos)
    INST(CConfiguracaoEleicao)

    TMPDIR=/tmp build/docker-build.sh sh -c 'cd /work/build/out/reading-probe; em++ -O0 -std=c++20 -S -emit-llvm reccol.cpp -o reccol.ll'
    /usr/bin/grep -oE 'i32 [1-9][0-9]*, i32 [1-9][0-9]* \}' build/out/reading-probe/reccol.ll
      i32 6, i32 5 }
      i32 7, i32 15 }
      i32 10, i32 13 }
      i32 11, i32 26 }

`S::inst().f();` at four spaces is column 5 and `auto& v = S::inst();` column 15, so a long column on a record with no
throw reads as a declaration's initializer, and a local of the right length is one way to give it, a choice. The two
macro lines differ by 13, the difference of the two class names' lengths: a column that grows by one per character of a
name across classes is a macro that takes the name once, and the column fixes only the invocation's total length, not
how its text is shared out.

**Read a constant in the shifted link, never the plain one.** A constant equal to a slot number can be an integer, and
the plain link cannot say. The shifted link moves the table by 20,000 ([splat.md](../splat.md) §3 "Operand kinds"), so
a slot reads 20,000 higher there and an integer does not. At 0b5f410 seven bodies hold `i32.const 1176`, the slot of
`CUePrinterError`'s destructor, and two of them mean the slot:

    wasm-objdump -d build/out/wasm/vota_web/vota_web_wasm.wasm | awk '/ func\[/ {f=$2} / i32\.const 1176$/ {print f}' | tr '\n' ' '; echo
      func[1026]: func[3978]: func[5061]: func[5152]: func[5725]: func[7702]: func[7703]:
    wasm-objdump -d build/out/wasm-kinds/vota_web/vota_web_wasm.wasm | awk '/ func\[/ {f=$2} / i32\.const 21176$/ {print f}' | tr '\n' ' '; echo
      func[5152]: func[5725]:

## R20. A slot's vtable, read from the data when `ledger/vtables.json` has no row or too long a one

`ledger/classes.json` misses classes as `vtables.json` does ([units.md](units.md) §U12), and `fn` then names no vtable
class for a slot a function fills: 11592's header gives only the class its vptr store names and `table slots 2275`. A
vtable is a zero word, the typeinfo's address and the slots, so from a slot, walk back over the words that are table
slots to the typeinfo, whose second word points at the mangled name:

```sh
wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'ref\.func:11592$'
#   - elem[2275] = ref.func:11592
python3 -I - target/vota_web_wasm.wasm 2275 <<'END'
import struct, sys
sys.path.insert(0, 'tools/extract'); import wasmmod
m = wasmmod.Module(sys.argv[1]); base, img = m.memory_image(); s = int(sys.argv[2]); n = max(m._elem()) + 1
w = lambda a: struct.unpack_from('<I', img, a - base)[0]
for o in range(0, len(img) - 3, 4):
    if struct.unpack_from('<I', img, o)[0] != s: continue
    a = base + o
    while 0 < w(a - 4) < n: a -= 4                      # back over the slots before it
    ti = w(a - 4)
    if w(a - 8) != 0 or not base <= ti < base + len(img): continue
    name = img[w(ti + 4) - base:].split(b'\0')[0].decode()
    print('vtable', a - 8, 'slot', (base + o - a) // 4, 'typeinfo', ti, name)
END
# vtable 1555728 slot 2 typeinfo 1555752 N5comum3asn29CConversorCodigoCargoConsultaE
```

So 11592 is `comum::asn::CConversorCodigoCargoConsulta`'s slot 2, `DoConverte`, a class neither ledger file lists. A
small slot number is also an integer, so a search for one can print several vtables; take the one whose class the
function's vptr stores or callers agree with.

A row can also be too long: the extraction reads on past a vtable's last slot into the next object. `vtables.json` gives
`ModuloEleitores::Dedo` nine functions, and `fn` names Dedo for 11895 at slot 8, but a generated SEQUENCE class has
seven slots ([asn1.md](asn1.md) §A3). The words after Dedo's seventh are the head of the SEQUENCE_OF info record that
follows: table slot 2445 (9010, `SEQUENCE_OF_Base::create`) and the tag 16, which as a slot is 11895's:

```sh
python3 -I -c "import struct, sys; sys.path.insert(0, 'tools/extract'); import wasmmod; base, img = wasmmod.Module('target/vota_web_wasm.wasm').memory_image(); print(struct.unpack_from('<11I', img, 1566108 - base))"
# (0, 1566036, 2195, 2603, 2197, 2198, 2199, 2200, 2201, 2445, 16)
```

Count a class's slots against its family before reading a slot past the base's count as a member.
