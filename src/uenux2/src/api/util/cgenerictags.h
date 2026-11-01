#pragma once

#include <cstddef>
#include <map>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Tags de tamanho fixo, cada uma mapeada para o tamanho (de 1 a 4 bytes) do campo de comprimento que a segue numa
 * codificação TLV (tag, comprimento, valor).
 */
class CGenericTags {
public:
    // inline in every user: fns 3831 and 5892 store 4 and 3 at +0 and +4 and an empty map; the parameter and the form
    // are chosen
    explicit CGenericTags(size_t tamanhoTag) : m_tamanhoTagComNulo(tamanhoTag + 1), m_tamanhoTag(tamanhoTag) {}

    void insert(const std::string& tag, size_t tamanho);
    size_t TagSize(const std::string& tag) const;

    std::string EncodeTLV(const std::string& tag, const std::string& valor) const;
    std::string EncodeTLV(const std::string& tag, const std::string& valor, size_t tamanho) const;
    void AppendTLV(std::string& tlv, const std::string& tag, const std::string& valor) const;
    void AppendTLV(std::string& tlv, const std::string& tag, const std::string& valor, size_t tamanho) const;
    size_t WalkTreeTLV(const std::string& tlv, const std::string& tag) const;
    std::string DecodeTLV(std::string& tlv, const std::string& tag) const;

private:
    size_t m_tamanhoTagComNulo;
    size_t m_tamanhoTag;
    std::map<std::string, uebyte> m_tags;
};

} // namespace api
