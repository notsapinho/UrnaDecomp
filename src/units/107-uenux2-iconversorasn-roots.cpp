// Roots: reach comum::asn::IConversorASN<ENTIDADE, DADO>'s Converte and Desconverte (app/comum/asn/iconversorasn.h) the
// way the target's callers do, until they land. Each instance here has direct callers only, at least two call sites in
// the target (ledger/callgraph.tsv), and binaryen keeps it out of line for that, and merges those of one shape into
// fns 1563 and 1008, with the record and the entity's typeid text as parameters. w107_converte and w107_desconverte
// call an instance twice, so each has two call sites, and the stand-in w107_todos, which holds them all, has a body no
// target function has.
//
// The objects are built in place, by guaranteed elision, so this TU calls no constructor or destructor of an entity or
// a data class: those are the ASN.1 runtime's and the units', and an instance here would be a copy ahead of them.
// The callers each instance stands for:
//   3726: 11390, 11394. 3727: 11391, 11395. 3730: 10270, 11411. 3736: 11424, 11451.
//   3737: 11423, 11452 (11381 is written). 3738: 10270, 11411 (11457 is written). 3799: 10271, 10273, 11587.
//   2275: 10266, 10271, 10273, 11587 (11458 is written). 5684: 11363. 5686: 11363. 5688: 11375 (11359 is written).
//   5691: 11394 (11397 is written). 5692: 11395, 11398. 5696: 11399 (11403 is written). 5697: 11400 (11404 is written).
//   5705: 5706, 11423. 5711: 11448. 5713, 5714: 11424, 11451. 5715, 5716: 11423, 11452.
//   5828: 11373, 11445.
// w107_dados gives a constructor its second call site, each stands for: 3712 11424 and 11451, 5672 5741, 3823 2725 and
// 11629. 5632 has one direct caller (11404) and a table slot (448), which 10205 passes to invoke_iiiii: its address is
// the reference the target has.
//
// The vtables are what the target keeps the converters by: slots 2 and 3, no direct caller. Every converter's data is
// reached that way, so the sink is the reference the target has.
//
// comum::md::CUrna has a forward declaration only: Converte takes it by reference.
#include <new>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.h"
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "app/comum/dados/md/municipiozona/ccomplementomunicipio.h"
#include "app/comum/dados/md/municipiozona/cmunicipio.h"
#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"
#include "app/comum/dados/md/processoeleitoral/cpleitodto.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/ccabecalhopacote.h"
#include "app/comum/md/cseguranca.h"
#include "asn1/modules/ModuloCandidatos.h"
#include "asn1/modules/ModuloComplementosMunicipios.h"
#include "asn1/modules/ModuloEleicao.h"
#include "asn1/modules/ModuloEstadoGeralDefs.h"
#include "asn1/modules/ModuloEstadoGeralUrna.h"
#include "asn1/modules/ModuloLocal.h"
#include "asn1/modules/ModuloProcessoEleitoral.h"
#include "asn1/modules/ModuloTiposCadastro.h"
#include "asn1/modules/ModuloTiposEleitorais.h"
#include "asn1/modules/ModuloTiposResultadosEcoUrna.h"

extern "C" {
int w3712(void*, unsigned, const void*, int) __asm__("_ZN5comum2md10CMunicipioC1EjRKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEb");
int w5672(void*, int, int) __asm__("_ZN5comum2md22CIdentificacaoAgregadaC1EtNS_17ETipoLocalVotacaoE");
int w3823(void*, int, int, const void*) __asm__("_ZN5comum2md10CSegurancaC1EhhRKNSt3__26vectorIhNS2_9allocatorIhEEEE");
int w5632(void*, void*, const void*, int) __asm__("_ZN5comum2md15estadoaplicacao10CDadoLocalC1ENSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEERKNS1_20CLocalidadeEleitoralENS_17ETipoLocalVotacaoE");
extern const char w107_municipio_vt[] __asm__("_ZTVN5comum3asn19CConversorMunicipioE");
extern const char w107_agregada_vt[] __asm__("_ZTVN5comum3asn31CConversorIdentificacaoAgregadaE");
extern const char w107_complemento_vt[] __asm__("_ZTVN5comum3asn30CConversorComplementoMunicipioE");
extern const char w107_seguranca_vt[] __asm__("_ZTVN5comum3asn19CConversorSegurancaE");
extern const char w107_abrangencia_vt[] __asm__("_ZTVN5comum3asn21CConversorAbrangenciaE");
extern const char w107_dadolocal_vt[] __asm__("_ZTVN5comum3asn19CConversorDadoLocalE");
extern const char w107_dadocarga_vt[] __asm__("_ZTVN5comum3asn19CConversorDadoCargaE");
}

namespace comum::md {
class CUrna;
}

namespace {

template <typename ENTIDADE, typename DADO>
inline char* w107_converte(char* destino, const char* entrada)
{
    const auto& conversor = *reinterpret_cast<const comum::asn::IConversorASN<ENTIDADE, DADO>*>(entrada);
    const auto& dado = *reinterpret_cast<const DADO*>(entrada + 8);
    ::new (destino) ENTIDADE(conversor.Converte(dado));
    ::new (destino + 256) ENTIDADE(conversor.Converte(dado));
    return destino + 512;
}

template <typename ENTIDADE, typename DADO>
inline char* w107_desconverte(char* destino, const char* entrada)
{
    const auto& conversor = *reinterpret_cast<const comum::asn::IConversorASN<ENTIDADE, DADO>*>(entrada);
    const auto& entidade = *reinterpret_cast<const ENTIDADE*>(entrada + 8);
    ::new (destino) DADO(conversor.Desconverte(entidade));
    ::new (destino + 256) DADO(conversor.Desconverte(entidade));
    return destino + 512;
}

__attribute__((noinline)) char* w107_todos(char* d, const char* e)
{
    using namespace comum::md;
    using namespace comum::md::estadoaplicacao;
    d = w107_desconverte<ModuloEstadoGeralDefs::NumViasImpressasRelatorios, CNumViasImpressasRelatorios>(d, e);
    d = w107_desconverte<ModuloComplementosMunicipios::ComplementoMunicipio, CComplementoMunicipio>(d, e);
    d = w107_desconverte<ModuloEleicao::NomesCargo, CNomesCargo>(d, e);
    d = w107_desconverte<ModuloEstadoGeralUrna::DadoCorrespondencia, CDadoCorrespondencia>(d, e);
    d = w107_desconverte<ModuloEstadoGeralUrna::DadoSecao, CLocalidadeEleitoral>(d, e);
    d = w107_desconverte<ModuloCandidatos::DadosCandidato, CDadosCandidato>(d, e);
    d = w107_desconverte<ModuloLocal::SecaoEleitoral, CSecaoEleitoral>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::Seguranca, CSeguranca>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::CabecalhoEntidade, CCabecalhoEntidade>(d, e);
    d = w107_desconverte<ModuloProcessoEleitoral::Pleito, CPleitoDTO>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::CabecalhoPacote, CCabecalhoPacote>(d, e);
    d = w107_desconverte<ModuloTiposCadastro::Municipio, CMunicipio>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::TipoIdentificadorEleitor, ecourna::app::dados::ETipoIdentificadorEleitor>(d, e);
    d = w107_converte<ModuloEstadoGeralDefs::NumViasImpressasRelatorios, CNumViasImpressasRelatorios>(d, e);
    d = w107_converte<ModuloComplementosMunicipios::ComplementoMunicipio, CComplementoMunicipio>(d, e);
    d = w107_converte<ModuloEstadoGeralUrna::DadoCorrespondencia, CDadoCorrespondencia>(d, e);
    d = w107_converte<ModuloEstadoGeralUrna::DadoSecao, CLocalidadeEleitoral>(d, e);
    d = w107_converte<ModuloLocal::SecaoEleitoral, CSecaoEleitoral>(d, e);
    d = w107_converte<ModuloTiposEleitorais::CabecalhoEntidade, CCabecalhoEntidade>(d, e);
    d = w107_converte<ModuloTiposResultadosEcoUrna::Urna, CUrna>(d, e);
    d = w107_converte<ModuloTiposCadastro::Municipio, CMunicipio>(d, e);
    return d;
}

__attribute__((noinline)) int w107_dados(char* d, int a, int b, const char* e)
{
    return w3712(d, a, e, b) + w5672(d + 32, a + 1, b + 2) + w3823(d + 64, b, a, e + 16);
}

char* (*volatile w107_sink)(char*, const char*);
int (*volatile w107_sink_dados)(char*, int, int, const char*);
const void* volatile w107_sink_vt;

struct SIConversorRoots {
    SIConversorRoots()
    {
        w107_sink = &w107_todos;
        w107_sink_dados = &w107_dados;
        w107_sink_vt = reinterpret_cast<const void*>(&w5632);
        w107_sink_vt = w107_municipio_vt;
        w107_sink_vt = w107_agregada_vt;
        w107_sink_vt = w107_complemento_vt;
        w107_sink_vt = w107_seguranca_vt;
        w107_sink_vt = w107_abrangencia_vt;
        w107_sink_vt = w107_dadolocal_vt;
        w107_sink_vt = w107_dadocarga_vt;
    }
} w107_roots;

} // namespace
