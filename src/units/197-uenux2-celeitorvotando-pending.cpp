// Pending members: the vota::CEleitorVotando slots src/uenux2/src/app/vota/eleitor/celeitorvotando.cpp does not hold
// yet. The destructor is declared first, as the key function, so this object emits the class's vtable, which needs
// them all; their bodies are NOT the target's, they trap. Target functions, reached through the vtable:
// - the destructor, D2 2483 (slot 0) and D0 7385 (slot 1): the D2 destroys the member at +20 through fn 1468,
//   api::CApplicationContext's destructor (api/gui/capplicationcontext.h, unit 193); GetInst (fn 3229, not written) and
//   fn 7416 call the D2 directly too;
// - StartState 7377 (slot 2, records celeitorvotando.cpp:125 and :131 of IniciaCiclo), 2313 B: calls fns 2837, 3721 and
//   4464, which have no name, and 1841, 3684 and 3783, which have names;
// - NeedChangeState 7352 (slot 3, record :294), 305 B: calls fns 4454 and 4464, which have no name;
// - FinishState 7370 (slot 5), 61 B: calls fn 5553 on the +20 member;
// - ProcessKey 7337 (slot 6), 96 B: calls suspenderEleitor (fn 4442, records :410 and :427), not written.
// Move each into celeitorvotando.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/celeitorvotando.h"

namespace vota {

CEleitorVotando::~CEleitorVotando()
{
    __builtin_trap();
}

void CEleitorVotando::StartState()
{
    __builtin_trap();
}

bool CEleitorVotando::NeedChangeState()
{
    __builtin_trap();
}

void CEleitorVotando::FinishState()
{
    __builtin_trap();
}

void CEleitorVotando::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
