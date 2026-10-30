#pragma once

// api::IText: RTTI names the class; it has no vtable in the target. The alignment at +4 is this class's own. Every
// implementation holds fn 1661, `return *(p + 4)`, in slot 3, which alone only says they share a layout (binaryen keeps
// one of identical bodies). What decides is where the constructor stores it: fns 10934 and 10548 build an api::CFixedText
// and store the vptr, then +4. An alignment set by the base's constructor comes before the derived class's vptr in the
// source and the backend reverses the two (docs/reference/facts/codegen.md C1); one set in CFixedText's mem-initializer
// gives +4 first, and neither function matches with it. fn 10958 does store +4 first, and it is not written yet, so that
// site is unexplained. The default argument is chosen (WasmText's in fn 8757 stores 0).

#include <memory>
#include <string>

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

} // namespace api
