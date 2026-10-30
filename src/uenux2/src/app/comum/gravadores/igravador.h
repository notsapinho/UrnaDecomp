#pragma once

#include "app/comum/gravadores/iresultado.h"

namespace api {
class CFile;
}

namespace comum {

// Recovered: the virtual members. The vtable (@1553648) fills IResultado's two pure slots (fns 11632, 11630), adds
// three slots of its own (fns 11634, 11633, 11631) and a pure one, slot 7, which the recorders' records name
// GravaResultado (cgravadorbu.cpp:484, cgravadorhashes.cpp:112, cgravadorrcsecao.cpp:110). No evidence names slots 2
// to 6: they are named after their slot. Every recorder derives from the class directly (RTTI). It adds no member:
// its constructor (fn 1396, IResultado's inlined) stores only IResultado's and the vptr, and the recorders store
// their own members from +40. The destructor is not declared (implicit): slot 0 holds IResultado's (fn 12090), which
// clang puts in place of an inline destructor with an empty body and no member to destroy, and the recorders'
// destructors inline it and store no vptr of this class (fn 11576; one defined in the class gives the same bytes, one
// defined out of line a call there). The constructor is not reconstructed, so not declared; the five members are
// pending.
class IGravador : public IResultado {
public:
    virtual void Slot2() override;
    virtual void Slot3() override;
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void GravaResultado(api::CFile& arquivo) const = 0;
};

} // namespace comum
