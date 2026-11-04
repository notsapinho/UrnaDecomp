// comum (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp): the list of
// the files of the WSQ directory "nao-registrado/" in reverse name order, target fn 5374, and with it the libc++ code
// of its std::sort the target keeps: __introsort (fn 5373), __insertion_sort_incomplete (fn 5370), __sort4 (fn 2726)
// and the comparator (fn 310). No record names fn 5374: its name, its being a free function and its line are chosen,
// and its file is its band's. comum::CControladorReconhecimentoMesario's constructor, GetInst (fn 1149) and its
// statics follow, their lines a choice; the statics below GetInst give the target's .bss order. The records of
// CControladorReconhecimentoMesario::ComparaDigitais (fn 5372, lines 65 and 76) are not written. After them, their
// lines a choice: PREFIXO_MESARIO and ArmazenaImagemMesario, SalvarBiometriaMesarioRegistrado (all three held by fn
// 5382) and GravaWsq (fn 5371). src/units/214-uenux2-app-comum-comparecimentomesario.mk says what each part rests on.
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"

#include <algorithm>
#include <filesystem>
#include <format>
#include <functional>
#include <string>
#include <vector>

#include <sys/statfs.h>

#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/gravadores/pathwsq.h"
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"
#include "api/io/cfile.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

std::vector<std::filesystem::path> ListaArquivosNaoRegistrados()
{
    const std::filesystem::path diretorio = GetPathWsqNaoRegistrado();
    std::vector<std::filesystem::path> arquivos;
    std::ranges::for_each(std::filesystem::directory_iterator(diretorio),
                          [&arquivos](const std::filesystem::directory_entry& entrada) {
                              if (!entrada.is_directory()) {
                                  arquivos.push_back(entrada.path().filename());
                              }
                          });
    std::sort(arquivos.begin(), arquivos.end(),
              [](const std::filesystem::path& a, const std::filesystem::path& b) { return a.string() > b.string(); });
    return arquivos;
}

CControladorReconhecimentoMesario::CControladorReconhecimentoMesario()
    : m_dedo(static_cast<md::CDedo::TipoDedo>(0))
    , m_limiar(20)
    , m_estadoBiometria(static_cast<md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(1))
    , m_idArquivo()
    , m_quantidadeNaoRegistrados(ListaArquivosNaoRegistrados().size())
{
}

CControladorReconhecimentoMesario& CControladorReconhecimentoMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CControladorReconhecimentoMesario());
    }
    return *s_inst;
}

std::unique_ptr<CControladorReconhecimentoMesario> CControladorReconhecimentoMesario::s_inst;
std::mutex CControladorReconhecimentoMesario::s_mutex;

// <stubs>
// f5372 · 720 B · unmatched · name unknown
// ? f5372(i32) { ... }
// </stubs>










const std::string PREFIXO_MESARIO = "me";

uint32_t ArmazenaImagemMesario(const std::vector<uebyte>& wsq, const std::string& titulo)
{
    const std::string nomeArquivo = ecourna::api::util::CStringUtils::PreencheAEsquerda(titulo, '0', 12) + "_Operador";
    const std::filesystem::path diretorio = GetPathWsqOperador();
    const std::filesystem::path diretorioExterno = GetPathWsqOperadorExterno();
    return CControlaArmazenamentoDeImagens::ArmazenaImagem(wsq, nomeArquivo, diretorio, diretorioExterno,
        PREFIXO_MESARIO);
}

void CControladorReconhecimentoMesario::SalvarBiometriaMesarioRegistrado(const std::vector<uebyte>& wsq,
                                                                         const std::string& titulo)
{
    const uint32_t id = ArmazenaImagemMesario(wsq, titulo);
    if (id == CControlaArmazenamentoDeImagens::ID_INVALIDO) {
        return;
    }
    const std::function<uint32_t()> geraId = [&id]() { return id; };
    GravaWsq(wsq, GetPathWsqRegistrado(), GetPathWsqRegistradoExterno(), geraId, 5 * 1024 * 1024);
}

void CControladorReconhecimentoMesario::GravaWsq(const std::vector<uebyte>& wsq, const std::filesystem::path& diretorio,
    const std::filesystem::path& diretorioExterno, const std::function<uint32_t()>& geraId, double espacoMinimo)
{
    std::string nome;
    struct statfs estado;
    if (statfs(CPath::GetPathDinamico(FLASH_EXTERNA).c_str(), &estado) == 0) {
        if (!(static_cast<double>(estado.f_bavail) * estado.f_bsize >= espacoMinimo)) {
            return;
        }
    }
    int id;
    std::filesystem::path caminho;
    std::filesystem::path caminhoExterno;
    do {
        id = geraId();
        nome = std::format("me{:06}.wsq", id);
        caminho = diretorio / nome;
        caminhoExterno = diretorioExterno / nome;
    } while (api::CSystem::ExistFile(caminho));
    m_idArquivo = id;
    api::CFile arquivo(caminho, "w+b", ecourna::api::io::FM_NOATIME);
    arquivo.Write(wsq);
    arquivo.Close();
    api::CSystem::CopyFile(caminho, caminhoExterno, false, true);
}

} // namespace comum
