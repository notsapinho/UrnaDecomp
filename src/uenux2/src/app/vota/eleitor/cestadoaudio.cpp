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
    , m_teclaEsperada(0)
    , m_teclaPressionada(0)
{
}

void CEstadoAudio::SelecionaModo0()
{
    m_modo = MODO_0;
}

void CEstadoAudio::SelecionaModo1()
{
    m_modo = MODO_1;
}

void CEstadoAudio::Desativa()
{
    m_modo = MODO_DESATIVADO;
}

void CEstadoAudio::SetTeclasTesteTeclado(char esperada, char pressionada)
{
    m_teclaEsperada = esperada;
    m_teclaPressionada = pressionada;
}

std::pair<char, char> CEstadoAudio::GetTeclasTesteTeclado() const
{
    return {m_teclaEsperada, m_teclaPressionada};
}

} // namespace vota
