#include "ecourna/api/security/ctrng.hpp"

#include <exception>
#include <limits>
#include <random>
#include <string>

namespace ecourna::api::security {

namespace {

const std::string DISPOSITIVO = "/dev/urandom";

} // namespace

uebyte CTrng::GetByte()
{
    std::random_device dispositivo(DISPOSITIVO);
    std::uniform_int_distribution<int> distribuicao(0, std::numeric_limits<uebyte>::max());
    return static_cast<uebyte>(distribuicao(dispositivo));
}

int CTrng::GetInt()
{
    std::random_device dispositivo(DISPOSITIVO);
    std::uniform_int_distribution<int> distribuicao(std::numeric_limits<int>::min() + 1, std::numeric_limits<int>::max() - 1);
    return distribuicao(dispositivo);
}

int CTrng::Generate(std::vector<uebyte>& dados)
{
    return Generate(dados, dados.size());
}

int CTrng::Generate(std::vector<uebyte>& dados, size_t tamanho)
{
    try {
        std::random_device dispositivo(DISPOSITIVO);
        std::uniform_int_distribution<int> distribuicao(0, std::numeric_limits<uebyte>::max());
        if (tamanho == 0) {
            return 1;
        }
        if (tamanho > dados.size()) {
            return 2;
        }
        for (size_t i = 0; i < tamanho; ++i) {
            dados[i] = static_cast<uebyte>(distribuicao(dispositivo));
        }
        return 0;
    }
    catch (const std::exception&) {
        return -1;
    }
}

} // namespace ecourna::api::security
