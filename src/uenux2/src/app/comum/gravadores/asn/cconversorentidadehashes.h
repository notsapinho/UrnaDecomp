#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/centidadehashes.h"
#include "asn1/modules/ModuloHashes.h"

namespace comum::asn {

// Writes the hashes' entity; the conversion the other way is the base's default DoDesconverte (the vtable's slot 3 is
// IConversorASN's, target fn 10265). RTTI names the class and its base (vtable @1599084); fn 5367 stores its vptr.
// DoConverte (slot 2, fn 10266) is not reconstructed: 159-uenux2-iconversorasn-defaults-pending.cpp traps it. No record
// names its file: the directory is that of its data class, md::CEntidadeHashes (gravadores/md/), and of its link
// neighbours' records (gravadores/asn/, docs/reference/facts/placing.md P3), and the file name is the class's, chosen.
class CConversorEntidadeHashes : public IConversorASN<ModuloHashes::EntidadeHashes, md::CEntidadeHashes> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
};

} // namespace comum::asn
