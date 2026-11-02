#pragma once

#include "app/vota/eleitor/isincronismovotoeleitor.h"

// vota::impl::CSincronismoVotoEleitor, ISincronismoVotoEleitor's default instance (RTTI: si_class of the interface,
// typeinfo @1534176, vtable @1534156 [174, 144, 7174]). GetInst (csincronismovotoeleitor.cpp:67) builds it: fn 7181,
// which holds GetInst inlined, allocates 4 bytes and stores only the vptr, so the class adds no data member. Its
// destructors are the shared bodies 174 and 144 (implicit). Slot 2, Sincroniza (fn 7174, 3288 B), is pending
// (src/units/241-uenux2-app-vota-eleitor-pending.cpp says what it waits for); being the class's key function, its trap
// makes the pending object emit the vtable, where the target's lies in csincronismovotoeleitor.cpp's data, after the
// interface's typeinfo. No record names a header for the class: this path, beside csincronismovotoeleitor.cpp, is
// chosen.

namespace vota::impl {

class CSincronismoVotoEleitor : public ISincronismoVotoEleitor {
public:
    bool Sincroniza() override;
};

} // namespace vota::impl
