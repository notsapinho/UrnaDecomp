#include "api/io/cencryptedfile.h"

#include "api/io/eueioerror.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"

namespace api {

// (original lines 9-32: content not recovered)
#line 33
// <stubs>
// f3653 · 3845 B · unmatched · name unknown
// void f3653(i32, i32) { ... }
// </stubs>

// (original lines 38-84: content not recovered)
#line 85
void CEncryptedFile::Save(const std::string& nome) const
{
    if (nome.empty()) {
        throw CUeIoError(EUE_IO_NOME_ARQUIVO_VAZIO, "Nome de arquivo vazio");
    }

    const uebyte complemento = 16 - (m_dados.size() % 16);
    std::vector<uebyte> dados;
    dados.reserve(m_dados.size() + complemento);
    dados.insert(dados.end(), m_dados.begin(), m_dados.end());
    for (int i = 0; i < complemento; ++i) {
        dados.push_back(complemento);
    }

    std::vector<uebyte> cifrado;
    m_cifrador->Encrypt(dados, cifrado);

    ecourna::api::io::CFile arquivo(nome, "wb");
    arquivo.RawWrite(cifrado.data(), cifrado.size());
    arquivo.Flush();
    arquivo.Sync();
    arquivo.Close();
}

} // namespace api

// <stubs>
// f2766 · 383 B · unmatched · name unknown
// void f2766(i32, i32) { ... }

// f3652 · 514 B · unmatched · name unknown
// void f3652(i32, i32) { ... }
// </stubs>
