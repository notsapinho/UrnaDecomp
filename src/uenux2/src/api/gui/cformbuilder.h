#pragma once

#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

/**
 * Monta os formulários da interface.
 *
 * Só o membro estático GetLabeledKeyPos (target fn 5544) está reconstruído; o resto da classe (AddStatusHeader, fn 502,
 * cujos registros estão nas linhas 292 e 305 de cformbuilder.cpp) não está.
 */
class CFormBuilder {
public:
    static SPoint GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento);
};

} // namespace api
