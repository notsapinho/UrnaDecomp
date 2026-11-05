// Roots: reach fragment 168's functions the way the target does. Each is called directly in the target, by callers no
// object of the link holds as code (functions not written), and binaryen inlines a function with one call site, so
// stand-ins give each more. Each stand-in's body is its own: no target function holds these calls.
// - comum::CAppStateContext's constructor (target fn 3844; callers 4713, 7061, 10204) has no stand-in: 4713 (unit
//   165's slots 2 and 3, through vota::CThreadVota::IniciaContexto), 10204 (unit 116's CThreadOperador::Run) and 7061
//   (unit 116's CThreadEleitor::Run) are in the link. Nor have ProcessKey (3843), ProcessInput (5911), ProcessTick
//   (5910), AcceptsKey (3842), AcceptsInput (5909) and AcceptsTick (5908): their callers, 4349 and 10204 (unit 116's,
//   4349 written and not matched), are both in the link.
// - vota::EhTreinamento (fn 1485; callers 10425, 10566, 10680, 12098): 10566 (unit 50), 10680 (unit 161) and 10425 (unit
//   142, written, which calls it twice) are in the link; w168_treinamento stands for 12098, not written. w168_tecla,
//   which stood for 10425 (ProcessKey's key its parameter), went.
// - vota::EhTreinamentoMesario (fn 1823; callers 7306, 10465, 10474, 10478, 10500, 10512): its stand-in went, every
//   caller in the link: 10512 (unit 161, written), 10465, 10474 and 10478 (unit 282), 7306 (unit 104) and 10500.
// - vota::AdicionaSeparador (fn 1387; callers 11908 and 11946, written, 12105 and 12110, not written), with the
//   alignments they pass, 0 and 2, so that dead-argument elimination keeps the parameter.
// - api::CPolySingletonList::has<vota::IAjusteInicial> (fn 2450; callers 7061, unit 116's, in the link and calling it
//   three times, and the static initializers in fn 14478, which call it with g_polySingletonsInfo's result and drop
//   what it returns) has no stand-in: the two calls that stood for 14478 went on a link without them that moved no row
//   (unit 168's fragment), and the instance our link keeps is unit 329's cajusteinicial.cpp.o's.
// - vota::VerificaAssinaturaArquivos (fn 4625; one target caller, 7787, not written, which calls it twice):
//   w168_arquivos stands for 7787, with the two directories 7787 passes, comum::CPath::GetPathTrab's (fn 358) of the
//   internal and the external flash, taken as parameters.
#include "app/vota/comum/votadefs.h"

namespace {

__attribute__((noinline)) int w168_treinamento()
{
    return vota::EhTreinamento() ? 23 : 29;
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

// stands for fn 12974, not written, which calls GetQuantidadeMaximaBUsAdicionais (fn 4582) once and reads what it
// returns; its other target caller, vota::CEmitirMaisBU::ProcessInput (fn 12081), is in the link (unit 104)
__attribute__((noinline)) int w168_qtdbu(int base)
{
    return vota::GetQuantidadeMaximaBUsAdicionais() + base;
}

// stands for fn 7787, not written, which calls VerificaAssinaturaArquivos (fn 4625) twice
__attribute__((noinline)) void w168_arquivos(const std::filesystem::path& interno, const std::filesystem::path& externo)
{
    vota::VerificaAssinaturaArquivos(interno);
    vota::VerificaAssinaturaArquivos(externo);
}

const void* volatile w168_sink;

struct SW168Roots {
    SW168Roots()
    {
        w168_sink = reinterpret_cast<const void*>(&w168_treinamento);
        w168_sink = reinterpret_cast<const void*>(&w168_separadores);
        w168_sink = reinterpret_cast<const void*>(&w168_assinaturas);
        w168_sink = reinterpret_cast<const void*>(&w168_qtdbu);
        w168_sink = reinterpret_cast<const void*>(&w168_arquivos);
    }
} w168_roots;

} // namespace
