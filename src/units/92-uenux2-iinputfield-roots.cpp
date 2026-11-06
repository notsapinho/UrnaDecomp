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
// __shared_ptr_emplace<CInputFieldControl<IScreenMT>> and stores CInputFieldControlBase<IScreenMT>'s vtable. So is fn
// 2383 (vota::AdicionaCampoNumerico, unit 110's ctelasvota.cpp), which builds a CInputField<CFramedText> and its
// __shared_ptr_pointer block and stores both vtables, so nothing below stands for those. So is fn 6624
// (adicionaBaseTelaVotoNuloConsulta, unit 110's ctelasvota.cpp: src/units/378-uenux2-ctelasvota-criatela.mk), whose
// AdicionaCampoNumero<CFramedText> builds __shared_ptr_emplace<CMaskedTextField<CFramedText>> and stores both its
// vtable and the field's, so nothing below stands for those either, and so is fn 3060
// (AdicionaCampoNumero<CGrayedFramedText>, ctelasvota.cpp's, unit 378's), which builds
// __shared_ptr_emplace<CMaskedTextField<CGrayedFramedText>> and stores both its vtable and the field's (the builder,
// the destructor emitter and the two sinks that stood for 4185 went). The other users are not reconstructed: fns 7787
// and 4185 (5913, unit 59's, and 3675, unit 120's, are in the link). So:
// - The optnone functions below are not rooted, and wasm-ld drops them with the constructors. They exist to make clang
//   emit what the target's builders emit (src/units/README.md "A class with no key function", "A control block"):
//   w92_emite_mascara calls the destructor by its qualified name; w92_emite_bloco_mascara instantiates the control
//   block as its builder does: std::shared_ptr<U>(T*) for __shared_ptr_pointer<CMaskedTextField<CFramedText>*> (fn
//   7787).
// - The static constructor takes the address of each vtable the target's unwritten builders store, which keeps every
//   slot. The target reaches Show, Hide, Read, Clear, SetLength, Rect, GetTypeName, Move and the D0s only through these
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

extern "C" {
extern const char w92_emplace_controlmt_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api18CInputFieldControlINS1_9IScreenMTEEENS_9allocatorIS4_EEEE");
extern const char w92_pointer_masked_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api16CMaskedTextFieldINS1_11CFramedTextEEENS_10shared_ptrIS4_E27__shared_ptr_default_deleteIS4_S4_EENS_9allocatorIS4_EEEE");
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CMaskedTextField<api::CFramedText>> w92_emite_bloco_mascara(
    api::CMaskedTextField<api::CFramedText>* campo)
{
    return std::shared_ptr<api::CMaskedTextField<api::CFramedText>>(campo);
}

__attribute__((optnone, noinline)) void w92_emite_mascara(api::CMaskedTextField<api::CFramedText>& campo)
{
    campo.api::CMaskedTextField<api::CFramedText>::~CMaskedTextField();
}

namespace {

// fn 2024, IInputField<IScreen>'s constructor, has six direct callers in the target (fns 901, 2383, 3675, 5565, 5913
// and 7787). 901 and 5565 are in the link and pass the length 0, true and false, and 5913 (unit 59) is too; the others
// pass other lengths and flags, and 2024's wasm type keeps every parameter. CampoNumeroA stands for 7787, building a
// CInputField<CFramedText> with the flags 7787 passes (true, false, true, false, false), its length and the rest
// varied from 901's and 5565's, or dead-argument elimination would fold those two's; 3675 (unit 120's) and 2383 (unit
// 110's, which passes its own parameters on) are in the link, and the stand-in for 2383 went.
//
// fn 1385, CFramedText's constructor, has eight direct callers in the target (fns 2383, 2384, 3675, 5535, 5913, 6624,
// 6652 and 7787), 5913 (unit 59), 3675 (unit 120), 2383, 6624 and 5535 (unit 110's and 173's; 5535 inlined into 3060)
// in the link. These two stand in for the
// others: the target's callers pass different lengths, points, fonts and alignments, so these do too, and each has a
// body no target function has.
__attribute__((noinline)) api::CFramedText* NovaMoldura(size_t n, const api::SPoint& p, const api::SFont& f)
{
    return new api::CFramedText(n, p, f, api::ALINHAMENTO_CENTRO);
}

__attribute__((noinline)) void MolduraEm(void* destino, size_t n, const api::SPoint& p, const api::SFont& f,
                                         api::ETextAlignment alinhamento)
{
    new (destino) api::CFramedText(n + 2, p, f, alinhamento);
}

__attribute__((noinline)) api::IInputField<api::IScreen>* CampoNumeroA(const std::shared_ptr<api::IInputValidation>& v,
                                                                       size_t n, const api::SPoint& p, const api::SFont& f)
{
    return new api::CInputField<api::CFramedText>(v, n, true, false, true, false, false, p, f, api::ALINHAMENTO_ESQUERDA);
}

const void* volatile w92_sink;

struct SW92Roots {
    SW92Roots()
    {
        w92_sink = reinterpret_cast<const void*>(&NovaMoldura);
        w92_sink = reinterpret_cast<const void*>(&MolduraEm);
        w92_sink = reinterpret_cast<const void*>(&CampoNumeroA);
        w92_sink = w92_emplace_controlmt_vt;
        w92_sink = w92_pointer_masked_vt;
    }
} w92_roots;

} // namespace
