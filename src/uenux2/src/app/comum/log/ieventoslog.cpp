// comum::IEventosLog (/home/rubio/tse/uenux2/src/app/comum/log/ieventoslog.cpp). Its records are records of the target:
//   5879  ConverteERelatoriosUE(const ERelatoriosUE)  record at line 426, column 19
//   5875  (fn of CLogComum) ConverteFonteAlim(const uebyte), ConverteStatusBateria(const uebyte)  records at lines 440, 456
// The reconstruction's notes are in unit 111's fragment.

#include "app/comum/log/ieventoslog.h"

#include <format>

#include "api/uelog/cloga.h"
#include "app/comum/log/euecomumlogerror.h"

namespace comum {

// (original lines 15-343: content not recovered)
#line 344
void IEventosLog::logaErro(const std::string& mensagem)
{
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(3), mensagem);
}

void IEventosLog::LogaMidiaResultadoAusente()
{
    logaErro("Mídia de resultado não estava presente");
}

void IEventosLog::LogaMidiaResultadoInvalida()
{
    logaErro("Mídia de resultado inválida para gravação de resultados");
}

void IEventosLog::LogaMesarioIndagadoImprimirZeresima()
{
    loga("Mesário indagado se quer imprimir a zerésima");
}

void IEventosLog::LogaErroEstadoAplicativo()
{
    logaErro("Erro estado do aplicativo não esperado");
}

void IEventosLog::LogaImprimindoRelatorioEstadoUrna()
{
    loga("Imprimindo relatório de estado da urna");
}


void IEventosLog::logaAlerta(const std::string& mensagem)
{
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

IEventosLog::IEventosLog(api::ELogAplicativos aplicativo) : m_aplicativo(aplicativo) {}

void IEventosLog::loga(const std::string& mensagem)
{
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void IEventosLog::LogaCargaBateria(uebyte fonte, uebyte status)
{
    const std::string mensagem = std::format("Carga da [{}]: [{}]", ConverteFonteAlim(fonte), ConverteStatusBateria(status));
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(status == 2 ? 2 : 1), mensagem);
}

// (original lines 393-395: content not recovered)
#line 396
std::string IEventosLog::ConverteERelatoriosUE(const ERelatoriosUE relatorio)
{
    switch (relatorio) {
        case RELATORIO_ZERESIMA:
            return "ZERÉSIMA";
        case RELATORIO_ZERESIMA_APURACAO:
            return "ZERÉSIMA DE APURAÇÃO";
        case RELATORIO_ZERESIMA_SECAO:
            return "ZERÉSIMA DE SEÇÃO";
        case RELATORIO_BU:
            return "BU";
        case RELATORIO_BUJ:
            return "BUJ";
        case RELATORIO_RDV:
            return "RDV";
        case RELATORIO_AUTOTESTE:
            return "AUTOTESTE";
        case RELATORIO_COMPROVANTE_CARGA:
            return "COMPROVANTE DE CARGA";
        case RELATORIO_HASHES_ARQUIVOS:
            return "HASHES ARQUIVOS";
        case RELATORIO_BIM:
            return "BIM";
        case RELATORIO_ARQUIVOS_ELEITORES_CANDIDATOS:
            return "ARQUIVOS DE ELEITORES E CANDIDATOS";
        case RELATORIO_RESUMO_ZERESIMA:
            return "RESUMO DA ZERÉSIMA";
        case RELATORIO_ELEITORES_HABILITADOS_BIOGRAFICAMENTE:
            return "ELEITORES HABILITADOS BIOGRAFICAMENTE";
        default:
            throw CUeComumLogError(EUE_COMUM_LOG_8852, "Valor inválido");
    }
}

std::string IEventosLog::ConverteFonteAlim(const uebyte fonte)
{
    switch (fonte) {
        case 0:
            return "ALIMENTAÇÃO AC";
        case 1:
            return "ALIMENTAÇÃO BATERIA INTERNA";
        case 2:
            return "ALIMENTAÇÃO BATERIA EXTERNA";
        default:
            throw CUeComumLogError(EUE_COMUM_LOG_8853, "Valor inválido");
    }
}

std::string IEventosLog::ConverteStatusBateria(const uebyte status)
{
    switch (status) {
        case 0:
            return "PLENA";
        case 1:
            return "PARCIAL";
        case 2:
            return "CRÍTICA";
        case 3:
            return "AUSENTE";
        default:
            throw CUeComumLogError(EUE_COMUM_LOG_8854, "Valor inválido");
    }
}

} // namespace comum
