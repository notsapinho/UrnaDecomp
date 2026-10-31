#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/cpleitodto.h"
#include "asn1/modules/ModuloProcessoEleitoral.h"

namespace comum::asn {

// Reads an election's "pleito"; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11364). RTTI names the class and its base (vtable @1570332); no record names its file:
// the directory mirrors md::CPleitoDTO's (docs/how-to-decompile.md step 3, rule 3), and the vtable lies between
// cconversororigemconfiguracao.cpp's objects (@1570224 to @1570320) and cconversorprocessoeleitoral.cpp's record
// (@1570392), where a file of its own sorts. The file name is the class's, chosen.
class CConversorPleito : public IConversorASN<ModuloProcessoEleitoral::Pleito, md::CPleitoDTO> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
