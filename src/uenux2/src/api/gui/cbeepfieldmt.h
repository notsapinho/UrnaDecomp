#pragma once

#include "api/gui/iformfield.h"

namespace api {

class IScreenMT;

class CBeepFieldMT : public IFormField<IScreenMT> {
public:
    explicit CBeepFieldMT(int vezes);

    void Draw(IScreenMT& screen) const override;

private:
    int m_vezes;
};

} // namespace api
