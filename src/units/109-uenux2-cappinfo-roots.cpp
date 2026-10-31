// Roots: keep comum::CAppInfo's members in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. Each of these has direct callers in the target and no table slot (ledger/callgraph.tsv), so the
// stand-ins give each two call sites and binaryen keeps its body out of line. Every target caller of GetVota's const
// overload and of GetCodigosCarga passes TURNO_ATUAL, 51, so both stand-ins do, and binaryen folds it as the target's
// did (fns 903 and 3788 have no parameter for it); the other overload's stand-ins pass two values. Declared through asm labels with the object's
// signatures; address-taken from a static constructor.
extern "C" {
int w185() __asm__("_ZN5comum8CAppInfo7GetInstEv");
int w291(int) __asm__("_ZN5comum8CAppInfo8GetGeralEv");
int w457(int) __asm__("_ZNK5comum8CAppInfo8GetGeralEv");
int w261(int, int) __asm__("_ZN5comum8CAppInfo7GetVotaENS_10EUrnaTurnoE");
int w903(int, int) __asm__("_ZNK5comum8CAppInfo7GetVotaENS_10EUrnaTurnoE");
int w697() __asm__("_ZN5comum8CAppInfo20EhTreinamentoEleitorEv");
void w1942(int) __asm__("_ZN5comum20GetIdentificacaoUrnaEv");
void w3788(int, int, int) __asm__("_ZNK5comum8CAppInfo15GetCodigosCargaENS_10EUrnaTurnoE");
int w819() __asm__("_ZN5comum9CPartidos7GetInstEv");
int w2819() __asm__("_ZN5comum6CFotos7GetInstEv");
int w3751(int) __asm__("_ZN5comum9CPartidosC1Ev");
int w3756(int) __asm__("_ZN5comum6CFotosC1Ev");
}

namespace {

const void* volatile cappinfo_sink;

__attribute__((noinline)) int Instancias() { return w185() + 2 * w185(); }
__attribute__((noinline)) int Gerais(int a, int b) { return w291(a) - w291(b); }
__attribute__((noinline)) int GeraisConst(int a, int b) { return w457(a) ^ w457(b); }
__attribute__((noinline)) int Votas(int a, int b, int t) { return w261(a, t) + 3 * w261(b, 49); }
__attribute__((noinline)) int VotasConst(int a, int b) { return w903(a, 51) * w903(b, 51); }
__attribute__((noinline)) int Treinamentos() { return w697() | (w697() << 1); }
__attribute__((noinline)) void Identificacoes(int a, int b)
{
    w1942(a);
    w1942(b + 12);
}

__attribute__((noinline)) void Codigos(int a, int b, int c)
{
    w3788(a, c, 51);
    w3788(b + 12, c, 51);
}

__attribute__((noinline)) int Partidos() { return w819() + 7 * w819(); }
__attribute__((noinline)) int Fotos() { return w2819() - 9 * w2819(); }

// fns 11499 and 11501 hold CPartidos::GetInst inlined, 3755 and 12641 CFotos::GetInst: each is a second caller of the
// constructor, and neither is written.
__attribute__((noinline)) void ConstroiPartidos(int a) { w3751(a + 4); }
__attribute__((noinline)) void ConstroiFotos(int a) { w3756(a + 8); }

struct SCAppInfoRoots {
    SCAppInfoRoots()
    {
        cappinfo_sink = reinterpret_cast<const void*>(&Instancias);
        cappinfo_sink = reinterpret_cast<const void*>(&Gerais);
        cappinfo_sink = reinterpret_cast<const void*>(&GeraisConst);
        cappinfo_sink = reinterpret_cast<const void*>(&Votas);
        cappinfo_sink = reinterpret_cast<const void*>(&VotasConst);
        cappinfo_sink = reinterpret_cast<const void*>(&Treinamentos);
        cappinfo_sink = reinterpret_cast<const void*>(&Identificacoes);
        cappinfo_sink = reinterpret_cast<const void*>(&Codigos);
        cappinfo_sink = reinterpret_cast<const void*>(&Partidos);
        cappinfo_sink = reinterpret_cast<const void*>(&Fotos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiPartidos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiFotos);
    }
} cappinfo_roots;

} // namespace
