#pragma once

#include "api/io/cfile.h"
#include "app/comum/asn/iconversorasn.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"
#include "asn1/modules/ModuloVersaoArquivos.h"

namespace comum::asn {

class CConversorVersoesArquivos : public IConversorASN<ModuloVersaoArquivos::EntidadeVersaoArquivos, md::CVersoesArquivos> {
protected:
    TEntidade DoConverte(const TDado& dado) const override;
    TDado DoDesconverte(const TEntidade& entidade) const override;
};

// Writes the data's entity into the file: a CConversorVersoesArquivos built on the stack converts it (Converte) and
// api::CFileASN::WriteToFile codes it. comum::CGravadorVersoesArquivos::GravaResultado (target fn 11582), its one caller,
// holds its code: the converter's vptr (@1599296) stored at +60 of its frame, and the records of the Converte and
// CodeObjectFunction instances (@1599428, @1599444, @1599460). That the converter's object defines it is a reading of
// the data: those records lie after this converter's vtable (@1599288) and typeinfos, far from the recorder's vtable
// (@1557240), as the records the target's writes of the hashes' and the envelope's entities pass (fns 5367 and 2724,
// thunks into binaryen's merge of the two, fn 6006: @1599208, @1598908) lie after those converters' vtables
// (@1599084, @1598820). Chosen: its name, its being a free function (it reads no converter's state), its parameter
// names and its place, after DoDesconverte.
void GravaArquivo(api::CFile& arquivo, const md::CVersoesArquivos& versoes);

} // namespace comum::asn
