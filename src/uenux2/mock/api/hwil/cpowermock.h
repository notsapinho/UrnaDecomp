#pragma once

#include <chrono>

#include "api/hwil/ipower.h"

namespace api::teste {

// Recovered: RTTI names the class, an si_class of api::IPower (vtable @1530944). The object is 48 bytes: fn 8302 (simulador's
// init) allocates 48 and clang inlined the constructor there: the implicit constructor this class gives, in a
// `new CPowerMock`, compiles to the same stores in the same order (+12, +4, +28, +20, the vptr, +40), neighbouring
// members merged into i64 constants, so the layout and the initial values below are read from those stores: IPower's
// block is zero, this class's own block at +20 has word 0 = 0x840, word 1 = 2 and word 3 = 100, and the i64 at +40 comes
// from fn 1360, whose body is std::chrono::steady_clock::now (clock_gettime(1, ...) and the message
// "clock_gettime(CLOCK_MONOTONIC) failed"). No member of the vtable reads +40. The destructors are the shared empty
// bodies (slots 13 and 14: fns 174 and 144), an implicit destructor. Slot 16 is `return true`, fn 434, a body other
// classes share; that the mock and not IPower holds it is chosen. `final` on the class gives the same bytes, so whether
// it is final is not recovered. The members' names are IPower's, chosen (api/hwil/ipower.h says from what), and so are
// the data members'. The path is chosen: the class has no record; comum::teste::CAppInfoBuilder's names
// mock/app/comum/cappinfobuilder.cpp for the tree of the teste namespaces, and the directory mirrors src/api/hwil/.
// Slot 7 reads this class's block, without ReadStatus, and clamps the level it holds.
class CPowerMock : public IPower {
public:
    virtual uebyte BatLevel() override
    {
        if (m_simulado.m_carga > 100) {
            m_simulado.m_carga = 100;
        }
        return m_simulado.m_carga;
    }

protected:
    virtual void ReadStatus(SStatus& status) override { status = m_simulado; }
    virtual bool Slot16() override { return true; }

private:
    SStatus m_simulado{.m_statusBatExt = 2, .m_bit11 = 1, .m_foneDesconectado = 1, .m_carga = 100};
    std::chrono::steady_clock::time_point m_inicio = std::chrono::steady_clock::now();
};

} // namespace api::teste
