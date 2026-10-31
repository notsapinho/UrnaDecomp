// simulador::CWasmCanaisLog (cwasmcanaislog.h says what is recovered and what is chosen). No record names this file:
// its path is chosen, the class's name in lower case beside the simulator's other files.
#include "cwasmcanaislog.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>

namespace simulador {

void CWasmCanaisLog::Escreve(int canal, const std::string& texto)
{
    Adiciona(canal, Agora() + " " + texto);
}

std::string CWasmCanaisLog::Agora()
{
    const std::time_t agora = std::time(nullptr);
    std::tm local{};
    localtime_r(&agora, &local);
    std::ostringstream texto;
    texto << '[' << std::put_time(&local, "%Y-%m-%d %H:%M:%S") << ']';
    return texto.str();
}

void CWasmCanaisLog::Adiciona(int canal, std::string linha)
{
    std::vector<std::function<void(const std::string&)>> observadores;
    std::string ultima;
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        SCanal& destino = m_canais[canal];
        destino.m_historico.push_back(std::move(linha));
        while (destino.m_historico.size() > 2000) {
            destino.m_historico.pop_front();
        }
        ultima = destino.m_historico.back();
        observadores.reserve(destino.m_observadores.size());
        for (const auto& [id, observador] : destino.m_observadores) {
            observadores.push_back(observador);
        }
    }
    for (const auto& observador : observadores) {
        observador(ultima);
    }
}

} // namespace simulador
