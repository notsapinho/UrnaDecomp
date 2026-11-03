#pragma once

// comum::CGeradorBUQRCodeVota. Reconstruction notes, not TSE's text. RTTI gives the class, an si_class of
// comum::CGeradorBUQRCode, and its vtable (@1575976) has four slots: the D2 (fn 11244), the D0 (fn 11243), Slot2 (fn
// 11242) and Slot3 (fn 11241). No record names a file of the class: this header's path and cgeradorbuqrcodevota.cpp's are
// chosen by the lower-case rule, and the data agree with an object of its own after cgeradorbuqrcode.cpp's: its vtable
// (@1575976) and typeinfo (@1576000) follow CGeradorBUQRCode's typeinfo (@1575968), in a run of relatorios objects in
// name order (cgeradorbuj.cpp's record @1575808, cgeradorrellistaeleitores.cpp's @1576188).
//
// Recovered: the layout and the destructor. The constructor (fn 5603) stores, after the base's 416 bytes, a 16-bit word
// at +416 from its third wasm argument (this the first), the bytes at +418 and +419, and 12 bytes copied to +420 from
// its fourth (the last). The bytes are two stores of 0 in the reverse of their offsets, unmerged, which clang gives for
// two parameters and not for two constants (a constant pair it stores as one 16-bit word, measured in this object); its
// two callers, fns 1956 and 12110, pass the same 0s, so binaryen's dead-argument elimination folded them into the body,
// and the wasm type keeps four words. The constructor takes two flags, and its callers pass false: the number is a
// choice, since one bool stored into both bytes gives the same two stores (a probe object of both forms), and with
// one flag 5603's symbol would mangle one bool. 11242 (Slot2, not reconstructed) tests the byte at +418 for "RED"
// against "VOTA". The third argument is
// comum::CRdvVota::Comparecimento()'s result in fn 1956. The names and the types beyond those widths are chosen;
// api::CDateTime is a 12-byte value that the slot-2 overrider's fields "DTEM:{} " and "HREM:{} " could print, and fn
// 1956 passes CEstadoGeralVota::GetDtHrEmissaoBU()'s copy. The destructor is out of line: the D0 (fn 11243) calls the
// D2 and then frees this (docs/reference/facts/reading.md R5); the D2 (fn 11244) only calls the base's. Nothing here
// shows whether the class is final: the D2 destroys no member of its own.

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

class CGeradorBUQRCodeVota : public CGeradorBUQRCode {
public:
    CGeradorBUQRCodeVota(const CCabecalhoQRCodeBuilder& cabecalho, ueword comparecimento, bool campo418, bool campo419,
                         const api::CDateTime& dataHoraEmissao);
    ~CGeradorBUQRCodeVota() override;

protected:
    void Slot2(CCabecalhoQRCodeBuilder& cabecalho) const override;
    std::string Slot3(TEleicaoID eleicao) const override;

private:
    ueword m_comparecimento;
    bool m_campo418;
    bool m_campo419;
    api::CDateTime m_dataHoraEmissao;
};

} // namespace comum
