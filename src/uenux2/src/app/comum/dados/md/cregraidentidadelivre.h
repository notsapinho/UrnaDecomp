#pragma once

#include <string>

#include "app/comum/dados/md/iregraidentidade.h"

namespace comum::md {

// comum::md::CRegraIdentidadeLivre: the rule of a free-form identity number (RTTI: si_class of IRegraIdentidade;
// vtable @1574644 [174, 144, 11273, 11274, 371]). The member names are the base's, chosen (iregraidentidade.h).
// GetTipo is fn 11273 (`return 3`) and ValidaDigitoVerificador fn 371 (`return true`), bodies binaryen merges with
// other classes', so whether they were inline is not recovered; they are written inline here.
class CRegraIdentidadeLivre : public IRegraIdentidade {
public:
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipo() const override
    {
        return ecourna::app::dados::TipoIDNumeroLivre;
    }
    std::string Formata(const std::string& numero) const override;
    bool ValidaDigitoVerificador(const std::string&) const override { return true; }
};

} // namespace comum::md
