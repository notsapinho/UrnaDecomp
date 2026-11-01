#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/cinfomunicipio.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/md/cidentificacaournacontingencia.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 140 bytes. ModuloLocal::Local's fields, in CConversorLocal::DoConverte's order (target fn
// 11451), and its destructor (fn 5744) give the idPE at +0 (DoConverte stores it into Local's idPE) and the country's
// name at +4, the state's abbreviation at +16 and
// name at +28, the municipality at +40, then two optionals, the section at +84 (flag +120) and the contingency urn at
// +124 (flag +136). TemSecao's and TemContingencia's names are chosen, and so are the member names.
// The two constructors are inlined into their one caller, CConversorLocal::DoDesconverte (fn 11452), and have no index
// of their own; each is read from there: it copies the id, the three strings and the municipality, constructs one of
// the optionals from its argument, leaves the other empty and calls ValidaCriacao (fn 5673). The parameters are const
// references: 11452 copy-constructs each member straight from its own locals. The parameters' names and order after
// the members', and the constructors being defined in clocal.cpp (not in this header), are chosen.
class CLocal {
public:
    CLocal(uedword idPE, const std::string& nomePais, const std::string& siglaUF, const std::string& nomeUF,
           const CInfoMunicipio& municipio, const CSecaoEleitoral& secao);
    CLocal(uedword idPE, const std::string& nomePais, const std::string& siglaUF, const std::string& nomeUF,
           const CInfoMunicipio& municipio, const CIdentificacaoUrnaContingencia& contingencia);

    uedword GetIdPE() const { return m_idPE; }
    const std::string& GetNomePais() const { return m_nomePais; }
    const std::string& GetSiglaUF() const { return m_siglaUF; }
    const std::string& GetNomeUF() const { return m_nomeUF; }
    const CInfoMunicipio& GetMunicipio() const { return m_municipio; }
    bool TemSecao() const { return m_secao.has_value(); }
    bool TemContingencia() const { return m_contingencia.has_value(); }
    const CSecaoEleitoral& GetSecao() const;
    const CIdentificacaoUrnaContingencia& GetContingencia() const;

private:
    void ValidaCriacao() const;

    uedword m_idPE;
    std::string m_nomePais;
    std::string m_siglaUF;
    std::string m_nomeUF;
    CInfoMunicipio m_municipio;
    std::optional<CSecaoEleitoral> m_secao;
    std::optional<CIdentificacaoUrnaContingencia> m_contingencia;
};

} // namespace comum::md
