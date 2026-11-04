#pragma once

#include <vector>

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
// The private members are the records' (ConverteNecessidadeEspecial static, the two transfer conversions const), each
// out of line in the .cpp and binaryen-inlined into 11411 behind a frame of its own; their access, declaration order
// and parameter names are chosen.
class CConversorEntidadeEleitores
    : public IConversorParcialASN<ModuloEleitores::EntidadeEleitores, md::CEntidadeEleitores, CVisitanteEleitor> {
protected:
    TDado DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const override;

private:
    static md::CEleitor::ENecessidadeEspecial ConverteNecessidadeEspecial(ModuloEleitores::EleitorUrna eleitor);
    md::CTransferenciaTemporaria::ETransferenciaTemporaria DesconverteTipoTransferenciaTemporaria(
        const ModuloEleitores::EleitorSequencia& eleitor) const;
    md::CTransferenciaTemporaria DesconverteTransferenciaTemporaria(const ModuloEleitores::EleitorSequencia& eleitor) const;
};

// The voter's identities, in the order of the entity's identifiers; the record names it a free function of comum::asn
// (cconversorentidadeeleitores.cpp:49 and :76) and its parameter's type, by value. That it is declared here is chosen.
std::vector<md::CEleitorIdentidade> GetInscricoesEleitor(ModuloEleitores::EleitorSequencia eleitor);

} // namespace comum::asn
