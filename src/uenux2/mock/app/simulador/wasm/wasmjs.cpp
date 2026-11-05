#include "wasmjs.h"

#include <iomanip>
#include <sstream>

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

std::string EscapaJson(const std::string& texto)
{
    std::ostringstream saida;
    for (const unsigned char c : texto) {
        switch (c) {
        case '\\':
            saida << "\\\\";
            break;
        case '"':
            saida << "\\\"";
            break;
        case '\b':
            saida << "\\b";
            break;
        case '\f':
            saida << "\\f";
            break;
        case '\n':
            saida << "\\n";
            break;
        case '\r':
            saida << "\\r";
            break;
        case '\t':
            saida << "\\t";
            break;
        default:
            if (c < 0x20) {
                saida << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
            } else if (c >= 0x80) {
                saida << "\\u00" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
            } else {
                saida << static_cast<char>(c);
            }
            break;
        }
    }
    return saida.str();
}

} // namespace simulador
