// Reconstruction: comum::CFotos's singleton (target fns 2819, 11512, 11513), its constructor (3756) and destructor (2818).
// Their lines are a choice, above the records of GetFotoPara (lines 39, 51) and CFotos::Load (lines 111, 121), which are
// not reconstructed.
#include "app/comum/dados/cfotos.h"

#include <memory>
#include <mutex>

namespace comum {

CFotos& CFotos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CFotos>();
    }
    return *s_inst;
}

std::unique_ptr<CFotos> CFotos::s_inst;
std::mutex CFotos::s_mutex;

CFotos::CFotos() : CFotos("CFotos") {}

CFotos::~CFotos() = default;

} // namespace comum

// <stubs>
// f3755 · 4858 B · unmatched · name unknown
// void f3755(i32, i32) { ... }
// </stubs>
