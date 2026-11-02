#pragma once

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
    // No target index: binaryen inlined it into SincronizaRelatorios (fn 1836), its one caller, behind a stack frame of
    // its own. Name chosen from what it does.
    static void SincronizaAssinaturaRelatorio(const std::string& arquivo);

    // The byte at 1832936 that VerificaUrnaDesligando tests: 14 target functions read it (`== 1`, `& 1` or a bare test)
    // and fn 3336, its one store, sets it to 1. That it is a bool is a choice that fits every read; no reader tests it in
    // a loop, which would tell a bool from a byte (docs/reference/facts/reading.md R14). Its name, its owner and that it
    // is public are chosen. Its place in .bss, just before vota::CAguardaMensagem's statics (app/vota/eleitor/), fits an
    // object of app/vota/comum/.
    static bool s_urnaDesligando;
};

} // namespace vota
