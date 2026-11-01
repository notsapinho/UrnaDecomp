// Roots of fragment 198: api::hash::CHashDiretorio's destructor (target fn 2220) is called by itself (the vector of
// subdirectories) and by 5359 and 5360 (5360 loads api/hash/cmontadorhash.cpp's records), neither reconstructed.
// DestroiDuas stands for both with two call sites, calling the destructor by its qualified name in an optnone function,
// which emits the implicit destructor in this object (src/units/README.md "Companion files"). The census pairs no
// target function with DestroiDuas. Compiled at UENUX2_CXXFLAGS; src/api/'s objects drop -fno-strict-aliasing, and this
// object is the same without it (fragment 198 has the comparison).
#include "api/hash/chashdiretorio.h"

namespace {

__attribute__((noinline, optnone)) void DestroiDuas(api::hash::CHashDiretorio* hashesA, api::hash::CHashDiretorio* hashesB)
{
    hashesA->~CHashDiretorio();
    hashesB->~CHashDiretorio();
}

void* volatile w198_sink;

struct SW198Roots {
    SW198Roots()
    {
        w198_sink = reinterpret_cast<void*>(&DestroiDuas);
    }
} w198_roots;

} // namespace
