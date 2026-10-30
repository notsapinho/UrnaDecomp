#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

class CConversorNomesCargo : public IConversorASN<ModuloEleicao::NomesCargo, md::CNomesCargo> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
