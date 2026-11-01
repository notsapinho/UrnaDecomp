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
// address the builder stores, so the sink below is the reference the target has. The last five lines of the sink are
// the vota menu items' own vtables, which fn 6599 stores: vota::CItemVisualizarCandidatosVota's keeps that class's D0,
// and the other four keep their slot 3 (fns 12267, 12266, 12259, 12255) and their shared D0 (fn 2939).
//
// Every block's kind was checked against the target's own vptr store: emplace where the builder calls make_shared,
// pointer where it allocates the T and the block apart. No stand-in stays in the link
// (`/usr/bin/grep -cE 'w102_|6SBloco|6SFonte' build/out/wasm-map/vota_web/names.tsv` prints 0).
//
// The fragment's name sorts between 10- and 11-, ahead of most units, so this object is the first definition of what it
// and a later companion both instantiate: comum::IResultado's D2 (fn 12090) came from here, not from unit 60's pending
// object, until unit 122's iresultado.cpp.o, which uenux2's sources link ahead of it, emitted it. Compiled with
// APP_CXXFLAGS. Compiled with UENUX2_CXXFLAGS the object's 391 functions compare equal, by function with the
// object-local numbers masked. The fragment says what ecourna's flags give for the ecourna classes' blocks. The order of
// the sink lines is free (docs/reference/facts/splat.md section S9).
#include <memory>
#include <string>
#include <vector>

#include "api/audio/alsa/cwavfile.h"
#include "api/audio/logger.h"
#include "api/gui/ccutfieldpaper.h"
#include "api/gui/cdataimage.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cdsimagefield.h"
#include "api/gui/cfixedimage.h"
#include "api/gui/cimagefieldupdate.h"
#include "api/gui/cinputfieldmt.h"
#include "api/gui/cmovie.h"
#include "api/gui/cmoviefield.h"
#include "api/gui/cnewlinefieldpaper.h"
#include "api/gui/cnumbervalidation.h"
#include "api/gui/coptionvalidation.h"
#include "api/gui/cpowerinformation.h"
#include "api/gui/cpreshowclearscreen.h"
#include "api/gui/cpreshownothing.h"
#include "api/gui/cprogressbar.h"
#include "api/gui/cqrcodeimagefieldpaper.h"
#include "api/gui/ctextfieldblinking.h"
#include "api/gui/ctextfieldpaper.h"
#include "api/gui/ctextfieldupdate.h"
#include "api/gui/iinputvalidation.h"
#include "api/persistencia/idao.h"
#include "app/comum/comparecimentomesario/dao/icomparecimentomesariodao.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/asn/candidatura/cvisitantefoto.h"
#include "app/comum/dados/asn/eleitor/cvisitanteeleitor.h"
#include "app/comum/dados/ccandidaturasds.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/crespostasds.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"
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
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"
#include "app/vota/operador/outrasopcoes/citensmenuvota.h"
#include "ecourna/api/security/caescipher.hpp"
#include "ecourna/api/security/cblockcipher.hpp"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/security/ctrng.hpp"
#include "ecourna/app/dados/resultadournacadastro/cidentificacaojustificativa.hpp"

extern "C" {
extern const char w102_vt_cdataimage_ccandidaturasdsfoto[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api10CDataImageIN5comum19CCandidaturasDSFotoEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cfixedimage[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api11CFixedImageENS_9allocatorIS2_EEEE");
extern const char w102_vt_cmoviefield[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api11CMovieFieldENS_9allocatorIS2_EEEE");
extern const char w102_vt_cprogressbar[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api12CProgressBarENS_9allocatorIS2_EEEE");
extern const char w102_vt_ctextfieldupdate[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api16CTextFieldUpdateENS_9allocatorIS2_EEEE");
extern const char w102_vt_cimagefieldupdate[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api17CImageFieldUpdateENS_9allocatorIS2_EEEE");
extern const char w102_vt_ctextfieldblinking[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api18CTextFieldBlinkingENS_9allocatorIS2_EEEE");
extern const char w102_vt_batteryicondatasource_cpowerinformation_iconorientation_0[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api21BatteryIconDataSourceILNS1_17CPowerInformation15IconOrientationE0EEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cmovie[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api6CMovieENS_9allocatorIS2_EEEE");
extern const char w102_vt_logger[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api6LoggerENS_9allocatorIS2_EEEE");
extern const char w102_vt_cwavfile[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api8CWavFileENS_9allocatorIS2_EEEE");
extern const char w102_vt_cdatatext_crespostasdsnumero[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum18CRespostasDSNumeroEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccandidaturasdsnome[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum19CCandidaturasDSNomeEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccandidaturasdsnumero[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum21CCandidaturasDSNumeroEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cdatatext_ccargodsnomesexocandidato[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api9CDataTextIN5comum25CCargoDSNomeSexoCandidatoEEENS_9allocatorIS5_EEEE");
extern const char w102_vt_cpreshowprogressbar[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN4vota19CPreShowProgressBarENS_9allocatorIS2_EEEE");
extern const char w102_vt_cprogressoencerramento[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN4vota22CProgressoEncerramentoENS_9allocatorIS2_EEEE");
extern const char w102_vt_ccopiadormr[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN5comum11CCopiadorMRENS_9allocatorIS2_EEEE");
extern const char w102_vt_ccopiadorwsqmr[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN5comum14CCopiadorWSQMRENS_9allocatorIS2_EEEE");
extern const char w102_vt_ctrng[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN7ecourna3api8security5CTrngENS_9allocatorIS4_EEEE");
extern const char w102_vt_cdsimagefield[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api13CDSImageFieldENS_10shared_ptrINS1_10IFormFieldINS1_7IScreenEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cinputfieldmt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api13CInputFieldMTENS_10shared_ptrINS1_11IInputFieldINS1_9IScreenMTEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_ccutfieldpaper[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api14CCutFieldPaperENS_10shared_ptrINS1_10IFormFieldINS1_6IPaperEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cpreshownothing_iscreen[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api15CPreShowNothingINS1_7IScreenEEENS_10shared_ptrINS1_8IPreShowIS3_EEE27__shared_ptr_default_deleteIS8_S4_EENS_9allocatorIS4_EEEE");
extern const char w102_vt_ctextfieldpaper[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api15CTextFieldPaperENS_10shared_ptrINS1_10IFormFieldINS1_6IPaperEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cnumbervalidation[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api17CNumberValidationENS_10shared_ptrINS1_16IInputValidationEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_coptionvalidation[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api17COptionValidationENS_10shared_ptrINS1_16IInputValidationEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cnewlinefieldpaper[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api18CNewLineFieldPaperENS_10shared_ptrINS1_10IFormFieldINS1_6IPaperEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cpreshowclearscreen[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api19CPreShowClearScreenENS_10shared_ptrINS1_8IPreShowINS1_7IScreenEEEE27__shared_ptr_default_deleteIS7_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cqrcodeimagefieldpaper[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api22CQRCodeImageFieldPaperENS_10shared_ptrIS2_E27__shared_ptr_default_deleteIS2_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cdatatext_cescolheopcao_copcaods[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api9CDataTextIN4vota13CEscolheOpcao8COpcaoDSEEENS_10shared_ptrINS1_5ITextEE27__shared_ptr_default_deleteIS9_S6_EENS_9allocatorIS6_EEEE");
extern const char w102_vt_cpreshowformvota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota16CPreShowFormVotaENS_10shared_ptrIN3api8IPreShowINS5_7IScreenEEEE27__shared_ptr_default_deleteIS8_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_citemparametrosurnavota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota23CItemParametrosUrnaVotaENS_10shared_ptrIN5comum9CItemMenuEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_citemversoespacotesvota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota23CItemVersoesPacotesVotaENS_10shared_ptrIN5comum9CItemMenuEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_citemimprimeestadournavota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota26CItemImprimeEstadoUrnaVotaENS_10shared_ptrIN5comum9CItemMenuEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_citemvisualizarcandidatosvota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota29CItemVisualizarCandidatosVotaENS_10shared_ptrIN5comum9CItemMenuEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_citemimprimelistaeleitoresvota[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN4vota30CItemImprimeListaEleitoresVotaENS_10shared_ptrIN5comum9CItemMenuEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorbu[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum11CGravadorBUENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorlog[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorLogENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorrdv[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorRDVENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorwsq[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum12CGravadorWSQENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorhashes[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum15CGravadorHashesENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorrcsecao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum16CGravadorRCSecaoENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorenvelopearquivo[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum24CGravadorEnvelopeArquivoENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_cgravadorversoesarquivos[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum24CGravadorVersoesArquivosENS_10shared_ptrINS1_9IGravadorEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w102_vt_celeitordinamico[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md16CEleitorDinamicoENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cidentificacaosecao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md19CIdentificacaoSecaoENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_ccomparecimentomesario[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md22CComparecimentoMesarioENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cidentificacaournacontingencia[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum2md30CIdentificacaoUrnaContingenciaENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cvisitantefoto[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3asn14CVisitanteFotoENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cvisitanteeleitor[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3asn17CVisitanteEleitorENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_ijustificadordao_idao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao16IJustificadorDAOENS_10shared_ptrIN3api12persistencia4IDAOEE27__shared_ptr_default_deleteIS8_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_ijustificadordao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao16IJustificadorDAOENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_icomparecimentomesariodao_idao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao25IComparecimentoMesarioDAOENS_10shared_ptrIN3api12persistencia4IDAOEE27__shared_ptr_default_deleteIS8_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_icomparecimentomesariodao[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN5comum3dao25IComparecimentoMesarioDAOENS_10shared_ptrIS3_E27__shared_ptr_default_deleteIS3_S3_EENS_9allocatorIS3_EEEE");
extern const char w102_vt_cblockcipher_caescipher_ctrng[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN7ecourna3api8security12CBlockCipherINS3_10CAesCipherENS3_5CTrngEEENS_10shared_ptrINS3_16ISymmetricCipherEE27__shared_ptr_default_deleteISA_S7_EENS_9allocatorIS7_EEEE");
extern const char w102_vt_csha512[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN7ecourna3api8security7CSha512ENS_10shared_ptrINS3_5IHashEE27__shared_ptr_default_deleteIS7_S4_EENS_9allocatorIS4_EEEE");
extern const char w102_vt_cidentificacaojustificativa[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN7ecourna3app5dados27CIdentificacaoJustificativaENS_10shared_ptrIS4_E27__shared_ptr_default_deleteIS4_S4_EENS_9allocatorIS4_EEEE");
extern const char w102_vt_string[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_10shared_ptrIS6_E27__shared_ptr_default_deleteIS6_S6_EENS4_IS6_EEEE");
extern const char w102_vt_item_visualizar[] __asm__("_ZTVN4vota29CItemVisualizarCandidatosVotaE");
extern const char w102_vt_item_estadourna[] __asm__("_ZTVN4vota26CItemImprimeEstadoUrnaVotaE");
extern const char w102_vt_item_listaeleitores[] __asm__("_ZTVN4vota30CItemImprimeListaEleitoresVotaE");
extern const char w102_vt_item_versoespacotes[] __asm__("_ZTVN4vota23CItemVersoesPacotesVotaE");
extern const char w102_vt_item_parametrosurna[] __asm__("_ZTVN4vota23CItemParametrosUrnaVotaE");
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

using TFormPaper = api::IFormField<api::IPaper>;
using TFormScreen = api::IFormField<api::IScreen>;
using TDao = api::persistencia::IDAO;
using TAes = ecourna::api::security::CBlockCipher<ecourna::api::security::CAesCipher, ecourna::api::security::CTrng>;

template struct SBloco<TFormPaper, api::CTextFieldPaper>;
template struct SBloco<TFormPaper, api::CCutFieldPaper>;
template struct SBloco<TFormPaper, api::CNewLineFieldPaper>;
template struct SBloco<TFormScreen, api::CDSImageField>;
template struct SBloco<api::IInputValidation, api::COptionValidation>;
template struct SBloco<TDao, comum::dao::IComparecimentoMesarioDAO>;
template struct SBloco<TDao, comum::dao::IJustificadorDAO>;
template struct SBloco<comum::dao::IComparecimentoMesarioDAO, comum::dao::IComparecimentoMesarioDAO>;
template struct SBloco<comum::dao::IJustificadorDAO, comum::dao::IJustificadorDAO>;
template struct SBloco<comum::md::CIdentificacaoSecao, comum::md::CIdentificacaoSecao>;
template struct SBloco<comum::md::CIdentificacaoUrnaContingencia, comum::md::CIdentificacaoUrnaContingencia>;
template struct SBloco<comum::md::CEleitorDinamico, comum::md::CEleitorDinamico>;
using TJustificativa = ecourna::app::dados::CIdentificacaoJustificativa;
template struct SBloco<TJustificativa, TJustificativa>;
template struct SBloco<comum::asn::CVisitanteFoto, comum::asn::CVisitanteFoto>;
template struct SBloco<api::CQRCodeImageFieldPaper, api::CQRCodeImageFieldPaper>;
template struct SBloco<comum::md::CComparecimentoMesario, comum::md::CComparecimentoMesario>;
template struct SBloco<std::string, std::string>;
template struct SBloco<ecourna::api::security::ISymmetricCipher, TAes>;
template struct SBloco<comum::IGravador, comum::CGravadorWSQ>;
template struct SBloco<ecourna::api::security::IHash, ecourna::api::security::CSha512>;

__attribute__((optnone, noinline)) std::shared_ptr<api::CMovie> w102_filme(
    std::vector<api::CMovieFrame> quadros, const api::SPoint& tamanho)
{
    return std::make_shared<api::CMovie>(std::move(quadros), tamanho);
}
__attribute__((optnone, noinline)) std::shared_ptr<vota::CProgressoEncerramento> w102_progresso()
{
    return std::make_shared<vota::CProgressoEncerramento>();
}

__attribute__((optnone, noinline)) std::shared_ptr<ecourna::api::security::CTrng> w102_trng()
{
    return std::make_shared<ecourna::api::security::CTrng>();
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CProgressBar> w102_barra(
    uedword v, uedword i, uedword s, const api::SRect& r, api::TColor c0, api::TColor c1, api::TColor c2,
    api::TColor c3, const std::string& t, api::TFontSize f, uebyte m, api::TColor c4)
{
    return std::make_shared<api::CProgressBar>(v, i, s, r, c0, c1, c2, c3, t, f, m, c4);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::CMovieField> w102_campo_filme(
    const api::SPoint& p, const std::shared_ptr<api::CMovie>& filme, api::EAnchorPoint a)
{
    return std::make_shared<api::CMovieField>(p, filme, a);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::CTextFieldBlinking> w102_piscante(
    const api::SPoint& p, const api::SharedIText& t, const api::SFont& f, api::TColor c0, api::TColor c1,
    api::TColor c2)
{
    return std::make_shared<api::CTextFieldBlinking>(p, t, f, c0, c1, c2);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::CTextFieldUpdate> w102_texto_vivo(
    const api::SPoint& p, const api::SharedIText& t, const std::chrono::milliseconds& i, const api::SFont& f,
    api::TColor c0, api::TColor c1)
{
    return std::make_shared<api::CTextFieldUpdate>(p, t, i, f, c0, c1);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::CImageFieldUpdate> w102_imagem_viva(
    const api::SPoint& p, const api::SharedIImage& im, const std::chrono::milliseconds& i, api::EAnchorPoint a)
{
    return std::make_shared<api::CImageFieldUpdate>(p, im, i, a);
}
__attribute__((optnone, noinline)) std::shared_ptr<api::CWavFile> w102_wav(const api::CWavAudio& a, const void* d)
{
    return std::make_shared<api::CWavFile>(a, d);
}

using TGravador = comum::IGravador;
using TItem = comum::CItemMenu;
using TPreShow = api::IPreShow<api::IScreen>;
template struct SBloco<TGravador, comum::CGravadorBU>;
template struct SBloco<TGravador, comum::CGravadorRDV>;
template struct SBloco<TGravador, comum::CGravadorRCSecao>;
template struct SBloco<TGravador, comum::CGravadorEnvelopeArquivo>;
template struct SBloco<TGravador, comum::CGravadorHashes>;
template struct SBloco<TGravador, comum::CGravadorVersoesArquivos>;
template struct SBloco<TGravador, comum::CGravadorLog>;
template struct SBloco<TItem, vota::CItemImprimeEstadoUrnaVota>;
template struct SBloco<TItem, vota::CItemImprimeListaEleitoresVota>;
template struct SBloco<TItem, vota::CItemVersoesPacotesVota>;
template struct SBloco<TItem, vota::CItemParametrosUrnaVota>;
template struct SBloco<TItem, vota::CItemVisualizarCandidatosVota>;
template struct SBloco<TPreShow, vota::CPreShowFormVota>;
template struct SBloco<TPreShow, api::CPreShowClearScreen>;
template struct SBloco<TPreShow, api::CPreShowNothing<api::IScreen>>;
template struct SBloco<api::IInputValidation, api::CNumberValidation>;
template struct SBloco<api::IInputField<api::IScreenMT>, api::CInputFieldMT>;
template struct SBloco<comum::asn::CVisitanteEleitor, comum::asn::CVisitanteEleitor>;
template struct SBloco<api::IText, api::CDataText<vota::CEscolheOpcao::COpcaoDS>>;

__attribute__((optnone, noinline)) std::shared_ptr<api::CFixedImage> w102_imagem_fixa(const std::string& arquivo)
{
    return std::make_shared<api::CFixedImage>(arquivo);
}
__attribute__((optnone, noinline)) std::shared_ptr<vota::CPreShowProgressBar> w102_preshow()
{
    return std::make_shared<vota::CPreShowProgressBar>();
}
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
using THorizontal = api::BatteryIconDataSource<api::CPowerInformation::IconOrientation::Horizontal>;
__attribute__((optnone, noinline)) std::shared_ptr<THorizontal> w102_bateria()
{
    return std::make_shared<THorizontal>();
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
        w102_sink = w102_vt_cfixedimage;
        w102_sink = w102_vt_cmoviefield;
        w102_sink = w102_vt_cprogressbar;
        w102_sink = w102_vt_ctextfieldupdate;
        w102_sink = w102_vt_cimagefieldupdate;
        w102_sink = w102_vt_ctextfieldblinking;
        w102_sink = w102_vt_batteryicondatasource_cpowerinformation_iconorientation_0;
        w102_sink = w102_vt_cmovie;
        w102_sink = w102_vt_logger;
        w102_sink = w102_vt_cwavfile;
        w102_sink = w102_vt_cdatatext_crespostasdsnumero;
        w102_sink = w102_vt_cdatatext_ccandidaturasdsnome;
        w102_sink = w102_vt_cdatatext_ccandidaturasdsnumero;
        w102_sink = w102_vt_cdatatext_ccargodsnomesexocandidato;
        w102_sink = w102_vt_cpreshowprogressbar;
        w102_sink = w102_vt_cprogressoencerramento;
        w102_sink = w102_vt_ccopiadormr;
        w102_sink = w102_vt_ccopiadorwsqmr;
        w102_sink = w102_vt_ctrng;
        w102_sink = w102_vt_cdsimagefield;
        w102_sink = w102_vt_cinputfieldmt;
        w102_sink = w102_vt_ccutfieldpaper;
        w102_sink = w102_vt_cpreshownothing_iscreen;
        w102_sink = w102_vt_ctextfieldpaper;
        w102_sink = w102_vt_cnumbervalidation;
        w102_sink = w102_vt_coptionvalidation;
        w102_sink = w102_vt_cnewlinefieldpaper;
        w102_sink = w102_vt_cpreshowclearscreen;
        w102_sink = w102_vt_cqrcodeimagefieldpaper;
        w102_sink = w102_vt_cdatatext_cescolheopcao_copcaods;
        w102_sink = w102_vt_cpreshowformvota;
        w102_sink = w102_vt_citemparametrosurnavota;
        w102_sink = w102_vt_citemversoespacotesvota;
        w102_sink = w102_vt_citemimprimeestadournavota;
        w102_sink = w102_vt_citemvisualizarcandidatosvota;
        w102_sink = w102_vt_citemimprimelistaeleitoresvota;
        w102_sink = w102_vt_cgravadorbu;
        w102_sink = w102_vt_cgravadorlog;
        w102_sink = w102_vt_cgravadorrdv;
        w102_sink = w102_vt_cgravadorwsq;
        w102_sink = w102_vt_cgravadorhashes;
        w102_sink = w102_vt_cgravadorrcsecao;
        w102_sink = w102_vt_cgravadorenvelopearquivo;
        w102_sink = w102_vt_cgravadorversoesarquivos;
        w102_sink = w102_vt_celeitordinamico;
        w102_sink = w102_vt_cidentificacaosecao;
        w102_sink = w102_vt_ccomparecimentomesario;
        w102_sink = w102_vt_cidentificacaournacontingencia;
        w102_sink = w102_vt_cvisitantefoto;
        w102_sink = w102_vt_cvisitanteeleitor;
        w102_sink = w102_vt_ijustificadordao_idao;
        w102_sink = w102_vt_ijustificadordao;
        w102_sink = w102_vt_icomparecimentomesariodao_idao;
        w102_sink = w102_vt_icomparecimentomesariodao;
        w102_sink = w102_vt_cblockcipher_caescipher_ctrng;
        w102_sink = w102_vt_csha512;
        w102_sink = w102_vt_cidentificacaojustificativa;
        w102_sink = w102_vt_string;
        w102_sink = w102_vt_item_visualizar;
        w102_sink = w102_vt_item_estadourna;
        w102_sink = w102_vt_item_listaeleitores;
        w102_sink = w102_vt_item_versoespacotes;
        w102_sink = w102_vt_item_parametrosurna;
    }
} w102_roots;

} // namespace
