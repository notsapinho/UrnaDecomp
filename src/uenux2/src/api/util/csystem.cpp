// api::CSystem (/home/rubio/tse/uenux2/src/api/util/csystem.cpp). Records fix the lines of GetFileSize (2759, 334:15),
// api::ExistResource (1690, 64:15; file-static: its record follows the external functions'), CopyFile (378, 390:15 to
// 476:19), Rename (692:15; binaryen inlines it into fn 11584), api::truncate (5457, 1024:15) and ZeroFill (2761,
// 1039:15). ExistFile, ExistDir, RemoveFile, RemoveTree, GetFreeSpace, GetUsedSpace and GetMemInfo (412, 5459, 2760,
// 5458, 5454, 5453, 5463; binaryen merges the first two as 6019) have no record: their names and lines are chosen,
// and so is the namespace of the last four, free functions of api (csystem.h and unit 32's fragment say from what). AlteraDono and AlteraPermissoes, which binaryen inlines into
// CopyFile, have no record and no target index: their names, lines and linkage are chosen (unit 32's fragment says what
// the target shows).
// CScopeGuard (lines 990-1011, an anonymous namespace), its name, place and members' names are chosen: it holds
// ZeroFill's lambda in a std::function. The file's other functions are not reconstructed yet; the lines their records
// name are left blank.

#include "api/util/csystem.h"

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fcntl.h>
#include <format>
#include <functional>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <vector>

#include "api/util/cdirreader.h"
#include "api/util/csynchronizer.h"
#include "api/util/eueutilerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

bool CSystem::s_dorme = true;

namespace {

constexpr size_t TAMANHO_BUFFER_COPIA = 32 * 1024;
constexpr size_t TAMANHO_BUFFER_MEMINFO = 4096;

} // namespace

// (original lines 44-57: content not recovered)
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

int AlteraDono(const std::string& arquivo, uid_t dono, gid_t grupo)
{
    struct stat info;

    if (stat(arquivo.c_str(), &info) != 0) {
        return -1;
    }
    if (S_ISDIR(info.st_mode)) {
        DIR* diretorio = opendir(arquivo.c_str());
        if (diretorio == nullptr) {
            return -1;
        }
        int resultado = fchown(dirfd(diretorio), dono, grupo);
        closedir(diretorio);
        if (resultado < 0) {
            return -1;
        }
    } else if (info.st_mode & S_IFREG) {
        int descritor = open(arquivo.c_str(), O_RDONLY);
        if (descritor == -1) {
            if (errno != EPERM && errno != EACCES) {
                return -1;
            }
            return chown(arquivo.c_str(), dono, grupo);
        }
        int resultado = fchown(descritor, dono, grupo);
        close(descritor);
        if (resultado < 0) {
            return -1;
        }
    } else {
        return chown(arquivo.c_str(), dono, grupo);
    }
    return 0;
}

int AlteraPermissoes(const std::string& arquivo, mode_t modo)
{
    struct stat info;

    if (stat(arquivo.c_str(), &info) != 0) {
        return -1;
    }
    if (S_ISDIR(info.st_mode)) {
        DIR* diretorio = opendir(arquivo.c_str());
        if (diretorio == nullptr) {
            return -1;
        }
        int resultado = fchmod(dirfd(diretorio), modo);
        closedir(diretorio);
        if (resultado < 0) {
            return -1;
        }
    } else if (info.st_mode & S_IFREG) {
        int descritor = open(arquivo.c_str(), O_RDONLY);
        if (descritor == -1) {
            if (errno != EPERM && errno != EACCES) {
                return -1;
            }
            return chmod(arquivo.c_str(), modo);
        }
        int resultado = fchmod(descritor, modo);
        close(descritor);
        if (resultado < 0) {
            return -1;
        }
    } else {
        return chmod(arquivo.c_str(), modo);
    }
    return 0;
}

int RemoveTree(const std::string& diretorio)
{
    struct stat info;
    std::vector<std::string> diretorios;
    std::vector<std::string> arquivos;
    CDirReader leitor(diretorio);

    while (leitor.NextEntry()) {
        const std::string nome = leitor.GetEntryName();
        if (leitor.IsLink() || leitor.IsFile()) {
            arquivos.push_back(diretorio + "/" + nome);
        } else if (leitor.IsDir() && nome != "." && nome != "..") {
            diretorios.push_back(diretorio + "/" + nome);
        }
    }
    leitor.Close();

    for (const std::string& subdiretorio : diretorios) {
        if (RemoveTree(subdiretorio) != 0 || rmdir(subdiretorio.c_str()) != 0) {
            return -1;
        }
    }
    for (const std::string& arquivo : arquivos) {
        if (lstat(arquivo.c_str(), &info) == -1 || !S_ISLNK(info.st_mode)) {
            CSystem::ZeroFill(arquivo);
        }
        if (remove(arquivo.c_str()) != 0) {
            return -1;
        }
    }
    return 0;
}

// (original lines 188-251: content not recovered)
#line 252
// <stubs>
// f2762 · 919 B · unmatched · name unknown
// ? f2762(i32) { ... }
// </stubs>

// (original lines 257-304: content not recovered)
#line 305
void CSystem::RemoveFile(const std::string& arquivo)
{
    struct stat info;

    if (lstat(arquivo.c_str(), &info) == -1 || !S_ISLNK(info.st_mode)) {
        ZeroFill(arquivo);
    }
    remove(arquivo.c_str());
}

// (original lines 315-321: content not recovered)
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

// (original lines 339-381: content not recovered)
#line 382
void CSystem::CopyFile(const std::string& origem, const std::string& destino, bool preservaAtributos, bool sobrescreve)
{
    if (origem == destino) {
        return;
    }


    if (!sobrescreve && ExistFile(destino)) {
        throw CUeUtilError(EUE_UTIL_ARQUIVO_DESTINO_EXISTENTE, std::format("O arquivo de destino [{}] já existe", destino));
    }


    int descritorOrigem = open(origem.c_str(), O_RDONLY);

    if (descritorOrigem < 0) {
        throw CUeUtilError(EUE_UTIL_FALHA_LER_ARQUIVO_ORIGEM, std::format("O arquivo de origem [{}] não pode ser lido: {}", origem, strerror(errno)));
    }

    const int sincronismo = CSynchronizer::GetInst().GetOpenFlag();

    // (original lines 402-404: content not recovered)
#line 405
    int descritorDestino = open(destino.c_str(), O_WRONLY | O_CREAT | O_TRUNC | sincronismo, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (descritorDestino < 0) {
        int erro = errno;
        close(descritorOrigem);
        errno = erro;

        // (original lines 412-413: content not recovered)
#line 414
        throw CUeUtilError(EUE_UTIL_FALHA_CRIAR_ARQUIVO_DESTINO, std::format("O arquivo de destino [{}] não pôde ser criado: {}", destino, strerror(erro)));
    }

    std::vector<char> buffer(TAMANHO_BUFFER_COPIA);
    int erro = 0;

    ssize_t lidos;
    while ((lidos = read(descritorOrigem, buffer.data(), buffer.size())) != 0) {
        if (lidos < 0) {
            erro = errno;
            break;
        }

        ssize_t escritos = 0;
        while (escritos < lidos) {
            ssize_t gravados = write(descritorDestino, buffer.data() + escritos, lidos - escritos);
            if (gravados <= 0) {
                erro = errno;
                break;
            }
            escritos += gravados;
        }
        if (escritos != lidos) {
            break;
        }
    }

    close(descritorOrigem);
    if (close(descritorDestino) != 0) {
        erro = errno;
    }


    if (erro != 0) {
        throw CUeUtilError(EUE_UTIL_FALHA_COPIAR_ARQUIVO, std::format("Falha ao copiar o arquivo [{}] para [{}]: {}", origem, destino, strerror(erro)));
    }

    if (preservaAtributos) {
        struct stat info;


        if (lstat(origem.c_str(), &info) < 0) {
            throw CUeUtilError(EUE_UTIL_FALHA_OBTER_INFORMACOES_ARQUIVO, std::format("Falha ao obter informações do arquivo [{}]: {}", origem, strerror(errno)));
        }

        struct utimbuf tempos;
        tempos.actime = info.st_atime;
        tempos.modtime = info.st_mtime;


        if (utime(destino.c_str(), &tempos) < 0) {
            throw CUeUtilError(EUE_UTIL_FALHA_ALTERAR_HORA_ARQUIVO, std::format("Falha ao alterar a hora do arquivo [{}]: {}", destino, strerror(errno)));
        }

        // (original lines 468-469: content not recovered)
#line 470
        if (AlteraDono(destino, info.st_uid, info.st_gid) < 0) {
            throw CUeUtilError(EUE_UTIL_FALHA_ALTERAR_DONO_ARQUIVO, std::format("Falha ao alterar o dono do arquivo [{}]: {}", destino, strerror(errno)));
        }


        if (AlteraPermissoes(destino, info.st_mode) < 0) {
            throw CUeUtilError(EUE_UTIL_FALHA_ALTERAR_PERMISSOES_ARQUIVO, std::format("Falha ao alterar as permissões do arquivo [{}]: {}", destino, strerror(errno)));
        }
    }

    CSynchronizer::GetInst().Sync();
}

// (original lines 483-684: content not recovered)
#line 685
void CSystem::Rename(const std::string& origem, const std::string& destino)
{
    if (origem == destino) {
        return;
    }

    if (rename(origem.c_str(), destino.c_str()) != 0) {
        throw CUeUtilError(EUE_UTIL_FALHA_RENOMEAR, std::format("Falha ao renomear [{}] para [{}]: {}", origem, destino, strerror(errno)));
    }
}

// (original lines 696-912: content not recovered)
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

uintmax_t GetFreeSpace(const std::string& caminho)
{
    const std::filesystem::path diretorio(caminho);
    return std::filesystem::space(diretorio).free;
}

uintmax_t GetUsedSpace(const std::string& caminho)
{
    const std::filesystem::path diretorio(caminho);
    const std::filesystem::space_info espaco = std::filesystem::space(diretorio);
    return espaco.capacity - espaco.free;
}

uedword GetMemInfo(const std::string& campo)
{
    std::vector<char> buffer(TAMANHO_BUFFER_MEMINFO);
    uedword valor = 0;

    const int descritor = open("/proc/meminfo", O_RDONLY);
    if (descritor < 0) {
        return valor;
    }
    const ssize_t lidos = read(descritor, buffer.data(), buffer.size());
    close(descritor);

    const std::string conteudo = std::string(buffer.data()).substr(0, lidos);
    const size_t posicao = conteudo.find(campo);
    if (posicao == std::string::npos) {
        return valor;
    }
    const std::string linha = conteudo.substr(posicao, conteudo.find('\n', posicao) - posicao);
    const size_t inicio = linha.find_first_of("0123456789");
    if (inicio != std::string::npos) {
        const size_t fim = linha.find_first_not_of("0123456789", inicio);
        if (fim != std::string::npos) {
            valor = ecourna::api::util::CStringUtils::ToDWord(linha.substr(inicio, fim - inicio));
        }
    }
    return valor;
}

} // namespace api
