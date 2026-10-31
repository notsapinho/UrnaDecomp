#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

// DoConverte and DoDesconverte (target fns 11401, 11402, slots 2 and 3) are not reconstructed, so nothing here emits the
// vtable: ConverteTipoUrna and DesconverteTipoUrna, which each calls twice, are reached from the roots file.
class CConversorDadoCarga : public IConversorASN<ModuloEstadoGeralUrna::DadoCarga, md::estadoaplicacao::CDadoCarga> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    ModuloEstadoGeralUrna::TipoUrnaOperacao ConverteTipoUrna(const EUrnaTipo tipo) const;
    EUrnaTipo DesconverteTipoUrna(const ModuloEstadoGeralUrna::TipoUrnaOperacao& tipo) const;
};

} // namespace comum::asn
