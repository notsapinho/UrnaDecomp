// Reconstruction: comum::asn::CMinuciasCompactadas's constructor and Descompacta, which binaryen inlines into fn 5702,
// their one caller (fragment 335 has the forms measured). No record names a line or this file: both are chosen.
#include "app/comum/dados/asn/eleitor/cminuciascompactadas.h"

#include <cmath>

namespace comum::asn {

CMinuciasCompactadas::CMinuciasCompactadas(const std::vector<SPar>& pares) : m_minucias(Descompacta(pares)), m_pares(pares)
{
}

std::vector<api::SXYT> CMinuciasCompactadas::Descompacta(const std::vector<SPar>& pares)
{
    std::vector<api::SXYT> minucias;
    m_quantidadeAngulos = 0;
    m_xMinimo = 999;
    m_yMinimo = 999;
    ueword xMaximo = 0;
    ueword yMaximo = 0;
    for (size_t i = 0; i < pares.size(); ++i) {
        const ueword angulo = pares[i].primeiro;
        const ueword quantidade = pares[i].segundo;
        ++m_quantidadeAngulos;
        for (int j = 0; j < quantidade; ++j) {
            const SPar ponto = pares.at(++i);
            minucias.push_back(api::SXYT{ponto.primeiro, ponto.segundo, angulo, 0});
            if (ponto.primeiro < m_xMinimo) {
                m_xMinimo = ponto.primeiro;
            }
            if (ponto.primeiro > xMaximo) {
                xMaximo = ponto.primeiro;
            }
            if (ponto.segundo < m_yMinimo) {
                m_yMinimo = ponto.segundo;
            }
            if (ponto.segundo > yMaximo) {
                yMaximo = ponto.segundo;
            }
        }
    }
    m_bitsX = static_cast<ueword>(std::ceil(std::log2(xMaximo - m_xMinimo)));
    m_bitsY = static_cast<ueword>(std::ceil(std::log2(yMaximo - m_yMinimo)));
    return minucias;
}

} // namespace comum::asn
