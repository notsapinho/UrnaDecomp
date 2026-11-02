#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota::testeteclado {

// vota::testeteclado::CEsperaRetestar (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1546772 [785,
// 1560, 11825, 7480, 1661, 11824, 425, 218, 12061, 11823]): the wait before the keyboard test may run again. It
// overrides StartState (fn 11825), FinishState (fn 11824), which stops the tick and hides the form
// (api::IForm<MEDIA>::Hide, inlined), and the base's slot 9, ProcessTickNaoDesligamento (fn 11823), which goes to
// CTesteTeclado for the tick at +36 once the wait's end has come. The layout is what StartState reads: +28 the form,
// whose slot 2 it calls; +36 a tick id, which it starts on vota::CThreadEleitor and FinishState stops; +40 a count of
// seconds, which it raises by 5 before it sets the end of the wait from it. The D2 (fn 785, CErroTesteTecladoFim's
// body) stores no vptr before it releases +28, so the class is final; the D0 (fn 1560) calls the D2 and frees `this`,
// so the destructor is out of line, declared first as the key function, a choice. A singleton: GetInst (fn 5936) keeps
// the object in a static std::unique_ptr (@1835036, destroyed at exit by fn 11828) under a static std::mutex
// (@1835012, by fn 11827), unit 104's shape, and holds the constructor inlined: the base's constructor with 4
// (EVENTO_TICK), at +28 the form vota::TelaEsperaRepetirTesteTeclado (app/vota/eleitor/comum/ctelasvota.cpp) builds
// over a std::function of the text callback (fn 11826, by its table slot), at +36 the tick CThreadEleitor gives for
// 100, and +40 cleared. +28 holds what vota::GetFormulario (fn 886) returns, so its type is that
// std::shared_ptr<api::IForm<api::IScreen>>; StartState and FinishState call its slot 2 and Hide, which IForm
// declares. The members' names, and +40's signedness, are chosen; so are GetInst, s_inst and s_mutex.
class CEsperaRetestar final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CEsperaRetestar() override;

    static CEsperaRetestar& GetInst();

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessTickNaoDesligamento(uebyte tick) override;

private:
    CEsperaRetestar();

    static std::mutex s_mutex;
    static std::unique_ptr<CEsperaRetestar> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_form;
    uebyte m_tickEspera;
    unsigned int m_segundosEspera;
};

} // namespace vota::testeteclado
