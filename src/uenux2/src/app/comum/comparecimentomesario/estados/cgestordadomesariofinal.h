#pragma once

#include <memory>
#include <mutex>

#include "app/comum/comparecimentomesario/estados/igestordadomesario.h"

namespace comum {

// comum::CGestorDadoMesarioFinal (RTTI: si_class of comum::IGestorDadoMesario; vtable @1595108 [174, 144, 10337, 7480,
// 1661, 218, 425, 218, 425, 2254]): it overrides slot 9 alone, which returns 2 (fn 2254, one body in 5 slots of the
// target's table), and adds no data member, so the object is the base's 12 bytes and slots 0 and 1 hold the destructors
// the states with no member share (fns 174 and 144). A singleton: GetInst keeps the object in a static std::unique_ptr
// (@1909820, destroyed at exit by fn 10331) under a static std::mutex (@1909796, by fn 10330); it has no target
// function of its own, as binaryen inlined it into its one caller, comum::CGestorDadoMesario::StartState (fn 10327).
// final: fn 10327 frees the old object with no call through the vtable. The constructor value-initializes the base: fn
// 10327 clears the base subobject's 11 bytes, at its alignment, before the base's constructor runs. It is out of line
// in the .cpp, as unit 104's are: fn 10327 stores what operator new returned and takes the vptr store's address from
// the base constructor's result. src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which
// is chosen.
class CGestorDadoMesarioFinal final : public IGestorDadoMesario {
public:
    static CGestorDadoMesarioFinal& GetInst();

    virtual int Slot9() const override;

private:
    CGestorDadoMesarioFinal();

    static std::mutex s_mutex;
    static std::unique_ptr<CGestorDadoMesarioFinal> s_inst;
};

} // namespace comum
