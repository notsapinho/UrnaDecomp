// Stand-ins for the target callers of unit 280's functions that are not reconstructed yet (the fragment's header has
// the evidence). Each stand-in's comment names the target callers it stands for; it goes when they are all in the link.
// The libc++ instances are called through __asm__ labels with the objects' signatures (wasm-objdump -x), so this TU
// instantiates none of them.
#include <filesystem>
#include <new>
#include <string>
#include <vector>

#include "api/util/csystem.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/carregaprocessoeleitoral.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/nomearquivo/cnomearquivo.h"
#include "app/comum/relatorios/crelatoriotesteimpressora.h"
#include "ecourna/app/dados/asn/midias/cconversorinformacaomidia.hpp"

extern "C" {
// std::vector<comum::md::CEleicaoPE>::push_back(const CEleicaoPE&), carregaprocessoeleitoral.cpp.o's copy
void w280_push_back(void* eleicoes, const void* eleicao) __asm__(
    "_ZNSt3__26vectorIN5comum2md10CEleicaoPEENS_9allocatorIS3_EEE9push_backB8ne210108ERKS3_");
// std::map<unsigned int, std::string>'s __tree::__find_equal<unsigned int>(hint, parent, dummy, key), cpe.cpp.o's copy
int w280_find_equal(void* arvore, void* dica, void** pai, void** vazio, const unsigned* chave) __asm__(
    "_ZNSt3__26__treeINS_12__value_typeIjNS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEEENS_19__map_value_"
    "compareIjNS_4pairIKjS7_EENS_4lessIjEELb1EEENS5_ISC_EEE12__find_equalIjEERPNS_16__tree_node_baseIPvEENS_21__tree_"
    "const_iteratorIS8_PNS_11__tree_nodeIS8_SK_EElEERPNS_15__tree_end_nodeISM_EESN_RKT_");
}

namespace {

// stands for fn 11869 (vota::CVerificaHorarioZeresima's slot 7), one of the two callers of CRelatorioTesteImpressora's
// constructor (fn 5586), which read its returned this, as this one does; the other, fn 11911
// (vota::CImpressaoEstadoUrna's slot 2), is in the link
__attribute__((noinline)) bool w280_relatorio(void* primeiro, void* segundo, int vias)
{
    const comum::CRelatorioTesteImpressora* a = ::new (primeiro) comum::CRelatorioTesteImpressora();
    const comum::CRelatorioTesteImpressora* b = ::new (segundo) comum::CRelatorioTesteImpressora();
    return a->TemQRCode() && b->TemQRCode() && vias > 280;
}

// stands for fn 7787, the other caller of CarregaProcessoEleitoral (fn 3771)
__attribute__((noinline)) unsigned w280_processo(const comum::md::estadoaplicacao::CEstadoGeral& geral)
{
    return comum::CarregaProcessoEleitoral(geral, comum::FLASH_INTERNA).GetID() + 280;
}

// stands for fn 7787, the other caller of SIdentificacaoArquivo's constructor (fn 5726), which reads its returned this
__attribute__((noinline)) comum::SIdentificacaoArquivo* w280_identificacao(void* destino, comum::EUrnaFase fase,
    uedword id, const std::string& uf, const comum::md::CPleito& pleito)
{
    return ::new (destino) comum::SIdentificacaoArquivo(fase, id + 280, uf, pleito);
}

// stands for fns 5967 and 7787, the callers of CPleito's copy constructor (fn 1281) not in the link that read its
// returned this (1543 and 11902, which read it too, are in the link; 2787 and 3771 drop it)
__attribute__((noinline)) std::size_t w280_copia(void* destino, const comum::md::CPleito& pleito)
{
    return (::new (destino) comum::md::CPleito(pleito))->GetEleicoes().size() + 280;
}

// stands for fn 7787, the other caller of CarregaArquivo<CConversorCabecalhoPacote> (fn 5706)
__attribute__((noinline)) std::size_t w280_cabecalho(const std::string& arquivo)
{
    return comum::CarregaArquivo<comum::asn::CConversorCabecalhoPacote>(arquivo).GetVersao().size() + 280;
}

// stands for fn 11629 (comum::CGravadorBU::GravaResultado), the caller of CarregaArquivoEcourna<CConversorInformacaoMidia>
// (fn 3735) besides 11587 (unit 305's) and 11626 (unit 160's)
__attribute__((noinline)) std::size_t w280_informacao(const std::string& arquivo)
{
    return comum::CarregaArquivoEcourna<ecourna::app::dados::asn::CConversorInformacaoMidia>(arquivo).GetUF().size() +
        280;
}

// stands for fn 7787, the other caller of api::TrocaExtensao (fn 5461)
__attribute__((noinline)) std::size_t w280_extensao(const std::string& arquivo)
{
    return api::TrocaExtensao(arquivo, "w280").size() + 280;
}

// stands for fn 3713, the other caller of CPleito's constructor (fn 5652)
__attribute__((noinline)) void w280_pleito(void* destino, const comum::md::TVectorEleicaoPE& eleicoes,
    const comum::md::TMapVersaoPacoteEleicao& versoes, const std::vector<comum::md::CSituacoesEleicoes>& situacoes,
    const std::string& nome, const api::CDate& data)
{
    ::new (destino) comum::md::CPleito(280, nome, data, eleicoes, versoes, situacoes);
}

// stands for fn 5649, the other caller of std::vector<CEleicaoPE>::push_back (fn 5777)
__attribute__((noinline)) std::size_t w280_eleicoes(comum::md::TVectorEleicaoPE& eleicoes, const comum::md::CEleicaoPE& eleicao)
{
    w280_push_back(&eleicoes, &eleicao);
    return eleicoes.size() + 280;
}

// stands for fns 5808 and 11349, the other callers of the version map's __find_equal (fn 3869; 3870 is in the link)
__attribute__((noinline)) int w280_busca(comum::md::TMapVersaoPacoteEleicao& versoes, unsigned chave)
{
    void* pai = nullptr;
    void* vazio = nullptr;
    return w280_find_equal(&versoes, nullptr, &pai, &vazio, &chave) + 280;
}

// stands for fn 4160, the other caller of CLocal::GetAgregadas (fn 3752; 5738 and 11242, unit 155's, are in the link)
__attribute__((noinline)) std::size_t w280_agregadas(const comum::CLocal& local)
{
    return local.GetAgregadas().size() + 280;
}

bool (*volatile w280_sink_relatorio)(void*, void*, int);
unsigned (*volatile w280_sink_processo)(const comum::md::estadoaplicacao::CEstadoGeral&);
comum::SIdentificacaoArquivo* (*volatile w280_sink_identificacao)(void*, comum::EUrnaFase, uedword, const std::string&,
    const comum::md::CPleito&);
std::size_t (*volatile w280_sink_copia)(void*, const comum::md::CPleito&);
std::size_t (*volatile w280_sink_cabecalho)(const std::string&);
std::size_t (*volatile w280_sink_informacao)(const std::string&);
std::size_t (*volatile w280_sink_extensao)(const std::string&);
void (*volatile w280_sink_pleito)(void*, const comum::md::TVectorEleicaoPE&, const comum::md::TMapVersaoPacoteEleicao&,
    const std::vector<comum::md::CSituacoesEleicoes>&, const std::string&, const api::CDate&);
std::size_t (*volatile w280_sink_eleicoes)(comum::md::TVectorEleicaoPE&, const comum::md::CEleicaoPE&);
int (*volatile w280_sink_busca)(comum::md::TMapVersaoPacoteEleicao&, unsigned);
std::size_t (*volatile w280_sink_agregadas)(const comum::CLocal&);

struct SProcessoEleitoralRoots {
    SProcessoEleitoralRoots()
    {
        w280_sink_relatorio = w280_relatorio;
        w280_sink_processo = w280_processo;
        w280_sink_identificacao = w280_identificacao;
        w280_sink_copia = w280_copia;
        w280_sink_cabecalho = w280_cabecalho;
        w280_sink_informacao = w280_informacao;
        w280_sink_extensao = w280_extensao;
        w280_sink_pleito = w280_pleito;
        w280_sink_eleicoes = w280_eleicoes;
        w280_sink_busca = w280_busca;
        w280_sink_agregadas = w280_agregadas;
    }
} processoeleitoral_roots;

} // namespace
