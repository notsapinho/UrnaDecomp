#pragma once

#include <memory>
#include <string>
#include <vector>

#include "api/audio/itexttospeech.h"

namespace RHVoice {
class engine;
}

namespace api {

// api::CRHVoiceTextToSpeech: RTTI gives an si_class of api::ITextToSpeech, vtable @1585548 [11530, 11518, 11511, 11507,
// 11505, 11504, 11500, 11494, 11491, 5441, 10838, 10841]: ITextToSpeech's slots 0 to 8, then its own destructors and
// DoSynthesize (fn 10841, 75,081 B). fn 10842 is the constructor (it stores the vptr, takes a string and builds a
// RHVoice::engine with std::make_shared). Recovered: the two data members the destructor (fn 5441) destroys after
// ITextToSpeech's 96 bytes, in its order: +104 first, a pointer it nulls before it deletes what it held, a struct of 24
// bytes whose std::string at +12 and std::vector at +0 it frees in that order (a std::unique_ptr to a struct of a vector
// and a string), then +96, a std::shared_ptr it releases. The D0 (fn 10838) frees what the D2 returns, the shape of a
// destructor that is not out of line (docs/how-to-decompile.md step 5): implicit here, which is chosen over one defined in
// the class without `inline`, and DoSynthesize is then the key function: the D2 and the D0 are emitted with the vtable. The D2 reads no element of the vector and nothing of the shared_ptr's pointee, so
// the element type, the shared_ptr's RHVoice::engine (the std::make_shared that fn 10842 calls), the struct and every
// name are chosen. The D2 does not begin with the class's own vptr store, only ITextToSpeech's, so the class is final
// (docs/how-to-decompile.md step 5). The path is chosen too, beside itexttospeech.h: no record names the class's files.
// DoSynthesize is not reconstructed: src/units/158-uenux2-api-pending.cpp traps it. The constructor is not written.
class CRHVoiceTextToSpeech final : public ITextToSpeech {
public:
    explicit CRHVoiceTextToSpeech(const std::string& voz);

    std::shared_ptr<CWavFile> DoSynthesize(const std::string& text, const SOptions& options) override;

private:
    struct SBuffer {
        std::vector<short> amostras;
        std::string nome;
    };

    std::shared_ptr<RHVoice::engine> m_engine;
    std::unique_ptr<SBuffer> m_buffer;
};

} // namespace api
