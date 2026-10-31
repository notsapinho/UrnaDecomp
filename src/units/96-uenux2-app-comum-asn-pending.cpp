// Pending member: the member comum::asn::CConversorDadosCandidato's vtable needs and no source of ours defines yet.
// The class overrides only DoDesconverte (slot 3, in src/uenux2/src/app/comum/dados/asn/candidatura/
// cconversordadoscandidato.cpp, which emits the vtable); slot 2 is its base's default DoConverte,
// comum::asn::IConversorASN<ModuloCandidatos::DadosCandidato, comum::md::CDadosCandidato>::DoConverte, target fn 11449,
// a 29-byte thunk of fn 731. iconversorasn.h does not define that default yet (47-uenux2-cconversorsituacoeseleicoes-
// pending.cpp says why, and this unit's fragment has the measurement of fn 731 at -O3), so this file defines this
// one instantiation's member as an explicit specialization, with the symbol the vtable references; its body is NOT the
// target's, it traps. Delete it when iconversorasn.h defines the default DoConverte: the specialization is a strong
// symbol with the name of that template's instantiation, so the link would keep this trap in the vtable without a word.
#include "app/comum/dados/asn/candidatura/cconversordadoscandidato.h"

namespace comum::asn {

template <>
IConversorASN<ModuloCandidatos::DadosCandidato, md::CDadosCandidato>::TEntidade
IConversorASN<ModuloCandidatos::DadosCandidato, md::CDadosCandidato>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

} // namespace comum::asn
