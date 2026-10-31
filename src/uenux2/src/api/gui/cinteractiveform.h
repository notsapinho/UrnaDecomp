#pragma once

// api::CInteractiveForm<MEDIA, INPUT> (/home/rubio/tse/uenux2/src/api/gui/cinteractiveform.h, named by its records:
// Read() line 57, WaitAndRead() line 62, ClearKeyboardInput() line 148 column 13). Nothing here is TSE's text; the notes
// are the reconstruction's, and src/units/120-uenux2-iform.mk has the evidence and the forms measured.
// - Instances <IScreen, IInputKbd> (vtable @1579168) and <IScreenMT, IInputMT> (@1580280), si_classes of IForm<MEDIA>.
//   The layout is the constructor's (inlined into fns 554 and 301) and the destructor's (fns 11079, 11032): +72 the
//   input fields the constructor finds among the form's fields with dynamic_cast, +84 the index of the one with the
//   focus, +88 the constructor's bool, which slots 2 and 3 test before calling the keyboard's slot 4: the record's
//   column, two levels in, puts that test inside ClearKeyboardInput.
// - SetFocus (fn 1401, one body for both instances) takes the focus from the field that had it and gives it to the new
//   one (IInputField<MEDIA>::SetAtivo). Slot 6 (fn 5529) focuses the field it is given when it is one of the inputs.
// - Read and WaitAndRead are not written, so their lines stay blank. Chosen: SetFocus's name, the data members' and
//   parameters' names, and Slot6's parameter type (a pointer, which the base's empty body, fn 425, takes as one word).

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

#include "api/gui/iform.h"
#include "api/gui/iinputfield.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

template <typename MEDIA, typename INPUT>
class CInteractiveForm : public IForm<MEDIA> {
public:
    CInteractiveForm(const std::vector<std::shared_ptr<IFormField<MEDIA>>>& campos,
                     const std::shared_ptr<IPreShow<MEDIA>>& preShow, bool limpaTeclado)
        : IForm<MEDIA>(campos, preShow), m_limpaTeclado(limpaTeclado)
    {
        for (const auto& campo : campos) {
            if (auto* entrada = dynamic_cast<IInputField<MEDIA>*>(campo.get())) {
                m_entradas.push_back(entrada);
            }
        }
    }

    // (original lines 41-64: content not recovered)
#line 65
    void Slot2() override
    {
        for (auto* entrada : m_entradas) {
            entrada->Clear();
        }
        SetFocus(0);
        IForm<MEDIA>::Slot2();
        ClearKeyboardInput();
    }

    void Slot3() override
    {
        for (auto* entrada : m_entradas) {
            entrada->Clear();
        }
        SetFocus(0);
        IForm<MEDIA>::Slot3();
        ClearKeyboardInput();
    }

    void Slot6(IFormField<MEDIA>* campo) override
    {
        auto it = std::find_if(m_entradas.begin(), m_entradas.end(),
                               [campo](IInputField<MEDIA>* entrada) { return entrada == campo; });
        if (it != m_entradas.end()) {
            SetFocus(it - m_entradas.begin());
        }
    }

    void Slot7() override
    {
        IForm<MEDIA>::Slot7();
        SetFocus(m_atual);
    }

    void SetFocus(size_t indice)
    {
        if (indice < m_entradas.size()) {
            if (m_atual < m_entradas.size() && indice != m_atual) {
                m_entradas[m_atual]->SetAtivo(false);
            }
            m_entradas[indice]->SetAtivo(true);
            m_atual = indice;
        }
    }

    // (original lines 111-144: content not recovered)
#line 145
    void ClearKeyboardInput()
    {
        if (m_limpaTeclado) {
            CPolySingleton<INPUT>::instance().Clear();
        }
    }

private:
    std::vector<IInputField<MEDIA>*> m_entradas;
    size_t m_atual = 0;
    bool m_limpaTeclado;
};

} // namespace api

// <stubs>
// f12077 · 600 B · unmatched · placement: link order · name unknown
// void f12077(i32) { ... }

// f12034 · 169 B · unmatched · placement: link order · name unknown
// void f12034(i32) { ... }

// f12026 · 130 B · unmatched · placement: link order · name unknown
// void f12026(i32) { ... }

// f11931 · 655 B · unmatched · placement: link order · name unknown
// void f11931(i32) { ... }

// f11927 · 337 B · unmatched · placement: link order · name unknown
// void f11927(i32) { ... }

// f11920 · 168 B · unmatched · placement: link order · name unknown
// void f11920(i32) { ... }

// f11869 · 861 B · unmatched · placement: link order · name unknown
// void f11869(i32) { ... }

// f11848 · 349 B · unmatched · placement: link order · name unknown
// void f11848(i32) { ... }

// f11838 · 242 B · unmatched · placement: link order · name unknown
// void f11838(i32) { ... }

// f11834 · 448 B · unmatched · placement: link order · name unknown
// void f11834(i32) { ... }

// f11812 · 1108 B · unmatched · placement: link order · name unknown
// void f11812(i32) { ... }

// f11809 · 1111 B · unmatched · placement: link order · name unknown
// void f11809(i32) { ... }

// f11797 · 593 B · unmatched · placement: link order · name unknown
// void f11797(i32) { ... }

// f10740 · 944 B · unmatched · placement: link order · name unknown
// void f10740(i32) { ... }

// f10731 · 152 B · unmatched · placement: link order · name unknown
// void f10731(i32) { ... }

// f10727 · 130 B · unmatched · placement: link order · name unknown
// void f10727(i32) { ... }

// f10721 · 2309 B · unmatched · placement: link order · name unknown
// void f10721(i32) { ... }

// f10713 · 1389 B · unmatched · placement: link order · name unknown
// void f10713(i32) { ... }

// f10709 · 14 B · unmatched · placement: link order · name unknown
// void f10709(i32) { ... }

// f10698 · 130 B · unmatched · placement: link order · name unknown
// void f10698(i32) { ... }

// f10689 · 3059 B · unmatched · placement: link order · name unknown
// void f10689(i32) { ... }

// f10677 · 756 B · unmatched · placement: link order · name unknown
// void f10677(i32) { ... }

// f10667 · 14 B · unmatched · placement: link order · name unknown
// void f10667(i32) { ... }

// f10641 · 12 B · unmatched · placement: link order · name unknown
// void f10641(i32) { ... }

// f10626 · 1004 B · unmatched · placement: link order · name unknown
// void f10626(i32) { ... }

// f10624 · 167 B · unmatched · placement: link order · name unknown
// void f10624(i32) { ... }

// f10604 · 14 B · unmatched · placement: link order · name unknown
// void f10604(i32) { ... }

// f10601 · 12 B · unmatched · placement: link order · name unknown
// void f10601(i32) { ... }

// f10598 · 12 B · unmatched · placement: link order · name unknown
// void f10598(i32) { ... }

// f10588 · 1112 B · unmatched · placement: link order · name unknown
// void f10588(i32) { ... }

// f10527 · 300 B · unmatched · placement: link order · name unknown
// void f10527(i32) { ... }

// f10523 · 400 B · unmatched · placement: link order · name unknown
// void f10523(i32) { ... }

// f10511 · 179 B · unmatched · placement: link order · name unknown
// void f10511(i32) { ... }

// f10508 · 12 B · unmatched · placement: link order · name unknown
// void f10508(i32) { ... }

// f10504 · 12 B · unmatched · placement: link order · name unknown
// void f10504(i32) { ... }

// f10496 · 12 B · unmatched · placement: link order · name unknown
// void f10496(i32) { ... }

// f10493 · 12 B · unmatched · placement: link order · name unknown
// void f10493(i32) { ... }

// f10485 · 172 B · unmatched · placement: link order · name unknown
// void f10485(i32) { ... }

// f10481 · 926 B · unmatched · placement: link order · name unknown
// void f10481(i32) { ... }

// f10477 · 158 B · unmatched · placement: link order · name unknown
// void f10477(i32) { ... }

// f10473 · 172 B · unmatched · placement: link order · name unknown
// void f10473(i32) { ... }

// f10466 · 136 B · unmatched · placement: link order · name unknown
// void f10466(i32) { ... }

// f10461 · 14 B · unmatched · placement: link order · name unknown
// void f10461(i32) { ... }

// f10458 · 130 B · unmatched · placement: link order · name unknown
// void f10458(i32) { ... }

// f10452 · 158 B · unmatched · placement: link order · name unknown
// void f10452(i32) { ... }

// f10443 · 2761 B · unmatched · placement: link order · name unknown
// void f10443(i32) { ... }

// f10439 · 1039 B · unmatched · placement: link order · name unknown
// void f10439(i32) { ... }

// f10435 · 200 B · unmatched · placement: link order · name unknown
// void f10435(i32) { ... }

// f10415 · 2081 B · unmatched · placement: link order · name unknown
// void f10415(i32) { ... }

// f10407 · 191 B · unmatched · placement: link order · name unknown
// void f10407(i32) { ... }

// f10357 · 130 B · unmatched · placement: link order · name unknown
// void f10357(i32) { ... }

// f10352 · 14 B · unmatched · placement: link order · name unknown
// void f10352(i32) { ... }

// f10347 · 14 B · unmatched · placement: link order · name unknown
// void f10347(i32) { ... }

// f10342 · 14 B · unmatched · placement: link order · name unknown
// void f10342(i32) { ... }

// f10322 · 14 B · unmatched · placement: link order · name unknown
// void f10322(i32) { ... }

// f10317 · 130 B · unmatched · placement: link order · name unknown
// void f10317(i32) { ... }

// f11874 · 352 B · unmatched · placement: link order · name unknown
// void f11874(i32) { ... }

// f10757 · 14 B · unmatched · placement: link order · name unknown
// void f10757(i32) { ... }
// </stubs>
