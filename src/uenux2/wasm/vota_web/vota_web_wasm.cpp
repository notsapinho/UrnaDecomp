// Reconstruction's note, not TSE's text: the executable TU of the web voting simulator. Its three records fix lines 361,
// 515 and 592; every other line is a choice, and src/units/170-uenux2-wasm-vota-web.mk says what is recovered, what is
// chosen and what waits.
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "api/audio/isound.h"
#include "api/gui/capplication.h"
#include "api/hwil/ifingerprepare.h"
#include "api/hwil/iinput.h"
#include "api/ipc/posix/cposixmutex.h"
#include "api/ipc/posix/cposixrwmutex.h"
#include "api/ipc/posix/cposixsemaphore.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"
#include "api/util/cajustedatahora.h"
#include "app/comum/iinterfacesavd.h"
#include "app/vota/cexecucaovotacooperativa.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"
#include "app/vota/eleitor/isincronismovotoeleitor.h"
#include "ecourna/api/security/cprng.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "uenux2/mock/app/simulador/wasm/cfingerpreparesimulador.h"
#include "uenux2/mock/app/simulador/wasm/cwasmthread.h"
#include "uenux2/mock/app/simulador/wasm/cwasmwebsound.h"
#include "uenux2/mock/app/simulador/wasm/simulador.h"
#include "uenux2/mock/app/simulador/wasm/wasmjs.h"

extern "C" {
// the JavaScript side (EM_JS, src/web/wasm_shim.cpp)
void js_use_external_keyboard(void);
int js_ler_dimensao_tela(int dimensao, int padrao);
}

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

// (original lines 55-357: content not recovered)
#line 358
class CPoliticaExecucaoEleitorWeb : public vota::impl::IPoliticaExecucaoEleitor {
public:

    void LimpaBufferInput() const override { api::CPolySingleton<api::IInputKbd>::instance().Clear(); }
};


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

// the SAVD channel of the wasm build, which answers every message with an empty response
constexpr ueint32 ESTADO_SAVD_WASM = 212593824;

class CWasmSavd : public comum::IInterfaceSavd {
public:
    void Escreve(const std::vector<uebyte>&) override {}

    void RecebeMensagem(ueint32& estado, std::vector<uebyte>& dados, size_t tamanho) override
    {
        estado = ESTADO_SAVD_WASM;
        if (tamanho != sizeof(comum::ueRespostaSavd)) {
            throw std::invalid_argument("CWasmSavd::RecebeMensagem - mensagem de tamanho invalido");
        }
        comum::ueRespostaSavd resposta{};
        resposta.marca = 254;
        const uebyte* bytes = reinterpret_cast<const uebyte*>(&resposta);
        dados.assign(bytes, bytes + sizeof(resposta));
    }

    ueint32 Slot4() override { return ESTADO_SAVD_WASM; }
};

class CSincronismoVotoEleitorWeb : public vota::impl::ISincronismoVotoEleitor {
public:
    bool Sincroniza() override { return true; }
};


} // namespace

extern "C" void votaPressKey(const char* tecla)
{
    Engine().PressKey(tecla);
}

extern "C" void votaSetAudioEnabled(int habilitado)
{
    Engine().SetAudioEnabled(habilitado);
}


int main()
{
    js_use_external_keyboard();
    const api::TPosition largura = js_ler_dimensao_tela(0, 1280);
    const api::TPosition altura = js_ler_dimensao_tela(1, 800);
    const simulador::SConfiguracao configuracao(10, "VOTA Web", largura, altura);

    api::CApplication::InitApplication("VOTA", "Software de Votação", "10.23.0.1 - DESENVOLVIMENTO", static_cast<ELogAplicativos>(1));

    api::CPolySingleton<comum::IInterfaceSavd>::set(new CWasmSavd());
    api::CPolySingleton<ecourna::api::security::IRng>::set(new ecourna::api::security::CPrng(0));
    api::CPolySingleton<ecourna::api::security::ISymmetricCipherFactory>::set(new ecourna::api::security::CSymmetricCipherFactory);
    api::CPolySingleton<api::IFingerPrepare>::set(new simulador::CFingerPrepareSimulador);
    api::CAjusteDataHora::Registra();
    api::CPolySingleton<api::IGenericFactory<api::IThreadImpl>>::set(new api::CDefaultGenericFactory<api::IThreadImpl, simulador::CWasmThread>);
    api::CPolySingleton<api::IGenericFactory<api::ISyncCtl>>::set(new api::CDefaultGenericFactory<api::ISyncCtl, api::CPosixMutex>);
    api::CPolySingleton<api::IGenericFactory<api::IRWSyncCtl>>::set(new api::CDefaultGenericFactory<api::IRWSyncCtl, api::CPosixRWMutex>);
    api::CPolySingleton<api::IGenericFactory<api::ISemaphore>>::set(new api::CDefaultGenericFactory<api::ISemaphore, api::CPosixSemaphore>);
    api::CPolySingleton<vota::impl::IPoliticaExecucaoEleitor>::set(new CPoliticaExecucaoEleitorWeb);
    api::CPolySingleton<vota::impl::ISincronismoVotoEleitor>::set(new CSincronismoVotoEleitorWeb);
    api::CPolySingleton<vota::IExecucaoVota>::set(new vota::CExecucaoVotaCooperativa(&vota::CAguardaMensagem::GetInst()));

    simulador::Inicializa(configuracao, [] {
        api::CPolySingleton<api::ISound>::set(new simulador::CWasmWebSound);
        simulador::EmitEvent("vota:ready", "{}");
    });
    return 0;
}
