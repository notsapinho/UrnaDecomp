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
}

namespace {

const void* volatile cvotacaostateaudio_sink;

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
    }
} cvotacaostateaudio_roots;

} // namespace
