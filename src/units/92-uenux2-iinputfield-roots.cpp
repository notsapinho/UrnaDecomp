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
// __shared_ptr_emplace<CInputFieldControl<IScreenMT>> and stores CInputFieldControlBase<IScreenMT>'s vtable. The other
// users are not reconstructed: fns 2383, 3675, 7787, 6624 and 4185 (5913, unit 59's, is in the link). So:
// - The optnone functions below are not rooted, and wasm-ld drops them with the constructors. They exist to make clang
//   emit what the target's builders emit (src/units/README.md "A class with no key function", "A control block"):
//   w92_emite_campo builds a CInputField as fn 2383 does; w92_emite_mascara and w92_emite_mascara_cinza call the
//   destructor by its qualified name; the w92_emite_bloco_* ones instantiate each control block as its builder does:
//   std::shared_ptr<U>(T*) for __shared_ptr_pointer<CInputField<CFramedText>*> (fn 2383) and
//   <CMaskedTextField<CFramedText>*> (fn 7787), and std::make_shared for <CMaskedTextField<CFramedText>> (fn 6624) and
//   <CMaskedTextField<CGrayedFramedText>> (fn 4185).
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
#include "api/gui/cgrayedframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cmaskedtextfield.h"
#include "api/gui/iscreen.h"

extern "C" {
extern const char w92_input_vt[] __asm__("_ZTVN3api11CInputFieldINS_11CFramedTextEEE");
extern const char w92_emplace_masked_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api16CMaskedTextFieldINS1_11CFramedTextEEENS_9allocatorIS4_EEEE");
extern const char w92_emplace_maskedgray_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api16CMaskedTextFieldINS1_17CGrayedFramedTextEEENS_9allocatorIS4_EEEE");
extern const char w92_emplace_controlmt_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api18CInputFieldControlINS1_9IScreenMTEEENS_9allocatorIS4_EEEE");
extern const char w92_pointer_input_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api11CInputFieldINS1_11CFramedTextEEENS_10shared_ptrINS1_11IInputFieldINS1_7IScreenEEEE27__shared_ptr_default_deleteIS9_S4_EENS_9allocatorIS4_EEEE");
extern const char w92_pointer_masked_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api16CMaskedTextFieldINS1_11CFramedTextEEENS_10shared_ptrIS4_E27__shared_ptr_default_deleteIS4_S4_EENS_9allocatorIS4_EEEE");
extern const char w92_masked_vt[] __asm__("_ZTVN3api16CMaskedTextFieldINS_11CFramedTextEEE");
extern const char w92_maskedgray_vt[] __asm__("_ZTVN3api16CMaskedTextFieldINS_17CGrayedFramedTextEEE");
}

__attribute__((optnone, noinline)) api::IInputField<api::IScreen>* w92_emite_campo(
    const std::shared_ptr<api::IInputValidation>& v, size_t n, const api::SPoint& p, const api::SFont& f)
{
    return new api::CInputField<api::CFramedText>(v, n, true, false, true, false, false, p, f, api::ALINHAMENTO_ESQUERDA);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::IInputField<api::IScreen>> w92_emite_bloco_campo(
    api::CInputField<api::CFramedText>* campo)
{
    return std::shared_ptr<api::IInputField<api::IScreen>>(campo);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CMaskedTextField<api::CFramedText>> w92_emite_bloco_mascara(
    api::CMaskedTextField<api::CFramedText>* campo)
{
    return std::shared_ptr<api::CMaskedTextField<api::CFramedText>>(campo);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CMaskedTextField<api::CFramedText>> w92_emite_mascara_shared(
    api::SharedIText texto, size_t n, const api::SPoint& p, const api::SFont& f)
{
    return std::make_shared<api::CMaskedTextField<api::CFramedText>>(texto, n, p, f, api::ALINHAMENTO_ESQUERDA);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CMaskedTextField<api::CGrayedFramedText>>
w92_emite_mascara_cinza_shared(api::SharedIText texto, size_t n, const api::SPoint& p)
{
    return std::make_shared<api::CMaskedTextField<api::CGrayedFramedText>>(texto, n, p);
}

__attribute__((optnone, noinline)) void w92_emite_mascara(api::CMaskedTextField<api::CFramedText>& campo)
{
    campo.api::CMaskedTextField<api::CFramedText>::~CMaskedTextField();
}

__attribute__((optnone, noinline)) void w92_emite_mascara_cinza(api::CMaskedTextField<api::CGrayedFramedText>& campo)
{
    campo.api::CMaskedTextField<api::CGrayedFramedText>::~CMaskedTextField();
}

namespace {

// fn 2024, IInputField<IScreen>'s constructor, has six direct callers in the target (fns 901, 2383, 3675, 5565, 5913
// and 7787). 901 and 5565 are in the link and pass the length 0, true and false, and 5913 (unit 59) is too; the
// others pass other lengths and flags, and 2024's wasm type keeps every parameter. CampoNumeroA and CampoNumeroB
// stand for 2383, 3675 and 7787: each builds a CInputField<CFramedText> as 2383 does, with the length and the five
// flags varied from each other and from 901's and 5565's, or dead-argument elimination would fold those two's.
//
// fn 1385, CFramedText's constructor, has eight direct callers in the target (fns 2383, 2384, 3675, 5535, 5913, 6624,
// 6652 and 7787), only 5913 in the link (unit 59). These two stand in for the others: the target's callers pass
// different lengths, points, fonts and alignments, so these do too, and each has a body no target function has.
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

__attribute__((noinline)) api::IInputField<api::IScreen>* CampoNumeroB(const std::shared_ptr<api::IInputValidation>& v,
                                                                       const api::SPoint& p, const api::SFont& f,
                                                                       api::ETextAlignment alinhamento)
{
    return new api::CInputField<api::CFramedText>(v, 11, false, true, false, true, true, p, f, alinhamento);
}

const void* volatile w92_sink;

struct SW92Roots {
    SW92Roots()
    {
        w92_sink = reinterpret_cast<const void*>(&NovaMoldura);
        w92_sink = reinterpret_cast<const void*>(&MolduraEm);
        w92_sink = reinterpret_cast<const void*>(&CampoNumeroA);
        w92_sink = reinterpret_cast<const void*>(&CampoNumeroB);
        w92_sink = w92_input_vt;
        w92_sink = w92_emplace_masked_vt;
        w92_sink = w92_emplace_maskedgray_vt;
        w92_sink = w92_emplace_controlmt_vt;
        w92_sink = w92_pointer_input_vt;
        w92_sink = w92_pointer_masked_vt;
        w92_sink = w92_masked_vt;
        w92_sink = w92_maskedgray_vt;
    }
} w92_roots;

} // namespace
