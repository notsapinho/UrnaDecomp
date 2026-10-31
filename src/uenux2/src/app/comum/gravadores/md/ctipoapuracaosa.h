#pragma once

#include <format>

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 8 bytes, from comum::asn::CConversorTipoApuracaoSA::DoDesconverte (target fn 10282), which
// holds the constructor, ValidaCriacao (record ctipoapuracaosa.cpp:40) and ValidaMotivoApuracao (:72) inlined (three
// stack frames in one body): the type of the count at +0 (i32.store, 1 to 4) and its reason
// at +4 (i32.store8; the record of ConverteMotivoApuracaoManual, cconversortipoapuracaosa.cpp:98, spells it
// `const uebyte`). comum::md::CUrna holds one in a std::optional at +124 (fn 2855 copies it with one i64 load).
// CConversorTipoApuracaoSA::DoConverte (fn 10283) maps the type 1 to 4 onto ModuloTiposResultadosEcoUrna::
// TipoApuracao's totalmenteManual to mistaMR and formats a bad one as a std::format handle through
// formatter<unsigned int> (its table slot 4452 holds fn 536), so the type is an enum with a formatter of its own, as
// app/comum/dados/md/estadoaplicacao/eurna.h writes them. Chosen: the enum's place in the class and the names of the
// enum, its enumerators (from the ASN.1 ones), the members and the getters, and that both checks are private.
class CTipoApuracaoSA {
public:
    enum ETipoApuracao {
        TIPO_TOTALMENTE_MANUAL = 1,
        TIPO_TOTALMENTE_ELETRONICA = 2,
        TIPO_MISTA_BU = 3,
        TIPO_MISTA_MR = 4,
    };

    CTipoApuracaoSA(ETipoApuracao tipoApuracao, uebyte motivoApuracao);

    ETipoApuracao GetTipoApuracao() const { return m_tipoApuracao; }
    uebyte GetMotivoApuracao() const { return m_motivoApuracao; }

private:
    void ValidaCriacao() const;
    void ValidaMotivoApuracao() const;

    ETipoApuracao m_tipoApuracao;
    uebyte m_motivoApuracao;
};

} // namespace comum::md

template <>
struct std::formatter<comum::md::CTipoApuracaoSA::ETipoApuracao> : comum::SFormatoEnum {};
