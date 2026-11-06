// Roots: keep vota::CEleitorVotando's functions in the skeleton link the way the target keeps them.
// - GetInst (fn 3229) has three direct callers in the target, fns 7428, 7481 and 11754, all in the link (units 150, 104
//   and 97): no stand-in. GetInst holds the constructor inlined, whose vptr store is the target's reference to the
//   class's vtable, and so keeps every slot.
// - RegistraVoto (fn 4471) has two direct callers in the target, fns 7428 and 11754, each calling it right after
//   GetInst, both reconstructed (units 150 and 97): no stand-in.
// - AdicionaVoto (fn 4192) and the five CLogVota::LogaVoto* members (fns 3272, 4546, 4542, 4541 and 4537) have two
//   direct callers in the target each, RegistraVoto and suspenderEleitor (fn 4442), which makes RegistraVoto's calls;
//   FinalizaEleitor (fn 4454) has two too, NeedChangeState (fn 7352) and suspenderEleitor. All are in the link: no
//   stand-in.
// - comum::md::CEleitorDecorator::GetAbrangencia (fn 3721) has three direct callers in the target: fn 5761
//   (CEleitores::DynamicCreate, unit 383's), fn 7377 (StartState), which holds GetCurrentAbrangenciaEleitor inlined,
//   and CEleitores' slot 0 (fn 2824, unit 110's), all in the link: Abrange, which stood for 5761, went.
// - comum::CCargos::OrdenaPorImpressao (fn 3782) has three direct callers in the target, fns 5604, 12098 and 12110;
//   5604 (unit 155's) is in the link: Imprime stands for the other two, two call sites.
// - The std::map<SCargoInfo, CVotos> copy of comum::md::CVotosCargos::InsereCedula (held by fn 4454) calls
//   __emplace_hint_unique_key_args (fn 5681), which calls __find_equal (fn 3251). 5681's other target caller, fn 11349
//   (comum::asn::CConversorEleicoesVota::DoDesconverte), is in the link (unit 140's). 3251's are fns 2386
//   (vota::CTelasCargo's constructor, unit 150's) and 3266 (src/app/roots_set.cpp's), both in the link: Procura,
//   which stood for 2386, went.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w197_ordena_impressao(void* cargos) __asm__("_ZN5comum7CCargos18OrdenaPorImpressaoEv");
}

namespace {

const void* volatile celeitorvotando_sink;

// stands for fns 12098 and 12110 (5604, unit 155's, is in the link)
__attribute__((noinline)) void Imprime(char* cargos, int vezes)
{
    w197_ordena_impressao(cargos);
    if (vezes > 1) {
        w197_ordena_impressao(cargos);
    }
}

struct SCEleitorVotandoRoots {
    SCEleitorVotandoRoots()
    {
        celeitorvotando_sink = reinterpret_cast<const void*>(&Imprime);
    }
} celeitorvotando_roots;

} // namespace
