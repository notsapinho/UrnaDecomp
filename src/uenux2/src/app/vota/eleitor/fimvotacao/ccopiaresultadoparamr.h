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

// vota::CCopiaResultadoParaMR (RTTI: si_class of comum::CAppState; vtable @1540072 [244, 387, 12134, 7480, 1661, 218,
// 425, 218, 425]): it overrides StartState (slot 2, fn 12134, records ccopiaresultadoparamr.cpp:59 and, for
// CopiaResultado, which it holds inlined, :85, :94, :112, :126 and :174), pending, and the destructors, the bodies the
// states over one std::shared_ptr at +12 share (fns 244 and 387): final, and out of line
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn 6174) keeps the object in a static
// std::unique_ptr (@1833440) under a static std::mutex (@1833416), unit 104's shape, and builds the 20-byte object as
// the base's constructor with 4 (EVENTO_TICK) and, at +12, the form "Gravando o resultado na mídia"
// (TelaCopiaResultadoParaMR, app/vota/eleitor/comum/ctelasvota.cpp, which binaryen inlines here behind a second
// stack-pointer prologue). Chosen: the member's name and its type (the std::shared_ptr of api::IForm<api::IScreen>
// that the function returns, which the target only stores), the names GetInst, s_inst and s_mutex, the destructor
// declared first. CopiaResultado, a member (its records name it), is declared here when it is written. This header's
// path is chosen, beside the .cpp the records name.
class CCopiaResultadoParaMR final : public comum::CAppState {
public:
    virtual ~CCopiaResultadoParaMR() override;

    static CCopiaResultadoParaMR& GetInst();

    virtual void StartState() override;

private:
    CCopiaResultadoParaMR();

    static std::mutex s_mutex;
    static std::unique_ptr<CCopiaResultadoParaMR> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_tela;
};

} // namespace vota
