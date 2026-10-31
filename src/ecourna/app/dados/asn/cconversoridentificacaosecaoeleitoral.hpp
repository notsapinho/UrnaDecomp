#pragma once
#include "ModuloTiposEleitorais.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/cidentificacaosecaoeleitoral.hpp"

namespace ecourna::app::dados::asn {

class CConversorIdentificacaoSecaoEleitoral : public api::asn::IConversorASN<ModuloTiposEleitorais::IdentificacaoSecaoEleitoral, CIdentificacaoSecaoEleitoral> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
