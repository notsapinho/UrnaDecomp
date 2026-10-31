#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/municipiozona/cmunicipio.h"
#include "asn1/modules/ModuloTiposCadastro.h"

namespace comum::asn {

class CConversorMunicipio : public IConversorASN<ModuloTiposCadastro::Municipio, md::CMunicipio> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
