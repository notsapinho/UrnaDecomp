// Reconstruction of api::CIniSection (api/io/cinisection.cpp, the file its operator='s record names): operator=, the
// constructor and SetKey. Line 36 is operator='s record (target fn 5480 holds it inlined); the other lines are a choice
// (src/units/379-uenux2-cinifile.mk).
#include "api/io/cinisection.h"

#include <utility>

#include "api/io/eueioerror.h"

namespace api {

// (original lines 12-32: content not recovered)
#line 33
CIniSection& CIniSection::operator=(const CIniSection& secao)
{
    if (secao.m_nome != m_nome) {
        throw CUeIoError(EUE_IO_NOME_SECAO_MODIFICADO, "O nome de uma seção é constante.");
    }
    TMapChaves copia(secao.m_chaves);
    m_chaves.swap(copia);
    return *this;
}

CIniSection::CIniSection(std::string nome)
    : m_nome(std::move(nome))
{
}

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
