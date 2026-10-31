#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

// RTTI names the class and its base (vtable @1568172, slots 2 and 3 target fns 11397 and 11398). The records name the
// file and the two helpers, ConverteEstadoUrna and DesconverteEstadoUrna (cconversorestadogeral.cpp:87 to :110).
class CConversorEstadoGeral
    : public IConversorASN<ModuloEstadoGeralUrna::EstadoGeralUrna, md::estadoaplicacao::CEstadoGeral> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    EEstadoUrna DesconverteEstadoUrna(const ModuloEstadoGeralUrna::EstadoUrna& estado) const;
    ModuloEstadoGeralUrna::EstadoUrna ConverteEstadoUrna(const EEstadoUrna estado) const;
};

} // namespace comum::asn
