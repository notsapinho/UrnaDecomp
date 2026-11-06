// Roots of unit 102: the std::shared_ptr control blocks of this tree's classes, in the shape src/units/README.md "A
// control block" sanctions: a builder the link drops, and the block's vtable kept by the static constructor below.
//
// The target's builders are not reconstructed (the fragment lists each block with the function that stores its vptr, by
// the grep of that section). So each builder here is an optnone function that nothing calls, which wasm-ld drops:
// - SBloco<U, T>::Constroi takes the T* it never gets and returns the std::shared_ptr<U>, for a
//   __shared_ptr_pointer<T*, ...>. It uses no constructor of T, so a head of T is enough. U is the first template
//   argument of the block's __shared_ptr_default_delete in the RTTI name.
// - the w102_ functions and SFonte hold the std::make_shared<T> of a __shared_ptr_emplace<T>. They need T's constructor
//   declared, not defined, and the block does not depend on its parameters: each is what the class's header declares.
// clang emits the block in this object with the builder. The target reaches its members only through its vtable, whose
// address the builder stores, so the sink below is the reference the target has. A block whose vptr a function of the
// link stores needs neither: its builder and sink went (the fragment lists them).
//
// Every block's kind was checked against the target's own vptr store: emplace where the builder calls make_shared,
// pointer where it allocates the T and the block apart. No stand-in stays in the link
// (`/usr/bin/grep -cE 'w102_|6SBloco|6SFonte' build/out/wasm-map/vota_web/names.tsv` prints 0).
//
// The fragment's name sorts between 10- and 11-, ahead of most units, so this object is the first definition of what it
// and a later companion both instantiate: comum::IResultado's D2 (fn 12090) came from here, not from unit 60's pending
// object, until unit 122's iresultado.cpp.o, which uenux2's sources link ahead of it, emitted it. Compiled with
// APP_CXXFLAGS; the fragment says what UENUX2_CXXFLAGS gives, and what ecourna's flags give for the ecourna classes'
// blocks. The order of
// the sink lines is free (docs/reference/facts/splat.md section S9).
#include <memory>
#include <string>
#include <vector>

#include "api/audio/alsa/cwavfile.h"
#include "api/audio/logger.h"
#include "api/gui/cdataimage.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cpreshownothing.h"
#include "api/persistencia/idao.h"
#include "app/comum/comparecimentomesario/dao/icomparecimentomesariodao.h"
#include "app/comum/dados/asn/candidatura/cvisitantefoto.h"
#include "app/comum/dados/ccandidaturasds.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/crespostasds.h"
#include "app/comum/gravadores/ccopiadormr.h"
#include "app/comum/gravadores/cgravadorbu.h"
#include "app/comum/gravadores/cgravadorenvelopearquivo.h"
#include "app/comum/gravadores/cgravadorhashes.h"
#include "app/comum/gravadores/cgravadorlog.h"
#include "app/comum/gravadores/cgravadorrcsecao.h"
#include "app/comum/gravadores/cgravadorrdv.h"
#include "app/comum/gravadores/cgravadorversoesarquivos.h"
#include "app/comum/gravadores/cgravadorwsq.h"
#include "app/comum/justificativa/dao/ijustificadordao.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cidentificacaournacontingencia.h"
#include "app/vota/comum/cpreshowformvota.h"
#include "app/vota/eleitor/fimvotacao/cprogressoencerramento.h"

extern "C" {
extern const char w102_vt_cdataimage_ccandidaturasdsfoto[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api10CDataImageIN5comum19CCandidaturasDSFotoEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_logger[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api6LoggerENS_9allocatorIS2_EEEE");
extern const char w102_vt_cwavfile[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api8CWavFileENS_9allocatorIS2_EEEE");
extern const char w102_vt_cdatatext_crespostasdsnumero[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum18CRespostasDSNumeroEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccandidaturasdsnome[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum19CCandidaturasDSNomeEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccandidaturasdsnumero[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum21CCandidaturasDSNumeroEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccargodsnomesexocandidato[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum25CCargoDSNomeSexoCandidatoEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cprogressoencerramento[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN4vota22CProgressoEncerramentoENS_9allocatorIS2_EEEE");
extern const char w102_vt_ccopiadormr[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN5comum11CCopiadorMRENS_9allocatorIS2_EEEE");
extern const char w102_vt_ccopiadorwsqmr[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN5comum14CCopiadorWSQMRENS_9allocatorIS2_EEEE");
extern const char w102_vt_cpreshownothing_iscreen[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api15CPreShowNothingINS1_7IScreenEEENS_10shared_ptrINS1_8IPreShowIS3_EEE27__shared_ptr_default_deleteIS8_S4_EENS_9allocatorIS4_EEEE");
extern const char w102_vt_cgravadorbu[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum11CGravadorBUENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorlog[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorLogENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorrdv[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorRDVENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorwsq[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorWSQENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorhashes[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum15CGravadorHashesENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorrcsecao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum16CGravadorRCSecaoENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorenvelopearquivo[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum24CGravadorEnvelopeArquivoENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorversoesarquivos[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum24CGravadorVersoesArquivosENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cidentificacaosecao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md19CIdentificacaoSecaoENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cidentificacaournacontingencia[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md30CIdentificacaoUrnaContingenciaENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cvisitantefoto[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3asn14CVisitanteFotoENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_ijustificadordao_idao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao16IJustificadorDAOENS_10shared_ptrIN3api12persistencia4IDAOEE27__shared_ptr_default_deleteIS8_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_icomparecimentomesariodao_idao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao25IComparecimentoMesarioDAOENS_10shared_ptrIN3api12persistencia4IDAOEE27__shared_ptr_default_deleteIS8_S3_EENS_9allocatorIS3_EEEE");
}

namespace api {
class IScreenMT;
} // namespace api

template <typename U, typename T>
struct SBloco {
    __attribute__((optnone, noinline)) static std::shared_ptr<U> Constroi(T* objeto)
    {
        return std::shared_ptr<U>(objeto);
    }
};

using TDao = api::persistencia::IDAO;

template struct SBloco<TDao, comum::dao::IComparecimentoMesarioDAO>;
template struct SBloco<TDao, comum::dao::IJustificadorDAO>;
template struct SBloco<comum::md::CIdentificacaoSecao, comum::md::CIdentificacaoSecao>;
template struct SBloco<comum::md::CIdentificacaoUrnaContingencia, comum::md::CIdentificacaoUrnaContingencia>;
template struct SBloco<comum::asn::CVisitanteFoto, comum::asn::CVisitanteFoto>;
template struct SBloco<comum::IGravador, comum::CGravadorWSQ>;

__attribute__((optnone, noinline)) std::shared_ptr<vota::CProgressoEncerramento> w102_progresso()
{
    return std::make_shared<vota::CProgressoEncerramento>();
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CWavFile> w102_wav(const api::CWavAudio& a, const void* d)
{
    return std::make_shared<api::CWavFile>(a, d);
}

using TGravador = comum::IGravador;
using TPreShow = api::IPreShow<api::IScreen>;
template struct SBloco<TGravador, comum::CGravadorBU>;
template struct SBloco<TGravador, comum::CGravadorRDV>;
template struct SBloco<TGravador, comum::CGravadorRCSecao>;
template struct SBloco<TGravador, comum::CGravadorEnvelopeArquivo>;
template struct SBloco<TGravador, comum::CGravadorHashes>;
template struct SBloco<TGravador, comum::CGravadorVersoesArquivos>;
template struct SBloco<TGravador, comum::CGravadorLog>;
template struct SBloco<TPreShow, api::CPreShowNothing<api::IScreen>>;

__attribute__((optnone, noinline)) std::shared_ptr<comum::CCopiadorMR> w102_copiador(comum::TMunicipioID municipio,
    comum::TZonaID zona, comum::TSecaoID secao, char fase, comum::EExtensaoArquivoResultado extensao)
{
    return std::make_shared<comum::CCopiadorMR>(municipio, zona, secao, fase, extensao);
}
__attribute__((optnone, noinline)) std::shared_ptr<comum::CCopiadorWSQMR> w102_copiador_wsq(comum::TMunicipioID municipio,
    comum::TZonaID zona, comum::TSecaoID secao, char fase, comum::EExtensaoArquivoResultado extensao)
{
    return std::make_shared<comum::CCopiadorWSQMR>(municipio, zona, secao, fase, extensao);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::Logger> w102_logger()
{
    return std::make_shared<api::Logger>();
}
template <typename TCampo, typename TFonte>
struct SFonte {
    __attribute__((optnone, noinline)) static std::shared_ptr<TCampo> Constroi(const TFonte& fonte)
    {
        return std::make_shared<TCampo>(fonte);
    }
};
template struct SFonte<api::CDataText<comum::CCandidaturasDSNumero>, comum::CCandidaturasDSNumero>;
template struct SFonte<api::CDataText<comum::CCandidaturasDSNome>, comum::CCandidaturasDSNome>;
template struct SFonte<api::CDataImage<comum::CCandidaturasDSFoto>, comum::CCandidaturasDSFoto>;
template struct SFonte<api::CDataText<comum::CCargoDSNomeSexoCandidato>, comum::CCargoDSNomeSexoCandidato>;
template struct SFonte<api::CDataText<comum::CRespostasDSNumero>, comum::CRespostasDSNumero>;

namespace {

const void* volatile w102_sink;

struct SW102Roots {
    SW102Roots()
    {
        w102_sink = w102_vt_cdataimage_ccandidaturasdsfoto;
        w102_sink = w102_vt_logger;
        w102_sink = w102_vt_cwavfile;
        w102_sink = w102_vt_cdatatext_crespostasdsnumero;
        w102_sink = w102_vt_cdatatext_ccandidaturasdsnome;
        w102_sink = w102_vt_cdatatext_ccandidaturasdsnumero;
        w102_sink = w102_vt_cdatatext_ccargodsnomesexocandidato;
        w102_sink = w102_vt_cprogressoencerramento;
        w102_sink = w102_vt_ccopiadormr;
        w102_sink = w102_vt_ccopiadorwsqmr;
        w102_sink = w102_vt_cpreshownothing_iscreen;
        w102_sink = w102_vt_cgravadorbu;
        w102_sink = w102_vt_cgravadorlog;
        w102_sink = w102_vt_cgravadorrdv;
        w102_sink = w102_vt_cgravadorwsq;
        w102_sink = w102_vt_cgravadorhashes;
        w102_sink = w102_vt_cgravadorrcsecao;
        w102_sink = w102_vt_cgravadorenvelopearquivo;
        w102_sink = w102_vt_cgravadorversoesarquivos;
        w102_sink = w102_vt_cidentificacaosecao;
        w102_sink = w102_vt_cidentificacaournacontingencia;
        w102_sink = w102_vt_cvisitantefoto;
        w102_sink = w102_vt_ijustificadordao_idao;
        w102_sink = w102_vt_icomparecimentomesariodao_idao;
    }
} w102_roots;

} // namespace
