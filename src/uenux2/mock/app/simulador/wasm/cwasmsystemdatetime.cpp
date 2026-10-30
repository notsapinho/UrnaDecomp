#include "cwasmsystemdatetime.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp): the browser's local time in seconds
extern "C" double js_obter_data_hora_local_navegador();

namespace simulador {

time_t CWasmSystemDateTime::GetTime()
{
    const double navegador = js_obter_data_hora_local_navegador();
    return m_diferenca + static_cast<time_t>(navegador);
}

void CWasmSystemDateTime::SetTime(time_t agora)
{
    m_diferenca = agora - static_cast<time_t>(js_obter_data_hora_local_navegador());
}

} // namespace simulador
