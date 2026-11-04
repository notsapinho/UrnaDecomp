#pragma once

#include <atomic>
#include <string>

// vota::CSincronizaVota: the copies of the voting application's files between the internal and the external flash, and
// the check that the urna is not shutting down. Its records name only static members (VerificaUrnaDesligando and
// SincronizaRelatorios, csincronizavota.cpp 47 and 392), so the class holds static members only, as api::CSystem does,
// and the members no record names join it: that they are members, their names and this header's path are chosen.
// Only what a written function needs is declared.

namespace vota {

class CSincronizaVota {
public:
    // Target fn 3336, the one store of s_urnaDesligando (it stores 1); its callers are vota::CThreadVota's two TrataErro
    // (fns 7709, 7710) and CThreadMonitor::Run (fn 10226). No record names it: its name, its being a member (it sets
    // the class's flag, and the class's records name only static members) and its place in csincronizavota.cpp, ahead
    // of VerificaUrnaDesligando, are chosen.
    static void MarcaUrnaDesligando();
    static void VerificaUrnaDesligando();
    static void SincronizaRelatorios(const std::string& arquivo);

    // Target fns 4687, 4682, 4668, 4662 and 4657 (no record, no string that names them): names chosen from what each
    // does.
    static void SincronizaAssinaturaVota();
    static void GravaBancoDadosMV();
    static void AssinaRDVEBancoDados();
    static void SincronizaBancoDados();
    static void GravaBancoDadosMI();
    // Target fn 491 (no record): saves the voting application's state to both flashes under two contexts. Its name is
    // chosen from the context's text ("Gravando o estado da urna", "... sincronização do estado geral do VOTA.").
    static void SincronizaEstadoGeralVota();
    // Target fn 3333 (no record): saves the urna's general state (comum::CAppInfo's, through comum::CServicoEstadoGeral)
    // to the internal flash, signs file 25 and syncs, then to the external one and copies package 120 to 121, under two
    // contexts, after the check of VerificaUrnaDesligando. Its name is chosen from the context's texts ("Gravando o
    // estado geral da urna na MI", "... na MV"); its place after SincronizaEstadoGeralVota is chosen.
    static void SincronizaEstadoGeral();
    // No target index: binaryen inlined it into SincronizaRelatorios (fn 1836), its one caller, behind a stack frame of
    // its own. Name chosen from what it does.
    static void SincronizaAssinaturaRelatorio(const std::string& arquivo);

    // The byte at 1832936 that VerificaUrnaDesligando tests: 14 target functions read it (`== 1`, `& 1` or a bare test)
    // and fn 3336, its one store, sets it to 1. That it is a bool is a choice that fits every read (no reader compares it
    // with another value). Its name, its owner and that it is public are chosen. Its place in .bss, just before
    // vota::CAguardaMensagem's statics (app/vota/eleitor/), fits an object of app/vota/comum/.
    // Not a plain bool: vota::CImprimirBUOutrasObrigatorias::StartState (fn 12065) tests it first in a loop whose guard
    // and back edge test only the BU count, and clang hoists a plain bool's load (a safe load) into both. Measured in
    // the whole link with `pnpm wasm score`: with a plain bool 107 over 788 rows (the flag tested on the guard and the
    // back edge); with std::atomic<bool> or volatile bool 96 over 779 (the back edge the target's; the guard's block
    // nesting is not), the two giving the same module. Of the 585 objects the header edit rebuilds, volatile bool
    // changes fn 12065's alone (the readers 12077, 12078 and 12081, matched, compile byte-identical), and
    // std::atomic<bool> csincronizavota.cpp.o as well, which links to volatile bool's module, so its 3336 and
    // VerificaUrnaDesligando keep their code. std::atomic<bool> over volatile bool is a choice.
    static std::atomic<bool> s_urnaDesligando;
};

} // namespace vota
