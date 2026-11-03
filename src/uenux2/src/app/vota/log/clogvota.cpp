// vota::CLogVota (/home/rubio/tse/uenux2/src/app/vota/log/clogvota.cpp). Its records are records of the target:
//   184    static CLogVota &GetInst()                                 record at line 37, column 37
//   10635  LogaEleitorImpedido(comum::md::ETipoImpedimento)            record at line 432, column 19 (held inlined)
// Lines of members with no record are chosen, fragments say why: 119's, 161's five, 156's two after GetInst; 152's seven
// after LogaTituloInvalidoRegistroMesario, 142's three, 138's one, 169's one, 138's two, 176's, 61's, 197's, 156's four after
// LogaPedidoTituloSuspensao; after LogaAguardandoConfirmacaoZeresima, 138's, 199's, 119's two; 104's, 169's two; 277's eight.
#include "app/vota/log/clogvota.h"
#include <format>
#include <memory>
#include <string>

#include "api/pattern/cpolysingleton.h"
#include "api/uelog/cloga.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"

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

void CLogVota::LogaMesarioIndagadoQtdViasAdicionais()
{
    loga("Mesário indagado sobre quantidade de vias adicionais");
}

void CLogVota::LogaMesarioNaoSolicitouViasAdicionais()
{
    loga("Mesário não solicitou emissão de vias adicionais");
}

void CLogVota::LogaErroPartidoNaoEncontrado()
{
    logaErro("Erro partido não encontrado");
}

void CLogVota::LogaTeclaIndevida()
{
    loga("Tecla indevida pressionada");
}

void CLogVota::LogaEleitorCorrigiuConfirmacaoCandidato()
{
    loga("Eleitor corrigiu na tela de confirmação de candidato");
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

void CLogVota::LogaAudioAtivadoConformeCadastro()
{
    loga("Áudio ativado conforme cadastro");
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

void CLogVota::LogaTituloSuspensaoDigitado()
{
    loga("Mesário digitou o título para suspender o eleitor");
}

void CLogVota::LogaTituloSuspensaoInvalido(const std::string& titulo)
{
    logaAlerta(std::format("Título {} é inválido para suspender a votação", titulo));
}

void CLogVota::LogaTituloSuspensaoValido(const std::string& titulo)
{
    logaAlerta(std::format("Título {} é válido para suspender a votação", titulo));
}


void CLogVota::LogaImprimindoRelatorio(comum::ERelatoriosUE relatorio, uebyte via)
{
    loga(std::format("Imprimindo relatório [{}] via nº [{}]", ConverteERelatoriosUE(relatorio), via));
}

void CLogVota::LogaQtdViasAdicionaisExcedeMaximo()
{
    logaAlerta("Quantidade de vias adicionais excede o máximo permitido");
}

void CLogVota::LogaMesarioIndagadoQualidadeBU()
{
    loga("Mesário indagado sobre qualidade do Boletim de Urna");
}

void CLogVota::LogaVotoBrancoPorSuspensao(const uebyte cargo)
{
    loga(std::format("Atribuido voto branco por suspensão [{}]",
                     comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo).GetNomeNeutro()));
}

void CLogVota::LogaVotoCargoSemCandidato(const uebyte cargo)
{
    loga(std::format("Atribuido voto para cargo sem candidato [{}]",
                     comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo).GetNomeNeutro()));
}

void CLogVota::LogaVotoNuloPorSuspensao(const uebyte cargo)
{
    loga(std::format("Atribuido voto nulo por suspensão [{}]",
                     comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo).GetNomeNeutro()));
}

void CLogVota::LogaVotoConfirmado(const uebyte cargo)
{
    loga(std::format("Voto confirmado para [{}]",
                     comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo).GetNomeNeutro()));
}

void CLogVota::LogaHabilitacaoCanceladaReconhecimentoBiometrico()
{
    logaAlerta("Habilitação cancelada durante reconhecimento biométrico");
}

void CLogVota::LogaVotacaoEncerrada()
{
    loga("Votação encerrada");
}

void CLogVota::LogaAguardandoConfirmacaoZeresima()
{
    loga("Aguardando confirmação para emissão da zerésima");
}

void CLogVota::LogaAguardandoHorarioZeresima()
{
    const std::string mensagem = "Aguardando data e hora para emissão da zerésima";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaAguardandoIdentificadorEleitor()
{
    const std::string mensagem = "Aguardando digitação do identificador do eleitor";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaDataEleicaoInvalida()
{
    const std::string mensagem = "Data da eleição inválida";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaErroEstadoAplicativoDesconhecido()
{
    logaErro("Erro estado do aplicativo não conhecido");
}

void CLogVota::LogaFimTesteTecladoSucesso()
{
    loga("Fim do teste de Teclado do TE - Sucesso");
}

void CLogVota::LogaTesteTecladoNaoExecutado()
{
    loga("Teste de Teclado do TE não executado");
}

void CLogVota::LogaInicioTesteTeclado()
{
    loga("Início do teste de Teclado do TE");
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

void CLogVota::LogaApresentadaTelaReinicioVotacao()
{
    const std::string mensagem = "Apresentada tela do reinício da votação";
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

void CLogVota::LogaVotoCargoSemCandidatoPorSuspensao(const uebyte cargo)
{
    loga(std::format("Atribuido voto para cargo sem candidato por suspensão [{}]",
                     comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo).GetNomeNeutro()));
}

void CLogVota::LogaErroVerificacaoComparecimento()
{
    logaErro("Erro na verificação do comparecimento");
}

void CLogVota::LogaFinalizacaoAplicativo()
{
    const std::string mensagem = "Finalização de aplicativo";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaDesligandoUrna()
{
    const std::string mensagem = "Desligando a urna";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMudancaChaveUrnaDesligada()
{
    const std::string mensagem = "Mudança do estado da chave: URNA DESLIGADA";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaEspacoLivreMI(uintmax_t espaco)
{
    loga(std::format("Espaço livre na MI [{}]", comum::FormataTamanho(espaco)));
}

void CLogVota::LogaEspacoLivreMV(uintmax_t espaco)
{
    loga(std::format("Espaço livre na MV [{}]", comum::FormataTamanho(espaco)));
}

void CLogVota::LogaEspacoUtilizadoMI(uintmax_t espaco)
{
    loga(std::format("Espaço utilizado na MI [{}]", comum::FormataTamanho(espaco)));
}

void CLogVota::LogaEspacoUtilizadoMV(uintmax_t espaco)
{
    loga(std::format("Espaço utilizado na MV [{}]", comum::FormataTamanho(espaco)));
}

void CLogVota::LogaQuantidade(const std::pair<std::string, uint64_t>& quantidade)
{
    loga(std::format("Quantidade de {} [{}]", quantidade.first, comum::FormataTamanho(quantidade.second)));
}

// (original lines 362-382: content not recovered)
#line 383
void CLogVota::LogaEleitorImpedido(comum::md::ETipoImpedimento impedimento)
{
    std::string descricao;
    switch (impedimento) {
        case comum::md::IMPEDIMENTO_SEM_IMPEDIMENTO:
            return;
        case comum::md::IMPEDIMENTO_VOTA_NA_SECAO_ORIGINAL:
            descricao = "vota na seção original";
            break;
        case comum::md::IMPEDIMENTO_SOLICITOU_VOTO_EM_TRANSITO:
            descricao = "solicitou voto em trânsito";
            break;
        case comum::md::IMPEDIMENTO_PRESO_PROVISORIO:
            descricao = "preso provisório";
            break;
        case comum::md::IMPEDIMENTO_SUSPENSO:
            descricao = "título suspenso";
            break;
        case comum::md::IMPEDIMENTO_CANCELADO:
            descricao = "título cancelado";
            break;
        case comum::md::IMPEDIMENTO_NAO_LIBERADO:
            descricao = "eleitor não está liberado para votar";
            break;
        case comum::md::IMPEDIMENTO_SEM_IDADE_MINIMA:
            descricao = "eleitor não tem idade mínima para votar";
            break;
        case comum::md::IMPEDIMENTO_MILITAR_EM_SERVICO:
            descricao = "eleitor é militar em serviço";
            break;
        case comum::md::IMPEDIMENTO_TTE_ACESSIBILIDADE:
            descricao = "eleitor pediu acessibilidade";
            break;
        case comum::md::IMPEDIMENTO_TTE_ELEITOR_CONVOCADO:
            descricao = "eleitor convocado pela Justiça Eleitoral";
            break;
        case comum::md::IMPEDIMENTO_TTE_JUSTICA_ELEITORAL:
            descricao = "eleitor é servidor da Justiça Eleitoral";
            break;
        case comum::md::IMPEDIMENTO_TTE_OFICIO:
            descricao = "eleitor transferido por ofício";
            break;
        case comum::md::IMPEDIMENTO_TTE_INDIGENAS_QUILOMBOLAS:
            descricao = "eleitor é um membro da comunidade indígena ou quilombola";
            break;
        case comum::md::IMPEDIMENTO_TTE_SITUACAO_RUA:
            descricao = "eleitor está em situação de rua";
            break;
        case comum::md::IMPEDIMENTO_INVALIDO:
            throw CUeVotaError(EUE_VOTA_TIPO_IMPEDIMENTO_INVALIDO, "Tipo inválido");
    }
    loga(std::format("Eleitor impedido - {}", descricao));
}

void CLogVota::LogaSolicitaDigitalMesario()
{
    loga("Solicita digital do mesário");
}

void CLogVota::LogaIdentificadorDigitadoMesario()
{
    const std::string mensagem = "Identificador do eleitor digitado pelo mesário";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMesarioConfirmaHorarioUrnaErrado()
{
    loga("Mesário confirma que o horário da urna está errado");
}

void CLogVota::LogaMesarioConfirmaHorarioUrnaCorreto()
{
    loga("Mesário confirma que o horário da urna está correto");
}

void CLogVota::LogaMesarioIndicouReimprimirBU()
{
    loga("Mesário indicou reimprimir Boletim de Urna");
}

void CLogVota::LogaMesarioIndicouQualidadeBU()
{
    loga("Mesário indicou qualidade OK para Boletim de Urna");
}

void CLogVota::LogaSolicitadaRetiradaMR()
{
    const std::string mensagem = "Solicitada a retirada da mídia de resultado";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaMRRetirada()
{
    const std::string mensagem = "Mídia de resultado retirada";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaSolicitadaEmissaoViasAdicionais(uebyte quantidade)
{
    const std::string mensagem = std::format("Solicitada a emissão de [{}] ", quantidade);
    loga(mensagem + (quantidade == 1 ? "via adicional" : "vias adicionais"));
}

void CLogVota::LogaInspecaoTerminada()
{
    loga("Inspeção da urna terminada");
}

void CLogVota::LogaEleitorSuspensoTreinamento()
{
    loga("Eleitor foi suspenso automaticamente no treinamento eleitor");
}

void CLogVota::LogaEleitorSuspensoPeloMesario()
{
    loga("Eleitor foi suspenso pelo mesário");
}

void CLogVota::LogaEleitorVotouParcialmenteSuspenso()
{
    loga("Eleitor votou parcialmente e em seguida foi suspenso");
}

void CLogVota::LogaEleitorSuspensoSemVoto()
{
    loga("Eleitor foi suspenso e não confirmou nenhum voto");
}

void CLogVota::LogaEncerramentoAntesDoHorario(const api::CDateTime& dataHora)
{
    const std::string mensagem =
        std::format("Encerramento só pode ser solicitado após as {} horas", dataHora.GetHora().Format("hh:mm:ss"));
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaTodosEleitoresVotaram(bool votaram)
{
    const std::string mensagem = std::format("Todas as pessoas presentes já votaram? {}", votaram ? "SIM" : "NÃO");
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaTituloDigitadoEncerramento(const std::string& titulo)
{
    const std::string mensagem = std::format("Título digitado para encerramento: {}", titulo);
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaEncerramentoCancelado()
{
    loga("Operador cancelou o encerramento da votação");
}

void CLogVota::LogaEncerramentoAbortado()
{
    const std::string mensagem = "Procedimento de encerramento abortado";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(2), mensagem);
}

void CLogVota::LogaEncerramentoConfirmado()
{
    const std::string mensagem = "Procedimento de encerramento confirmado";
    api::CLoga::loga(m_aplicativo, static_cast<api::ESeveridade>(1), mensagem);
}

void CLogVota::LogaAudioAtivadoPeloMesario()
{
    loga("Áudio ativado pelo mesário");
}

void CLogVota::LogaAudioDesativadoPeloMesario()
{
    loga("Áudio desativado pelo mesário");
}

} // namespace vota
