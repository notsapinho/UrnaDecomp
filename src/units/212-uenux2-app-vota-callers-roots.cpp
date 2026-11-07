// Roots: give the members fragment 212 adds to units 88, 110 and 119 the call sites the target gives them, while
// their callers are not written.
//
// vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550) has two direct callers in the target, FormatPartyName (fn
// 6954) and fn 11683 (vota::CPedeMajoritario::ProcessInputAudio), both written: no stand-in.
//
// comum::md::CCargo::TemFoto (fn 1546) has six direct callers in the target, fns 1192, 4185, 6569, 6660, 6671 and
// 6678, and CCargo::QtdSuplentes (fn 1157) seven, fns 1588, 6569, 6660, 6671, 6678, 7787 and 12272, none written but
// 1192, 4185, 6569, 6678, 1588 and 12272 (units 110's and 378's; those with records are
// app/vota/eleitor/comum/ctelasvota.cpp's). DetalheCargo stands for the others with two calls of each.
//
// vota::MensagemErroCargo (fn 690) has thirteen direct callers in the target, all of ctelasvota.cpp: fns 3064, 6602,
// 6603, 6605, 6608, 6624, 6641, 6646, 6652, 6660, 6671, 6678 and 7787, of which 3064, 6608, 6624, 6646 and 6678 are
// written and in the link (src/units/378-uenux2-ctelasvota-criatela.mk). MensagensCargo stands for the others with two
// calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The results returned through a pointer are left as they are, as nothing calls these.
extern "C" {
int w212_tem_foto(const void* cargo) __asm__("_ZNK5comum2md6CCargo7TemFotoEv");
int w212_suplentes(const void* cargo) __asm__("_ZNK5comum2md6CCargo12QtdSuplentesEv");
void w212_mensagem_cargo(void* mensagem, const void* tela, const void* cargo, const void* erro) __asm__(
    "_ZN4vota17MensagemErroCargoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKN5comum2md6CCargoES8_");
}

namespace {

const void* volatile app_vota_callers_sink;

// stands for fns 6660, 6671 (TemFoto) and 6660, 6671, 7787 (QtdSuplentes); 1192, 4185, 6569, 6678, 1588 and 12272
// are in the link
__attribute__((noinline)) int DetalheCargo(const void* cargo, const void* outro)
{
    return w212_tem_foto(cargo) * 7 + w212_tem_foto(outro) + w212_suplentes(cargo) - w212_suplentes(outro) * 3;
}

// stands for fns 6602, 6603, 6605, 6641, 6652, 6660, 6671 and 7787 (3064, 6608, 6624, 6646 and 6678 are in the
// link)
__attribute__((noinline)) int MensagensCargo(const void* tela, const void* cargo, const void* erro)
{
    char mensagem[12];
    char outra[12];
    w212_mensagem_cargo(mensagem, tela, cargo, erro);
    w212_mensagem_cargo(outra, erro, cargo, tela);
    return mensagem[11] + outra[11] * 5;
}

struct SAppVotaCallersRoots {
    SAppVotaCallersRoots()
    {
        app_vota_callers_sink = reinterpret_cast<const void*>(&DetalheCargo);
        app_vota_callers_sink = reinterpret_cast<const void*>(&MensagensCargo);
    }
} app_vota_callers_roots;

} // namespace
