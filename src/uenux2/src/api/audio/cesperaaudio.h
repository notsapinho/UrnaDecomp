#pragma once

namespace api {

// Recovered: RTTI names both classes: api::IEsperaAudio (typeinfo 1528612, a polymorphic class with no base) and
// api::CEsperaAudio, an si_class of it (vtable @1528576), the default wait ISound::WaitAsync returns; its other
// implementer is cwasmwebsound.cpp's file-static CEsperaAudioWasm (vtable @1528660). Slots 0 and 1 are the destructor,
// the shared empty 174 and 144. Slot 2 (fn 9509) stores 1 at +4 and slot 3 reads it, a flag set by whoever holds the
// wait: fn 2683, one function with slots 4 and 6 of vota::impl::CInformacaoThreadOperador and sqlite's rtreeEof. The
// class is final, or its destructor is: slot 2 of __shared_ptr_emplace<CEsperaAudio> (__on_zero_shared) holds 218, an
// empty body, and without either that member calls the destructor through the vtable, however the reads are written.
// The class form is chosen (units/81-uenux2-simulador-wasm-devices.mk). Fns 8382 and 8450 read +4 with no call, which
// either form gives. The header is evidence: fns 8450 and 9515, ISound's and CWasmWebSound's WaitAsync, both build the
// class. Its path is chosen from ISound's. No record, symbol or string names it or a member: the names are from roles.
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
