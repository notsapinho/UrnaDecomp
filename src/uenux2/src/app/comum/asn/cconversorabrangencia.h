#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/md/cabrangencia.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

class CConversorAbrangencia : public IConversorASN<ModuloTiposEleitorais::Abrangencia, md::CAbrangencia> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
