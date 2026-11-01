// api::CGenericTags (/home/rubio/tse/uenux2/src/api/util/cgenerictags.cpp). TagSize's throw is a record of the
// target, so its position in this file is fixed:
//   5468  TagSize(const std::string &) const   record at line 46, column 15

#include "api/util/cgenerictags.h"

#include <format>

#include "api/util/eueutilerror.h"

namespace api {

// (original lines 13-27: content not recovered)
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

} // namespace api

// <stubs>
// f5467 · 2505 B · unmatched · name unknown
// void f5467(i32, i32, i32, i32, i32) { ... }

// f5466 · 627 B · unmatched · name unknown
// void f5466(i32, i32, i32, i32) { ... }

// f5892 · 3294 B · unmatched · name unknown
// ? f5892(i32, i32, i32, i32, i32) { ... }
// </stubs>
