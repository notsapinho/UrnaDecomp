// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"

namespace comum::asn {

// comum::asn::CConversorEstadoGeral::DoDesconverte, slot 3, target fn 11398: its record lines (cconversorestadogeral.cpp
// 87 and 91, DesconverteEstadoUrna inlined) and its callee fn 5637, comum::md::estadoaplicacao::CEstadoGeral's
// constructor, which is not written (5637 calls fn 1249, which has no name).
CConversorEstadoGeral::TDado CConversorEstadoGeral::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
