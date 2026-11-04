#pragma once

#include "app/comum/asn/iconversorparcialasn.h"
#include "app/comum/dados/asn/eleitor/cvisitanteeleitor.h"
#include "app/comum/dados/md/eleitor/centidadeeleitores.h"
#include "asn1/modules/ModuloEleitores.h"

namespace comum::asn {

// Converts the voters' file entity with what comum::asn::CVisitanteEleitor collected while it was read (vtable @1566768:
// slots 0 and 1 the shared empty destructors 174 and 144, slot 2 DoDesconverte, target fn 11411). RTTI names the class
// and its base; the records of cconversorentidadeeleitores.cpp (lines 38, 49, 76, 210 and 236) name its file and the
// members fn 11411 holds inlined. The constructor has no function of its own: fn 11523 stores the vptr (1566776) in the
// top 4 bytes (+76) of the 80-byte frame of the reader that calls Desconverte, so the class has no data member. The
// path of this header is the .cpp's, beside it.
class CConversorEntidadeEleitores
    : public IConversorParcialASN<ModuloEleitores::EntidadeEleitores, md::CEntidadeEleitores, CVisitanteEleitor> {
protected:
    TDado DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const override;
};

} // namespace comum::asn
