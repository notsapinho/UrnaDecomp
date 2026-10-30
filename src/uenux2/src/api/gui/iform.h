#pragma once

// api::IForm<MEDIA> (/home/rubio/tse/uenux2/src/api/gui/iform.h: the records of FindFieldAs, line 142, and of
// GetRenderForm, line 178, name the file). Nothing here is TSE's text. RTTI gives IForm<IScreen>, IForm<IScreenMT> and
// IForm<IPaper>, each a class with no base; their vtables have 8 slots.
//
// The layout is what the constructor (fn 6024 for IScreen and IScreenMT, 5548 and 5522 passing it their vptr;
// IForm<IPaper>'s is inlined into fn 5515) and the destructor (IForm<IScreen>'s fn 2781, which destroys +60, +52, +28,
// +20 and +8 in that order) give; 72 bytes, the offset where CInteractiveForm's own members begin (fn 554):
//   +4       the flag IsVisible reads: the constructor zeroes it, slot 7 (fn 5539) stores 1, the code that covers a
//            form (fns 5540, 5541, 5987) stores 0, and its readers hold the mutex. Only those stores of 0 and 1 and its
//            size are evidence: the bool is chosen
//   +8       the form's fields: the destructor calls slot 6 (SetForm) of each with nullptr, and FindFieldAs (fn 1721)
//            walks them and casts from IFormField<IScreen> (typeinfo 1537332)
//   +20/+24  a std::shared_ptr the constructor copies from its second argument; slot 7 calls its slot 2 (Draw) with the
//            render form before the fields'. Its type is chosen: only that slot is evidence
//   +28      a std::mutex (the constructor zeroes 24 bytes; fn 2781 calls fn 150 there). Slots 4 and 7 hold it over the
//            flag test and the drawing, and the fields hold it to read the flag: only the unlock shows, fn 150 after
//            the load; the lock leaves no call in the target or in our link
//   +52/+56  a std::shared_ptr<FormControlBlock>: the constructor builds it with std::make_shared (RTTI names
//            __shared_ptr_emplace<api::FormControlBlock>, 140 bytes, so 128 of object: a byte set to 1 and, at +4, 124
//            bytes locked and unlocked by fns 3328 and 3327, between which fn 2781 clears the byte). The bool and the
//            std::shared_mutex are chosen: a std::shared_timed_mutex is 124 bytes too and links to the same module
//   +60      a std::string, assigned from an argument of fn 554
//
// The names of the data members, of slots 2, 3, 4, 6 and 7, of IsVisible, the constructor's parameters and of
// FormControlBlock's members, and slot 6's parameter type, are chosen: no evidence gives them. Its empty body, fn 425,
// takes one argument besides this; CInteractiveForm's override, fn 5529, searches a vector of 4-byte values for it, so
// the int may be a pointer. Refresh is named for its body (fn 11133, slot 4): under the mutex, when the flag is set, it
// calls Refresh on every field and then the render form's slot 27. IsVisible is a member by choice: the fields' code
// inlines its lock, read and unlock. GetRenderForm and FindFieldAs are the records' names; their definitions are not
// recovered, and their records' lines, 178 and 142, lie past this header. The destructor's body is not recovered
// either; its D0 (fn 11136, f136(f2781(p0))) is the shape of a destructor defined in the class.

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

#include "api/gui/iformfield.h"

namespace api {

/**
 * Bloco de controle de um formulário, compartilhado com quem precisa saber se ele ainda existe.
 */
struct FormControlBlock {
    bool m_ativo = true;
    std::shared_mutex m_mutex;
};

/**
 * Formulário: um conjunto de campos desenhados numa mídia.
 */
template <typename MEDIA>
class IForm {
public:
    IForm(const std::vector<std::shared_ptr<IFormField<MEDIA>>>& campos,
          const std::shared_ptr<IFormField<MEDIA>>& fundo);

    virtual ~IForm();

    virtual void Slot2();

    virtual void Slot3();

    virtual void Refresh();

    virtual MEDIA& GetRenderForm() const;

    virtual void Slot6(int) {}

    virtual void Slot7();

    template <typename T>
    std::shared_ptr<T> FindFieldAs(const std::string& nome) const;

    bool IsVisible() const
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        return m_visivel;
    }

protected:
    bool m_visivel = false;
    std::vector<std::shared_ptr<IFormField<MEDIA>>> m_campos;
    std::shared_ptr<IFormField<MEDIA>> m_fundo;
    mutable std::mutex m_mutex;
    std::shared_ptr<FormControlBlock> m_controle;
    std::string m_nome;
};

} // namespace api

// <stubs>
// f1721 · 296 B · unmatched · name unknown
// void f1721(i32, i32, i32) { ... }

// f11132 · 49 B · unmatched · name unknown
// ? f11132(i32) { ... }

// f11041 · 49 B · unmatched · name unknown
// ? f11041(i32) { ... }
// </stubs>
