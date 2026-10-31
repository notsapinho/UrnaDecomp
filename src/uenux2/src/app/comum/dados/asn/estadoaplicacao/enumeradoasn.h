#pragma once

// A generated ENUMERATED formats as its value. The seven table slots of target fn 1699 hold one handle body, which loads
// the value at +8 and extends it to i64 before it formats it, and the throws pass the entity itself (fn 5694 stores its
// reference as the handle's pointer). The cast is what extends it: formatter<...>::format is a template on its argument,
// so formatter<long long> without the cast formats an int. The path and the template are chosen; one specialization per
// class gives the same bodies (measured on TipoUrnaOperacao).

#include <concepts>
#include <format>

#include "asn1/asn1.h"

template <typename E>
    requires std::derived_from<E, ASN1::ENUMERATED>
struct std::formatter<E> : std::formatter<long long> {
    template <typename FormatContext>
    auto format(const E& valor, FormatContext& contexto) const
    {
        return std::formatter<long long>::format(static_cast<long long>(valor.asInt()), contexto);
    }
};
