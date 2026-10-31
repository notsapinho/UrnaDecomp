// simulador::CWasmLogd (cwasmlogd.h): the writer, escreve, CWasmLogd's key function. No record names this file: its
// path is chosen (src/units/62-uenux2-cwasmlogd.mk says why). The constructor is not reconstructed.
#include "cwasmlogd.h"

#include <cstdio>
#include <format>

#include "cwasmcanaislog.h"

namespace simulador {

void CWasmLogd::escreve(std::uint8_t codigo, api::ESeveridade severidade, const std::string& mensagem)
{
    const std::string linha = std::format("{}|{}|{}", codigo, static_cast<int>(severidade), mensagem);
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        if (FILE* arquivo = std::fopen(m_arquivo.c_str(), "ab")) {
            std::fwrite(linha.c_str(), 1, linha.size(), arquivo);
            std::fputc('\n', arquivo);
            std::fflush(arquivo);
            std::fclose(arquivo);
        }
    }
    CWasmCanaisLog::GetInst().Escreve(2, linha);
}

} // namespace simulador
