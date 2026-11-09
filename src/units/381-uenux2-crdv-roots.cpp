// Roots: reach fragment 381's functions the way the target does. Each is called directly in the target; the callers
// the link holds are counted (CRdv::SalvaInterno calls GetArquivoRdvInterno, SalvaExterno GetArquivoRdvExterno, and
// both call api::CEncryptedFile's constructor, fn 1692, whose other target callers are 6734 and 7174), and the
// stand-in below, with a body of its own, stands for the rest, so that each function has two call sites:
// - fn 7787 (in its data load, before the CTelasVota::CreateInst it holds) calls 1551, 1701, 2826 and 5762 once each.
// fn 6737 (vota::CEstadoAudio::GeraDadosDinamicos, unit 116), which calls GetArquivoRdvInterno (fn 1551),
// GetArquivoRdvExterno (1701), GetArquivoBancoDadosInterno (2826) and GetArquivoBancoDadosExterno (5762) once each and
// CRdv::SalvaInterno (5737) and SalvaExterno (5736) twice each, fn 7174 (vota::impl::CSincronismoVotoEleitor::
// Sincroniza, unit 241: 1551 and 1701 four times, 2826 once) and fn 6734 (vota::CEstadoAudio::CarregaEleitores,
// fragment 386: 1551 and 2826) are in the link, and the stand-in for 6737 went.
#include <string>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdv.h"

namespace {

// stands for fn 7787
__attribute__((noinline)) size_t w381_telas(size_t base)
{
    size_t tamanho = base + comum::GetArquivoRdvInterno().size();
    tamanho ^= comum::GetArquivoRdvExterno().size();
    tamanho += comum::GetArquivoBancoDadosInterno().size() * 5;
    tamanho -= comum::GetArquivoBancoDadosExterno().size();
    return tamanho;
}

const void* volatile w381_sink;

struct SW381Roots {
    SW381Roots()
    {
        w381_sink = reinterpret_cast<const void*>(&w381_telas);
    }
} w381_roots;

} // namespace
