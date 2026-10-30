#pragma once

#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

namespace comum {

// comum::CPedeTituloMesarioInicial (RTTI: si_class of comum::IPedeTituloMesario; vtable @1593952): overrides slot 9, which returns 1, and the
// destructors. The destructor is out of line: the D0 (fn 3609, a body the three derived classes share) calls the D1 and
// then frees `this`. Its D2 holds the base's inline destructor, so binaryen merges it with the base's, fn 1378, which is
// why slot 0 holds that function. Declared first, it is the key function, a choice. The record of the constructor names
// the .cpp; the constructor is inlined into fn 10388 and not reconstructed, so its line stays blank there. The line of
// what the .cpp defines is a choice, and so is the header's path, beside that file.
class CPedeTituloMesarioInicial : public IPedeTituloMesario {
public:
    virtual ~CPedeTituloMesarioInicial() override;

    virtual int Slot9() const override;
};

} // namespace comum
