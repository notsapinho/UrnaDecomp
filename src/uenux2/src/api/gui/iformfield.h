#pragma once

// api::IFormFieldBase<MEDIA> and api::IFormField<MEDIA> (/home/rubio/tse/uenux2/src/api/gui/iformfield.h, the file is
// chosen: no record names it). RTTI gives IFormField<IScreen>, IFormField<IScreenMT> and IFormField<IPaper>, each an
// si_class of IFormFieldBase of the same media (ledger/classes.json), and the field vtables (ledger/vtables.json) give
// each media its own IFormField:
//   IScreen    10 slots: the 8 of IFormFieldBase, then Rect and Move (api::CTextFieldMultiLine, api::CTextField); slot 7,
//              GetTypeName, is every field's own (no string "IFormField<IScreen>" in the target)
//   IScreenMT  8 slots, no Rect/Move; slot 7 is one body in all ten IScreenMT field vtables (target fn 11051), which
//              returns "IFormField<IScreenMT>" (api::CTextFieldMT, api::CLedFieldMT, api::CBeepFieldMT, ...)
//   IPaper     8 slots, no Rect/Move; slot 7 (target fn 11014) returns "IFormField<IPaper>" (api::CTextFieldPaper, ...)
// so the primary template is only declared and each media has an explicit specialization. IFormFieldBase<MEDIA>'s own
// vtable (IScreen @1537360, IScreenMT @1579652, IPaper @1580868) has __cxa_pure_virtual in slots 2 and 7.

#include <string>

#include "api/gui/primitives.h"

namespace api {

template <typename MEDIA>
class IForm;

class IScreen;
class IScreenMT;
class IPaper;

/**
 * Campo de um formulário, desenhado numa mídia (tela, papel).
 */
template <typename MEDIA>
class IFormFieldBase {
public:
    virtual ~IFormFieldBase() = default;

    virtual void Draw(MEDIA& media) const = 0;

    virtual void Show() {}

    virtual void Hide() {}

    /**
     * Redesenha o campo se ele foi alterado desde o último desenho.
     *
     * @return true se o campo foi redesenhado
     */
    virtual bool Refresh(MEDIA& media)
    {
        const bool alterado = m_alterado;
        m_alterado = false;
        if (alterado) {
            Draw(media);
        }
        return alterado;
    }

    virtual void SetForm(IForm<MEDIA>* form) { m_form = form; }

    virtual std::string GetTypeName() const = 0;

protected:
    bool m_alterado = false;
    IForm<MEDIA>* m_form = nullptr;
    std::string m_nome;
};

/**
 * Campo de um formulário numa mídia; cada mídia define o seu.
 */
template <typename MEDIA>
class IFormField;

/**
 * Campo desenhado na tela: ocupa um retângulo e pode ser movido.
 */
template <>
class IFormField<IScreen> : public IFormFieldBase<IScreen> {
public:
    virtual SRect Rect() const = 0;

    virtual void Move(const SPoint& posicao) = 0;
};

/**
 * Campo desenhado na tela MT.
 */
template <>
class IFormField<IScreenMT> : public IFormFieldBase<IScreenMT> {
public:
    std::string GetTypeName() const override { return "IFormField<IScreenMT>"; }
};

/**
 * Campo impresso no papel.
 */
template <>
class IFormField<IPaper> : public IFormFieldBase<IPaper> {
public:
    std::string GetTypeName() const override { return "IFormField<IPaper>"; }
};

} // namespace api
