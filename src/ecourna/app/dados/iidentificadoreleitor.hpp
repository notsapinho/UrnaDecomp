#pragma once
#include <compare>
#include <memory>
#include <string>

#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace ecourna::app::dados {

class IIdentificadorEleitor {
public:
    IIdentificadorEleitor(TTipoIdentificadorEleitor tipo, const std::string& numero, uebyte tamanho);
    virtual ~IIdentificadorEleitor() = default;

    virtual std::string Formatado() const = 0;

    int GetTipo() const { return m_tipo; }
    std::string GetNumero() const;
    uebyte GetTamanho() const { return m_tamanho; }

    // What std::map<CNumeroInscricaoEleitoral, ...>'s find (target fn 3741) compares: the type as unsigned, which is why
    // m_tipo is the enum, then the text, then the size. operator< written out and over std::tie give other bytes.
    auto operator<=>(const IIdentificadorEleitor&) const = default;

private:
    ETipoIdentificadorEleitor m_tipo;
    std::string m_numero;
    uebyte m_tamanho;
};

using TSharedIdentificadorEleitor = std::shared_ptr<IIdentificadorEleitor>;

} // namespace ecourna::app::dados
