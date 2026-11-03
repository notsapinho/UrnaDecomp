#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"
#include "ecourna/api/uetypes.hpp"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// The record of ImprimeBU (cimprimindobu.cpp:111) names this type, unqualified. Its callers pass 0 (12077, 12078,
// 12081) and 1 (12065); with 0, ImprimeBU prints the file with the title "boletim de urna" and "<n>ª via", with 1 with
// two empty strings. The scope, the enumerators' names and that it is an unscoped enum are chosen.
enum PrintMessageMode {
    PRINT_WITH_MESSAGE = 0,
    PRINT_WITHOUT_MESSAGE = 1,
};

// vota::CImprimindoBU (RTTI: si_class of comum::CAppState; vtable @1541292 [244, 387, 12078, 7480, 1661, 218, 425,
// 12077, 425]): it overrides StartState (slot 2, fn 12078, records lines 70 and 71) and ProcessInput (slot 7, fn
// 12077), both pending: StartState calls fns 1127 and 4551 and ImprimeBU (fn 2890) and reads a .bss flag with no name,
// ProcessInput calls fns 491 (unit 205's now) and 3701. ImprimeBU is static by its records' text (`static void
// vota::CImprimindoBU::ImprimeBU(uebyte, PrintMessageMode)`, lines 111 and 114), and public:
// CEmitirMaisBU::ProcessInput (fn 12081) and CImprimirBUOutrasObrigatorias::StartState (fn 12065) call it too. The
// destructors are the bodies the states over one std::shared_ptr at +12 share (fns 244 and 387): final, and out of line
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn 5986) keeps the object in a static std::unique_ptr
// (@1833652, destroyed at exit by fn 12080) under a static std::mutex (@1833628, by fn 12079), and builds it as the
// base's constructor with 2 and, at +12, a copy of CTelasVota::GetInst()'s member at +100, the form. Chosen: the
// member's name and its type (CTelasVota's members' type, which ctelasvota.h chooses), the names GetInst, s_inst and
// s_mutex, the destructor declared first. This header's path is chosen, beside the .cpp the records name.
class CImprimindoBU final : public comum::CAppState {
public:
    virtual ~CImprimindoBU() override;

    static CImprimindoBU& GetInst();

    static void ImprimeBU(uebyte numVia, PrintMessageMode modo);

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CImprimindoBU();

    static std::mutex s_mutex;
    static std::unique_ptr<CImprimindoBU> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
