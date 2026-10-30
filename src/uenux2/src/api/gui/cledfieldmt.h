#pragma once

// api::CLedFieldMT: the class is named by RTTI (an si_class of api::IFormField<api::IScreenMT>,
// ledger/classes.json), Draw by its record (cledfieldmt.cpp:46:19). The header's path, the enum and its enumerators,
// the constructor's parameter and the member's name are chosen: no evidence names them. The layout (28 bytes:
// IFormFieldBase's 24, then the operation at +24) is read from Draw and from the merged factory body 3890 (reached
// through fn 435, which passes it this class's vtable): it allocates 28 bytes, clears the base's members and stores
// its argument at +24. The constructor has no target function of its own (3890 holds it inlined), so it is declared
// only. The destructor is implicit: the deleting destructor (fn 2777, through 1565) holds its body, and slot 0 of the
// class's vtable is IFormFieldBase<IScreenMT>'s own (target fn 11052).

#include "api/gui/iformfield.h"

namespace api {

class IScreenMT;

// the operation the field performs when drawn: Draw calls IScreenMT's slot 8 + the operation (api/gui/iscreenmt.h)
// and throws for any other value. The callers of 435 pass 0 (most forms), 1 (vota::CMostraEleitorVotando,
// vota::CEleitorDemorando) or 2 (fn 5341); simulador::CWasmScreenMT turns its LED off for 0 and 3 and on for 1 and 2
enum ELedOperacao {
    LED_OPERACAO_0,
    LED_OPERACAO_1,
    LED_OPERACAO_2,
    LED_OPERACAO_3,
};

class CLedFieldMT : public IFormField<IScreenMT> {
public:
    explicit CLedFieldMT(ELedOperacao operacao);

    void Draw(IScreenMT& screen) const override;

private:
    ELedOperacao m_operacao;
};

} // namespace api
