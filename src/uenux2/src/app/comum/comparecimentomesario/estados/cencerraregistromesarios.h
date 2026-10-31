#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IScreenMT;
class IInputMT;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace comum {

class IControladorRegistraMesarios;

// comum::CEncerraRegistroMesarios (RTTI: si_class of comum::CAppState; vtable @1593880 [448, 765, 10380, 7480, 1661,
// 218, 425, 218, 425]): it overrides StartState (slot 2, fn 10380), which asks the controller where the registration of
// mesarios goes next. A singleton: GetInst (fn 5388) keeps the object in a static std::unique_ptr (@1909512, destroyed
// at exit by fn 10382) under a static std::mutex (@1909488, by fn 10381); the constructor, inlined there, passes 0 to
// the base's and leaves both forms empty. The 28-byte object and its two forms are those of the 19 states over the
// destructors 448 and 765: src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is
// chosen.
class CEncerraRegistroMesarios final : public CAppState {
public:
    virtual ~CEncerraRegistroMesarios() override;

    static CEncerraRegistroMesarios& GetInst();

    virtual void StartState() override;

private:
    CEncerraRegistroMesarios();

    void DefineProximoEstado();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CEncerraRegistroMesarios> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

} // namespace comum
