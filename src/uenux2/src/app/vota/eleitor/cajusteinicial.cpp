// vota::CAjusteInicial, and vota::IAjusteInicial::GetInst (records cajusteinicial.cpp:57 to :245). The reconstruction's
// note, not TSE's text: src/units/329-uenux2-cajusteinicial.mk says what is evidence and what is chosen, the lines of
// the functions no record places among them.
#include "app/vota/eleitor/cajusteinicial.h"

#include <format>
#include <memory>
#include <string>

#include "api/pattern/cpolysingleton.h"
#include "api/pattern/cpolysingletonlist.h"
#include "api/util/cdatetime.h"
#include "api/util/cdirreader.h"
#include "api/util/csystem.h"
#include "api/util/iajustedatahora.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/iinterfaceinit.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"
#include "app/vota/eleitor/fimvotacao/ccopiaresultadoparamr.h"
#include "app/vota/eleitor/fimvotacao/cfinalizaaquisicao.h"
#include "app/vota/eleitor/fimvotacao/cgerabu.h"
#include "app/vota/eleitor/fimvotacao/cgerarelatorios.h"
#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"
#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"
#include "app/vota/eleitor/fimvotacao/ciniciobu.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"
#include "app/vota/eleitor/fimvotacao/cverificaqtdbusadicionais.h"
#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"
#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.h"
#include "app/vota/eleitor/iniciovotacao/cverificaeleicaopassou.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CAjusteInicial::CAjusteInicial() = default;

// (original lines 46-51: content not recovered)
#line 52
IAjusteInicial& IAjusteInicial::GetInst()
{
    if (!api::CPolySingletonList::has<IAjusteInicial>()) {
        api::CPolySingleton<IAjusteInicial>::set(std::unique_ptr<IAjusteInicial>(new CAjusteInicial));
    }
    return api::CPolySingleton<IAjusteInicial>::instance();
}

// (original lines 60-67: content not recovered)
#line 68
void CAjusteInicial::ValidaTemposDesligamento()
{
    const int tempoDesligamento = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoDesligamentoAutomatico();
    const int tempoAviso = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoAvisoDesligamentoAutomatico();

    if (tempoDesligamento <= 0) {
        throw CUeVotaError(EUE_VOTA_TEMPO_LIMITE_BATERIA_INTERNA_INVALIDO, "Tempo limite de uso de bateria interna inválido");
    }


    if (tempoAviso <= 0) {
        throw CUeVotaError(EUE_VOTA_TEMPO_AVISO_DESLIGAMENTO_INVALIDO, "Tempo de aviso de desligamento por uso da bateria interna inválido");
    }


    if (tempoDesligamento < tempoAviso) {
        throw CUeVotaError(EUE_VOTA_TEMPO_AVISO_DESLIGAMENTO_MAIOR_QUE_LIMITE, "Tempo de aviso de desligamento não pode ser maior que o tempo para desligar a urna");
    }
}

// (original lines 88-111: content not recovered)
#line 112
void CAjusteInicial::InicioVota()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    const comum::md::estadoaplicacao::CEstadoGeralVota& vota = appInfo.GetVota();
    const comum::EEstadoVota estadoVota = vota.GetEstadoVota();
    const comum::EEstadoEncerramento estadoEncerramento = vota.GetEstadoEncerramento();
    switch (estadoVota) {
        case comum::EAVINICIAL:
        case comum::EAVGERADADOSDINAMICOS:
        case comum::EAVAGUARDAHORAZERESIMA:
            m_pNextState = &CVerificaEleicaoPassou::GetInst();
            break;
        case comum::EAVGERARZE:
            m_pNextState = &CInicioZeresima::GetInst();
            break;
        case comum::EAVZERESIMAGERADA:
            m_pNextState = &CImprimindoZeresima::GetInst();
            break;
        case comum::EAVZERESIMAIMPRESSA:
        case comum::EAVREGISTROMESARIOINICIAL:
        case comum::EAVVOTAR:
            m_pNextState = &testeteclado::CRetomada::GetInst();
            break;
        case comum::EAVFIMAQUISICAOVOTOS:
            m_pNextState = &CFinalizaAquisicao::GetInst();
            break;
        case comum::EAVREGISTROMESARIOFINAL:
            m_pNextState = &CReinicioComparecimentoMesario::GetInst();
            break;
        case comum::EAVGERARBU:
            m_pNextState = &CGeraBU::GetInst();
            break;
        case comum::EAVGERARRELATORIOS:
            m_pNextState = &CGeraRelatorios::GetInst();
            break;
        case comum::EAVIMPRIMIRBU:
            m_pNextState = &CInicioBU::GetInst();
            break;
        case comum::EAVGRAVARRESULTADOS:
            m_pNextState = &CGravaResultado::GetInst();
            break;
        case comum::EAVCOPIARESULTADOSMR:
            m_pNextState = &CCopiaResultadoParaMR::GetInst();
            break;
        case comum::EAVENCERRADA:
            switch (estadoEncerramento) {
                case comum::EAEINICIAL:
                case comum::EAEIMPRIMIROBRIGATORIABU:
                    m_pNextState = &CImprimirBUOutrasObrigatorias::GetInst();
                    break;
                case comum::EAERETIRAMR:
                    m_pNextState = &CRetirarMR::GetInst();
                    break;
                case comum::EAEFIMDOSTRABALHOS:
                    m_pNextState = &CVerificaQtdBUsAdicionais::GetInst();
                    break;
                default:
                    CLogVota::GetInst().LogaErroEstadoAplicativoDesconhecido();
                    throw CUeVotaError(EUE_VOTA_AJUSTE_INICIAL_ESTADO_ENCERRAMENTO_DESCONHECIDO,
                                       std::format("Estado encerramento nao conhecido = {}", estadoEncerramento));
            }
            break;


        default:
            CLogVota::GetInst().LogaErroEstadoAplicativoDesconhecido();
            throw CUeVotaError(EUE_VOTA_AJUSTE_INICIAL_ESTADO_DESCONHECIDO, std::format("Estado nao conhecido = {}", estadoVota));
    }
}

// (original lines 182-184: content not recovered)
#line 185
void CAjusteInicial::LimpaMidiaResultado()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetGeral().GetDadoCarga().GetFase() != comum::FASE_TREINAMENTO || appInfo.GetVota().GetTreinamentoEleitor()) {
        return;
    }
    comum::IInterfaceInit& interface = api::CPolySingleton<comum::IInterfaceInit>::instance();
    interface.HabilitarMR();
    if (!interface.IsMRPresenteSemHabilitar()) {
        CLogVota::GetInst().LogaMidiaResultadoAusente();
        return;
    }
    interface.HabilitarMR();
    if (interface.IsMRMontadoSemHabilitar()) {
        interface.DesmontarMRSemDesabilitar();
        interface.DesabilitarMR();
    }
    interface.HabilitarMR();
    interface.MontarMRSemHabilitar();
    std::unique_ptr<api::CDirReader> leitor(AbreDiretorio(comum::CPath::GetPathMR()));
    if (leitor) {
        while (leitor->NextEntry()) {
            const std::string nome = leitor->GetEntryName();
            if (nome.compare(0, 9, "infomidia") != 0 && nome.compare(0, 6, "turno2") != 0) {
                api::CSystem::RemoveFile((comum::CPath::GetPathMR() / nome).string());
            }
        }
    }
}

void CAjusteInicial::AjustaDataHora()
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();


    const bool demonstracaoAtiva = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    const bool treinamento = appInfo.GetGeral().GetDadoCarga().GetFase() == comum::FASE_TREINAMENTO;
    if (demonstracaoAtiva || treinamento) {
        comum::CAppInfo& appInfoGeral = comum::CAppInfo::GetInst();
        comum::md::estadoaplicacao::CEstadoGeral& geral = appInfoGeral.GetGeral();
        const comum::EEstadoVota estadoVota = appInfoGeral.GetVota().GetEstadoVota();
        const comum::CConfiguracaoEleicao& configuracao = comum::CConfiguracaoEleicao::GetInst();
        const time_t agora = api::CDateTime::Now().ConvertToLocalTime();
        api::CDateTime dataHora;
        if (estadoVota <= comum::EAVREGISTROMESARIOINICIAL) {
            if (appInfo.GetVota().GetTreinamentoEleitor()) {
                dataHora = configuracao.GetDataHoraInicioVotacao();
            } else {
                const api::CDateTime zeresima = configuracao.GetDataHoraZeresima();
                dataHora = api::CDateTime(zeresima.GetData(), zeresima.GetHora() - 30);
            }
            const time_t nova = dataHora.ConvertToLocalTime();
            comum::md::estadoaplicacao::CAjusteDataHora ajuste = geral.GetAjusteDataHora();
            ajuste.AdicionaDeltaT(nova - agora);
            geral.SetAjusteDataHora(ajuste);

            // (original lines 241-244: content not recovered)
#line 245
            api::CPolySingleton<api::IAjusteDataHora>::instance().Ajusta(dataHora);
            CSincronizaVota::SincronizaEstadoGeral();
        }
    }
}

void CriaControladorRegistraMesarios()
{
    api::TPolySingletonsInfo& info = api::g_polySingletonsInfo();
    std::unique_ptr<comum::IControladorRegistraMesarios> controlador(new CControladorRegistraMesariosVota);
    api::CPolySingletonList::set(std::move(controlador), info);
}

void CAjusteInicial::StartState()
{
    AjustaDataHora();
    ValidaTemposDesligamento();
    LimpaMidiaResultado();
    if (comum::CInformacaoEleicao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna()).ImprimeBJust() &&
        !api::CPolySingletonList::has<comum::IControladorRegistraMesarios>()) {
        CriaControladorRegistraMesarios();
    }
    InicioVota();
}

} // namespace vota
