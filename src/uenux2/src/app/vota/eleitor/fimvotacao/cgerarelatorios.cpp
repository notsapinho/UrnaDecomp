#include "app/vota/eleitor/fimvotacao/cgerarelatorios.h"

#include "api/gui/capplication.h"
#include "api/gui/iform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/comparecimentomesario/estados/cimprimiridentificacaomesariosfinal.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/comum/relatorios/cgeradorbuj.h"
#include "app/comum/relatorios/cgeradorreleleitoreshabbiograf.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/ciniciobu.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CGeraRelatorios::CGeraRelatorios()
    : comum::CAppState(),
      m_telaPreparandoDados(TelaPreparandoDadosEncerramento())
{
}

CGeraRelatorios::~CGeraRelatorios() = default;

CGeraRelatorios& CGeraRelatorios::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraRelatorios());
    }
    return *s_inst;
}

std::unique_ptr<CGeraRelatorios> CGeraRelatorios::s_inst;
std::mutex CGeraRelatorios::s_mutex;

void GeraRelatorioBUJ();
void GeraRelatorioBIM();
void GeraRelatorioBEHB();

void CGeraRelatorios::StartState()
{
    CAppInfo& poInfo = CAppInfo::GetInst();
    ASSERT(poInfo.GetVota().GetEstadoVota() == EAVGERARRELATORIOS, api::EUA_GERARELATORIOS_EST_INVALIDO);
    m_telaPreparandoDados->Slot2();
    CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_BUJ, false);
    GeraRelatorioBUJ();
    CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_BUJ, true);
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.ImprimeBJust()) {
        CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_BIM, false);
        GeraRelatorioBIM();
        CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_BIM, true);
    }
    const CLocal& local = CLocal::GetInst();
    if (!informacao.EhModoDemonstracao() && local.UrnaBiometrica()) {
        CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE, false);
        GeraRelatorioBEHB();
        CLogVota::GetInst().LogaGerandoRelatorio(RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE, true);
    }
    poInfo.GetVota().SetEstadoVota(EAVIMPRIMIRBU);
    CSincronizaVota::SincronizaEstadoGeralVota();
    m_pNextState = &CInicioBU::GetInst();
}

void GeraRelatorioBUJ()
{
    const md::estadoaplicacao::CLocalidadeEleitoral secao =
        CAppInfo::GetInst().GetGeral().GetDadoLocal().GetSecaoCarga();
    const CLocal& local = CLocal::GetInst();
    const std::string titulo = "Boletim de Justificativa Eleitoral";
    const std::string separador = CRelUtil::GetSeparadorFase(CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase());
    CGeradorBUJ gerador(titulo, separador, secao.GetMunicipio(), secao.GetZona(), secao.GetSecao(),
                        local.GetNomeMunicipio(), CAppInfo::GetInst().GetGeral().GetCorrespondencia());
    const std::string arquivo = "buj.dat";
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(
        2, "", "Gerando boletim de justificativa na MI",
        "Ocorreu um erro durante a geração do boletim de justificativa na MI.");
    gerador.GeraBUJ((CPath::GetPathTrab(FLASH_INTERNA) / arquivo).string());
    CSincronizaVota::SincronizaRelatorios(arquivo);
}

void GeraRelatorioBIM()
{
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(
        2, "", "Gerando boletim de mesários na MI",
        "Ocorreu um erro durante a geração do boletim de mesários na MI.");
    CImprimirIdentificacaoMesariosFinal boletim(true);
    boletim.Imprime((CPath::GetPathTrab(FLASH_INTERNA) / "bim.dat").string());
    CSincronizaVota::SincronizaRelatorios("bim.dat");
}

void GeraRelatorioBEHB()
{
    const api::CApplicationContextGuard guarda = api::CApplication::CriaContexto(
        2, "", "Gerando relatório de eleitores habilitados biograficamente",
        "Ocorreu um erro durante a geração do relatório de eleitores habilitados biograficamente na MI.");
    const CGeradorRelEleitoresHabBiograf gerador;
    gerador.Gera(CPath::GetPathTrab(FLASH_INTERNA) / "behb.dat");
    CSincronizaVota::SincronizaRelatorios("behb.dat");
}

} // namespace vota
