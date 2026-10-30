# Reading the source from the target's bytes

What a target body says about the C++ that compiled to it, beyond the name its `std::source_location` record gives:
the parameters a wasm type hides, how a class returns by value, whether a destructor is out of line, implicit or
`final`, whether a class is abstract, a free function's linkage, and code binaryen inlined from another function.
`docs/how-to-decompile.md` steps 2, 3 and 5 rely on these.

The probes are short TUs compiled by the pinned em++ with uenux2's flags, `-O2 -fPIC -std=c++20 -DNDEBUG
-fno-strict-aliasing` (`docs/reference/facts/app-flags.md` §F6), under `build/out/DOCS-A/probe/` of a checkout at
7bf701e; their sources are given in full. Readouts are `pnpm --silent wasm fn ../target/vota_web_wasm.wasm <index>`,
run from `asmlift-wasm/` with Node 24 first on PATH ([workflow.md](workflow.md) §W1).

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

## R4. A destructor that destroys members and stores no vptr is a `final` class's

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

## R5. A D0 that calls its D2 is an out-of-line destructor's; a D0 that holds the D2's body is an implicit or in-class one's

For a destructor defined out of line, clang emits D1 as an alias of D2 and the deleting destructor D0 calls D1, then
`operator delete`; the inliner does not inline through the alias. An implicit destructor, or one defined in the
class, is linkonce_odr with no alias, and D0 inlines it. The probe above (R4):

    wasm-objdump -d build/out/DOCS-A/probe/dtor.o | awk '/^[0-9a-f]+ func\[/ {name=$3} /D0Ev>:/ {p=1} p && /call |i32.store/ {print name, $0} /^$/ {p=0}'
      <_ZN3OolD0Ev>:  0000fd: 10 81 80 80 80 00          | call 1 <_ZN3OolD1Ev>
      <_ZN3OolD0Ev>:  000108: 10 80 80 80 80 00          | call 0 <env._ZdlPvm>
      <_ZN3FinD0Ev>:  00015d: 10 84 80 80 80 00          | call 4 <_ZN3FinD1Ev>
      <_ZN3FinD0Ev>:  000168: 10 80 80 80 80 00          | call 0 <env._ZdlPvm>
      <_ZN3InlD0Ev>:  0001b8: 36 02 00                   | i32.store 2 0
      <_ZN3InlD0Ev>:  0001d8: 10 80 80 80 80 00          |   call 0 <env._ZdlPvm>
      <_ZN3InlD0Ev>:  0001e3: 10 80 80 80 80 00          | call 0 <env._ZdlPvm>

(the awk also prints lines of the functions that follow each D0 up to the next blank line; the D0 rows are the ones
named `D0Ev`). In the target:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11443 | sed -n '/folded readout/,$p'
      function f11443(i32 p0) -> () {
        f5709(p0);
        f136(p0);
      }

11443 is `comum::asn::CVisitanteFoto`'s D0 calling its D2 5709: out of line, as unit 36 writes it (`git show
9271d74:src/uenux2/src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp` has `CVisitanteFoto::~CVisitanteFoto() =
default;` on line 5). 11176 (`comum::CSigVerifier`'s D0; unit 26 keeps the destructor implicit) and 12049
(`vota::IQRCodeBUDS`'s) free the members themselves and then call `f136(p0)`, `operator delete`; 12049 starts with
the vptr store `i32.store[p0] = 1542092` (R4: not `final`). The D2's bytes are the same in both forms, so only the D0 tells them apart. Whether the destructor
is out of line decides the key function, and so the TU that emits the vtable, the D2 and the D0.

## R6. A class whose only virtual members are inline has no key function: only a TU that uses its vtable emits it

With no non-inline virtual member, the vtable, D2 and D0 are linkonce_odr, emitted only by a TU that references the
vtable, which a constructor defined there does. In the probe of R4, `NoCtor` (destructor in the class, one
non-virtual member defined) gets nothing; `Inl` (the same with a constructor defined) gets a weak vtable:

    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only /work/build/out/DOCS-A/probe/dtor.o | /usr/bin/grep -E '_ZTV|NoCtor'
      000000ae T _ZN6NoCtor1fEv
      00000040 D _ZTV3Fin
      00000010 W _ZTV3Inl
      00000000 D _ZTV3Ool

So to land such a class's destructors in the form the target's D0 shows (R5, in the class), the TU must also define
a constructor, at its record's line; the target may have inlined it everywhere, and our link then drops it as
unreferenced. The out-of-line form emits them without a constructor but gives a D0 that calls the D2 (R5).

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
