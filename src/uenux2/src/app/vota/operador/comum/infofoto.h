#pragma once

#include <cstddef>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace vota {

// What vota::ValidaFotoEleitor (fotoeleitor.cpp) reads of a JPEG photo: the frame of fn 3616 that holds the validation
// keeps these five words at +12 to +28 and stores the parse's values there at each of its exits, before the throw of
// std::vector::at too, and reloads them after the calls that follow; the widths are the stores' (four i32, a byte),
// the -1 of the first three is their starting value, and the last two's zero start is chosen (an uninitialized field
// reads as the wasm local's 0 too). LeInfoFoto walks the markers: a SOFn
// marker (0xC0 to 0xCF but 0xC4, 0xC8, 0xCC, and 0xDE) gives the height, the width and 8 bits per component, SOS (0xDA)
// ends the walk, COM (0xFE) gives the comment's length, APP1 (0xE1) sets the flag, the markers of a segment that has a
// length are skipped and any other byte after 0xFF advances two bytes. It is out of line in infofoto.cpp, a TU of its
// own, and binaryen inlines it into its one caller (no target index): with it in the validator's TU, clang keeps the
// fields in locals across the calls the validator makes, where the target reloads them with i32.load16_u (fn 3616 read
// 274 over 1521 rows so, and 243 over 1516 with the parser here, pnpm wasm score; a reading of why). The struct's and
// the members' names, its being a struct, the file and the function's name are chosen.
struct SInfoFoto {
    int largura = -1;
    int altura = -1;
    int bitsPorPixel = -1;
    size_t tamanhoComentario = 0;
    bool temExif = false;
};

SInfoFoto LeInfoFoto(const std::vector<uebyte>& dados);

} // namespace vota
