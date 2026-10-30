#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/cinfomunicipio.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/md/cidentificacaournacontingencia.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 140 bytes. ModuloLocal::Local's fields, in CConversorLocal::DoConverte's order (target fn
// 11451), and its destructor (fn 5744) give the country's code at +0 and name at +4, the state's abbreviation at +16 and
// name at +28, the municipality at +40, then two optionals, the section at +84 (flag +120) and the contingency urn at
// +124 (flag +136). DoDesconverte (fn 11452) holds both constructors and calls ValidaCriacao once for each, so they are
// not declared here: they come with 11452's reconstruction. TemSecao's and TemContingencia's names are chosen, and so
// are the member names.
class CLocal {
public:
    const std::string& GetSiglaUF() const { return m_siglaUF; }
    const CInfoMunicipio& GetMunicipio() const { return m_municipio; }
    bool TemSecao() const { return m_secao.has_value(); }
    bool TemContingencia() const { return m_contingencia.has_value(); }
    const CSecaoEleitoral& GetSecao() const;
    const CIdentificacaoUrnaContingencia& GetContingencia() const;

private:
    void ValidaCriacao() const;

    uedword m_codigoPais;
    std::string m_nomePais;
    std::string m_siglaUF;
    std::string m_nomeUF;
    CInfoMunicipio m_municipio;
    std::optional<CSecaoEleitoral> m_secao;
    std::optional<CIdentificacaoUrnaContingencia> m_contingencia;
};

} // namespace comum::md
