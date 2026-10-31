// Roots: keep unit 97's classes in the skeleton link the way the target keeps them.
//
// vota::CPedeNulo's and CPedeNominal's slot 15 (target fns 11745, 11725), the three comum::CPedeTituloMesario* states'
// D0 (3609) and vota::testeteclado::CErroTesteTecladoFim's StartState and destructors (3857, 785, 1560) are reached only
// through their vtables, each referenced in the target by a constructor inlined into a builder not reconstructed (fn
// 10388 for the CPedeTituloMesario* states). Taking the vtables' address keeps every slot. None of those direct callers
// of the destructors is stood in for: the destructors are in the table, so binaryen keeps them out of line. The ten
// confirmation states' vtables are referenced by their constructors, inlined into their GetInst, which slot 16 of the
// CConfereVotoEmCargo instances calls.
//
// The ten vota::CConfereVotoEmCargo<ESTADO, TELA> instances are built in the target by their GetInst, inlined into four
// functions not reconstructed: fn 11744 (CPedeNulo::GetProximoEstado) builds the instances over CCandidatoInapto and
// CProporcionalNulo, fn 11724 (CPedeNominal::GetProximoEstado) those over CConfirmaVotoLegenda, CCandidatoInexistente,
// CCandidatoInapto and CConfirmaVotoNominal, fn 11711 (CPedeProporcional::ProcessInputAudio) the one over
// CProporcionalBranco, and fn 11683 (CPedeMajoritario::ProcessInputAudio) the four over the CMajoritario* states (the
// vptrs each stores). ConfereNulo, ConfereNominal, ConfereProporcional and ConfereMajoritario stand for them and call
// those GetInst as they do; this object then instantiates the class template, its vtables, slots and statics, as unit
// 79's roots instantiate their class templates, and they come from here until those callers land. Their stores of the
// vptrs keep the vtables, with the D0 (fn 1278) and slot 16 (the thunks into fns 1961 and 2901) in them, and their
// calls give IConfereVotoEmCargo's constructor (fn 1165), whose four callers are those functions, its call sites. So
// this file includes the unit's headers, and is compiled with UENUX2_CXXFLAGS, the tree's flags, so that no match of
// that code rests on a flag the tree lacks.
//
// api::CPosixRWMutex's constructor (target fn 10245) is reached only by its table slot 244, which fn 10864 passes to fn
// 6023, so its own address is taken; its vptr store keeps that class's vtable, and with it slots 0 to 4.
//
// The constructors, with direct callers in the target that are not reconstructed: CVotacaoStateAudio's (fn 1785) has
// six, of which fns 5929, 5932, 6051's two (GetInst of vota::CPedeProporcional and CPedeMajoritario, binaryen's
// merge) and 1165 are written, so EstadoAudio stands for the other two (4420, 4459). CConfirmaVotoEmCargo's (fn 5929)
// has two, fns 11752 and 11700, both written. CConfirmaProporcional's (fn 11752) has one, fn 1961, the body binaryen
// shares for six singletons' builders, and CConfirmaMajoritario's (fn 11700) fn 2901, the same for four: the ten
// GetInst those bodies hold are written and call them, so no stand-in is needed there. Their callers are slot 16 of the
// CConfereVotoEmCargo instances, which this file's stand-ins bring into the link. CCompletaProporcional's
// (fn 5932) has one, fn 11711, pending: DoisCompletaProporcional stands for it with two calls. The two GetInst (fns
// 3849 and 5921, thunks into fn 6051) have their slot 16 callers written (fns 11751 and 11699) and 4459, 11756 not:
// PedeProporcional and PedeMajoritario stand for those. None of CEstadoComDesligamentoAutomatico's (fn 1285) ten
// callers is written (2888, 3855, 3877, 5936, 5947, 5948, 11804, 11809, 11812, 12051): DoisDesligamentos stands for
// them with two calls. Each stand-in passes what the target's callers vary (the events, the two stored arguments) as a
// variable, so binaryen folds none of them, and adds a constant somewhere, so no two are alike.
//
// The rest is declared through asm labels (a constructor returns `this` before binaryen runs).
#include <cstdint>

#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariobranco.h"
#include "app/vota/eleitor/votamajoritario/cmajoritarionulo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariorepetido.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"
#include "app/vota/eleitor/votaproporcional/ccandidatoinapto.h"
#include "app/vota/eleitor/votaproporcional/ccandidatoinexistente.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotolegenda.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"
#include "app/vota/eleitor/votaproporcional/cproporcionalbranco.h"
#include "app/vota/eleitor/votaproporcional/cproporcionalnulo.h"

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

template <typename ESTADO, int TELA>
using Confere = vota::CConfereVotoEmCargo<ESTADO, static_cast<vota::ETelaVotacao>(TELA)>;

// stands for fn 11744
__attribute__((noinline)) std::uintptr_t ConfereNulo(int qual)
{
    if (qual == 1) {
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CCandidatoInapto, 14>::GetInst());
    }
    return reinterpret_cast<std::uintptr_t>(&Confere<vota::CProporcionalNulo, 7>::GetInst());
}

// stands for fn 11724
__attribute__((noinline)) std::uintptr_t ConfereNominal(int qual)
{
    switch (qual) {
    case 2:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CConfirmaVotoLegenda, 10>::GetInst());
    case 3:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CCandidatoInexistente, 12>::GetInst());
    case 4:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CCandidatoInapto, 14>::GetInst());
    default:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CConfirmaVotoNominal, 2>::GetInst());
    }
}

// stands for fn 11711
__attribute__((noinline)) std::uintptr_t ConfereProporcional()
{
    return reinterpret_cast<std::uintptr_t>(&Confere<vota::CProporcionalBranco, 4>::GetInst()) + 9;
}

// stands for fn 11683
__attribute__((noinline)) std::uintptr_t ConfereMajoritario(int qual)
{
    switch (qual) {
    case 5:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CMajoritarioBranco, 4>::GetInst());
    case 6:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CMajoritarioNulo, 7>::GetInst());
    case 7:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CMajoritarioRepetido, 16>::GetInst());
    default:
        return reinterpret_cast<std::uintptr_t>(&Confere<vota::CMajoritarioValido, 2>::GetInst());
    }
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
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereNulo);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereNominal);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereMajoritario);
        cvotacaostateaudio_sink = cpedenulo_vt;
        cvotacaostateaudio_sink = cpedenominal_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisDesligamentos);
    }
} cvotacaostateaudio_roots;

} // namespace
