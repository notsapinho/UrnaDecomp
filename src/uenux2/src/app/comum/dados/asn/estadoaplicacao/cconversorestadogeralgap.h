#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "asn1/modules/ModuloEstadoGeralGap.h"

namespace comum::md::estadoaplicacao {

class CEstadoGeralGap;

} // namespace comum::md::estadoaplicacao

namespace comum::asn {

// DoConverte and DoDesconverte (target fns 11394, 11395, slots 2 and 3) are not reconstructed and CEstadoGeralGap has no
// header yet, so nothing here emits the vtable: DesconverteUrnaAplicativo and ConverteUrnaAplicativo, which each calls
// twice, are reached from the roots file.
class CConversorEstadoGeralGap : public IConversorASN<ModuloEstadoGeralGap::EstadoGeralGap, md::estadoaplicacao::CEstadoGeralGap> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    EUrnaAplicativo DesconverteUrnaAplicativo(const ModuloEstadoGeralGap::UrnaAplicativo& aplicativo) const;
    ModuloEstadoGeralGap::UrnaAplicativo ConverteUrnaAplicativo(const EUrnaAplicativo aplicativo) const;
};

} // namespace comum::asn
