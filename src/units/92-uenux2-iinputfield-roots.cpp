// Roots of unit 92: the input-field class templates, which have no key function, reached the way the target reaches them.
// None of their users is reconstructed: fns 901, 2383, 3675, 5530, 5913 and 395 build them, and they need
// ITimerScheduler::GetInst (fn 1259) or a mask's constructor (fn 1385), which need api::CPolySingleton. So:
// - The optnone functions below are not rooted, and wasm-ld drops them with the constructors. They exist to make clang
//   emit what the target's builders emit (src/units/README.md "A class with no key function", "A control block"):
//   w92_emite and w92_emite_mt build a CInputFieldControl as fns 5530 and 395 do, w92_emite_campo a CInputField as fn
//   2383 does; w92_emite_mascara and w92_emite_mascara_cinza call the destructor by its qualified name;
//   the w92_emite_bloco_* and w92_emite_controle* ones instantiate each
//   control block as its builder does: std::shared_ptr<U>(T*) for __shared_ptr_pointer<CInputField<CFramedText>*>
//   (fn 2383), <CMaskedTextField<CFramedText>*> (fn 7787) and <CInputFieldControl<IScreenMT>*> (fn 395), and
//   std::make_shared for __shared_ptr_emplace<CInputFieldControl<IScreen>> (fn 5530), <CInputFieldControl<IScreenMT>>
//   (fn 5410), <CMaskedTextField<CFramedText>> (fn 6624) and <CMaskedTextField<CGrayedFramedText>> (fn 4185). The
//   constructor of CInputFieldControlBase brings __shared_ptr_pointer<CControlValidation*> (fn 5565).
// - The static constructor takes the address of each vtable the target's own code stores, which keeps every slot. The
//   target reaches Show, Hide, Read, Clear, SetLength, Rect, GetTypeName, Move and the D0s only through these vtables,
//   and the D2s also from the D0s. Taking CInputFieldControlBase's vtables keeps nothing more; they are what fns 5565
//   and 5410 store.
// - The __func vtables keep the timer's lambda (fns 6306, 12381 to 12355, 11020 to 11023), which the target stores in the
//   constructors fns 2024 and 3673.
// - CFramedText's Rect and Move have their two direct callers in the fields (one target function each for the two masks,
//   and CInputField's): the target has a third, fns 10896 and 2770. DrawFrame's are the Draws and fn 5534, which the traps
//   of the pending file collapse, so Molduras stands in for them, with two of the colours fn 5534 passes.
// The header is included because nothing else instantiates the templates; everything this object emits and the unit
// claims is code a landed header defines. Compiled with APP_CXXFLAGS, like the other stand-ins. The 145 functions of the
// object compare equal under UENUX2_CXXFLAGS, by function with the object-local numbers masked.
#include "api/gui/cframedtext.h"
#include "api/gui/cgrayedframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cmaskedtextfield.h"
#include "api/gui/iscreen.h"

extern "C" {
extern const char w92_iinputfield_vt[] __asm__("_ZTVN3api11IInputFieldINS_7IScreenEEE");
extern const char w92_iinputfieldmt_vt[] __asm__("_ZTVN3api11IInputFieldINS_9IScreenMTEEE");
extern const char w92_controlbase_vt[] __asm__("_ZTVN3api22CInputFieldControlBaseINS_7IScreenEEE");
extern const char w92_controlbasemt_vt[] __asm__("_ZTVN3api22CInputFieldControlBaseINS_9IScreenMTEEE");
extern const char w92_control_vt[] __asm__("_ZTVN3api18CInputFieldControlINS_7IScreenEEE");
extern const char w92_controlmt_vt[] __asm__("_ZTVN3api18CInputFieldControlINS_9IScreenMTEEE");
extern const char w92_input_vt[] __asm__("_ZTVN3api11CInputFieldINS_11CFramedTextEEE");
extern const char w92_func_vt[] __asm__("_ZTVNSt3__210__function6__funcIZN3api11IInputFieldINS2_7IScreenEEC1ERKNS_10shared_ptrINS2_16IInputValidationEEEmbbbbbEUlvE_FvvEEE");
extern const char w92_funcmt_vt[] __asm__("_ZTVNSt3__210__function6__funcIZN3api11IInputFieldINS2_9IScreenMTEEC1ERKNS_10shared_ptrINS2_16IInputValidationEEEmbbbbbEUlvE_FvvEEE");
extern const char w92_emplace_masked_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api16CMaskedTextFieldINS1_11CFramedTextEEENS_9allocatorIS4_EEEE");
extern const char w92_emplace_maskedgray_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api16CMaskedTextFieldINS1_17CGrayedFramedTextEEENS_9allocatorIS4_EEEE");
extern const char w92_emplace_control_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api18CInputFieldControlINS1_7IScreenEEENS_9allocatorIS4_EEEE");
extern const char w92_emplace_controlmt_vt[] __asm__("_ZTVNSt3__220__shared_ptr_emplaceIN3api18CInputFieldControlINS1_9IScreenMTEEENS_9allocatorIS4_EEEE");
extern const char w92_pointer_input_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api11CInputFieldINS1_11CFramedTextEEENS_10shared_ptrINS1_11IInputFieldINS1_7IScreenEEEE27__shared_ptr_default_deleteIS9_S4_EENS_9allocatorIS4_EEEE");
extern const char w92_pointer_masked_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api16CMaskedTextFieldINS1_11CFramedTextEEENS_10shared_ptrIS4_E27__shared_ptr_default_deleteIS4_S4_EENS_9allocatorIS4_EEEE");
extern const char w92_pointer_validation_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api18CControlValidationENS_10shared_ptrINS1_16IInputValidationEE27__shared_ptr_default_deleteIS5_S2_EENS_9allocatorIS2_EEEE");
extern const char w92_pointer_controlmt_vt[] __asm__("_ZTVNSt3__220__shared_ptr_pointerIPN3api18CInputFieldControlINS1_9IScreenMTEEENS_10shared_ptrINS1_11IInputFieldIS3_EEE27__shared_ptr_default_deleteIS8_S4_EENS_9allocatorIS4_EEEE");
extern const char w92_masked_vt[] __asm__("_ZTVN3api16CMaskedTextFieldINS_11CFramedTextEEE");
extern const char w92_maskedgray_vt[] __asm__("_ZTVN3api16CMaskedTextFieldINS_17CGrayedFramedTextEEE");
}

__attribute__((optnone, noinline)) api::IInputField<api::IScreen>* w92_emite(int teclas)
{
    return new api::CInputFieldControl<api::IScreen>(teclas);
}

__attribute__((optnone, noinline)) api::IInputField<api::IScreenMT>* w92_emite_mt(int teclas)
{
    return new api::CInputFieldControl<api::IScreenMT>(teclas);
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

__attribute__((optnone, noinline)) std::shared_ptr<api::IInputField<api::IScreenMT>> w92_emite_bloco_mt(
    api::CInputFieldControl<api::IScreenMT>* campo)
{
    return std::shared_ptr<api::IInputField<api::IScreenMT>>(campo);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CInputFieldControl<api::IScreen>> w92_emite_controle(int teclas)
{
    return std::make_shared<api::CInputFieldControl<api::IScreen>>(teclas);
}

__attribute__((optnone, noinline)) std::shared_ptr<api::CInputFieldControl<api::IScreenMT>> w92_emite_controle_mt(
    int teclas)
{
    return std::make_shared<api::CInputFieldControl<api::IScreenMT>>(teclas);
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

// Calls DrawFrame twice with different arguments: no target function has this body.
__attribute__((noinline)) void Molduras(const api::CFramedText& mascara, api::IScreen& tela, size_t inicio)
{
    mascara.DrawFrame(inicio, static_cast<api::TColor>(3), tela);
    mascara.DrawFrame(inicio + 1, static_cast<api::TColor>(2), tela);
}

const void* volatile w92_sink;

struct SW92Roots {
    SW92Roots()
    {
        w92_sink = w92_iinputfield_vt;
        w92_sink = w92_iinputfieldmt_vt;
        w92_sink = w92_controlbase_vt;
        w92_sink = w92_controlbasemt_vt;
        w92_sink = w92_control_vt;
        w92_sink = w92_controlmt_vt;
        w92_sink = reinterpret_cast<const void*>(&Molduras);
        w92_sink = w92_input_vt;
        w92_sink = w92_func_vt;
        w92_sink = w92_funcmt_vt;
        w92_sink = w92_emplace_masked_vt;
        w92_sink = w92_emplace_maskedgray_vt;
        w92_sink = w92_emplace_control_vt;
        w92_sink = w92_emplace_controlmt_vt;
        w92_sink = w92_pointer_input_vt;
        w92_sink = w92_pointer_masked_vt;
        w92_sink = w92_pointer_validation_vt;
        w92_sink = w92_pointer_controlmt_vt;
        w92_sink = w92_masked_vt;
        w92_sink = w92_maskedgray_vt;
    }
} w92_roots;

} // namespace
