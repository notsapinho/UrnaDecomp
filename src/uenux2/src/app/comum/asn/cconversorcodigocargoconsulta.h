#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

class CConversorCodigoCargoConsulta : public IConversorASN<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
