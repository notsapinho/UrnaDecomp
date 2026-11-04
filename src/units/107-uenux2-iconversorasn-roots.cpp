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
//   3730: 11411 (10270 is written). 3726, 3727 and 3736 need none: their callers 11390 and 11394, 11391 and 11395, and
//   11424 and 11451, are written.
//   3737 needs none: its callers 11381, 11423 and 11452 are written. 3738: 11411 (10270, 11457). 3799: 10273 (10271, 11587).
//   2275: 10266, 10273 (10271, 11458, 11587). 5688 needs none: its callers 11359 and 11375 are written.
//   5692: 11398 (11395 is written). 5691, 5696 and 5697 need none: their callers 11394 and 11397, 11399 and 11403, and
//   11400 and 11404, are written.
//   5711: 11448. 5705, 5713 and 5714 need none: their callers 5706 and 11423, and 11424 and 11451, are written.
//   5715 and 5716 need none: their callers 11423 and 11452 are written.
//   5828: 11445 (11373 is written).
// w107_dados gives a constructor its second call site, and stands for: 3823 11629 (2725, unit 293's, is in the link). 5672's call went: its callers
// 5741 and 11455 are written. 3712 needs none:
// its callers 11378, 11424 and 11451 are written. 5632 has one direct caller (11404) and a table slot (448), which 10205 passes to invoke_iiiii: its address is
// the reference the target has.
//
// The vtables are what the target keeps the converters by: slots 2 and 3, no direct caller. Every converter's data is
// reached that way, so the sink is the reference the target has.
//
// comum::md::CUrna has a forward declaration only: Converte takes it by reference.
#include <new>

#include "app/comum/asn/iconversorasn.h"
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "app/comum/dados/md/municipiozona/ccomplementomunicipio.h"
#include "app/comum/dados/md/municipiozona/cmunicipio.h"
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
    d = w107_desconverte<ModuloEstadoGeralUrna::DadoCorrespondencia, CDadoCorrespondencia>(d, e);
    d = w107_desconverte<ModuloCandidatos::DadosCandidato, CDadosCandidato>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::Seguranca, CSeguranca>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::CabecalhoEntidade, CCabecalhoEntidade>(d, e);
    d = w107_desconverte<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char>(d, e);
    d = w107_converte<ModuloTiposEleitorais::CabecalhoEntidade, CCabecalhoEntidade>(d, e);
    d = w107_converte<ModuloTiposResultadosEcoUrna::Urna, CUrna>(d, e);
    return d;
}

__attribute__((noinline)) int w107_dados(char* d, int a, int b, const char* e)
{
    return w3823(d + 64, b, a, e + 16);
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
