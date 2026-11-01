#pragma once

// comum::CGeradorBUQRCodeVota. Reconstruction notes, not TSE's text. RTTI gives the class, an si_class of
// comum::CGeradorBUQRCode, and its vtable (@1575976) has four slots: the D2 (fn 11244), the D0 (fn 11243), Slot2 (fn
// 11242) and Slot3 (fn 11241). No record names a file of the class: this header's path and cgeradorbuqrcodevota.cpp's are
// chosen by the lower-case rule, and the data agree with an object of its own after cgeradorbuqrcode.cpp's: its vtable
// (@1575976) and typeinfo (@1576000) follow CGeradorBUQRCode's typeinfo (@1575968), in a run of relatorios objects in
// name order (cgeradorbuj.cpp's record @1575808, cgeradorrellistaeleitores.cpp's @1576188).
//
// Recovered: the layout and the destructor. The constructor (fn 5603, not reconstructed) stores, after the base's 416
// bytes, a 16-bit word at +416 from its third argument, zeroes the bytes at +418 and +419, and copies 12 bytes to +420
// from its fourth. Their names and types are chosen beyond those widths; api::CDateTime is a 12-byte value that the
// slot-2 overrider's fields "DTEM:{} " and "HREM:{} " could print. The destructor is out of line: the D0 (fn 11243) calls
// the D2 and then frees this (docs/reference/facts/reading.md R5); the D2 (fn 11244) only calls the base's. Nothing here
// shows whether the class is final: the D2 destroys no member of its own.

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

class CGeradorBUQRCodeVota : public CGeradorBUQRCode {
public:
    ~CGeradorBUQRCodeVota() override;

protected:
    std::string Slot2() const override;
    std::string Slot3(TEleicaoID eleicao) const override;

private:
    ueword m_campo416;
    uebyte m_campo418;
    uebyte m_campo419;
    api::CDateTime m_dataHoraEmissao;
};

} // namespace comum
