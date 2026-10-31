#pragma once

#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Campo que desenha uma imagem numa posição da tela.
 */
class CImageField : public IFormField<IScreen> {
public:
    CImageField(const SPoint& posicao, const SharedIImage& imagem, EAnchorPoint ancora);

    std::string GetTypeName() const override { return "CImageField"; }

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

protected:
    void SetImage(SharedIImage imagem);

    SPoint m_posicao;
    SharedIImage m_imagem;
    std::unique_ptr<SPoint> m_tamanho;
    EAnchorPoint m_ancora;
};

} // namespace api
