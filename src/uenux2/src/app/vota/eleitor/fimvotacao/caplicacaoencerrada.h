#pragma once

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CAplicacaoEncerrada (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1542024 [785, 1560,
// 12058, 7480, 1661, 218, 425, 218, 12061, 425]): the state that tells the voting is over. It overrides StartState (fn
// 12058): it logs "Votação encerrada" and calls slot 2 of the form at +28, which the constructor copies from
// vota::CTelasVota::GetInst()'s +36 and +40 (fn 3877, GetInst, not reconstructed: the constructor calls the base's,
// which this tree does not declare). The D2 (fn 785, CErroTesteTecladoFim's body) stores no vptr before it releases
// +28, so the class is final; the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of line, declared
// first as the key function, a choice. The member's name and this header's path are chosen.
class CAplicacaoEncerrada final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CAplicacaoEncerrada() override;

    virtual void StartState() override;

private:
    CFormInterativoTelaVota m_form;
};

} // namespace vota
