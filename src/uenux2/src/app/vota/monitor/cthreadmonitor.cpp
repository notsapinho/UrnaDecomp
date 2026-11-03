#include "app/vota/monitor/cthreadmonitor.h"

#include <cstdint>
#include <format>
#include <future>
#include <string>

#include "api/hwil/ibeep.h"
#include "api/hwil/ipower.h"
#include "api/hwil/iurna.h"
#include "api/util/csystem.h"
#include "api/util/isystemdatetime.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/iinterfaceinit.h"
#include "app/comum/util/cmonitoraalimentacao.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CThreadMonitor& CThreadMonitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadMonitor());
    }
    return *s_inst;
}

std::unique_ptr<CThreadMonitor> CThreadMonitor::s_inst;
std::mutex CThreadMonitor::s_mutex;

// (original lines 37-50: content not recovered)
#line 51
CThreadMonitor::CThreadMonitor()
    : m_fonePlugado(!api::CPolySingleton<api::IPower>::instance().FoneDesconectado())
    , m_ultimoLog(api::ISystemDateTime::GetInst().GetTime())
{
    comum::util::CMonitoraAlimentacao::CreateInst(static_cast<comum::util::ELogAplicativos>(1));
}

CThreadMonitor::~CThreadMonitor() = default;

void CThreadMonitor::Run()
{
    comum::util::CMonitoraAlimentacao& alimentacao = comum::util::CMonitoraAlimentacao::GetInst();
    do {
        alimentacao.VerificaAlimentacao();
        MonitorFoneOuvido();
        if (VotacaoSuspensa()) {
            CLogVota::GetInst().LogaMudancaChaveUrnaDesligada();
            SaiPorVotacaoSuspensa();
        }
        VerificaErrosCriticos();
        const time_t agora = api::ISystemDateTime::GetInst().GetTime();
        if (agora >= m_ultimoLog) {
            LogaEspaco();
            LogaMemoria();
            LogaStatusRedeAcBateria();
            m_ultimoLog = agora + 1800;
        }
        api::CSystem::Dorme(500);
    } while (!PararSolicitado());
}

// (original lines 82-90: content not recovered)
#line 91
bool CThreadMonitor::VotacaoSuspensa()
{
    return api::CPolySingleton<api::IPower>::instance().ChaveDesligada();
}

void CThreadMonitor::SaiPorVotacaoSuspensa()
{
    CSincronizaVota::MarcaUrnaDesligando();
    ParaOutrasThreads();

    // (original lines 101-102: content not recovered)
#line 103
    (void)std::async(std::launch::async, []() { api::CPolySingleton<api::IBeep>::instance().BeepAlert(); });
}

// (original lines 106-124: content not recovered)
#line 125
void CThreadMonitor::MonitorFoneOuvido()
{
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    const bool fonePlugado = !ipower.FoneDesconectado();
    if (fonePlugado != m_fonePlugado) {
        CLogVota::GetInst().loga(fonePlugado ? "Fone de ouvido conectado" : "Fone de ouvido desconectado");
        m_fonePlugado = fonePlugado;
    }
}

// (original lines 135-150: content not recovered)
#line 151
void CThreadMonitor::VerificaErroCriticoFlash()
{
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    if (comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() != comum::FASE_TREINAMENTO) {
        if (ipower.MidiaExternaAusente()) {
            throw CUeVotaError(EUE_VOTA_MIDIA_EXTERNA_AUSENTE, "Erro na Mídia Externa - Mídia não está presente");
        }
    }
}

// (original lines 161-162: content not recovered)
#line 163
void CThreadMonitor::VerificaErroCriticoKbdTE()
{
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    if (ipower.TecladoEleitorDesconectado()) {
        throw CUeVotaError(EUE_VOTA_TECLADO_ELEITOR_DESCONECTADO, "Erro no teclado do eleitor - dispositivo desconectado");
    }
}

void CThreadMonitor::VerificaErrosCriticos()
{
    VerificaErroCriticoFlash();
    VerificaErroCriticoKbdTE();
}

// (original lines 177-211: content not recovered)
#line 212
void CThreadMonitor::LogaEspaco() const
{
    try {
        const uintmax_t livreMI = api::GetFreeSpace(comum::CPath::GetPathDinamico(comum::FLASH_INTERNA));
        const uintmax_t livreMV = api::GetFreeSpace(comum::CPath::GetPathDinamico(comum::FLASH_EXTERNA));
        const uintmax_t usadoMI = api::GetUsedSpace(comum::CPath::GetPathDinamico(comum::FLASH_INTERNA));
        const uintmax_t usadoMV = api::GetUsedSpace(comum::CPath::GetPathDinamico(comum::FLASH_EXTERNA));

        CLogVota::GetInst().LogaEspacoLivreMI(livreMI);
        CLogVota::GetInst().LogaEspacoLivreMV(livreMV);
        CLogVota::GetInst().LogaEspacoUtilizadoMI(usadoMI);
        CLogVota::GetInst().LogaEspacoUtilizadoMV(usadoMV);

        api::CPolySingleton<comum::IInterfaceInit>::instance().LogDiskInfo();
    } catch (...) {
    }
}

void CThreadMonitor::LogaMemoria() const
{
    const uint64_t total = api::GetMemTotal();
    const uint64_t livre = api::GetMemFree();
    CLogVota::GetInst().LogaQuantidade({"memória total", total * 1024});
    CLogVota::GetInst().LogaQuantidade({"memória livre", livre * 1024});
    CLogVota::GetInst().LogaQuantidade({"memória usada", (total - livre) * 1024});
}

// (original lines 239-255: content not recovered)
#line 256
void CThreadMonitor::LogaStatusRedeAcBateria() const
{
    auto modeloUrna = api::CPolySingleton<api::IUrna>::instance().Modelo();
    if (modeloUrna < 2020) return;
    api::IPower& energia = api::CPolySingleton<api::IPower>::instance();
    const uebyte fonte = energia.Fonte();
    const int tensaoRede = energia.AcVoltage();
    const int tensaoBatExt = energia.BatExtVoltage();
    const int tensaoBat = tensaoBatExt <= 0 ? energia.BatIntVoltage() : energia.BatExtVoltage();
    const int corrente = energia.BatCurrent();

    std::string mensagem = "Urna ligada ";
    const std::string conexao = fonte != 0 ? "desconectada da" : "conectada na";
    mensagem += std::format("{} rede CA em [{:3.2f}V] e ", conexao, tensaoRede / 100.0);
    const double amperes = corrente / 100.0;
    const double tensao = tensaoBat / 100.0;
    if (tensaoBatExt <= 0) {
        mensagem += std::format("na Bateria Interna com [{:2.2f}V/{}A]", tensao, amperes);
    } else {
        mensagem += std::format("na Bateria Externa com [{:2.2f}V/{}A]", tensao, amperes);
    }
    CLogVota::GetInst().loga(mensagem);
}

void CThreadMonitor::ParaOutrasThreads()
{
    CThreadOperador::GetInst().Stop();
    CThreadEleitor::GetInst().Stop();
}

} // namespace vota
