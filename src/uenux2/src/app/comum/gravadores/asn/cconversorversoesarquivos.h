#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"
#include "asn1/modules/ModuloVersaoArquivos.h"

namespace comum::asn {

class CConversorVersoesArquivos : public IConversorASN<ModuloVersaoArquivos::EntidadeVersaoArquivos, md::CVersoesArquivos> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
