#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CAplicacaoEncerrada (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1542024 [785, 1560,
// 12058, 7480, 1661, 218, 425, 218, 12061, 425]): the state that tells the voting is over. It overrides StartState (fn
// 12058): it logs "Votação encerrada" and calls slot 2 of the form at +28, which the constructor copies from
// vota::CTelasVota::GetInst()'s +36 and +40. The D2 (fn 785, CErroTesteTecladoFim's body) stores no vptr before it
// releases +28, so the class is final; the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of line,
// declared first as the key function, a choice. A singleton: GetInst (fn 3877) keeps the object in a static
// std::unique_ptr (@1833820, destroyed at exit by fn 12060) under a static std::mutex (@1833796, by fn 12059), and
// builds it with the constructor, inlined there: the base's constructor with 0, then the copy of CTelasVota's +36. The
// exit destructor of s_inst is a member of the body binaryen merges for every static std::unique_ptr whose class's D2
// is fn 785 (fn 1564). The member's name, the statics' names and this header's path are chosen.
class CAplicacaoEncerrada final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CAplicacaoEncerrada() override;

    static CAplicacaoEncerrada& GetInst();

    virtual void StartState() override;

private:
    CAplicacaoEncerrada();

    static std::mutex s_mutex;
    static std::unique_ptr<CAplicacaoEncerrada> s_inst;

    CFormInterativoTelaVota m_form;
};

} // namespace vota
