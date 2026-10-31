#pragma once
#include "ModuloFederacoes.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/federacoes/cfederacao.hpp"

namespace ecourna::app::dados::asn {

class CConversorFederacao : public api::asn::IConversorASN<ModuloFederacoes::Federacao, CFederacao> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
