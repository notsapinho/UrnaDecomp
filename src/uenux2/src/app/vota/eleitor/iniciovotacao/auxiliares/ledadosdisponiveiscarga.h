#pragma once

// vota::LeDadosDisponiveisCarga: the md::CDadosDisponiveisCarga of a file, read through api::CFileASN and
// comum::asn::CConversorDadosDisponiveisCarga. Reconstruction notes, not TSE's text: no record, slot or RTTI names the
// function or this file. vota::CImpressaoVersaoPacotes::StartState (target fn 11905) holds it inlined by binaryen
// behind a 64-byte frame of its own (the converter's vptr at +60, the entity at +8), so it is out of line in another TU
// (src/units/287-uenux2-cgeradorrelversaopacotedados.mk has the measurement). Its name, its being a free function, its
// namespace (the caller's class's) and this header's and its .cpp's paths are chosen.

#include <string>

#include "app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.h"

namespace vota {

comum::md::CDadosDisponiveisCarga LeDadosDisponiveisCarga(const std::string& arquivo);

} // namespace vota
