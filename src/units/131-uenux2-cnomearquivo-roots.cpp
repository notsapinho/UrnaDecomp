// Roots: reach unit 131's name builders the way the target's callers do, until they land. Each has direct callers in
// the target, so each gets two call sites in our link and stays out of line, and the anonymous-namespace helpers of
// cnomearquivo.cpp stay in the link as their callees. The target's 1705 and 3772 keep every parameter (wasm types of 6
// and 9 parameters), so binaryen folded none there; no argument here is one constant at both call sites, so that it
// folds none here. Each stand-in folds the two results into a size, a body no target function has, and none is called:
// - comum::CNomeArquivo::NomeArquivoUF (fn 1705): fn 5778 calls it twice, fn 7787 five times;
// - comum::CNomeArquivo::NomeArquivoSecao (fn 3772): fns 3745, 5727 and 7787, once each.
#include <string>

#include "app/comum/nomearquivo/cnomearquivo.h"

namespace {

// stands for fns 5778 and 7787
__attribute__((noinline)) int w131_uf(comum::EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
    const std::string& extensao)
{
    return static_cast<int>(comum::CNomeArquivo::NomeArquivoUF(fase, pleito, uf, tipo, extensao).size() +
        comum::CNomeArquivo::NomeArquivoUF(comum::FASE_TREINAMENTO, pleito + 1, uf, extensao, tipo).size());
}

// stands for fns 3745, 5727 and 7787
__attribute__((noinline)) int w131_secao(comum::EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
    uedword zona, uedword secao, const std::string& tipo, const std::string& extensao)
{
    return static_cast<int>(
        comum::CNomeArquivo::NomeArquivoSecao(fase, pleito, uf, municipio, zona, secao, tipo, extensao).size() * 3 +
        comum::CNomeArquivo::NomeArquivoSecao(fase, pleito, uf, municipio + 2, secao, zona, extensao, tipo).size());
}

int (*volatile w131_sink_uf)(comum::EUrnaFase, uedword, const std::string&, const std::string&, const std::string&);
int (*volatile w131_sink_secao)(comum::EUrnaFase, uedword, const std::string&, uedword, uedword, uedword,
    const std::string&, const std::string&);

struct SW131Roots {
    SW131Roots()
    {
        w131_sink_uf = w131_uf;
        w131_sink_secao = w131_secao;
    }
} w131_roots;

} // namespace
