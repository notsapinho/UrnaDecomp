#pragma once

// vota::impl::IPoliticaExecucaoEleitor. RTTI of its control block names it; the path is chosen, beside
// cpoliticaexecucaoeleitor.cpp, whose record at line 45 is GetInst's (inlined into fn 5925, not reconstructed). The bytes
// give a virtual destructor in the first slot (the control block's __on_zero_shared calls the deleting destructor at
// vtable + 4, fn 172) and slot 2, vota::impl::CPoliticaExecucaoEleitor's LimpaBufferInput (fn 13564, records
// cpoliticaexecucaoeleitor.cpp:33-37), whose name and signature are that record's. That it is pure here is chosen: the
// interface has no vtable in the target (src/units/165-uenux2-app-vota-execucao.mk says how that was searched). No
// data member is reconstructed, so nothing may construct the interface alone.

namespace vota::impl {

class IPoliticaExecucaoEleitor {
public:
    virtual ~IPoliticaExecucaoEleitor() = default;

    static IPoliticaExecucaoEleitor& GetInst();

    virtual void LimpaBufferInput() const = 0;
};

} // namespace vota::impl
