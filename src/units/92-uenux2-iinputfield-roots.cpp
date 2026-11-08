// Roots of unit 92: the input-field class templates, which have no key function, reached the way the target reaches them.
// Two of their IScreen builders are in the link, fns 901 and 5530 (api::CInteractiveFormBuilder's AddInputControl,
// api/gui/cinteractiveformbuilder.cpp), and with them CInputFieldControlBase<IScreen>'s constructor (fn 5565) and
// IInputField<IScreen>'s (fn 2024): they store IInputField<IScreen>'s vtable and its lambda's __func vtable,
// CInputFieldControlBase<IScreen>'s and CInputFieldControl<IScreen>'s, and build
// __shared_ptr_emplace<CInputFieldControl<IScreen>> and __shared_ptr_pointer<CControlValidation*>, so nothing below
// stands for those. One IScreenMT builder is in the link too, fn 395 (api::CMTFormBuilder::AddInputControl,
// api/gui/cmtformbuilder.cpp), and with it IInputField<IScreenMT>'s constructor (fn 3673): they store
// CInputFieldControl<IScreenMT>'s vtable, IInputField<IScreenMT>'s and its lambda's __func vtable, and build
// __shared_ptr_pointer<CInputFieldControl<IScreenMT>*>, so nothing below stands for those either, and so is fn 5410
// (vota::MontaTelaEleitorPodeVotar, unit 161), whose inlined CMTFormBuilder::AddInputControl(int) builds
// __shared_ptr_emplace<CInputFieldControl<IScreenMT>> and stores CInputFieldControlBase<IScreenMT>'s vtable (the
// block's sink went: 5410 stores its vptr, and the link without it moved no row). So is fn
// 2383 (vota::AdicionaCampoNumerico, unit 110's ctelasvota.cpp), which builds a CInputField<CFramedText> and its
// __shared_ptr_pointer block and stores both vtables, so nothing below stands for those. So is fn 6624
// (adicionaBaseTelaVotoNuloConsulta, unit 110's ctelasvota.cpp: src/units/378-uenux2-ctelasvota-criatela.mk), whose
// AdicionaCampoNumero<CFramedText> builds __shared_ptr_emplace<CMaskedTextField<CFramedText>> and stores both its
// vtable and the field's, so nothing below stands for those either, and so is fn 3060
// (AdicionaCampoNumero<CGrayedFramedText>, ctelasvota.cpp's, unit 378's), which builds
// __shared_ptr_emplace<CMaskedTextField<CGrayedFramedText>> and stores both its vtable and the field's (the builder,
// the destructor emitter and the two sinks that stood for 4185 went), and so is fn 4185 (AdicionaDadosCandidato, unit
// 378's), whose AdicionaCampoNumero<CGrayedFramedText, comum::CCandidaturasDSNumero> builds the same block. So is fn
// 7787's CreateInst (unit 443's, through unit 441's roots), whose vota::AdicionaNumeroPartido builds
// __shared_ptr_pointer<CMaskedTextField<CFramedText>*> as std::shared_ptr<U>(T*) and stores both vtables, and whose
// screens call CFramedText's constructor twice and IInputField<IScreen>'s once: the block's builder and vtable sink and
// the stand-ins MolduraEm and CampoNumeroA, which stood for those, went (5913, unit 59's, and 3675, unit 120's, are in
// the link too). So:
// - The optnone function below is not rooted, and wasm-ld drops it. It exists to make clang emit what the target's
//   builders emit (src/units/README.md "A class with no key function"): w92_emite_mascara calls the destructor by its
//   qualified name.
// - The target reaches Show, Hide, Read, Clear, SetLength, Rect, GetTypeName, Move and the D0s only through the
//   vtables, and the D2s also from the D0s.
// - CFramedText's Rect and Move have their two direct callers in the fields (one target function each for the two masks,
//   and CInputField's): the target has a third, fns 10896 and 2770. DrawFrame's are fn 5534 (twice), the Draw 12438 and
//   fn 10897 (CInputMenuField::Draw, unit 84), all in the link.
// The header is included because nothing else instantiates the templates; everything this object emits and the unit
// claims is code a landed header defines. Compiled with APP_CXXFLAGS, like the other stand-ins; what UENUX2_CXXFLAGS
// gives for it is in src/units/92-uenux2-iinputfield.mk.
#include "api/gui/cframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cmaskedtextfield.h"
#include "api/gui/iscreen.h"

__attribute__((optnone, noinline)) void w92_emite_mascara(api::CMaskedTextField<api::CFramedText>& campo)
{
    campo.api::CMaskedTextField<api::CFramedText>::~CMaskedTextField();
}
