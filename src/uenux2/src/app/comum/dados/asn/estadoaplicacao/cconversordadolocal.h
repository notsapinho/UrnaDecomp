#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cdadolocal.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

class CConversorDadoLocal : public IConversorASN<ModuloEstadoGeralUrna::DadoLocal, md::estadoaplicacao::CDadoLocal> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
