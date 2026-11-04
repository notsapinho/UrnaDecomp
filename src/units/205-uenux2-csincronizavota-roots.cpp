// Roots: reach fragment 205's functions the way the target does. Each is called directly in the target; the callers
// the link holds are counted (SincronizaBancoDados calls VerificaUrnaDesligando, inlined, and GravaBancoDadosMI, which
// calls GravaBancoDadosMV), and these stand-ins, each with a body of its own (no two of one shape, so that binaryen
// merges none), stand for the rest, none of which is written:
// - fn 1685 (api::CUeDesligandoError's constructor) is called by the throw of VerificaUrnaDesligando, which clang inlines
//   into each of its seven target callers (491, 1836, 3333, 4662, 6737, 7174, 10590); 4662 is SincronizaBancoDados,
//   1836 SincronizaRelatorios, 491 SincronizaEstadoGeralVota, 3333 SincronizaEstadoGeral and 10590
//   vota::CPedeAnoNascimento::ProcessInput (unit 283, through SincronizaJustificativa), in the link, so every call
//   passes the location of csincronizavota.cpp 47:15 and dead-argument elimination folds it as in the target;
// - SincronizaAssinaturaVota (fn 4687) and GravaBancoDadosMI (fn 4657) need no stand-in: their target callers, 491 and
//   10590, and 4662 and 10590, are in the link;
// - GravaBancoDadosMV (fn 4682): callers 4657 (written) and 7174;
// - SincronizaBancoDados (fn 4662): callers 7787 and 10786 (unit 119's trap for CControladorRegistraMesariosVota's slot
//   16);
// - AssinaRDVEBancoDados (fn 4668): caller 6737, which calls it twice;
// - SincronizaRelatorios (fn 1836): callers 11943, 11946, 12105 (three times) and 12110, the slot 2 of four vota states.
// - SincronizaEstadoGeralVota (fn 491): 31 callers, of which 20 are in the link: 5972, 10710, 10734, 10797, 11830,
//   11855, 11902, 11905, 11911, 11920, 11924, 11927, 11931, 11940, 11991, 12031, 12034, 12065, 12077 and 12081.
// - SincronizaEstadoGeral (fn 3333): callers 7160, 7306 and 10710 (unit 277, in the link).
// - MarcaUrnaDesligando (fn 3336): callers 7709 and 7710 (vota::CThreadVota's two TrataErro), traps in unit 116's
//   pending file, and 10226 (CThreadMonitor::Run, unit 116's, matched).
#include "app/vota/comum/csincronizavota.h"

namespace {

// stands for fn 7174, GravaBancoDadosMV's other target caller (4657 is in the link); its calls of
// SincronizaAssinaturaVota and GravaBancoDadosMI went with 10590 in the link
__attribute__((noinline)) int w205_banco(int passo)
{
    vota::CSincronizaVota::GravaBancoDadosMV();
    return passo + 3;
}

// stands for fns 7787 and 10786
__attribute__((noinline)) int w205_sincroniza(int vezes)
{
    vota::CSincronizaVota::SincronizaBancoDados();
    if (vezes > 1) {
        vota::CSincronizaVota::SincronizaBancoDados();
    }
    return vezes - 1;
}

// stands for fn 6737
__attribute__((noinline)) int w205_assina(int base)
{
    vota::CSincronizaVota::AssinaRDVEBancoDados();
    vota::CSincronizaVota::AssinaRDVEBancoDados();
    return base * 3;
}

// stands for fns 11943, 11946, 12105 and 12110, which pass the report they wrote
__attribute__((noinline)) void w205_relatorios(const std::string& relatorio, const std::string& outro)
{
    vota::CSincronizaVota::SincronizaRelatorios(relatorio);
    vota::CSincronizaVota::SincronizaRelatorios(outro);
}

// stands for fns 7709 and 7710 (10226 is in the link)
__attribute__((noinline)) int w205_desligando(int passo)
{
    vota::CSincronizaVota::MarcaUrnaDesligando();
    vota::CSincronizaVota::MarcaUrnaDesligando();
    return passo + 5;
}

// stands for SincronizaEstadoGeralVota's (fn 491's) 11 target callers that are not in the link (the list above names
// the 20 that are)
__attribute__((noinline)) int w205_estado(int vezes)
{
    vota::CSincronizaVota::SincronizaEstadoGeralVota();
    vota::CSincronizaVota::SincronizaEstadoGeralVota();
    return vezes * 7;
}

// stands for fns 7160 and 7306, SincronizaEstadoGeral's (fn 3333's) target callers that are not in the link (10710,
// the third, is: unit 277)
__attribute__((noinline)) int w205_estado_geral(int passo)
{
    vota::CSincronizaVota::SincronizaEstadoGeral();
    return passo + 11;
}

const void* volatile w205_sink;

struct SW205Roots {
    SW205Roots()
    {
        w205_sink = reinterpret_cast<const void*>(&w205_banco);
        w205_sink = reinterpret_cast<const void*>(&w205_sincroniza);
        w205_sink = reinterpret_cast<const void*>(&w205_assina);
        w205_sink = reinterpret_cast<const void*>(&w205_relatorios);
        w205_sink = reinterpret_cast<const void*>(&w205_desligando);
        w205_sink = reinterpret_cast<const void*>(&w205_estado);
        w205_sink = reinterpret_cast<const void*>(&w205_estado_geral);
    }
} w205_roots;

} // namespace
