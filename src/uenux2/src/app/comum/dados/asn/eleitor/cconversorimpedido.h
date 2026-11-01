#pragma once

#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/etipoimpedimento.h"
#include "asn1/modules/ModuloImpedidos.h"

namespace comum::md {
class CEleitorIdentidade;
class CImpedido;
} // namespace comum::md

namespace comum::asn {

// DoDesconverte (target fn 11410, the class's only override and so its key function), MontaEleitorIdentidade (record
// cconversorimpedido.cpp:40, which binaryen inlines into fn 11410) and DesconverteTipoImpedimento (fn 5699).
class CConversorImpedido : public IConversorASN<ModuloImpedidos::EntidadeImpedidos, std::vector<md::CImpedido>> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    md::CEleitorIdentidade MontaEleitorIdentidade(const ModuloTiposEleitorais::IdentificadorEleitor& identificador) const;
    md::ETipoImpedimento DesconverteTipoImpedimento(ModuloImpedidos::TipoImpedimento tipo) const;
};

} // namespace comum::asn
