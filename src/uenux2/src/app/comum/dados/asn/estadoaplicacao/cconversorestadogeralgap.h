#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "asn1/modules/ModuloEstadoGeralGap.h"

namespace comum::md::estadoaplicacao {

class CEstadoGeralGap;

} // namespace comum::md::estadoaplicacao

namespace comum::asn {

// RTTI names the class and its base (vtable @1568488). DoConverte and DoDesconverte (target fns 11394 and 11395, slots
// 2 and 3) are written in cconversorestadogeralgap.cpp, which emits the vtable; each calls one of the two helpers below
// twice.
class CConversorEstadoGeralGap : public IConversorASN<ModuloEstadoGeralGap::EstadoGeralGap, md::estadoaplicacao::CEstadoGeralGap> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    EUrnaAplicativo DesconverteUrnaAplicativo(const ModuloEstadoGeralGap::UrnaAplicativo& aplicativo) const;
    ModuloEstadoGeralGap::UrnaAplicativo ConverteUrnaAplicativo(const EUrnaAplicativo aplicativo) const;
};

} // namespace comum::asn
