// Roots: keep unit 97's classes in the skeleton link the way the target keeps them.
//
// The three comum::CPedeTituloMesario* states' D0 (3609) and vota::testeteclado::CErroTesteTecladoFim's StartState and
// destructors (3857, 785, 1560) are reached only through their vtables, each referenced in the target by a constructor
// inlined into a builder not reconstructed (fn 10388 for the CPedeTituloMesario* states). Taking the vtables' address
// keeps every slot. None of those direct callers of the destructors is stood in for: the destructors are in the table,
// so binaryen keeps them out of line. The ten confirmation states' vtables are referenced by their constructors, inlined
// into their GetInst, which slot 16 of the CConfereVotoEmCargo instances calls, and vota::CPedeNulo's and CPedeNominal's
// by theirs, inlined into their GetInst, inlined into fn 11711 (written).
//
// The ten vota::CConfereVotoEmCargo<ESTADO, TELA> instances are built in the target by their GetInst, inlined into four
// functions, all written: fn 11744 (CPedeNulo::GetProximoEstado), fn 11724 (CPedeNominal::GetProximoEstado), fn 11711
// (CPedeProporcional::ProcessInputAudio) and fn 11683 (CPedeMajoritario::ProcessInputAudio), whose objects instantiate
// the class template for the instances they build. Their calls give IConfereVotoEmCargo's constructor (fn 1165), whose
// four callers they are, its call sites.
//
// api::CPosixRWMutex's constructor (target fn 10245) is reached only by its table slot 244, which fn 10864 passes to fn
// 6023: fn 10864 is the executable TU's CDefaultGenericFactory<IRWSyncCtl, CPosixRWMutex> (unit 170), in the link, so
// the constructor needs no line here.
//
// The constructors, with direct callers in the target that are not reconstructed: CVotacaoStateAudio's (fn 1785) has
// six, fns 5929, 5932, 6051's two (GetInst of vota::CPedeProporcional and CPedeMajoritario, binaryen's merge), 1165,
// 4420 and 4459, all written, so it needs no stand-in. CConfirmaVotoEmCargo's (fn 5929)
// has two, fns 11752 and 11700, both written. CConfirmaProporcional's (fn 11752) has one, fn 1961, the body binaryen
// shares for six singletons' builders, and CConfirmaMajoritario's (fn 11700) fn 2901, the same for four: the ten
// GetInst those bodies hold are written and call them, so no stand-in is needed there. Their callers are slot 16 of the
// CConfereVotoEmCargo instances, which their builders bring into the link. CCompletaProporcional's
// (fn 5932) has one, fn 11711, which calls it twice (vota::CPedeNulo's and CPedeNominal's GetInst, inlined there), and
// the two GetInst (fns 3849 and 5921, thunks into fn 6051) have their slot 16 callers (fns 11751 and 11699), fn 4459 and
// CPedeProporcional's fn 11756, all written. Of
// CEstadoComDesligamentoAutomatico's (fn 1285) ten callers
// 2888, 3855, 3877, 5936, 5947, 5948 and 12051 are in the link: DoisDesligamentos stands for the other three (11804,
// 11809, 11812) with two calls. Each stand-in passes what the target's callers vary (the events, the two stored
// arguments) as a variable, so binaryen folds none of them, and adds a constant somewhere, so no two are alike.
//
// vota::LegendaValida (target fn 5922) has two callers in the target: fn 11711, written, and fn 5500, the executable
// TU's state reader, not written, which calls it in a try through invoke_iii, by its table slot (90). Its address is
// taken here, as the target's table holds it, and it stays out of line with its one call.
//
// comum::md::CCargo::GetDetalheConsulta (target fn 1923, a thunk into binaryen's merge 6029, whose other member is
// comum::md::CLocal::GetContingencia, fn 3724) has six direct callers in the target: fns 3074, 3819, 5604, 6999, 7787 and
// 11253. 6999 and 5604 are written; unit 232's roots stand for the other four (DetalhesConsulta, two calls).
//
// Everything is declared through asm labels (a constructor returns `this` before binaryen runs), so this TU includes no
// header and instantiates nothing.
extern "C" {
extern const char cpedetitulomesarioinicial_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioInicialE");
extern const char cpedetitulomesariofinal_vt[] __asm__("_ZTVN5comum23CPedeTituloMesarioFinalE");
extern const char cpedetitulomesariovotacao_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioVotacaoE");
extern const char cerrotestetecladofim_vt[] __asm__("_ZTVN4vota12testeteclado20CErroTesteTecladoFimE");
int w97_desligamento(void*, int) __asm__("_ZN4vota32CEstadoComDesligamentoAutomaticoC2Ei");
int w97_legenda_valida(int, int) __asm__("_ZN4vota13LegendaValidaEht");
}

namespace {

const void* volatile cvotacaostateaudio_sink;

// stands for fn 1285's ten callers
__attribute__((noinline)) int DoisDesligamentos(void* estado, void* outro, int eventos)
{
    return w97_desligamento(estado, eventos) + w97_desligamento(outro, eventos + 3);
}

struct SCVotacaoStateAudioRoots {
    SCVotacaoStateAudioRoots()
    {
        cvotacaostateaudio_sink = cpedetitulomesarioinicial_vt;
        cvotacaostateaudio_sink = cpedetitulomesariofinal_vt;
        cvotacaostateaudio_sink = cpedetitulomesariovotacao_vt;
        cvotacaostateaudio_sink = cerrotestetecladofim_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisDesligamentos);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&w97_legenda_valida);
    }
} cvotacaostateaudio_roots;

} // namespace
