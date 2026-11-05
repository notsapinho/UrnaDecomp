#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CMenuFiltrarCandidatosPorCargo (RTTI: si_class of comum::CAppState; vtable @1545448 [174, 144, 11888, 7480,
// 1661, 218, 425, 218, 425]): it overrides StartState (slot 2, fn 11888, record cmenufiltrarcandidatosporcargo.cpp:44,
// pending: src/units/104-uenux2-app-vota-estados-pending.cpp) and adds no data member, so the object is the base's 12
// bytes and slots 0 and 1 hold the destructors the states with no member share (fns 174 and 144). final: GetInst
// frees the old object with no call through the vtable. A singleton: GetInst, inlined into
// vota::CMenuVisualizarCandidatos::StartState (fn 11881), keeps the object in a static std::unique_ptr (@1834576,
// destroyed at exit by fn 11890) under a static std::mutex (@1834552, by fn 11889), and builds it as the base's
// constructor with 2. Chosen: the names GetInst, s_inst and s_mutex, and this header's path beside the .cpp the record
// names.
class CMenuFiltrarCandidatosPorCargo final : public comum::CAppState {
public:
    static CMenuFiltrarCandidatosPorCargo& GetInst();

    virtual void StartState() override;

private:
    CMenuFiltrarCandidatosPorCargo();

    static std::mutex s_mutex;
    static std::unique_ptr<CMenuFiltrarCandidatosPorCargo> s_inst;
};

} // namespace vota
