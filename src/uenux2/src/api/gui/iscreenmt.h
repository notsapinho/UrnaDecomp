#pragma once

// api::IScreenMT (/home/rubio/tse/uenux2/src/api/gui/iscreenmt.h; the path is chosen beside iscreen.h: no record
// names a file of the class). RTTI names the class (a class with no base, ledger/classes.json); its vtable (@1529848,
// 20 slots, ledger/vtables.json) holds the destructor (slot 0, target fn 8741; slot 1 is the trap an abstract class's
// deleting destructor gets), 17 pure virtual members (slots 2-13 and 15-19) and one member with an empty body (slot 14,
// fn 218). Only ShowClock has a name in the target, through the RTTI name of the local class
// simulador::CWasmScreenMT::ShowClock(api::SPoint const&)::WasmText (ledger/classes.json); every other member name is
// chosen, from what the callers and simulador::CWasmScreenMT's overrides do:
//   slot 0      the destructor. Inline in the original: CWasmScreenMT's D2 and D0 (fns 8745, 8744) hold its body, the
//               vptr store and a call of fn 3461, where one defined out of line would be a call
//               (docs/reference/facts/reading.md R5). Its body waits for fn 3461, so it is declared here without one
//               and trapped in src/units/78-uenux2-cwasmscreenmt-pending.cpp; it moves into the class with its body
//   slot 2      Clear: CWasmScreenMT's override fills its four lines with spaces and repaints; api::CPreShowClearMT
//               (fn 11047) calls it, then slot 13
//   slot 3      ShowText: fn 8799 reads the position's two shorts and calls the text's slots 2 and 3; CTextFieldMT::Draw
//               (fn 10934) and CTextFieldUpdateMT::Draw (fn 10548) call it with a position and an api::IText
//   slot 4      ShowImage: comum::CInfoMTLCD's slot 2 (fn 11653) centres an image's size on slots 17 and 18 and calls it
//               with that position, the image and 0. The override's body is empty (fn 1870)
//   slot 5      named after its slot: nothing shows what it does; the override is the shared empty fn 218
//   slot 6      Buzz: api::CBuzzFieldMT::Draw (fn 11049) calls it with its +24 and +28. The parameters are ints by their
//               wasm type and the callers' constants (fn 941's call sites pass 51 and 10, or 52 and 5)
//   slot 7      Beep: api::CBeepFieldMT::Draw (fn 11053) calls it with its +24; the callers of fn 1072 pass 1 or 2
//   slots 8-11  Led0 to Led3, named after the operation (0 to 3, api/gui/cledfieldmt.h) for which
//               api::CLedFieldMT::Draw calls each one; CWasmScreenMT's overrides turn its one LED off in slots 8 and 11
//               and on in slots 9 and 10 (fns 5038, 5036), then call its slot 14
//   slot 12     ShowClock: api::CClockFieldMT::Draw (fn 11048) calls it with the SPoint at its +24
//   slot 13     named after its slot: fn 11047 calls it after Clear; the override is the shared empty fn 218
//   slot 14     Refresh, the only slot with a body here (fn 218, empty): CWasmScreenMT's overrides of slots 2, 3 and 6-11
//               and 19 call it after each change, and its own (fn 8746) hands the four lines and the LED to the page
//   slots 15-16 named after their slot: nothing shows what they do; the overrides are the shared empty fn 218
//   slots 17-18 GetWidth and GetHeight: fn 11653 centres an image on them; the overrides return 480 and 80 (fns 8743,
//               8742). The result types are ints by their wasm type
//   slot 19     named after its slot: the override (fn 5039, one body with slot 7's) ignores its int and repaints

#include "api/gui/primitives.h"

namespace api {

class IImage;
class IText;

class IScreenMT {
public:
    virtual ~IScreenMT();

    virtual void Clear() = 0;

    virtual void ShowText(const SPoint& posicao, const IText& text) = 0;

    virtual void ShowImage(const SPoint& posicao, const IImage& imagem, int) = 0;

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
