// Roots: reach unit 293's functions the way the target's callers do, until those callers land. Each has direct callers
// in the target and no table slot (ledger/callgraph.tsv), so each noinline stand-in below gives it two call sites and
// binaryen keeps its body out of line. The stand-ins differ in their bodies, from each other and from every target
// function, take what the target's callers vary as parameters, and are address-taken from a static constructor.
// - api::CPolySingleton<api::IKernelHSM>::instance (fn 2279): fns 2725, 11419, 11616, 11629 and 12110; 2725 is written
//   (ccontrolaarmazenamentodeimagens.cpp), w293_hsm stands for the others. It passes
//   an empty std::source_location, as unit 100's w100_usa does: a record here would be none of the target's.
// - ecourna::api::io::DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (fn 2280): fns 2725, 11419, 11616 and
//   11629; 2725 is written, the stand-in is for the others.
// - comum::asn::GravaArquivo for the envelope (fn 2724): fns 2725, 11626 and 11629 (which calls it twice); 11626 (unit
//   160) and 2725 are written, the stand-in is for 11629.
// - comum::asn::GravaArquivo for the hashes (fn 5367): fn 11620, which calls it twice.
// - comum::CControlaArmazenamentoDeImagens::ArmazenaImagem (fn 2725): fns 5382 and 10425, which calls it twice; 5382 is
//   in the link (unit 135), w293_armazena stands for 10425 and reads the result, as 5382 does. It passes the name it
//   gets as the prefix too, so dead-argument elimination folds no prefix in (5382 passes "me", 10425 "").
// libc's __futimesat (fn 6236), the body of utimes, needs no stand-in now: its callers 2725 (unit 293) and SQLite's
// dotlockLock (fn 12674) are in the link. ccontrolaarmazenamentodeimagens.cpp.o instantiates the two templates first in
// our link now, so the link keeps its copies; this TU compiles with the tree's flags too, as cgravadorbu.cpp's object
// does, whose copies the target keeps by a reading (their records lie in its run).
#include <source_location>
#include <string>
#include <vector>

#include "api/hwil/ikernelhsm.h"
#include "api/io/cfile.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"
#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"
#include "asn1/modules/ModuloEnvelopeChave.h"
#include "ecourna/api/io/asn/serialization.hpp"

namespace {

__attribute__((noinline)) int w293_hsm()
{
    const std::source_location local;
    api::IKernelHSM& a = api::CPolySingleton<api::IKernelHSM>::instance(api::g_polySingletonsInfo(), local);
    api::IKernelHSM& b = api::CPolySingleton<api::IKernelHSM>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 19 : 23;
}

__attribute__((noinline)) void w293_chaves(ModuloEnvelopeChave::EntidadeChave& chave, ModuloEnvelopeChave::EntidadeChave& outra,
    const std::string& nome, const std::string& outroNome)
{
    ecourna::api::io::DeserializeFromFile(chave, nome);
    ecourna::api::io::DeserializeFromFile(outra, outroNome);
}

__attribute__((noinline)) void w293_envelopes(const api::CFile& arquivo, const api::CFile& outro,
    const comum::md::CEnvelopeGenerico& envelope, const comum::md::CEnvelopeGenerico& outroEnvelope)
{
    comum::asn::GravaArquivo(arquivo, envelope);
    comum::asn::GravaArquivo(outro, outroEnvelope);
}

__attribute__((noinline)) void w293_hashes(const api::CFile& arquivo, const comum::md::CEntidadeHashes& hashes,
    const comum::md::CEntidadeHashes& outros)
{
    comum::asn::GravaArquivo(arquivo, outros);
    comum::asn::GravaArquivo(arquivo, hashes);
}

// stands for fn 10425 (5382 is written)
__attribute__((noinline)) int w293_armazena(const std::vector<uebyte>& wsq, const std::string& nome,
    const std::string& diretorio, const std::string& externo)
{
    return static_cast<int>(comum::CControlaArmazenamentoDeImagens::ArmazenaImagem(wsq, nome, diretorio, externo, nome)) + 17;
}

const void* volatile w293_sink;

struct SW293Roots {
    SW293Roots()
    {
        w293_sink = reinterpret_cast<const void*>(&w293_hsm);
        w293_sink = reinterpret_cast<const void*>(&w293_chaves);
        w293_sink = reinterpret_cast<const void*>(&w293_envelopes);
        w293_sink = reinterpret_cast<const void*>(&w293_hashes);
        w293_sink = reinterpret_cast<const void*>(&w293_armazena);
    }
} w293_roots;

} // namespace
