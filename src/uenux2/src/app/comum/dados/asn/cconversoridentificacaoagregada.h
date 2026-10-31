#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "asn1/modules/ModuloLocal.h"

namespace comum::asn {

class CConversorIdentificacaoAgregada : public IConversorASN<ModuloLocal::IdentificacaoAgregada, md::CIdentificacaoAgregada> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
