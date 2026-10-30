#pragma once

#include <string>

#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum::md {

// Recovered: the layout, 16 bytes, the identifier's text at +0 and its type at +12. GetIdentidadeEleitor and
// GetIdentidadePrincipalEleitor of vota::impl::CInformacaoThreadOperador (target fns 10560 and 10559, records
// cinformacaothreadoperador.cpp:494 and :504) return one by value: they copy the std::string, then the 4-byte member at
// +12. That member's type is a choice: ETipoIdentificadorEleitor is the type the voter's identifiers carry
// (CEleitorDecorator::GetIdentidadePorTipo, record celeitordecorator.cpp:39). No record names this header's file: it
// goes with the comum::md voter classes, whose records are in md/eleitor/. The member names are not in the target, nor
// are the two getters' (fns 708, 5775 and 5776 read the two members).
class CEleitorIdentidade {
public:
    const std::string& GetIdentificador() const { return m_identificador; }
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipo() const { return m_tipo; }

private:
    std::string m_identificador;
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipo;
};

} // namespace comum::md
