#pragma once

#include "api/util/cdatetime.h"
#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CVerificaHorarioZeresima (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1545856 [785, 1560,
// 11871, 7480, 1661, 11868, 425, 11869, 12061, 11870]): the wait for the time set for the zerésima. It overrides
// StartState (fn 11871, record :64, pending), FinishState (fn 11868) and ProcessInput (fn 11869, pending). Its slot 9 is
// ProcessTickNaoDesligamento(uebyte) by its record (fn 11870, :80), which the base's header names otherwise: it is not
// written, so the base's empty one fills the slot here. The layout is what GetInst (fn 5947, not reconstructed: the
// constructor calls the base's, which this tree does not declare) stores: +28 the form, from
// vota::CTelasVota::GetInst()'s +20 and +24; +36 the time, from comum::CConfiguracaoEleicao's +544; +48 the id of a
// 2000-ms tick added stopped, which FinishState stops. The D2 (fn 785, CErroTesteTecladoFim's body) stores no vptr before
// it releases +28, so the class is final; the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of
// line, declared first as the key function, a choice. The members' names are chosen.
class CVerificaHorarioZeresima final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CVerificaHorarioZeresima() override;

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

private:
    CFormInterativoTelaVota m_form;
    api::CDateTime m_horario;
    uebyte m_tickHorario;
};

} // namespace vota
