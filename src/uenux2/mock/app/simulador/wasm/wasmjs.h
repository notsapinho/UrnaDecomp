#pragma once

#include <string>

namespace simulador {

// The C++ side of three EM_JS functions (src/units/99-uenux2-simulador-wasm-cwasmthread.mk says why they are in a TU
// of their own). The names, this header's path and the namespace are chosen: no record, symbol or string names them.
void EmitEvent(const char* nome, const std::string& detalhe);
void PushKey(const std::string& tecla);
void ConsoleError(const std::string& mensagem);

} // namespace simulador
