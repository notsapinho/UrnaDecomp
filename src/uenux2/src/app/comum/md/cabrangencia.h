#pragma once

#include <string>

#include "app/comum/asn/util.h"
#include "app/comum/dados/md/municipiozona/cmunicipio.h"

namespace comum::md {

// The layout, 20 bytes, from the constructor (target fn 3739, records cabrangencia.cpp:31 to :51): the type at +0, the
// string at +4, the municipality at +16. The member and getter names are chosen, from the messages and from
// ModuloTiposEleitorais::IdentificacaoAbrangencia's fields.
class CAbrangencia {
public:
    CAbrangencia(ETipoAbrangencia tipo, const std::string& uf, TMunicipioID municipio);

    ETipoAbrangencia GetTipo() const { return m_tipo; }
    const std::string& GetUF() const { return m_uf; }
    TMunicipioID GetMunicipio() const { return m_municipio; }

private:
    ETipoAbrangencia m_tipo;
    std::string m_uf;
    TMunicipioID m_municipio;
};

} // namespace comum::md
