#pragma once

#include <utility>
#include <vector>

#include "app/comum/dados/md/rdv/cvoto.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum::md {

// The records of CVotosCargos::InsereCedula and ConfereCedula and of CVotosEleicoesVota::RecebeCedula take this class
// by const reference; fn 4454, a vota::CEleitorVotando member no record names, holds all three inlined and is the one
// target function that loads them (column 6 of ledger/source-locations.tsv). What its bytes show of the class
// (`pnpm wasm fn ../target/vota_web_wasm.wasm 4454`):
// - 4454 builds a map of 32-byte nodes, a word key at +16 and the value at +20, and constructs each value with a call
//   of fn 203's body, which zeroes 12 bytes; it then pushes into the vector at +20 to +28 copies of 20-byte pairs, a
//   byte (the post's id) at +0 and a CVoto at +4, taken from vota::g_votosEleitor
//   (app/vota/eleitor/comum/cinformacaoeleitor.h), which is read as one of these too (that header says what the
//   reading rests on);
// - the inlined ConfereCedula compares that vector's (end - begin) / 20 with CVotosCargos::QuantidadeEscolhas (fn 5642)
//   and throws "Tamanho da cedula (" under its record cvotoscargos.cpp:248 (1573780) when they differ.
// The constructor is a call there, so it is user-provided and defined out of line, in ccedula.cpp (a reading: one
// clang sees inline is folded into the stores). Chosen: the class's namespace (the records print it unqualified; it is
// that of the classes that take it), this header's path and ccedula.cpp's (no record names a file of it), std::pair as
// the element (no symbol spells it), the data member's name and Adiciona's; that the vector is the one data member
// rests on the 12 bytes.
class CCedula {
public:
    CCedula();

    void Adiciona(TCargoID cargo, CVoto voto);

private:
    std::vector<std::pair<TCargoID, CVoto>> m_votos;
};

} // namespace comum::md
