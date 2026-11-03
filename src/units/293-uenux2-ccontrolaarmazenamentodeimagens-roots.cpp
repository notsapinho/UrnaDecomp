// Roots: reach unit 293's functions the way the target's callers do, until those callers land. Each has direct callers
// in the target and no table slot (ledger/callgraph.tsv), so each noinline stand-in below gives it two call sites and
// binaryen keeps its body out of line. The stand-ins differ in their bodies, from each other and from every target
// function, take what the target's callers vary as parameters, and are address-taken from a static constructor.
// - api::CPolySingleton<api::IKernelHSM>::instance (fn 2279): fns 2725, 11419, 11616, 11629 and 12110. w293_hsm passes
//   an empty std::source_location, as unit 100's w100_usa does: a record here would be none of the target's.
// - ecourna::api::io::DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (fn 2280): fns 2725, 11419, 11616 and
//   11629.
// - comum::asn::GravaArquivo for the envelope (fn 2724): fns 2725, 11626 and 11629 (which calls it twice).
// - comum::asn::GravaArquivo for the hashes (fn 5367): fn 11620, which calls it twice.
// - libc's __futimesat (fn 6236), the body of utimes, which binaryen inlines into each caller (the dirfd it passes
//   folded): fn 2725 calls utimes. Its other caller, SQLite's dotlockLock (fn 12674), is in the link, and with no
//   second call site binaryen inlined __futimesat into it, where the target calls 6236. Neither target caller reads
//   the result, so w293_tempos does not either: a stand-in that read it kept the result binaryen drops in the target.
// This TU is the first to instantiate the two templates, so the link keeps its copies; it compiles with the tree's
// flags, as cgravadorbu.cpp's object, whose copies the target keeps (their records lie in its run of the data), does.
#include <source_location>
#include <string>

#include <sys/time.h>

#include "api/hwil/ikernelhsm.h"
#include "api/io/cfile.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"
#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"
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

__attribute__((noinline)) void w293_tempos(const char* caminho, const struct timeval* tempos, const char* outro)
{
    utimes(caminho, tempos);
    utimes(outro, tempos + 1);
}

const void* volatile w293_sink;

struct SW293Roots {
    SW293Roots()
    {
        w293_sink = reinterpret_cast<const void*>(&w293_hsm);
        w293_sink = reinterpret_cast<const void*>(&w293_chaves);
        w293_sink = reinterpret_cast<const void*>(&w293_envelopes);
        w293_sink = reinterpret_cast<const void*>(&w293_hashes);
        w293_sink = reinterpret_cast<const void*>(&w293_tempos);
    }
} w293_roots;

} // namespace
