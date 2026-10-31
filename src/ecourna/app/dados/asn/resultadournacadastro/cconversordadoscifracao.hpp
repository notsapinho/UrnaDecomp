#pragma once
#include "ModuloResultadoUrnaCadastro.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/resultadournacadastro/cdadoscifracao.hpp"

namespace ecourna::app::dados::asn {

class CConversorDadosCifracao : public api::asn::IConversorASN<ModuloResultadoUrnaCadastro::DadosCifracao, CDadosCifracao> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDeconverte(const TEntidade& entidade) const override;
};

} // namespace ecourna::app::dados::asn
