#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/chistoricovotoimpresso.h"
#include "asn1/modules/ModuloBoletimUrna.h"

namespace comum::asn {

// Writes the printed-vote history of a BU; the conversion the other way is the base's default DoDesconverte (the
// vtable's slot 3 is IConversorASN's, target fn 10275). The class name is its RTTI's. No record names its file: the
// directory is chosen beside CConversorEntidadeBU's (records in gravadores/asn/cconversorentidadebu.cpp), whose slots
// 10272 and 10273 come right before this class's 10275 and 10276 in the target, and the file name is the class's.
class CConversorHistoricoVotoImpresso
    : public IConversorASN<ModuloBoletimUrna::HistoricoVotoImpresso, md::CHistoricoVotoImpresso> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
};

} // namespace comum::asn
