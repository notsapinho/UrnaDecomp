#pragma once

// api::IPaper, the paper the report forms print on. No record names its header, so the file is chosen, beside
// iscreen.h. Its RTTI is a class with no base (typeinfo 1531164, ledger/classes.json); api::IPaperRelatorios derives
// from it, and simulador::CWasmNullPaper from that (vtable @1530564, 15 slots, ledger/vtables.json). IPaper has no vtable
// of its own in the target.
//
// The paper fields' Draw(IPaper&) members call four of its slots through the IPaper they get, so those are IPaper's
// own: slot 2 prints a text (api::CTextFieldPaper::Draw, target fn 10920, passes the field's IText and its EStyle),
// slots 3 and 4 take no argument (api::CCutFieldPaper's Draw 11015 calls slot 3, api::CNewLineFieldPaper's 11012 calls
// slot 4 once per line) and slot 12 takes three (api::CQRCodeImageFieldPaper's Draw 10963). Only slot 2 is recovered,
// and its name is chosen: no record or symbol names any of them.
//
// EStyle is the record's `IPaper::EStyle` (ctextfieldpaper.cpp:23:15). The target's callers of the CTextFieldPaper
// constructor pass 1 and 2; no evidence names the values, so the enumerators are not recovered.

#include "api/gui/itext.h"

namespace api {

/**
 * Papel onde os formulários são impressos.
 */
class IPaper {
public:
    /**
     * Estilo do texto impresso.
     */
    enum EStyle {
    };

    virtual ~IPaper() = default;

    /**
     * Imprime o texto de @p text no estilo @p estilo.
     */
    virtual void PrintText(const IText& text, EStyle estilo) = 0;
};

} // namespace api
