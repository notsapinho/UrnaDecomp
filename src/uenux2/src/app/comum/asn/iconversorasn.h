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
    virtual TEntidade DoConverte(const TDado& dado) const;

    // (original lines 88-93: content not recovered)
#line 94
    virtual TDado DoDesconverte(const TEntidade& entidade) const;
};

} // namespace comum::asn

// <stubs>
// f11421 · 29 B · unmatched · placement: link order · name unknown
// void f11421(i32, i32, i32) { ... }

// f11415 · 29 B · unmatched · placement: link order · name unknown
// void f11415(i32, i32, i32) { ... }

// f11374 · 29 B · unmatched · placement: link order · name unknown
// void f11374(i32, i32, i32) { ... }

// f11372 · 29 B · unmatched · placement: link order · name unknown
// void f11372(i32, i32, i32) { ... }

// f11370 · 29 B · unmatched · placement: link order · name unknown
// void f11370(i32, i32, i32) { ... }

// f11446 · 29 B · unmatched · placement: link order · name unknown
// void f11446(i32, i32, i32) { ... }

// f11444 · 29 B · unmatched · placement: link order · name unknown
// void f11444(i32, i32, i32) { ... }

// f11439 · 29 B · unmatched · placement: link order · name unknown
// void f11439(i32, i32, i32) { ... }

// f11409 · 29 B · unmatched · placement: link order · name unknown
// void f11409(i32, i32, i32) { ... }

// f11376 · 29 B · unmatched · placement: link order · name unknown
// void f11376(i32, i32, i32) { ... }

// f10275 · 29 B · unmatched · name unknown
// void f10275(i32, i32, i32) { ... }

// f10272 · 29 B · unmatched · name unknown
// void f10272(i32, i32, i32) { ... }

// f10265 · 29 B · unmatched · name unknown
// void f10265(i32, i32, i32) { ... }
// </stubs>
