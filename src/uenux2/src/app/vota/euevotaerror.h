#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

// The error class's RTTI, CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}>, gives the enum's name, its
// namespace and its limits. This file's path and the CUeVotaError alias name are chosen, after api/util/eueutilerror.h
// and its CUeUtilError: no record names the file and no evidence names the alias.

namespace vota {

enum EUeVotaError {
    // the value is the code vota::CSincronizaVota::SincronizaRelatorios (target fn 1836, record csincronizavota.cpp:392)
    // throws; the name is chosen from its message, "O arquivo{} não é um relatório válido para sincronização": no
    // evidence names it
    EUE_VOTA_RELATORIO_INVALIDO_SINCRONIZACAO = 9302,
    // the value is the code vota::IConfereVotoEmCargo's anonymous-namespace GetCargoID (record cconferevotoemcargo.cpp:41,
    // inlined into target fn 11793) throws; the name is chosen from its message, "O cargo atual nao esta posicionado",
    // and the class: no evidence names it
    EUE_VOTA_CONFERE_VOTO_EM_CARGO_CARGO_NAO_POSICIONADO = 9305,
    // the values are the codes the GetTelaCargoAtual(const std::string &) of vota::CConfirmaVotoEmCargo and
    // vota::CConfirmaVotoSemCandidato throw (target fns 5928 and 4483, which pass them to fn 3921); the names are chosen
    // from the message, "<caller> - o cargo atual nao esta posicionado", and the class: no evidence names them
    EUE_VOTA_CONFIRMA_VOTO_EM_CARGO_CARGO_NAO_POSICIONADO = 9306,
    EUE_VOTA_CONFIRMA_VOTO_SEM_CANDIDATO_CARGO_NAO_POSICIONADO = 9307,
    // the value is the code vota::CConfirmaVotoSemCandidato::EmiteEcoComInputField (target fn 4477, record
    // cconfirmavotosemcandidato.cpp:77) throws; the name is chosen from its message, "Nao havia campos de input no
    // formulario sem nada digitado", and the class: no evidence names it
    EUE_VOTA_CONFIRMA_VOTO_SEM_CANDIDATO_SEM_INPUT = 9308,
    // the value is the code vota::CDefineRotaPosReinicio::NeedChangeState (target fn 11858, record
    // cdefinerotaposreinicio.cpp:81) throws; the name is chosen from its message, "Estado inválido = {}", and the class:
    // no evidence names it
    EUE_VOTA_DEFINE_ROTA_POS_REINICIO_ESTADO_INVALIDO = 9309,
    // the value is the code vota::CEleitorVotando::ChamaEstadoProximoCargo (target fn 4459, record
    // celeitorvotando.cpp:229) throws; the name is chosen from its message, "Tipo de cargo nao identificado": no evidence
    // names it
    EUE_VOTA_TIPO_CARGO_NAO_IDENTIFICADO = 9310,
    // the values are the codes vota::CEleitorVotando::suspenderEleitor (target fn 4442, records celeitorvotando.cpp:410
    // and :427) throws; the names are chosen from their messages, "Forma suspensao sem voto invalida" and "Forma
    // suspensao com voto invalida": no evidence names them
    EUE_VOTA_FORMA_SUSPENSAO_SEM_VOTO_INVALIDA = 9312,
    EUE_VOTA_FORMA_SUSPENSAO_COM_VOTO_INVALIDA = 9313,
    // the value is the code vota::CInstrucaoVotacaoAcessibilidade::ProcessInputAudio (target fn 7248, record
    // cinstrucaovotacaoacessibilidade.cpp:54) throws; the name is chosen from its message, "Número de inputs inválido",
    // and the class: no evidence names it
    EUE_VOTA_INSTRUCAO_ACESSIBILIDADE_INPUTS_INVALIDOS = 9314,
    // the value is the code vota::CVotacaoStateAudio::EmiteEcoComInputField (target fn 3139, record
    // cvotacaostateaudio.cpp:188) throws; the name is chosen from its message, "Nao havia campos de input no formulario
    // sem nada digitado", and the class: no evidence names it
    EUE_VOTA_STATE_AUDIO_SEM_INPUT = 9318,
    // the value is the code vota::CVotacaoStateAudio::EmiteEcoCorrigeConfirma (record cvotacaostateaudio.cpp:209,
    // inlined into target fn 11754) throws; the name is chosen from its message, "Nao havia campos de input no
    // formulario sem nada digitado", and the function: no evidence names it
    EUE_VOTA_STATE_AUDIO_CORRIGE_CONFIRMA_SEM_INPUT = 9319,
    // the value is the code vota::CVotacaoStateAudio::FormatPartyName (target fn 6954, record
    // cvotacaostateaudio.cpp:297) throws; the name is chosen from its message, "Nao foi encontrado o partido": no
    // evidence names it
    EUE_VOTA_PARTIDO_NAO_ENCONTRADO = 9321,
    // the value is the code vota::NomeTela (target fn 6718) throws; the name is chosen from its message, "Tela
    // inválida {}": no evidence names it
    EUE_VOTA_TELA_INVALIDA = 9327,
    // the value is the code vota::CTelasCargo::GetTela (record ctelascargo.cpp:80, inlined into target fn 4135)
    // throws; the name is chosen from its message, "Cargo {} não possui [{}]": no evidence names it
    EUE_VOTA_CARGO_NAO_POSSUI_TELA = 9330,
    // the value is the code vota::CTelasVota::GetTelaCargo (target fn 4135, record ctelasvota.cpp:3534) throws; the
    // name is chosen from its message, "Nao existe o conjunto de telas associado ao cargo id {}": no evidence names it
    EUE_VOTA_CONJUNTO_TELAS_INEXISTENTE = 9358,
    // the values are the codes vota::testeteclado::CTesteTeclado::StartState (target fn 11805, records
    // ctesteteclado.cpp:38 and :42) throws; the names are chosen from their messages, "Sem teclas para testar" and
    // "Tecla não encontrada: <tecla>": no evidence names them
    EUE_VOTA_TESTE_TECLADO_SEM_TECLAS = 9359,
    EUE_VOTA_TESTE_TECLADO_TECLA_NAO_ENCONTRADA = 9360,
    // the value is the code vota::CEmitirMaisBU::ProcessInput (target fn 12081, record cemitirmaisbu.cpp:64) throws;
    // the name is chosen from its message, "Era esperado pelo menos um input": no evidence names it
    EUE_VOTA_EMITIR_MAIS_BU_SEM_INPUT = 9371,
    // the value is the code vota::IQRCodeBUDS::IQRCodeBUDS (inlined into target fn 1956) throws; the name is chosen
    // from its message, "Vetor de partes vazio": no evidence names it
    EUE_VOTA_VETOR_PARTES_VAZIO = 9372,
    // the value is the code vota::CMostraQRCodeBU::ProcessInput (target fn 12051, record cmostraqrcodebu.cpp:85)
    // throws; the name is chosen from its message, "Número de inputs inválido": no evidence names it
    EUE_VOTA_QRCODE_BU_NUMERO_INPUTS_INVALIDO = 9373,
    // the value is the code vota::CMostraQRCodeBU::AjustaTela (target fn 5982, record cmostraqrcodebu.cpp:195) throws;
    // the name is chosen from its message, "Campo não encontrado no formulário": no evidence names it
    EUE_VOTA_QRCODE_BU_CAMPO_NAO_ENCONTRADO = 9374,
    // the value is the code vota::CQuerReimprimirZeresima::StartState (target fn 11849, record
    // cquerreimprimirzeresima.cpp:45) throws; the name is chosen from its message, "Erro na verificação do
    // comparecimento": no evidence names it
    EUE_VOTA_ERRO_VERIFICACAO_COMPARECIMENTO = 9375,
    // the values are the codes vota::CVerificaEleicaoPassou::StartState (target fn 11914, record
    // cverificaeleicaopassou.cpp:70) and vota::testeteclado::CPreZeresima::GetEstadoPassouNoTeste (target fn 5945, record
    // cprezeresima.cpp:56) throw; the names are chosen from their messages, "Estado nao esperado" and "Estado nao
    // esperado <estado>", and the classes: no evidence names them
    EUE_VOTA_VERIFICA_ELEICAO_PASSOU_ESTADO_NAO_ESPERADO = 9376,
    EUE_VOTA_PRE_ZERESIMA_ESTADO_NAO_ESPERADO = 9377,
    // the values are the codes the GetTelaCargoAtual of vota::CPedeMajoritario, vota::CCompletaProporcional and
    // vota::CPedeProporcional throw (target fns 5920, 5931 and 5923, which pass them to fns 6050 and 3921); the names
    // are chosen from the message, "O cargo atual nao esta posicionado", and the class: no evidence names them
    EUE_VOTA_PEDE_MAJORITARIO_CARGO_NAO_POSICIONADO = 9380,
    // the values are the codes vota::CPedeMajoritario::ProcessInputAudio (target fn 11683, record cpedemajoritario.cpp:64)
    // and its ExisteCandidatoValidoResposta (record :125, inlined there) throw, and vota::CCompletaProporcional's
    // EmiteEcoComInputField (target fn 5930, record ccompletaproporcional.cpp:60); the names are chosen from their
    // messages, "O cargo atual nao esta posicionado", "Nao foi encontrado o partido do candidato" and "Nao havia campos de
    // input no formulario sem nada digitado", and the classes: no evidence names them
    EUE_VOTA_PEDE_MAJORITARIO_ENTRADA_CARGO_NAO_POSICIONADO = 9381,
    EUE_VOTA_PEDE_MAJORITARIO_PARTIDO_NAO_ENCONTRADO = 9382,
    EUE_VOTA_COMPLETA_PROPORCIONAL_SEM_INPUT = 9383,
    EUE_VOTA_COMPLETA_PROPORCIONAL_CARGO_NAO_POSICIONADO = 9384,
    // the value is the code vota::CPedeNulo::GetProximoEstado (target fn 11744, record cpedenulo.cpp:44) throws; the
    // name is chosen from its message, "O cargo atual nao esta posicionado", and the class: no evidence names it
    EUE_VOTA_PEDE_NULO_CARGO_NAO_POSICIONADO = 9385,
    EUE_VOTA_PEDE_PROPORCIONAL_CARGO_NAO_POSICIONADO = 9386,
    // the value is the code vota::CPedeProporcional::ProcessInputAudio (target fn 11711, record
    // cpedeproporcional.cpp:84) throws; the name is chosen from its message, "O cargo atual nao esta posicionado", and the
    // class: no evidence names it
    EUE_VOTA_PEDE_PROPORCIONAL_ENTRADA_CARGO_NAO_POSICIONADO = 9387,
    // the value is the code vota::CLogVota::LogaEleitorImpedido throws (record clogvota.cpp:432, inlined into target fn
    // 10635); the name is chosen from its message, "Tipo inválido": no evidence names it
    EUE_VOTA_TIPO_IMPEDIMENTO_INVALIDO = 9388,
    // the values are the codes vota::CThreadMonitor::VerificaErroCriticoFlash (record cthreadmonitor.cpp:156) and
    // VerificaErroCriticoKbdTE (cthreadmonitor.cpp:167), inlined into target fn 10226, throw; the names are chosen from
    // their messages, "Erro na Mídia Externa - Mídia não está presente" and "Erro no teclado do eleitor - dispositivo
    // desconectado": no evidence names them
    EUE_VOTA_MIDIA_EXTERNA_AUSENTE = 9390,
    EUE_VOTA_TECLADO_ELEITOR_DESCONECTADO = 9391,
    // the value is the code vota::CEleitorEncontrado::StartState (target fn 10635, record celeitorencontrado.cpp:102)
    // throws; the name is chosen from its message, "Eleitor não posicionado": no evidence names it
    EUE_VOTA_ELEITOR_NAO_POSICIONADO = 9394,
    // the value is the code vota::IConfirmaJustificativa's constructor (target fn 3625, record
    // iconfirmajustificativa.cpp:34) throws; the name is chosen from its message, "Frase muito grande [<frase>]": no
    // evidence names it
    EUE_VOTA_FRASE_JUSTIFICATIVA_MUITO_GRANDE = 9395,
    // the value is the code vota::IIniciaJustificativa's constructor (target fn 3624) throws; the name is chosen from
    // its message, "Confirmação de justificativa nula": no evidence names it
    EUE_VOTA_CONFIRMACAO_JUSTIFICATIVA_NULA = 9396,
    // the value is the code vota::CControlaReconhecimento::AvancaTentativa (target fn 5406) throws; the name is chosen
    // from its message, "Limite de tentativas atingido.": no evidence names it
    EUE_VOTA_LIMITE_TENTATIVAS_ATINGIDO = 9397,
    // the value is the code vota::CControlaReconhecimento::AvancaVerificacao (record ccontrolareconhecimento.cpp:176,
    // inlined into target fn 10447) throws; the name is chosen from its message, "Limite de verificações de dado do
    // eleitor atingido.": no evidence names it
    EUE_VOTA_LIMITE_VERIFICACOES_ATINGIDO = 9398,
    // the value is the code vota::CPedeDigital::StartState (target fn 10468, record cpededigital.cpp:115) throws; the
    // name is chosen from its message, "Biometria desativada na configuração da eleição, fluxo indevido.": no evidence
    // names it
    EUE_VOTA_BIOMETRIA_DESATIVADA = 9400,
    // the values are the codes CInformacaoThreadOperador's four getters throw (target fns 10562, 10561, 10560, 10559);
    // the names are chosen from their messages and their getters, "Identidade não registrada" and "Tipo de identidade
    // não registrado": no evidence names them
    EUE_VOTA_IDENTIDADE_DIGITADA_NAO_REGISTRADA = 9401,
    EUE_VOTA_TIPO_IDENTIDADE_NAO_REGISTRADO = 9402,
    EUE_VOTA_IDENTIDADE_ELEITOR_NAO_REGISTRADA = 9403,
    EUE_VOTA_IDENTIDADE_PRINCIPAL_NAO_REGISTRADA = 9404,
    // the value is the code vota::CMostraQRCodeCertificado::ProcessInput (target fn 12038, record
    // cmostraqrcodecertificado.cpp:39) throws; the name is chosen from its message, "Número de inputs inválido": no
    // evidence names it
    EUE_VOTA_QRCODE_CERTIFICADO_NUMERO_INPUTS_INVALIDO = 9408,
    // the value is the code vota::TipoToStr throws (record cinformacaothreadoperador.cpp:40, inlined into target fn
    // 10586); the name is chosen from its message, "Tipo de identidade do eleitor inválido": no evidence names it
    EUE_VOTA_TIPO_IDENTIDADE_INVALIDO = 9409,
    // the value is the code vota::CControlaReconhecimento::AvancaProximoDedo1x4 (record
    // ccontrolareconhecimento.cpp:187, inlined into target fn 10465) throws; the name is chosen from its message, "Fim
    // da verificação 1x4 atingido.": no evidence names it
    EUE_VOTA_FIM_VERIFICACAO_1X4 = 9399,
    // the values are the codes vota::testeteclado::CTesteTeclado::ProcessInput (target fn 11804, records
    // ctesteteclado.cpp:60 and :81) throws, when the key just tested and when the next one is not on the screen; the
    // names are chosen from their message, "Tecla não encontrada: <tecla>", and that order: no evidence names them
    EUE_VOTA_TESTE_TECLADO_TECLA_ATUAL_NAO_ENCONTRADA = 9361,
    EUE_VOTA_TESTE_TECLADO_PROXIMA_TECLA_NAO_ENCONTRADA = 9362,
    // the values are the codes vota::CAjusteInicial::InicioVota throws (records cajusteinicial.cpp:170 and :178,
    // inlined into target fn 7160) when the vote is closed and its closing state is none it knows, and when the vote's
    // state is none it knows; the names are chosen from their messages, "Estado encerramento nao conhecido = {}" and
    // "Estado nao conhecido = {}", and the class: no evidence names them
    EUE_VOTA_AJUSTE_INICIAL_ESTADO_ENCERRAMENTO_DESCONHECIDO = 9303,
    EUE_VOTA_AJUSTE_INICIAL_ESTADO_DESCONHECIDO = 9304,
    // the values are the codes vota::CAjusteInicial::ValidaTemposDesligamento throws (records cajusteinicial.cpp:74,
    // :79 and :84, inlined into target fn 7160); the names are chosen from their messages, "Tempo limite de uso de
    // bateria interna inválido", "Tempo de aviso de desligamento por uso da bateria interna inválido" and "Tempo de
    // aviso de desligamento não pode ser maior que o tempo para desligar a urna": no evidence names them
    EUE_VOTA_TEMPO_LIMITE_BATERIA_INTERNA_INVALIDO = 9405,
    EUE_VOTA_TEMPO_AVISO_DESLIGAMENTO_INVALIDO = 9406,
    EUE_VOTA_TEMPO_AVISO_DESLIGAMENTO_MAIOR_QUE_LIMITE = 9407,
    // the values are the codes vota::CVisualizarCandidatos::StartState (target fn 11876, records
    // cvisualizarcandidatos.cpp:132 and :140) throws when no candidature passes the filters and when the screen does not
    // hold one input field; the names are chosen from their messages, "Nenhuma candidatura a ser exibida" and "Número de
    // inputs inválido", and the class: no evidence names them
    EUE_VOTA_VISUALIZAR_CANDIDATOS_SEM_CANDIDATURA = 9378,
    EUE_VOTA_VISUALIZAR_CANDIDATOS_NUMERO_INPUTS_INVALIDO = 9379,
    // the value is the code the substitutes' lambda of vota::CTelasVota::CriaTelaVisualizacaoCandidato (target fn 12272,
    // record ctelasvota.cpp:3366) throws; the name is chosen from its message, "Sem suporte a mais de 2 suplentes": no
    // evidence names it
    EUE_VOTA_VISUALIZACAO_CANDIDATO_SUPLENTES_DEMAIS = 9356,
};

using CUeVotaError = ecourna::api::exception::CBaseError<EUeVotaError, ecourna::api::exception::SErrorLimits{9300, 9500}>;

} // namespace vota
