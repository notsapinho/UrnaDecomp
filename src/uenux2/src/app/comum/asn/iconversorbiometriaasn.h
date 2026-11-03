#pragma once

#include <format>
#include <sstream>
#include <typeinfo>

#include "app/comum/asn/euecomumasnerror.h"
#include "asn1/asn1.h"

namespace comum::md {
class CParametro;
} // namespace comum::md

namespace comum::asn {

// Converts between a generated ASN.1 entity and a comum data class under a parameter (the records name it
// md::CParametro, whose header this tree does not have: declared here, its path not recovered). The records give the
// class, its Desconverte (line 62) and the default DoConverte, which throws (line 81). Desconverte is written from fn
// 1937, comum::CEleitorDetalhe::GetBiometria, which holds it behind a frame of its own: IConversorASN's Desconverte
// with the parameter passed on to slot 3 (its lines but the throw's are chosen). DoDesconverte's slot is the derived
// class's in the one instance the target has; that the base declares it pure is chosen.
template <typename ENTIDADE, typename DADO>
class IConversorBiometriaASN {
public:
    typedef ENTIDADE TEntidade;
    typedef DADO TDado;

    virtual ~IConversorBiometriaASN() {}

    // (original lines 30-56: content not recovered)
#line 57
    TDado Desconverte(const TEntidade& entidade, const md::CParametro& parametro) const
    {
        if (!entidade.isValid() || !entidade.isStrictlyValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, typeid(TEntidade).name(), entidade);
            throw CUeComumAsnError(EUE_COMUM_ASN_ENTIDADE_BIOMETRIA_INVALIDA, std::format("Entidade está inválida: {}", erro.str()));
        }
        return DoDesconverte(entidade, parametro);
    }

// (original lines 67-77: content not recovered)
#line 78
protected:
    virtual TEntidade DoConverte(const TDado& /*dado*/, const md::CParametro& /*parametro*/) const
    {
        throw CUeComumAsnError(EUE_COMUM_ASN_DOCONVERTE_BIOMETRIA_NAO_IMPLEMENTADO, std::format("Método DoConverte() não implementado para {}", typeid(TEntidade).name()));
    }

    virtual TDado DoDesconverte(const TEntidade& entidade, const md::CParametro& parametro) const = 0;
};

} // namespace comum::asn
