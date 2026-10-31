#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "asn1/modules/ModuloLocal.h"

namespace comum::asn {

// Recovered: the class and its two slots, named by its RTTI (typeinfo 1561728, vtable 1561704), whose base is
// IConversorASN<ModuloLocal::SecaoEleitoral, comum::md::CSecaoEleitoral>: DoConverte (slot 2, target fn 11454) and
// DoDesconverte (slot 3, fn 11453). No record names the class's file; the header's path and its file's are chosen (unit
// 143's fragment says from what).
class CConversorSecaoEleitoral : public IConversorASN<ModuloLocal::SecaoEleitoral, md::CSecaoEleitoral> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
