#pragma once

// api::CInputFieldMT: RTTI gives an si_class of IInputField<IScreenMT>, and its vtable (@1587484) holds IInputField's
// slots but slot 2, Draw (fn 10726, in app/vota/operador/outrasopcoes/cinputfieldmt.cpp;
// src/units/146-uenux2-cinputfieldmt.mk says why there). The path of this header is chosen, beside iinputfield.h.
//
// The layout comes from fn 1151, the one function that stores the vptr (`/usr/bin/grep -rlE 'i32\.const
// 1587492($|[^0-9])' build/out/splat/pieces/asm` prints only its piece), and from Draw: a 72-byte object; at +64 the
// SPoint 1151 copies from its argument and Draw passes to IScreenMT::ShowText; at +68 a byte 1151 sets to 0 and Draw
// tests against 1, drawing a '*' for each character when it is set. The member names, the bool type of +68 and the
// constructor's parameter for it with its default are chosen.
//
// The constructor is 1151's code inlined: IInputField's constructor (fn 3673) with the validation, the length and the
// confirm-on-full flag 1151 passes on, and false, true, false, false, which 3673 holds as constants because every
// caller passes them (binaryen's dead-argument elimination). That this class passes them, and not 1151, is chosen. 1151
// is not reconstructed, so no function of this link holds the constructor and nothing has compared it with the target.
//
// Draw is declared out of line, so it is the key function and cinputfieldmt.cpp emits the vtable. Evidence: the
// target's vtable lies in the data away from the control block that 1151 instantiates
// (__shared_ptr_pointer<CInputFieldMT*, ...> @1588176, with other classes' data between), so the TU that emitted the
// vtable is not 1151's, and since 1151 alone stores the vptr, that TU builds no CInputFieldMT. A reading: it emitted
// the vtable with the key function, and Draw, the class's one member of its own, is that function. In use band 1
// (ledger/ordinals.tsv), fn 10726 is next to fn 10727, vota::CTituloEncerramentoInvalido's slot 7, and four indices
// from 10722 and 10721, vota::CPedeTituloEncerramento's slots 2 and 7: the two classes whose data surround the vtable.
// The destructor is implicit: slot 0 is IInputField's D2 (fn 5517), and slot 1 is fn 3672, the D0 that
// CInputFieldControl<IScreenMT>'s vtable holds too, since neither class adds a member that needs destroying.

#include <cstddef>
#include <memory>

#include "api/gui/iinputfield.h"
#include "api/gui/iinputvalidation.h"
#include "api/gui/primitives.h"

namespace api {

class IScreenMT;

class CInputFieldMT : public IInputField<IScreenMT> {
public:
    CInputFieldMT(const std::shared_ptr<IInputValidation>& validation, size_t length, bool confirmaAoCompletar,
                  const SPoint& posicao, bool mascarado = false)
        : IInputField<IScreenMT>(validation, length, confirmaAoCompletar, false, true, false, false),
          m_posicao(posicao),
          m_mascarado(mascarado)
    {
    }

    void Draw(IScreenMT& screen) const override;

private:
    SPoint m_posicao;
    bool m_mascarado;
};

} // namespace api
