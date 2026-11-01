// Roots: reach unit 50's functions the way the target does. Each is called directly in the target by callers no object
// of the link holds yet, and binaryen inlines a function called once, so a stand-in calls each twice; two are reached by
// table slot only, and the stand-ins take their addresses. Declared through asm labels, so this TU needs no uenux2 header
// and instantiates nothing; a function that returns a class takes the result's address first, as the target's do.
// - vota::impl::IInformacaoThreadOperador::GetInst (target fn 599): the 16 vota:: functions over it and
//   GetTextoIdentidadeDigitada (fn 10586) call it in the link, and w50_getinst stands for its callers not written yet,
//   fns 3616, 10425, 10451, 10481, 10523, 10646, 10676 and 10680 (`awk -F'\t' '$2==599' ledger/callgraph.tsv`). GetInst
//   builds the class with its constructor inlined and stores the vtable (@1590108), which keeps the slots' bodies and the
//   destructors (fns 10552 and 10551).
// - the vota:: functions over GetInst, each with the target callers w50_fachada stands for: IsAudioAtivado (fn 2746;
//   3883, 5400, 10481, 10511), IsAudioAtivadoMesario (1687; 10539, 10646, 10689, 10695, 10742, 10751),
//   SetAudioAtivadoMesario (5415; 10523, 10751), LimpaBiometria (3621; 5400, 10500, 10511), AgendaInspecao (3620; 652,
//   10527, 10676), IsVotacaoBloqueadaPorHorario (2226; 10676, 10677, 10680, 10689, 10706), SetIdentidadeDigitada (5414;
//   10677), SetTipoIdentidadeDigitada (3619; 10626, 10627, 10677), GetIdentidadeDigitada (3623; 10420, 10627, 10670),
//   GetTipoIdentidadeDigitada (5416; 10588, 10664), GetIdentidadeEleitor (1535; 3616, 10425, 10587, 10590, 10631),
//   SetEleitorSemFoto (5413; 3616), SetFotoNaoApresentada (1904; 3616) and GetApresentacaoFotoEleitor (2745; 10425).
//   GetTextoAudio (10584) and GetTextoComparecimento (10583) have no direct caller: fn 652 passes their table slots (4054
//   and 4053), and the sink takes their addresses. So does it for GetTextoIdentidadeDigitada (10586), whose slot 3907 fns
//   1150, 1901, 1905, 2735, 2747, 3625, 5401, 5418, 10439, 10500, 10588 and 10635 pass.
// - std::random_device's default constructor (fn 5935), the libc++ header's, whose copy cinformacaothreadoperador.cpp.o
//   emits first: its callers are CInformacaoThreadOperador::SorteiaDataHoraInspecao (fn 5412) and fn 11803 (a slot of
//   vota::testeteclado::impl::CGeradorTeclasAleatorio, not written), which w50_random_device stands for.
extern "C" {
int informacaothreadoperador_getinst() __asm__("_ZN4vota4impl25IInformacaoThreadOperador7GetInstEv");
int informacaothreadoperador_random_device(void* dispositivo) __asm__("_ZNSt3__213random_deviceC2B8ne210108Ev");

int vota_IsAudioAtivado() __asm__("_ZN4vota14IsAudioAtivadoEv");
int vota_IsAudioAtivadoMesario() __asm__("_ZN4vota21IsAudioAtivadoMesarioEv");
void vota_SetAudioAtivadoMesario(bool ativado) __asm__("_ZN4vota22SetAudioAtivadoMesarioEb");
void vota_GetTextoAudio(void* texto) __asm__("_ZN4vota13GetTextoAudioEv");
void vota_LimpaBiometria() __asm__("_ZN4vota14LimpaBiometriaEv");
void vota_GetTextoComparecimento(void* texto) __asm__("_ZN4vota22GetTextoComparecimentoEv");
void vota_AgendaInspecao() __asm__("_ZN4vota14AgendaInspecaoEv");
int vota_IsVotacaoBloqueadaPorHorario() __asm__("_ZN4vota28IsVotacaoBloqueadaPorHorarioEv");
void vota_SetIdentidadeDigitada(const void* identidade) __asm__(
    "_ZN4vota21SetIdentidadeDigitadaERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
void vota_SetTipoIdentidadeDigitada(int tipo) __asm__(
    "_ZN4vota25SetTipoIdentidadeDigitadaEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void vota_GetIdentidadeDigitada(void* identidade) __asm__("_ZN4vota21GetIdentidadeDigitadaEv");
int vota_GetTipoIdentidadeDigitada() __asm__("_ZN4vota25GetTipoIdentidadeDigitadaEv");
void vota_GetIdentidadeEleitor(void* identidade) __asm__("_ZN4vota20GetIdentidadeEleitorEv");
void vota_SetEleitorSemFoto() __asm__("_ZN4vota17SetEleitorSemFotoEv");
void vota_SetFotoNaoApresentada(int resultado) __asm__(
    "_ZN4vota21SetFotoNaoApresentadaEN7ecourna3app5dados24CApresentacaoFotoEleitor10EResultadoE");
void vota_GetApresentacaoFotoEleitor(void* apresentacao) __asm__("_ZN4vota26GetApresentacaoFotoEleitorEv");
void vota_GetTextoIdentidadeDigitada(void* texto) __asm__("_ZN4vota26GetTextoIdentidadeDigitadaEv");
}

namespace {

__attribute__((noinline)) int w50_getinst(int salto)
{
    const int primeira = informacaothreadoperador_getinst();
    return primeira == informacaothreadoperador_getinst() ? salto + 3 : salto + 5;
}

__attribute__((noinline)) int w50_random_device(int salto)
{
    char dispositivos[2];
    const int primeiro = informacaothreadoperador_random_device(&dispositivos[0]);
    return primeiro == informacaothreadoperador_random_device(&dispositivos[1]) ? salto + 7 : salto + 11;
}

__attribute__((noinline)) int w50_fachada(int salto, void* resultado, const void* identidade)
{
    int soma = salto;
    soma += vota_IsAudioAtivado() + 2 * vota_IsAudioAtivado();
    soma += vota_IsAudioAtivadoMesario() + 3 * vota_IsAudioAtivadoMesario();
    vota_SetAudioAtivadoMesario(soma > 4);
    vota_SetAudioAtivadoMesario(soma > 9);
    vota_LimpaBiometria();
    vota_LimpaBiometria();
    vota_AgendaInspecao();
    vota_AgendaInspecao();
    soma += vota_IsVotacaoBloqueadaPorHorario() + 5 * vota_IsVotacaoBloqueadaPorHorario();
    vota_SetIdentidadeDigitada(identidade);
    vota_SetIdentidadeDigitada(resultado);
    vota_SetTipoIdentidadeDigitada(soma);
    vota_SetTipoIdentidadeDigitada(soma + 1);
    vota_GetIdentidadeDigitada(resultado);
    vota_GetIdentidadeDigitada(static_cast<char*>(resultado) + 16);
    soma += vota_GetTipoIdentidadeDigitada() + 7 * vota_GetTipoIdentidadeDigitada();
    vota_GetIdentidadeEleitor(resultado);
    vota_GetIdentidadeEleitor(static_cast<char*>(resultado) + 32);
    vota_SetEleitorSemFoto();
    vota_SetEleitorSemFoto();
    vota_SetFotoNaoApresentada(soma);
    vota_SetFotoNaoApresentada(soma + 2);
    vota_GetApresentacaoFotoEleitor(resultado);
    vota_GetApresentacaoFotoEleitor(static_cast<char*>(resultado) + 48);
    return soma;
}

const void* volatile w50_sink;

struct SInformacaoThreadOperadorRoots {
    SInformacaoThreadOperadorRoots()
    {
        w50_sink = reinterpret_cast<const void*>(&w50_getinst);
        w50_sink = reinterpret_cast<const void*>(&w50_random_device);
        w50_sink = reinterpret_cast<const void*>(&w50_fachada);
        w50_sink = reinterpret_cast<const void*>(&vota_GetTextoAudio);
        w50_sink = reinterpret_cast<const void*>(&vota_GetTextoComparecimento);
        w50_sink = reinterpret_cast<const void*>(&vota_GetTextoIdentidadeDigitada);
    }
} w50_roots;

} // namespace
