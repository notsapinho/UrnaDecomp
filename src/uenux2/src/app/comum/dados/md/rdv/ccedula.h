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
// that of the classes that take it), this header's path and ccedula.cpp's (no record names a file of it), the data
// member's name and the members' names, that the member is private and the accessors members; that the vector is the
// one data member rests on the 12 bytes.
// The element is an aggregate (a reading of 4454's bytes, which do not match): the inlined ConfereCedula searches the
// vector for a value it builds in its frame, storing the post's id at +0 and then calling CVoto's constructor on +4
// of the same object, which brace-initializing an aggregate gives; a std::pair built from a CVoto temporary
// constructs the temporary first and moves it in. Its name and its members' names are chosen; its equality is
// defaulted, as the search compares the id, the type and the number in place.
// Out of line in ccedula.cpp, measured (src/units/197-uenux2-celeitorvotando.mk): Limpa, which slot 2 of
// vota::CEleitorVotando (fn 7377) calls on vota::g_votosEleitor and which keeps the new end's store before the
// next statement's, and Adiciona(const SVotoCargo&), whose push fn 4454 splits as the out-of-line form gives.
// GetVotos, inline, is chosen; vota::CVotacaoStateAudio::FormataMensagem (fn 6999) reads the vector's size through it
// from vota::g_votosEleitor.
// A post's vote in a ballot: the post's id and the vote.
struct SVotoCargo {
    TCargoID cargo;
    CVoto voto;

    bool operator==(const SVotoCargo& outro) const = default;
};

class CCedula {
public:
    CCedula();

    void Adiciona(TCargoID cargo, CVoto voto);
    void Adiciona(const SVotoCargo& voto);
    void Limpa();
    const std::vector<SVotoCargo>& GetVotos() const { return m_votos; }

private:
    std::vector<SVotoCargo> m_votos;
};

} // namespace comum::md
