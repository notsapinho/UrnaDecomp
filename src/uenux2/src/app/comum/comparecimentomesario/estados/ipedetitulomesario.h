#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IScreenMT;
class IInputMT;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace comum {

// comum::IPedeTituloMesario (RTTI: si_class of comum::CAppState; vtable @1595576 [1378, 325, 10314, 7480, 1661, 218,
// 425, 10313, 425, 12143]): the base of comum::CPedeTituloMesarioInicial, CPedeTituloMesarioFinal and
// CPedeTituloMesarioVotacao, abstract (slot 1 is the trap 325, slot 9 __cxa_pure_virtual). It overrides the
// destructors, StartState (slot 2, fn 10314) and ProcessInput (slot 7, fn 10313, pending); slot 2's name is
// comum::CAppState's. A record in ipedetitulomesario.cpp (line 30, the anonymous GetControlador inlined into fn 10313)
// names the file; this header's path is chosen, beside it. The vtable and typeinfo lie in that file's data, before that
// record and after the derived classes' objects, so a member is out of line there: a class with no key function would
// have its vtable copied in its first user's object. StartState, declared first, is that key function, a choice: no
// evidence says which member it is. The destructor is not: the derived classes' D0 (fn 3609) calls their D1 and frees
// `this`, so their destructors are out of line, and their slot 0 still holds fn 1378. A derived D2 that holds this D2's
// body, which clang inlines only when the destructor is inline, is what binaryen merges with this one; over an
// out-of-line destructor it would be a body of one call, as fn 884 is over fn 1035. It is left implicit: in the class,
// `= default` with or without `inline` gives the same fns 1378 and 3609 (src/units/97-uenux2-cvotacaostateaudio.mk).
//
// The layout is what the constructor (fn 3608) stores: +12 and +20 two std::shared_ptr it takes by value (it copies
// their four words and writes nothing back). +12 is the operator's form: fn 10313 reads it through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1595652). +20 is the form
// on the voter's terminal: fn 10388 builds it with fn 1255 ("REGISTRO DE MESÁRIOS"), which reaches fn 5550 through fns
// 11140 and 6117; 5550's control block is __shared_ptr_pointer<api::IForm<api::IScreen>*, ...> (vptr 1578144). Fn 3608
// passes comum::CAppState::EVENTO_ENTRADA (2) to the base constructor. Slot 9's name and result type are chosen: the
// derived classes return 1 (Inicial, Votacao, fn 434) and 2 (Final, fn 2254), and fn 10313 only passes the value on to
// fn 2738. The member and parameter names are not in the target.
class IPedeTituloMesario : public CAppState {
public:
    virtual void StartState() override;

    virtual void ProcessInput() override;

    virtual int Slot9() const = 0;

protected:
    IPedeTituloMesario(std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> form,
                       std::shared_ptr<api::IForm<api::IScreen>> formEleitor);

private:
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

} // namespace comum
