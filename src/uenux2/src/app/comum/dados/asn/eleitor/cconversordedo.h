#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/eleitor/cdedo.h"
#include "asn1/modules/ModuloEleitores.h"

namespace comum::asn {

// Reads a finger of a voter's biometry; the conversion the other way is the base's default DoConverte (the vtable's
// slot 2 is IConversorASN's, target fn 11415). RTTI names the class and its base (vtable @1566480); records put
// DoDesconverte (fn 11416) in cconversordedo.cpp, and this header beside it is a chosen path.
class CConversorDedo : public IConversorASN<ModuloEleitores::Dedo, md::CDedo> {
protected:
    md::CDedo DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
