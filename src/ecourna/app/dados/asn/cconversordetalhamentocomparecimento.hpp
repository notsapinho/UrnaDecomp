#pragma once
#include "ModuloBoletimUrna.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/cdetalhamentocomparecimento.hpp"

namespace ecourna::app::dados::asn {

class CConversorDetalhamentoComparecimento : public api::asn::IConversorASN<ModuloBoletimUrna::DetalhamentoComparecimento, CDetalhamentoComparecimento> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
