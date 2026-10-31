#include "cwasminit.h"

#include <format>
#include <string>

#include "cwasmcanaislog.h"

namespace {

// a line of channel 0 of the log, for each message EnviarMensagem answers (fn 1524)
void Loga(int mensagem, const std::string& resposta)
{
    simulador::CWasmCanaisLog::GetInst().Escreve(0, std::format("CWasmInit::{} {}", mensagem, resposta));
}

} // namespace

namespace simulador {

int CWasmInit::Slot4()
{
    return m_parametro;
}

std::vector<int> CWasmInit::EnviarMensagem(ueint32 mensagem)
{
    const int codigo = mensagem & 0xFFFF;
    int resposta = 0;
    switch (codigo) {
    case 10:
    case 11:
    case 34:
    case 36:
    case 47:
    case 48:
    case 58:
    case 68:
        Loga(codigo, {});
        break;
    case 17:
    case 18:
        Loga(codigo, "= no");
        resposta = 1;
        break;
    case 67:
        Loga(codigo, "= 0");
        break;
    case 6:
        Loga(codigo, "= FE_NOT_PRESENT");
        resposta = 1;
        break;
    case 15:
    case 16:
        Loga(codigo, "= no");
        resposta = 1;
        break;
    case 39:
        Loga(codigo, "= 512000");
        resposta = 512000;
        break;
    case 7:
        Loga(codigo, {});
        break;
    default:
        Loga(codigo, "= default");
        break;
    }
    return {resposta};
}

} // namespace simulador
