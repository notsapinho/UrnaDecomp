#pragma once

#include "api/io/cfile.h"
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

// Writes an envelope into an open file: a CConversorEnvelopeGenerico on the stack, IConversorASN::Converte and
// api::CFileASN::WriteToFile, which binaryen inlines (target fn 2724, a thunk that passes their three records,
// iconversorasn.h:56 and cfileasn.h:161 and :171, the entity's typeinfo name and the converter's vptr to fn 6006,
// binaryen's merge of it with the hashes' writer, fn 5367). Its callers are comum::CControlaArmazenamentoDeImagens'
// fn 2725, IGravadorEnvelope::GravaResultado (fn 11626) and CGravadorBU (fn 11629). That it is cconversorenvelopegenerico.cpp's
// code is a reading of the data: its records (@1598908 to @1598940) follow this converter's vtable (@1598820), its
// typeinfos and the records its slots hold (fns 10271, 10270), in the run of that object's data
// (docs/reference/facts/placing.md P4). Its name, its being a free function of comum::asn and its line are chosen: no
// record, slot or RTTI names it. So are its `const api::CFile&` and its const converter (cconversorversoesarquivos.h's
// writer takes `api::CFile&`: a choice on each side).
void GravaArquivo(const api::CFile& arquivo, const md::CEnvelopeGenerico& envelope);

} // namespace comum::asn
