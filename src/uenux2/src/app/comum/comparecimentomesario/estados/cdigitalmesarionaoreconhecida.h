#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace comum {

// comum::CDigitalMesarioNaoReconhecida (RTTI: si_class of comum::CAppState; vtable @1595240 [244, 387, 1070, 7480,
// 1661, 218, 425, 10322, 425]): it overrides StartState (slot 2, fn 1070, one body in twelve states' slot 2: it shows
// the form at +12) and ProcessInput (slot 7, fn 10322, a thunk into fn 2895, shared with three other states), which
// goes back to asking for the titulo on CONFIRMA. Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49
// final states share: a std::shared_ptr at +12 is all they release, and the bodies read nothing else of the object,
// whose size is unknown. A singleton: GetInst keeps the object in a static std::unique_ptr (@1909876, destroyed at exit
// by fn 10326, a thunk into fn 389) under a static std::mutex (@1909852, by fn 10324). GetInst, its constructor and the
// file's anonymous CNomeMesariosUrnaDS (fn 10323, record cdigitalmesarionaoreconhecida.cpp:27) are not reconstructed.
// src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is chosen.
class CDigitalMesarioNaoReconhecida final : public CAppState {
public:
    virtual ~CDigitalMesarioNaoReconhecida() override;

    static CDigitalMesarioNaoReconhecida& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalMesarioNaoReconhecida();

    static std::mutex s_mutex;
    static std::unique_ptr<CDigitalMesarioNaoReconhecida> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace comum
