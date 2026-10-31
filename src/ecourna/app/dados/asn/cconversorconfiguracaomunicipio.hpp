#pragma once
#include "ModuloConfiguracaoMunicipios.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

namespace ecourna::app::dados::asn {

class CConversorConfiguracaoMunicipio : public api::asn::IConversorASN<ModuloConfiguracaoMunicipios::ConfiguracaoMunicipio, CConfiguracaoMunicipio> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
