#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.h"
#include "asn1/modules/ModuloProcessoEleitoral.h"

namespace comum::asn {

// Reads the election process's entity; the conversion the other way is the base's default DoConverte (the vtable's
// slot 2 is IConversorASN's, target fn 11362). RTTI names the class and its base (vtable @1570408); the record of
// DoDesconverte (line 50) names the file.
class CConversorProcessoEleitoral
    : public IConversorASN<ModuloProcessoEleitoral::EntidadeProcessoEleitoral, md::CProcessoEleitoralDTO> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
