// Roots: keep the comum::md::estadoaplicacao classes and their converters in the skeleton link the way the target keeps
// them. Their users are not reconstructed yet.
// - The target reaches the converters only through their vtables, so rooting a vtable keeps the same set until the
//   functions that store its vptr are in the link. CConversorEstadoGeralGap's vtable is rooted: its slots 2 and 3 (fns
//   11394, 11395) are written, and the target reaches them only through that vtable (table slots 2680 and 2681, no
//   direct caller). Of the Gap's storers, 10112 is in the link and 7787 is not, so its sink stays. The sinks of the
//   other three went, each once the target functions that store its vptr were in the link: CConversorEstadoGeralSA's
//   (slots 11392, 11393), whose one storer is fn 10089 (unit 206's save); CConversorLocalidadeEleitoral's (11388,
//   11389), stored by fns 11399, 11400, 11403 and 11404 (fragment 172); CConversorAjusteDataHora's (11405, 11406),
//   stored by fns 11397 and 11398 (unit 124).
// - A function with direct calls gets two call sites. The constructors of CLocalidadeEleitoral (fn 5631, target callers
//   9863 and 11389) and CEstadoGeralSA (fn 5625, 10101 and 11393) have one real caller here, so one stand-in each, and
//   so has CEstadoGeralVota's (fn 5628, 10067 and 11391: 11391 is fragment 172's, and estadoaplicacao_build_vota stands
//   for 10067). The constructor of CDadoCarga (fn 5633, 10167 and 11402), GetFaseChar (fn 2253, five callers), AdicionaDeltaT (fn 3702, three callers) and CCabecalhoQRCodeBuilder's
//   DefineHistoricoCarga and DefineCodigoCarga (fns 5622 and 5623, 1956 and 12110 each) and CCabecalhoQRCodeBuilder's
//   constructor (fn 5624, 1956 and 12110: estadoaplicacao_build_qrcode) have none, so one stand-in that calls each
//   twice. CEstadoGeralVota::IncrementaQtdBU's stand-in (fn 3701) went: its target callers 12065, 12077 and 12081 are
//   in the link (units 104 and 156). CConversorEstadoGeralGap's ConverteUrnaAplicativo and DesconverteUrnaAplicativo (fns 5689, 5690) have their
//   two call sites each in their one target caller, DoConverte or DoDesconverte (fns 11394, 11395), which are written.
//   The same for CCabecalhoQRCodeBuilder's DefineIdUrna, DefineSecao and DefineZona (fns 5621, 5620, 5618, 1956 and
//   12110 each: estadoaplicacao_use_local, which varies every argument so binaryen folds none). Fn 1956 is in the link
//   now (unit 37), so these stand-ins and estadoaplicacao_use_historico, estadoaplicacao_use_idcarga and
//   estadoaplicacao_build_qrcode stand for fn 12110 alone. IsOrigemSA and IsOrigemRED (fns 5617, 5616) have their
//   target call sites in the link, two each in fn 5604 (unit 155), so they stay out of line, and binaryen merges them
//   into one shared body, as the target's fn 6028. CDadoCarga's constructor has one real caller now, its converter's
//   DoDesconverte (11402), and the stand-in stands for 10167.
// - CDadoCorrespondencia's constructor (fn 5630) has one direct caller in the target (11400, written, fragment 172's)
//   and a table slot (450), so its address. The same for CEstadoGeralGap's constructor (fn 5626: its direct caller is
//   11395, written, and fn 10123 calls it through table slot 453 with invoke_iiiiiiiiiiii) and for
//   CEstadoGeralVota::MarcaInicioAquisicao (fn 5627: its direct caller, fn 5972, is in the link, unit 199's, and table
//   slot 52 holds it).
// - ValidaCriacao, ValidaModelo, ConverteEstadoSA, DesconverteEstadoSA and the two *TipoAjusteDataHora helpers have one
//   caller each in the target and here, so binaryen inlines them; they are left unrooted.
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2 or
// ASN.1 header. The stand-ins are only address-taken, so binaryen can fold no argument of theirs.
extern "C" {
extern const char estadoaplicacao_gap_vt[] __asm__("_ZTVN5comum3asn24CConversorEstadoGeralGapE");
void* estadoaplicacao_localidade(void*, int, int, int) __asm__("_ZN5comum2md15estadoaplicacao20CLocalidadeEleitoralC1Ejtt");
void* estadoaplicacao_sa(void*, int, int, int, int, int) __asm__("_ZN5comum2md15estadoaplicacao14CEstadoGeralSAC1ENS_9EEstadoSAEbjtt");
void* estadoaplicacao_carga(void*, int, int, int, int, int) __asm__("_ZN5comum2md15estadoaplicacao10CDadoCargaC1ENS_10EUrnaTurnoENS_9EUrnaTipoES4_NS_11EUrnaModeloENS_9EUrnaFaseE");
int estadoaplicacao_fase(const void*) __asm__("_ZNK5comum2md15estadoaplicacao10CDadoCarga11GetFaseCharEv");
void estadoaplicacao_delta(void*, int) __asm__("_ZN5comum2md15estadoaplicacao15CAjusteDataHora14AdicionaDeltaTEi");
void estadoaplicacao_historico(void*, const void*) __asm__("_ZN5comum23CCabecalhoQRCodeBuilder20DefineHistoricoCargaERKNSt3__26vectorINS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEENS6_IS8_EEEE");
void estadoaplicacao_idcarga(void*, const void*) __asm__("_ZN5comum23CCabecalhoQRCodeBuilder17DefineCodigoCargaERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void estadoaplicacao_idurna(void*, unsigned) __asm__("_ZN5comum23CCabecalhoQRCodeBuilder12DefineIdUrnaEj");
void estadoaplicacao_secao(void*, unsigned short) __asm__("_ZN5comum23CCabecalhoQRCodeBuilder11DefineSecaoEt");
void estadoaplicacao_zona(void*, unsigned short) __asm__("_ZN5comum23CCabecalhoQRCodeBuilder10DefineZonaEt");
void* estadoaplicacao_vota(void*, int, int, int, void*, void*, void*, int, int, void*, int, void*, void*, int) __asm__("_ZN5comum2md15estadoaplicacao16CEstadoGeralVotaC1ENS_11EEstadoVotaENS_19EEstadoEncerramentoEhNSt3__28optionalIjEENS6_IN3api9CDateTimeEEESA_ttSA_bNS1_27CNumViasImpressasRelatoriosESA_b");
void* estadoaplicacao_corresp(void*, int, void*, void*, void*, void*, void*, void*) __asm__("_ZN5comum2md15estadoaplicacao20CDadoCorrespondenciaC1EjNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEN3api9CDateTimeES9_NS1_20CLocalidadeEleitoralENS3_6vectorIhNS7_IhEEEEN7ecourna3app5dados26CIdentificadorGeradorMidiaE");
void* estadoaplicacao_gap(void*, void*, int, int, int, int, int, int, void*, void*, void*) __asm__("_ZN5comum2md15estadoaplicacao15CEstadoGeralGapC1ENSt3__26vectorINS1_20CDadoCorrespondenciaENS3_9allocatorIS5_EEEENS_15EUrnaAplicativoES9_bbbbNS1_27CNumViasImpressasRelatoriosESA_NS3_8optionalIN3api5CDateEEE");
void* estadoaplicacao_qrcode(void*) __asm__("_ZN5comum23CCabecalhoQRCodeBuilderC1Ev");
void estadoaplicacao_inicio(void*) __asm__("_ZN5comum2md15estadoaplicacao16CEstadoGeralVota20MarcaInicioAquisicaoEv");
}

namespace {

const void* volatile estadoaplicacao_sink;

__attribute__((noinline)) void estadoaplicacao_build_localidade(void* dado, int municipio, int zona, int secao)
{
    estadoaplicacao_localidade(dado, municipio, zona, secao);
}

__attribute__((noinline)) void estadoaplicacao_build_sa(void* dado, int estado, int bloqueada, int municipio, int zona, int secao)
{
    estadoaplicacao_sa(dado, estado, bloqueada, municipio, zona, secao);
}

__attribute__((noinline)) void estadoaplicacao_build_carga(void* a, void* b, int turno, int t1, int t2, int modelo, int fase)
{
    estadoaplicacao_carga(a, turno, t1, t2, modelo, fase);
    estadoaplicacao_carga(b, turno, t2, t1, modelo, fase);
}

__attribute__((noinline)) int estadoaplicacao_use_fase(const void* a, const void* b)
{
    return estadoaplicacao_fase(a) + estadoaplicacao_fase(b);
}

__attribute__((noinline)) void estadoaplicacao_use_delta(void* a, void* b, int delta)
{
    estadoaplicacao_delta(a, delta);
    estadoaplicacao_delta(b, delta + 2);
}

__attribute__((noinline)) void estadoaplicacao_use_historico(void* a, void* b, const void* cargas)
{
    estadoaplicacao_historico(a, cargas);
    estadoaplicacao_historico(b, cargas);
}

__attribute__((noinline)) void estadoaplicacao_use_idcarga(void* a, void* b, const void* id)
{
    estadoaplicacao_idcarga(a, id);
    estadoaplicacao_idcarga(b, id);
}

__attribute__((noinline)) void estadoaplicacao_use_local(void* a, void* b, unsigned urna, unsigned short secao, unsigned short zona)
{
    estadoaplicacao_idurna(a, urna);
    estadoaplicacao_secao(a, secao);
    estadoaplicacao_zona(a, zona);
    estadoaplicacao_idurna(b, urna + 3);
    estadoaplicacao_secao(b, zona);
    estadoaplicacao_zona(b, secao);
}

__attribute__((noinline)) void* estadoaplicacao_build_qrcode(char* a, char* b)
{
    estadoaplicacao_qrcode(a);
    return estadoaplicacao_qrcode(b + 8);
}

__attribute__((noinline)) void estadoaplicacao_build_vota(void** dado, void** args, int* v)
{
    estadoaplicacao_vota(dado[0], v[0], v[1], v[2], args[0], args[1], args[2], v[3], v[4], args[3], v[5], args[4], args[5], v[6]);
    estadoaplicacao_vota(dado[1], v[1], v[0], v[3], args[0], args[2], args[1], v[2], v[5], args[3], v[4], args[4], args[5], v[6]);
}

struct SEstadoAplicacaoRoots {
    SEstadoAplicacaoRoots()
    {
        estadoaplicacao_sink = estadoaplicacao_gap_vt;
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_localidade);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_sa);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_carga);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_fase);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_delta);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_historico);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_idcarga);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_local);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_vota);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_qrcode);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_corresp);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_gap);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_inicio);
    }
} estadoaplicacao_roots;

} // namespace
