// Roots: keep vota::CEleitorVotouNaoVotou's StartState and destructors (target fns 10431, 1284 and 2884, slots 2, 0 and
// 1 of its vtable @1592928) in the skeleton link the way the target keeps them.
//
// StartState is reached only through the vtable. The vtable is referenced in the target only by the constructor,
// inlined into GetInst (fn 1901), which is in the link: of its target callers, fns 10209, 10419 and 10425, only 10419
// (unit 142) is, so a stand-in calls it twice, and GetInst's constructor keeps the vtable and every slot.
//
// comum::IPedeTituloMesario's constructor (target fn 3608) has its three direct call sites in fn 10388 (the derived
// states' constructors, inlined there), which is in the link (CPedeTituloMesario::StartState), so it needs no stand-in.
//
// Declared through an asm label, so this TU needs no uenux2 header and instantiates nothing; compiled with
// APP_CXXFLAGS.
extern "C" {
int w1901_root_0() __asm__("_ZN4vota21CEleitorVotouNaoVotou7GetInstEv");
}

namespace {

// Stands for fns 10209 and 10425, the target callers of vota::CEleitorVotouNaoVotou::GetInst (fn 1901) not in the link
// (10419, unit 142's, is).
__attribute__((noinline)) int VotouNaoVotou()
{
    return w1901_root_0() | w1901_root_0();
}

const void* volatile celeitorvotounaovotou_sink;

struct SCEleitorVotouNaoVotouRoots {
    SCEleitorVotouNaoVotouRoots()
    {
        celeitorvotounaovotou_sink = reinterpret_cast<const void*>(&VotouNaoVotou);
    }
} celeitorvotounaovotou_roots;

} // namespace
