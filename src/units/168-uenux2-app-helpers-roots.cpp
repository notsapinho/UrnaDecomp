// Roots: reach fragment 168's functions the way the target does. Each is called directly in the target, by callers no
// object of the link holds as code (traps or functions not written), and binaryen inlines a function with one call site,
// so two stand-ins call each. Each stand-in's body is its own: no target function holds these calls.
// - comum::CAppStateContext's constructor (target fn 3844; callers 4713, 7061, 10204): 4713 (unit 165's slots 2 and 3,
//   through vota::CThreadVota::IniciaContexto) and 10204 (unit 116's CThreadOperador::Run) are in the link, and the
//   stand-ins construct one for 7061, unit 116's trap. ProcessKey (3843), ProcessInput (5911), ProcessTick (5910),
//   AcceptsKey (3842), AcceptsInput (5909) and AcceptsTick (5908) have no stand-in: their callers, 4349 and 10204
//   (unit 116's, 4349 written and not matched), are both in the link.
// - vota::EhTreinamento (fn 1485; callers 10425, 10566, 10680, 12098): 10566 is in the link (unit 50), the others are
//   not written.
// - vota::AdicionaSeparador (fn 1387; callers 11908, 11946, 12105, 12110, none written), with the two alignments they
//   pass, 0 and 2, so that dead-argument elimination keeps the parameter.
// - api::CPolySingletonList::has<vota::IAjusteInicial> (fn 2450; callers 7061, unit 116's trap, and the static
//   initializers in fn 14478, which call it with g_polySingletonsInfo's result and drop what it returns). The instance
//   is the header's template, emitted here first: no object before this one instantiates it.
#include "api/pattern/cpolysingletonlist.h"
#include "app/comum/cappstatecontext.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/iajusteinicial.h"

namespace {

__attribute__((noinline)) int w168_tecla(comum::CAppState* estado, uebyte tecla)
{
    comum::CAppStateContext contexto(estado);
    return (vota::EhTreinamento() ? 3 : 5) + tecla;
}

__attribute__((noinline)) int w168_ajuste(comum::CAppState* estado)
{
    comum::CAppStateContext contexto(estado);
    const bool ajuste = api::CPolySingletonList::has<vota::IAjusteInicial>();
    return (ajuste ? 17 : 19) + (vota::EhTreinamento() ? 23 : 29) +
           (api::CPolySingletonList::has<vota::IAjusteInicial>() ? 31 : 37);
}

__attribute__((noinline)) void w168_separadores(api::CPaperFormBuilder* builder, api::CPaperFormBuilder* outro)
{
    vota::AdicionaSeparador(*builder, api::ALINHAMENTO_ESQUERDA);
    vota::AdicionaSeparador(*outro, api::ALINHAMENTO_CENTRO);
}

// stands for fn 7174 (vota::impl::CSincronismoVotoEleitor's slot 2, not written), which calls VerificaAssinaturaMI
// (fn 3290) and VerificaAssinaturaMV (fn 3288) three times each
__attribute__((noinline)) void w168_assinaturas(const std::string& arquivo, const std::string& outro)
{
    vota::VerificaAssinaturaMI(arquivo);
    vota::VerificaAssinaturaMV(arquivo);
    vota::VerificaAssinaturaMI(outro);
    vota::VerificaAssinaturaMV(outro);
}

// stand for fns 12081 (vota::CEmitirMaisBU::ProcessInput) and 12974, not written, which call
// GetQuantidadeMaximaBUsAdicionais (fn 4582) once each and read what it returns
__attribute__((noinline)) int w168_qtdbu(int base)
{
    return vota::GetQuantidadeMaximaBUsAdicionais() + base;
}

__attribute__((noinline)) int w168_qtdbu_vezes(int fator)
{
    return vota::GetQuantidadeMaximaBUsAdicionais() * fator;
}

const void* volatile w168_sink;

struct SW168Roots {
    SW168Roots()
    {
        w168_sink = reinterpret_cast<const void*>(&w168_tecla);
        w168_sink = reinterpret_cast<const void*>(&w168_ajuste);
        w168_sink = reinterpret_cast<const void*>(&w168_separadores);
        w168_sink = reinterpret_cast<const void*>(&w168_assinaturas);
        w168_sink = reinterpret_cast<const void*>(&w168_qtdbu);
        w168_sink = reinterpret_cast<const void*>(&w168_qtdbu_vezes);
    }
} w168_roots;

} // namespace
