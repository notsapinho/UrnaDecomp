// Roots of unit 220: the call sites and table slots the target gives the functions below, whose target callers are not
// in the link. binaryen inlines a function with one call site (docs/reference/facts/tool-traps.md X1), and each of the
// called ones has two or more direct callers in the target (ledger/callgraph.tsv), so the stand-ins give them two call
// sites each; a function the target reaches by its table slot has its address taken. Each stand-in names the target
// callers it stands for, and goes when they are in splat/matched.txt or written in the link. The GetInst callees are
// declared through asm labels; the others through their headers, since the stand-in for fn 12110
// instantiates code of those headers (CDataSourcesRelatorio's members, std::vector's destruction): this file
// compiles at the flags of 12110's directory, app/vota/ (strict aliasing, the fragment's rule), those of
// cgeradorresumozeresima.cpp, whose copies of CodVerificador (fn 11974) and its helper (fn 5967) the target keeps;
// the vector's destruction (fn 5980) links from cmostraqrcodecertificado.cpp.o, 12039's, and 11260's kept copy is
// cgeradorbu.cpp's, built without strict aliasing (the fragment has the measurement).
#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/relatorios/cdatasourcesrelatorio.h"
#include "app/comum/relatorios/crelutil.h"

extern "C" {
int w220_gerarelatorios_getinst(void) __asm__("_ZN4vota15CGeraRelatorios7GetInstEv");
int w220_copiaresultado_getinst(void) __asm__("_ZN4vota21CCopiaResultadoParaMR7GetInstEv");
}

namespace {

volatile int w220_n;
const void* volatile w220_sink;

// Stands for the other caller of two GetInst, vota::CCopiaResultadoParaMR's (fn 6174) and vota::CGeraRelatorios's
// (fn 6084), whose first, vota::CAjusteInicial::StartState (fn 7160, unit 329), is in the link:
// CGravaResultado::StartState (fn 12098, CCopiaResultadoParaMR's) and CGeraBU::StartState (fn 12110, pending here,
// CGeraRelatorios's). The calls of vota::CGeraBU's (fn 6129) went: its target callers, 7160 and fn 7481 (unit 104's
// CAguardaMensagem::ProcessKey), are in the link.
__attribute__((noinline)) int ChamaEstadosEncerramentoOutros(int n)
{
    return w220_gerarelatorios_getinst() * 7 + w220_copiaresultado_getinst() + n;
}

// The stand-ins for vota::AdicionaCabecalhoTesteTeclado (fn 3054, app/vota/eleitor/comum/ctelasvota.cpp) and
// vota::testeteclado::CEsperaRetestar::GetInst (fn 5936) went: every target caller of each is in the link (3054's
// 5936, 11804, 11809 and 11805, unit 217's, written; 5936's 11809 and 11812).

// api::CDateTime::operator- (fn 5471) needs none: its target callers, CEsperaRetestar's text callback (fn 11826) and
// fn 13012 (unit 443's TextoAlertaDesligamento), are in the link, and DiferencaDatas, which stood for 13012, went.

// Stands for fn 12110 (vota::CGeraBU::StartState, pending here): two of its five calls of
// comum::CRelUtil::ImprimeQuantidade (fn 2248, crelutil.cpp, unit 123) and its call of
// CEstadoGeral::GetDadosQRCodeCertificado (fn 5634, cestadogeral.cpp, unit 215) with true, whose result it destroys
// through fn 5980, as 12110 does. Only its address is taken, below: nothing calls it.
__attribute__((noinline)) int ChamaGeraBU(api::CPaperFormBuilder& builder, const std::string& rotulo, int n,
                                         const comum::md::estadoaplicacao::CEstadoGeral& geral)
{
    comum::CRelUtil::ImprimeQuantidade(builder, rotulo, n);
    comum::CRelUtil::ImprimeQuantidade(builder, rotulo, n + 7);
    return static_cast<int>(geral.GetDadosQRCodeCertificado(true).size()) + n;
}

using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;

struct SW220Roots {
    SW220Roots()
    {
        w220_n = ChamaEstadosEncerramentoOutros(w220_n);
        w220_sink = reinterpret_cast<const void*>(&ChamaGeraBU);
        // fn 12110's table slots of CDataSourcesRelatorio<CRdvVota, CEleitores>'s TrailerProporcionalPartido (fn 11260,
        // slot 2922), HeaderNominais (fn 11259, slot 2923) and CodVerificador (fn 11974, slot 1633), which it hands to
        // api::CPaperFormBuilder::AddTextField.
        w220_sink = reinterpret_cast<const void*>(&DataSources::TrailerProporcionalPartido);
        w220_sink = reinterpret_cast<const void*>(&DataSources::HeaderNominais);
        w220_sink = reinterpret_cast<const void*>(&DataSources::CodVerificador);
    }
} w220_roots;

} // namespace
