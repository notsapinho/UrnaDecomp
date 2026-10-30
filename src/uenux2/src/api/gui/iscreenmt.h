#pragma once

// api::IScreenMT (/home/rubio/tse/uenux2/src/api/gui/iscreenmt.h; the path is chosen beside iscreen.h: no record
// names a file of the class). RTTI names the class (a class with no base, ledger/classes.json); its vtable (@1529848,
// 20 slots, ledger/vtables.json) holds the destructor (slot 0, target fn 8741; slot 1 is the trap an abstract class's
// deleting destructor gets), 17 pure virtual members (slots 2-13 and 15-19) and one member with an empty body (slot 14,
// fn 218). No record or symbol names any of its members, so every member name below is chosen. Declared are the slots
// up to 11, the ones api::CLedFieldMT::Draw (target fn 11050) calls and the ones before them that fix their place:
//   slot 0      the destructor; its body (fn 8741: the vptr store, then a call of fn 3461) is not reconstructed
//   slots 2-7   named after their slot; their parameters are the wasm shape of simulador::CWasmScreenMT's
//               overrides (fns 8810, 8799, 1870, 218, 8787, 5039: slot 3 takes two i32, slot 4 three, slot 6 two,
//               slot 7 one), not recovered types. api::CTextFieldMT::Draw (10934) calls slots 2 and 3,
//               api::CBuzzFieldMT::Draw (11049) slot 6 with its +24 and +28, api::CBeepFieldMT::Draw (11053) slot 7
//               with its +24
//   slots 8-11  Led0 to Led3, named after the operation (0 to 3, api/gui/cledfieldmt.h) for which
//               api::CLedFieldMT::Draw calls each one; simulador::CWasmScreenMT's overrides turn its one LED off in
//               slots 8 and 11 and on in slots 9 and 10 (fns 5038, 5036), then call its slot 14
// Not declared yet: slots 12-19. Slot 12 is pure, and api::CClockFieldMT::Draw (11048) calls it with the SPoint at
// its +24 (the local class simulador::CWasmScreenMT::ShowClock(api::SPoint const&)::WasmText suggests its name);
// slots 13 and 15-19 are pure; slot 14 has an empty body, and simulador::CWasmScreenMT calls it from its slots 7-11
// and 19.

#include "api/gui/primitives.h"

namespace api {

class IText;

class IScreenMT {
public:
    virtual ~IScreenMT();

    virtual void Clear() = 0;

    virtual void ShowText(const SPoint& posicao, const IText& text) = 0;

    virtual void Slot4(int, int, int) = 0;

    virtual void Slot5() = 0;

    virtual void Buzz(int, int) = 0;

    virtual void Beep(int) = 0;

    virtual void Led0() = 0;

    virtual void Led1() = 0;

    virtual void Led2() = 0;

    virtual void Led3() = 0;

    virtual void ShowClock(const SPoint& posicao) = 0;

    virtual void Slot13() = 0;

    virtual void Refresh() {}

    virtual void Slot15() = 0;

    virtual void Slot16() = 0;

    virtual int GetWidth() const = 0;

    virtual int GetHeight() const = 0;

    virtual void Slot19(int) = 0;
};

} // namespace api
