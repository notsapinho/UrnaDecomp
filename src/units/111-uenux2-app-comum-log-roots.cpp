// Roots: reach comum's log calls and comum::CInformacaoEleicao's members the way the target's callers do, until they land.
// Every stand-in here has a body no target function has: each makes more than one call (and folds their results, where
// they have one), and none is called. Each function below has direct callers in the target, none reconstructed unless
// said, so each gets two call sites and stays out of line:
// - comum::CLogComum's LogaCopiandoArqResParaFI, LogaResultadoCopiadoResFE, LogaGerandoResultados: the target's fn
//   12098 calls them, on GetInst's result, which it drops; LogaNivelBateria (5875) needs none: its one target caller,
//   10226 (vota::CThreadMonitor::Run, unit 116's), is in the link and calls it twice;
// - comum::IEventosLog::logaAlerta (fn 1398) and logaErro (fn 2282) need none: their target callers are all in the
//   link, 1398's eight (10512, unit 161's, the last) and 2282's five (10478, unit 282's, the last);
// - comum::IEventosLog's members that log a fixed text: the target's fns 7160 and 12134 (5885), 12134 twice (5883)
//   (7160 is in the link, unit 329's, so one call of 5885 stands for 12134); 5882 needs none, its two callers 11849 and
//   11921 (units 104 and 169) being in the link, nor 5880, its two callers 11869 and 11911 (units 138 and 176) being;
//   LogaErroEstadoAplicativo (5881) needs none, its two callers 5945 and 11914 (units 138 and 199) being in the link;
// - comum::CInformacaoEleicao's constructor (fn 603, 22 callers in the target), ImprimeBJust (1950) and
//   EhModoDemonstracao (2286) need none: their last caller not in the link, 12105, is (fragment 372's); nor do the
//   counts' getters (3847, 5914 to 5918, 2865), their callers being in the link.
#include <string>

#include "app/comum/log/clogcomum.h"
#include "app/comum/log/ieventoslog.h"

namespace {

// stands for fn 12098
__attribute__((noinline)) int w111_copia(comum::EExtensaoArquivoResultado extensao, comum::EExtensaoArquivoResultado outra)
{
    comum::CLogComum& log = comum::CLogComum::GetInst();
    log.LogaCopiandoArqResParaFI(extensao);
    log.LogaCopiandoArqResParaFI(outra);
    log.LogaResultadoCopiadoResFE(outra);
    log.LogaResultadoCopiadoResFE(extensao);
    return 3;
}

// stands for fn 12098 (its calls of LogaNivelBateria, for 10226, went: 10226 is in the link)
__attribute__((noinline)) int w111_gera(comum::EExtensaoArquivoResultado extensao)
{
    comum::CLogComum& log = comum::CLogComum::GetInst();
    log.LogaGerandoResultados(extensao, comum::STATUS_OPERACAO_INICIO);
    log.LogaGerandoResultados(extensao, comum::STATUS_OPERACAO_TERMINO);
    return 5;
}

// stands for fn 12134: its calls for 11869, 11849, 11921 and 7160 went, those callers being in the link
__attribute__((noinline)) int w111_textos(comum::IEventosLog& log, comum::IEventosLog& outro)
{
    log.LogaMidiaResultadoAusente();
    log.LogaMidiaResultadoInvalida();
    outro.LogaMidiaResultadoInvalida();
    return 10;
}

int (*volatile w111_sink_copia)(comum::EExtensaoArquivoResultado, comum::EExtensaoArquivoResultado);
int (*volatile w111_sink_gera)(comum::EExtensaoArquivoResultado);
int (*volatile w111_sink_textos)(comum::IEventosLog&, comum::IEventosLog&);

struct SW111Roots {
    SW111Roots()
    {
        w111_sink_copia = w111_copia;
        w111_sink_gera = w111_gera;
        w111_sink_textos = w111_textos;
    }
} w111_roots;

} // namespace
