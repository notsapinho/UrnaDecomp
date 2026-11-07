// Reconstruction's note, not TSE's text: api::CApplication (/home/rubio/tse/uenux2/src/api/gui/capplication.cpp), in
// part. The records fix line 503 (EnterLoopDoingNothing, target fn 5566) and keep 303, 377, 432 and 478 blank
// (QRCodeSRC::build, ShowExceptionMsgScreen, LogExceptionMsg and EnterLoopBeeping's lambda, not written). The statics
// follow the target's .bss order (a reading) but s_finalizar; the rest is chosen: src/units/171-uenux2-capplication.mk.
// MostraMensagemTemporaria, its helper and FONTE_MENSAGEM have no record: their lines are chosen (capplication.h).
#include "api/gui/capplication.h"

#include <locale>
#include <optional>
#include <sstream>

#include "api/gui/cformbuilder.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "api/util/cwait.h"

namespace api {

bool CApplication::s_demonstracao = false;
bool CApplication::s_finalizar = false;
SRect CApplication::s_areaTela{0, 0, 639, 479};
int CApplication::s_modo = 48;
int CApplication::s_codigoRetorno = -1;
std::string CApplication::s_aplicacao;
std::string CApplication::s_descricao;
std::string CApplication::s_versao;
ELogAplicativos CApplication::s_aplicativo;
CApplicationContextStack CApplication::s_contextos;

void PushContextoInicial(std::string titulo, std::string descricao);

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

void PushContextoInicial(std::string titulo, std::string descricao)
{
    CApplication::PushContext(CriaContextoPadrao(std::move(titulo), std::move(descricao)));
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
    return CriaContexto(CriaContextoAplicacao(tipo, std::move(titulo), std::move(descricao), std::move(detalhe)));
}

std::string Join(const std::vector<std::string>& partes, const std::string& separador)
{
    std::ostringstream saida;
    for (const std::string& parte : partes) {
        if (&parte != &partes.front()) {
            saida << separador;
        }
        saida << parte;
    }
    return saida.str();
}

CApplicationContext CApplication::GetContexto()
{
    if (s_contextos.m_contextos.empty()) {
        return CriaContextoPadrao("Erro inesperado", "Pilha de contexto vazia");
    }
    std::optional<CApplicationContext> contexto = s_contextos.m_contextos.back();
    return std::move(*contexto);
}

CApplication::EExceptionLevel GetExceptionLevel()
{
    return CApplication::GetContexto().m_padrao ? CApplication::EXCEPTION_LEVEL_2 : CApplication::EXCEPTION_LEVEL_1;
}

const SFont FONTE_MENSAGEM{35, 0};

namespace {

void ExibeMensagemTemporaria(const std::string& mensagem, CWait& espera)
{
    CFormBuilder builder;
    builder.AddFill(SPoint(0, 210), SPoint(639, 310), static_cast<TColor>(30));
    builder.AddTextField(mensagem, SPoint(320, 242), FONTE_MENSAGEM, ALINHAMENTO_CENTRO, static_cast<TColor>(2),
                         static_cast<TColor>(30));
    const std::shared_ptr<IForm<IScreen>> form = builder.GetFormSemLimpar("");
    form->Slot3();
    espera.Wait();
}

} // namespace

void MostraMensagemTemporaria(const std::string& mensagem, CWait&& espera)
{
    ExibeMensagemTemporaria(mensagem, espera);
}

// (original lines 120-497: content not recovered)
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

std::string CApplication::GetDescricaoModo()
{
    if (s_demonstracao) {
        return "DEMONSTRAÇÃO";
    }
    switch (s_modo) {
    case 50:
        return "SIMULADO";
    case 51:
        return "TREINAMENTO";
    }
    return "";
}

const SRect& CApplication::GetAreaTela()
{
    return s_areaTela;
}

} // namespace api
