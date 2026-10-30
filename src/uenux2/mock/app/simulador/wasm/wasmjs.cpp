#include "wasmjs.h"

extern "C" {
void js_emit_event(const char* name, const char* detail);
void js_push_key(const char* key);
void js_console_error(const char* message);
}

namespace simulador {

void EmitEvent(const char* nome, const std::string& detalhe)
{
    js_emit_event(nome, detalhe.c_str());
}

void PushKey(const std::string& tecla)
{
    js_push_key(tecla.c_str());
}

void ConsoleError(const std::string& mensagem)
{
    js_console_error(mensagem.c_str());
}

} // namespace simulador
