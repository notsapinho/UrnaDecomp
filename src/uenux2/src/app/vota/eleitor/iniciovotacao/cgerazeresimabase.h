#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class CPaperFormBuilder;
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CGeraZeresimaBase (RTTI: si_class of comum::CAppState; vtable @1544384 [1720, 325, 11946, 7480, 1661, 218, 425,
// 218, 425, 12143, 12143]): an abstract state, the base of vota::CGeraZeresima and vota::CRegerarZeresima. Slot 1 is
// the trap an abstract class's deleting destructor is (fn 325), and slots 9 and 10 are pure (fn 12143). StartState
// (slot 2, fn 11946) ends by calling slot 9 and storing what slot 10 returns as the next state, as
// vota::CGeraResumoZeresimaBase's does. The layout is the constructor's (fn 5965): the base's constructor gets 0, and
// +12 a std::shared_ptr copied from vota::CTelasVota::GetInst()'s +212 (fn 407), whose slot 2 StartState calls; the
// pointee's type is that member's, api::IForm<api::IScreen> (CTelasVota's constructor stores GetFormulario's form
// there: ctelasvota.h). The destructor is out of line, in another object
// than the derived classes': their destructors (fns 5961 and 5960) call fn 1720, which stores this class's vptr and
// releases +12 (through binaryen's fn 2902). The constructor reads the member through a getter chosen for it
// (ctelasvota.h). StartState sets the next state to this and calls slot 2 of the form and vota::GeraZeresima
// (cgeradorzeresima.h), which binaryen inlines into it with the report it builds, before slots 9 and 10;
// src/units/325-uenux2-geradores-zeresima.mk has its evidence and the forms measured.
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CGeraZeresimaBase : public comum::CAppState {
public:
    virtual ~CGeraZeresimaBase() override;

    virtual void StartState() override;

protected:
    CGeraZeresimaBase();

    virtual void AposGeracao() = 0;

    virtual comum::CAppState* GetProximoEstado() = 0;

private:
    std::shared_ptr<api::IForm<api::IScreen>> m_form;
};

// No target index: two parts of the RDV extract's title, which fn 5971 (vota::CriaPartesExtratoRDV,
// cgeradorresumozeresima.cpp) holds behind stack frames of their own, binaryen's inlining of a function with one caller
// (docs/reference/facts/reading.md R10). ImprimeAvisoSemVotos adds "Não há votos ou justificativas registrados" in
// IPaper's style 2 between two centred lines of 38 '=' and a new line; ImprimeTituloExtratoRDV the extract's title line
// and a new line. Their object links after 5971's (measured: src/units/325-uenux2-geradores-zeresima.mk), so they are
// in another file than their caller; this file, the object after it in the data and in our link, their names and
// their being free functions of vota (they read no state) are chosen.
void ImprimeAvisoSemVotos(api::CPaperFormBuilder& builder);
void ImprimeTituloExtratoRDV(api::CPaperFormBuilder& builder);

} // namespace vota
