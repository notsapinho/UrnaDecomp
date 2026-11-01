#include "ecourna/api/util/repete.hpp"

namespace ecourna::api::util {

void Repete(std::string& destino, const std::string& texto, size_t vezes)
{
    destino.reserve(destino.size() + vezes * texto.size());
    for (size_t i = 0; i < vezes; ++i) {
        destino += texto;
    }
}

} // namespace ecourna::api::util
