#pragma once

#include <string>

#include "api/gui/iscreenmt.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IScreenMT, vtable @1529748, 20 slots). The layout is what fn 8302,
// into which the constructor is inlined, and the members give: 56 bytes (its f137(56)), four std::string from +4 to
// +51 and a bool at +52. ShowText (fn 8799) reaches the strings as this + 4 + 12 * (y - 1) and Refresh walks them, so they
// are one array; a run of four std::string members and a pointer to the first give the same code, and that the
// array is a C array and not a std::array is a choice (src/units/78-uenux2-cwasmscreenmt.mk lists what was measured).
// The destructor is implicit: the D0 (fn 8744) holds the D2's body, and the D2 (fn 8745) begins with this class's vptr
// store, so the class is not final (docs/reference/facts/reading.md R4, R5). Its members call slot 14 through the
// vtable, which `final` would make a direct call. The names are api::IScreenMT's (iscreenmt.h says from what); the data
// members' are chosen. A line holds 40 characters and the screen has 4 lines: the numbers in fns 8810 and 8799.
class CWasmScreenMT : public api::IScreenMT {
public:
    CWasmScreenMT();

    void Clear() override;
    void ShowText(const api::SPoint& posicao, const api::IText& text) override;
    void ShowImage(const api::SPoint& posicao, const api::IImage& imagem, int) override;
    void Slot5() override;
    void Buzz(int, int) override;
    void Beep(int) override;
    void Led0() override;
    void Led1() override;
    void Led2() override;
    void Led3() override;
    void ShowClock(const api::SPoint& posicao) override;
    void Slot13() override;
    void Refresh() override;
    void Slot15() override;
    void Slot16() override;
    int GetWidth() const override;
    int GetHeight() const override;
    void Slot19(int) override;

private:
    std::string m_linhas[4];
    bool m_led = false;
};

} // namespace simulador
