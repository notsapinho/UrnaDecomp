#pragma once
#include "ModuloResultadoUrnaCadastro.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/resultadournacadastro/ccomparecimentosecao.hpp"

namespace ecourna::app::dados::asn {

class CConversorComparecimentoSecao : public api::asn::IConversorASN<ModuloResultadoUrnaCadastro::ComparecimentoSecao, CComparecimentoSecao> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
