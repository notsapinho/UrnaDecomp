// Roots of fragment 186, compiled at UENUX2_CXXFLAGS (the tree whose objects hold the target's copies of the template
// code below), each stand-in address-taken from a static constructor:
// - api::hash::CHashArquivo's constructor (target fn 3600). The target calls it directly from three functions
//   (ledger/callgraph.tsv), none through the table: 10269, comum::asn::CConversorHashArquivo::DoDesconverte (unit 46,
//   in the link), and 5358 and 5360. 5358 is in the link (api::hash::ListaHashesArquivos, fragment 227, written and
//   not matched); 5360 is not reconstructed (it holds the records of api::hash::CMontadorHash in cmontadorhash.cpp and
//   of CHashDiretorio::ValidaObjeto, chashdiretorio.cpp:41). w186_hash stands for 5360, and stood for 5358 too until it
//   was written; it stays while 5360 waits. Both of those read the constructor's result
//   (`local.set` after the call, where 10269 drops it), and the target's wasm type keeps it, (i32 i32 i32)->(i32): the
//   stand-in returns it, so dead-argument elimination keeps it here too. Declared through an asm label with the
//   object's signature (a constructor returns `this`).
// - std::vector<comum::md::CComparecimentoMesario>::__emplace_back_slow_path (target fn 5375). Its one caller in the
//   target, 11616 (comum::CGravadorRCSecao's slot 7, not reconstructed), calls it twice, each time after it copies a
//   52-byte element into a temporary and finds no room in the vector: a push_back of an rvalue, and the element
//   CComparecimentoMesario, are readings of the layout (src/units/186-uenux2-chasharquivo.mk).
//   w186_comparecimentos stands for 11616 and makes the same two calls.
// (CBaseError<comum::EUeComumReconhecimentoBiometricoError, SErrorLimits{9000, 9050}>'s constructor, fn 5369, needs no
// stand-in now: its one target caller, 2725, unit 293's, is in the link and throws it twice, with codes 9000 and 9001,
// two messages and the records at ccontrolaarmazenamentodeimagens.cpp:117 and :135, so no argument is one constant.)
#include <string>
#include <utility>
#include <vector>

#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

extern "C" {
int w3600_root_0(int, int, int) __asm__(
    "_ZN3api4hash12CHashArquivoC1ERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEESA_");
}

namespace {

__attribute__((noinline)) int w186_hash(int arquivo, int nome, int hash)
{
    return w3600_root_0(arquivo + 24, nome, hash);
}

__attribute__((noinline)) unsigned w186_comparecimentos(std::vector<comum::md::CComparecimentoMesario>& mesarios,
                                                        const comum::md::CComparecimentoMesario& primeiro,
                                                        const comum::md::CComparecimentoMesario& segundo)
{
    mesarios.push_back(comum::md::CComparecimentoMesario(primeiro));
    mesarios.push_back(comum::md::CComparecimentoMesario(segundo));
    return mesarios.size() + 186;
}

int (*volatile w186_sink_hash)(int, int, int);
unsigned (*volatile w186_sink_comparecimentos)(std::vector<comum::md::CComparecimentoMesario>&,
                                               const comum::md::CComparecimentoMesario&,
                                               const comum::md::CComparecimentoMesario&);

struct SW186Roots {
    SW186Roots()
    {
        w186_sink_hash = w186_hash;
        w186_sink_comparecimentos = w186_comparecimentos;
    }
} w186_roots;

} // namespace
