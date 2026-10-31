#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum {

// A data source of an answer's number (RTTI, in the argument of api::CDataText; fn 6652 builds that text with
// std::make_shared). The path is chosen.
//
// Recovered: one byte, the number's width. fn 6652 builds the source on its stack with a call of fn 5729, which stores
// its byte argument at +0 and returns this, and copies that byte into the CDataText at +20 (the object at +8 of the
// CDataText, 12 bytes into the block); fn 12621, CDataText<CRespostasDSNumero>::GetText, reads it at +8 as the second
// argument of std::format. So the constructor takes the byte, and 6652 holds a call of it, not its one store, which
// reads as a constructor defined in another TU (a reading, not measured). fn 600, api::CSynchronizer::CreateInst by its
// record, calls fn 5729 on a fresh one-byte object too, so the target holds one body for both and does not tell which
// source defines this one. It is declared only: no function of ours needs its body. The member's and the parameter's
// names, the parameter's type and `explicit` are chosen.
//
// The call operator is defined in crespostas.cpp: fn 12621 holds CRespostas::GetInst's code inlined, and GetInst is an
// out-of-line function of that file (record crespostas.cpp:28, fn 2812), so the operator was compiled there. The
// GetText that holds it is another TU's copy: CDataText<CRespostasDSNumero>'s vtable (1537832) lies between
// ctelasvota.cpp's records 1537776 and 1537968, so binaryen inlined the operator into its one caller.
class CRespostasDSNumero {
public:
    explicit CRespostasDSNumero(uebyte digitos);

    std::string operator()() const;

private:
    uebyte m_digitos;
};

// The current answer's text, a screen's text field: fn 6652 passes it to api::CFormBuilder::AddTextField (fn 1191) by
// table slot 1096, and no direct call reaches it. Its body, fn 11479, holds CRespostas::GetInst's code (record
// crespostas.cpp:28), which only that file can inline, so it is defined there, after CRespostasDSNumero's call
// operator: the target links it after the file's statics (11481, 11480 are their exit destructors). Its name, its being
// a free function, this header and its line are chosen.
std::string RespostaCorrente();

} // namespace comum
