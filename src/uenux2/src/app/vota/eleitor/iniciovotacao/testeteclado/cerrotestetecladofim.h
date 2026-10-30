#pragma once

#include <memory>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota::testeteclado {

// vota::testeteclado::CErroTesteTecladoFim (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1546920
// [785, 1560, 3857, 7480, 1661, 218, 425, 218, 12061, 425]): overrides StartState (fn 3857, one body with
// CEnviarManutencao's and CTesteFalhou's) and the destructors. The D2 (fn 785) stores no vptr before it releases +32,
// so the class is final; the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of line. Declared
// first, it is the key function, a choice. +28 is a std::shared_ptr to what StartState calls slot 2 of: the type is
// chosen, the one comum::IPedeTituloMesario's form has. The file, this header's path and the member's name are chosen.
class CErroTesteTecladoFim final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CErroTesteTecladoFim() override;

    virtual void StartState() override;

private:
    std::shared_ptr<api::IForm<api::IScreen>> m_form;
};

} // namespace vota::testeteclado
