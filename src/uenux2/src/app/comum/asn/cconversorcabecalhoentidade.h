#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "asn1/modules/ModuloTiposEleitorais.h"

namespace comum::asn {

// RTTI names the class and its base (vtable @1556732, slots 2 and 3: fns 11589 and 11588), and the two members'
// records are cconversorcabecalhoentidade.cpp:35 and :56, where both are written (fragment 172); they call the date
// conversions fns 1080 and 1713. The header's path is chosen, beside the .cpp its records name.
class CConversorCabecalhoEntidade : public IConversorASN<ModuloTiposEleitorais::CabecalhoEntidade, md::CCabecalhoEntidade> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
