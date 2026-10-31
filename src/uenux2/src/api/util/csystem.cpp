// api::CSystem (/home/rubio/tse/uenux2/src/api/util/csystem.cpp): two functions whose throws are records of the
// target, so their positions in this file are fixed:
//   2759  CSystem::GetFileSize(const std::string&)               record at line 334, column 15
//   5457  api::truncate(int, off_t, const std::string&)          record at line 1024, column 15
// The file's other functions are not reconstructed yet; the lines their records name are left blank. One of them,
// api::ExistResource (1690, record at line 64), is file-static (its record comes after the external functions'
// records of this file): it is emitted out of line only once its callers here (2762, 5455, 2761) are written.

#include "api/util/csystem.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <format>
#include <functional>
#include <sys/stat.h>
#include <unistd.h>

#include "api/util/eueutilerror.h"

namespace api {

bool CSystem::s_dorme = true;

// (original lines 25-57: content not recovered)
#line 58
static bool ExistResource(struct stat& info, const std::string& recurso)
{
    if (stat(recurso.c_str(), &info) == -1) {
        if (errno == ENOENT || errno == ENOTDIR) {
            return false;
        }
        throw CUeUtilError(EUE_UTIL_FALHA_VALIDAR_RECURSO, std::format("Falha ao validar a existência do recurso [{}]: {}", recurso, strerror(errno)));
    }
    return true;
}

bool CSystem::ExistFile(const std::string& arquivo)
{
    struct stat info;

    return ExistResource(info, arquivo) && S_ISREG(info.st_mode);
}

bool CSystem::ExistDir(const std::string& diretorio)
{
    struct stat info;

    return ExistResource(info, diretorio) && S_ISDIR(info.st_mode);
}

// (original lines 83-251: content not recovered)
#line 252
// <stubs>
// f2762 · 919 B · unmatched · name unknown
// ? f2762(i32) { ... }
// </stubs>

// (original lines 257-321: content not recovered)
#line 322
/**
 * Obtém o tamanho de um arquivo.
 *
 * @param arquivo caminho do arquivo
 * @return tamanho do arquivo em bytes
 * @throw CUeUtilError se o estado do arquivo não puder ser obtido
 */
uedword CSystem::GetFileSize(const std::string& arquivo)
{
    struct stat info;

    if (stat(arquivo.c_str(), &info) != 0) {
        throw CUeUtilError(EUE_UTIL_FALHA_OBTER_TAMANHO_ARQUIVO, std::format("Falha ao obter tamanho do arquivo [{}]: {}", arquivo, strerror(errno)));
    }
    return info.st_size;
}

// (original lines 339-393: content not recovered)
#line 394
// <stubs>
// f378 · 4665 B · unmatched · name unknown
// void f378(i32, i32, i32) { ... }
// </stubs>

// (original lines 399-912: content not recovered)
#line 913
// <stubs>
// f5455 · 4258 B · unmatched · name unknown
// void f5455(i32, i32, i32) { ... }
// </stubs>

// (original lines 918-989: content not recovered)
#line 990
namespace {

class CScopeGuard {
public:
    explicit CScopeGuard(std::function<void()> acao)
        : m_acao(std::move(acao))
    {
    }

    ~CScopeGuard()
    {
        if (m_acao) {
            m_acao();
            m_acao = nullptr;
        }
    }

private:
    std::function<void()> m_acao;
};

} // namespace
/**
 * Trunca um arquivo aberto no tamanho dado.
 *
 * @param descritor descritor do arquivo
 * @param tamanho novo tamanho do arquivo
 * @param arquivo caminho do arquivo, para a mensagem de erro
 *
 * @throw CUeUtilError se o arquivo não puder ser truncado
 */
void truncate(int descritor, off_t tamanho, const std::string& arquivo)
{
    if (ftruncate(descritor, tamanho) == -1) {
        throw CUeUtilError(EUE_UTIL_FALHA_TRUNCAR_ARQUIVO, std::format("Falha ao truncar arquivo: {}-{}", arquivo, strerror(errno)));
    }
}

// (original lines 1028-1030: content not recovered)
#line 1031
void CSystem::ZeroFill(const std::string& arquivo)
{
    if (!ExistFile(arquivo)) {
        return;
    }

    int descritor = open(arquivo.c_str(), O_WRONLY);
    if (descritor == -1) {
        throw CUeUtilError(EUE_UTIL_FALHA_ABRIR_ARQUIVO, std::format("Falha ao abrir arquivo: {}-{}", arquivo, strerror(errno)));
    }
    CScopeGuard fechaArquivo([&descritor]() { close(descritor); });

    off_t tamanho = lseek(descritor, 0, SEEK_END);
    truncate(descritor, 0, arquivo);
    truncate(descritor, tamanho, arquivo);
}

} // namespace api
