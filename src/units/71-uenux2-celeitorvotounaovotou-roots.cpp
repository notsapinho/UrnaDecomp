// Roots: keep vota::CEleitorVotouNaoVotou's StartState and destructors (target fns 10431, 1284 and 2884, slots 2, 0 and
// 1 of its vtable @1592928) in the skeleton link the way the target keeps them.
//
// StartState is reached only through the vtable. The vtable is referenced in the target only by the constructor,
// inlined into GetInst (fn 1901), which is in the link: its target callers, fns 10209, 10419 and 10425, are not, so a
// stand-in calls it twice, and GetInst's constructor keeps the vtable and every slot.
//
// comum::IPedeTituloMesario's constructor (target fn 3608) has three direct call sites in the target, all in fn 10388
// (the derived states' constructors, inlined there), and uses of the `this` it returns, on which they store their own
// vptr. Two noinline callers stand in for them and use that result: their bodies differ from each other and from every
// target function, one adding to the result and one to the address. The vptr store in that constructor keeps the class's
// vtable, and so slots 0 and 2 (fns 1378 and 10314), as the three derived vtables do in the target. fn 1378 has three
// direct callers too, none stood in for: it is in the table, so binaryen keeps it out of line.
//
// Declared through asm labels with the wasm-level signatures (a by-value std::shared_ptr is the address of a copy, and a
// constructor returns `this` before binaryen runs), so this TU needs no uenux2 header and instantiates nothing; compiled
// with APP_CXXFLAGS.
extern "C" {
int w1901_root_0() __asm__("_ZN4vota21CEleitorVotouNaoVotou7GetInstEv");
int w3608_root_0(int, const void*, const void*) __asm__(
    "_ZN5comum18IPedeTituloMesarioC2ENSt3__210shared_ptrIN3api16CInteractiveFormINS3_9IScreenMTENS3_8IInputMTEEEEENS2_INS3_5IFormINS3_7IScreenEEEEE");
}

namespace {

// Stands for fns 10209, 10419 and 10425, the target callers of vota::CEleitorVotouNaoVotou::GetInst (fn 1901).
__attribute__((noinline)) int VotouNaoVotou()
{
    return w1901_root_0() | w1901_root_0();
}

__attribute__((noinline)) int ConstroiPedeTitulo(int estado, const void* form, const void* formEleitor)
{
    return w3608_root_0(estado, form, formEleitor) + 4;
}

__attribute__((noinline)) int ConstroiPedeTituloMembro(int bloco, const void* form, const void* formEleitor)
{
    return w3608_root_0(bloco + 16, form, formEleitor);
}

const void* volatile celeitorvotounaovotou_sink;

struct SCEleitorVotouNaoVotouRoots {
    SCEleitorVotouNaoVotouRoots()
    {
        celeitorvotounaovotou_sink = reinterpret_cast<const void*>(&VotouNaoVotou);
        celeitorvotounaovotou_sink = reinterpret_cast<const void*>(&ConstroiPedeTitulo);
        celeitorvotounaovotou_sink = reinterpret_cast<const void*>(&ConstroiPedeTituloMembro);
    }
} celeitorvotounaovotou_roots;

} // namespace
