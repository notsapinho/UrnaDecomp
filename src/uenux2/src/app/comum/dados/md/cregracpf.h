#pragma once

#include <string>

#include "app/comum/dados/md/iregraidentidade.h"

namespace comum::md {

// comum::md::CRegraCPF: the rule of the CPF number (RTTI: si_class of IRegraIdentidade; vtable @1574732 [174, 144,
// 2254, 11269, 11270]). The member names are the base's, chosen (iregraidentidade.h). GetTipo is fn 2254, a
// `return 2` binaryen merges with another body, so whether it was inline is not recovered; it is written inline here.
class CRegraCPF : public IRegraIdentidade {
public:
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipo() const override { return ecourna::app::dados::TipoIDCPF; }
    std::string Formata(const std::string& numero) const override;
    bool ValidaDigitoVerificador(const std::string& numero) const override;
};

} // namespace comum::md
