#pragma once
#include "ModuloInformacaoMidia.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/asn/sequenciaasn.hpp"
#include "ecourna/app/dados/midias/cinformacaomidia.hpp"

namespace ecourna::app::dados::asn {

class CConversorInformacaoMidia
    : public api::asn::IConversorASN<ModuloInformacaoMidia::InformacaoMidia, CInformacaoMidia> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;

private:
    ModuloInformacaoMidia::TipoMidia ConverteTipoMidia(TDado::ETipoMidia tipoMidia) const;
    TDado::ETipoMidia DeconverteTipoMidia(ModuloInformacaoMidia::TipoMidia tipoMidia) const;
};

} // namespace ecourna::app::dados::asn
