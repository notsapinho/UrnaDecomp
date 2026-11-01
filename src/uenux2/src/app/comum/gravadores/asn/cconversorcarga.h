#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/correspondencia/ccarga.h"
#include "asn1/modules/ModuloTiposEcoUrna.h"

namespace comum::asn {

// RTTI: comum::asn::CConversorCarga (typeinfo @1596164, its name the string at 543560), an si_class of
// IConversorASN<ModuloTiposEcoUrna::Carga, comum::md::CCarga>; vtable @1596140 [174, 144, 10291, 10290], which
// ledger/vtables.json misses (docs/reference/facts/units.md U12): DoConverte (fn 10291) in slot 2 and DoDesconverte
// (fn 10290) in slot 3. CConversorCorrespResultado builds one on its stack (fn 10288 stores the vptr 1596148) and calls
// it through the vtable. Its vtable and typeinfo lie between gravadores/asn/util.cpp's records and
// cconversorcorrespresultado.cpp's in the data. Recovered: the head only; both members are pending (fn 10290 calls
// fns 2802 and 1713, fn 10291 fn 1080, and those wait; the 3733 and 3734 they call match, unit 166). Chosen: the
// path, after the class name (no record names its file).
class CConversorCarga : public IConversorASN<ModuloTiposEcoUrna::Carga, md::CCarga> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
