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
// - Read (line 57, its record's EInputResult return) passes the input device to the slot 8 of the field with the
//   focus, through std::vector::at: the target gets CPolySingleton<INPUT>::instance() before the bounds check, so the
//   instance is a local first. comum's mesario states hold it inlined in their slot 7
//   (src/units/135-uenux2-comum-mesario-estados.mk). Chosen: SetFocus's name, the data members', parameters' and Read's
//   local's names, how the record's column 25 is spelled, and Slot6's parameter type (a pointer, which the base's empty
//   body, fn 425, takes as one word).
// - WaitAndRead (line 62, its record's): vota::CVisualizarCandidatos::StartState (fn 11876) holds it inlined, the
//   keyboard's instance kept, its slot 3 (HasKey) asked until it says yes, with api::CSystem::Dorme(10) between, then
//   Read's code. WaitAndRead's lines but 62, and Slot2's (moved down), are chosen.
// - GetEntradas: vota::CMostraQRCodeBU::ProcessInput and CMostraQRCodeCertificado::ProcessInput (fns 12051, 12038) read
//   the input fields' vector (+72, +76) and throw when it does not hold one field. Its name, its const reference
//   result and its lines (original 116-119) are chosen.
// - GetEntradaAtual: vota::CPedeIdentidade::ProcessTick (fn 10676) reads the text of the field with the focus,
//   std::vector::at with the index at +84. Its name, its pointer result and its lines (original 121-124) are chosen.
// - LimpaEntradas clears the input fields and focuses the first; fn 10689 holds it inlined by binaryen. Its name, its
//   being a member, its lines (126-132) and Slot2's and Slot3's loops kept in place are chosen (unit 121's fragment).

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

#include "api/gui/iform.h"
#include "api/gui/iinputfield.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"

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
    EInputResult Read()
    {
        auto& teclado = CPolySingleton<INPUT>::instance();
        return m_entradas.at(m_atual)->Read(teclado);
    }
    EInputResult WaitAndRead()
    {
        auto& teclado = CPolySingleton<INPUT>::instance();
        while (!teclado.HasKey()) {
            CSystem::Dorme(10);
        }
        return m_entradas.at(m_atual)->Read(teclado);
    }

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


    const std::vector<IInputField<MEDIA>*>& GetEntradas() const
    {
        return m_entradas;
    }

    IInputField<MEDIA>* GetEntradaAtual() const
    {
        return m_entradas.at(m_atual);
    }

    void LimpaEntradas()
    {
        for (auto* entrada : m_entradas) {
            entrada->Clear();
        }
        SetFocus(0);
    }

    // (original lines 134-144: content not recovered)
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
