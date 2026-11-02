// Roots: give the members fragment 212 adds to units 88, 97, 110 and 119 the call sites the target gives them, while
// their callers are not written.
//
// vota::CVotacaoStateAudio::FormatPartyName (fn 6954) has one direct caller in the target, fn 6999 (slot 14 of the
// class, pending in unit 97), which calls it twice: NomesPartidos stands for it with two calls.
//
// vota::CLogVota::LogaErroPartidoNaoEncontrado (fn 4550) has two direct callers in the target, FormatPartyName (fn
// 6954, written) and fn 11683 (vota::CPedeMajoritario, not written): ErroPartido stands for 11683.
//
// comum::md::CCargo::TemFoto (fn 1546) has six direct callers in the target, fns 1192, 4185, 6569, 6660, 6671 and
// 6678, and CCargo::QtdSuplentes (fn 1157) seven, fns 1588, 6569, 6660, 6671, 6678, 7787 and 12272, none written
// (those with records are app/vota/eleitor/comum/ctelasvota.cpp's). DetalheCargo stands for them with two calls of each.
//
// vota::MensagemErroCargo (fn 690) has thirteen direct callers in the target, all of ctelasvota.cpp: fns 3064, 6602,
// 6603, 6605, 6608, 6624, 6641, 6646, 6652, 6660, 6671, 6678 and 7787, none written. MensagensCargo stands for them
// with two calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The results returned through a pointer are left as they are, as nothing calls these.
extern "C" {
void w212_partido(void* nome, void* estado, const void* numero) __asm__(
    "_ZN4vota18CVotacaoStateAudio15FormatPartyNameERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w212_erro_partido(void* log) __asm__("_ZN4vota8CLogVota28LogaErroPartidoNaoEncontradoEv");
int w212_tem_foto(const void* cargo) __asm__("_ZNK5comum2md6CCargo7TemFotoEv");
int w212_suplentes(const void* cargo) __asm__("_ZNK5comum2md6CCargo12QtdSuplentesEv");
void w212_mensagem_cargo(void* mensagem, const void* tela, const void* cargo, const void* erro) __asm__(
    "_ZN4vota17MensagemErroCargoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEERKN5comum2md6CCargoES8_");
}

namespace {

const void* volatile app_vota_callers_sink;

// stands for fn 6999
__attribute__((noinline)) int NomesPartidos(void* estado, const void* numero, const void* outro)
{
    char nome[12];
    char sigla[12];
    w212_partido(nome, estado, numero);
    w212_partido(sigla, estado, outro);
    return nome[11] - sigla[11];
}

// stands for fn 11683
__attribute__((noinline)) void ErroPartido(void* log, int vezes)
{
    if (vezes > 3) {
        w212_erro_partido(log);
    }
}

// stands for fns 1192, 4185, 6569, 6660, 6671, 6678 (TemFoto) and 1588, 6569, 6660, 6671, 6678, 7787, 12272
// (QtdSuplentes)
__attribute__((noinline)) int DetalheCargo(const void* cargo, const void* outro)
{
    return w212_tem_foto(cargo) * 7 + w212_tem_foto(outro) + w212_suplentes(cargo) - w212_suplentes(outro) * 3;
}

// stands for fns 3064, 6602, 6603, 6605, 6608, 6624, 6641, 6646, 6652, 6660, 6671, 6678 and 7787
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
        app_vota_callers_sink = reinterpret_cast<const void*>(&NomesPartidos);
        app_vota_callers_sink = reinterpret_cast<const void*>(&ErroPartido);
        app_vota_callers_sink = reinterpret_cast<const void*>(&DetalheCargo);
        app_vota_callers_sink = reinterpret_cast<const void*>(&MensagensCargo);
    }
} app_vota_callers_roots;

} // namespace
