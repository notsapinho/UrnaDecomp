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

namespace vota {

// vota::CTentativaCapturaDigitalEsgotada (RTTI: si_class of comum::CAppState; vtable @1592280 [244, 387, 1070, 7480,
// 1661, 218, 425, 10461, 425]): the screen vota::CRegistraDigitalOperador::ProcessTick (fn 10451) shows once the byte
// at +32 of that class counts down to 0: "Digital do mesário não capturada", "Eleitor não habilitado para votação" and
// "CONFIRMA: prosseguir". It overrides StartState (slot 2, fn 1070, one body in twelve states' slot 2: it shows the
// form at +12) and ProcessInput (slot 7, fn 10461, a thunk into binaryen's fn 2295, the body it shares with
// vota::CIdentidadeInvalida's and three other states'), which goes to vota::CPedeIdentidade on CONFIRMA. The destructor
// is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it releases. A
// singleton: vota::CRegistraDigitalOperador::ProcessTick (fn 10451) holds GetInst and the constructor inlined: after
// the test of s_inst, the 20-byte new and then a 64-byte frame of the constructor's own, where it passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor, stores the vptr and builds the form in place
// (AddLed, AddBeep(1), the three texts and AddInputControl; ctentativacapturadigitalesgotada.cpp's MontaTela, an
// internal function clang inlines into its one caller). The statics are @1909092 (the std::unique_ptr) and @1909068
// (the std::mutex), whose exit destructors are fns 10463 and 10462. GetInst, the constructor and the statics are
// written; their lines, the builder's name and linkage are chosen. The file is named after the class, in the
// directory of the objects around its vtable, a choice (src/units/278-uenux2-cvalidaidentidade.mk says why), and it
// links ahead of cregistradigitaloperador.cpp, as its vtable lies ahead of that class's in the data
// (src/units/221-uenux2-app-comum-constructors.mk has the measurement).
class CTentativaCapturaDigitalEsgotada final : public comum::CAppState {
public:
    virtual ~CTentativaCapturaDigitalEsgotada() override;

    static CTentativaCapturaDigitalEsgotada& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CTentativaCapturaDigitalEsgotada();

    static std::unique_ptr<CTentativaCapturaDigitalEsgotada> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
