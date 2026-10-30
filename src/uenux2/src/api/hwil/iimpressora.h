#pragma once

// api::IImpressora, the printer. The records of DisableSensors (line 103) and EnableSensors (line 116) name this file;
// everything else in it is the reconstruction's. RTTI gives a class with no base (typeinfo 1583856), and
// api::IImpressoraRelatorios derives from it (iimpressorarelatorios.h). It has no vtable in the target
// (ledger/vtables.json). Its typeinfo follows IImpressoraRelatorios's in that class's key function's object, which
// reads as no key function of its own: here all its virtual members are pure or inline.
//
// The slots are read from simulador::CWasmNullPrinter's vtable (@1530644, 15 slots): the destructor is in slots 10 and
// 11, so ten members are declared before it; slots 4 and 5 hold IImpressoraRelatorios's bodies. Slots 6 and 7 are the
// two defaults the records name, whose fns 8360 and 8341 are thunks of binaryen's merge of the two (fn 6133). The name
// SetStyle comes from the record of the override, and GetColumns is chosen from what slot 5 returns (fn 10880: 38, or
// 19 in style 3). Fn 3875 calls slot 9 with no argument before a report prints, which names nothing. No caller of slots
// 0 to 3 and 8 was found, and their bodies show only wasm types (fns 340, 425, 218). Slot names; return types chosen.

#include <format>

#include "api/hwil/eueprintererror.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

// The record of SetStyle spells this type unqualified, so its scope is chosen, as are the kind of type and its
// enumerators: the target shows only that 0 is refused ("no style") and that 3 gives half the columns (fn 10880).
enum ELPStyle {
    ELP_STYLE_NONE = 0,
    ELP_STYLE_LARGURA_DUPLA = 3,
};

class IImpressora {
public:
    virtual int Slot0() = 0;
    virtual void Slot1(int valor) = 0;
    virtual void Slot2() = 0;
    virtual void Slot3() = 0;
    virtual void SetStyle(ELPStyle style) = 0;
    virtual int GetColumns() = 0;

    // (original lines 39-100: content not recovered)
#line 101
    virtual void DisableSensors(uebyte sensor)
    {
        throw CUePrinterError(EUE_PRINTER_DISABLE_SENSORS_NAO_SUPORTADO, std::format("Not supported ({})", sensor));
    }

    // (original lines 106-113: content not recovered)
#line 114
    virtual void EnableSensors(uebyte sensor)
    {
        throw CUePrinterError(EUE_PRINTER_ENABLE_SENSORS_NAO_SUPORTADO, std::format("Not supported ({})", sensor));
    }

    virtual void Slot8() = 0;
    virtual void Slot9() = 0;

    virtual ~IImpressora() = default;
};

} // namespace api
