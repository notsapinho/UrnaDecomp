#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/curna.h"
#include "asn1/modules/ModuloTiposResultadosEcoUrna.h"

namespace comum::asn {

// RTTI: comum::asn::CConversorUrna, an si_class of IConversorASN<ModuloTiposResultadosEcoUrna::Urna, comum::md::CUrna>;
// vtable @1596452, DoConverte (fn 10287) in slot 2 and DoDesconverte (fn 10284) in slot 3. The destructor slots hold
// binaryen's shared bodies (fns 174 and 144): the class has no member. The four static members are declared as their
// records (cconversorurna.cpp:77, :95, :117, :139) print them; binaryen inlines each into its one caller (the slots'
// bodies hold their stack frames). That they are private is a choice. The path is chosen, beside the .cpp its records
// name.
class CConversorUrna : public IConversorASN<ModuloTiposResultadosEcoUrna::Urna, md::CUrna> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    static ModuloTiposResultadosEcoUrna::TipoUrna::NamedNumber ConverteTipoUrna(EUrnaTipo tipoUrna);
    static EUrnaTipo DesconverteTipoUrna(ModuloTiposResultadosEcoUrna::TipoUrna::NamedNumber tipoUrna);
    static ModuloTiposResultadosEcoUrna::TipoArquivo::NamedNumber ConverteTipoArquivo(ETipoArquivo tipoArquivo);
    static ETipoArquivo DesconverteTipoArquivo(ModuloTiposResultadosEcoUrna::TipoArquivo::NamedNumber tipoArquivo);
};

} // namespace comum::asn
