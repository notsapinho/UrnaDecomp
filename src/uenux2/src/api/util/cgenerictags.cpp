// api::CGenericTags (/home/rubio/tse/uenux2/src/api/util/cgenerictags.cpp). Records fix the throws' lines, all at
// column 15: insert (1071) 31, 34 and 37, TagSize (5468) 46, EncodeTLV (5467) 79 and 85, and AppendTLV 102 (inlined
// into 5466). The overloads without the length-field size (3647, 5466) have no record: their names and lines are
// chosen (src/units/33-uenux2-cgenerictags.mk says from what).

#include "api/util/cgenerictags.h"

#include <cmath>
#include <format>

#include "api/util/eueutilerror.h"
#include "ecourna/api/util/repete.hpp"

namespace api {

// (original lines 16-27: content not recovered)
#line 28
void CGenericTags::insert(const std::string& tag, size_t tamanho)
{
    if (tag.size() != m_tamanhoTagComNulo - 1) {
        throw CUeUtilError(EUE_UTIL_TAG_TAMANHO_INVALIDO, std::format("Tag [{}] com tamanho inválido", tag));
    }
    if (m_tags.find(tag) != m_tags.end()) {
        throw CUeUtilError(EUE_UTIL_TAG_JA_MAPEADA, std::format("Tag [{}] já foi mapeada", tag));
    }
    if (tamanho < 1 || tamanho > 4) {
        throw CUeUtilError(EUE_UTIL_TAG_TAMANHO_CAMPO_INVALIDO, std::format("Tag [{}] com tamanho inválido", tag));
    }
    m_tags.insert(std::make_pair(tag, tamanho));
}

size_t CGenericTags::TagSize(const std::string& tag) const
{
    const auto it = m_tags.find(tag);
    if (it == m_tags.end()) {
        throw CUeUtilError(EUE_UTIL_TAG_NAO_MAPEADA, std::format("Tag [{}] não mapeada", tag));
    }
    return it->second;
}

std::string CGenericTags::EncodeTLV(const std::string& tag, const std::string& valor) const
{
    return EncodeTLV(tag, valor, TagSize(tag));
}

// (original lines 56-75: content not recovered)
#line 76
std::string CGenericTags::EncodeTLV(const std::string& tag, const std::string& valor, size_t tamanho) const
{
    if (tag.size() != m_tamanhoTagComNulo - 1) {
        throw CUeUtilError(EUE_UTIL_TLV_TAG_TAMANHO_INVALIDO, std::format("Tag [{}] com tamanho inválido", tag));
    }
    const size_t limite = std::pow(2, tamanho * 8) - 1;
    std::string tlv = tag;
    ecourna::api::util::Repete(tlv, std::string(1, static_cast<char>(';' + tamanho)), m_tamanhoTagComNulo - tag.size());
    if (valor.size() > limite) {
        throw CUeUtilError(EUE_UTIL_TLV_LIMITE_EXCEDIDO, std::format("Tag [{}] excedeu o limite de codificação", tag));
    }
    return std::format("{}{:0{}x}{}", tlv, valor.size(), tamanho * 2, valor);
}

void CGenericTags::AppendTLV(std::string& tlv, const std::string& tag, const std::string& valor) const
{
    AppendTLV(tlv, tag, valor, TagSize(tag));
}

// (original lines 95-98: content not recovered)
#line 99
void CGenericTags::AppendTLV(std::string& tlv, const std::string& tag, const std::string& valor, size_t tamanho) const
{
    if (tag.size() != m_tamanhoTagComNulo - 1) {
        throw CUeUtilError(EUE_UTIL_TLV_ANEXA_TAG_TAMANHO_INVALIDO, std::format("Tag [{}] com tamanho inválido", tag));
    }
    tlv += EncodeTLV(tag, valor, tamanho);
}

} // namespace api

// <stubs>
// f5892 · 3294 B · unmatched · name unknown
// ? f5892(i32, i32, i32, i32, i32) { ... }
// </stubs>
