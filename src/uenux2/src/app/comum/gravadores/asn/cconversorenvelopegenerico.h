#pragma once

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/cenvelopegenerico.h"
#include "asn1/modules/ModuloEnvelopeGenerico.h"

namespace comum::asn {

// RTTI: comum::asn::CConversorEnvelopeGenerico, an si_class of IConversorASN<ModuloEnvelopeGenerico::
// EntidadeEnvelopeGenerico, comum::md::CEnvelopeGenerico>; vtable @1598820, DoConverte (fn 10271) in slot 2 and
// DoDesconverte (fn 10270) in slot 3. The destructor slots hold binaryen's shared bodies (fns 174 and 144): the class
// has no member. The two static members are declared as their records (cconversorenvelopegenerico.cpp:168, :191) print
// them; binaryen inlines each into its one caller. That they are private is a choice. The path is chosen, beside the
// .cpp its records name.
class CConversorEnvelopeGenerico
    : public IConversorASN<ModuloEnvelopeGenerico::EntidadeEnvelopeGenerico, md::CEnvelopeGenerico> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;

private:
    static ModuloEnvelopeGenerico::TipoEnvelope::NamedNumber ConverteTipoEnvelope(TDado::Tipo tipo);
    static md::CEnvelopeGenerico::Tipo DesconverteTipoEnvelope(ModuloEnvelopeGenerico::TipoEnvelope::NamedNumber tipo);
};

} // namespace comum::asn
