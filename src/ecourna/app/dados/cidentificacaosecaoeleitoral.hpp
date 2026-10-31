#pragma once
#include "ecourna/app/dados/cmunicipiozona.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace ecourna::app::dados {

// An electoral section: its municipality and zone (@0, 8 B), its polling place (@8) and its number (@12). 16 bytes.
// The layout and the constructor's parameters are the converter's (fns 9129, 9127) and fn 5110's; the names follow
// ModuloTiposEleitorais::IdentificacaoSecaoEleitoral.
class CIdentificacaoSecaoEleitoral {
public:
    CIdentificacaoSecaoEleitoral(const CMunicipioZona& municipioZona, TLocalID local, TSecaoID secao);

    CMunicipioZona GetMunicipioZona() const { return m_municipioZona; }
    TLocalID GetLocal() const { return m_local; }
    TSecaoID GetSecao() const { return m_secao; }

private:
    CMunicipioZona m_municipioZona;
    TLocalID m_local;
    TSecaoID m_secao;
};

} // namespace ecourna::app::dados
