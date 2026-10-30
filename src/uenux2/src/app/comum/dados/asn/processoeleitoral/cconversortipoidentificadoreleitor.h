#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "asn1/modules/ModuloTiposEleitorais.h"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum::asn {

class CConversorTipoIdentificadorEleitor
    : public IConversorASN<ModuloTiposEleitorais::TipoIdentificadorEleitor,
                           ecourna::app::dados::ETipoIdentificadorEleitor> {
protected:
    ModuloTiposEleitorais::TipoIdentificadorEleitor DoConverte(const TDado& tipo) const override;
    ecourna::app::dados::ETipoIdentificadorEleitor DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
