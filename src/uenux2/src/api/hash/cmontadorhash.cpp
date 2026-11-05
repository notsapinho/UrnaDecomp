// Reconstruction: of this file (the records name it) CMontadorHash::CriaHashesDiretorio (target fn 5360) with the
// functions binaryen inlines into it (CalculaHash, CalculaHashGeral and the file-static CalculaHashArquivo, which clang
// inlines into CalculaHash), ListaHashesDiretorio (fn 5359) and ListaHashesArquivos (fn 5358). Lines 49, 78, 91, 98 and
// 121 are records of the target; the other lines, the includes and the using-declarations are the reconstruction's
// (src/units/227-uenux2-contratos-cmontadorhash.mk says what each rests on).
#include "api/hash/cmontadorhash.h"

#include <algorithm>
#include <filesystem>
#include <memory>

#include "api/hash/euehasherror.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/util/cdirreader.h"
#include "api/util/csystem.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/security/ihash.hpp"
#include "ecourna/api/security/itextencoding.hpp"

namespace api::hash {

using ecourna::api::security::IHash;
using ecourna::api::security::ITextEncoding;
using namespace std::string_literals;

std::string CMontadorHash::s_hashGeral;

// (original lines 29-46: content not recovered)
#line 47
static const std::vector<uebyte> CalculaHashArquivo(const std::string& arquivo)
{
    std::unique_ptr<IHash> algoritmoHash = CPolySingleton<IGenericFactory<IHash>>::instance().Create();
    ecourna::api::io::CFile entrada(arquivo, "rb");
    uebyte buffer[4096];
    while (!entrada.Eof()) {
        const uedword lidos = entrada.RawRead(buffer, sizeof(buffer));
        if (lidos != 0) {
            algoritmoHash->Update(std::vector<uebyte>(buffer, buffer + lidos));
        }
    }
    return algoritmoHash->Finish();
}

// (original lines 61-74: content not recovered)
#line 75
std::string CMontadorHash::CalculaHash(const std::string& arquivo)
{
    const std::vector<uebyte> hash = CalculaHashArquivo(arquivo);
    std::unique_ptr<ITextEncoding> encoding = CPolySingleton<IGenericFactory<ITextEncoding>>::instance().Create();
    return encoding->Encode(hash);
}

// (original lines 82-84: content not recovered)
#line 85
std::string CMontadorHash::CalculaHashGeral(const std::string& hashGeral, const std::string& hash)
{
    if (hashGeral.empty()) {
        return hash;
    } else {
        std::unique_ptr<IHash> algoritmoHash =
            CPolySingleton<IGenericFactory<IHash>>::instance().Create();
        std::vector<uebyte> dados(hashGeral.begin(), hashGeral.end());
        dados.insert(dados.end(), hash.begin(), hash.end());
        algoritmoHash->Update(dados);
        const std::vector<uebyte> resumo = algoritmoHash->Finish();

        std::unique_ptr<ITextEncoding> encoding =
            CPolySingleton<IGenericFactory<ITextEncoding>>::instance().Create();
        return encoding->Encode(resumo);
    }
}

// (original lines 103-114: content not recovered)
#line 115
CHashDiretorio CMontadorHash::CriaHashesDiretorio(const std::string& diretorio, const std::set<std::string>& excluidos)
{
    CDirReader leitor("");
    std::vector<std::string> arquivos;
    std::vector<std::string> diretorios;
    if (!leitor.Open(diretorio)) {
        throw CUeHashError(EUE_HASH_DIRETORIO_NAO_ABERTO,
            "CMontadorHash::CriaHashesDiretorio - diretório [" + diretorio + "] não pode ser aberto");
    }

    while (leitor.NextEntry()) {
        if (leitor.GetEntryName() == "." || leitor.GetEntryName() == ".." || leitor.GetEntryName() == "lost+found" ||
            leitor.GetEntryName() == "tmp") {
            continue;
        }
        const std::string caminho = diretorio + leitor.GetEntryName() + (leitor.IsDir() ? "/" : "");
        if (excluidos.find(caminho) != excluidos.end()) {
            continue;
        }
        if (leitor.IsLink()) {
            const std::string link = diretorio + leitor.GetEntryName();
            std::filesystem::path destino = std::filesystem::read_symlink(link);
            if (!destino.has_root_directory()) {
                destino = diretorio + destino.string();
            }
            std::filesystem::path canonico = std::filesystem::weakly_canonical(destino);
            const std::filesystem::path alvo = leitor.IsDir() ? canonico.string() + "/"s : canonico.string();
            bool incluido = excluidos.find(alvo) == excluidos.end();
            while (incluido && canonico.has_parent_path()) {
                canonico = canonico.parent_path();
                if (canonico == canonico.root_path()) {
                    break;
                }
                if (excluidos.find(std::filesystem::path(canonico.string() + "/"s)) != excluidos.end()) {
                    incluido = false;
                }
            }
            if (!incluido) {
                continue;
            }
        }
        if (leitor.IsFile()) {
            arquivos.push_back(caminho);
        } else {
            diretorios.push_back(caminho);
        }
    }
    leitor.Close();

    std::sort(arquivos.begin(), arquivos.end());
    std::sort(diretorios.begin(), diretorios.end());

    const std::set<std::string> ignorados = {"uenux.cfg", "avbootcfg.vsu"};
    std::vector<CHashArquivo> hashes;
    for (size_t i = 0; i < arquivos.size(); i++) {
        const std::string hash = CalculaHash(arquivos[i]);
        const std::string nome = GetFileName(arquivos[i]);
        if (ignorados.find(nome) == ignorados.end()) {
            s_hashGeral = CalculaHashGeral(s_hashGeral, hash);
        }
        hashes.push_back(CHashArquivo(nome, hash));
    }

    std::vector<CHashDiretorio> subdiretorios;
    for (size_t i = 0; i < diretorios.size(); i++) {
        subdiretorios.push_back(CriaHashesDiretorio(diretorios[i], excluidos));
    }
    return CHashDiretorio(diretorio, hashes, subdiretorios);
}

std::vector<CHashArquivo> ListaHashesDiretorio(const std::string& diretorio, const std::set<std::string>& excluidos)
{
    return ListaHashesArquivos(CMontadorHash::CriaHashesDiretorio(diretorio, excluidos));
}

std::vector<CHashArquivo> ListaHashesArquivos(const CHashDiretorio& diretorio)
{
    std::vector<CHashArquivo> hashes;
    for (const CHashArquivo& arquivo : diretorio.GetArquivos()) {
        const CHashArquivo hash(diretorio.GetNome() + arquivo.GetNome(), arquivo.GetHash());
        hashes.push_back(hash);
    }
    for (const CHashDiretorio& subdiretorio : diretorio.GetDiretorios()) {
        std::vector<CHashArquivo> hashesSubdiretorio = ListaHashesArquivos(subdiretorio);
        hashes.insert(hashes.end(), hashesSubdiretorio.begin(), hashesSubdiretorio.end());
    }
    return hashes;
}

} // namespace api::hash
