#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/municipiozona/ccomplementomunicipio.h"
#include "asn1/modules/ModuloComplementosMunicipios.h"

namespace comum::asn {

class CConversorComplementoMunicipio : public IConversorASN<ModuloComplementosMunicipios::ComplementoMunicipio, md::CComplementoMunicipio> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
