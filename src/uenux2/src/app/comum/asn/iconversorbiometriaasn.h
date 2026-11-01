#pragma once

#include <format>
#include <typeinfo>

#include "app/comum/asn/euecomumasnerror.h"
#include "asn1/asn1.h"

namespace comum::md {
class CParametro;
} // namespace comum::md

namespace comum::asn {

// Converts between a generated ASN.1 entity and a comum data class under a parameter (the records name it
// md::CParametro, whose header this tree does not have: declared here, its path not recovered). The records give the
// class, its Desconverte (line 62, fn 1937 holds it inlined, not written) and the default DoConverte, which throws
// (line 81). DoDesconverte's slot is the derived class's in the one instance the target has; that the base declares
// it pure is chosen.
template <typename ENTIDADE, typename DADO>
class IConversorBiometriaASN {
public:
    typedef ENTIDADE TEntidade;
    typedef DADO TDado;

    virtual ~IConversorBiometriaASN() {}

// (original lines 28-77: content not recovered)
#line 78
protected:
    virtual TEntidade DoConverte(const TDado& /*dado*/, const md::CParametro& /*parametro*/) const
    {
        throw CUeComumAsnError(EUE_COMUM_ASN_DOCONVERTE_BIOMETRIA_NAO_IMPLEMENTADO, std::format("Método DoConverte() não implementado para {}", typeid(TEntidade).name()));
    }

    virtual TDado DoDesconverte(const TEntidade& entidade, const md::CParametro& parametro) const = 0;
};

} // namespace comum::asn
