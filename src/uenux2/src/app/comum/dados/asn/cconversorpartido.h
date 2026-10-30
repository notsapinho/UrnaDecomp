#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/cpartido.h"
#include "asn1/modules/ModuloPartidos.h"

namespace comum::asn {

class CConversorPartido : public IConversorASN<ModuloPartidos::Partido, md::CPartido> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
