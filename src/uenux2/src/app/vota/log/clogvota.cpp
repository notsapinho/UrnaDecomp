// vota::CLogVota (/home/rubio/tse/uenux2/src/app/vota/log/clogvota.cpp). Its records are records of the target:
//   184    static CLogVota &GetInst()                                 record at line 37, column 37
//   10635  LogaEleitorImpedido(comum::md::ETipoImpedimento)            record at line 432, column 19 (not written)
// Members with no record sit at chosen lines, each unit's fragment says why: 119's, 161's five after GetInst, 152's
// seven after LogaTituloInvalidoRegistroMesario, 142's three, 138's one, 169's one, then 138's two, 176's, 61's, 197's.

#include "app/vota/log/clogvota.h"

#include <format>
#include <memory>
#include <string>

#include "api/pattern/cpolysingleton.h"
#include "api/uelog/cloga.h"

namespace vota {

CLogVota::CLogVota() : comum::IEventosLog(static_cast<api::ELogAplicativos>(1)) {}

void CLogVota::LogaMesarioRegistrado(const std::string& titulo)
{
    const std::string mensagem = std::format("Mesário {} registrado", titulo);
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMesarioJaRegistrado(const std::string& titulo)
{
    const std::string mensagem = std::format("Mesário {} já registrado", titulo);
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

CLogVota& CLogVota::GetInst()
{
    if (!api::CPolySingletonList::has<comum::IEventosLog>()) {
        api::CPolySingleton<comum::IEventosLog>::set(std::unique_ptr<comum::IEventosLog>(new CLogVota));
    }
    return dynamic_cast<CLogVota &>(api::CPolySingleton<comum::IEventosLog>::instance());
}

void CLogVota::LogaEleitorJaVotou()
{
    logaAlerta("O eleitor identificado já votou");
}

void CLogVota::LogaIdentificadorEleitorInvalido()
{
    const std::string mensagem = "Identificador do eleitor digitado inválido";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaSolicitacaoDadoPessoalEleitor()
{
    loga("Solicitação de dado pessoal do eleitor para habilitação manual");
}

void CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado()
{
    loga("Habilitação cancelada durante confirmação de dado do eleitor");
}

void CLogVota::LogaHabilitacaoCanceladaCapturaDigitalMesario()
{
    loga("Habilitação cancelada durante a captura de digital do mesário");
}

void CLogVota::LogaIndagaRegistroMesarios()
{
    const std::string mensagem = "Operador indagado se ocorrerá registro de mesários";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaTituloInvalidoRegistroMesario()
{
    const std::string mensagem = "Digitado título inválido para o registro de mesário";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaIndagaEleitorVotando()
{
    logaAlerta("Mesário indagado se eleitor está votando");
}

void CLogVota::LogaPedidoDesconexaoFone()
{
    loga("Solicitado ao mesário que desconecte o fone de ouvido");
}

void CLogVota::LogaPedidoConexaoFone()
{
    loga("Solicitado ao mesário que conecte o fone de ouvido");
}

void CLogVota::LogaHorarioVotacaoTerminou()
{
    const std::string mensagem = "Horário de votação terminou";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaInspecaoIniciada()
{
    loga("Inspeção da urna iniciada");
}

void CLogVota::LogaAudioDesativadoFimVotacao()
{
    loga("Áudio desativado pelo fim da votação");
}

void CLogVota::LogaSuspensaoAbortada()
{
    loga("Mesário abortou processo de suspensão");
}

void CLogVota::LogaJustificativaRecebida()
{
    const std::string mensagem = "Justificativa recebida";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaEleitorJaJustificou()
{
    const std::string mensagem = "Eleitor já justificou";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaPedidoTituloSuspensao()
{
    loga("Solicitado título eleitoral para suspensão do eleitor");
}

void CLogVota::LogaVotacaoEncerrada()
{
    loga("Votação encerrada");
}

void CLogVota::LogaAguardandoConfirmacaoZeresima()
{
    loga("Aguardando confirmação para emissão da zerésima");
}

void CLogVota::LogaMesarioConfirmouReinicioVotacao()
{
    const std::string mensagem = "Mesário confirmou o reinício da votação";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMesarioSelecionouOutrasOpcoes()
{
    const std::string mensagem = "Mesário selecionou outras opções";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMesarioIndagadoHorarioUrna()
{
    loga("Mesário indagado se horário da urna está correto");
}

void CLogVota::LogaTempoLimiteBateriaInterna()
{
    const std::string mensagem = "Tempo limite de espera usando bateria interna atingido";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaErroIdentificacaoTipoCargo()
{
    logaErro("Erro na identificação do tipo de cargo");
}

void CLogVota::LogaEleitorVoltouADigitar()
{
    loga("Eleitor voltou a digitar enquanto estava sendo suspenso");
}

} // namespace vota

// <stubs>
// f10635 · 3870 B · unmatched · name unknown
// void f10635(i32) { ... }
// </stubs>
