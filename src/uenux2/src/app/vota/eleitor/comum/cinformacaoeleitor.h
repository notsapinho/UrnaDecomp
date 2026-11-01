#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"

// Reconstruction's note, not TSE's text: static objects of the vota application that no symbol or record names, these
// two and the byte further down.
// - The number the voter typed, a std::string at 1833288. vota::CPedeNulo's and vota::CPedeNominal's GetProximoEstado
//   (fns 11744 and 11724) assign their argument to it, vota::CEleitorVotando::ChamaEstadoProximoCargo (fn 4459) assigns
//   it an empty string, and fns 5500, 6999, 7377, 11683, 11711, 11754 and 11756 read it; fn 13176, at table slot 1098,
//   which the screen builders of ctelasvota.cpp take, returns its address, and fn 13593 destroys it at exit
//   (`/usr/bin/grep -rlE 'i32\.const 1833288($|[^0-9])' build/out/splat/pieces/asm`). __wasm_call_ctors holds no store
//   to it: it is constant-initialized.
// - The time the urn shuts down, an api::CDateTime at 1833312. __wasm_call_ctors builds it with CDate's and CTime's
//   default constructors (fns 1382 and 2230 on 1833312 and 1833320), vota::CEstadoComDesligamentoAutomatico::ProcessTick
//   (fn 12061) sets it to its time limit when that passes, vota::CExibeAlertaDesligamento::StartState (fn 12018) copies
//   it, and fn 13012, at table slot 1102, hands it with the current time to fn 5471 and formats the result.
// Where they are defined is a reading of the data, src/units/197-uenux2-celeitorvotando.mk says which. Chosen: that they
// are objects of namespace vota and not static members of a class, their names, and this header's path.
namespace vota {

extern std::string g_numeroDigitado;

// The assignment of the number typed. vota::CEleitorVotando::ChamaEstadoProximoCargo (fn 4459) and its slot 2 (fn 7377)
// build an empty std::string temporary, copy it in with __assign_no_alias (fn 196) when the object is long, and destroy
// it: a copy into the object from a `const std::string&` bound to a temporary, which an inline function taking one
// gives with the argument "", and `g_numeroDigitado = std::string()` (a move, which frees the old buffer instead),
// `= ""` and `.clear()` (no call) do not (measured in a probe object at the tree's flags). That it is a function, its
// name, and that fns 11744 and 11724 assign through it too are chosen: they gave operand rows only (pnpm wasm score,
// whole link) with the assignment written in place as well.
inline void SetNumeroDigitado(const std::string& numero)
{
    g_numeroDigitado = numero;
}

extern api::CDateTime g_dataHoraDesligamento;

// The choice being voted in the current post, a byte at 1536340 that the data hold as 1. vota::CEleitorVotando's
// NeedChangeState (fn 7352) compares it with the post's +13 (comum::md::CCargo::GetQtdeEscolhas) and sets it back to 1 or
// adds 1 to it, its slot 2 (fn 7377) sets it to 1, and its ProcessTick (fn 7349), CVotacaoStateAudio::FormataMensagem
// (fn 6999) and fns 4442, 4464, 11683, 12587, 12811 and 13550 read it; 4464 and 12811 pass it to
// comum::md::CCargo::GetOrdinalEscolha (fn 2258), whose record names its parameter's type, TQtdEscolha. It lies in the
// data between this file's record (1536276) and comum/cpoliticaexecucaoeleitor.cpp's (1536344). Its name and its type
// are chosen: the readers load and store one byte, and two pass it as a TQtdEscolha.
extern comum::md::TQtdEscolha g_escolhaAtual;

} // namespace vota
