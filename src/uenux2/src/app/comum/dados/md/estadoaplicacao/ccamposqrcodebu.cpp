// Reconstruction: target fns 5623 and 5622, under the chosen names of ccamposqrcodebu.h. No record names this file: the
// directory is the link-order neighbours', the md/estadoaplicacao constructors of stretch 802 (fns 5625 to 5631).
#include "app/comum/dados/md/estadoaplicacao/ccamposqrcodebu.h"

#include <format>

namespace comum::md::estadoaplicacao {

void CCamposQRCodeBU::DefineHistoricoCargas(const std::vector<std::string>& cargas)
{
    m_historicoCargas = std::format("HIQT:{} ", cargas.size());
    unsigned indice = 0;
    for (const std::string& carga : cargas) {
        m_historicoCargas += std::format("HICA:{}:{:.24s} ", ++indice, carga);
    }
}

void CCamposQRCodeBU::DefineIdentificadorCarga(const std::string& identificadorCarga)
{
    m_identificadorCarga = std::format("IDCA:{:.24s} ", identificadorCarga);
}

} // namespace comum::md::estadoaplicacao
