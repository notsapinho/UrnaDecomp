#pragma once
#include "ModuloFederacoes.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/federacoes/cfederacoes.hpp"

namespace ecourna::app::dados::asn {

class CConversorFederacoes : public api::asn::IConversorASN<ModuloFederacoes::EntidadeFederacoes, CFederacoes> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
