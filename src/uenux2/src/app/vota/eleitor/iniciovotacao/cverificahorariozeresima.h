#pragma once

#include <memory>
#include <mutex>

#include "api/util/cdatetime.h"
#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CVerificaHorarioZeresima (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1545856 [785, 1560,
// 11871, 7480, 1661, 11868, 425, 11869, 12061, 11870]): the wait for the time set for the zerésima. It overrides
// StartState (fn 11871, record :64), FinishState (fn 11868), ProcessInput (fn 11869, pending) and
// ProcessTickNaoDesligamento (fn 11870, record :80), the base's slot 9. The layout is what GetInst (fn 5947) stores: +28
// the form, from vota::CTelasVota::GetInst()'s +20 and +24; +36 the time, from comum::CConfiguracaoEleicao's +544; +48
// the id of a 2000-ms tick added stopped, which StartState starts and FinishState stops. The D2 (fn 785,
// CErroTesteTecladoFim's body) stores no vptr before it releases +28, so the class is final; the D0 (fn 1560) calls the
// D2 and frees `this`, so the destructor is out of line, declared first as the key function, a choice. A singleton:
// GetInst keeps the object in a static std::unique_ptr (@1834688, destroyed at exit by fn 11873) under a static
// std::mutex (@1834664, by fn 11872), unit 104's shape; the constructor passes 6 to the base's. The members' names are
// chosen.
class CVerificaHorarioZeresima final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CVerificaHorarioZeresima() override;

    static CVerificaHorarioZeresima& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTickNaoDesligamento(uebyte tick) override;

private:
    CVerificaHorarioZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CVerificaHorarioZeresima> s_inst;

    CFormInterativoTelaVota m_form;
    api::CDateTime m_horario;
    uebyte m_tickHorario;
};

} // namespace vota
