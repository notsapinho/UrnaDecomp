#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "asn1/modules/ModuloTiposResultadosEcoUrna.h"

namespace comum::asn {

// RTTI: comum::asn::CConversorCorrespResultado, an si_class of
// IConversorASN<ModuloTiposResultadosEcoUrna::CorrespondenciaResultado, comum::md::CCorrespondenciaResultado>; vtable
// @1596216, DoConverte (fn 10289) in slot 2 and DoDesconverte (fn 10288) in slot 3, as their records
// (cconversorcorrespresultado.cpp:53 and :85) print them. The destructor slots hold binaryen's shared bodies (fns 174
// and 144): the class has no member. The path is chosen, beside the .cpp its records name.
class CConversorCorrespResultado
    : public IConversorASN<ModuloTiposResultadosEcoUrna::CorrespondenciaResultado, md::CCorrespondenciaResultado> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

} // namespace comum::asn
