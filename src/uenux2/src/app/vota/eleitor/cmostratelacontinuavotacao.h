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

// vota::CMostraTelaContinuaVotacao (RTTI: si_class of comum::CAppState; vtable @1533948 [244, 387, 7221, 7480, 1661,
// 218, 425, 218, 425]): it overrides StartState (slot 2, fn 7221), which shows the form at +12, posts type 12 to
// vota::CThreadOperador's queue and goes to vota::CAguardaMensagem's state. The 20-byte object adds a std::shared_ptr
// at +12, to a form (StartState calls its slot 2; the pointee's type is chosen, the one vota::CMaisInformacoes's form
// has). Slots 0 and 1 hold the destructors the 49 states with that one member share (fns 244 and 387), a final class's
// with the destructor out of line (cmaisinformacoes.h says what shows it). A singleton: GetInst, which binaryen inlined
// into its one caller (fn 7481, vota::CAguardaMensagem's slot 6), keeps the object in a static std::unique_ptr
// (@1833104) under a static std::mutex (@1833080) and builds it with comum::CAppState's constructor and 0, its vptr,
// vota::CTelasVota::GetInst() and fn 6557 over +12. GetInst and the constructor are not written: fn 6557 has no name.
// No record names the class or its file. Its vtable and typeinfo lie in app/vota/eleitor/'s data, after
// cinstrucaovotacaoacessibilidade.cpp's records and right before vota::CFimVotoEleitor's vtable (cfimvotoeleitor.cpp's
// record follows it), which is not that directory's name order: the data allow the class in cfimvotoeleitor.cpp's
// object too. The path, from the class's name, and every member name are chosen; unit 174's fragment has the rest.
class CMostraTelaContinuaVotacao final : public comum::CAppState {
public:
    virtual ~CMostraTelaContinuaVotacao() override;

    static CMostraTelaContinuaVotacao& GetInst();

    virtual void StartState() override;

private:
    CMostraTelaContinuaVotacao();

    static std::mutex s_mutex;
    static std::unique_ptr<CMostraTelaContinuaVotacao> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_form;
};

} // namespace vota
