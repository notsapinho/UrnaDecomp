#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CReinicioVotacao (RTTI: si_class of comum::CAppState; vtable @1546628 [244, 387, 11835, 7480, 1661, 218, 425,
// 11834, 425]): it overrides StartState (slot 2, pending) and ProcessInput (slot 7, fn 11834), which reads the form
// (Read(), record cinteractiveform.h:57) and on CONFIRMA logs and goes to vota::CDefineRotaPosReinicio, on BRANCO logs
// and goes to vota::CMaisInformacoes with this state to come back to. The 20-byte object adds a
// std::shared_ptr at +12, which the constructor copies from vota::CTelasVota::GetInst()'s +148 and +152. The destructor
// is out of line: the deleting one (fn 387) calls it and frees `this`, and it stores no vptr, as a final class's (fns
// 244 and 387 are the bodies 49 states share). A singleton: GetInst (fn 5938) keeps the object in a static
// std::unique_ptr (@1834968, destroyed at exit by fn 11837) under a static std::mutex (@1834944, by fn 11836). The
// constructor passes 2 to the base's. src/units/138-uenux2-testeteclado.mk says which of this is evidence and which is
// chosen.
class CReinicioVotacao final : public comum::CAppState {
public:
    virtual ~CReinicioVotacao() override;

    static CReinicioVotacao& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CReinicioVotacao();

    static std::mutex s_mutex;
    static std::unique_ptr<CReinicioVotacao> s_inst;

    CFormInterativoTelaVota m_form;
};

} // namespace vota
