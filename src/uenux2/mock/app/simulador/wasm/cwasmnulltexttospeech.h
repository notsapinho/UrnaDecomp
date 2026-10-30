#pragma once

#include "api/audio/itexttospeech.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ITextToSpeech, vtable @1528696), the wasm build's speech, which
// synthesizes nothing: slot 11 (fn 9436) returns an empty std::shared_ptr. It adds no member: the object is 96 bytes, as
// ITextToSpeech's, and its slot 9 is ITextToSpeech's destructor (fn 11489). DoSynthesize is out of line, the class's key
// function: its vtable and typeinfo lie after cwasmwebsound.cpp's data (@1528696 and 1528752), not in
// vota_web_wasm.cpp's, although that TU stores the vptr (fn 13877), and ITextToSpeech's, which has no key function, do
// lie there. The class is not `final` by choice: `final` gives the same object. The member's name is api::ITextToSpeech's
// (chosen: api/audio/itexttospeech.h says from what).
class CWasmNullTextToSpeech : public api::ITextToSpeech {
public:
    virtual std::shared_ptr<api::CWavFile> DoSynthesize(const std::string& text, const SOptions& options) override;
};

} // namespace simulador
