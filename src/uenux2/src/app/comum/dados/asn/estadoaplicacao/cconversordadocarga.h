#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

class CConversorDadoCarga : public IConversorASN<ModuloEstadoGeralUrna::DadoCarga, md::estadoaplicacao::CDadoCarga> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    ModuloEstadoGeralUrna::TipoUrnaOperacao ConverteTipoUrna(const EUrnaTipo tipo) const;
    EUrnaTipo DesconverteTipoUrna(const ModuloEstadoGeralUrna::TipoUrnaOperacao& tipo) const;
    ModuloTiposEcoUrna::ModeloEquipamento ConverteModelo(const EUrnaModelo modelo) const;
    EUrnaModelo DesconverteModelo(const ModuloTiposEcoUrna::ModeloEquipamento& modelo) const;
};

} // namespace comum::asn
