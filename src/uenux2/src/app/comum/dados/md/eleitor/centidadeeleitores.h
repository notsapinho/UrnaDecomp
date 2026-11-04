#pragma once

#include <optional>
#include <vector>

#include "app/comum/dados/md/eleitor/celeitor.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cseguranca.h"

namespace comum::md {

// The voters' file entity, as comum::asn::CConversorEntidadeEleitores builds it from ModuloEleitores::EntidadeEleitores:
// its header, the section's identification, the optional seguranca and the voters, in the order of the entity's fields.
// The class's name is the RTTI of the converter's base, comum::asn::IConversorParcialASN<ModuloEleitores::
// EntidadeEleitores, comum::md::CEntidadeEleitores, comum::asn::CVisitanteEleitor>. Recovered: the layout, 60 bytes,
// from the converter's slot 2 (target fn 11411), which builds it in its result: the CCabecalhoEntidade at +0 (copied
// from IConversorASN<CabecalhoEntidade, CCabecalhoEntidade>::Desconverte's result, fn 3738), a 32-bit word at +20 and
// 16-bit ones at +24 and +26 (the identificacao's municipioZona's two fields and its secao), a std::optional of the
// 16-byte CSeguranca at +28 (its flag at +44: 1 with the entity's seguranca, through fn 3730, else 0) and a std::vector
// of 104-byte CEleitor at +48 (fn 946 per voter); and from fn 11523, which destroys it in that order's reverse (the
// voters, then the optional) after copying the voters out. The member and getter names, the types of the three words
// (comum's section aliases, of those widths), the constructor's parameter order (the members') and its being inline are
// chosen.
class CEntidadeEleitores {
public:
    CEntidadeEleitores(const CCabecalhoEntidade& cabecalho, TMunicipioID municipio, TZonaID zona, TSecaoID secao,
        const std::optional<CSeguranca>& seguranca, const std::vector<CEleitor>& eleitores)
        : m_cabecalho(cabecalho), m_municipio(municipio), m_zona(zona), m_secao(secao), m_seguranca(seguranca),
          m_eleitores(eleitores)
    {
    }

    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    TMunicipioID GetMunicipio() const { return m_municipio; }
    TZonaID GetZona() const { return m_zona; }
    TSecaoID GetSecao() const { return m_secao; }
    const std::optional<CSeguranca>& GetSeguranca() const { return m_seguranca; }
    const std::vector<CEleitor>& GetEleitores() const { return m_eleitores; }

private:
    CCabecalhoEntidade m_cabecalho;
    TMunicipioID m_municipio;
    TZonaID m_zona;
    TSecaoID m_secao;
    std::optional<CSeguranca> m_seguranca;
    std::vector<CEleitor> m_eleitores;
};

} // namespace comum::md
