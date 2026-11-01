#pragma once

// comum::CGeradorBUQRCode (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp, its records' file; the
// header beside it is chosen) and comum::SQtdeAptos. Reconstruction notes, not TSE's text.
//
// RTTI gives CGeradorBUQRCode with no base, and its vtable (@1575912) has four slots: the D2 (fn 2251), 325 for the D0
// (an abstract class's) and two pure slots. No record, slot or caller names those two: Slot2 and Slot3 are named after
// their slots. Their signatures are CGeradorBUQRCodeVota's overriders' (fns 11242 and 11241, cgeradorbuqrcodevota.h):
// both return a std::string, and slot 3 takes one more word, which fn 5604 passes from CCargos::GetCurrentEleicaoID
// (fn 2835), so its type, TEleicaoID, is chosen from that.
//
// Recovered: the layout and the destructor. CGeradorBUQRCodeVota's constructor (fn 5603) holds this class's inlined: it
// copies a CCabecalhoQRCodeBuilder to +4 (fn 5608; 396 bytes), stores CRdvVota::GetInst()'s result (fn 555) at +400
// and moves to +404 the map that comum::CEleitores's slot 0 (fn 2824) returns. The D2 (fn 2251) destroys the map's tree
// (fn 1405) and then the builder (fn 2885), the reverse of their offsets. GetQtdAptos (record
// cgeradorbuqrcode.cpp:80) looks the current post's coverage up in that map, and fn 3696 formats what it finds. The
// destructor is out of line, this class's key function: CGeradorBUQRCodeVota's D2 (fn 11244) calls this D2, and with
// `virtual ~CGeradorBUQRCode() = default;` in the class clang inlines its body into that D2 (measured on
// cgeradorbuqrcodevota.cpp's object). The vtable (@1575912) lies in the run of this file's records, before line 80's.
// A reference for +400 and every member's and the map's names are chosen.
//
// SQtdeAptos: the map's mapped type. fn 2824 allocates its nodes with 24 bytes (a 16-byte node, the 4-byte key and 4
// bytes of value), zeroes the value and counts in the 16-bit words at +0 and +2 of it, and fn 3696 prints the first as
// "APTS:{} ", the second as "APTT:{} " and their sum as "APTA:{} ", so its members are named after those labels. Where it
// is declared is chosen: the lambdas of std::function<comum::SQtdeAptos()> (RTTI) return it too, and CEleitores's slot 0
// returns the map.

#include <map>
#include <string>

#include "app/comum/asn/util.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/relatorios/ccabecalhoqrcodebuilder.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

class CRdvVota;

struct SQtdeAptos {
    ueword m_qtdeAptosDaSecao;
    ueword m_qtdeAptosTTE;
};

class CGeradorBUQRCode {
public:
    virtual ~CGeradorBUQRCode();

protected:
    virtual std::string Slot2() const = 0;
    virtual std::string Slot3(TEleicaoID eleicao) const = 0;

    std::string GetCamposAptos() const;
    const SQtdeAptos& GetQtdAptos(md::ETipoAbrangencia abrangencia) const;

    CCabecalhoQRCodeBuilder m_cabecalho;
    const CRdvVota& m_rdv;
    std::map<md::ETipoAbrangencia, SQtdeAptos> m_qtdAptos;
};

} // namespace comum
