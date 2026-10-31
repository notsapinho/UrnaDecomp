#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/estadoaplicacao/cajustedatahora.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"

namespace comum::asn {

class CConversorAjusteDataHora
    : public IConversorASN<ModuloEstadoGeralUrna::AjusteDataHora, md::estadoaplicacao::CAjusteDataHora> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    md::estadoaplicacao::CAjusteDataHora::ETipoDeltaT DesconverteTipoAjusteDataHora(const ModuloEstadoGeralUrna::TipoAjusteDataHora& tipo) const;
    ModuloEstadoGeralUrna::TipoAjusteDataHora ConverteTipoAjusteDataHora(const md::estadoaplicacao::CAjusteDataHora::ETipoDeltaT& tipo) const;
};

} // namespace comum::asn
