#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// api::EUePersistenciaError, SErrorLimits{6800, 6850}: the typeinfo of CBaseError<api::EUePersistenciaError, ...> gives
// the enum's name, namespace and limits. The values are the codes the three defaults of
// api/persistencia/iuenuxgenericdao.h and CDAORepositorio::Entregar (cdaorepositorio.hpp) throw. Each enumerator's name
// is chosen from its message ("<member> nao implementada para entidade ", "Classe DAO {} nao foi registrada."): no
// evidence names one. The path, beside the headers that throw them, is chosen too.
enum EUePersistenciaError {
    EUE_PERSISTENCIA_DAO_NAO_REGISTRADA = 6802,
    EUE_PERSISTENCIA_EXCLUIR_NAO_IMPLEMENTADA = 6804,
    EUE_PERSISTENCIA_EXCLUIR_ID_NAO_IMPLEMENTADA = 6805,
    EUE_PERSISTENCIA_ATUALIZAR_NAO_IMPLEMENTADA = 6806,
};

using CUePersistenciaError =
    ecourna::api::exception::CBaseError<EUePersistenciaError, ecourna::api::exception::SErrorLimits{6800, 6850}>;

} // namespace api
