#pragma once

#include <cstdint>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Conversões de imagens em memória, um byte por pixel, feitas no lugar.
 */
class CBmpConversor {
public:
    static void VerticalFlip(unsigned char* data, const int width, const int height);
    static void InvertColors(unsigned char* data, const int width, const int height);
    static std::vector<uebyte> CreateBitmapHeader(const unsigned long dataSize, const unsigned long width,
                                                  const unsigned long height, const int numColors);
};

} // namespace api
