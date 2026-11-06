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
void w1942(int) __asm__("_ZN5comum20GetIdentificacaoUrnaEv");
void w3788(int, int, int) __asm__("_ZNK5comum8CAppInfo15GetCodigosCargaENS_10EUrnaTurnoE");
int w2841(int, int) __asm__("_ZNK5comum8CAppInfo7TemVotaENS_10EUrnaTurnoE");
int w819() __asm__("_ZN5comum9CPartidos7GetInstEv");
int w2819() __asm__("_ZN5comum6CFotos7GetInstEv");
int w3751(int) __asm__("_ZN5comum9CPartidosC1Ev");
int w3756(int) __asm__("_ZN5comum6CFotosC1Ev");
void w3755(void* imagem, const void* id) __asm__("_ZN5comum6CFotos9GetImagemERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

const void* volatile cappinfo_sink;

// Stands for fn 457's callers (3769, 436, 1274, 1836, 3288, 3290, 4657, 4668, 4682, 4687, 2298, 3898, unit 110's 2266,
// unit 104's 10635, unit 277's 10710, unit 329's 7160, unit 293's 2725, unit 135's 5382, unit 283's 10590, unit 155's
// 11242, unit 221's 10451, unit 110's 3059 and 4160, fragment 372's 12105, unit 116's 6737 and unit 241's 7174 are
// linked, and 491): 7787, 12098, 12110, 12134.
__attribute__((noinline)) int GeraisConst(int a, int b) { return w457(a) ^ w457(b); }
// The stand-in for fn 903's caller 7160 went: 7160 (unit 329) is linked, with unit 102's four, unit 138's 11870 and
// 11871, unit 50's 10566, unit 104's 12082 and 12081, unit 277's 10710 and unit 110's 13023.
// The stand-in for fn 697's callers 6737 and 7174 went: both are linked (units 116 and 241), with unit 239's 10501,
// unit 199's 11994, unit 142's 1150, unit 50's 10569, unit 197's 3229, unit 138's 11835, unit 161's 10680, 652 and
// 10677, unit 121's 2753, unit 277's 10706 and 10722, unit 104's 11924 and 10209, unit 156's 12077 and unit 152's 10440.
// Stands for fn 3788's callers: 7787, 12098, 12110.
__attribute__((noinline)) void Codigos(int a, int b, int c)
{
    w3788(a, c, 51);
    w3788(b + 12, c, 51);
}
// Stands for fn 2841's caller 12110 (11242, unit 155's, and 12105, fragment 372's, which calls it twice, are in the
// link), which passes the turn it reads (not a constant): one call, the two that stood for 12105 having gone with it.
__attribute__((noinline)) int Votos(int a, int t) { return 2 * w2841(a + 4, t ^ 1) + 3; }

// Stands for fn 819's caller 7787 (11976, unit 325's, 11260, unit 220's, 11213, 11255, 3820, 6954, 11181, 5922,
// 11261, 11683, 11711, 5604, unit 155's written Gera, 2543, unit 98's, and 11629, unit 200's, are in the link):
// one call, the one that stood for 11976 having gone with it.
__attribute__((noinline)) int Partidos() { return 7 * w819() + 1; }
// Stands for fn 2819's callers: 7787 and 12641 (12520, unit 110's, is in the link).
__attribute__((noinline)) int Fotos() { return w2819() - 9 * w2819(); }
// Stand for fns 11499 and 11501, which hold CPartidos::GetInst inlined, and 12641, which holds CFotos::GetInst: each is a
// second caller of the constructor, and none is written (3755, which holds it too, is in the link).
__attribute__((noinline)) void ConstroiPartidos(int a) { w3751(a + 4); }
__attribute__((noinline)) void ConstroiFotos(int a) { w3756(a + 8); }
// Stands for fn 3755's (CFotos::GetImagem's) caller 12641, CDataImage<CCandidaturasDSFoto>::GetData, not written, which
// calls it twice (its other caller, 12520, is in the link): the result is a std::vector<uint8_t>, returned through the
// first argument.
__attribute__((noinline)) void Imagens(char* imagem, const void* id)
{
    w3755(imagem, id);
    w3755(imagem + 12, id);
}
// The stand-in for SalvaVotaInterno's and SalvaVotaExterno's (fns 3790, 3789) caller 7174 went: it is linked (unit
// 241), with 491 and 10590 (units 205 and 283).

struct SCAppInfoRoots {
    SCAppInfoRoots()
    {
        cappinfo_sink = reinterpret_cast<const void*>(&w185);
        cappinfo_sink = reinterpret_cast<const void*>(&w291);
        cappinfo_sink = reinterpret_cast<const void*>(&w261);
        cappinfo_sink = reinterpret_cast<const void*>(&w1942);
        cappinfo_sink = reinterpret_cast<const void*>(&GeraisConst);
        cappinfo_sink = reinterpret_cast<const void*>(&Codigos);
        cappinfo_sink = reinterpret_cast<const void*>(&Votos);
        cappinfo_sink = reinterpret_cast<const void*>(&Partidos);
        cappinfo_sink = reinterpret_cast<const void*>(&Fotos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiPartidos);
        cappinfo_sink = reinterpret_cast<const void*>(&ConstroiFotos);
        cappinfo_sink = reinterpret_cast<const void*>(&Imagens);
    }
} cappinfo_roots;

} // namespace
