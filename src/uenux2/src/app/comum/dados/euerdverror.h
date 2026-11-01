#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// The names of 4661, 4666 to 4668, 4723 and 4724 are chosen from their messages (md::CVoto's, md::CVotosCargos' and
// md::CVotosEleicoesVota's constructors, fns 2256, 5643 and 5640): no evidence names them.
enum EUeRdvError {
    EUE_RDV_VOTO_INVALIDO = 4661,
    EUE_RDV_MAPA_VOTOS_VAZIO = 4666,
    EUE_RDV_VOTOS_NAO_MULTIPLO_ESCOLHAS = 4667,
    EUE_RDV_VOTOS_DIFERENTE_ESPERADO = 4668,
    EUE_RDV_CARGO_NAO_ENCONTRADO = 4671,
    EUE_RDV_GRUPO_VOTOS_VAZIO = 4723,
    EUE_RDV_CARGO_EM_MAIS_DE_UMA_ELEICAO = 4724,
    EUE_RDV_CANDIDATO_SEM_ELEICAO = 4725,
    EUE_RDV_LEGENDA_SEM_ELEICAO = 4726,
    EUE_RDV_PARTIDO_SEM_ELEICAO = 4727,
    EUE_RDV_NOMINAIS_SEM_ELEICAO = 4728,
    EUE_RDV_LEGENDAS_SEM_ELEICAO = 4729,
    EUE_RDV_NULOS_SEM_ELEICAO = 4730,
    EUE_RDV_BRANCOS_SEM_ELEICAO = 4731,
    EUE_RDV_CARGO_SEM_ELEICAO = 4732,
    EUE_RDV_VOTOS_SEM_ELEICAO = 4733,
    EUE_RDV_COMPARECIMENTO_SEM_ELEICAO = 4734,
};

using CUeRdvError = ecourna::api::exception::CBaseError<EUeRdvError, ecourna::api::exception::SErrorLimits{4650, 4850}>;

} // namespace api
