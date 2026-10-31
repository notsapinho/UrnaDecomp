#pragma once
#include "ModuloParametrizacaoUrna.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/parametrizacaourna/cparametrizacaourna.hpp"

namespace ecourna::app::dados::asn {

class CConversorParametrizacaoUrna : public api::asn::IConversorASN<ModuloParametrizacaoUrna::EntidadeParametrizacaoUrna, CParametrizacaoUrna> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
