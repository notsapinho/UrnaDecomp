#include "api/io/cencryptedfile.h"

#include <cstring>

#include "api/io/eueioerror.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"

namespace api {

CEncryptedFile::~CEncryptedFile() = default;

// (original lines 13-32: content not recovered)
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


uedword CEncryptedFile::Write(const std::vector<uebyte>& dados)
{
    if (dados.empty()) {
        return 0;
    }
    return MemWrite(dados.data(), dados.size());
}

uedword CEncryptedFile::Read(std::vector<uebyte>& dados)
{
    const uedword restante = m_dados.size() - m_posicao;
    if (restante == 0) {
        return 0;
    }
    const auto tamanho = dados.size();
    dados.resize(tamanho + restante, 0xFF);
    return MemRead(dados.data() + tamanho, restante);
}

// (original lines 129-138: content not recovered)
#line 139
uedword CEncryptedFile::MemWrite(const void* buffer, uedword tamanho)
{
    if (tamanho == 0) {
        throw CUeIoError(EUE_IO_MEMWRITE_TAMANHO_INVALIDO, "Tamanho inválido");
    }
    if (buffer == nullptr) {
        throw CUeIoError(EUE_IO_MEMWRITE_BUFFER_INVALIDO, "Buffer inválido");
    }

    if (m_posicao + tamanho > m_dados.size()) {
        m_dados.resize(m_posicao + tamanho);
    }
    std::memcpy(m_dados.data() + m_posicao, buffer, tamanho);
    m_posicao += tamanho;
    return tamanho;
}

// (original lines 156-157: content not recovered)
#line 158
uedword CEncryptedFile::MemRead(void* buffer, uedword tamanho)
{
    if (tamanho == 0) {
        throw CUeIoError(EUE_IO_MEMREAD_TAMANHO_INVALIDO, "Tamanho inválido");
    }
    if (buffer == nullptr) {
        throw CUeIoError(EUE_IO_MEMREAD_BUFFER_INVALIDO, "Buffer inválido");
    }
    if (m_dados.size() == 0 || m_dados.size() < tamanho) {
        throw CUeIoError(EUE_IO_MEMREAD_NADA_PARA_LER, "Não há nada para ler");
    }

    uedword lidos = 0;
    if (m_posicao + tamanho <= m_dados.size()) {
        std::memcpy(buffer, m_dados.data() + m_posicao, tamanho);
        m_posicao += tamanho;
        lidos = tamanho;
    }
    return lidos;
}

} // namespace api
