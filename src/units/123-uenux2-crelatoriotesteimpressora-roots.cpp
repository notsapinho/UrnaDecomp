// Roots: keep comum::CRelatorioTesteImpressora in the skeleton link the way the target keeps it.
// - Its one user is its constructor (fn 5586, not reconstructed), which stores the vptr (@1576660, vtable @1576652) into
//   an object of the frames of fns 11869 (vota::CVerificaHorarioZeresima's slot 7) and 11911 (vota::CImpressaoEstadoUrna's
//   slot 2), which hand it to fn 5591; 5591 reaches every member through the vtable, slots 2 to 25. Taking the vtable's
//   address keeps the same set: every slot in the table and none called directly.
// - GetCorrespondencia (slot 9, fn 11197) calls CDadoCorrespondencia's copy constructor, fn 1249, which has six callers
//   in the target (awk -F'\t' '$2==1249' ledger/callgraph.tsv: 5637, 5740, 5856, 11197, 11395, 12098). None of the
//   others is reconstructed, so w123_copia stands for them: with one caller binaryen inlines the copy into 11197, as the
//   target does not.
// - InicializaTradutorFrase (slot 10, fn 11196) hands its map to comum::md::CTradutorFrase::SetLabels, inline, which
//   calls the tree's __assign_multi, fn 5794, with the static map's address. 5794 has two callers in the target
//   (awk -F'\t' '$2==5794' ledger/callgraph.tsv: 7787, 11196); w123_labels stands for 7787, not reconstructed, so that
//   it keeps two call sites here, as src/units/README.md "Companion files" asks. It goes when 7787 lands.
// - GetSeparadorFase (slot 20, fn 11183) calls CRelUtil::GetSeparadorFase, fn 1919, which has six callers in the target
//   (awk -F'\t' '$2==1919' ledger/callgraph.tsv: 2785, 11183, 11943, 11946, 12105, 12110). w123_separador stands for the
//   five not reconstructed: with one caller binaryen inlines 1919 into 11183.
// - 1919 throws CUeComumRelatoriosError, whose constructor is fn 580, a thunk of binaryen's 710 with 14 callers in the
//   target (awk -F'\t' '$2==580' ledger/callgraph.tsv); 1919 is the only one reconstructed, and with one caller binaryen
//   inlines the constructor into it. w123_erro stands for the other 13 (11181, 11212, 11214, 11233, 11968, 12110, 1543,
//   2786, 2791, 3689, 3696, 5967, 942). It passes an empty std::source_location: a default argument would make a record
//   on this line, which is none of the target's.
#include <source_location>
#include <string>

#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

extern "C" {
extern const char relatoriotesteimpressora_vt[] __asm__("_ZTVN5comum25CRelatorioTesteImpressoraE");
}

namespace {

using comum::md::estadoaplicacao::CDadoCorrespondencia;

__attribute__((noinline)) unsigned w123_copia(const CDadoCorrespondencia& correspondencia)
{
    const CDadoCorrespondencia copia(correspondencia);
    return copia.GetNumeroInternoUrna() + 123;
}

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

const void* volatile relatoriotesteimpressora_sink;
unsigned (*volatile w123_sink_copia)(const CDadoCorrespondencia&);
unsigned (*volatile w123_sink_labels)(const std::map<char, ecourna::app::dados::CLabelParametrizado>&);
unsigned (*volatile w123_sink_separador)(comum::EUrnaFase);
void (*volatile w123_sink_erro)(int, const std::string&);

struct SRelatorioTesteImpressoraRoots {
    SRelatorioTesteImpressoraRoots()
    {
        relatoriotesteimpressora_sink = relatoriotesteimpressora_vt;
        w123_sink_copia = w123_copia;
        w123_sink_labels = w123_labels;
        w123_sink_separador = w123_separador;
        w123_sink_erro = w123_erro;
    }
} relatoriotesteimpressora_roots;

} // namespace
