#pragma once

#include "app/comum/asn/iconversorbiometriaasn.h"
#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"
#include "asn1/modules/ModuloEleitores.h"

namespace comum::asn {

// Reads a voter's ciphered biometry under a parameter; the conversion the other way is the base's default DoConverte
// (the vtable's slot 2 is IConversorBiometriaASN's, target fn 11418). RTTI names the class and its base (vtable
// @1566292); records put DoDesconverte's inlined LeChave (fn 11419) in cconversorbiometriaeleitorcifrada.cpp, and this
// header beside it is a chosen path.
class CConversorBiometriaEleitorCifrada
    : public IConversorBiometriaASN<ModuloEleitores::BiometriaEleitorCifrada, md::CBiometriaEleitor> {
protected:
    TDado DoDesconverte(const TEntidade& entidade, const md::CParametro& parametro) const override;
};

} // namespace comum::asn
