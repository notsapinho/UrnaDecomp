// api::CEscritorLog (/home/rubio/tse/uenux2/src/api/uelog/cescritorlog.cpp, the file its records name). This comment is
// the reconstruction's: src/units/62-uenux2-cwasmlogd.mk says what is evidence and what is chosen.

#include "api/uelog/cescritorlog.h"

#include <cstdint>
#include <format>
#include <string>

#include "api/uelog/eueuelogerror.h"

namespace api {

static const std::uint8_t MAX_APLICATIVOS = 61;
static const std::uint8_t PRIMEIRA_OPERACAO = 230;
static const std::uint8_t ULTIMA_OPERACAO = 240;

// (original lines 18-24: content not recovered)
#line 25
static void confereAppValida(const std::string& funcao, ELogAplicativos aplicativo)
{
    if (aplicativo >= MAX_APLICATIVOS) {
        throw CUeUeLogError(EUE_UELOG_APLICACAO_INVALIDA, std::format("{} - O código da aplicação deve ser menor que {} [{}]", funcao, MAX_APLICATIVOS, aplicativo));
    }
}

// (original lines 32-34: content not recovered)
#line 35
void CEscritorLog::fazOperacao(ELogOperacoesLogD operacao)
{
    if (operacao < PRIMEIRA_OPERACAO) {
        throw CUeUeLogError(EUE_UELOG_OPERACAO_MENOR, std::format("Não existe nenhuma operação com número menor que {} [{}]", PRIMEIRA_OPERACAO, operacao));
    }

    // (original lines 41-42: content not recovered)
#line 43
    if (operacao > ULTIMA_OPERACAO) {
        throw CUeUeLogError(EUE_UELOG_OPERACAO_MAIOR, std::format("Não existe nenhuma operação com número maior que {} [{}]", ULTIMA_OPERACAO, operacao));
    }

    escreve(operacao, static_cast<ESeveridade>(1), "");
}

void CEscritorLog::loga(ELogAplicativos aplicativo, ESeveridade severidade, const std::string& mensagem)
{
    confereAppValida("loga", aplicativo);
    escreve(aplicativo, severidade, mensagem);
}

} // namespace api
