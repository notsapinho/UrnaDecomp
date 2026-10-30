#pragma once

#include "api/hash/chasharquivo.h"
#include "app/comum/asn/iconversorasn.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

class CConversorHashArquivo : public IConversorASN<ModuloTiposEleitorais::ArquivoAssinatura, api::hash::CHashArquivo> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
