#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/municipiozona/ccomplementosmunicipiosuf.h"
#include "asn1/modules/ModuloComplementosMunicipios.h"

namespace comum::asn {

// Reads the municipalities' complements of the one UF an entity holds; the conversion the other way is the base's
// default DoConverte (the vtable's slot 2 is IConversorASN's, target fn 11380). RTTI names the class and its base
// (vtable @1569612), the record of DoDesconverte's throw its file.
class CConversorComplementosMunicipios
    : public IConversorASN<ModuloComplementosMunicipios::EntidadeComplementosMunicipios, md::CComplementosMunicipiosUF> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
