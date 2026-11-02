#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/ccedula.h"
#include "app/comum/dados/md/rdv/cvoto.h"

// Reconstruction's note, not TSE's text: static objects of the vota application that no symbol or record names, these
// two, the votes cast further down (with the function that appends to them) and the byte.
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

// The votes cast in the current cycle, a 12-byte object at 1833300: a vector of 20-byte (post id, vote) pairs, the id a
// byte at +0 and the comum::md::CVoto at +4, which fn 4192 appends to, fn 7377 empties in place, fns 6999, 4454 and
// 11683 read, and fn 13588 (table slot 1079) destroys at exit, freeing each element's string at +8. __wasm_call_ctors
// calls a constructor on it, fn 203's body, which zeroes the 12 bytes. Its type is read as comum::md::CCedula
// (app/comum/dados/md/rdv/ccedula.h), the class the records of fn 4454's inlined callees take: 4454 copies this
// object's elements, one by one, into the vectors of CCedula values that it builds with the same call of fn 203's body,
// keyed by a word it looks up from each pair's post id. The reading rests on those bytes: this object has the class's
// 12 bytes, its constructor call and its elements. Its constructor and Adiciona, which fn 4192 holds behind a stack
// frame of its own, are in ccedula.cpp (src/units/197-uenux2-celeitorvotando.mk has the measurement). g_votosEleitor's
// name is chosen.
extern comum::md::CCedula g_votosEleitor;

// fn 4192: copies the vote in a 16-byte frame and passes it by value to CCedula::Adiciona, held in a second,
// 32-byte frame, which builds the pair there and pushes it. Its callers are vota::CEleitorVotando::RegistraVoto (fn
// 4471) and suspenderEleitor (fn 4442), in celeitorvotando.cpp, which would inline a function this small
// (docs/how-to-decompile.md step 3): so it is in another TU, this one beside the object (a choice). Its name and that it
// is a free function are chosen.
void AdicionaVoto(comum::md::TCargoID cargo, const comum::md::CVoto& voto);

extern api::CDateTime g_dataHoraDesligamento;

// The choice being voted in the current post, a byte at 1536340 that the data hold as 1. vota::CEleitorVotando's
// NeedChangeState (fn 7352) compares it with the post's +13 (comum::md::CCargo::GetQtdeEscolhas) and sets it back to 1 or
// adds 1 to it, its slot 2 (fn 7377) sets it to 1, and its ProcessTick (fn 7349), CVotacaoStateAudio::FormataMensagem
// (fn 6999) and fns 4442, 4464, 11683, 12587, 12811 and 13550 read it; 4464 and 12811 pass it to
// comum::md::CCargo::GetOrdinalEscolha (fn 2258), whose record names its parameter's type, TQtdEscolha. It lies in the
// data between this file's record (1536276) and comum/cpoliticaexecucaoeleitor.cpp's (1536344). Its name and its type
// are chosen: the readers load and store one byte, and two pass it as a TQtdEscolha.
extern comum::md::TQtdEscolha g_escolhaAtual;

// The letter of the "{o/a}" tag that CVotacaoStateAudio::FormataMensagem (fn 6999) fills: 'a' when the current
// candidacy's holder is a woman, else 'o'. 6999 holds it inlined by binaryen (written in that function's file, clang
// forms a select there that the target does not have), so it is a function of another TU. Its name, its being a free
// function and its place beside the voter's statics are chosen.
char ArtigoCandidato();

} // namespace vota
