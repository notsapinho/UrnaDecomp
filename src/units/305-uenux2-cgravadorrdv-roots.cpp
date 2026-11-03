// Roots: reach unit 305's template instance the way the target's callers do, until those callers land.
// - api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto> (fn 5825): fns 5680 and 11587;
//   11587 is written (cgravadorrdv.cpp, whose object instantiates it first and gives the link's copy), the stand-in is
//   for 5680 (comum::asn::IConversorASN<EntidadeRegistroDigitalVoto, ...>::Desconverte with the decode inlined), so
//   that the instance keeps two call sites and binaryen keeps it out of line. Its body is no target function's: it
//   decodes two buffers and compares their validity.
// It compiles with the tree's flags, as cgravadorrdv.cpp's object does.
#include <vector>

#include "api/io/asn/cfileasn.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"

namespace {

__attribute__((noinline)) int w305_rdv(const std::vector<char>& dados, const std::vector<char>& outros)
{
    const ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto a =
        api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto>(dados);
    const ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto b =
        api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto>(outros);
    return a.isValid() == b.isValid() ? 305 : 503;
}

const void* volatile w305_sink;

struct SW305Roots {
    SW305Roots()
    {
        w305_sink = reinterpret_cast<const void*>(&w305_rdv);
    }
} w305_roots;

} // namespace
