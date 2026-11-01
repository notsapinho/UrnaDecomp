#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/processoeleitoral/cdetalhecandidato.h"
#include "asn1/modules/ModuloEleicao.h"

namespace comum::asn {

// Reads an office's candidate details; the conversion the other way is the base's default DoConverte (the vtable's slot
// 2 is IConversorASN's, target fn 11374). RTTI names the class and its base (vtable @1569872); records put DoDesconverte
// (fn 11375) in cconversordetalhecandidato.cpp, and this header beside it is a chosen path.
class CConversorDetalheCandidato : public IConversorASN<ModuloEleicao::DetalheCargo, md::CDetalheCandidato> {
protected:
    md::CDetalheCandidato DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
