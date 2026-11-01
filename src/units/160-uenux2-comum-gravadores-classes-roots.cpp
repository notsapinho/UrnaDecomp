// Roots: reach unit 160's functions the way the target's callers do, until those callers land. Every stand-in here has
// a body no target function has and is not called; the ones that construct build their objects in buffers they are
// given, and pass what the target's callers vary as variables, so that binaryen folds no argument:
// - comum::CCopiadorMR's constructor (fn 1276): fns 3827 and 12134; 3827 is written, the stand-in is for 12134, which
//   calls it nine times with nine extensions;
// - comum::CCopiadorWSQMR's constructor (fn 3827): fn 12134 calls it three times, with the extensions 16, 17 and 18;
// - comum::md::CIdentificacaoVotavel's constructor (fn 5864): fn 3820 calls it twice, with the party 0 and a number;
// - comum::md::CVotosVotavel's constructors (fns 2856 and 5863): fns 3819 and 3820, and fn 3820 twice.
// Each returns `this` in the target, which a caller reads (3827 reads 1276's, 12134 3827's, 3820 the others'), so the
// stand-ins read the results of their placement news. The copiers' constructors store their classes' vptrs, which
// keeps both vtables.
// - comum::CGravadorEnvelopeArquivo's constructor (fn 5856): fn 12098 calls it twice, with the extension 9 and 11, the
//   SAVD file 43 and 44 and the envelope type 2 and 4, and reads its result.
// comum::CGravadorEnvelopeArquivo::LeConteudo (fn 11623) needs no root: its vtable, which the target reaches it
// through, is in unit 136's sink.
// comum::asn::CConversorEnvelopeGenerico: the target reaches DoConverte and DoDesconverte (fns 10271, 10270) only
// through its vtable (@1598820), which fn 2724 stores (a shim into a body binaryen merged, which 11626, 11629 and
// 2725 call), not written yet; so its address goes into a sink. Its slots store CConversorUrna's vtable,
// CConversorUrna's those of CConversorCorrespResultado and CConversorTipoApuracaoSA, and CConversorCorrespResultado's
// slots CConversorCarga's.
#include <new>

#include "app/comum/carquivosresultado.h"
#include "app/comum/gravadores/ccopiadormr.h"
#include "app/comum/gravadores/cgravadorenvelopearquivo.h"
#include "app/comum/gravadores/md/cvotosvotavel.h"

extern "C" const char w160_vt_envelope[] __asm__("_ZTVN5comum3asn26CConversorEnvelopeGenericoE");

namespace {

// stands for fn 12134
__attribute__((noinline)) long w160_copiadores(void* a, void* b, void* c, void* d, comum::TMunicipioID municipio,
    comum::TZonaID zona, comum::TSecaoID secao, char fase, comum::EExtensaoArquivoResultado extensao,
    comum::EExtensaoArquivoResultado outra)
{
    comum::CCopiadorMR* mr = new (a) comum::CCopiadorMR(municipio, zona, secao, fase, extensao);
    comum::CCopiadorMR* outro = new (b) comum::CCopiadorMR(municipio, zona, secao, fase, outra);
    comum::CCopiadorWSQMR* wsq = new (c) comum::CCopiadorWSQMR(municipio, zona, secao, fase, extensao);
    comum::CCopiadorWSQMR* outroWsq = new (d) comum::CCopiadorWSQMR(municipio, zona, secao, fase, outra);
    return (reinterpret_cast<long>(mr) - reinterpret_cast<long>(outro)) +
        (reinterpret_cast<long>(wsq) ^ reinterpret_cast<long>(outroWsq));
}

// stands for fns 3819 and 3820
__attribute__((noinline)) long w160_votos(void* a, void* b, void* c, void* d, void* e, void* f,
    comum::md::CVoto::ETipo tipo, comum::md::CVoto::ETipo outro, comum::TCandidatoID candidato, ueword quantidade,
    comum::TPartidoID partido)
{
    comum::md::CIdentificacaoVotavel* semPartido = new (a) comum::md::CIdentificacaoVotavel(candidato, 0);
    comum::md::CIdentificacaoVotavel* comPartido = new (b) comum::md::CIdentificacaoVotavel(candidato, partido);
    comum::md::CVotosVotavel* v = new (c) comum::md::CVotosVotavel(tipo, candidato, quantidade, *semPartido);
    comum::md::CVotosVotavel* w = new (d) comum::md::CVotosVotavel(outro, candidato, quantidade, *comPartido);
    comum::md::CVotosVotavel* x = new (e) comum::md::CVotosVotavel(tipo, candidato, quantidade);
    comum::md::CVotosVotavel* y = new (f) comum::md::CVotosVotavel(outro, candidato, quantidade);
    return (reinterpret_cast<long>(v) - reinterpret_cast<long>(w)) +
        (reinterpret_cast<long>(x) ^ reinterpret_cast<long>(y));
}

// stands for fn 12098
__attribute__((noinline)) long w160_envelopes(void* a, void* b, const api::CDateTime& dataHora,
    comum::TMunicipioID municipio, comum::TZonaID zona, comum::TLocalID local, comum::TSecaoID secao, char fase,
    const comum::md::estadoaplicacao::CDadoCorrespondencia& correspondencia, const std::string& nome)
{
    comum::CGravadorEnvelopeArquivo* bu = new (a) comum::CGravadorEnvelopeArquivo(dataHora, municipio, zona, local,
        secao, fase, comum::EXTENSAO_IMGBU_DAT, static_cast<comum::ESavdArquivoUE>(43),
        comum::md::CEnvelopeGenerico::ENVELOPE_BOLETIM_URNA_IMPRESSO, correspondencia, nome);
    comum::CGravadorEnvelopeArquivo* zeresima = new (b) comum::CGravadorEnvelopeArquivo(dataHora, municipio, zona,
        local, secao, fase, comum::EXTENSAO_IMGZE_DAT, static_cast<comum::ESavdArquivoUE>(44),
        comum::md::CEnvelopeGenerico::ENVELOPE_ZERESIMA_IMPRESSA, correspondencia, nome);
    return reinterpret_cast<long>(bu) - reinterpret_cast<long>(zeresima);
}

long (*volatile w160_sink_copiadores)(void*, void*, void*, void*, comum::TMunicipioID, comum::TZonaID, comum::TSecaoID,
    char, comum::EExtensaoArquivoResultado, comum::EExtensaoArquivoResultado);

long (*volatile w160_sink_votos)(void*, void*, void*, void*, void*, void*, comum::md::CVoto::ETipo,
    comum::md::CVoto::ETipo, comum::TCandidatoID, ueword, comum::TPartidoID);

long (*volatile w160_sink_envelopes)(void*, void*, const api::CDateTime&, comum::TMunicipioID, comum::TZonaID,
    comum::TLocalID, comum::TSecaoID, char, const comum::md::estadoaplicacao::CDadoCorrespondencia&, const std::string&);

const void* volatile w160_sink_vt;

struct SW160Roots {
    SW160Roots()
    {
        w160_sink_copiadores = w160_copiadores;
        w160_sink_votos = w160_votos;
        w160_sink_envelopes = w160_envelopes;
        w160_sink_vt = w160_vt_envelope;
    }
} w160_roots;

} // namespace
