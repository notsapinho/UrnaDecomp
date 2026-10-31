// Pending members: the member comum::asn::CConversorSituacoesEleicoes's vtable needs and no source of ours defines yet.
// The class overrides only DoDesconverte (slot 3, in
// src/uenux2/src/app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.cpp, which emits the vtable); slot 2
// is its base's default DoConverte, comum::asn::IConversorASN<ModuloSituacoesEleicoes::EntidadeSituacoesEleicoes,
// std::vector<comum::md::CSituacoesEleicoes>>::DoConverte, target fn 11360 (29 B), whose record puts a throw on line 89
// col 15 of src/app/comum/asn/iconversorasn.h. That default is a member of the class template every comum converter
// derives from, and iconversorasn.h does not define it yet (it calls fn 731, not named yet); defining it there would
// change every unit that includes the header. So this file defines this one instantiation's member as an explicit
// specialization, with the symbol the vtable references; its body is NOT the target's, it traps.
// Delete this file when iconversorasn.h defines the default DoConverte: the specialization is a strong symbol with the
// name of that template's instantiation, so the link would keep this trap in the vtable without a word.
// Its source, in the class at lines 87 to 90 of the header (the default DoDesconverte is the same at lines 96 to 99, with
// code 7656 and "Método DoDesconverte()..."; the codes are comum::EUeComumAsnError's):
//     throw CUeComumAsnError(7655, std::format("Método DoConverte() não implementado para {}", typeid(TEntidade).name()));
// Fn 731 is binaryen's merge of those two defaults, 20 thunks over it, so it forms only with both in the link (one
// inherited DoDesconverte: comum::asn::CConversorHistoricoVotoImpresso, CConversorEntidadeBU or CConversorEntidadeHashes)
// and 96-uenux2-app-comum-asn.mk has its measurement at -O3, the tree's level.
#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"

namespace comum::asn {

template <>
IConversorASN<ModuloSituacoesEleicoes::EntidadeSituacoesEleicoes, std::vector<md::CSituacoesEleicoes>>::TEntidade
IConversorASN<ModuloSituacoesEleicoes::EntidadeSituacoesEleicoes, std::vector<md::CSituacoesEleicoes>>::DoConverte(
    const TDado&) const
{
    __builtin_trap();
}

} // namespace comum::asn
