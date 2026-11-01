#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

// The error class's RTTI, CBaseError<vota::EUeVotaError, SErrorLimits{9300, 9500}>, gives the enum's name, its
// namespace and its limits. This file's path and the CUeVotaError alias name are chosen, after api/util/eueutilerror.h
// and its CUeUtilError: no record names the file and no evidence names the alias.

namespace vota {

enum EUeVotaError {
    // the values are the codes the GetTelaCargoAtual(const std::string &) of vota::CConfirmaVotoEmCargo and
    // vota::CConfirmaVotoSemCandidato throw (target fns 5928 and 4483, which pass them to fn 3921); the names are chosen
    // from the message, "<caller> - o cargo atual nao esta posicionado", and the class: no evidence names them
    EUE_VOTA_CONFIRMA_VOTO_EM_CARGO_CARGO_NAO_POSICIONADO = 9306,
    EUE_VOTA_CONFIRMA_VOTO_SEM_CANDIDATO_CARGO_NAO_POSICIONADO = 9307,
    // the value is the code vota::NomeTela (target fn 6718) throws; the name is chosen from its message, "Tela
    // inválida {}": no evidence names it
    EUE_VOTA_TELA_INVALIDA = 9327,
    // the value is the code vota::CTelasCargo::GetTela (record ctelascargo.cpp:80, inlined into target fn 4135)
    // throws; the name is chosen from its message, "Cargo {} não possui [{}]": no evidence names it
    EUE_VOTA_CARGO_NAO_POSSUI_TELA = 9330,
    // the value is the code vota::CTelasVota::GetTelaCargo (target fn 4135, record ctelasvota.cpp:3534) throws; the
    // name is chosen from its message, "Nao existe o conjunto de telas associado ao cargo id {}": no evidence names it
    EUE_VOTA_CONJUNTO_TELAS_INEXISTENTE = 9358,
    // the value is the code vota::IQRCodeBUDS::IQRCodeBUDS (inlined into target fn 1956) throws; the name is chosen
    // from its message, "Vetor de partes vazio": no evidence names it
    EUE_VOTA_VETOR_PARTES_VAZIO = 9372,
    // the values are the codes the GetTelaCargoAtual of vota::CPedeMajoritario, vota::CCompletaProporcional and
    // vota::CPedeProporcional throw (target fns 5920, 5931 and 5923, which pass them to fns 6050 and 3921); the names
    // are chosen from the message, "O cargo atual nao esta posicionado", and the class: no evidence names them
    EUE_VOTA_PEDE_MAJORITARIO_CARGO_NAO_POSICIONADO = 9380,
    EUE_VOTA_COMPLETA_PROPORCIONAL_CARGO_NAO_POSICIONADO = 9384,
    EUE_VOTA_PEDE_PROPORCIONAL_CARGO_NAO_POSICIONADO = 9386,
    // the value is the code vota::IIniciaJustificativa's constructor (target fn 3624) throws; the name is chosen from
    // its message, "Confirmação de justificativa nula": no evidence names it
    EUE_VOTA_CONFIRMACAO_JUSTIFICATIVA_NULA = 9396,
    // the value is the code vota::CControlaReconhecimento::AvancaTentativa (target fn 5406) throws; the name is chosen
    // from its message, "Limite de tentativas atingido.": no evidence names it
    EUE_VOTA_LIMITE_TENTATIVAS_ATINGIDO = 9397,
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
};

using CUeVotaError = ecourna::api::exception::CBaseError<EUeVotaError, ecourna::api::exception::SErrorLimits{9300, 9500}>;

} // namespace vota
