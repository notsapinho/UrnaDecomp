// Roots: reach comum's log calls and comum::CInformacaoEleicao's members the way the target's callers do, until they land.
// Every stand-in here has a body no target function has: each makes more than one call and folds their results, and
// none is called. Each function below has direct callers in the target, none reconstructed, so each gets two call sites
// and stays out of line:
// - comum::CLogComum's LogaCopiandoArqResParaFI, LogaResultadoCopiadoResFE, LogaGerandoResultados, LogaNivelBateria:
//   the target's fns 12098 and 10226 call them, on GetInst's result, which they drop;
// - comum::IEventosLog::ConverteERelatoriosUE: the target's fns 1047 and 1127;
// - comum::CInformacaoEleicao's constructor and members: fn 603 has 22 callers in the target; each member's own callers
//   are listed in the class header.
#include <string>

#include "app/comum/informacao/cinformacaoeleicao.h"
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

// stands for fns 12098 and 10226
__attribute__((noinline)) int w111_gera(comum::EExtensaoArquivoResultado extensao, uebyte fonte, uebyte status)
{
    comum::CLogComum& log = comum::CLogComum::GetInst();
    log.LogaGerandoResultados(extensao, comum::STATUS_OPERACAO_INICIO);
    log.LogaNivelBateria(fonte, status);
    log.LogaGerandoResultados(extensao, comum::STATUS_OPERACAO_TERMINO);
    log.LogaNivelBateria(status, fonte);
    return 5;
}

// stands for fns 1047 and 1127
__attribute__((noinline)) int w111_relatorio(comum::IEventosLog& log, comum::ERelatoriosUE relatorio, comum::ERelatoriosUE outro)
{
    return static_cast<int>(log.ConverteERelatoriosUE(relatorio).size() + log.ConverteERelatoriosUE(outro).size());
}

// stands for the callers of fn 603, among them 12023, 6599, 11666 to 11669
__attribute__((noinline)) int w111_informacao(const ecourna::app::dados::CParametrosUrna& dados)
{
    comum::CInformacaoEleicao a(dados);
    comum::CInformacaoEleicao b(dados);
    return a.GetNumViasBU() + a.GetNumViasBUAdicionais() + a.GetNumViasEstadoUrna() + a.GetNumViasEleitores() + a.GetNumViasVersoesDados() +
        a.GetNumViasPU() + (a.ImprimeBJust() ? 7 : 11) + (a.EhModoDemonstracao() ? 13 : 17) + b.GetNumViasBU() + b.GetNumViasBUAdicionais() +
        b.GetNumViasEstadoUrna() + b.GetNumViasEleitores() + b.GetNumViasVersoesDados() + b.GetNumViasPU() + (b.ImprimeBJust() ? 19 : 23) +
        (b.EhModoDemonstracao() ? 29 : 31);
}

int (*volatile w111_sink_copia)(comum::EExtensaoArquivoResultado, comum::EExtensaoArquivoResultado);
int (*volatile w111_sink_gera)(comum::EExtensaoArquivoResultado, uebyte, uebyte);
int (*volatile w111_sink_relatorio)(comum::IEventosLog&, comum::ERelatoriosUE, comum::ERelatoriosUE);
int (*volatile w111_sink_informacao)(const ecourna::app::dados::CParametrosUrna&);

struct SW111Roots {
    SW111Roots()
    {
        w111_sink_copia = w111_copia;
        w111_sink_gera = w111_gera;
        w111_sink_relatorio = w111_relatorio;
        w111_sink_informacao = w111_informacao;
    }
} w111_roots;

} // namespace
