// Roots: keep the members of comum::CAppInfo, CFotos and CPartidos in the skeleton link the way the target keeps them. Their
// users are not reconstructed yet. Fns 185, 291, 261 and 1942 hold table slots (33, 35, 50 and 1567, in the target's elem
// segment), so each has its own address taken: that is the reference the target has, and a table entry keeps a body out of
// line whatever its callers. It also keeps a parameter, which is why fn 261 has one although all 86 of its direct calls pass
// 51. The others have direct callers and no slot (ledger/callgraph.tsv), so a noinline stand-in gives each two call sites,
// counting the reconstructed ones, and binaryen keeps its body out of line. Each stand-in's comment names the target callers
// it stands for. Every target caller of GetVota's const overload and of GetCodigosCarga passes TURNO_ATUAL, 51, so the
// stand-ins do, and binaryen folds it as the target's did (fns 903 and 3788 have no parameter for it). Declared through asm
// labels with the object's signatures; address-taken from a static constructor.
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

// Stands for fn 457's callers (3769, 436 and 1274 are linked): 491, 1836, 2266, 2298, 2725, 3059, 3288, 3290, 3898,
// 4160, 4657, 4668, 4682, 4687, 5382, 6737, 7160, 7174, 7787, 10451, 10590, 10635, 10710, 11242, 12098, 12105, 12110,
// 12134.
__attribute__((noinline)) int GeraisConst(int a, int b) { return w457(a) ^ w457(b); }
// Stands for fn 903's callers 7160, 10566, 10710, 12081, 12082, 13023 (unit 102's four and unit 138's 11870 and 11871
// are linked).
__attribute__((noinline)) int VotasConst(int a, int b) { return w903(a, 51) * w903(b, 51); }
// Stands for fn 697's callers: 652, 2753, 3229, 6737, 7174, 10209, 10440, 10501, 10569, 10677, 10680, 10706,
// 10722, 11835, 11924, 12077 (unit 199's 11994 and unit 142's 1150 are linked).
__attribute__((noinline)) int Treinamentos() { return w697() | (w697() << 1); }
// Stands for fn 3788's callers: 7787, 12098, 12110.
__attribute__((noinline)) void Codigos(int a, int b, int c)
{
    w3788(a, c, 51);
    w3788(b + 12, c, 51);
}

// Stands for fn 819's callers: 2543, 3820, 5604, 5922, 6954, 7787, 11181, 11213, 11255, 11260, 11261, 11629, 11683,
// 11711, 11976.
__attribute__((noinline)) int Partidos() { return w819() + 7 * w819(); }
// Stands for fn 2819's callers: 7787, 12520, 12641.
__attribute__((noinline)) int Fotos() { return w2819() - 9 * w2819(); }
// Stand for fns 11499 and 11501, which hold CPartidos::GetInst inlined, and 3755 and 12641, which hold CFotos::GetInst: each
// is a second caller of the constructor, and none is written.
__attribute__((noinline)) void ConstroiPartidos(int a) { w3751(a + 4); }
__attribute__((noinline)) void ConstroiFotos(int a) { w3756(a + 8); }

struct SCAppInfoRoots {
    SCAppInfoRoots()
    {
        cappinfo_sink = reinterpret_cast<const void*>(&w185);
        cappinfo_sink = reinterpret_cast<const void*>(&w291);
        cappinfo_sink = reinterpret_cast<const void*>(&w261);
        cappinfo_sink = reinterpret_cast<const void*>(&w1942);
        cappinfo_sink = reinterpret_cast<const void*>(&GeraisConst);
        cappinfo_sink = reinterpret_cast<const void*>(&VotasConst);
        cappinfo_sink = reinterpret_cast<const void*>(&Treinamentos);
        cappinfo_sink = reinterpret_cast<const void*>(&Codigos);
        cappinfo_sink = reinterpret_cast<const void*>(&Partidos);
        cappinfo_sink = reinterpret_cast<const void*>(&Fotos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiPartidos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiFotos);
    }
} cappinfo_roots;

} // namespace
