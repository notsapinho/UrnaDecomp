#pragma once

#include <string>

#include "api/gui/iscreenmt.h"

namespace simulador {

class CWasmScreenMT : public api::IScreenMT {
public:
    CWasmScreenMT();

    void Clear() override;
    void ShowText(const api::SPoint& posicao, const api::IText& text) override;
    void Slot4(int, int, int) override;
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
