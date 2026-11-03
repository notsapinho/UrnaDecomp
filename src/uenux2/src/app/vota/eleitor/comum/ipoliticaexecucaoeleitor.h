#pragma once

// vota::impl::IPoliticaExecucaoEleitor. RTTI of its control block names it; the path is chosen, beside
// cpoliticaexecucaoeleitor.cpp, whose record at line 45 is GetInst's (POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO
// over CPoliticaExecucaoEleitor, which fn 5925, the slot 17 of vota::CConfirmaVotoNominal and CMajoritarioValido,
// holds inlined). The bytes give a virtual destructor
// in the first slot (the control block's __on_zero_shared calls the deleting destructor at vtable + 4, fn 172), out of
// line in cpoliticaexecucaoeleitor.cpp, the key function: the typeinfo (@1536360) lies in that file's data, between
// GetInst's record and CPoliticaExecucaoEleitor's vtable, not in the executable TU's, which links first and uses the
// class (docs/reference/facts/reading.md R6), and that TU's has<T> (fn 2744, a thunk of fn 3884) loads the type name
// from it. That the destructor is the key function is a choice, slot 2 being pure here; so is `= default`. Slot 2 is
// vota::impl::CPoliticaExecucaoEleitor's LimpaBufferInput (fn 13564, records cpoliticaexecucaoeleitor.cpp:33-37), whose
// name and signature are that record's. That it is pure here is chosen: the interface has no vtable in the target
// (src/units/165-uenux2-app-vota-execucao.mk says how that was searched). No data member is reconstructed, so nothing
// may construct the interface alone.

namespace vota::impl {

class IPoliticaExecucaoEleitor {
public:
    virtual ~IPoliticaExecucaoEleitor();

    static IPoliticaExecucaoEleitor& GetInst();

    virtual void LimpaBufferInput() const = 0;
};

} // namespace vota::impl
