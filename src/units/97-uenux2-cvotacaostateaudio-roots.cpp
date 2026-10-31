// Roots: keep unit 97's classes in the skeleton link the way the target keeps them.
//
// vota::CPedeNulo's and CPedeNominal's slot 15 (target fns 11745, 11725), the three comum::CPedeTituloMesario* states'
// D0 (3609) and vota::testeteclado::CErroTesteTecladoFim's StartState and destructors (3857, 785, 1560) are reached only
// through their vtables, each referenced in the target by a constructor inlined into a builder not reconstructed (fn
// 10388 for the CPedeTituloMesario* states). Taking the vtables' address keeps every slot. None of those direct callers
// of the destructors is stood in for: the destructors are in the table, so binaryen keeps them out of line. The ten
// confirmation states' vtables are referenced by their constructors, inlined into their GetInst.
// vota::IConfereVotoEmCargo's vtable, with its in-class destructor (fn 1717) and slots 11 and 15 (fns 11792, 11789), is
// referenced in the target by its constructor (fn 1165, not reconstructed) and by that destructor; its address is taken.
//
// api::CPosixRWMutex's constructor (target fn 10245) is reached only by its table slot 244, which fn 10864 passes to fn
// 6023, so its own address is taken; its vptr store keeps that class's vtable, and with it slots 0 to 4.
//
// The constructors, with direct callers in the target that are not reconstructed: CVotacaoStateAudio's (fn 1785) has
// six, of which fns 5929, 5932 and 6051's two (GetInst of vota::CPedeProporcional and CPedeMajoritario, binaryen's
// merge) are written, so EstadoAudio stands for the other three (1165, 4420, 4459). CConfirmaVotoEmCargo's (fn 5929)
// has two, fns 11752 and 11700, both written. CConfirmaProporcional's (fn 11752) has one, fn 1961, the body binaryen
// shares for six singletons' builders, and CConfirmaMajoritario's (fn 11700) fn 2901, the same for four: the ten
// GetInst those bodies hold are written and call them, so no stand-in is needed there. Their callers, the slot-16
// thunks of the CConfereVotoEmCargo instances, are not written: DezSingletons stands for them. CCompletaProporcional's
// (fn 5932) has one, fn 11711, pending: DoisCompletaProporcional stands for it with two calls. The two GetInst (fns
// 3849 and 5921, thunks into fn 6051) have their slot 16 callers written (fns 11751 and 11699) and 4459, 11756 not:
// PedeProporcional and PedeMajoritario stand for those. None of CEstadoComDesligamentoAutomatico's (fn 1285) ten
// callers is written (2888, 3855, 3877, 5936, 5947, 5948, 11804, 11809, 11812, 12051): DoisDesligamentos stands for
// them with two calls. Each stand-in passes what the target's callers vary (the events, the two stored arguments) as a
// variable, so binaryen folds none of them, and adds a constant somewhere, so no two are alike.
//
// Declared through asm labels (a constructor returns `this` before binaryen runs), so this TU needs no uenux2 header
// and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cpedetitulomesarioinicial_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioInicialE");
extern const char cpedetitulomesariofinal_vt[] __asm__("_ZTVN5comum23CPedeTituloMesarioFinalE");
extern const char cpedetitulomesariovotacao_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioVotacaoE");
extern const char cerrotestetecladofim_vt[] __asm__("_ZTVN4vota12testeteclado20CErroTesteTecladoFimE");
int w10245_root_0(int) __asm__("_ZN3api13CPosixRWMutexC2Ev");
int w97_estado_audio(void*, int) __asm__("_ZN4vota18CVotacaoStateAudioC2Ei");
int w97_completa_proporcional(void*, int) __asm__("_ZN4vota21CCompletaProporcionalC2Eh");
int w97_pede_proporcional() __asm__("_ZN4vota17CPedeProporcional7GetInstEv");
int w97_pede_majoritario() __asm__("_ZN4vota16CPedeMajoritario7GetInstEv");
int w97_inst_0() __asm__("_ZN4vota19CProporcionalBranco7GetInstEv");
int w97_inst_1() __asm__("_ZN4vota20CConfirmaVotoNominal7GetInstEv");
int w97_inst_2() __asm__("_ZN4vota21CCandidatoInexistente7GetInstEv");
int w97_inst_3() __asm__("_ZN4vota20CConfirmaVotoLegenda7GetInstEv");
int w97_inst_4() __asm__("_ZN4vota17CProporcionalNulo7GetInstEv");
int w97_inst_5() __asm__("_ZN4vota16CCandidatoInapto7GetInstEv");
int w97_inst_6() __asm__("_ZN4vota18CMajoritarioValido7GetInstEv");
int w97_inst_7() __asm__("_ZN4vota20CMajoritarioRepetido7GetInstEv");
int w97_inst_8() __asm__("_ZN4vota16CMajoritarioNulo7GetInstEv");
int w97_inst_9() __asm__("_ZN4vota18CMajoritarioBranco7GetInstEv");
extern const char iconferevotoemcargo_vt[] __asm__("_ZTVN4vota19IConfereVotoEmCargoE");
extern const char cpedenulo_vt[] __asm__("_ZTVN4vota9CPedeNuloE");
extern const char cpedenominal_vt[] __asm__("_ZTVN4vota12CPedeNominalE");
int w97_desligamento(void*, int) __asm__("_ZN4vota32CEstadoComDesligamentoAutomaticoC2Ei");
}

namespace {

const void* volatile cvotacaostateaudio_sink;

// stands for fns 1165, 4420 and 4459
__attribute__((noinline)) int EstadoAudio(void* estado, int eventos)
{
    return w97_estado_audio(estado, eventos + 1);
}

// stands for fn 11711
__attribute__((noinline)) int DoisCompletaProporcional(void* estado, void* outro, int tela)
{
    return w97_completa_proporcional(estado, tela) + w97_completa_proporcional(outro, tela + 5);
}

// stands for fns 4459 and 11756
__attribute__((noinline)) int PedeProporcional()
{
    return w97_pede_proporcional() + 6;
}

// stands for fn 4459
__attribute__((noinline)) int PedeMajoritario()
{
    return w97_pede_majoritario() + 7;
}

// stands for the ten slot-16 thunks of the CConfereVotoEmCargo instances (fns 11670 to 11673, 11707, 11715 to 11717,
// 11738 and 11739), each of which holds one GetInst inlined
__attribute__((noinline)) int DezSingletons()
{
    return w97_inst_0() + w97_inst_1() + w97_inst_2() + w97_inst_3()
        + w97_inst_4() + w97_inst_5() + w97_inst_6() + w97_inst_7()
        + w97_inst_8() + w97_inst_9();
}

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
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&w10245_root_0);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&EstadoAudio);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisCompletaProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&PedeProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&PedeMajoritario);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DezSingletons);
        cvotacaostateaudio_sink = iconferevotoemcargo_vt;
        cvotacaostateaudio_sink = cpedenulo_vt;
        cvotacaostateaudio_sink = cpedenominal_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisDesligamentos);
    }
} cvotacaostateaudio_roots;

} // namespace
