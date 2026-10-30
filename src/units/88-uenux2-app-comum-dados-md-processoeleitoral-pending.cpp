// Pending members: the member comum::asn::CConversorNomesCargo's vtable needs and no source of ours defines yet.
// The class overrides only DoDesconverte (slot 3, in
// src/uenux2/src/app/comum/dados/asn/processoeleitoral/cconversornomescargo.cpp, which emits the vtable); slot 2 is its
// base's default DoConverte, comum::asn::IConversorASN<ModuloEleicao::NomesCargo, comum::md::CNomesCargo>::DoConverte,
// target fn 11368 (29 B, a call of the shared body fn 731 with this instantiation's constants). That default is a member
// of the class template every comum converter derives from, and iconversorasn.h does not define it yet. So this file
// defines this one instantiation's member as an explicit specialization, with the symbol the vtable references; its
// body is NOT the target's, it traps.
// Delete this file when iconversorasn.h defines the default DoConverte: the specialization is a strong symbol with the
// name of that template's instantiation, so the link would keep this trap in the vtable without a word.
#include "app/comum/dados/asn/processoeleitoral/cconversornomescargo.h"

namespace comum::asn {

template <>
IConversorASN<ModuloEleicao::NomesCargo, md::CNomesCargo>::TEntidade
IConversorASN<ModuloEleicao::NomesCargo, md::CNomesCargo>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

} // namespace comum::asn
