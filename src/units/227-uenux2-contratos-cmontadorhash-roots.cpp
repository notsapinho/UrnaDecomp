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

// comum::md::CDependenciasContratos::GetValor (fn 3826): its target callers are fn 12098, which calls it twice and is
// not written, and fn 5869, in the link since unit 268.
__attribute__((noinline)) std::size_t w227_dependencias(comum::md::CDependenciasContratos& dependencias,
    const std::string& chave, const std::string& outra)
{
    return dependencias.GetValor(chave).size() * dependencias.GetValor(outra).size();
}

namespace {

void* volatile w227_sink[2];

struct SW227Roots {
    SW227Roots()
    {
        w227_sink[0] = reinterpret_cast<void*>(&w227_versoes);
        w227_sink[1] = reinterpret_cast<void*>(&w227_dependencias);
    }
} w227_roots;

} // namespace
