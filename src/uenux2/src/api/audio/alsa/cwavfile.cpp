#include "api/audio/alsa/cwavfile.h"

#include <cstdlib>

namespace api {

// (original lines 7-43: content not recovered)
#line 44
// <stubs>
// f10841 · 75081 B · unmatched · name unknown
// void f10841(i32, i32, i32, i32) { ... }
// </stubs>







CWavFile::~CWavFile()
{
    if (m_dados != nullptr) {
        free(m_dados);
        m_dados = nullptr;
    }
    if (m_buffer != nullptr) {
        free(m_buffer);
    }
}

} // namespace api
