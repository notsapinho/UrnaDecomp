#pragma once

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota::testeteclado {

// vota::testeteclado::CEsperaRetestar (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1546772 [785,
// 1560, 11825, 7480, 1661, 11824, 425, 218, 12061, 11823]): the wait before the keyboard test may run again. It
// overrides StartState (fn 11825) and FinishState (fn 11824), which stops the tick and hides the form
// (api::IForm<MEDIA>::Hide, inlined); its slot 9 (fn 11823) is not written, so the base's empty one fills it here. The layout is what StartState reads: +28 the form, whose slot 2 it calls; +36 a tick
// id, which it starts on vota::CThreadEleitor and FinishState stops; +40 a count of seconds, which it raises by 5 before
// it sets the end of the wait from it. The D2 (fn 785, CErroTesteTecladoFim's body) stores no vptr before it releases
// +28, so the class is final; the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of line, declared
// first as the key function, a choice. The constructor and GetInst (fn 5936, which holds it inlined) are not
// reconstructed. The members' names, and +40's signedness, are chosen.
class CEsperaRetestar final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CEsperaRetestar() override;

    virtual void StartState() override;

    virtual void FinishState() override;

private:
    CFormInterativoTelaVota m_form;
    uebyte m_tickEspera;
    unsigned int m_segundosEspera;
};

} // namespace vota::testeteclado
