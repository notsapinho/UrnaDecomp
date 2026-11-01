#pragma once

#include <optional>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/iresultado.h"
#include "app/comum/gravadores/md/curna.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cseguranca.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 224 bytes, from the three constructors (target fns 3821, 5860 and 5861) and ValidaCriacao
// (fn 3822, records cenvelopegenerico.cpp:127 to :156): the entity's header (20 bytes copied) at +0, the phase at +20,
// a std::optional<CUrna> at +24 (engaged at +160), the municipality at +164, the zone at +168, a
// std::optional<TLocalID> at +172 (engaged at +176), the section at +180, the envelope's type at +184, a
// std::optional<CSeguranca> at +188 (engaged at +204), a std::vector of the content at +208 and the urna's type at
// +220, which fn 5860 takes from the CUrna it copies. The members follow ModuloEnvelopeGenerico::
// EntidadeEnvelopeGenerico's fields. The three getters' records (:96, :106, :117) print `const CUrna &`, `TLocalID` and
// `const CSeguranca &`, and the nested type's name `Tipo` is the records' (cconversorenvelopegenerico.cpp:168, :191).
// The local's std::optional is passed by value: comum::asn::CConversorEnvelopeGenerico::DoDesconverte (fn 10270) copies
// it into a slot of its own frame for each call, which a const reference does not give (unit 160's fragment has the
// measurement); the constructors' own bytes are the same either way.
// Chosen: the identifiers as iresultado.h's types, comum::EUrnaTipo, the content as uebyte, the other parameters' forms
// beyond what the bodies copy (const references, each copied: the vector is allocated and copied, not moved), and every
// member and enumerator name; the parameters' order is the wasm parameters'.
class CEnvelopeGenerico {
public:
    // CConversorEnvelopeGenerico::ConverteTipoEnvelope (fn 10271) maps 0 to 4 through a table to
    // ModuloEnvelopeGenerico::TipoEnvelope's 1, 2, 4, 5 and 6, and ValidaCriacao refuses 5 and above; the names
    // follow those enumerators.
    enum Tipo {
        ENVELOPE_BOLETIM_URNA,
        ENVELOPE_REGISTRO_DIGITAL_VOTO,
        ENVELOPE_BOLETIM_URNA_IMPRESSO,
        ENVELOPE_IMAGEM_BIOMETRIA,
        ENVELOPE_ZERESIMA_IMPRESSA,
    };

    CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, TMunicipioID municipio, TZonaID zona,
        std::optional<TLocalID> local, TSecaoID secao, Tipo tipo, const CSeguranca& seguranca,
        const std::vector<uebyte>& conteudo, EUrnaTipo tipoUrna);
    CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, const CUrna& urna, TMunicipioID municipio,
        TZonaID zona, std::optional<TLocalID> local, TSecaoID secao, Tipo tipo,
        const std::vector<uebyte>& conteudo);
    CEnvelopeGenerico(const CCabecalhoEntidade& cabecalho, EUrnaFase fase, TMunicipioID municipio, TZonaID zona,
        std::optional<TLocalID> local, TSecaoID secao, Tipo tipo, const std::vector<uebyte>& conteudo,
        EUrnaTipo tipoUrna);

    const CUrna& GetUrna() const;
    TLocalID GetLocal() const;
    const CSeguranca& GetSeguranca() const;

    // comum::asn::CConversorEnvelopeGenerico::DoConverte (fn 10271) reads these; the names are chosen. It tests the
    // urna's and the security's presence before it calls GetUrna and GetSeguranca, whose own tests binaryen keeps.
    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    EUrnaFase GetFase() const { return m_fase; }
    bool TemUrna() const { return m_urna.has_value(); }
    TMunicipioID GetMunicipio() const { return m_municipio; }
    TZonaID GetZona() const { return m_zona; }
    TSecaoID GetSecao() const { return m_secao; }
    Tipo GetTipo() const { return m_tipo; }
    bool TemSeguranca() const { return m_seguranca.has_value(); }
    const std::vector<uebyte>& GetConteudo() const { return m_conteudo; }
    EUrnaTipo GetTipoUrna() const { return m_tipoUrna; }

private:
    void ValidaCriacao() const;

    CCabecalhoEntidade m_cabecalho;
    EUrnaFase m_fase;
    std::optional<CUrna> m_urna;
    TMunicipioID m_municipio;
    TZonaID m_zona;
    std::optional<TLocalID> m_local;
    TSecaoID m_secao;
    Tipo m_tipo;
    std::optional<CSeguranca> m_seguranca;
    std::vector<uebyte> m_conteudo;
    EUrnaTipo m_tipoUrna;
};

} // namespace comum::md
