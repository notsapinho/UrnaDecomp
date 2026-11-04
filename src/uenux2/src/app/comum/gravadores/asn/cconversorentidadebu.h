#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/centidadebu.h"
#include "asn1/modules/ModuloBoletimUrna.h"

namespace comum::asn {

// Writes the BU's entity; the conversion the other way is the base's default DoDesconverte (the vtable's slot 3 is
// IConversorASN's, target fn 10272). RTTI names the class and its base (vtable @1597528); fn 11629 stores its vptr.
// DoConverte (slot 2, fn 10273, record cconversorentidadebu.cpp:232) is not reconstructed:
// 159-uenux2-iconversorasn-defaults-pending.cpp traps it. Its records are this header's .cpp's, the path the records
// name; the header's path beside it is chosen.
class CConversorEntidadeBU : public IConversorASN<ModuloBoletimUrna::EntidadeBoletimUrna, md::CEntidadeBU> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
};

} // namespace comum::asn
