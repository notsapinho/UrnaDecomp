// Roots: reach unit 50's functions the way the target does. Each is called directly in the target by callers no object
// of the link holds yet, and binaryen inlines a function called once, so a stand-in calls each twice; one reached by
// table slot has its address taken. Declared through asm labels, so this TU needs no uenux2 header
// and instantiates nothing; a function that returns a class takes the result's address first, as the target's do.
// - vota::impl::IInformacaoThreadOperador::GetInst (target fn 599): the 16 vota:: functions over it and
//   GetTextoIdentidadeDigitada (fn 10586) call it in the link, and w50_getinst stands for its callers not written yet,
//   fns 10425 and 10451 (`awk -F'\t' '$2==599' ledger/callgraph.tsv`; 10676 and 10680, unit 161's, 10646, unit
//   104's, 10523, unit 152's, 3616, unit 319's, and 10481, unit 282's, are in the link). GetInst
//   builds the class with its constructor inlined and stores the vtable (@1590108), which keeps the slots' bodies and the
//   destructors (fns 10552 and 10551).
// - the vota:: functions over GetInst, each with the target callers w50_fachada stands for: GetIdentidadeEleitor (1535;
//   10425, 10590; 10587, 10631 and 3616, units 152's, 104's and 319's, are in the link) and GetApresentacaoFotoEleitor
//   (2745; 10425). The calls of LimpaBiometria (3621), SetEleitorSemFoto (5413) and SetFotoNaoApresentada (1904) went:
//   their target callers (5400, 10500 and 10511; 3616) are in the link. So did those of IsAudioAtivado (2746): its
//   target callers 10481 (unit 282's), 3883 (unit 282's merge), 10511 (unit 161's) and 5400 (unit 239's) are in the
//   link. SetIdentidadeDigitada (5414) needs none: its one target caller, 10677 (unit 161's), calls it twice.
//   AgendaInspecao (3620), SetTipoIdentidadeDigitada (3619), GetIdentidadeDigitada (3623), IsAudioAtivadoMesario (1687)
//   and IsVotacaoBloqueadaPorHorario (2226) need none either: their target callers are in the link (652, 10527 and
//   10676; 10626, 10627 and 10677; 10420, 10627 and 10670; 10539, 10646, 10689, 10695, 10742 and 10751; 10676, 10677,
//   10680, 10689 and 10706).
//   SetAudioAtivadoMesario (5415) and GetTipoIdentidadeDigitada (5416) have their two target callers each in the link
//   (10523, unit 152's, and 10751, unit 277's; 10588, unit 174's, and 10664, unit 161's): no stand-in.
//   GetTextoAudio (10584) and GetTextoComparecimento (10583) have no direct caller: fn 652, the one target function
//   that passes their table slots (4054 and 4053), is in the link, so no stand-in takes their addresses. The sink of
//   GetTextoIdentidadeDigitada's (10586) went: fn 10500, the last target function that passes its slot 3907 not in the
//   link, is (1150, 1901, 1905, 2735, 2747, 3625, 5401, 5418, 10439, 10588 and 10635 pass it too).
extern "C" {
int informacaothreadoperador_getinst() __asm__("_ZN4vota4impl25IInformacaoThreadOperador7GetInstEv");

void vota_GetIdentidadeEleitor(void* identidade) __asm__("_ZN4vota20GetIdentidadeEleitorEv");
void vota_GetApresentacaoFotoEleitor(void* apresentacao) __asm__("_ZN4vota26GetApresentacaoFotoEleitorEv");
}

namespace {

__attribute__((noinline)) int w50_getinst(int salto)
{
    const int primeira = informacaothreadoperador_getinst();
    return primeira == informacaothreadoperador_getinst() ? salto + 3 : salto + 5;
}

__attribute__((noinline)) int w50_fachada(int salto, void* resultado)
{
    int soma = salto;
    vota_GetIdentidadeEleitor(resultado);
    vota_GetIdentidadeEleitor(static_cast<char*>(resultado) + 32);
    vota_GetApresentacaoFotoEleitor(resultado);
    vota_GetApresentacaoFotoEleitor(static_cast<char*>(resultado) + 48);
    return soma;
}

const void* volatile w50_sink;

struct SInformacaoThreadOperadorRoots {
    SInformacaoThreadOperadorRoots()
    {
        w50_sink = reinterpret_cast<const void*>(&w50_getinst);
        w50_sink = reinterpret_cast<const void*>(&w50_fachada);
    }
} w50_roots;

} // namespace
