// Roots: reach unit 293's functions the way the target's callers do, until those callers land. Each has direct callers
// in the target and no table slot (ledger/callgraph.tsv), so each noinline stand-in below gives it two call sites and
// binaryen keeps its body out of line. The stand-ins differ in their bodies, from each other and from every target
// function, take what the target's callers vary as parameters, and are address-taken from a static constructor.
// - api::CPolySingleton<api::IKernelHSM>::instance (fn 2279): fns 2725, 11419, 11616, 11629 and 12110; 2725
//   (ccontrolaarmazenamentodeimagens.cpp), 11419 (fragment 335's), 11616 (unit 122) and 11629 (unit 200's) are written,
//   w293_hsm stands for 12110. It passes an empty std::source_location, as unit 100's w100_usa does: a record here
//   would be none of the target's.
// - ecourna::api::io::DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (fn 2280) needs none now: its callers
//   2725, 11419, 11616 (unit 122) and 11629 (unit 200's) are all written, and its stand-in went with 11629.
// - comum::asn::GravaArquivo for the envelope (fn 2724) needs none now: its callers 2725, 11626 (unit 160) and 11629
//   (unit 200, which calls it twice) are all written, and its stand-in went with 11629.
// - comum::asn::GravaArquivo for the hashes (fn 5367): fn 11620, which calls it twice.
// - comum::CControlaArmazenamentoDeImagens::ArmazenaImagem (fn 2725) needs no stand-in now: its target callers, 5382
//   (unit 135) and 10425 (unit 142, written, which calls it three times with the prefix "" where 5382 passes "me"), are
//   in the link.
// libc's __futimesat (fn 6236), the body of utimes, needs no stand-in now: its callers 2725 (unit 293) and SQLite's
// dotlockLock (fn 12674) are in the link. Unit 122's cgravadorrcsecao.cpp.o instantiates the two templates first in our
// link now, so the link keeps its copies; the target keeps cgravadorbu.cpp's by a reading (their records lie in its
// run); this TU compiles with the tree's flags too.
#include <source_location>
#include <string>
#include <vector>

#include "api/hwil/ikernelhsm.h"
#include "api/io/cfile.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"

namespace {

__attribute__((noinline)) int w293_hsm()
{
    const std::source_location local;
    api::IKernelHSM& a = api::CPolySingleton<api::IKernelHSM>::instance(api::g_polySingletonsInfo(), local);
    api::IKernelHSM& b = api::CPolySingleton<api::IKernelHSM>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 19 : 23;
}

__attribute__((noinline)) void w293_hashes(const api::CFile& arquivo, const comum::md::CEntidadeHashes& hashes,
    const comum::md::CEntidadeHashes& outros)
{
    comum::asn::GravaArquivo(arquivo, outros);
    comum::asn::GravaArquivo(arquivo, hashes);
}

const void* volatile w293_sink;

struct SW293Roots {
    SW293Roots()
    {
        w293_sink = reinterpret_cast<const void*>(&w293_hsm);
        w293_sink = reinterpret_cast<const void*>(&w293_hashes);
    }
} w293_roots;

} // namespace
