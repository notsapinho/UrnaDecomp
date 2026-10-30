// Reconstruction's note, not TSE's text. Line 23 is the record of GetInst (fn 1155, not written), so it stays blank and
// what this file holds follows it: api::CSystemDateTime, whose slots are fns 10855 and 10853. No record names the
// class's file. It is here by data order: its vtable (@1585236) and typeinfo (@1585260) lie right before this file's
// record at 1585272, after cwait.cpp's records, where api/util/'s objects run in name order, and only fn 1155 stores its
// vptr. That supports the place and does not prove it. Defining the class in this file rather than in a header is a
// choice, and so is GetTime out of line: the class's key function, so that this object emits the vtable with no GetInst
// written (units/81-uenux2-simulador-wasm-devices.mk lists the same-bytes forms).

// (original lines 9-18: content not recovered)
#line 19
// <stubs>
// f1155 · 1944 B · unmatched · name unknown
// ? f1155() { ... }
// </stubs>

#include "api/util/isystemdatetime.h"

namespace api {

class CSystemDateTime : public ISystemDateTime {
public:
    virtual time_t GetTime() override;
    virtual void SetTime(time_t agora) override;
};

time_t CSystemDateTime::GetTime()
{
    return time(nullptr);
}

void CSystemDateTime::SetTime(time_t agora) {}

} // namespace api
