// vota::CEleitorEncontrado (/home/rubio/tse/uenux2/src/app/vota/operador/leidentidade/celeitorencontrado.cpp). This
// comment is the reconstruction's. The file's record is StartState's (fn 10635, pending), line 102, past the lines
// written here. Written: the constructor, GetInst and the statics, whose lines are a choice; fn 10631 holds GetInst
// inlined. src/units/104-uenux2-app-vota-estados.mk says which of this is evidence.
#include "app/vota/operador/leidentidade/celeitorencontrado.h"

namespace vota {

CEleitorEncontrado& CEleitorEncontrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorEncontrado());
    }
    return *s_inst;
}

CEleitorEncontrado::CEleitorEncontrado()
    : comum::CAppState(EVENTO_NENHUM)
{
}

std::unique_ptr<CEleitorEncontrado> CEleitorEncontrado::s_inst;
std::mutex CEleitorEncontrado::s_mutex;

} // namespace vota
