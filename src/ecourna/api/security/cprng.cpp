#include "ecourna/api/security/cprng.hpp"

#include <limits>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

namespace ecourna::api::security {

CPrng::CPrng(int semente)
    : m_semente(semente)
{
}

uebyte CPrng::GetByte()
{
    boost::random::mt19937 gerador(static_cast<uebyte>(m_semente));
    boost::random::uniform_int_distribution<uebyte> distribuicao;
    return distribuicao(gerador);
}

int CPrng::GetInt()
{
    boost::random::mt19937 gerador(m_semente);
    boost::random::uniform_int_distribution<int> distribuicao(std::numeric_limits<int>::min() + 1,
                                                             std::numeric_limits<int>::max() - 1);
    return distribuicao(gerador);
}

int CPrng::Generate(std::vector<uebyte>& dados)
{
    return Generate(dados, dados.size());
}

int CPrng::Generate(std::vector<uebyte>& dados, size_t tamanho)
{
    boost::random::mt19937 gerador(static_cast<uebyte>(m_semente));
    boost::random::uniform_int_distribution<uebyte> distribuicao;
    if (tamanho == 0) {
        return 1;
    }
    if (tamanho > dados.size()) {
        return 2;
    }
    for (size_t i = 0; i < tamanho; ++i) {
        dados[i] = distribuicao(gerador);
    }
    return 0;
}

} // namespace ecourna::api::security
