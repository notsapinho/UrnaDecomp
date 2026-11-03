// api::CSystem (/home/rubio/tse/uenux2/src/api/util/csystem.cpp). Records fix the lines of GetFileSize (2759, 334:15),
// api::ExistResource (1690, 64:15; file-static: its record follows the external functions'), IsEmptyDir (2762, 255:15),
// CopyFile (378, 390:15 to 476:19), Rename (692:15; binaryen inlines it into fn 11584), api::truncate (5457, 1024:15) and
// ZeroFill (2761, 1039:15). ExistFile, ExistDir, RemoveFile, RemoveTree, GetFreeSpace, GetUsedSpace, GetMemInfo,
// GetFileName and GetDirName (412, 5459, 2760, 5458, 5454, 5453, 5463, 2763, 5462; binaryen merges the first two as 6019)
// have no record: their names and lines are chosen, and so are the last six's being free functions and their namespace,
// api: RemoveTree, which only this file calls, and the five csystem.h declares (unit 32's fragment says why). So do
// CreateDir and DiretorioContemApenas, which binaryen inlines into fns 5821 and 11167, GetMemTotal and GetMemFree, into
// fn 10226 (no target index), and AlteraDono and AlteraPermissoes, inlined into CopyFile: their names, lines and
// linkage are chosen (unit 32's fragment says what the target shows). CScopeGuard
// (lines 990-1011, an anonymous namespace), its name, place and members' names are chosen: it holds ZeroFill's lambda in
// a std::function. ReplaceFile (5455) holds TemporaryPath (records 236:15 and 243:15) and the anonymous namespace's
// PrepareReplace (916:15 to 928:15) and ReplaceResource (954:15, 962:15) inlined; its name, and RenameResource's (3645),
// Existe's, ReplaceDir's (both with no target index) and their lines, are chosen (unit 32's fragment says from what).
// The file's other functions are not reconstructed yet; the lines their records name are left blank.

#include "api/util/csystem.h"

#include <algorithm>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <fcntl.h>
#include <format>
#include <functional>
#include <iterator>
#include <sys/stat.h>
#include <unistd.h>
#include <utime.h>
#include <string_view>
#include <vector>

#include "api/util/cdirreader.h"
#include "api/util/cstringutils.h"
#include "api/util/csynchronizer.h"
#include "api/util/eueutilerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

bool CSystem::s_dorme = true;

namespace {

constexpr size_t TAMANHO_BUFFER_COPIA = 32 * 1024;
constexpr size_t TAMANHO_BUFFER_MEMINFO = 4096;

} // namespace

// (original lines 52-57: content not recovered)
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

std::string GetFileName(const std::string& caminho)
{
    const size_t barra = caminho.rfind('/');
    if (barra == std::string::npos) {
        return caminho;
    }
    return caminho.substr(barra + 1);
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

// (original lines 197-229: content not recovered)
#line 230
std::string CSystem::TemporaryPath(const std::string& caminho)
{
    std::string temporario = caminho + ".XXXXXX";

    const int descritor = mkstemp(&temporario.at(0));
    if (descritor == -1) {
        throw CUeUtilError(EUE_UTIL_FALHA_CRIAR_CAMINHO_TEMPORARIO, std::format("Falha ao criar caminho temporário para [{}]: {}", caminho, strerror(errno)));
    }
    close(descritor);

    // (original lines 240-241: content not recovered)
#line 242
    if (temporario.at(0) == '\0') {
        throw CUeUtilError(EUE_UTIL_CAMINHO_TEMPORARIO_VAZIO, std::format("Falha ao criar caminho temporário para [{}]: {}", caminho, strerror(errno)));
    }

    return temporario;
}

// (original lines 249-250: content not recovered)
#line 251
bool CSystem::IsEmptyDir(const std::string& diretorio)
{

    if (!ExistDir(diretorio)) {
        throw CUeUtilError(EUE_UTIL_DIRETORIO_NAO_EXISTE, std::format("O diretório [{}] não existe: {}", diretorio, strerror(errno)));
    }

    CDirReader leitor(diretorio);
    bool vazio = true;
    while (leitor.NextEntry()) {
        const std::string nome = leitor.GetEntryName();
        if (leitor.IsDir() && nome != "." && nome != "..") {
            vazio = false;
            break;
        }
        if (leitor.IsFile()) {
            vazio = false;
            break;
        }
    }
    leitor.Close();
    return vazio;
}

bool CreateDir(const std::string& diretorio)
{
    std::string caminho;
    std::string::const_iterator inicio = diretorio.begin();
    while (inicio != diretorio.end()) {
        const std::string::const_iterator fim = std::find(inicio, diretorio.end(), '/');
        if (std::distance(inicio, fim) > 0) {
            std::copy(inicio, fim, std::back_inserter(caminho));
            if (!CSystem::ExistDir(caminho) && mkdir(caminho.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) < 0) {
                return false;
            }
        }
        caminho.push_back('/');
        inicio = (fim == diretorio.end()) ? fim : fim + 1;
    }
    return true;
}

// (original lines 293-304: content not recovered)
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

// (original lines 696-897: content not recovered)
#line 898
namespace {

bool Existe(const std::string& recurso)
{
    struct stat info;

    return stat(recurso.c_str(), &info) == 0;
}


std::string PrepareReplace(const std::string& origem, const std::string& destino, const std::string& backup,
                           bool (*existe)(const std::string&), const std::string& contexto, const std::string& tipo)
{
    const std::string caminhoBackup = backup.empty() ? CSystem::TemporaryPath(origem) : backup;
    if (backup.empty()) {
        CSystem::RemoveFile(caminhoBackup);
    }
    if (!existe(origem)) {
        throw CUeUtilError(EUE_UTIL_RECURSO_NAO_ENCONTRADO, std::format("{} - {} [{}] não encontrado", contexto, tipo, origem));
    }

    // (original lines 919-920: content not recovered)
#line 921
    if (origem == destino) {
        throw CUeUtilError(EUE_UTIL_RECURSOS_MESMO_NOME, std::format("{} - os {}s têm o mesmo nome [{}]", contexto, tipo, destino));
    }

    // (original lines 925-926: content not recovered)
#line 927
    if (Existe(caminhoBackup)) {
        throw CUeUtilError(EUE_UTIL_BACKUP_EXISTENTE, std::format("{} - {} [{}] existe", contexto, tipo, caminhoBackup));
    }

    return caminhoBackup;
}

std::string RenameResource(const std::string& origem, const std::string& destino)
{
    if (rename(origem.c_str(), destino.c_str()) != 0) {
        return "RenameResource(" + origem + ", " + destino + ") - " + strerror(errno);
    }
    return "";
}

void ReplaceResource(const std::string& origem, const std::string& destino, const std::string& backup,
                     const std::string& contexto)
{
    std::string erro;

    // (original lines 947-952: content not recovered)
#line 953
    if (Existe(destino) && !(erro = RenameResource(destino, backup)).empty()) {
        throw CUeUtilError(EUE_UTIL_FALHA_RENOMEAR_DESTINO, contexto + " - " + erro);
    }

    erro = RenameResource(origem, destino);
    if (!erro.empty()) {
        if (Existe(backup)) {
            RenameResource(backup, destino);
        }
        throw CUeUtilError(EUE_UTIL_FALHA_RENOMEAR_ORIGEM, contexto + " - " + erro);
    }

    if (CSystem::ExistDir(backup)) {
        if (RemoveTree(backup) == 0) {
            rmdir(backup.c_str());
        }
    } else if (CSystem::ExistFile(backup)) {
        CSystem::RemoveFile(backup);
    }
}

} // namespace

void CSystem::ReplaceFile(const std::string& origem, const std::string& destino, const std::string& backup)
{
    const std::string caminhoBackup = PrepareReplace(origem, destino, backup, CSystem::ExistFile, "CSystem::ReplaceFile", "arquivo");
    ReplaceResource(origem, destino, caminhoBackup, "CSystem::ReplaceFile");
}

void CSystem::ReplaceDir(const std::string& origem, const std::string& destino, const std::string& backup)
{
    const std::string caminhoBackup = PrepareReplace(origem, destino, backup, CSystem::ExistDir, "CSystem::ReplaceDir", "diretório");
    ReplaceResource(origem, destino, caminhoBackup, "CSystem::ReplaceDir");
}

// (original lines 988-989: content not recovered)
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

bool CasaPadrao(const std::string& nome, const std::string& padrao)
{
    const std::string_view textoNome(nome);
    const std::string_view textoPadrao(padrao);
    if (textoNome.compare(0, 7, "#regex#") == 0) {
        return CStringUtils::CasaRegex(nome, padrao);
    }
    if (textoPadrao.compare(0, 7, "#regex#") == 0) {
        return CStringUtils::CasaRegex(padrao, nome);
    }
    if (textoNome.size() != textoPadrao.size()) {
        return false;
    }
    for (size_t i = 0; i < textoNome.size(); ++i) {
        if (textoNome[i] != textoPadrao[i] && !CStringUtils::CasaCaractere(textoPadrao[i], textoNome[i]) &&
            !CStringUtils::CasaCaractere(textoNome[i], textoPadrao[i])) {
            return false;
        }
    }
    return true;
}

namespace {

class CCasaNome {
public:
    explicit CCasaNome(std::string nome) : m_nome(std::move(nome)) {}

    bool operator()(const std::string& padrao) const { return CasaPadrao(m_nome, padrao); }

private:
    std::string m_nome;
};

} // namespace

bool CasamTodos(const std::vector<std::string>& nomes, const std::vector<std::string>& padroes)
{
    if (nomes.empty() || padroes.size() == 0) {
        return false;
    }
    for (const std::string& nome : nomes) {
        if (std::find_if(padroes.begin(), padroes.end(), CCasaNome(nome)) == padroes.end()) {
            return false;
        }
    }
    return true;
}

bool DiretorioContemApenas(const std::string& diretorio, const std::vector<std::string>& padroes)
{
    if (padroes.empty() || !CSystem::ExistDir(diretorio) || CSystem::IsEmptyDir(diretorio)) {
        return false;
    }
    std::vector<std::string> arquivos;
    CDirReader leitor(diretorio);
    while (leitor.NextEntry()) {
        const std::string nome = leitor.GetEntryName();
        if (leitor.IsDir() && nome != "." && nome != "..") {
            return false;
        }
        if (leitor.IsFile()) {
            arquivos.push_back(nome);
        }
    }
    leitor.Close();
    return padroes.size() <= arquivos.size() && CasamTodos(padroes, arquivos) && CasamTodos(arquivos, padroes);
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

long GetMemTotal()
{
    return GetMemInfo("MemTotal");
}

long GetMemFree()
{
    return GetMemInfo("MemFree");
}

std::string GetDirName(const std::string& caminho)
{
    return caminho.substr(0, caminho.rfind('/'));
}

std::string TrocaExtensao(const std::string& arquivo, const std::string& extensao)
{
    const std::string diretorio = GetDirName(arquivo) != arquivo ? GetDirName(arquivo) : "";
    const std::string nome = GetFileName(arquivo);
    const size_t ponto = nome.rfind('.');
    if (ponto == std::string::npos) {
        return arquivo;
    }
    return (!diretorio.empty() ? diretorio + "/" : "") + nome.substr(0, ponto + 1) + extensao;
}

} // namespace api
