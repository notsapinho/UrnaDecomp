// Roots: the callers of fragment 227's functions that are not reconstructed yet. binaryen inlines a function called
// once, so each function gets at least two call sites, counting the reconstructed callers; each stand-in names the
// target callers it stands for, and goes when they are all in the link.
#include <cstddef>
#include <string>
#include <vector>

#include "api/hash/cmontadorhash.h"
#include "api/io/cfile.h"
#include "app/comum/gravadores/md/cdependenciascontratos.h"
#include "app/comum/gravadores/md/cversoescontratos.h"

// comum::md::CVersoesContratos::GetValor (fn 3825): its one target caller, fn 12098 (vota::CGravaResultado::StartState),
// calls it three times.
__attribute__((noinline)) std::size_t w227_versoes(comum::md::CVersoesContratos& versoes, const std::string& chave,
    const std::string& outra)
{
    return versoes.GetValor(chave).size() + versoes.GetValor(outra).size();
}

// comum::md::CDependenciasContratos::GetValor (fn 3826): its target callers are fn 12098, which calls it twice, and fn
// 5869, which is not written.
__attribute__((noinline)) std::size_t w227_dependencias(comum::md::CDependenciasContratos& dependencias,
    const std::string& chave, const std::string& outra)
{
    return dependencias.GetValor(chave).size() * dependencias.GetValor(outra).size();
}

// api::hash::ListaHashesArquivos (fn 5358): its target callers are itself and fn 5359, which is not written (it calls
// CriaHashesDiretorio, fn 5360).
__attribute__((noinline)) std::size_t w227_hashes(const api::hash::CHashDiretorio& diretorio)
{
    return api::hash::ListaHashesArquivos(diretorio).size() + 3;
}

// std::vector<api::hash::CHashArquivo>'s range insert (fn 5854), which ListaHashesArquivos calls: its other target
// caller is fn 11620 (CGravadorHashes::GravaResultado).
__attribute__((noinline)) void w227_insere(std::vector<api::hash::CHashArquivo>& hashes,
    std::vector<api::hash::CHashArquivo>& outros)
{
    hashes.insert(hashes.end(), outros.begin(), outros.end());
}

// ecourna::api::io::CFile::Write (fn 5180): its target callers, fn 5371 (api::CFileASN::CodeObjectFunction for
// ModuloRegistroDigitalVoto::EntidadeResultadoRDV) and fn 11587 (comum::CGravadorRDV::GravaResultado), are not written.
__attribute__((noinline)) void w227_escreve(const ecourna::api::io::CFile& arquivo, const std::vector<char>& dados,
    const std::vector<char>& outros)
{
    arquivo.Write(dados);
    arquivo.Write(outros);
}

namespace {

void* volatile w227_sink[5];

struct SW227Roots {
    SW227Roots()
    {
        w227_sink[0] = reinterpret_cast<void*>(&w227_versoes);
        w227_sink[1] = reinterpret_cast<void*>(&w227_dependencias);
        w227_sink[2] = reinterpret_cast<void*>(&w227_hashes);
        w227_sink[3] = reinterpret_cast<void*>(&w227_insere);
        w227_sink[4] = reinterpret_cast<void*>(&w227_escreve);
    }
} w227_roots;

} // namespace
