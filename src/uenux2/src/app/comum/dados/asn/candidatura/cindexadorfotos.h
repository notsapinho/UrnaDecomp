#pragma once

#include "app/comum/asn/iconversorparcialasn.h"
#include "app/comum/dados/asn/candidatura/cvisitantefoto.h"
#include "app/comum/dados/md/candidatura/cindicesfotos.h"
#include "asn1/modules/ModuloFotosCandidatos.h"

namespace comum::asn {

// Indexes the candidates' photos: the entries comum::asn::CVisitanteFoto collected and the municipality of the entity's
// abrangencia (vtable @1562540, slot 2 target fn 11441). RTTI names the class and its base. No record names its file:
// the directory mirrors md::CIndicesFotos's (docs/how-to-decompile.md step 3, rule 3) and holds CVisitanteFoto, whose
// typeinfo precedes this vtable in the data; the file name is the class's, chosen.
class CIndexadorFotos
    : public IConversorParcialASN<ModuloFotosCandidatos::EntidadeFotosCandidatos, md::CIndicesFotos, CVisitanteFoto> {
protected:
    TDado DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const override;
};

} // namespace comum::asn
