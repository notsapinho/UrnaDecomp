// comum (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp). The
// reconstruction's notes, not TSE's text, are in src/units/214-uenux2-app-comum-comparecimentomesario.mk: the records
// fix ComparaDigitais's lines (65 and 76); every other line is a choice.
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"

#include <algorithm>
#include <filesystem>
#include <format>
#include <functional>
#include <string>
#include <vector>

#include <sys/statfs.h>

#include "api/hwil/ifingermatcher.h"
#include "api/hwil/ifingerscanner.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/log/clogcomum.h"
#include "app/comum/gravadores/pathwsq.h"
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"
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

bool CControladorReconhecimentoMesario::ComparaDigitais(const std::vector<uebyte>& digital,
                                                        const std::vector<uebyte>& outraDigital)
{
    auto& digitais = api::CPolySingleton<api::IFingerScanner>::instance();
    std::vector<uebyte> modelo;
    std::vector<api::SXYT> minucias;
    vota::CParametrosImagemDigital::GetInst().ExtraiTemplate(digital, digitais.Slot2(), digitais.Slot1(), modelo);
    vota::CParametrosImagemDigital::GetInst().ExtraiMinucias(outraDigital, digitais.Slot2(), digitais.Slot1(),
                                                             minucias);

    // (original lines 72-75: content not recovered)
#line 76
    auto& checador = api::CPolySingleton<api::IFingerMatcher>::instance();
    const bool batem = checador.Slot2(modelo, minucias, m_limiar);
    CLogComum::GetInst().LogaScoreReconhecimentoMesario(checador.Slot4());
    return batem;
}

std::unique_ptr<CControladorReconhecimentoMesario> CControladorReconhecimentoMesario::s_inst;
std::mutex CControladorReconhecimentoMesario::s_mutex;

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

bool CControladorReconhecimentoMesario::BiometriaPresenteNoArquivo(const std::vector<uebyte>& digital,
    const std::filesystem::path& diretorio, int idArquivo)
{
    const std::string nome = std::format("me{:06}.wsq", idArquivo);
    const std::filesystem::path caminho = diretorio / nome;
    if (std::filesystem::exists(caminho)) {
        if (ComparaDigitais(digital, ecourna::api::io::CFile::ReadFileBinary(caminho))) {
            return true;
        }
    }
    return false;
}

bool CControladorReconhecimentoMesario::BiometriaPresenteNosRegistrados(const std::vector<uebyte>& digital,
                                                                        int idArquivo)
{
    return BiometriaPresenteNoArquivo(digital, GetPathWsqRegistrado(), idArquivo);
}

bool CControladorReconhecimentoMesario::BiometriaPresenteNosNaoRegistrados(const std::vector<uebyte>& digital)
{
    const std::vector<std::filesystem::path> arquivos = ListaArquivosNaoRegistrados();
    const std::vector<std::filesystem::path> recentes(
        arquivos.begin(), arquivos.begin() + std::min<std::size_t>(arquivos.size(), 6));
    for (const std::filesystem::path& arquivo : recentes) {
        const std::filesystem::path caminho = GetPathWsqNaoRegistrado() / arquivo;
        if (std::filesystem::exists(caminho)) {
            if (ComparaDigitais(digital, ecourna::api::io::CFile::ReadFileBinary(caminho))) {
                return true;
            }
        }
    }
    return false;
}

void CControladorReconhecimentoMesario::SalvarBiometriaMesarioNaoRegistrado(const std::vector<uebyte>& wsq)
{
    const std::function<uint32_t()> geraId = [this]() { return ++m_quantidadeNaoRegistrados; };
    GravaWsq(wsq, GetPathWsqNaoRegistrado(), GetPathWsqNaoRegistradoExterno(), geraId, 5 * 1024 * 1024);
}

} // namespace comum
