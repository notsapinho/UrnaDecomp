// simulador::CWasmThread (src/units/99-uenux2-simulador-wasm-cwasmthread.mk says what is evidence and what is chosen).
// The reconstruction's notes: the lines above Create's record are laid out to bring its throw to line 31.
#include "cwasmthread.h"

#include <emscripten.h>

#include <algorithm>
#include <string>

#include "api/ipc/eueipcerror.h"

extern "C" void js_thread_log(const char* msg);


namespace simulador {

struct SContextoThread {
    void* (*rotina)(void*);
    void* parametro;
    int concluido;
    int id;
};

std::vector<SContextoThread*> CWasmThread::s_contextos;
int CWasmThread::s_proximoId = 0;


void CWasmThread::Create(void* (*rotina)(void*), void* parametro)
{
    if (rotina == nullptr) {
        throw api::CUeIpcError(api::EUE_IPC_IMPLEMENTACAO_NAO_ESPECIFICADA, "CWasmThread::Create sem função válida");
    }
    SContextoThread* contexto = new SContextoThread{rotina, parametro, 0, 0};
    contexto->id = ++s_proximoId;
    m_contexto = contexto;
    s_contextos.emplace_back(contexto);
    js_thread_log((std::string("Create #") + std::to_string(contexto->id) + " - enqueued").c_str());
}

void CWasmThread::Wait()
{
    SContextoThread* contexto = m_contexto;
    if (contexto == nullptr) {
        js_thread_log("Wait - no ctx, returning");
        return;
    }
    js_thread_log("Wait - polling");
    while (contexto->concluido == 0) {
        emscripten_sleep(100);
    }
    js_thread_log("Wait - finished");
    auto it = std::find(s_contextos.begin(), s_contextos.end(), contexto);
    if (it != s_contextos.end()) {
        s_contextos.erase(it);
    }
    delete contexto;
    m_contexto = nullptr;
}

void CWasmThread::Yield()
{
    js_thread_log("Yield");
    emscripten_sleep(0);
    js_thread_log("Yield - returned");
}

} // namespace simulador
