// Roots: keep the vtables of vota::CMostraQRCodeCertificado (@1542480), vota::CRetirarMR (@1542676) and comum's four
// menu items (@1550780 to @1550888) in the skeleton link the way the target reaches their slots: only through the
// vtable, which the classes' constructors store. The states' constructors are inlined into their GetInst, and neither
// of those two GetInst has a caller here: CMostraQRCodeCertificado's only caller is CMostraQRCodeBU::ProcessInput (fn
// 12051), pending, and CRetirarMR's (fn 2291) is not reconstructed. vota::CQuerImprimirBU's vtable needs no line: its
// GetInst is inlined into CInicioBU::StartState (fn 12062, unit 104), which stores its vptr.
// vota::CLimiteCopiasBUAtingido's vtable needs no line: its GetInst is inlined into
// CVerificaQtdBUsAdicionais::StartState (fn 12023, unit 185), which stores its vptr. Comum's items are built by fn
// 6599, which stores each comum vptr and then the vota item's (unit 102's roots keep the vota items' vtables). Taking
// each vtable's address from a static constructor puts their slots in the table, as the target has them. The six
// vota::CLogVota members of this unit (fns 1127, 4551, 4556, 2495, 4563 and 4557, in app/vota/log/clogvota.cpp) have
// direct call sites in the target, two or more each (ledger/callgraph.tsv; 4557's two are both in fn 12081), so
// binaryen keeps them out of line; the stand-ins below give them those call sites, each standing for the callers it
// names, and go when those callers are in splat/matched.txt or written in the link. Declared through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
int w156_imprimindobu_getinst(void) __asm__("_ZN4vota13CImprimindoBU7GetInstEv");
int w156_logvota_getinst(void) __asm__("_ZN4vota8CLogVota7GetInstEv");
void w156_loga_imprimindo_relatorio(int, int, unsigned) __asm__(
    "_ZN4vota8CLogVota23LogaImprimindoRelatorioEN5comum13ERelatoriosUEEj");
void w156_loga_qualidade_bu(int) __asm__("_ZN4vota8CLogVota30LogaMesarioIndagadoQualidadeBUEv");
void w156_loga_vias_adicionais(int) __asm__("_ZN4vota8CLogVota33LogaQtdViasAdicionaisExcedeMaximoEv");
void w156_loga_biometrico(int) __asm__("_ZN4vota8CLogVota48LogaHabilitacaoCanceladaReconhecimentoBiometricoEv");
void w156_loga_indagado_vias(int) __asm__("_ZN4vota8CLogVota36LogaMesarioIndagadoQtdViasAdicionaisEv");
void w156_loga_nao_solicitou_vias(int) __asm__("_ZN4vota8CLogVota37LogaMesarioNaoSolicitouViasAdicionaisEv");
extern const char w156_vt_cmostraqrcodecertificado[] __asm__("_ZTVN4vota24CMostraQRCodeCertificadoE");
extern const char w156_vt_cretirarmr[] __asm__("_ZTVN4vota10CRetirarMRE");
extern const char w156_vt_comum_estadourna[] __asm__("_ZTVN5comum22CItemImprimeEstadoUrnaE");
extern const char w156_vt_comum_listaeleitores[] __asm__("_ZTVN5comum26CItemImprimeListaEleitoresE");
extern const char w156_vt_comum_parametrosurna[] __asm__("_ZTVN5comum19CItemParametrosUrnaE");
extern const char w156_vt_comum_versoespacotes[] __asm__("_ZTVN5comum19CItemVersoesPacotesE");
}

namespace {

const void* volatile w156_sink;
volatile int w156_n;

// Stands for CQuerImprimirBU::ProcessInput (fn 12034, pending here), one of vota::CImprimindoBU::GetInst's (fn 5986)
// two target callers; the other, CInicioBU::StartState (fn 12062, unit 104), is in the link. It adds its argument to the
// result, so binaryen keeps it and its body is no target function's.
__attribute__((noinline)) int ChamaImprimindoBU(int n)
{
    return w156_imprimindobu_getinst() + n;
}

// Stands for the printing states' slots that call CLogVota::LogaImprimindoRelatorio (fn 1127: 11852, 11855, 11991,
// 12065, 12068, 12071, 12074, 12077, 12078 and 12081), each with a report and a copy number of its own (12078 passes 3
// and 1), and for vota::CImprimindoBU's two slots that call LogaMesarioIndagadoQualidadeBU (fn 4551: 12077, 12078).
__attribute__((noinline)) int ImprimeRelatorios(int n)
{
    int log = w156_logvota_getinst();
    w156_loga_imprimindo_relatorio(log, 3, 1);
    w156_loga_qualidade_bu(log);
    w156_loga_imprimindo_relatorio(log, n, n + 2);
    w156_loga_qualidade_bu(log);
    return n + 79;
}

// Stands for CEmitirMaisBU::ProcessInput (fn 12081), the caller of LogaQtdViasAdicionaisExcedeMaximo (fn 4556) beside
// CLimiteCopiasBUAtingido::StartState, and for the operador slots that call
// LogaHabilitacaoCanceladaReconhecimentoBiometrico (fn 2495: 10473, 10477 and 10485; 10466, CPedeDigital::ProcessInput,
// is in the link).
__attribute__((noinline)) int AlertaVias(int n)
{
    int log = w156_logvota_getinst();
    w156_loga_vias_adicionais(log);
    w156_loga_biometrico(log);
    w156_loga_biometrico(w156_logvota_getinst());
    return n * 3 + 83;
}

// Stands for CEmitirMaisBU::ProcessInput (fn 12081, pending in unit 104), which calls
// LogaMesarioNaoSolicitouViasAdicionais (fn 4557) twice, its only caller, and LogaMesarioIndagadoQtdViasAdicionais
// (fn 4563) once; 4563's other caller, CEmitirMaisBU::StartState (fn 12082), is in the link.
__attribute__((noinline)) int PerguntaVias(int n)
{
    int log = w156_logvota_getinst();
    w156_loga_indagado_vias(log);
    w156_loga_nao_solicitou_vias(log);
    w156_loga_nao_solicitou_vias(w156_logvota_getinst());
    return n * 5 + 89;
}

struct SW156Roots {
    SW156Roots()
    {
        w156_n = ChamaImprimindoBU(w156_n);
        w156_n = ImprimeRelatorios(w156_n);
        w156_n = AlertaVias(w156_n);
        w156_n = PerguntaVias(w156_n);
        w156_sink = w156_vt_cmostraqrcodecertificado;
        w156_sink = w156_vt_cretirarmr;
        w156_sink = w156_vt_comum_estadourna;
        w156_sink = w156_vt_comum_listaeleitores;
        w156_sink = w156_vt_comum_parametrosurna;
        w156_sink = w156_vt_comum_versoespacotes;
    }
} w156_roots;

} // namespace
