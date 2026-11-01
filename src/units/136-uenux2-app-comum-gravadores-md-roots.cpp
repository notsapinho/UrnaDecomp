// Roots: reach unit 136's data-class members the way the target's callers do, until those callers land. Every stand-in
// here has a body no target function has and is not called; the ones that construct build their objects in buffers
// they are given, and only w136_destroi_urna destroys one. Each function below has direct callers in the target, so
// each gets two call sites in our link and stays out of line; the stand-ins pass their own parameters, so that
// binaryen folds no argument:
// - comum::md::CCorrespondenciaResultado's constructor (fn 2801): fns 10288, 11587, 11626 and 11629; 10288 is written
//   (unit 160), the stand-in is for the others;
// - comum::md::CUrna's constructors (fns 2854 and 2855): fns 10284, 11587, 11626 and 11629; 10284 is written (unit
//   160), the stand-in is for the others;
// - comum::md::CEnvelopeGenerico's constructors (fns 3821, 5860 and 5861): fns 2725, 10270 and 11629, fns 10270 and
//   11626, and fns 10270 and 11629; 10270 is written (unit 160), the stand-in is for the others;
// - comum::md::CEntidadeHashes::ValidaCriacao (fn 5855): fn 11620 calls it twice;
// - comum::md::CUrna's implicit destructor (fn 1394): fns 2725, 10270, 11587, 11626 and 11629; 10270 is written (unit
//   160), the stand-in is for the others. It returns `this`, which 10270 frees (`f136(f1394(l7))`), so the stand-in
//   deletes its two objects. Unit 160's cconversorenvelopegenerico.cpp.o emits that inline destructor ahead of this
//   object, and the link keeps its copy; this object compiles with the tree's flags (UENUX2_CXXFLAGS, the fragment's
//   rule) all the same.
// CCarga's copy constructor (fn 1557), CUrna::ValidaCriacao (fn 5862) and CEnvelopeGenerico::ValidaCriacao (fn 3822)
// have their callers among these constructors. Fns 2801, 3821 and 5861 return `this` in the target, which a caller
// reads, so the stand-ins read the result of the placement new, which clang takes from the constructor's returned
// `this` (measured: with the result unread, binaryen dropped it from all three, and 3821 and 5861 then differed in
// that result alone); fns 2854, 2855 and 5860 return nothing in the target (binaryen dropped the unread result), and the
// stand-ins do not read theirs. CEntidadeHashes::ValidaCriacao is private, so it is called through an asm label.
// The recorders comum::CGravadorHashes, CGravadorLog, CGravadorRDV and CGravadorVersoesArquivos: the target reaches
// their destructors only through their vtables, which their constructors store (inlined into
// vota::CGravaResultado::StartState, fn 12098), not written yet; so the vtables' addresses go into a sink, the
// reference the target has. CGravadorEnvelopeArquivo's vtable and IGravadorEnvelope's are stored by
// CGravadorEnvelopeArquivo's constructor (fn 5856, unit 160's) and destructors.
#include <new>
#include <optional>
#include <string>
#include <vector>

#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "app/comum/gravadores/md/cenvelopegenerico.h"
#include "app/comum/gravadores/md/curna.h"

extern "C" {
void w136_valida_hashes(const void* entidade) __asm__("_ZNK5comum2md15CEntidadeHashes13ValidaCriacaoEv");
extern const char w136_vt_hashes[] __asm__("_ZTVN5comum15CGravadorHashesE");
extern const char w136_vt_log[] __asm__("_ZTVN5comum12CGravadorLogE");
extern const char w136_vt_rdv[] __asm__("_ZTVN5comum12CGravadorRDVE");
extern const char w136_vt_versoes[] __asm__("_ZTVN5comum24CGravadorVersoesArquivosE");
}

namespace {

// stands for fns 11587, 11626 and 11629
__attribute__((noinline)) long w136_correspondencia(void* a, void* b, uedword municipio, ueword zona, ueword secao,
    const comum::md::CCarga& carga, comum::EUrnaTipo tipo, comum::EUrnaTipo outro)
{
    return reinterpret_cast<long>(new (a) comum::md::CCorrespondenciaResultado(municipio, zona, secao, carga, tipo)) -
        reinterpret_cast<long>(new (b) comum::md::CCorrespondenciaResultado(municipio, zona, secao, carga, outro));
}

// stands for fns 11587, 11626 and 11629
__attribute__((noinline)) int w136_urna(void* a, void* b, void* c, void* d, comum::EUrnaTipo tipo,
    const std::string& versao, const comum::md::CCorrespondenciaResultado& correspondencia,
    comum::ETipoArquivo tipoArquivo, comum::ETipoArquivo outroTipo, const std::string& serial,
    const comum::md::CTipoApuracaoSA& apuracao)
{
    new (a) comum::md::CUrna(tipo, versao, correspondencia, tipoArquivo, serial);
    new (b) comum::md::CUrna(tipo, versao, correspondencia, outroTipo, serial);
    new (c) comum::md::CUrna(tipo, versao, correspondencia, tipoArquivo, serial, apuracao);
    new (d) comum::md::CUrna(tipo, versao, correspondencia, outroTipo, serial, apuracao);
    return 5;
}

// stands for fns 2725, 11626 and 11629
__attribute__((noinline)) long w136_envelope(void* a, void* b, void* c, void* d, void* e, void* f,
    const comum::md::CCabecalhoEntidade& cabecalho, comum::EUrnaFase fase, const comum::md::CUrna& urna,
    comum::TMunicipioID municipio, comum::TZonaID zona, const std::optional<comum::TLocalID>& local,
    comum::TSecaoID secao, comum::md::CEnvelopeGenerico::Tipo tipo, comum::md::CEnvelopeGenerico::Tipo outro,
    const comum::md::CSeguranca& seguranca, const std::vector<uebyte>& conteudo, comum::EUrnaTipo tipoUrna)
{
    new (c) comum::md::CEnvelopeGenerico(cabecalho, fase, urna, municipio, zona, local, secao, tipo, conteudo);
    new (d) comum::md::CEnvelopeGenerico(cabecalho, fase, urna, municipio, zona, local, secao, outro, conteudo);
    return reinterpret_cast<long>(new (a) comum::md::CEnvelopeGenerico(cabecalho, fase, municipio, zona, local, secao,
               tipo, seguranca, conteudo, tipoUrna)) +
        reinterpret_cast<long>(new (b) comum::md::CEnvelopeGenerico(cabecalho, fase, municipio, zona, local, secao, outro,
            seguranca, conteudo, tipoUrna)) -
        reinterpret_cast<long>(new (e) comum::md::CEnvelopeGenerico(cabecalho, fase, municipio, zona, local, secao, tipo,
            conteudo, tipoUrna)) -
        reinterpret_cast<long>(new (f) comum::md::CEnvelopeGenerico(cabecalho, fase, municipio, zona, local, secao, outro,
            conteudo, tipoUrna));
}

// stands for fns 2725, 11587, 11626 and 11629
__attribute__((noinline)) int w136_destroi_urna(comum::md::CUrna* urna, comum::md::CUrna* outra)
{
    delete urna;
    delete outra;
    return 13;
}

// stands for fn 11620
__attribute__((noinline)) int w136_hashes(const void* entidade, const void* outra)
{
    w136_valida_hashes(entidade);
    w136_valida_hashes(outra);
    return 11;
}

long (*volatile w136_sink_correspondencia)(void*, void*, uedword, ueword, ueword, const comum::md::CCarga&, comum::EUrnaTipo,
    comum::EUrnaTipo);
int (*volatile w136_sink_urna)(void*, void*, void*, void*, comum::EUrnaTipo, const std::string&,
    const comum::md::CCorrespondenciaResultado&, comum::ETipoArquivo, comum::ETipoArquivo, const std::string&,
    const comum::md::CTipoApuracaoSA&);
long (*volatile w136_sink_envelope)(void*, void*, void*, void*, void*, void*, const comum::md::CCabecalhoEntidade&,
    comum::EUrnaFase, const comum::md::CUrna&, comum::TMunicipioID, comum::TZonaID, const std::optional<comum::TLocalID>&,
    comum::TSecaoID, comum::md::CEnvelopeGenerico::Tipo, comum::md::CEnvelopeGenerico::Tipo, const comum::md::CSeguranca&,
    const std::vector<uebyte>&, comum::EUrnaTipo);
int (*volatile w136_sink_hashes)(const void*, const void*);
int (*volatile w136_sink_destroi_urna)(comum::md::CUrna*, comum::md::CUrna*);
const void* volatile w136_sink_vt[4];

struct SW136Roots {
    SW136Roots()
    {
        w136_sink_correspondencia = w136_correspondencia;
        w136_sink_urna = w136_urna;
        w136_sink_envelope = w136_envelope;
        w136_sink_hashes = w136_hashes;
        w136_sink_destroi_urna = w136_destroi_urna;
        w136_sink_vt[0] = w136_vt_hashes;
        w136_sink_vt[1] = w136_vt_log;
        w136_sink_vt[2] = w136_vt_rdv;
        w136_sink_vt[3] = w136_vt_versoes;
    }
} w136_roots;

} // namespace
