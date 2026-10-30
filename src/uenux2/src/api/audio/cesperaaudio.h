#pragma once

namespace api {

// Recovered: RTTI names both classes: api::IEsperaAudio (typeinfo 1528612, a polymorphic class with no base) and
// api::CEsperaAudio, an si_class of it (vtable @1528576), the default wait ISound::WaitAsync returns; its other
// implementer is cwasmwebsound.cpp's file-static CEsperaAudioWasm (vtable @1528660). Slots 0 and 1 are the destructor,
// the shared empty bodies 174 and 144 in CEsperaAudio's vtable. Slot 2 (fn 9509) stores 1 at +4 and slot 3 (fn 2683, one
// body with sqlite's rtreeEof) reads it: a flag set by whoever holds the wait and read by the wait. The class is final,
// or its destructor is: slot 2 of __shared_ptr_emplace<CEsperaAudio> (__on_zero_shared) holds 218, an empty body, and
// without either form that member calls the destructor through the vtable, however the reads below are written. The
// class form is the chosen one of the two (units/81-uenux2-simulador-wasm-devices.mk). ISound::WaitAsync's lambda (fn
// 8382) and fn 8450 read +4 with no call, which either form gives. No record, symbol or string names this file or any
// member: Cancela, Cancelada and m_cancelada are chosen from those roles, and the path from ISound's.
class IEsperaAudio {
public:
    virtual ~IEsperaAudio() = default;

    virtual void Cancela() = 0;
    virtual bool Cancelada() = 0;
};

class CEsperaAudio final : public IEsperaAudio {
public:
    virtual void Cancela() override { m_cancelada = true; }
    virtual bool Cancelada() override { return m_cancelada; }

private:
    bool m_cancelada = false;
};

} // namespace api
