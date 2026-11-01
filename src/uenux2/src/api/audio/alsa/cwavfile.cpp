#include "api/audio/alsa/cwavfile.h"

#include <cstdlib>

namespace api {

















































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
