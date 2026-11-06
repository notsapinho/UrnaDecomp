// Roots: reach fragment 381's functions the way the target does. Each is called directly in the target; the callers
// the link holds are counted (CRdv::SalvaInterno calls GetArquivoRdvInterno, SalvaExterno GetArquivoRdvExterno, and
// both call api::CEncryptedFile's constructor, fn 1692, whose other target callers are 6734, in the link since
// fragment 386, and 7174), and these
// stand-ins, each with a body of its own, stand for the rest, so that each function has two call sites:
// - fn 6737 (no record; it holds vota::CSincronizaVota::VerificaUrnaDesligando inlined, src/units/205-uenux2-
//   csincronizavota.mk) calls GetArquivoRdvInterno (fn 1551), GetArquivoRdvExterno (1701), GetArquivoBancoDadosInterno
//   (2826) and GetArquivoBancoDadosExterno (5762) once each, and CRdv::SalvaInterno (5737) and SalvaExterno (5736)
//   twice each, on comum::CRdvVota::GetInst()'s object;
// - fn 7787 (vota::CTelasVota's constructor) calls 1551, 1701, 2826 and 5762 once each.
// The other target callers of 1551, 1701 and 2826 are fns 6734 (vota::CEstadoAudio::CarregaEleitores, in the link
// since fragment 386: 1551 and 2826) and 7174 (vota::impl::CSincronismoVotoEleitor::Sincroniza: 1551 and 1701 four
// times, 2826 once, not written); no stand-in is needed for 7174, since each function has two call sites without it.
#include <string>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdv.h"

namespace {

// stands for fn 6737
__attribute__((noinline)) size_t w381_salva(const comum::CRdv& rdv)
{
    size_t tamanho = comum::GetArquivoRdvInterno().size();
    tamanho += comum::GetArquivoRdvExterno().size();
    rdv.SalvaInterno();
    rdv.SalvaExterno();
    tamanho += comum::GetArquivoBancoDadosInterno().size() * 2;
    rdv.SalvaInterno();
    tamanho += comum::GetArquivoBancoDadosExterno().size() * 3;
    rdv.SalvaExterno();
    return tamanho;
}

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
        w381_sink = reinterpret_cast<const void*>(&w381_salva);
        w381_sink = reinterpret_cast<const void*>(&w381_telas);
    }
} w381_roots;

} // namespace
