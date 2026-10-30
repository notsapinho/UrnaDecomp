#pragma once

#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/etipoimpedimento.h"
#include "asn1/modules/ModuloImpedidos.h"

namespace comum::md {
class CImpedido;
} // namespace comum::md

namespace comum::asn {

// DesconverteTipoImpedimento (target fn 5699) is the one member reconstructed. DoDesconverte (fn 11410, the class's only
// override) is declared and not defined, so nothing emits the vtable yet.
class CConversorImpedido : public IConversorASN<ModuloImpedidos::EntidadeImpedidos, std::vector<md::CImpedido>> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    md::ETipoImpedimento DesconverteTipoImpedimento(ModuloImpedidos::TipoImpedimento tipo) const;
};

} // namespace comum::asn
