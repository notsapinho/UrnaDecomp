// Roots: keep comum::CRelatorioTesteImpressora in the skeleton link the way the target keeps it.
// - Its one user is its constructor (fn 5586, not reconstructed), which stores the vptr (@1576660, vtable @1576652) into
//   an object of the frames of fns 11869 (vota::CVerificaHorarioZeresima's slot 7) and 11911 (vota::CImpressaoEstadoUrna's
//   slot 2), which hand it to fn 5591; 5591 reaches every member through the vtable, slots 2 to 25. Taking the vtable's
//   address keeps the same set: every slot in the table and none called directly.
// - GetCorrespondencia (slot 9, fn 11197) calls CDadoCorrespondencia's copy constructor, fn 1249, which has six callers
//   in the target (awk -F'\t' '$2==1249' ledger/callgraph.tsv: 5637, 5740, 5856, 11197, 11395, 12098). 11395
//   (comum::asn::CConversorEstadoGeralGap::DoDesconverte, unit 93) is in the link, with three call sites, and reads the
//   copy's result as the target's does, so no stand-in is needed for it.
// - InicializaTradutorFrase (slot 10, fn 11196) hands its map to comum::md::CTradutorFrase::SetLabels, inline, which
//   calls the tree's __assign_multi, fn 5794, with the static map's address. 5794 has two callers in the target
//   (awk -F'\t' '$2==5794' ledger/callgraph.tsv: 7787, 11196); w123_labels stands for 7787, not reconstructed, so that
//   it keeps two call sites here, as src/units/README.md "Companion files" asks. It goes when 7787 lands.
// - GetSeparadorFase (slot 20, fn 11183) calls CRelUtil::GetSeparadorFase, fn 1919, which has six callers in the target
//   (awk -F'\t' '$2==1919' ledger/callgraph.tsv: 2785, 11183, 11943, 11946, 12105, 12110). w123_separador stands for the
//   five not reconstructed: with one caller binaryen inlines 1919 into 11183.
// - 1919 throws CUeComumRelatoriosError, whose constructor is fn 580, a thunk of binaryen's 710 with 14 callers in the
//   target (awk -F'\t' '$2==580' ledger/callgraph.tsv); with one caller binaryen inlines the constructor into it, as it
//   did into 1919 alone. w123_erro stands for nine of the other 13 (11181, 11212, 11233, 11968, 12110, 1543,
//   2791, 3689, 5967; 11214, 3696, 942 and 2786 are in the link). It passes an empty std::source_location: a default
//   argument would make a record on this line, which is none of the target's.
// - CRelUtil::GetIDCargaFormatado, fn 2786, has four callers in the target (awk -F'\t' '$2==2786' ledger/callgraph.tsv:
//   5579, 11256, 12105, 12110), none reconstructed: w123_idcarga stands for them and calls it twice, or binaryen would
//   inline it into its one caller.
// - CRelUtil::IncluiAvisoModoDemonstracao, fn 5583, has two (awk -F'\t' '$2==5583' ledger/callgraph.tsv: 1543, 5591),
//   neither reconstructed: w123_demonstracao stands for both and calls it twice.
#include <source_location>
#include <string>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

extern "C" {
extern const char relatoriotesteimpressora_vt[] __asm__("_ZTVN5comum25CRelatorioTesteImpressoraE");
}

namespace {

__attribute__((noinline)) unsigned w123_labels(const std::map<char, ecourna::app::dados::CLabelParametrizado>& labels)
{
    comum::md::CTradutorFrase::SetLabels(labels);
    return labels.size() + 123;
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

__attribute__((noinline)) void w123_demonstracao(api::CPaperFormBuilder& builder, api::CPaperFormBuilder& outro)
{
    comum::CRelUtil::IncluiAvisoModoDemonstracao(builder);
    comum::CRelUtil::IncluiAvisoModoDemonstracao(outro);
}

const void* volatile relatoriotesteimpressora_sink;
unsigned (*volatile w123_sink_labels)(const std::map<char, ecourna::app::dados::CLabelParametrizado>&);
unsigned (*volatile w123_sink_separador)(comum::EUrnaFase);
void (*volatile w123_sink_erro)(int, const std::string&);
unsigned (*volatile w123_sink_idcarga)(const std::string&, const std::string&);
void (*volatile w123_sink_demonstracao)(api::CPaperFormBuilder&, api::CPaperFormBuilder&);

struct SRelatorioTesteImpressoraRoots {
    SRelatorioTesteImpressoraRoots()
    {
        relatoriotesteimpressora_sink = relatoriotesteimpressora_vt;
        w123_sink_labels = w123_labels;
        w123_sink_separador = w123_separador;
        w123_sink_erro = w123_erro;
        w123_sink_idcarga = w123_idcarga;
        w123_sink_demonstracao = w123_demonstracao;
    }
} relatoriotesteimpressora_roots;

} // namespace
