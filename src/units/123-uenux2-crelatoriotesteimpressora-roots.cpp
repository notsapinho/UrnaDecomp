// Roots: keep comum::CRelatorioTesteImpressora's callees in the skeleton link the way the target keeps them. The class's
// vtable is kept by its constructor (fn 5586, crelatoriotesteimpressora.cpp), which stores the vptr and which unit 280's
// roots reach for its caller 11869 (11911, unit 296's, is in the link).
// - GetCorrespondencia (slot 9, fn 11197) calls CDadoCorrespondencia's copy constructor, fn 1249, which has six callers
//   in the target (awk -F'\t' '$2==1249' ledger/callgraph.tsv: 5637, 5740, 5856, 11197, 11395, 12098). 5856 (unit 160)
//   and 11395 (comum::asn::CConversorEstadoGeralGap::DoDesconverte, unit 93, three call sites) are in the link, and
//   11395 reads the copy's result as the target's does, and 5740 (unit 89's, the general state's copy) is in the link
//   too; 5637 and 12098 still wait. The stand-in that stood for
//   them went before they landed, on a link without it that moves no row: 11197 and 5856 keep `match`.
// - InicializaTradutorFrase (slot 10, fn 11196) hands its map to comum::md::CTradutorFrase::SetLabels, inline, which
//   calls the tree's __assign_multi, fn 5794, with the static map's address. 5794 has two callers in the target
//   (awk -F'\t' '$2==5794' ledger/callgraph.tsv: 7787, 11196); w123_labels stands for 7787, not reconstructed, so that
//   it keeps two call sites here, as src/units/README.md "Companion files" asks. It goes when 7787 lands.
// - The map InicializaTradutorFrase builds comes from std::map<char, ecourna::app::dados::CLabelParametrizado>'s
//   initializer-list constructor, fn 5795, which this unit's crelatoriotesteimpressora.cpp.o instantiates. 5795 has
//   two callers in the target (awk -F'\t' '$2==5795' ledger/callgraph.tsv: 7787, 11196), and with 11196 alone
//   binaryen inlines it there. w123_mapa stands for 7787: it calls that object's constructor through an __asm__ label
//   with the object's signature (a constructor returns this; the list comes by address, the comparator by reference),
//   so this file instantiates no copy of it, and reads the result, as the target's wasm type keeps it. It goes when
//   7787 lands.
// - GetSeparadorFase (slot 20, fn 11183) calls CRelUtil::GetSeparadorFase, fn 1919, which has six callers in the target
//   (awk -F'\t' '$2==1919' ledger/callgraph.tsv: 2785, 11183, 11943, 11946, 12105, 12110). w123_separador stands for the
//   four not reconstructed (11943, 11946, 12105, 12110; 2785 and 11183 are in the link).
// - 1919 throws CUeComumRelatoriosError, whose constructor is fn 580, a thunk of binaryen's 710 with 14 callers in the
//   target (awk -F'\t' '$2==580' ledger/callgraph.tsv); with one caller binaryen inlines the constructor into it, as it
//   did into 1919 alone. w123_erro stands for four of the other 13 (11968, 12110, 2791, 5967; 11181, 11212,
//   11214, 3696, 942, 2786, 3689, 1543 and 11233 are in the link). It passes an empty std::source_location: a default
//   argument would make a record on this line, which is none of the target's.
// - CRelUtil::GetIDCargaFormatado, fn 2786, has four callers in the target (awk -F'\t' '$2==2786' ledger/callgraph.tsv:
//   5579, 11256, 12105, 12110): 11256 is in the link, and w123_idcarga stands for the other three and calls it twice.
// - CRelUtil::IncluiCabecalhoEleicoesMZS, fn 1543, has six callers in the target (awk -F'\t' '$2==1543'
//   ledger/callgraph.tsv: 5977, 11223, 11902, 11908, 12105, 12110); 11902 (unit 176's), 11223 (unit 287's) and 11908
//   (unit 176's) are in the link, with one call each, and w123_cabecalho stands for the other three and calls it twice,
//   with the header types and the flag varied as those callers vary them (0 or 2 and 1, 11223 and 11902; 0 and 0, 5977,
//   11908, 12110; 0 or 1 and 0, 12105), so that dead-argument elimination folds none.
// - CRelUtil::ImprimeResumoCorrespondencia, fn 1541, has the same six callers as 1543 (awk -F'\t' '$2==1541'
//   ledger/callgraph.tsv), and CRelUtil::ImprimeSeparadorFase, fn 2785, four of them (11223, 11902, 11908, 12105);
//   11902, 11223 and 11908 are in the link, and w123_rodape stands for the others (5977, 12105 and 12110 for 1541,
//   12105 for 2785) and calls each twice.
// - CRelUtil::FormTituloPartido, which the target holds inlined by binaryen in fn 11946 (vota::CGeraZeresimaBase's slot
//   2, not reconstructed), takes the address of crelutil.cpp's internal TituloPartido (fn 11181, table slot 3050, which
//   only 11946 passes): w123_titulo stands for 11946 and calls it once, so binaryen inlines it here as there, and 11181
//   is reached as the target reaches it. It goes when 11946 lands.
// - CRelUtil::ImprimeSeparadorVia, fn 5581, has one caller in the target, fn 12110 (vota::CGeraBU's slot 2, not
//   reconstructed), which calls it twice (awk -F'\t' '$2==5581' ledger/callgraph.tsv): w123_vias stands for it with
//   two call sites, so binaryen keeps 5581 out of line. 12110 passes no constant (the same builder at both calls, a
//   counter plus one and a total), and w123_vias passes different ones where it passes constants, so that
//   dead-argument elimination folds none. It goes when 12110 lands.
#include <source_location>
#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

extern "C" {
int w123_construtor(void* mapa, const void* lista, const void* comparador) __asm__(
    "_ZNSt3__23mapIcN7ecourna3app5dados19CLabelParametrizadoENS_4lessIcEENS_9allocatorINS_4pairIKcS4_EEEEEC2B8ne210108ESt16"
    "initializer_listISA_ERKS6_");
}

namespace {

__attribute__((noinline)) unsigned w123_labels(const std::map<char, ecourna::app::dados::CLabelParametrizado>& labels)
{
    comum::md::CTradutorFrase::SetLabels(labels);
    return labels.size() + 123;
}

// stands for fn 7787
__attribute__((noinline)) int w123_mapa(void* mapa, const void* lista, const void* comparador)
{
    return w123_construtor(mapa, lista, comparador) + 123;
}

__attribute__((noinline)) unsigned w123_separador(comum::EUrnaFase fase)
{
    return comum::CRelUtil::GetSeparadorFase(fase).size() + 123;
}

__attribute__((noinline)) void w123_erro(int codigo, const std::string& mensagem)
{
    throw comum::CUeComumRelatoriosError(static_cast<comum::EUeComumRelatoriosError>(codigo + 123), mensagem + "w123",
                                         std::source_location());
}

__attribute__((noinline)) unsigned w123_idcarga(const std::string& carga, const std::string& outra)
{
    return comum::CRelUtil::GetIDCargaFormatado(carga).size() + comum::CRelUtil::GetIDCargaFormatado(outra).size() + 123;
}

__attribute__((noinline)) void w123_cabecalho(api::CPaperFormBuilder& builder, const std::string& titulo,
                                              const std::string& municipio, unsigned tipo)
{
    comum::CRelUtil::IncluiCabecalhoEleicoesMZS(builder, titulo, tipo + 123, tipo, tipo + 7, municipio,
                                                static_cast<comum::CRelUtil::ETipoCabecalho>(tipo), tipo > 1);
    comum::CRelUtil::IncluiCabecalhoEleicoesMZS(builder, municipio, 123, 7, tipo, titulo,
                                                comum::CRelUtil::eCabecalhoSecao, false);
}

__attribute__((noinline)) void w123_rodape(api::CPaperFormBuilder& builder, api::CPaperFormBuilder& outro,
                                           const comum::md::estadoaplicacao::CDadoCorrespondencia& correspondencia,
                                           comum::EUrnaFase fase)
{
    comum::CRelUtil::ImprimeResumoCorrespondencia(builder, correspondencia);
    comum::CRelUtil::ImprimeSeparadorFase(builder, fase);
    comum::CRelUtil::ImprimeResumoCorrespondencia(outro, correspondencia);
    comum::CRelUtil::ImprimeSeparadorFase(outro, comum::FASE_OFICIAL);
}

__attribute__((noinline)) unsigned w123_titulo(unsigned base)
{
    return comum::CRelUtil::FormTituloPartido() ? base + 123 : base;
}

__attribute__((noinline)) void w123_vias(api::CPaperFormBuilder& builder, api::CPaperFormBuilder& outro, unsigned total)
{
    comum::CRelUtil::ImprimeSeparadorVia(builder, 1, total);
    comum::CRelUtil::ImprimeSeparadorVia(outro, 3, total + 5);
}

unsigned (*volatile w123_sink_labels)(const std::map<char, ecourna::app::dados::CLabelParametrizado>&);
int (*volatile w123_sink_mapa)(void*, const void*, const void*);
unsigned (*volatile w123_sink_separador)(comum::EUrnaFase);
void (*volatile w123_sink_erro)(int, const std::string&);
unsigned (*volatile w123_sink_idcarga)(const std::string&, const std::string&);
void (*volatile w123_sink_cabecalho)(api::CPaperFormBuilder&, const std::string&, const std::string&, unsigned);
void (*volatile w123_sink_rodape)(api::CPaperFormBuilder&, api::CPaperFormBuilder&,
                                  const comum::md::estadoaplicacao::CDadoCorrespondencia&, comum::EUrnaFase);
unsigned (*volatile w123_sink_titulo)(unsigned);
void (*volatile w123_sink_vias)(api::CPaperFormBuilder&, api::CPaperFormBuilder&, unsigned);

struct SRelatorioTesteImpressoraRoots {
    SRelatorioTesteImpressoraRoots()
    {
        w123_sink_labels = w123_labels;
        w123_sink_mapa = w123_mapa;
        w123_sink_separador = w123_separador;
        w123_sink_erro = w123_erro;
        w123_sink_idcarga = w123_idcarga;
        w123_sink_cabecalho = w123_cabecalho;
        w123_sink_rodape = w123_rodape;
        w123_sink_titulo = w123_titulo;
        w123_sink_vias = w123_vias;
    }
} relatoriotesteimpressora_roots;

} // namespace
