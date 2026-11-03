#pragma once

#include <memory>
#include <string>

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
// destructors, StartState (slot 2, fn 10314) and ProcessInput (slot 7, fn 10313); slot 2's name is
// comum::CAppState's. A record in ipedetitulomesario.cpp (line 30, the anonymous GetControlador inlined into fn 10313)
// names the file; this header's path is chosen, beside it. The vtable and typeinfo lie in that file's data, before that
// record and after the derived classes' objects, so a member is out of line there: a class with no key function would
// have its vtable copied in its first user's object. StartState, declared first, is that key function, a choice: no
// evidence says which member it is. The destructor is not: the derived classes' D0 (fn 3609) calls their D1 and frees
// `this`, so their destructors are out of line, and their slot 0 still holds fn 1378. A derived D2 that holds this D2's
// body, which clang inlines only when the destructor is inline, is what binaryen merges with this one; over an
// out-of-line destructor in another object it would be a body of one call, as fn 884 is over fn 1035. Left implicit: in the class,
// `= default` with or without `inline` gives the same fns 1378 and 3609 (src/units/97-uenux2-cvotacaostateaudio.mk).
//
// The layout is what the constructor (fn 3608) stores: +12 and +20 two std::shared_ptr it takes by value (it copies
// their four words and writes nothing back). +12 is the operator's form: fn 10313 reads it through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1595652). +20 is the form
// on the voter's terminal: fn 10388 builds it with fn 1255 ("REGISTRO DE MESÁRIOS", TelaEleitorRegistroMesarios below), which
// reaches fn 5550 through fns 11140 and 6117; 5550's control block is __shared_ptr_pointer<api::IForm<api::IScreen>*,
// ...> (vptr 1578144). Fn 3608 passes comum::CAppState::EVENTO_ENTRADA (2) to the base constructor. Slot 9's name and
// result type are chosen: the derived classes return 1 (Inicial, Votacao, fn 434) and 2 (Final, fn 2254), and fn 10313
// only passes the value on to fn 2738. The member and parameter names are not in the target.
class IPedeTituloMesario : public CAppState {
public:
    virtual void StartState() override;

    virtual void ProcessInput() override;

    virtual int Slot9() const = 0;

protected:
    IPedeTituloMesario(std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> form,
                       std::shared_ptr<api::IForm<api::IScreen>> formEleitor);

private:
    // Whether the register holds the mesario with this formatted titulo in this state's period (Slot9): fn 10313 holds it
    // inlined by binaryen, a 48-byte frame of its own that opens before CRegistradorMesario::GetInst's call and calls
    // Slot9 inside, so it takes `this`; clang leaves it a call in the object (src/units/71-uenux2-celeitorvotounaovotou.mk).
    // Its name, its being a const member and its parameter's type are chosen.
    bool MesarioJaRegistrado(const std::string& titulo) const;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

// The voter's screen of the registration: comum::TelaRegistroMesarios's code (cregistrarmesarios.h) a second time; target
// fn 1255 is the one body of both. That the source had two functions is read from fn 11140
// (api::CFormBuilder::GetForm(const std::string &)): fn 1255 is its one caller and it is in no table slot, yet it is out
// of line, and binaryen inlines a function with one call site and no slot (docs/reference/facts/tool-traps.md X1).
// src/units/247-uenux2-cregistrarmesarios.mk has the measurements. What the second copy is, measured in the whole link
// (pnpm wasm score of fn 10388, and build/out/wasm-map/vota_web/names.tsv for 11140):
// - the three derived classes' constructors, which fn 10388 holds, call fn 1255 in their base's initializer with no
//   vptr store before it; a member of this class called there uses `this`, and clang then stores the derived class's
//   vptr before the base initializer (wasm-objdump -d of cpedetitulomesarioinicial.cpp.o: the store of
//   _ZTVN5comum25CPedeTituloMesarioInicialE+8 opens the constructor; 10388 at 195 over 2070 rows, 9 inserted);
// - a free function with TelaRegistroMesarios's wasm type is merged with it by binaryen before it inlines, and 11140,
//   left with one caller, is inlined (it leaves names.tsv, and splat-symbols drops its line and 6117's);
// - a delegating constructor that calls the member gives no vptr store but a second copy of each argument (24 inserted
//   rows).
// A function of comum that takes a parameter its body does not read gives the target's rows (186 over 2061, all
// operand-only, the statics' addresses) and keeps 11140: binaryen's dead-argument elimination drops the parameter after
// the first merge pass. So the second copy reads no object and has a parameter; which one is not in the target. Chosen:
// its name, the parameter's type and name, the values the constructors pass (their slot 9's), its declaration here and
// its definition in ipedetitulomesario.cpp, and that those three constructors are its callers.
std::shared_ptr<api::IForm<api::IScreen>> TelaEleitorRegistroMesarios(int periodo);

} // namespace comum
