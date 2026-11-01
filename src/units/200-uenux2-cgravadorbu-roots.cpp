// Roots: reach unit 200's functions the way the target does, until their callers land. It compiles with the tree's
// flags: the two instances below are libc++ code over this tree's classes whose one target caller is a function of this
// tree (fn 11629), so the target's copies are read as that tree's.
// - comum::CGravadorBU's vtable (@1554132), whose destructors (fns 5857, 11628, slots 0 and 1) the target reaches only
//   through it: the constructor that stores it (inlined into vota::CGravaResultado::StartState, fn 12098) is not
//   written, so its address goes into a sink.
// - libc++'s uninitialized copy of a range of comum::md::CResultadoVotacaoPorEleicao (fn 2853), which a copy of a
//   std::vector of them calls, and the vector's __base_destruct_at_end (fn 5859), which its destructor calls: the one
//   target caller of each is comum::CGravadorBU::GravaResultado (fn 11629), not written. The stand-in copies two
//   vectors and destroys both, so that each instance has two call sites, and its body is no target function's.
#include <cstddef>
#include <vector>

#include "app/comum/gravadores/md/cresultadovotacaoporeleicao.h"

extern "C" const char w200_vt_bu[] __asm__("_ZTVN5comum11CGravadorBUE");

namespace {

// stands for fn 11629
__attribute__((noinline)) std::size_t w200_resultados(
    const std::vector<comum::md::CResultadoVotacaoPorEleicao>& resultados,
    const std::vector<comum::md::CResultadoVotacaoPorEleicao>& outros)
{
    const std::vector<comum::md::CResultadoVotacaoPorEleicao> copia(resultados);
    const std::vector<comum::md::CResultadoVotacaoPorEleicao> outraCopia(outros);
    return copia.size() + 3 * outraCopia.size();
}

std::size_t (*volatile w200_sink_resultados)(const std::vector<comum::md::CResultadoVotacaoPorEleicao>&,
    const std::vector<comum::md::CResultadoVotacaoPorEleicao>&);

const void* volatile w200_sink_vt;

struct SW200Roots {
    SW200Roots()
    {
        w200_sink_vt = w200_vt_bu;
        w200_sink_resultados = w200_resultados;
    }
} w200_roots;

} // namespace
