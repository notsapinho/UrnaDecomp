#include "api/io/cencryptedfile.h"

#include <cstring>
#include <format>
#include <vector>

#include "api/io/eueioerror.h"
#include "api/util/csystem.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"

namespace api {

CEncryptedFile::~CEncryptedFile() = default;

// (original lines 16-32: content not recovered)
#line 33
void CEncryptedFile::Load(const std::string& nome)
{
    if (nome.empty()) {
        throw CUeIoError(EUE_IO_LOAD_NOME_ARQUIVO_VAZIO, "Nome de arquivo vazio");
    }
    if (!CSystem::ExistFile(nome)) {
        throw CUeIoError(EUE_IO_ARQUIVO_INEXISTENTE, std::format("Arquivo [{}] não existe", nome));
    }

    const uedword tamanho = CSystem::GetFileSize(nome);
    if (tamanho == 0 || tamanho % 16 != 0) {
        CUeIoError(EUE_IO_TAMANHO_ARQUIVO_INVALIDO, std::format("Arquivo [{}] com tamanho inválido", nome));
    }

    ecourna::api::io::CFile arquivo(nome, "rb");
    std::vector<uebyte> cifrado(tamanho);

    if (arquivo.RawRead(cifrado.data(), tamanho) != tamanho) {
        CUeIoError(EUE_IO_FALHA_LEITURA_ARQUIVO, std::format("Falha ao ler arquivo [{}]", nome));
    }

    std::vector<uebyte> dados;
    m_cifrador->Decrypt(cifrado, dados);

    const uebyte complemento = dados.back();
    if (complemento > 16) {
        throw CUeIoError(EUE_IO_PADDING_INVALIDO, std::format("Tamanho de padding inválido em [{}]", nome));
    }

    // (original lines 62-63: content not recovered)
#line 64
    if (complemento > tamanho) {
        throw CUeIoError(EUE_IO_PADDING_EXCESSIVO, std::format("Tamanho de padding excessivo em [{}]", nome));
    }

    // (original lines 68-70: content not recovered)
#line 71
    for (int i = 1; i < complemento; ++i) {
        if (dados[dados.size() - 1 - i] != complemento) {
            CUeIoError(EUE_IO_PADDING_SECUNDARIO_INVALIDO, std::format("Tamanho de padding secundário inválido em [{}]", nome));
        }
    }

    std::vector<uebyte> conteudo(dados.begin(), dados.end() - complemento);
    m_dados.swap(conteudo);
    m_posicao = 0;
}

// (original lines 82-84: content not recovered)
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
