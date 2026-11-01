// Reconstruction's note, not TSE's text: api::CApplication (/home/rubio/tse/uenux2/src/api/gui/capplication.cpp), in
// part. The records fix line 503 (EnterLoopDoingNothing, target fn 5566) and keep 303, 377, 432 and 478 blank
// (QRCodeSRC::build, ShowExceptionMsgScreen, LogExceptionMsg and EnterLoopBeeping's lambda, not written). Every other
// line, the statics' place and the include order are chosen: src/units/171-uenux2-capplication.mk has the rest.
#include "api/gui/capplication.h"

#include <locale>

#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"

namespace api {

bool CApplication::s_finalizar = false;
int CApplication::s_codigoRetorno = -1;
std::string CApplication::s_aplicacao;
std::string CApplication::s_descricao;
std::string CApplication::s_versao;
ELogAplicativos CApplication::s_aplicativo;
CApplicationContextStack CApplication::s_contextos;

void CApplication::InitApplication(const std::string& aplicacao, const std::string& descricao, const std::string& versao,
                                   ELogAplicativos aplicativo)
{
    s_aplicacao = aplicacao;
    s_descricao = descricao;
    s_versao = versao;
    s_aplicativo = aplicativo;
    s_codigoRetorno = -1;

    struct commaAsDecimalSeparator : std::numpunct<char> {
        char do_decimal_point() const override { return ','; }
    };
    std::locale::global(std::locale(std::locale(), new commaAsDecimalSeparator));

    s_contextos.m_contextos.clear();
    PushContextoInicial("Não é possível continuar a execução", "Erro inesperado");
}

void CApplication::PushContextoInicial(std::string titulo, std::string descricao)
{
    PushContext(CApplicationContext::CriaPadrao(std::move(titulo), std::move(descricao)));
}

void CApplication::PushContext(CApplicationContext context)
{
    s_contextos.Push(std::move(context));
}

CApplicationContextGuard CApplication::CriaContexto(CApplicationContext contexto)
{
    return CApplicationContextGuard(s_contextos, std::move(contexto));
}

CApplicationContextGuard CApplication::CriaContexto(int tipo, std::string titulo, std::string descricao,
                                                    std::string detalhe)
{
    return CriaContexto(CApplicationContext::Cria(tipo, std::move(titulo), std::move(descricao), std::move(detalhe)));
}

// (original lines 62-497: content not recovered)
#line 498
void CApplication::EnterLoopDoingNothing()
{
    if (!s_finalizar) {
        do {
            if (CPolySingletonList::has<IScreen>()) {
                auto& screen = CPolySingleton<IScreen>::instance();
                screen.Slot37();
            }
            CSystem::Dorme(1000);
        } while (!s_finalizar && s_codigoRetorno <= 0);
    }
}

} // namespace api
