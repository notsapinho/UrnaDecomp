#pragma once

#include <vector>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "asn1/modules/ModuloCandidatos.h"

namespace comum::asn {

// Reads the candidacies of a candidates' entity; the conversion the other way is the base's default DoConverte (the
// vtable's slot 2 is IConversorASN's, target fn 11444). RTTI names the class and its base (vtable @1562360). No record
// names its file: the directory mirrors md::CCandidatura's (docs/how-to-decompile.md step 3, rule 3) and the file name
// is the class's, both chosen.
class CConversorCandidaturas
    : public IConversorASN<ModuloCandidatos::EntidadeCandidatos, std::vector<md::CCandidatura>> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
