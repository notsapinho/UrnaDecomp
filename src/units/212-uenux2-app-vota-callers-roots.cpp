// Roots: give the members fragment 212 adds to units 88, 110 and 119 the call sites the target gives them, while
// their callers are not written.
//
// vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550) has two direct callers in the target, FormatPartyName (fn
// 6954) and fn 11683 (vota::CPedeMajoritario::ProcessInputAudio), both written: no stand-in.
//
// comum::md::CCargo::TemFoto (fn 1546) has six direct callers in the target, fns 1192, 4185, 6569, 6660, 6671 and
// 6678, all in the link (6660 and 6671 since unit 441), and its two calls went. CCargo::QtdSuplentes (fn 1157) has seven,
// fns 1588, 6569, 6660, 6671, 6678, 7787 and 12272, all in the link but 7787 (not written); DetalheCargo stands for 7787
// with one call.
//
// vota::MensagemErroCargo (fn 690) has thirteen direct callers in the target, all of ctelasvota.cpp: fns 3064, 6602,
// 6603, 6605, 6608, 6624, 6641, 6646, 6652, 6660, 6671, 6678 and 7787, all in the link but 7787
// (src/units/378-uenux2-ctelasvota-criatela.mk and src/units/441-uenux2-ctelasvota-bases.mk). MensagensCargo stands for
// 7787 with one call.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The results returned through a pointer are left as they are, as nothing calls these.
extern "C" {
int w212_suplentes(const void* cargo) __asm__("_ZNK5comum2md6CCargo12QtdSuplentesEv");
void w212_mensagem_cargo(void* mensagem, const void* tela, const void* cargo, const void* erro) __asm__(
    "_ZN4vota17MensagemErroCargoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKN5comum2md6CCargoES8_");
}

namespace {

const void* volatile app_vota_callers_sink;

// stands for fn 7787 (QtdSuplentes); its other target callers are in the link
__attribute__((noinline)) int DetalheCargo(const void* cargo)
{
    return w212_suplentes(cargo) * 7 + 212;
}

// stands for fn 7787; its other target callers are in the link
__attribute__((noinline)) int MensagensCargo(const void* tela, const void* cargo, const void* erro)
{
    char mensagem[12];
    w212_mensagem_cargo(mensagem, tela, cargo, erro);
    return mensagem[11] * 5;
}

struct SAppVotaCallersRoots {
    SAppVotaCallersRoots()
    {
        app_vota_callers_sink = reinterpret_cast<const void*>(&DetalheCargo);
        app_vota_callers_sink = reinterpret_cast<const void*>(&MensagensCargo);
    }
} app_vota_callers_roots;

} // namespace
