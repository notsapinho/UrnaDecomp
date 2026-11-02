// Reconstruction's note: of this file (the records name it) the reconstruction holds ListaHashesArquivos only (target
// fn 5358), no record: its name and its line, after the records', are chosen. Lines 49, 78, 91, 98 and 121 are the
// records of CalculaHashArquivo and CMontadorHash's CalculaHash, CalculaHashGeral and CriaHashesDiretorio, which only
// fn 5360 holds (not written), and stay blank.
#include "api/hash/cmontadorhash.h"

namespace api::hash {

// (original lines 9-45: content not recovered)
#line 46
// <stubs>
// f5360 · 9613 B · unmatched · name unknown
// void f5360(i32, i32, i32) { ... }
// </stubs>










































































std::vector<CHashArquivo> ListaHashesArquivos(const CHashDiretorio& diretorio)
{
    std::vector<CHashArquivo> hashes;
    for (const CHashArquivo& arquivo : diretorio.GetArquivos()) {
        const CHashArquivo hash(diretorio.GetNome() + arquivo.GetNome(), arquivo.GetHash());
        hashes.push_back(hash);
    }
    for (const CHashDiretorio& subdiretorio : diretorio.GetDiretorios()) {
        std::vector<CHashArquivo> hashesSubdiretorio = ListaHashesArquivos(subdiretorio);
        hashes.insert(hashes.end(), hashesSubdiretorio.begin(), hashesSubdiretorio.end());
    }
    return hashes;
}

} // namespace api::hash
