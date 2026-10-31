#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"
#include "asn1/modules/ModuloEleitores.h"

namespace comum::asn {

// Reads a voter's biometry; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11421). RTTI names the class and its base (vtable @1565992); records put DoDesconverte
// (fn 11422) in cconversorbiometriaeleitor.cpp, and this header beside it is a chosen path.
class CConversorBiometriaEleitor : public IConversorASN<ModuloEleitores::BiometriaEleitor, md::CBiometriaEleitor> {
protected:
    md::CBiometriaEleitor DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
