#pragma once

// api::IForm<MEDIA> (/home/rubio/tse/uenux2/src/api/gui/iform.h: the records of FindFieldAs, line 142, and of
// GetRenderForm, line 178 column 52, name the file) and what its members use: api::FormControlBlock,
// api::FormHandle<MEDIA> and api::CFormStack<MEDIA> with its nested CObservable (RTTI). Nothing here is TSE's text; the
// comments are the reconstruction's, and src/units/120-uenux2-iform.mk has the evidence, the forms measured and the
// choices.
// - IForm<MEDIA>: the layout is the constructor's (fn 6024, binaryen's one body of the IScreen and IScreenMT ones) and
//   the destructors' (fns 2781, 2776, 5514): +4 the visible flag, +8 the fields, +20 the pre-show (the
//   IPreShow<MEDIA> fns 301, 1694 and 5515 build), +28 a mutex, +52 the control block, +60 the name. Every member is
//   defined in the class, a choice; the destructor's D0 (fns 11136, 11045, 5513) calls the D2 and frees its result.
// - CFormStack<MEDIA>: the stack of the forms shown, per media two static members (guarded in __wasm_call_ctors) and two
//   function-local statics of GetObservable (a guard byte and a std::once_flag beside them). RTTI names the class only
//   through CObservable, whose base is api::IObservable<std::vector<FormHandle<MEDIA>>> (api/pattern/iobservable.h).
// - Chosen: Slot2, Slot3, Slot6 and Slot7 keep the names the landed callers use; Hide, Desenha, Redesenha, SetName,
//   every member of CFormStack, CObservable and FormHandle, the data members and every parameter. FindFieldAs (fn 1721)
//   is not written, so its line stays blank. The spacing before GetRenderForm's brace puts the call on the record's
//   column, a choice.

#include <algorithm>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

#include "api/gui/iformfield.h"
#include "api/gui/ipaper.h"
#include "api/gui/ipreshow.h"
#include "api/gui/iscreen.h"
#include "api/gui/iscreenmt.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/iobservable.h"

namespace api {

template <typename MEDIA>
class IForm;

struct FormControlBlock {
    bool m_ativo = true;
    std::shared_mutex m_mutex;
};

template <typename MEDIA>
struct FormHandle {
    IForm<MEDIA>* m_form;
    std::shared_ptr<FormControlBlock> m_controle;
};

template <typename MEDIA>
class CFormStack {
public:
    using Handles = std::vector<FormHandle<MEDIA>>;

    class CObservable : public IObservable<Handles> {
    public:
        void Inicia(const Handles& handles)
        {
            std::lock_guard<std::mutex> trava(this->m_mutex);
            this->m_valor = handles;
        }

        void Atualiza(const Handles& handles)
        {
            std::lock_guard<std::mutex> trava(this->m_mutex);
            this->m_valor = handles;
            for (auto* observer : this->m_observers) {
                observer->Update(this->m_valor);
            }
        }
    };

    static CObservable& GetObservable()
    {
        static CObservable s_observable;
        static std::once_flag s_iniciado;
        std::call_once(s_iniciado, [] { s_observable.Inicia(GetHandles()); });
        return s_observable;
    }

    static Handles GetHandles();

    static void Exibe(IForm<MEDIA>* form);

    static void Empilha(IForm<MEDIA>* form);

    static void Remove(IForm<MEDIA>* form);

    static void Notifica();

private:
    static std::mutex s_mutex;
    static std::vector<IForm<MEDIA>*> s_forms;
};

template <typename MEDIA>
class IForm {
public:
    IForm(const std::vector<std::shared_ptr<IFormField<MEDIA>>>& campos, const std::shared_ptr<IPreShow<MEDIA>>& preShow)
        : m_campos(campos), m_preShow(preShow), m_controle(std::make_shared<FormControlBlock>())
    {
        for (auto& campo : m_campos) {
            campo->SetForm(this);
        }
    }

    virtual ~IForm()
    {
        {
            std::lock_guard<std::shared_mutex> trava(m_controle->m_mutex);
            m_controle->m_ativo = false;
        }
        CFormStack<MEDIA>::Remove(this);
        for (auto& campo : m_campos) {
            campo->SetForm(nullptr);
        }
    }

    virtual void Slot2() { CFormStack<MEDIA>::Exibe(this); }

    virtual void Slot3() { CFormStack<MEDIA>::Empilha(this); }

    virtual void Refresh()
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        if (m_visivel) {
            MEDIA& midia = GetRenderForm();
            for (auto& campo : m_campos) {
                campo->Refresh(midia);
            }
            GetRenderForm().Refresh();
        }
    }

    // (original lines 136-177: content not recovered)
#line 178
    virtual MEDIA& GetRenderForm() const  { return CPolySingleton<MEDIA>::instance(); }

    virtual void Slot6(IFormField<MEDIA>*) {}

    virtual void Slot7()
    {
        m_visivel = true;
        Redesenha();
        for (auto& campo : m_campos) {
            campo->Show();
        }
    }

    bool IsVisible() const
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        return m_visivel;
    }

    void SetName(std::string nome) { m_nome = std::move(nome); }

protected:
    friend class CFormStack<MEDIA>;

    void Hide()
    {
        {
            std::lock_guard<std::mutex> trava(m_mutex);
            m_visivel = false;
        }
        for (auto& campo : m_campos) {
            campo->Hide();
        }
    }

    void Desenha()
    {
        MEDIA& midia = GetRenderForm();
        m_preShow->PreShow(midia);
        for (auto& campo : m_campos) {
            campo->Draw(midia);
        }
    }

    void Redesenha()
    {
        std::lock_guard<std::mutex> trava(m_mutex);
        if (m_visivel) {
            Desenha();
            GetRenderForm().Refresh();
        }
    }

    bool m_visivel = false;
    std::vector<std::shared_ptr<IFormField<MEDIA>>> m_campos;
    std::shared_ptr<IPreShow<MEDIA>> m_preShow;
    mutable std::mutex m_mutex;
    std::shared_ptr<FormControlBlock> m_controle;
    std::string m_nome;
};

template <typename MEDIA>
std::mutex CFormStack<MEDIA>::s_mutex;

template <typename MEDIA>
std::vector<IForm<MEDIA>*> CFormStack<MEDIA>::s_forms;

template <typename MEDIA>
typename CFormStack<MEDIA>::Handles CFormStack<MEDIA>::GetHandles()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    Handles handles;
    handles.reserve(s_forms.size());
    for (IForm<MEDIA>* form : s_forms) {
        handles.push_back(FormHandle<MEDIA>{form, form->m_controle});
    }
    return handles;
}

template <typename MEDIA>
void CFormStack<MEDIA>::Exibe(IForm<MEDIA>* form)
{
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        if (!s_forms.empty()) {
            s_forms.back()->Hide();
        }
        while (!s_forms.empty()) {
            s_forms.pop_back();
        }
        s_forms.push_back(form);
        form->Slot7();
    }
    Notifica();
}

template <typename MEDIA>
void CFormStack<MEDIA>::Empilha(IForm<MEDIA>* form)
{
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        if (!s_forms.empty()) {
            IForm<MEDIA>* topo = s_forms.back();
            if (form == topo) {
                return;
            }
            topo->Hide();
            auto it = std::find(s_forms.begin(), s_forms.end(), form);
            if (it != s_forms.end()) {
                s_forms.erase(it);
            }
        }
        s_forms.push_back(form);
        form->Slot7();
    }
    Notifica();
}

template <typename MEDIA>
void CFormStack<MEDIA>::Remove(IForm<MEDIA>* form)
{
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        auto it = std::find(s_forms.begin(), s_forms.end(), form);
        if (s_forms.empty() || it == s_forms.end()) {
            return;
        }
        if (form == s_forms.back()) {
            form->Hide();
        }
        s_forms.erase(it);
        for (IForm<MEDIA>* outro : s_forms) {
            if (outro == s_forms.back()) {
                outro->Slot7();
            } else {
                outro->Desenha();
            }
        }
    }
    Notifica();
}

template <typename MEDIA>
void CFormStack<MEDIA>::Notifica()
{
    GetObservable().Atualiza(GetHandles());
}

} // namespace api

// <stubs>
// f1721 � 296 B � unmatched � placement: link order � name unknown
// void f1721(i32, i32, i32) { ... }
// </stubs>
