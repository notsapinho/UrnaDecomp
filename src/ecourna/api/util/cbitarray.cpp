#include "ecourna/api/util/cbitarray.hpp"

#include "ecourna/api/util/eutilerror.hpp"

namespace ecourna::api::util {

CBitArray::CBitArray(const std::vector<uebyte>& bytes)
    : m_bits(std::make_shared<boost::dynamic_bitset<uebyte>>()), m_bytes(), m_escrita(true), m_leitura(false), m_posicao(0)
{
    for (size_t i = 0; i < bytes.size(); ++i) {
        for (int bit = 7; bit >= 0; --bit) {
            m_bits->push_back(bytes.at(i) & (1 << bit));
        }
    }
}

// (original lines 17-40: content not recovered)
#line 41
ueword CBitArray::GetValor(const uebyte bits)
{
    if (!m_escrita) {
        throw CUtilError(EUE_BITARRAY_SEM_ESCRITA, "sem permissao de escrita no array de bits");
    }
    ueword valor = GetValor(m_posicao, bits);
    m_posicao += bits;
    return valor;
}

ueword CBitArray::GetValor(const ueqword posicao, const uebyte bits) const
{
    ueword valor = 0;
    ueqword pos = posicao;
    if (m_bits == nullptr) {
        throw CUtilError(EUE_BITARRAY_NAO_ALOCADO, "array de bits nao alocado corretamente");
    }
    if (bits > 0) {
        ueqword restantes = m_bits->size() - posicao;
        if (restantes > m_bits->size()) restantes = 0;
        if (bits - 1 < restantes) {
            for (int i = bits; i > 0; --i) if (m_bits->test(pos++)) valor |= 1 << (i - 1);
        } else {
            throw CUtilError(EUE_BITARRAY_POSICAO_INVALIDA, "busca no vetor em posicao invalida");
        }
    }
    return valor;
}

} // namespace ecourna::api::util
