// Reconstruction's note, not TSE's text: vota::CFimVotoEleitor's constructor, GetInst and statics, which fn 7181
// (vota::CSincronismoEleitor::ProcessKey) holds inlined. The file's one record, line 42, is StartState's (fn 7198,
// pending), and its line stays blank; the other lines are chosen, above it, where the statics' exit destructors' order
// puts them (cfimvotoeleitor.h).
#include "app/vota/eleitor/cfimvotoeleitor.h"

namespace vota {

CFimVotoEleitor::CFimVotoEleitor()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFimVotoEleitor& CFimVotoEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFimVotoEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CFimVotoEleitor> CFimVotoEleitor::s_inst;
std::mutex CFimVotoEleitor::s_mutex;




















} // namespace vota
