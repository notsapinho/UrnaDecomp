#pragma once

// vota::impl::ISincronismoVotoEleitor. RTTI of its control block names it; the path is chosen, beside
// csincronismovotoeleitor.cpp, whose one record (line 67) is GetInst's
// (POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO over vota::impl::CSincronismoVotoEleitor), which fn 7181 holds
// inlined. The bytes give a virtual destructor in the first slot: the control block's __on_zero_shared calls the
// deleting destructor at vtable + 4 (fn 172). It is out of line, in csincronismovotoeleitor.cpp, the class's key
// function. Evidence: its typeinfo (@1534148) lies in that file's data, between GetInst's record and
// CSincronismoVotoEleitor's vtable, not in the executable TU's, which links first and uses the class
// (docs/reference/facts/reading.md R6); that TU's has<T> (fn 2741, a thunk of fn 3884) loads the type name from the
// typeinfo, and 7181's inlined instance<T>, from the TU that holds the typeinfo, has it as a constant. That the
// destructor is the key function is a choice, slot 2 being pure here; so is `= default`. Slot 2 returns a word: the
// shared body 434 (`return 1`) in the executable TU's (anonymous namespace)::CSincronismoVotoEleitorWeb, fn 7174 in
// vota::impl::CSincronismoVotoEleitor. Its name and its bool are chosen.

namespace vota::impl {

class ISincronismoVotoEleitor {
public:
    virtual ~ISincronismoVotoEleitor();

    static ISincronismoVotoEleitor& GetInst();

    virtual bool Sincroniza() = 0;
};

} // namespace vota::impl
