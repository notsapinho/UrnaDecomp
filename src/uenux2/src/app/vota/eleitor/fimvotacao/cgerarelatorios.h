#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CGeraRelatorios (RTTI: si_class of comum::CAppState; vtable @1540516 [244, 387, 12105, 7480, 1661, 218, 425,
// 218, 425]): it overrides StartState (slot 2, fn 12105, record cgerarelatorios.cpp:51, written in cgerarelatorios.cpp
// with the three report functions it holds inlined: src/units/372-uenux2-relatorios-gerarelatorios.mk) and the
// destructors, the bodies the states over one std::shared_ptr at +12 share (fns 244 and 387): final, and out of line
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn 6084) keeps the object in a static
// std::unique_ptr (@1833568) under a static std::mutex (@1833544), unit 104's shape, and builds the 20-byte object as
// the base's constructor with 0 and, at +12, the form "Preparando dados para encerramento" (fn 6583,
// app/vota/eleitor/comum/ctelasvota.cpp, called). Chosen: the member's name and its type (the std::shared_ptr of
// api::IForm<api::IScreen> that fn 6583 returns, which the target only stores), the names GetInst, s_inst and s_mutex,
// the destructor declared first. This header's path is chosen, beside the .cpp the record names.
class CGeraRelatorios final : public comum::CAppState {
public:
    virtual ~CGeraRelatorios() override;

    static CGeraRelatorios& GetInst();

    virtual void StartState() override;

private:
    CGeraRelatorios();

    static std::mutex s_mutex;
    static std::unique_ptr<CGeraRelatorios> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_telaPreparandoDados;
};

} // namespace vota
