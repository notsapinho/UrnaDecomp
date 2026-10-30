#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralsa.h"
#include "asn1/modules/ModuloEstadoGeralSA.h"

namespace comum::asn {

class CConversorEstadoGeralSA
    : public IConversorASN<ModuloEstadoGeralSA::EstadoGeralSA, md::estadoaplicacao::CEstadoGeralSA> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    ModuloEstadoGeralSA::EstadoSA ConverteEstadoSA(const EEstadoSA estado) const;
    EEstadoSA DesconverteEstadoSA(const ModuloEstadoGeralSA::EstadoSA& estado) const;
};

} // namespace comum::asn
