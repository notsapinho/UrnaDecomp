#pragma once

#include "app/comum/cappstate.h"

namespace comum {

class IControladorRegistraMesarios;

// comum::IGestorDadoMesario (RTTI: si_class of comum::CAppState, typeinfo @1594976): the base of
// comum::CGestorDadoMesarioInicial, CGestorDadoMesarioVotacao and CGestorDadoMesarioFinal, which share its StartState
// (slot 2, fn 10337, pending: src/units/135-uenux2-comum-mesario-estados-pending.cpp) and return 1, 1 and 2 from slot
// 9. A record in igestordadomesario.cpp (line 65, GetControlador, inlined into fn 10337) names the file; this header's
// path is chosen, beside it. ledger/vtables.json lists no vtable of the class, and its typeinfo follows that record in
// the data, CGestorDadoMesarioInicial's vtable right after it: read as a typeinfo emitted with an out-of-line member of
// that file (docs/reference/facts/reading.md R6), StartState, which is there. In our link nothing stores its vptr, as
// the derived constructors store their own over it, so wasm-ld drops the vtable the pending object emits and keeps the
// typeinfo (the link map has _ZTIN5comum18IGestorDadoMesarioE and no _ZTV). The constructor is the implicit one: fn
// 10327 clears the 11 bytes of this base subobject before calling CAppState's constructor (fn 224) with 0, the
// value-initialization of a base whose default constructor is not user-provided (`= default` gives the same bytes).
// Slot 9's name and type are those of comum::IPedeTituloMesario's slot 9, which returns the same values in the same
// three phases: chosen.
class IGestorDadoMesario : public CAppState {
public:
    virtual void StartState() override;

    virtual int Slot9() const = 0;

private:
    const IControladorRegistraMesarios& GetControlador();
};

} // namespace comum
