#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/comum/ctelascargo.h"

namespace vota::testeteclado {

// vota::testeteclado::CTesteFalhou (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1547056 [785,
// 1560, 3857, 7480, 1661, 218, 425, 11809, 12061, 425]): the screen of a wrong key in the keyboard test. Slots 0 to 2
// and 8 are vota::testeteclado::CErroTesteTecladoFim's bodies (fns 785, 1560, 3857 and 12061), so the class shares its
// shape: final, the destructor out of line, a std::shared_ptr at +28 (the form StartState shows) in a 36-byte object.
// ProcessInput is fn 11809. A singleton: vota::testeteclado::CTesteTeclado::ProcessInput (fn 11804), its one caller,
// holds GetInst and the constructor inlined; GetInst keeps the object in a static std::unique_ptr (@1835120) under a
// static std::mutex (@1835096), whose exit destructors are fns 11811 and 11810. The constructor passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and builds the form straight into +28 (fn 576 writes it there).
// No record names the class or its file: this header's path and the .cpp's, beside the other states of
// testeteclado/, and every member name are chosen; src/units/217-uenux2-ctesteteclado.mk has the rest.
class CTesteFalhou final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CTesteFalhou() override;

    static CTesteFalhou& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CTesteFalhou();

    static std::unique_ptr<CTesteFalhou> s_inst;
    static std::mutex s_mutex;

    CFormInterativoTelaVota m_form;
};

} // namespace vota::testeteclado
