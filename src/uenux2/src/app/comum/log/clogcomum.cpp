// comum::CLogComum (/home/rubio/tse/uenux2/src/app/comum/log/clogcomum.cpp). Its records are records of the target:
//   5878  LogaCopiandoArqResParaFI(EExtensaoArquivoResultado)                              record at line 76, column 18
//   3828  LogaResultadoCopiadoResFE(EExtensaoArquivoResultado)                             record at line 84, column 18
//   5876  LogaGerandoResultados(EExtensaoArquivoResultado, EStatusOperacaoRelatorio)       record at line 92, column 25 (written, unmatched)
//   5875  LogaNivelBateria(uebyte, uebyte)                                                 record at line 106, column 18
//         LogaSuspensoMonitoramenteRepeticao(uebyte)                                     record at line 136, column 18
//         LogaTipoBateria()                                                              records at lines 144, 145, 158
// (the last two have no target index: binaryen inlined them into fn 10226, vota::CThreadMonitor's slot 2)
// The reconstruction's notes are in unit 111's fragment.

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

// (original lines 39-73: content not recovered)
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

} // namespace comum
