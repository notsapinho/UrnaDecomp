#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CMostraQRCodeCertificado (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1542480 [785, 1560,
// 12040, 7480, 1661, 218, 425, 12038, 12061, 425]): it overrides StartState (slot 2, fn 12040, pending: it calls fns
// 502, 576, 653 and 2782, which have no body here) and ProcessInput (slot 7, fn 12038, record line 39), which throws
// unless the form holds one input field and goes back to CMostraQRCodeBU on CORRIGE. The destructors are
// CMostraQRCodeBU's bodies (fns 785 and 1560): final, and out of line (docs/reference/facts/reading.md R4, R5). A
// singleton: GetInst, inlined into CMostraQRCodeBU::ProcessInput (fn 12051), keeps the object in a static
// std::unique_ptr (@1833876, destroyed at exit by fn 12042) under a static std::mutex (@1833852, by fn 12041), and
// builds it as the base's constructor with 2 and a null +28, the form. Chosen: the member's name, the names GetInst,
// s_inst and s_mutex, the destructor declared first. This header's path is chosen, beside the .cpp the record names.
class CMostraQRCodeCertificado final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CMostraQRCodeCertificado() override;

    static CMostraQRCodeCertificado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CMostraQRCodeCertificado();

    static std::mutex s_mutex;
    static std::unique_ptr<CMostraQRCodeCertificado> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
