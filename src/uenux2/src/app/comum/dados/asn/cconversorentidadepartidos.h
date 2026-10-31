#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/centidadepartidos.h"
#include "asn1/modules/ModuloPartidos.h"

namespace comum::asn {

class CConversorEntidadePartidos : public IConversorASN<ModuloPartidos::EntidadePartidos, md::CEntidadePartidos> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
