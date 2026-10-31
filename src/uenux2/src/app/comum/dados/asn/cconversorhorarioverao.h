#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/chorarioverao.h"
#include "asn1/modules/ModuloComplementosMunicipios.h"

namespace comum::asn {

class CConversorHorarioVerao : public IConversorASN<ModuloComplementosMunicipios::HorarioVerao, md::CHorarioVerao> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
