// Roots: keep comum::CGeracaoVersoesContratos::ObtemDependencias (target fn 5869) in the skeleton link the way the
// target reaches it. Its target callers are itself and fn 12098 (vota::CGravaResultado::StartState), which calls it
// once and is not reconstructed; this noinline caller stands for 12098, and with the recursive call the function has
// two call sites. The result is built in place, so this object instantiates no member of std::set. Compiled with
// APP_CXXFLAGS.
#include <new>
#include <set>
#include <string>

#include "app/comum/gravadores/cgeracaoversoescontratos.h"

__attribute__((noinline)) void w268_dependencias(comum::CGeracaoVersoesContratos& geracao, void* destino,
    const std::string& contrato, std::set<std::string>& dependencias)
{
    ::new (destino) std::set<std::string>(geracao.ObtemDependencias(contrato, dependencias));
}

namespace {

void* volatile w268_sink;

struct SW268Roots {
    SW268Roots()
    {
        w268_sink = reinterpret_cast<void*>(&w268_dependencias);
    }
} w268_roots;

} // namespace

// Stands in for the other target callers of fn 1163, libc++'s
// __tree<std::string>::__emplace_hint_unique_extract_key<const std::string&> (a std::set<std::string>'s hinted insert,
// the emplace inlined into it): 5360 and 11620, not reconstructed, which build a std::set<std::string> from an
// initializer list (two and eight inserts at the end hint). ObtemDependencias's set copy calls 1163 at one site, and
// binaryen inlines a function called once. Called through its label with the object's signature (the iterator result
// is one i32), so this object instantiates nothing of std::set; the label resolves while cgeracaoversoescontratos.cpp
// builds with strict aliasing, which keeps 1163 out of line there (src/Makefile UENUX2_TBAA_DIRS).
extern "C" int w268_insere(int, int, int) __asm__(
    "_ZNSt3__26__treeINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_4lessIS6_EENS4_IS6_EEE33__"
    "emplace_hint_unique_extract_keyB8ne210108IRKS6_EENS_15__tree_iteratorIS6_PNS_11__tree_nodeIS6_PvEElEENS_21__"
    "tree_const_iteratorIS6_SI_lEEOT_NS_22__extract_key_self_tagE");

__attribute__((noinline)) void w268_conjunto(int conjunto, int fim, int primeiro, int segundo)
{
    w268_insere(conjunto, fim, primeiro);
    w268_insere(conjunto, fim, segundo);
}

namespace {

void* volatile w268_sink_conjunto;

struct SW268RootsConjunto {
    SW268RootsConjunto()
    {
        w268_sink_conjunto = reinterpret_cast<void*>(&w268_conjunto);
    }
} w268_roots_conjunto;

} // namespace
