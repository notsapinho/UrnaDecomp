// DRAFT
#include "uenux2/mock/app/simulador/wasm/cwasmscreenmt.h"

namespace api {

IScreenMT::~IScreenMT()
{
    __builtin_trap();
}

} // namespace api

namespace simulador {

void CWasmScreenMT::ShowClock(const api::SPoint& posicao)
{
    __builtin_trap();
}

} // namespace simulador
