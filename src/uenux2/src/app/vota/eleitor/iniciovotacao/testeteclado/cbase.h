#pragma once

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota::testeteclado {

// vota::testeteclado::CBase (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1545768 [1559, 325,
// 11875, 7480, 1661, 218, 425, 11874, 12061, 425, 12143, 12143, 12143]): the base of CPreZeresima and CRetomada, the two
// states that offer the keyboard test. Abstract: slot 1 is the trap 325, and slots 10 to 12 are pure. StartState (fn
// 11875) asks slot 10 for the form, keeps it at +28 and calls its slot 2. ProcessInput (fn 11874, pending) reads the
// keyboard through the form and moves to slot 12's state, or to CTesteTeclado after storing slot 11's state in it.
// Slot 11 is GetEstadoPassouNoTeste by CPreZeresima's record (cprezeresima.cpp:56); the names of slots 10 and 12 are
// chosen from those uses. Fn 1559, the D2, stores this class's vptr and releases +28, the only member. CPreZeresima's
// slot 0, its own D2 out of line in cprezeresima.cpp, is this same body, so this destructor is not out of line in
// another object (a reading: such a one stays a call there at -fPIC); implicit is a choice over `inline`. The
// constructor (fn 5948, passing 2 to the base's) is not reconstructed: it calls the base's, which this tree does not
// declare. StartState, the first non-inline virtual member, is the key function, a choice. This header's path and the
// member's name are chosen.
class CBase : public CEstadoComDesligamentoAutomatico {
public:
    virtual void StartState() override;

    virtual void ProcessInput() override;

protected:
    virtual CFormInterativoTelaVota GetTela() = 0;

    virtual comum::CAppState* GetEstadoPassouNoTeste() = 0;

    virtual comum::CAppState* GetEstadoSemTeste() = 0;

    CFormInterativoTelaVota m_form;
};

} // namespace vota::testeteclado
