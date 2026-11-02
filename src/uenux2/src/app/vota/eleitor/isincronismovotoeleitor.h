#pragma once

// vota::impl::ISincronismoVotoEleitor: the head alone. RTTI of its control block names it; the path is chosen, beside csincronismovotoeleitor.cpp. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). Slot 2 returns a word: the shared body 434 (`return 1`) in
// the executable TU's (anonymous namespace)::CSincronismoVotoEleitorWeb, fn 7174 in vota::impl::CSincronismoVotoEleitor. Its name and
// its bool are chosen.

namespace vota::impl {

class ISincronismoVotoEleitor {
public:
    virtual ~ISincronismoVotoEleitor() = default;

    virtual bool Sincroniza() = 0;
};

} // namespace vota::impl
