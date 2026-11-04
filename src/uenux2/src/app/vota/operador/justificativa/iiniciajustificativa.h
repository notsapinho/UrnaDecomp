#pragma once

#include "app/comum/cappstate.h"
#include "ecourna/api/uetypes.hpp"

namespace vota {

class IConfirmaJustificativa;

// vota::IIniciaJustificativa (RTTI: si_class of comum::CAppState; vtable @1590036 [174, 144, 10587, 7480, 1661, 218,
// 425, 218, 425]), the base of vota::CIniciaJustificativa, CIniciaJustificativaTemporario and
// CIniciaJustificativaTransito, whose vtables hold the same slots. It overrides StartState (slot 2, fn 10587), which goes
// to vota::CJustificativaEfetuada when comum::CJustificador lists the voter's título and to the confirmation state at
// +12 when not (src/units/152-uenux2-app-vota-operador-estados.mk). Slots 0 and 1 hold bodies other
// classes share (fns 174 and 144), which say nothing of where the destructor is defined: it is left implicit, a
// choice. The constructor (fn
// 3624, record iiniciajustificativa.cpp:27, which spells its parameter) passes 0 to the base's, stores its argument at
// +12 before the vptr, as a derived class's member, and throws the vota error 9396 when it is null. The member's name
// is chosen.
class IIniciaJustificativa : public comum::CAppState {
public:
    explicit IIniciaJustificativa(IConfirmaJustificativa* confirma);

    virtual void StartState() override;

protected:
    IConfirmaJustificativa* m_confirma;
};

// No target index: the 16-byte frame vota::CPedeAnoNascimento::ProcessInput (fn 10590) opens on its way to
// CJustificativaEfetuada, a function binaryen inlined into its one caller. It justifies the voter whose identity was
// typed and saves the justification; src/units/283-uenux2-app-vota-operador-justificativa.mk has the evidence for
// its body. That it is a free function (it reads no class state), its name and its file are chosen.
void JustificaEleitor(ueint16 ano);

} // namespace vota
