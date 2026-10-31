#pragma once

// comum::asn::Utils: the conversions between the ASN.1 modules' types and comum's that the converters share. The
// records name the class and show every member static; the path is util.cpp's, whose records name it. No record names
// this header, so its path is chosen.
//
// The enumerators of md::ETipoAbrangencia are chosen: only their values are evidence (the range DesconverteAbrangencia
// accepts), and so is where it is declared. The records print ETipoLocalVotacao unqualified and ETipoAbrangencia as
// md::, from inside comum::asn.

#include <format>
#include <type_traits>

#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "app/comum/etipolocalvotacao.h"
#include "app/comum/eurnafase.h"
#include "app/comum/eurnaturno.h"
#include "asn1/modules/ModuloCandidatos.h"
#include "asn1/modules/ModuloTiposCadastro.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum {

namespace md {

enum ETipoAbrangencia {
    ABRANGENCIA_MUNICIPAL,
    ABRANGENCIA_ESTADUAL,
    ABRANGENCIA_FEDERAL,
};

} // namespace md

namespace asn {

class Utils {
public:
    static ModuloTiposEleitorais::Fase ConverteFase(const EUrnaFase& fase);
    static EUrnaFase DesconverteFase(const ModuloTiposEleitorais::Fase& fase);
    static md::ETipoAbrangencia DesconverteAbrangencia(ModuloTiposEleitorais::TipoAbrangencia::NamedNumber abrangencia);
    static ModuloTiposEleitorais::TipoAbrangencia::NamedNumber ConverteAbrangencia(md::ETipoAbrangencia abrangencia);
    static md::CSexo::ESexo DesconverteSexo(ModuloTiposEleitorais::CodigoSexo::NamedNumber sexo);
    static ModuloTiposEleitorais::Turno ConverteTurno(EUrnaTurno turno);
    static EUrnaTurno DesconverteTurno(ModuloTiposEleitorais::Turno turno);
    static ModuloTiposCadastro::TipoLocalVotacao ConverteTipoLocalVotacao(ETipoLocalVotacao tipo);
    static ETipoLocalVotacao DesconverteTipoLocalVotacao(ModuloTiposCadastro::TipoLocalVotacao tipo);
};

} // namespace asn

} // namespace comum

// std::format has no formatter for an enum, so the target's throws pass one as a handle (type code 15). Evidence: the
// handles of EUrnaFase and ETipoLocalVotacao (chosen as plain enums of non-negative values) hold fn 536, whose char
// presentation tests `>= 128` unsigned (formatter<unsigned int>), and the handle of the generated
// ModuloTiposEleitorais::TipoAbrangencia::NamedNumber, an `int` enum since it has unknownEnumeration_ = -1, holds fn
// 1711, which tests the signed range (formatter<int>). That one template over the underlying type serves them is
// chosen; an explicit specialization per enum gives the same bodies (the fragment's measurement).
template <typename E>
    requires std::is_enum_v<E>
struct std::formatter<E> : std::formatter<std::underlying_type_t<E>> {
    template <typename FormatContext>
    auto format(E valor, FormatContext& contexto) const
    {
        return std::formatter<std::underlying_type_t<E>>::format(static_cast<std::underlying_type_t<E>>(valor), contexto);
    }
};
