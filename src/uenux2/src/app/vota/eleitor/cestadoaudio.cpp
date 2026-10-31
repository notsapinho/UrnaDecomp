#include "app/vota/eleitor/cestadoaudio.h"

namespace vota {

CEstadoAudio& CEstadoAudio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEstadoAudio());
    }
    return *s_inst;
}

std::unique_ptr<CEstadoAudio> CEstadoAudio::s_inst;
std::mutex CEstadoAudio::s_mutex;

CEstadoAudio::CEstadoAudio()
    : m_dadosCarregados(false)
    , m_eleitoresCarregados(false)
    , m_modo(MODO_DESATIVADO)
    , m_bancoCarregado(false)
    , m_campo9(0)
    , m_campo10(0)
{
}

} // namespace vota
