#pragma once

#include "api/gui/iformfield.h"

namespace api {

class IScreenMT;

class CBuzzFieldMT : public IFormField<IScreenMT> {
public:
    CBuzzFieldMT(int frequencia, int duracao);

    void Draw(IScreenMT& screen) const override;

private:
    int m_frequencia;
    int m_duracao;
};

} // namespace api
