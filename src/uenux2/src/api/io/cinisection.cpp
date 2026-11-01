// Reconstruction of api::CIniSection (api/io/cinisection.cpp, the file its operator='s record names): SetKey only.
// Line 36 is operator='s record (target fn 5480 holds it), not written; SetKey's lines are a choice.
#include "api/io/cinisection.h"

#include <utility>

namespace api {
































void CIniSection::SetKey(const CIniKey& chave)
{
    auto it = m_chaves.find(chave.GetNome());
    if (it != m_chaves.end()) {
        it->second = chave;
    } else {
        m_chaves.insert(m_chaves.end(), std::make_pair(chave.GetNome(), chave));
    }
}

} // namespace api
