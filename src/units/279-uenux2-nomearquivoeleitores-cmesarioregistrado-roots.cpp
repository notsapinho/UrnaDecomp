// Roots of unit 279 (src/units/279-uenux2-nomearquivoeleitores-cmesarioregistrado.mk): the references the target keeps
// the unit's functions by, while their callers are not in the link. comum::CMesarioRegistrado's vtable needs none: the
// vptr store of its constructor, which IGestorDadoMesario::StartState (fn 10337, unit 135) holds inlined with GetInst,
// is in the link and keeps StartState (fn 10339) and ProcessInput (fn 10338) in the table.
// - comum::NomeArquivoEleitores (fn 3745): the target's table holds it (slot 2464), and its direct callers, fns 1937
//   (comum::CEleitorDetalhe::GetBiometria) and 7787, are not written: its address is taken, the reference the table is.
// - comum::NomeArquivoEleitoresTTE (fn 5727): fns 1937 and 7787 call it once each; w279_tte calls it twice for them,
//   with no argument one constant at both calls, so binaryen folds none, as in the target.
// The stand-in's body is no target function's.
#include <string>

#include "app/comum/nomearquivo/cnomearquivo.h"

namespace {

// stands for fns 1937 and 7787
__attribute__((noinline)) int w279_tte(const comum::SIdentificacaoArquivo& identificacao, uedword municipio, ueword zona,
    ueword secao)
{
    return static_cast<int>(comum::NomeArquivoEleitoresTTE(identificacao, municipio + 1, zona, secao).size() * 5 +
        comum::NomeArquivoEleitoresTTE(identificacao, municipio, zona, secao + 3).size());
}

int (*volatile w279_sink_tte)(const comum::SIdentificacaoArquivo&, uedword, ueword, ueword);
std::string (*volatile w279_sink_eleitores)(const comum::SIdentificacaoArquivo&, uedword, ueword, ueword);

struct SW279Roots {
    SW279Roots()
    {
        w279_sink_tte = w279_tte;
        w279_sink_eleitores = comum::NomeArquivoEleitores;
    }
} w279_roots;

} // namespace
