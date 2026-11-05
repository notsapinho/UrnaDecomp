#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace vota {

// vota::CMenuFiltrarCandidatosPorPartido (RTTI: si_class of comum::CAppState; vtable @1545520 [174, 144, 11884, 7480,
// 1661, 218, 425, 218, 425]): it overrides StartState (slot 2, fn 11884, record
// cmenufiltrarcandidatosporpartido.cpp:39, written there: src/units/104-uenux2-app-vota-estados.mk) and adds no data
// member, so the object is the base's 12 bytes and slots 0 and 1 hold the destructors the states with no member share
// (fns 174 and 144). final: GetInst frees the old object with no call through the vtable. A singleton: GetInst, inlined
// into vota::CMenuVisualizarCandidatos::StartState (fn 11881), keeps the object in a static std::unique_ptr (@1834604,
// destroyed at exit by fn 11886) under a static std::mutex (@1834580, by fn 11885), and builds it as the base's
// constructor with 2. Chosen: the names GetInst, s_inst and s_mutex, and this header's path beside the .cpp the record
// names.
class CMenuFiltrarCandidatosPorPartido final : public comum::CAppState {
public:
    static CMenuFiltrarCandidatosPorPartido& GetInst();

    virtual void StartState() override;

private:
    CMenuFiltrarCandidatosPorPartido();

    static std::mutex s_mutex;
    static std::unique_ptr<CMenuFiltrarCandidatosPorPartido> s_inst;
};

} // namespace vota
