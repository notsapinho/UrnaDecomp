#include "api/util/cdirreader.h"

#include <sys/stat.h>

#include "api/util/eueutilerror.h"

namespace api {

// (original lines 9-24: content not recovered)
#line 25
CDirReader::CDirReader(const std::string& diretorio)
{
    if (!diretorio.empty()) {
        Open(diretorio);
        if (m_dir == nullptr) {
            throw CUeUtilError(EUE_UTIL_FALHA_LER_DIRETORIO, "Não foi possível ler o diretório " + diretorio);
        }
    }
}

CDirReader::~CDirReader()
{
    Close();
}

bool CDirReader::NextEntry()
{
    if (m_dir == nullptr) {
        throw CUeUtilError(EUE_UTIL_DIRETORIO_NAO_ABERTO, "O diretório não está aberto");
    }

    m_entrada = readdir(m_dir);
    return m_entrada != nullptr;
}

bool CDirReader::Open(const std::string& diretorio)
{
    DIR* dir = opendir(diretorio.c_str());
    if (dir != nullptr) {
        Close();
        m_diretorio = diretorio;
        m_dir = dir;
        m_entrada = nullptr;
    }
    return dir != nullptr;
}

void CDirReader::Close()
{
    if (m_dir != nullptr) {
        closedir(m_dir);
        m_diretorio.clear();
        m_dir = nullptr;
        m_entrada = nullptr;
    }
}

bool CDirReader::IsDir() const
{
    const dirent* entrada = m_entrada;
    if (entrada == nullptr) {
        return false;
    }
    const std::string caminho = m_diretorio + '/' + entrada->d_name;
    struct stat info;
    return stat(caminho.c_str(), &info) != -1 && S_ISDIR(info.st_mode);
}

bool CDirReader::IsFile() const
{
    const dirent* entrada = m_entrada;
    if (entrada == nullptr) {
        return false;
    }
    const std::string caminho = m_diretorio + '/' + entrada->d_name;
    struct stat info;
    return stat(caminho.c_str(), &info) != -1 && S_ISREG(info.st_mode);
}

bool CDirReader::IsLink() const
{
    const dirent* entrada = m_entrada;
    if (entrada == nullptr) {
        return false;
    }
    const std::string caminho = m_diretorio + '/' + entrada->d_name;
    struct stat info;
    return lstat(caminho.c_str(), &info) != -1 && S_ISLNK(info.st_mode);
}

} // namespace api
