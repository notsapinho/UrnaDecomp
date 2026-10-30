#pragma once

#include <string>

#include "app/comum/dados/md/iregraidentidade.h"

namespace comum::md {

// comum::md::CRegraTitulo: the rule of the voter's registration number, the titulo de eleitor (RTTI: si_class of
// IRegraIdentidade; vtable @1574692 [174, 144, 434, 11271, 11272]). The member names are the base's, chosen
// (iregraidentidade.h). GetTipo is fn 434, a `return 1` binaryen merges with other classes' bodies, so whether it was
// inline is not recovered; it is written inline here. Formata is defined out of line, which makes it the key function,
// a choice: defined in the class, with ValidaDigitoVerificador the key function, it gives the same bytes and link
// order.
class CRegraTitulo : public IRegraIdentidade {
public:
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipo() const override
    {
        return ecourna::app::dados::TipoIDInscricaoEleitoral;
    }
    std::string Formata(const std::string& numero) const override;
    bool ValidaDigitoVerificador(const std::string& numero) const override;
};

} // namespace comum::md
