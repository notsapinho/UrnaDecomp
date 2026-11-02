#pragma once

// vota::testeteclado::impl::CGeradorTeclasAleatorio (RTTI: si_class of IGeradorTeclas; vtable @1547288 [174, 144,
// 11803]). The default instance IGeradorTeclas::GetInst creates: GetInst stores this vptr (@1547296) in a 4-byte
// object, and the record's column fits the macro's spelling of the two names (src/units/217-uenux2-ctesteteclado.mk).
// Slot 2 (fn 11803) shuffles the keys it is given with a std::mt19937 it seeds once from a std::random_device, a
// function-local static (@1835152, guard @1837652). The destructors are bodies binaryen shares (174 and 144); with the
// implicit destructor our link merges this class's into twins (their symbols are not in names.tsv). GeraSequencia is
// the key function, out of line in ctesteteclado.cpp, whose data hold the vtable after CTesteTeclado's typeinfo. This
// header's path is chosen, the class's name in lower case beside ctesteteclado.cpp; not final is a choice.

#include <string>
#include <vector>

#include "app/vota/eleitor/iniciovotacao/testeteclado/igeradorteclas.h"

namespace vota::testeteclado::impl {

class CGeradorTeclasAleatorio : public IGeradorTeclas {
public:
    std::vector<std::string> GeraSequencia(std::vector<std::string> teclas) override;
};

} // namespace vota::testeteclado::impl
