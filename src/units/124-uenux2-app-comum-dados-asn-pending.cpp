// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap.
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"

namespace comum::asn {

// comum::asn::CConversorEstadoGeral::DoDesconverte, slot 3, target fn 11398: its record lines (cconversorestadogeral.cpp
// 87 and 91, DesconverteEstadoUrna inlined) and its callee fn 5637, comum::md::estadoaplicacao::CEstadoGeral's
// constructor, which is not written (5637 calls fn 1249, which has no name).
CConversorEstadoGeral::TDado CConversorEstadoGeral::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

// comum::asn::CConversorDadoCorrespondencia, both slots: DoConverte (target fn 11399) and DoDesconverte (fn 11400), which
// build the correspondence's dates through api::CDateTime (fns 1713, 1080, 3604, 3605, 3733, 3734 are their callees).
// This file emits the class's vtable with them; CConversorEstadoGeral::DoConverte (fn 11397) builds one on its stack.
CConversorDadoCorrespondencia::TEntidade CConversorDadoCorrespondencia::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorDadoCorrespondencia::TDado CConversorDadoCorrespondencia::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
