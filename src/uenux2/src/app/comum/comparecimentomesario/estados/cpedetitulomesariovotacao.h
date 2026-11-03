#pragma once

#include <memory>
#include <mutex>

#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

namespace comum {

// comum::CPedeTituloMesarioVotacao (RTTI: si_class of comum::IPedeTituloMesario; vtable @1594256): overrides slot 9, which returns 1, and the
// destructors. The destructor is out of line: the D0 (fn 3609, a body the three derived classes share) calls the D1 and
// then frees `this`. Its D2 holds the base's inline destructor, so binaryen merges it with the base's, fn 1378, which is
// why slot 0 holds that function. Declared first, it is the key function, a choice. final: fn 10388 deletes the old
// object with a direct call of that D2 and free, no call through the vtable (a `final` destructor in place of the
// class's `final` is the other form that allows it, not linked). A singleton: GetInst keeps the object in a
// static std::unique_ptr (@1909596, destroyed at exit by fn 10366, a thunk into binaryen's fn 3881, which the three
// classes' pointers share) under a static std::mutex (@1909572, by fn 10364). GetInst and the constructor, with
// its form's builder, have no target function of their own: CPedeTituloMesario::StartState (fn 10388) holds them
// inlined by binaryen, the constructor behind a frame of its own. The record of the constructor names the .cpp. The
// line of what the .cpp defines is a choice, but for the constructor's record and the statics' place below GetInst (the
// target's .bss order), and so is the header's path, beside that file.
class CPedeTituloMesarioVotacao final : public IPedeTituloMesario {
public:
    virtual ~CPedeTituloMesarioVotacao() override;

    static CPedeTituloMesarioVotacao& GetInst();

    virtual int Slot9() const override;

private:
    CPedeTituloMesarioVotacao();

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeTituloMesarioVotacao> s_inst;
};

} // namespace comum
