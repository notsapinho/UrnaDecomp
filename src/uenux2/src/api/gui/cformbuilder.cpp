// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp). Only the static GetLabeledKeyPos (target
// fn 5544) is reconstructed; its throw is a record of the target (line 372, column 11), so its position in this file is
// fixed. The file's other records, AddStatusHeader's throws at lines 292 and 305 (target fn 502), fall on blank lines.

#include "api/gui/cformbuilder.h"

#include <format>

#include "api/gui/eueguierror.h"

namespace api {

namespace {

// distâncias, em pixels, do rótulo de uma tecla às bordas da área em que ela é desenhada
constexpr TPosition MARGEM_ESQUERDA = 23;
constexpr TPosition MARGEM_DIREITA = 19;
constexpr TPosition DISTANCIA_BASE = 47;

} // namespace

// (original lines 22-347: content not recovered)
#line 348
/**
 * Posição do rótulo de uma tecla desenhada em @p area: junto à borda esquerda,
 * junto à direita ou no centro, conforme @p alinhamento, e acima da base,
 * deslocada de @p deslocamento.
 *
 * @throw CUeGuiError se o alinhamento for desconhecido
 */
SPoint CFormBuilder::GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento)
{
    SPoint posicao;
    switch (alinhamento) {
    case ALINHAMENTO_ESQUERDA:
        posicao = SPoint(area.left + MARGEM_ESQUERDA, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    case ALINHAMENTO_CENTRO: {
        const TPosition largura = area.right - area.left + 1;
        posicao = SPoint(area.left + largura / 2, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    }
    case ALINHAMENTO_DIREITA:
        posicao = SPoint(area.right - MARGEM_DIREITA, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    }

    throw CUeGuiError(EUE_GUI_GETLABELEDKEYPOS_ALINHAMENTO_DESCONHECIDO, std::format("Alinhamento desconhecido ({})", static_cast<int>(alinhamento)));
}

} // namespace api
