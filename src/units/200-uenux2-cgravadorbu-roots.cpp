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
// - comum::md::CResultadoVotacao's constructor (fn 3824) and std::vector<md::CResultadoVotacao>'s
//   __emplace_back_slow_path<const md::CResultadoVotacao &> (fn 3817, the push_back of a copy): their one target
//   caller, 11629 again, calls each three times. w200_votacao builds two results with different types and pushes a
//   copy of each, two call sites of each; the push_back's copies call the vector copy fn 1556, which 3824 and 3817 call
//   too.
// - comum::MontaVotosCargos (fn 3819), a free function of cgravadorbu.cpp: its one target caller, 11629, calls it three
//   times, over the cargos of each type. w200_monta calls it twice through an asm label (the result's address first),
//   with two lists of cargos it is given.
// - comum::FiltraCargos (fn 3818), a free function of cgravadorbu.cpp: its one target caller, 11629, calls it three
//   times, with the types 0, 1 and 2. w200_filtra calls it twice through an asm label (the result's address first),
//   with a type it is given and that type plus one, into buffers it is given.
#include <cstddef>
#include <vector>

#include "app/comum/gravadores/md/cresultadovotacao.h"
#include "app/comum/gravadores/md/cresultadovotacaoporeleicao.h"

extern "C" {
extern const char w200_vt_bu[] __asm__("_ZTVN5comum11CGravadorBUE");
void w200_monta_votos(void*, const void*, const void*, const void*, const void*, const void*) __asm__(
    "_ZN5comum16MontaVotosCargosERKNSt3__26vectorINS_2md6CCargoENS0_9allocatorIS3_EEEERKNS0_3mapIhhNS0_4lessIhEENS4_INS0_4pairIKhhEEEEEERKNS_4CRdvERKNS_13CCandidaturasERKNS_9CPartidosE");
void w200_filtra_cargos(void*, const void*, int) __asm__(
    "_ZN5comum12FiltraCargosERKNSt3__26vectorINS_2md6CCargoENS0_9allocatorIS3_EEEENS3_5ETipoE");
}

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

// stands for fn 11629
__attribute__((noinline)) std::size_t w200_votacao(std::vector<comum::md::CResultadoVotacao>& resultados, uedword tipo,
    ueword quantidade, const std::vector<comum::md::CVotosCargo>& votos)
{
    const comum::md::CResultadoVotacao resultado(tipo, quantidade, votos);
    resultados.push_back(resultado);
    const comum::md::CResultadoVotacao outro(tipo + 2, quantidade, votos);
    resultados.push_back(outro);
    return resultados.size();
}

// stands for fn 11629
__attribute__((noinline)) void w200_monta(void* votos, void* outros, const void* cargos, const void* outrosCargos,
    const void* ordem, const void* rdv, const void* candidaturas, const void* partidos)
{
    w200_monta_votos(votos, cargos, ordem, rdv, candidaturas, partidos);
    w200_monta_votos(outros, outrosCargos, ordem, rdv, candidaturas, partidos);
}

// stands for fn 11629
__attribute__((noinline)) void w200_filtra(void* filtrados, void* outros, const void* cargos, int tipo)
{
    w200_filtra_cargos(filtrados, cargos, tipo);
    w200_filtra_cargos(outros, cargos, tipo + 1);
}

std::size_t (*volatile w200_sink_resultados)(const std::vector<comum::md::CResultadoVotacaoPorEleicao>&,
    const std::vector<comum::md::CResultadoVotacaoPorEleicao>&);

std::size_t (*volatile w200_sink_votacao)(std::vector<comum::md::CResultadoVotacao>&, uedword, ueword,
    const std::vector<comum::md::CVotosCargo>&);

void (*volatile w200_sink_monta)(void*, void*, const void*, const void*, const void*, const void*, const void*,
    const void*);

void (*volatile w200_sink_filtra)(void*, void*, const void*, int);

const void* volatile w200_sink_vt;

struct SW200Roots {
    SW200Roots()
    {
        w200_sink_vt = w200_vt_bu;
        w200_sink_resultados = w200_resultados;
        w200_sink_votacao = w200_votacao;
        w200_sink_monta = w200_monta;
        w200_sink_filtra = w200_filtra;
    }
} w200_roots;

} // namespace
