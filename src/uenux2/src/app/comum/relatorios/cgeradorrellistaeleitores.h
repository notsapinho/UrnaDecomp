#pragma once

// The voters' list report of comum. Reconstruction notes, not TSE's text: no record names this header, so its path
// is chosen, beside cgeradorrellistaeleitores.cpp, whose record (SituacaoEleitor's, line 100) names the file.
//
// ImprimeListaEleitores has no target index: vota::CImpressaoListaEleitores::StartState (fn 11908) holds it inlined
// by binaryen (a 144-byte frame of its own) and passes it the title and the copy's text, which the frame of
// DoPrintJob inside it copies from 11908's own (src/units/317-uenux2-relatorios-aptos.mk). Its name, its
// parameters' names and its being a free function of comum are chosen.

#include <string>

namespace comum {

void ImprimeListaEleitores(const std::string& titulo, const std::string& via);

} // namespace comum
