// comum::CLogComum (/home/rubio/tse/uenux2/src/app/comum/log/clogcomum.cpp). Its records are records of the target:
//   5878  LogaCopiandoArqResParaFI(EExtensaoArquivoResultado)                              record at line 76, column 18
//   3828  LogaResultadoCopiadoResFE(EExtensaoArquivoResultado)                             record at line 84, column 18
//   5876  LogaGerandoResultados(EExtensaoArquivoResultado, EStatusOperacaoRelatorio)       record at line 92, column 25 (written, unmatched)
//   5875  LogaNivelBateria(uebyte, uebyte)                                                 record at line 106, column 18
//         LogaSuspensoMonitoramenteRepeticao(uebyte)                                     record at line 136, column 18
//         LogaTipoBateria()                                                              records at lines 144, 145, 158
//         LogaScoreReconhecimentoMesario(const ueint32)                                  record at line 214, column 18
//         the session members and the signing ones                                   records listed below
// (the last four rows have no target index: binaryen inlined the first two into fn 10226, vota::CThreadMonitor's
// slot 2, the third into fn 5372, comum::CControladorReconhecimentoMesario::ComparaDigitais, the seven into fn 12098)
// The seven's records: lines 44, 50, 56, 62, 166, 172, 178. The reconstruction's notes are in unit 111's fragment.

#include "app/comum/log/clogcomum.h"

#include <format>
#include <string>

#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/log/euecomumlogerror.h"
#include "app/comum/log/ieventoslog.h"

namespace comum {

CLogComum& CLogComum::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_instancia) {
        s_instancia.reset(new CLogComum);
    }
    return *s_instancia;
}

std::unique_ptr<CLogComum> CLogComum::s_instancia;
std::mutex CLogComum::s_mutex;

CLogComum::CLogComum() = default;

CLogComum::~CLogComum() = default;

void CLogComum::LogaIniciaSessaoMSD()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Inicia uma sessão no MSD");
}

void CLogComum::LogaFinalizaSessaoMSD()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Finaliza a sessão no MSD");
}

void CLogComum::LogaIniciaSessaoMSE()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Inicia uma sessão no MSE");
}

void CLogComum::LogaFinalizaSessaoMSE()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Finaliza a sessão no MSE");
}

// (original lines 66-73: content not recovered)
#line 74
void CLogComum::LogaCopiandoArqResParaFI(EExtensaoArquivoResultado extensao)
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    const std::string mensagem = std::format("Copiando arquivo de resultado para MI: [{}]", CArquivosResultado::GetInst()[extensao]);
    logs.loga(mensagem);
}


void CLogComum::LogaResultadoCopiadoResFE(EExtensaoArquivoResultado extensao)
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    const std::string mensagem = std::format("Copiando arquivo de resultado para ME: [{}]", CArquivosResultado::GetInst()[extensao]);
    logs.loga(mensagem);
}


void CLogComum::LogaGerandoResultados(EExtensaoArquivoResultado extensao, EStatusOperacaoRelatorio status)
{
    IEventosLog& logs = api::CPolySingleton<IEventosLog>::instance();
    const std::string etapa = status ? "Término" : "Início";
    const std::string mensagem = std::format("Gerando arquivo de resultado [{}] + [{}]", CArquivosResultado::GetInst()[extensao], etapa);
    logs.loga(mensagem);
}

// (original lines 98-103: content not recovered)
#line 104
void CLogComum::LogaNivelBateria(uebyte fonte, uebyte status)
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.LogaCargaBateria(fonte, status);
}

// (original lines 110-133: content not recovered)
#line 134
void CLogComum::LogaSuspensoMonitoramenteRepeticao(uebyte eventos)
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga(std::format("Suspenso monitoramento de alimentação devido repetição de eventos. [ {} ] eventos", eventos));
}

// (original lines 140-141: content not recovered)
#line 142
void CLogComum::LogaTipoBateria()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    const uebyte fonte = ipower.Fonte();
    switch (fonte) {
        case 0:
            logs.loga("Urna operando na rede elétrica");
            break;
        case 1:
            logs.loga("Urna operando na bateria interna");
            break;
        case 2:
            logs.loga("Urna operando na bateria externa");
            break;
        default:
            throw CUeComumLogError(EUE_COMUM_LOG_8850, "Tipo de alimentação não implementado");
    }
}

// (original lines 162-163: content not recovered)
#line 164
void CLogComum::LogaInicioProcedimentoAssinatura()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Início do procedimento de assinatura dos arquivos de resultados");
}

void CLogComum::LogaTerminoProcedimentoAssinatura()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Término do procedimento de assinatura dos arquivos de resultados");
}

void CLogComum::LogaPreparandoAssinaturaArquivosResultado()
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga("Preparando para assinatura dos arquivos de resultados");
}

// (original lines 182-211: content not recovered)
#line 212
void CLogComum::LogaScoreReconhecimentoMesario(const ueint32 score)
{
    auto& logs = api::CPolySingleton<IEventosLog>::instance();
    logs.loga(std::format("Batimento de digitais retornou o score {}", score));
}

} // namespace comum
