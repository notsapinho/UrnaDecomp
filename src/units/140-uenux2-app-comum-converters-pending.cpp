// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet. Their
// bodies are NOT the target's; they trap.
// - The base's default DoConverte of CConversorPleito (slot 2, target fn 11364) and of CConversorProcessoEleitoral
//   (slot 2, fn 11362): comum::asn::IConversorASN<ENTIDADE, DADO>::DoConverte, 29-byte thunks of fn 731.
//   iconversorasn.h does not define that default yet (47-uenux2-cconversorsituacoeseleicoes-pending.cpp says why, and
//   96-uenux2-app-comum-asn.mk has the measurement: fn 731 needs -O3, the tree's level), so this file defines each
//   instantiation's member as an explicit specialization, with the symbol the vtable references. Delete them when
//   iconversorasn.h defines the default DoConverte: a specialization is a strong symbol with the name of that template's
//   instantiation, so the link would keep the trap without a word.
// - CConversorEleicoesVota::DoDesconverte (slot 3, fn 11349, records cconversoreleicoesvota.cpp:69, :74, :94 and :104),
//   not written: it builds md::CVotosEleicoesVota's maps from the entity (5054 B); its direct callees 3869, 5640, 5643
//   and 5681 are not matched.
// - CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s DoConverte and DoDesconverte (slots 2 and 3, fns 11483 and
//   11482), not written: the entity's header from the class's words and the elections through its member converter.
//   Explicit specializations of the class template's members for this instance; they move into the template when
//   written.
#include "app/comum/dados/asn/processoeleitoral/cconversorpleito.h"
#include "app/comum/dados/asn/rdv/cconversoreleicoesvota.h"
#include "app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorprocessoeleitoral.h"

namespace comum::asn {

template <>
IConversorASN<ModuloProcessoEleitoral::Pleito, md::CPleitoDTO>::TEntidade
IConversorASN<ModuloProcessoEleitoral::Pleito, md::CPleitoDTO>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

template <>
IConversorASN<ModuloProcessoEleitoral::EntidadeProcessoEleitoral, md::CProcessoEleitoralDTO>::TEntidade
IConversorASN<ModuloProcessoEleitoral::EntidadeProcessoEleitoral, md::CProcessoEleitoralDTO>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorEleicoesVota::TDado CConversorEleicoesVota::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

template <>
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::TEntidade
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

template <>
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::TDado
CConversorRegistroDigitalVoto<CConversorEleicoesVota>::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
