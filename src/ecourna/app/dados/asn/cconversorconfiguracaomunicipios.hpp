#pragma once
#include <vector>

#include "ModuloConfiguracaoMunicipios.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipios.hpp"

namespace ecourna::app::dados::asn {

class CConversorConfiguracaoMunicipios : public api::asn::IConversorASN<ModuloConfiguracaoMunicipios::EntidadeConfiguracaoMunicipios, CConfiguracaoMunicipios> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;

private:
    static std::vector<CConfiguracaoMunicipio> ParaVetor(const TMapConfiguracaoMunicipio& mapa);
    static TMapConfiguracaoMunicipio ParaMapa(const std::vector<CConfiguracaoMunicipio>& configuracoes);
};

} // namespace ecourna::app::dados::asn
