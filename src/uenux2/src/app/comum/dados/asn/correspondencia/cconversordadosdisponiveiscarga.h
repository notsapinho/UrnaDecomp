#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.h"
#include "asn1/modules/ModuloDadosDisponiveisCarga.h"

namespace comum::asn {

// Recovered: the class and its two slots, named by its RTTI (typeinfo 1565812, vtable @1565788, read from the data:
// ledger/vtables.json has no row for it), whose base is IConversorASN<ModuloDadosDisponiveisCarga::DadosDisponiveisCarga,
// comum::md::CDadosDisponiveisCarga>: DoConverte (slot 2, target fn 11424) and DoDesconverte (slot 3, fn 11423). Slots 0
// and 1 hold the shared bodies 174 and 144, as the sibling converters' do (CConversorSecaoEleitoral's, CConversorMunicipio's);
// as for them, no destructor is declared, a choice. No record names the class's file; the header's path and its file's
// are chosen (fragment 245 says from what).
class CConversorDadosDisponiveisCarga
    : public IConversorASN<ModuloDadosDisponiveisCarga::DadosDisponiveisCarga, md::CDadosDisponiveisCarga> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
