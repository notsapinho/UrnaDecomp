#pragma once

#include <format>
#include <sstream>
#include <typeinfo>

#include "app/comum/asn/euecomumasnerror.h"
#include "asn1/asn1.h"

namespace comum::asn {

// Converts between a generated ASN.1 entity and a comum data class: Converte/Desconverte validate the entity and
// call the virtual pair; the default DoConverte/DoDesconverte throw (records at lines 89 and 98).
template <typename ENTIDADE, typename DADO>
class IConversorASN {
public:
    typedef ENTIDADE TEntidade;
    typedef DADO TDado;

    virtual ~IConversorASN() {}

    // (original lines 22-49: content not recovered)
#line 50
    TEntidade Converte(const TDado& dado) const
    {
        TEntidade entidade = DoConverte(dado);
        if (!entidade.isValid() || !entidade.isStrictlyValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, typeid(TEntidade).name(), entidade);
            throw CUeComumAsnError(EUE_COMUM_ASN_ENTIDADE_ESTADO_INVALIDO, std::format("Entidade deixada em estado inválido: {}", erro.str()));
        }
        return entidade;
    }

    // (original lines 61-65: content not recovered)
#line 66
    TDado Desconverte(const TEntidade& entidade) const
    {
        if (!entidade.isValid() || !entidade.isStrictlyValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, typeid(TEntidade).name(), entidade);
            throw CUeComumAsnError(EUE_COMUM_ASN_ENTIDADE_INVALIDA, std::format("Entidade está inválida: {}", erro.str()));
        }
        return DoDesconverte(entidade);
    }

// (original lines 76-84: content not recovered)
#line 85
protected:

    virtual TEntidade DoConverte(const TDado& /*dado*/) const
    {
        throw CUeComumAsnError(EUE_COMUM_ASN_DOCONVERTE_NAO_IMPLEMENTADO, std::format("Método DoConverte() não implementado para {}", typeid(TEntidade).name()));
    }

    // (original lines 92-95: content not recovered)
#line 96
    virtual TDado DoDesconverte(const TEntidade& /*entidade*/) const
    {
        throw CUeComumAsnError(EUE_COMUM_ASN_DODESCONVERTE_NAO_IMPLEMENTADO, std::format("Método DoDesconverte() não implementado para {}", typeid(TEntidade).name()));
    }
};

} // namespace comum::asn
