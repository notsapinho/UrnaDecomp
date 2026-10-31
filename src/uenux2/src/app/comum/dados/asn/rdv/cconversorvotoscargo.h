#pragma once

#include <utility>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/asn/rdv/cconversorvoto.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"

namespace comum::asn {

// Converts one cargo's votes. RTTI names the class and its base (vtable @1570996); the records name the file
// (cconversorvotoscargo.cpp:28, :50 and :55). The layout, 20 bytes, is the constructor's (fn 5683): the cargo's
// md::CVotosCargos::SCargoInfo at +4 and a CConversorVoto at +16 (its vptr, @1570816). The member names are chosen.
class CConversorVotosCargo
    : public IConversorASN<ModuloRegistroDigitalVoto::VotosCargo, std::pair<md::CVotosCargos::SCargoInfo, md::CVotos>> {
public:
    explicit CConversorVotosCargo(const md::CVotosCargos::SCargoInfo& cargoInfo);

protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    md::CVotosCargos::SCargoInfo m_cargoInfo;
    CConversorVoto m_conversorVoto;
};

} // namespace comum::asn
