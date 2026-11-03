// Reconstruction: comum::asn::GravaArquivo for the hashes' entity (target fn 5367), the one function of this file
// written so far. No record names the file or its lines: the file is the converter's, chosen as its header's notes say,
// and so are the lines. CConversorEntidadeHashes::DoConverte (fn 10266) is not written: unit 159's pending object traps
// it and emits the class's vtable.

#include "app/comum/gravadores/asn/cconversorentidadehashes.h"

#include "api/io/asn/cfileasn.h"

namespace comum::asn {

void GravaArquivo(const api::CFile& arquivo, const md::CEntidadeHashes& hashes)
{
    const CConversorEntidadeHashes conversor;
    api::CFileASN::WriteToFile(arquivo, conversor.Converte(hashes));
}

} // namespace comum::asn
