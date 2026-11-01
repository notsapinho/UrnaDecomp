#pragma once
#include <cstddef>
#include <string>

namespace ecourna::api::util {

// Appends texto to destino vezes times, reserving the room first. api::CGenericTags::EncodeTLV (target fn 5467) holds
// its body, inlined by binaryen, with its loads as ecourna's -fno-delete-null-pointer-checks compiles them
// (src/units/182-ecourna-api-util-repete.mk). No record names it: its name, this header's and its source's paths, its
// namespace and its being a free function are chosen.
void Repete(std::string& destino, const std::string& texto, size_t vezes);

} // namespace ecourna::api::util
