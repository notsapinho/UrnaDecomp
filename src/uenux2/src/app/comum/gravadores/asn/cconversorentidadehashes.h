#pragma once

#include "api/io/cfile.h"
#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/centidadehashes.h"
#include "asn1/modules/ModuloHashes.h"

namespace comum::asn {

// Writes the hashes' entity; the conversion the other way is the base's default DoDesconverte (the vtable's slot 3 is
// IConversorASN's, target fn 10265). RTTI names the class and its base (vtable @1599084); fn 5367 stores its vptr.
// DoConverte (slot 2, fn 10266) is not reconstructed: 159-uenux2-iconversorasn-defaults-pending.cpp traps it. No record
// names its file: the directory is that of its data class, md::CEntidadeHashes (gravadores/md/), and of its link
// neighbours' records (gravadores/asn/, docs/reference/facts/placing.md P3), and the file name is the class's, chosen.
class CConversorEntidadeHashes : public IConversorASN<ModuloHashes::EntidadeHashes, md::CEntidadeHashes> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
};

// Writes the hashes' entity into an open file: a CConversorEntidadeHashes on the stack, IConversorASN::Converte and
// api::CFileASN::WriteToFile, which binaryen inlines (target fn 5367, a thunk into fn 6006, binaryen's merge of it with
// the envelope's writer, fn 2724, cconversorenvelopegenerico.h). Its one caller, CGravadorHashes::GravaResultado (fn
// 11620), calls it twice and is not written. That it is this converter's object's code, cconversorentidadehashes.cpp,
// is a reading of the data: its records (iconversorasn.h:56, cfileasn.h:161 and :171, @1599208 to @1599240) follow
// this class's vtable (@1599084), its typeinfos, another vtable and the records its slots hold (fns 10266, 10265), as
// fn 2724's follow CConversorEnvelopeGenerico's (docs/reference/facts/placing.md P4). Its name, its being a free
// function of comum::asn, the file's being this one, its `const api::CFile&` and its const converter are chosen
// (cconversorversoesarquivos.h's writer takes `api::CFile&`: a choice on each side).
void GravaArquivo(const api::CFile& arquivo, const md::CEntidadeHashes& hashes);

} // namespace comum::asn
