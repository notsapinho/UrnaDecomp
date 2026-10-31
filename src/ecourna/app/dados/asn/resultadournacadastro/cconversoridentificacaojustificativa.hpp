#pragma once
#include "ModuloResultadoUrnaCadastro.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/resultadournacadastro/cidentificacaojustificativa.hpp"

namespace ecourna::app::dados::asn {

class CConversorIdentificacaoJustificativa : public api::asn::IConversorASN<ModuloResultadoUrnaCadastro::IdentificacaoJustificativa, CIdentificacaoJustificativa> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
