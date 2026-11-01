// Reconstruction's note, not TSE's text: the executable TU of the web voting simulator. Its three records fix lines 361,
// 515 and 592; every other line is a choice, and src/units/170-uenux2-wasm-vota-web.mk says what is recovered, what is
// chosen and what waits.
#include <memory>
#include <string>

#include "api/audio/isound.h"
#include "api/pattern/cpolysingleton.h"
#include "uenux2/mock/app/simulador/wasm/wasmjs.h"

namespace api {

static TPolySingletonsInfo& polySingletonsInfoPadrao()
{
    static TPolySingletonsInfo info;
    info.m_depuracao = true;
    return info;
}

TPolySingletonsInfo& (*g_polySingletonsInfo)() = polySingletonsInfoPadrao;

} // namespace api

namespace {

// (original lines 26-357: content not recovered)
#line 358
// <stubs>
// f10835 · 62 B · unmatched · name unknown
// void f10835(i32) { ... }
// </stubs>

// (original lines 363-364: content not recovered)
#line 365
class CVotaWebEngine {
public:

    // (original lines 368-588: content not recovered)
#line 589
    void SetAudioEnabled(bool habilitado)
    {
        m_audioHabilitado = habilitado;
        api::CPolySingleton<api::ISound>::instance().Mute(!habilitado);
    }

    void PressKey(const char* tecla)
    {
        if (tecla) {
            simulador::PushKey(tecla);
        }
    }

private:
    bool m_inicializado = false;
    bool m_encerrado = false;
    bool m_audioHabilitado = true;
    bool m_audioEleitorHabilitado = false;
    bool m_aguardando = false;
    bool m_avisado = false;
    int m_avisos = 0;
    double m_proximoAviso = 0;
    std::string m_estado = "{}";
};

std::unique_ptr<CVotaWebEngine> g_engine;

CVotaWebEngine& Engine()
{
    if (!g_engine) {
        g_engine = std::make_unique<CVotaWebEngine>();
    }
    return *g_engine;
}

} // namespace

extern "C" void votaPressKey(const char* tecla)
{
    Engine().PressKey(tecla);
}

extern "C" void votaSetAudioEnabled(int habilitado)
{
    Engine().SetAudioEnabled(habilitado);
}
