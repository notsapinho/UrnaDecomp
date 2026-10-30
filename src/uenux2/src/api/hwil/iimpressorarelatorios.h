#pragma once

// api::IImpressoraRelatorios, the printer the reports use. RTTI gives an si_class of api::IImpressora (typeinfo
// 1583844) and the record of SetStyle (iimpressorarelatorios.cpp:22:15) the class, the member and the file beside it;
// this header's path is chosen, from that file's name. SetStyle reads as the key function: the typeinfo lies in that
// object, after the record, and simulador::CWasmNullPrinter's object has no copy. The target has no vtable for it
// (ledger/vtables.json).
//
// Slots 4 and 5 are this class's (fns 10881 and 10880, which read the style at +4; 10880's index sits next to 10881's
// in their use band, which reads as the same object). Slot 12 is called by SetStyle through the vtable before the store
// of the style, and CWasmNullPrinter's body (fn 8365) stores the same member, so +4 is a member that class can reach.
// That slots 12 to 14 are declared here and not in IImpressora is chosen: no evidence separates the two. The name
// ApplyStyle is chosen from SetStyle's use of slot 12; slots 13 and 14 keep their slots' names, and the return types
// are chosen.

#include "api/hwil/iimpressora.h"

namespace api {

class IImpressoraRelatorios : public IImpressora {
public:
    void SetStyle(ELPStyle style) override;
    int GetColumns() override;

    virtual void ApplyStyle(ELPStyle style) = 0;
    virtual int Slot13() = 0;
    virtual void Slot14(int a, int b, int c) = 0;

protected:
    ELPStyle m_style = ELP_STYLE_NONE;
};

} // namespace api
