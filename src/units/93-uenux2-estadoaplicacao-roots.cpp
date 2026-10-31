// Roots: keep the comum::md::estadoaplicacao classes and their converters in the skeleton link the way the target keeps
// them. Their users are not reconstructed yet.
// - Three converters are complete, and the target reaches them only through their vtables (fns 11388, 11389, 11392,
//   11393, 11405, 11406 fill slots 2 and 3), so rooting the vtables keeps the same set.
// - A function with direct calls gets two call sites. The constructors of CLocalidadeEleitoral (fn 5631, target callers
//   9863 and 11389) and CEstadoGeralSA (fn 5625, 10101 and 11393) have one real caller here, so one stand-in each. The
//   constructors of CDadoCarga (fn 5633, 10167 and 11402) and CEstadoGeralVota (fn 5628, 10067 and 11391), GetFaseChar
//   (fn 2253, five callers), AdicionaDeltaT (fn 3702, three callers) and CCabecalhoQRCodeBuilder's DefineHistoricoCarga
//   and DefineCodigoCarga (fns 5622 and 5623, 1956 and 12110 each) have none, and neither do the two converter
//   helpers each of which its class's unwritten slot calls twice (fns 5689, 5690), so one stand-in that calls each
//   twice. The same for CCabecalhoQRCodeBuilder's DefineIdUrna, DefineSecao and DefineZona (fns 5621, 5620, 5618, 1956
//   and 12110 each: estadoaplicacao_use_local, which varies every argument so binaryen folds none) and IsOrigemSA and
//   IsOrigemRED (fns 5617, 5616, which fn 5604 calls twice each: estadoaplicacao_use_origem). With two callers each the
//   two tests stay out of line, and binaryen merges them into one shared body, as the target's fn 6028. CDadoCarga's constructor has one real caller now, its converter's DoDesconverte (11402), and the stand-in
//   stands for 10167.
// - CDadoCorrespondencia's constructor (fn 5630) has one direct caller in the target (11400) and a table slot (450), so
//   one stand-in and its address.
// - ValidaCriacao, ValidaModelo, ConverteEstadoSA, DesconverteEstadoSA and the two *TipoAjusteDataHora helpers have one
//   caller each in the target and here, so binaryen inlines them; they are left unrooted.
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2 or
// ASN.1 header. The stand-ins are only address-taken, so binaryen can fold no argument of theirs.
extern "C" {
extern const char estadoaplicacao_localidade_vt[] __asm__("_ZTVN5comum3asn29CConversorLocalidadeEleitoralE");
extern const char estadoaplicacao_ajuste_vt[] __asm__("_ZTVN5comum3asn24CConversorAjusteDataHoraE");
extern const char estadoaplicacao_sa_vt[] __asm__("_ZTVN5comum3asn23CConversorEstadoGeralSAE");
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
bool estadoaplicacao_origemsa(const void*) __asm__("_ZNK5comum23CCabecalhoQRCodeBuilder10IsOrigemSAEv");
bool estadoaplicacao_origemred(const void*) __asm__("_ZNK5comum23CCabecalhoQRCodeBuilder11IsOrigemREDEv");
void* estadoaplicacao_vota(void*, int, int, int, void*, void*, void*, int, int, void*, int, void*, void*, int) __asm__("_ZN5comum2md15estadoaplicacao16CEstadoGeralVotaC1ENS_11EEstadoVotaENS_19EEstadoEncerramentoEhNSt3__28optionalIjEENS6_IN3api9CDateTimeEEESA_ttSA_bNS1_27CNumViasImpressasRelatoriosESA_b");
void* estadoaplicacao_corresp(void*, int, void*, void*, void*, void*, void*, void*) __asm__("_ZN5comum2md15estadoaplicacao20CDadoCorrespondenciaC1EjNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEN3api9CDateTimeES9_NS1_20CLocalidadeEleitoralENS3_6vectorIhNS7_IhEEEEN7ecourna3app5dados26CIdentificadorGeradorMidiaE");
void estadoaplicacao_app(void*, const void*, int) __asm__("_ZNK5comum3asn24CConversorEstadoGeralGap22ConverteUrnaAplicativoENS_15EUrnaAplicativoE");
int estadoaplicacao_desapp(const void*, const void*) __asm__("_ZNK5comum3asn24CConversorEstadoGeralGap25DesconverteUrnaAplicativoERKN20ModuloEstadoGeralGap14UrnaAplicativoE");
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

__attribute__((noinline)) void estadoaplicacao_use_app(void* a, void* b, const void* conversor, int atual, int anterior)
{
    estadoaplicacao_app(a, conversor, atual);
    estadoaplicacao_app(b, conversor, anterior + 1);
}

__attribute__((noinline)) int estadoaplicacao_use_desapp(const void* conversor, const void* a, const void* b)
{
    return estadoaplicacao_desapp(conversor, a) * estadoaplicacao_desapp(conversor, b);
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

__attribute__((noinline)) int estadoaplicacao_use_origem(const void* a, const void* b)
{
    return estadoaplicacao_origemsa(a) + 2 * estadoaplicacao_origemred(a) + 4 * estadoaplicacao_origemsa(b) +
           8 * estadoaplicacao_origemred(b);
}

__attribute__((noinline)) void estadoaplicacao_build_vota(void** dado, void** args, int* v)
{
    estadoaplicacao_vota(dado[0], v[0], v[1], v[2], args[0], args[1], args[2], v[3], v[4], args[3], v[5], args[4], args[5], v[6]);
    estadoaplicacao_vota(dado[1], v[1], v[0], v[3], args[0], args[2], args[1], v[2], v[5], args[3], v[4], args[4], args[5], v[6]);
}

__attribute__((noinline)) void* estadoaplicacao_build_corresp(void* dado, void** args, int numero)
{
    return estadoaplicacao_corresp(dado, numero, args[0], args[1], args[2], args[3], args[4], args[5]);
}

struct SEstadoAplicacaoRoots {
    SEstadoAplicacaoRoots()
    {
        estadoaplicacao_sink = estadoaplicacao_localidade_vt;
        estadoaplicacao_sink = estadoaplicacao_ajuste_vt;
        estadoaplicacao_sink = estadoaplicacao_sa_vt;
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_localidade);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_sa);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_carga);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_fase);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_delta);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_app);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_desapp);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_historico);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_idcarga);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_local);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_use_origem);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_vota);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_build_corresp);
        estadoaplicacao_sink = reinterpret_cast<const void*>(&estadoaplicacao_corresp);
    }
} estadoaplicacao_roots;

} // namespace
