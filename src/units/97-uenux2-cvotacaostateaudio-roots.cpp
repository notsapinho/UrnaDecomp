// Roots: keep unit 97's classes in the skeleton link the way the target keeps them.
//
// The five vota states' slot 15 (target fns 11704, 11701, 11748, 11731, 11735) and destructors (884, 883), the three
// comum::CPedeTituloMesario* states' D0 (3609) and vota::testeteclado::CErroTesteTecladoFim's StartState and destructors
// (3857, 785, 1560) are reached only through their vtables, each referenced in the target by a constructor, inlined into
// fns 1961 and 2901, into 10388, and into a builder not reconstructed. Taking the vtables' address keeps every slot.
// None of those direct callers of the destructors is stood in for: the destructors are in the table, so binaryen keeps
// them out of line.
//
// api::CPosixRWMutex's constructor (target fn 10245) is reached only by its table slot 244, which fn 10864 passes to fn
// 6023, so its own address is taken; its vptr store keeps that class's vtable, and with it slots 0 to 4.
//
// The constructors, with direct callers in the target that are not reconstructed: CVotacaoStateAudio's (fn 1785) has
// six, of which fn 5929 is written, so EstadoAudio stands for the other five (1165, 4420, 4459, 5932, 6051).
// CConfirmaVotoEmCargo's (fn 5929) has two, fn 11752, written, and fn 11700, CConfirmaMajoritario's, which ConfirmaEmCargo
// stands for. CConfirmaProporcional's (fn 11752) has one, fn 1961, the body binaryen shares for six singletons'
// builders: DoisConfirmaProporcional stands for it with two calls. None of CEstadoComDesligamentoAutomatico's (fn 1285)
// ten callers is written (2888, 3855, 3877, 5936, 5947, 5948, 11804, 11809, 11812, 12051): DoisDesligamentos stands for
// them with two calls. Each stand-in passes what the target's callers vary (the events, the two stored arguments) as a
// variable, so binaryen folds none of them, and adds a constant somewhere, so no two are alike.
//
// Declared through asm labels (a constructor returns `this` before binaryen runs), so this TU needs no uenux2 header and
// instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cproporcionalbranco_vt[] __asm__("_ZTVN4vota19CProporcionalBrancoE");
extern const char cproporcionalnulo_vt[] __asm__("_ZTVN4vota17CProporcionalNuloE");
extern const char ccandidatoinapto_vt[] __asm__("_ZTVN4vota16CCandidatoInaptoE");
extern const char ccandidatoinexistente_vt[] __asm__("_ZTVN4vota21CCandidatoInexistenteE");
extern const char cconfirmavotolegenda_vt[] __asm__("_ZTVN4vota20CConfirmaVotoLegendaE");
extern const char cpedetitulomesarioinicial_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioInicialE");
extern const char cpedetitulomesariofinal_vt[] __asm__("_ZTVN5comum23CPedeTituloMesarioFinalE");
extern const char cpedetitulomesariovotacao_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioVotacaoE");
extern const char cerrotestetecladofim_vt[] __asm__("_ZTVN4vota12testeteclado20CErroTesteTecladoFimE");
int w10245_root_0(int) __asm__("_ZN3api13CPosixRWMutexC2Ev");
int w97_estado_audio(void*, int) __asm__("_ZN4vota18CVotacaoStateAudioC2Ei");
int w97_confirma_cargo(void*, int, int, int) __asm__("_ZN4vota20CConfirmaVotoEmCargoC2Eihi");
int w97_confirma_proporcional(void*, int, int) __asm__("_ZN4vota21CConfirmaProporcionalC2Ehi");
int w97_desligamento(void*, int) __asm__("_ZN4vota32CEstadoComDesligamentoAutomaticoC2Ei");
}

namespace {

const void* volatile cvotacaostateaudio_sink;

// stands for fns 1165, 4420, 4459, 5932 and 6051
__attribute__((noinline)) int EstadoAudio(void* estado, int eventos)
{
    return w97_estado_audio(estado, eventos + 1);
}

// stands for fn 11700
__attribute__((noinline)) int ConfirmaEmCargo(void* estado, int eventos, int tela, int tipoVoto)
{
    return w97_confirma_cargo(estado, eventos, tela + 1, tipoVoto);
}

// stands for fn 1961
__attribute__((noinline)) int DoisConfirmaProporcional(void* estado, void* outro, int tela, int tipoVoto)
{
    return w97_confirma_proporcional(estado, tela, tipoVoto) + w97_confirma_proporcional(outro, tela + 2, tipoVoto);
}

// stands for fn 1285's ten callers
__attribute__((noinline)) int DoisDesligamentos(void* estado, void* outro, int eventos)
{
    return w97_desligamento(estado, eventos) + w97_desligamento(outro, eventos + 3);
}

struct SCVotacaoStateAudioRoots {
    SCVotacaoStateAudioRoots()
    {
        cvotacaostateaudio_sink = cproporcionalbranco_vt;
        cvotacaostateaudio_sink = cproporcionalnulo_vt;
        cvotacaostateaudio_sink = ccandidatoinapto_vt;
        cvotacaostateaudio_sink = ccandidatoinexistente_vt;
        cvotacaostateaudio_sink = cconfirmavotolegenda_vt;
        cvotacaostateaudio_sink = cpedetitulomesarioinicial_vt;
        cvotacaostateaudio_sink = cpedetitulomesariofinal_vt;
        cvotacaostateaudio_sink = cpedetitulomesariovotacao_vt;
        cvotacaostateaudio_sink = cerrotestetecladofim_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&w10245_root_0);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&EstadoAudio);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfirmaEmCargo);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisConfirmaProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisDesligamentos);
    }
} cvotacaostateaudio_roots;

} // namespace
