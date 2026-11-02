#pragma once

#include <cstddef>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/cinteractiveform.h"
#include "api/gui/ctextbox.h"
#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota::testeteclado {

// vota::testeteclado::CTesteTeclado (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1547132 [2868,
// 11806, 11805, 7480, 1661, 218, 425, 11804, 12061, 425]): the keyboard test itself. It overrides StartState (fn 11805,
// records ctesteteclado.cpp:38 and :42, written) and ProcessInput (fn 11804, records :50, :60 and :81, pending), and the
// destructors. The D2 (fn 2868) stores no vptr before it destroys +48, +36 and +28, so the class is final; the D0 (fn
// 11806) calls the D2 and frees `this`, so the destructor is out of line, declared first as the key function, a choice.
// A singleton: GetInst (fn 3855) builds the 68-byte object over the base's constructor (fn 1285) with 2
// (EVENTO_ENTRADA), clears +28 to +68, makes +36 an empty tree, and keeps it in a static std::unique_ptr (@1835148,
// destroyed at exit by fn 11808) under a static std::mutex (@1835124, by fn 11807), unit 104's shape. The layout is
// what the D2, GetInst, StartState and vota::testeteclado::CBase::ProcessInput (fn 11874) read: +28 the form, into
// which StartState moves what vota::GetFormularioInterativo (fn 576) returns, a CFormInterativoTelaVota, and whose slot
// 2 it calls; +36 a std::map whose key is a std::string (StartState looks it up with fn 163, the std::string-keyed
// map's find) and whose value holds a byte at +12 and a std::shared_ptr at +16: StartState moves in the map
// vota::TelaTesteTeclado builds, of each key's char and api::CTextBox (std::make_shared<api::CTextBox> of 80 bytes),
// and passes the found box to api::CTextBox::SetStatus (fn 940, which stores at +44, CTextBox's status) with 1;
// ProcessInput widens the byte signed, so a char; +48 a std::vector<std::string> (the D2's loop frees 12-byte strings;
// StartState moves in the generator's sequence and indexes it with +60 through fn 3854); +60 that index, which
// StartState sets to 0; +64 what CBase::ProcessInput stores from its slot 11, GetEstadoPassouNoTeste, before it moves
// to this state. Chosen: every member's name, the map's mapped type being a std::pair (the shared_ptr's CTextBox is
// what StartState calls fn 940 on), size_t for +60, the setter of +64 and its name, GetInst's name and the statics'
// (unit 104's convention), and this header's path, beside ctesteteclado.cpp. The two api/gui includes are the members'
// types, here so that ctesteteclado.cpp keeps StartState on its record lines (src/units/217-uenux2-ctesteteclado.mk).
class CTesteTeclado final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CTesteTeclado() override;

    static CTesteTeclado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

    void SetEstadoPassouNoTeste(comum::CAppState* estado) { m_pEstadoPassouNoTeste = estado; }

private:
    CTesteTeclado();

    static std::mutex s_mutex;
    static std::unique_ptr<CTesteTeclado> s_inst;

    CFormInterativoTelaVota m_form;
    std::map<std::string, std::pair<char, std::shared_ptr<api::CTextBox>>> m_teclas;
    std::vector<std::string> m_sequencia;
    size_t m_indice;
    comum::CAppState* m_pEstadoPassouNoTeste;
};

} // namespace vota::testeteclado
