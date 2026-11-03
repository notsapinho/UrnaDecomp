#pragma once

// comum::AdicionaParametro: a line of a parameter's name with its value right-aligned to 38 columns, added to a
// report's builder; comum::CGeradorRelVersaoPacoteDados's slot 4 (target fn 11222) holds it inlined by binaryen, behind
// a frame of its own. Reconstruction notes, not TSE's text: no record, slot or RTTI names it. Its body is
// comum::CGeradorRelPU::AdicionaParametro's (fn 677) over the builder passed in. Its name, its being a free function
// and this header's and its .cpp's paths are chosen; src/units/287-uenux2-cgeradorrelversaopacotedados.mk has why it is
// out of line in a TU of its own.

#include <string>

#include "api/gui/cpaperformbuilder.h"

namespace comum {

void AdicionaParametro(api::CPaperFormBuilder& builder, const std::string& nome, const std::string& valor);

} // namespace comum
