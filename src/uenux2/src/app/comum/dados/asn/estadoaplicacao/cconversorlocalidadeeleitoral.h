#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

class CConversorLocalidadeEleitoral
    : public IConversorASN<ModuloEstadoGeralUrna::DadoSecao, md::estadoaplicacao::CLocalidadeEleitoral> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
