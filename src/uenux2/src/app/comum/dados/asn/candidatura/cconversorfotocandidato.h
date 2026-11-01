#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/cfotocandidato.h"
#include "asn1/modules/ModuloFotosCandidatos.h"

namespace comum::asn {

// Reads a candidate's photo; the conversion the other way is the base's default DoConverte (the vtable's slot 2 is
// IConversorASN's, target fn 11439). RTTI names the class and its base (vtable @1562580). No record names its file: the
// directory mirrors md::CFotoCandidato's (docs/how-to-decompile.md step 3, rule 3) and the file name is the class's,
// both chosen.
class CConversorFotoCandidato : public IConversorASN<ModuloFotosCandidatos::FotoCandidato, md::CFotoCandidato> {
protected:
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
