#pragma once

// api::IText: RTTI names the class; it has no vtable in the target. The alignment at +4 is this class's own. Every
// implementation holds fn 1661, `return *(p + 4)`, in slot 3, which alone only says they share a layout (binaryen keeps
// one of identical bodies). What decides is the store order in the call shapes where the two layouts differ: fns 10934
// and 10548 build an api::CFixedText and store the vptr, then +4, which a member set by IText's constructor gives there
// and one set in CFixedText's mem-initializer does not (+4 first). fn 10958 stores +4 first, and in its shape (a by-value
// copy of a string, then the constructor) both layouts compile to one body that does: it is neutral, not against. The
// default argument is chosen (fn 8757's WasmText stores 0 there, after its vptr).

#include <memory>
#include <string>

#include "api/gui/primitives.h"

namespace api {

enum ETextAlignment {
    ALINHAMENTO_ESQUERDA = 0,
    ALINHAMENTO_DIREITA = 1,
    ALINHAMENTO_CENTRO = 2,
};

/**
 * Fonte do texto exibido por um campo.
 */
class IText {
public:
    explicit IText(ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA)
        : m_alinhamento(alinhamento)
    {
    }

    virtual ~IText() = default;
    virtual std::string GetText() const = 0;
    virtual ETextAlignment GetAlignment() const { return m_alinhamento; }

private:
    ETextAlignment m_alinhamento;
};

using SharedIText = std::shared_ptr<IText>;

// Moves a text's anchor to where its first character goes. Fns 3889 and 10929 hold this switch: in 3889 the point is one
// 32-bit load that the code shifts, which a local whose address went to an inlined callee gives and a local read
// by its members does not (the fragment has the measurement). That this is a function of its own, and its name, are chosen.
inline void AlinhaPosicao(SPoint& posicao, ETextAlignment alinhamento, TPosition largura)
{
    switch (alinhamento) {
        case ALINHAMENTO_DIREITA:
            posicao.x -= largura;
            break;
        case ALINHAMENTO_CENTRO:
            posicao.x -= largura / 2;
            break;
        default:
            break;
    }
}

} // namespace api
