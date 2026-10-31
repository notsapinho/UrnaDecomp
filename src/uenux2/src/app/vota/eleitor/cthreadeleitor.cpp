#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

CThreadEleitor& CThreadEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CThreadEleitor> CThreadEleitor::s_inst;
std::mutex CThreadEleitor::s_mutex;

CThreadEleitor::CThreadEleitor() = default;

CThreadEleitor::~CThreadEleitor() = default;

} // namespace vota

// <stubs>
// f4349 · 1427 B · unmatched · name unknown
// ? f4349(i32) { ... }
// </stubs>
