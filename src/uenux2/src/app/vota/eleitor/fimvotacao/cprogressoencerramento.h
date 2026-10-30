#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cabstracttelaprogresso.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
class CProgressBar;
} // namespace api

namespace vota {

/**
 * Tela de progresso mostrada enquanto o resultado da votacao e gravado.
 */
// vota::CProgressoEncerramento (RTTI: si_class of comum::CAbstractTelaProgresso; vtable @1540588 [3907, 12104, 12103,
// 12102, 12101]). Only CGravaResultado::StartState builds it (fn 12098, with std::make_shared and the constructor
// inlined: 56 bytes, the control block's 12 and this class's 44), and its constructor takes nothing from it. The layout
// is what that constructor stores and the destructor (fn 3907) destroys: the form at +4, which the constructor gets
// from a std::shared_ptr<api::IForm<api::IScreen>> (fn 5550 builds that type), the progress bar at +12, an
// api::CProgressBar (fn 5545 makes it, and slot 4 calls the bar's increment, fn 5508, on it), and a std::mutex at +20
// that slots 2 to 4 hold while they run. Recovered: the destructor, out of line (the deleting one, fn 12104, calls it)
// and declared first, so it is the key function and cprogressoencerramento.cpp emits the vtable. It stores no vptr,
// which clang leaves out of a destructor that destroys members only when the class is final. Not recovered: the
// constructor and the three overriders (they call fns 3667 and 5508, which have no name yet). The member names are
// not in the target.
class CProgressoEncerramento final : public comum::CAbstractTelaProgresso {
public:
    CProgressoEncerramento();
    virtual ~CProgressoEncerramento() override;

    virtual void Inicia() override;

    virtual void Finaliza() override;

    virtual void Incrementa() override;

private:
    std::shared_ptr<api::IForm<api::IScreen>> m_form;
    std::shared_ptr<api::CProgressBar> m_barra;
    std::mutex m_mutex;
};

} // namespace vota
