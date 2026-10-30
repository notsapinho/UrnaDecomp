#pragma once

#include <ctime>

// Reconstruction's note, not TSE's text. The record at line 46 is `static void api::ISystemDateTime::CreateInst()
// [T = api::CSystemDateTime]`, which fn 1155 holds with isystemdatetime.cpp's record 23:12 of GetInst: the singleton's
// members are not written, so line 46 stays blank and the class follows it, and the class's lines are a choice.
// RTTI names api::ISystemDateTime (typeinfo 1531172, a polymorphic class with no base) and its two implementers,
// api::CSystemDateTime (vtable @1585236) and simulador::CWasmSystemDateTime (vtable @1532044), 4 slots each.
// - slot 0 returns an i64 and takes nothing: fns 5472, 5473 and 10870 call it on fn 1155's result and pass it to fn
//   1000, and CSystemDateTime's is time(0), so it is a time_t, 64 bits here.
// - slot 1 takes an i64 and returns nothing: CSystemDateTime's is empty, and CWasmSystemDateTime's keeps the difference
//   between it and the browser's clock, which its slot 0 adds back. So it sets the clock.
// - slots 2 and 3 are the destructor: both implementers hold the shared empty bodies 174 and 144. It is declared after
//   the two members for that, in the class and defaulted, the chosen form.
// No evidence gives slots 0 and 1 a name: GetTime and SetTime are chosen from those roles.






























namespace api {

class ISystemDateTime {
public:
    virtual time_t GetTime() = 0;
    virtual void SetTime(time_t agora) = 0;
    virtual ~ISystemDateTime() = default;
};

} // namespace api
