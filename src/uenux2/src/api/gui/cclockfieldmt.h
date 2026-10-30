#pragma once

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"

namespace api {

class IScreenMT;

class CClockFieldMT : public IFormField<IScreenMT> {
public:
    explicit CClockFieldMT(const SPoint& posicao);

    void Draw(IScreenMT& screen) const override;

private:
    SPoint m_posicao;
};

} // namespace api
