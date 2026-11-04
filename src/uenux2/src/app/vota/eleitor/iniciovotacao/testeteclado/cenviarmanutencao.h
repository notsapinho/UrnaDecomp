#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/comum/ctelascargo.h"

namespace vota::testeteclado {

// vota::testeteclado::CEnviarManutencao (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1546980
// [785, 1560, 3857, 7480, 1661, 218, 425, 11812, 12061, 425]): asks whether the urn goes to maintenance after a failed
// keyboard test. Slots 0 to 2 and 8 are vota::testeteclado::CErroTesteTecladoFim's bodies, as for
// vota::testeteclado::CTesteFalhou, so the class has that shape (final, destructor out of line, a std::shared_ptr at
// +28 in a 36-byte object); ProcessInput is fn 11812. A singleton: CTesteFalhou::ProcessInput (fn 11809), its one
// caller, holds GetInst and the constructor inlined; GetInst keeps the object in a static std::unique_ptr (@1835092)
// under a static std::mutex (@1835068), whose exit destructors are fns 11814 and 11813. The constructor passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's and builds the form straight into +28. No record names the class
// or its file: this header's path and the .cpp's and every member name are chosen; src/units/217-uenux2-ctesteteclado.mk
// has the rest.
class CEnviarManutencao final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CEnviarManutencao() override;

    static CEnviarManutencao& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEnviarManutencao();

    static std::unique_ptr<CEnviarManutencao> s_inst;
    static std::mutex s_mutex;

    CFormInterativoTelaVota m_form;
};

} // namespace vota::testeteclado
