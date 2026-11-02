#pragma once

#include "app/comum/cappstate.h"

namespace vota {

// vota::CSincronismoEleitor (RTTI: si_class of comum::CAppState; vtable @1534076 [174, 144, 7178, 7480, 1661, 218, 7181,
// 218, 425]): it overrides StartState (slot 2, fn 7178) and ProcessKey (slot 6, fn 7181, pending:
// src/units/192-uenux2-app-vota-estados-sincronismo-pending.cpp says what it waits for). Its singleton lives in fn 4454,
// which holds GetInst and the constructor inlined: it allocates 12 bytes, passes comum::CAppState::EVENTO_TECLA (1) to
// the base's constructor and stores only the vptr, keeps the object in a static std::unique_ptr (@1833160) under a static
// std::mutex (@1833136), and frees an old object with no call through the vtable, as for a final class. GetInst, the
// constructor and the statics are not written here: the target has no function of GetInst's own, and the statics' only
// reader besides their exit destructors (fns 7195 and 7187) is fn 4454, which is not written. The destructors are the bodies 174
// and 144 the class shares with the base, an implicit destructor.
//
// No record names the class: the path is chosen. Its vtable and typeinfo lie in the data between
// app/vota/eleitor/cfimvotoeleitor.cpp's record (1534048) and app/vota/eleitor/csincronismovotoeleitor.cpp's (1534132),
// where csincronismoeleitor.cpp, the class's name in lower case, sorts in that directory's name order; a place at the end
// of either neighbour's object fits the data too.
class CSincronismoEleitor final : public comum::CAppState {
public:
    virtual void StartState() override;

    virtual void ProcessKey(uebyte tecla) override;
};

} // namespace vota
