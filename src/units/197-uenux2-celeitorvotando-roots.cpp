// Roots: keep vota::CEleitorVotando's functions in the skeleton link the way the target keeps them.
// - ChamaEstadoProximoCargo (target fn 4459) and MostraCargoNoOperador (fn 4464) have the same two direct callers in the
//   target, CEleitorVotando's NeedChangeState (fn 7352, slot 3) and its slot 2 (fn 7377, which holds IniciaCiclo's
//   records), both pending; with no caller wasm-ld drops a function, and with one binaryen inlines it. Precisa stands for
//   fn 7352 and Inicia for fn 7377, each calling both once, with bodies no target function has. Each goes when the
//   caller it stands for is in the link.
// - GetInst (fn 3229) has three direct callers in the target, fns 7428, 7481 and 11754, none reconstructed: Obtem
//   stands for them, two call sites. GetInst holds the constructor inlined, whose vptr store is the target's reference
//   to the class's vtable, and so keeps every slot.
// - RegistraVoto (fn 4471) has two direct callers in the target, fns 7428 and 11754, each calling it right after
//   GetInst: Registra stands for them, two call sites on GetInst's result.
// - AdicionaVoto (fn 4192) and the five CLogVota::LogaVoto* members (fns 3272, 4546, 4542, 4541 and 4537) have two
//   direct callers in the target each, RegistraVoto and suspenderEleitor (fn 4442, records celeitorvotando.cpp:410 and
//   :427, not written), which makes RegistraVoto's calls: Suspende stands for fn 4442, one call of each.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w197_chama_estado(void* eleitor) __asm__("_ZN4vota15CEleitorVotando23ChamaEstadoProximoCargoEv");
void w197_mostra_cargo(const void* cargo) __asm__("_ZN4vota21MostraCargoNoOperadorERKN5comum2md6CCargoE");
char* w197_inst() __asm__("_ZN4vota15CEleitorVotando7GetInstEv");
void w197_registra(void* eleitor, unsigned char cargo, int tipo, const void* numero) __asm__(
    "_ZN4vota15CEleitorVotando12RegistraVotoEhN5comum2md5CVoto5ETipoERKNSt3__212basic_stringIcNS5_11char_traitsIcEENS5_"
    "9allocatorIcEEEE");
void w197_adiciona(unsigned char cargo, const void* voto) __asm__("_ZN4vota12AdicionaVotoEhRKN5comum2md5CVotoE");
void* w197_log() __asm__("_ZN4vota8CLogVota7GetInstEv");
void w197_loga_cssp(void* log, unsigned char cargo) __asm__(
    "_ZN4vota8CLogVota37LogaVotoCargoSemCandidatoPorSuspensaoEh");
void w197_loga_bps(void* log, unsigned char cargo) __asm__("_ZN4vota8CLogVota26LogaVotoBrancoPorSuspensaoEh");
void w197_loga_csc(void* log, unsigned char cargo) __asm__("_ZN4vota8CLogVota25LogaVotoCargoSemCandidatoEh");
void w197_loga_nps(void* log, unsigned char cargo) __asm__("_ZN4vota8CLogVota24LogaVotoNuloPorSuspensaoEh");
void w197_loga_vc(void* log, unsigned char cargo) __asm__("_ZN4vota8CLogVota18LogaVotoConfirmadoEh");
}

namespace {

const void* volatile celeitorvotando_sink;

// stands for fn 7352
__attribute__((noinline)) int Precisa(void* eleitor, const char* cargo)
{
    w197_mostra_cargo(cargo + 4);
    w197_chama_estado(eleitor);
    return 197;
}

// stands for fn 7377
__attribute__((noinline)) void Inicia(void* eleitor, const char* cargo, int* contador)
{
    w197_mostra_cargo(cargo);
    w197_chama_estado(eleitor);
    *contador += 2;
}

// stands for fns 7428, 7481 and 11754
__attribute__((noinline)) int Obtem(int vezes)
{
    const char* primeiro = w197_inst();
    const char* segundo = w197_inst();
    return primeiro[vezes] - segundo[3];
}

// stands for fns 7428 and 11754
__attribute__((noinline)) int Registra(const unsigned char* cargos, int tipo, const char* numeros)
{
    char* eleitor = w197_inst();
    w197_registra(eleitor, cargos[0], tipo, numeros);
    w197_registra(eleitor, cargos[1], tipo + 1, numeros + 12);
    return cargos[2] + tipo;
}

// stands for fn 4442
__attribute__((noinline)) void Suspende(const unsigned char* cargos, const char* votos)
{
    w197_adiciona(cargos[0], votos + 16);
    void* log = w197_log();
    w197_loga_cssp(log, cargos[1]);
    w197_loga_bps(log, cargos[2]);
    w197_loga_csc(log, cargos[3]);
    w197_loga_nps(log, cargos[4]);
    w197_loga_vc(log, cargos[5]);
}

struct SCEleitorVotandoRoots {
    SCEleitorVotandoRoots()
    {
        celeitorvotando_sink = reinterpret_cast<const void*>(&Precisa);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Inicia);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Obtem);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Registra);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Suspende);
    }
} celeitorvotando_roots;

} // namespace
