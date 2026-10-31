#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/md/cseguranca.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

class CConversorSeguranca : public IConversorASN<ModuloTiposEleitorais::Seguranca, md::CSeguranca> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
