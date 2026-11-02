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
// functions: fn 11744 (CPedeNulo::GetProximoEstado) builds the instances over CCandidatoInapto and CProporcionalNulo,
// fn 11724 (CPedeNominal::GetProximoEstado) those over CConfirmaVotoLegenda, CCandidatoInexistente, CCandidatoInapto and
// CConfirmaVotoNominal (both written, in cpedenulo.cpp and cpedenominal.cpp, which instantiate those six), fn 11711
// (CPedeProporcional::ProcessInputAudio) the one over CProporcionalBranco, and fn 11683
// (CPedeMajoritario::ProcessInputAudio) the four over the CMajoritario* states (the vptrs each stores). The last two are
// not reconstructed: ConfereProporcional and ConfereMajoritario stand for them and call those GetInst as they do; this
// object then instantiates the class template for their five instances, their vtables, slots and statics, as unit
// 79's roots instantiate their class templates, and they come from here until those callers land. Their stores of the
// vptrs keep the vtables, with the D0 (fn 1278) and slot 16 (the thunks into fns 1961 and 2901) in them, and their
// calls give IConfereVotoEmCargo's constructor (fn 1165), whose four callers are those functions, its call sites. So
// this file includes the unit's headers, and is compiled with UENUX2_CXXFLAGS, the tree's flags, so that no match of
// that code rests on a flag the tree lacks. app/vota/'s own objects drop -fno-strict-aliasing (src/Makefile
// UENUX2_TBAA_DIRS); compiled without it too, this object is the same, byte for byte.
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
// CConfereVotoEmCargo instances, which this file's stand-ins bring into the link. CCompletaProporcional's
// (fn 5932) has one, fn 11711, pending: DoisCompletaProporcional stands for it with two calls. The two GetInst (fns
// 3849 and 5921, thunks into fn 6051) have their slot 16 callers written (fns 11751 and 11699) and fn 4459, which calls
// both; CPedeProporcional's other caller, 11756, is not: PedeProporcional stands for it. Of
// CEstadoComDesligamentoAutomatico's (fn 1285) ten callers
// 2888, 3877, 5947 and 5948 are in the link: DoisDesligamentos stands for the other six (3855, 5936, 11804, 11809,
// 11812, 12051) with two calls. Each stand-in passes what the target's callers vary (the events, the two stored
// arguments) as a variable, so binaryen folds none of them, and adds a constant somewhere, so no two are alike.
//
// GetTelaCargoAtual of vota::CPedeMajoritario, CPedeProporcional, CConfirmaVotoEmCargo and CCompletaProporcional (fns
// 5920, 5923, 5928 and 5931) has two direct callers in the target each, the class's StartStateAudio (written) and its
// ProcessInputAudio (fns 11683, 11711, 11754 and 11756, pending): with StartStateAudio alone binaryen inlines it, and
// the members do not form the shared bodies fns 6050 and 3921. TelaMajoritario, TelaProporcional, TelaEmCargo and
// TelaCompleta stand for the four ProcessInputAudio. The forms they return are left as they are, as nothing calls
// these.
//
// The rest is declared through asm labels (a constructor returns `this` before binaryen runs).
#include <cstdint>

#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariobranco.h"
#include "app/vota/eleitor/votamajoritario/cmajoritarionulo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariorepetido.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"
#include "app/vota/eleitor/votaproporcional/cproporcionalbranco.h"

extern "C" {
extern const char cpedetitulomesarioinicial_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioInicialE");
extern const char cpedetitulomesariofinal_vt[] __asm__("_ZTVN5comum23CPedeTituloMesarioFinalE");
extern const char cpedetitulomesariovotacao_vt[] __asm__("_ZTVN5comum25CPedeTituloMesarioVotacaoE");
extern const char cerrotestetecladofim_vt[] __asm__("_ZTVN4vota12testeteclado20CErroTesteTecladoFimE");
int w97_completa_proporcional(void*, int) __asm__("_ZN4vota21CCompletaProporcionalC2Eh");
int w97_pede_proporcional() __asm__("_ZN4vota17CPedeProporcional7GetInstEv");
extern const char cpedenulo_vt[] __asm__("_ZTVN4vota9CPedeNuloE");
extern const char cpedenominal_vt[] __asm__("_ZTVN4vota12CPedeNominalE");
int w97_desligamento(void*, int) __asm__("_ZN4vota32CEstadoComDesligamentoAutomaticoC2Ei");
void w97_tela_majoritario(void* tela, void* estado) __asm__("_ZN4vota16CPedeMajoritario17GetTelaCargoAtualEv");
void w97_tela_proporcional(void* tela, void* estado) __asm__("_ZN4vota17CPedeProporcional17GetTelaCargoAtualEv");
void w97_tela_em_cargo(void* tela, void* estado, const void* chamador) __asm__(
    "_ZN4vota20CConfirmaVotoEmCargo17GetTelaCargoAtualERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w97_tela_completa(void* tela, void* estado, const void* chamador) __asm__(
    "_ZN4vota21CCompletaProporcional17GetTelaCargoAtualERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

const void* volatile cvotacaostateaudio_sink;

// stands for fn 11711
__attribute__((noinline)) int DoisCompletaProporcional(void* estado, void* outro, int tela)
{
    return w97_completa_proporcional(estado, tela) + w97_completa_proporcional(outro, tela + 5);
}

// stands for fn 11756
__attribute__((noinline)) int PedeProporcional()
{
    return w97_pede_proporcional() + 6;
}

template <typename ESTADO, int TELA>
using Confere = vota::CConfereVotoEmCargo<ESTADO, static_cast<vota::ETelaVotacao>(TELA)>;

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

// stands for fn 11683
__attribute__((noinline)) int TelaMajoritario(void* estado)
{
    char tela[8];
    w97_tela_majoritario(tela, estado);
    return tela[1] + 11;
}

// stands for fn 11711
__attribute__((noinline)) int TelaProporcional(void* estado)
{
    char tela[8];
    w97_tela_proporcional(tela, estado);
    return tela[2] + 12;
}

// stands for fn 11754
__attribute__((noinline)) int TelaEmCargo(void* estado, const void* chamador)
{
    char tela[8];
    w97_tela_em_cargo(tela, estado, chamador);
    return tela[3] + 13;
}

// stands for fn 11756
__attribute__((noinline)) int TelaCompleta(void* estado, const void* chamador)
{
    char tela[8];
    w97_tela_completa(tela, estado, chamador);
    return tela[5] + 14;
}

struct SCVotacaoStateAudioRoots {
    SCVotacaoStateAudioRoots()
    {
        cvotacaostateaudio_sink = cpedetitulomesarioinicial_vt;
        cvotacaostateaudio_sink = cpedetitulomesariofinal_vt;
        cvotacaostateaudio_sink = cpedetitulomesariovotacao_vt;
        cvotacaostateaudio_sink = cerrotestetecladofim_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisCompletaProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&PedeProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&ConfereMajoritario);
        cvotacaostateaudio_sink = cpedenulo_vt;
        cvotacaostateaudio_sink = cpedenominal_vt;
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&DoisDesligamentos);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&TelaMajoritario);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&TelaProporcional);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&TelaEmCargo);
        cvotacaostateaudio_sink = reinterpret_cast<const void*>(&TelaCompleta);
    }
} cvotacaostateaudio_roots;

} // namespace
