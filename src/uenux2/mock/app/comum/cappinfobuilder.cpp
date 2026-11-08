// Reconstruction's notes, not TSE's text. The members of comum::teste::CAppInfoBuilder whose records this file holds
// (lines 112, 277 and 287, each the default std::source_location of a Converte call, at the call's column), the two
// converters they call and the file writer. The TU compiles at the executable TU's rule, -Oz -fexceptions (its landing
// pads are the target's), its object right after that TU's on the link line; src/units/253-uenux2-cappinfobuilder.mk
// has the evidence, the measurements and what each member waits for. Every line but the records' is chosen, and so
// are the converters' and the writer's names.

#include "cappinfobuilder.h"

#include <filesystem>
#include <fstream>
#include <source_location>
#include <stdexcept>
#include <string>

#include "app/comum/appinfo/servicos/cservicoestadogeral.h"
#include "app/comum/appinfo/servicos/cservicoestadogeralgap.h"
#include "app/comum/appinfo/servicos/cservicoestadogeralsa.h"
#include "app/comum/appinfo/servicos/cservicoestadogeralvota.h"
#include "app/comum/cpath.h"

namespace comum::teste {

EFlashOrigem Converte(EMidia midia, std::source_location local = std::source_location::current())
{
    switch (midia) {
    case EMidia::INTERNA:
        return FLASH_INTERNA;
    case EMidia::EXTERNA:
        return FLASH_EXTERNA;
    }
    throw std::logic_error(std::format("Converte - midia invalida [{}] da linha [{}]", midia, local.line()));
}

int Converte(EUrnaTurno turno, std::source_location local = std::source_location::current())
{
    switch (turno) {
    case TURNO_1:
        return 0;
    case TURNO_2:
        return 1;
    default:
        break;
    }
    throw std::logic_error(std::format("Converte - turno invalido [{}] da linha [{}]", turno, local.line()));
}

void GravaArquivo(const std::string& arquivo, const std::string& conteudo)
{
    std::filesystem::create_directories(std::filesystem::path(arquivo).parent_path());
    std::ofstream saida(arquivo, std::ios::binary);
    saida << conteudo;
}

std::vector<EApp> TodosApps()
{
    return {EApp::GAP, EApp::SA, EApp::VOTA};
}

CAppInfoBuilder::CAppInfoBuilder(uedword idPE)
{
    m_geral.m_idPE = idPE;
}

CAppInfoBuilder& CAppInfoBuilder::SalvaTudo(bool assina, std::vector<EMidia> midias)
{
    return SalvaGeral(assina, midias)
        .SalvaAppsTurno1(assina, midias, TodosApps())
        .SalvaAppsTurno2(assina, midias, TodosApps());
}

// (original lines 72-108: content not recovered)
#line 109
CAppInfoBuilder& CAppInfoBuilder::SalvaGeral(bool assina, std::vector<EMidia> midias)
{
    for (auto midia : midias) {
        const EFlashOrigem origem = Converte(midia);
        if (assina) {
            GravaArquivo(CPath::GetPathDinamico(origem) / "eg.vsu", "assinatura EG");
        }
        CServicoEstadoGeral(origem).Salva(md::estadoaplicacao::CEstadoGeral(m_geral));
    }
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SalvaAppsTurno1(bool assina, std::vector<EMidia> midias, std::vector<EApp> apps)
{
    return SalvaApps(assina, midias, TURNO_1, apps);
}

CAppInfoBuilder& CAppInfoBuilder::SalvaAppsTurno2(bool assina, std::vector<EMidia> midias, std::vector<EApp> apps)
{
    return SalvaApps(assina, midias, TURNO_2, apps);
}

// (original lines 131-272: content not recovered)
#line 273
CAppInfoBuilder& CAppInfoBuilder::SalvaApps(bool assina, std::vector<EMidia> midias, EUrnaTurno turno,
                                             std::vector<EApp> apps)
{
    for (auto midia : midias) {
        const auto flash = Converte(midia);
        for (auto app : apps) {
            SalvaApp(assina, flash, turno, app);
        }
    }
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SalvaApp(bool assina, EFlashOrigem origem, EUrnaTurno turno, EApp app)
{
    const auto idx = Converte(turno);
    const auto pathTrab = CPath::GetPathTrab(origem, turno);
    switch (app) {
    case EApp::GAP:
        if (assina) {
            GravaArquivo(pathTrab / "gap.vsu", "assinatura EG Gap");
        }
        CServicoEstadoGeralGap(origem, turno).Salva(md::estadoaplicacao::CEstadoGeralGap(m_gap[idx]));
        break;
    case EApp::SA:
        if (assina) {
            GravaArquivo(pathTrab / "sa.vsu", "assinatura EG SA");
        }
        CServicoEstadoGeralSA(origem, turno).Salva(md::estadoaplicacao::CEstadoGeralSA(m_sa[idx]));
        break;
    case EApp::VOTA:
        if (assina) {
            GravaArquivo(pathTrab / "vota.vsu", "assinatura EG Vota");
        }
        CServicoEstadoGeralVota(origem, turno).Salva(md::estadoaplicacao::CEstadoGeralVota(m_vota[idx]));
        break;
    }
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SetFase(EUrnaFase fase)
{
    m_geral.m_dadoCarga.m_fase = fase;
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SetTurno(EUrnaTurno turno)
{
    m_geral.m_dadoCarga.m_turno = turno;
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SetTipoUrna(EUrnaTipo tipo)
{
    m_geral.m_dadoCarga.m_tipoUrnaT1 = tipo;
    m_geral.m_dadoCarga.m_tipoUrnaT2 = tipo;
    return *this;
}

CAppInfoBuilder& CAppInfoBuilder::SetLocalidade(uedword municipio, ueword zona, ueword secao)
{
    m_geral.m_dadoLocal.m_secaoCarga.m_municipio = municipio;
    m_geral.m_dadoLocal.m_secaoCarga.m_zona = zona;
    m_geral.m_dadoLocal.m_secaoCarga.m_secao = secao;
    return *this;
}

} // namespace comum::teste
