#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace comum {

// comum's error codes. The enum's name, its namespace and its limits are the target's: the typeinfo of
// CBaseError<comum::EUeComumError, SErrorLimits{7200, 7600}>, which fn 480's vptr names. This header's path is chosen
// (app/comum/, the root of the namespace's tree). Each value is a code a function of the tree throws, and each name is
// chosen from the throw's function and message: no evidence names an enumerator.
enum EUeComumError {
    // CArquivosResultado::operator[] (fn 347), "Extensão de arquivo de resultado associada ao identificador {} não
    // encontrada"
    EUE_COMUM_EXTENSAO_RESULTADO_NAO_ENCONTRADA = 7200,
    // CArquivosSavd::operator[](ESavdPacote) (fn 275), "Arquivo de assinatura associado ao identificador {} não
    // encontrado"
    EUE_COMUM_ARQUIVO_ASSINATURA_NAO_ENCONTRADO = 7201,
    // CArquivosSavd::operator[](ESavdArquivoUE) (fn 680), "Arquivo assinado associado ao identificador {} não encontrado"
    EUE_COMUM_ARQUIVO_ASSINADO_NAO_ENCONTRADO = 7203,
    // CPacoteArquivos::ValidarChaveEAplicacaoValida (fn 4625 holds it), "A chave informada não é válida: {}"
    EUE_COMUM_CHAVE_INVALIDA = 7219,
    // CPacoteArquivos::ValidarChaveEAplicacaoValida (fn 4625 holds it), "A aplicação informada não é válida: {}"
    EUE_COMUM_APLICACAO_INVALIDA = 7220,
    // CPacoteArquivos::RetornaNomeChave (fn 5900), "Chave desconhecida: {}"
    EUE_COMUM_CHAVE_DESCONHECIDA = 7221,
    // CPacoteArquivos::TrataErroPacote (fn 5901), "Falha ao validar assinatura {}\npacote: ({})\nErro SAVD: ({} - {})"
    EUE_COMUM_VALIDAR_ASSINATURA_PACOTE = 7222,
    // CPacoteArquivos::TrataErroPacoteArquivo (fn 4625 holds it), "Falha ao validar assinatura {}\npacote:
    // ({})\narquivo: ({})\nErro SAVD: ({} - {})"
    EUE_COMUM_VALIDAR_ASSINATURA_ARQUIVO = 7223,
    // CPath::GetPathRootSemSA (fn 634), "Mídia inválida: {}"
    EUE_COMUM_PATH_MIDIA_INVALIDA = 7224,
    // CPath::GetPathResult (fn 1399), "Turno invalido: {}"
    EUE_COMUM_PATH_RESULT_TURNO_INVALIDO = 7226,
    // CPath::GetPathTrab (fn 358), "Turno invalido: {}"
    EUE_COMUM_PATH_TRAB_TURNO_INVALIDO = 7227,
    // IInterfaceInit::CurrentBootDevice (fn 11646), "Resposta nula"
    EUE_COMUM_BOOT_DEVICE_RESPOSTA_NULA = 7231,
    // IInterfaceInit::IsMRPresenteSemHabilitar and IsMRMontadoSemHabilitar (fns 2862, 5897), "Resposta nula"
    EUE_COMUM_MR_PRESENTE_RESPOSTA_NULA = 7237,
    EUE_COMUM_MR_MONTADO_RESPOSTA_NULA = 7238,
    // IInterfaceInit::MontarMRSemHabilitar (fn 5896), "Resposta nula" and "Falha ao montar mídia de resultado ({})"
    EUE_COMUM_MONTAR_MR_RESPOSTA_NULA = 7239,
    EUE_COMUM_MONTAR_MR_FALHA = 7240,
    // IInterfaceInit::DesmontarMRSemDesabilitar (fn 3832), "Resposta nula" and "Falha ao desmontar mídia de resultado ({})"
    EUE_COMUM_DESMONTAR_MR_RESPOSTA_NULA = 7241,
    EUE_COMUM_DESMONTAR_MR_FALHA = 7242,
    // IInterfaceInit::DesligarUrna (fn 5894), "Resposta nula" and "Erro ao desligar urna: {}"
    EUE_COMUM_DESLIGAR_URNA_RESPOSTA_NULA = 7268,
    EUE_COMUM_DESLIGAR_URNA_FALHA = 7269,
    // IInterfaceInit::LogDiskInfo (inlined into fn 10226, vota::CThreadMonitor's slot 2), "Resposta nula"
    EUE_COMUM_LOG_DISK_INFO_RESPOSTA_NULA = 7277,
    // IInterfaceInit::DispositivoMR (inlined into fn 5896), "Resposta nula" and "Falha ao obter dispositivo da MR: {}"
    EUE_COMUM_DISPOSITIVO_MR_RESPOSTA_NULA = 7282,
    EUE_COMUM_DISPOSITIVO_MR_FALHA = 7283,
    // IInterfaceInit::EnviarMensagemThrowVoid (fn 3833), "{}: Resposta nula" and "Falha ao enviar mensagem {}, {}: {}"
    EUE_COMUM_ENVIAR_MENSAGEM_RESPOSTA_NULA = 7293,
    EUE_COMUM_ENVIAR_MENSAGEM_FALHA = 7294,
    // IInterfaceInit::GetDemoMode (fn 729), "Resposta nula" and "Falha ao obter estado do modo de demonstração: {}"
    EUE_COMUM_MODO_DEMO_RESPOSTA_NULA = 7295,
    EUE_COMUM_MODO_DEMO_FALHA = 7296,
    // IInterfaceSavd::DesconverteHeader (inlined into fn 3830), "Header com tamanho incorreto: {}/{}" and "Header com
    // marca incorreta"
    EUE_COMUM_SAVD_HEADER_TAMANHO_INCORRETO = 7305,
    EUE_COMUM_SAVD_HEADER_MARCA_INCORRETA = 7306,
    // IInterfaceSavd::DesconverteMensagem (inlined into fn 3830), "Mensagem com tamanho incorreto: {}/{}", "Mensagem com
    // marca incorreta" and "Buffer com tamanho insuficiente para mensagem: {}/{}"
    EUE_COMUM_SAVD_MENSAGEM_TAMANHO_INCORRETO = 7307,
    EUE_COMUM_SAVD_MENSAGEM_MARCA_INCORRETA = 7308,
    EUE_COMUM_SAVD_MENSAGEM_BUFFER_INSUFICIENTE = 7309,
    // ValidarUE (fn 5890), "Falha ao validar assinatura UE\npacote: ({})\nErro SAVD: ({})\n{}"
    EUE_COMUM_VALIDAR_ASSINATURA_UE = 7323,
    // ValidarUE over a file (inlined into fn 11179, CSigVerifier::Verify), "Falha ao validar assinatura UE\npacote:
    // ({})\narquivo: ({})\nErro SAVD: ({})\n{}"
    EUE_COMUM_VALIDAR_ASSINATURA_UE_ARQUIVO = 7324,
    // AssinarUE (inlined into fn 1277, CAssinador::Assina), "Falha ao assinar ({}-UE[{}])"
    EUE_COMUM_ASSINAR_UE = 7336,
    // AssinarEcourna (inlined into CAssinador::AssinaArquivosResultado, which fn 12098 holds inlined), "Falha ao
    // assinar ({}-Ecourna[{}])"
    EUE_COMUM_ASSINAR_ECOURNA = 7338,
    // EnviarAcaoHSM (fn 5889), "Falha ao enviar ação ao HSM. {}"
    EUE_COMUM_ENVIAR_ACAO_HSM = 7340,
};

using CUeComumError = ecourna::api::exception::CBaseError<EUeComumError, ecourna::api::exception::SErrorLimits{7200, 7600}>;

} // namespace comum
