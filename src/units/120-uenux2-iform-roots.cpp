// Roots: keep the unit's members in the skeleton link the way the target reaches them. Compiled with APP_CXXFLAGS, like
// the other stand-ins; it instantiates none of the unit's templates (the extern template below keeps CFormStack's copy
// out), so every body it reaches comes from the unit's objects.
//
//   FormInterativoA, FormInterativoB  the callers of 554, api::CInteractiveFormBuilder::GetInteractiveForm (1591, 1767,
//                     3063, 3064, 3067, 6616, 6626, 6639, 6681, 7787; 576 is linked): two call sites, or binaryen
//                     would inline it, with the name and the bool varied as theirs are
//   CampoA, CampoB    the callers of the control fields' adders, none reconstructed: of 901, AddInputControl() (1591,
//                     2376, 3063, 3064, 6626, 6639, 7787, 11804, 11809) and of 5530, AddInputControl(int) (7787 and
//                     12055, which pass the keys 6 and 5). Each adder gets two call sites
//   ControleTeclas    653, AddLabeledInputControl, not reconstructed, the other caller of 5565
//                     (CInputFieldControlBase<IScreen>'s constructor): it builds the control field over the mask of its
//                     keys with std::make_shared, as this does. With 5530 alone binaryen would inline 5565 into it
//   SaiDoFormulario   12081, vota::CEmitirMaisBU::ProcessInput, the other direct caller of 5987,
//                     api::CFormStack<api::IScreen>::Remove: with the destructor of IForm<IScreen> alone it would inline
//   TelaMT            the callers of 1714, api::CPolySingleton<api::IScreenMT>::instance, not in our link: 10410,
//                     10680, 10690. 11041 (IForm<IScreenMT>::GetRenderForm) and unit 153's CInfoMTLCD members 3836
//                     and 11653 call it in the link; the stand-in stays until those three land. It passes an empty
//                     std::source_location, as unit 100's w100_usa does: a default argument would make a record on this
//                     file's line, which no target function has
#include <memory>
#include <source_location>
#include <string>

#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/iscreen.h"

extern template void api::CFormStack<api::IScreen>::Remove(api::IForm<api::IScreen>*);
extern template api::IScreenMT& api::CPolySingleton<api::IScreenMT>::instance(api::TPolySingletonsInfo&,
                                                                              const std::source_location&);

namespace {

__attribute__((noinline)) int FormInterativoA(api::CInteractiveFormBuilder& form,
                                              const std::shared_ptr<api::IPreShow<api::IScreen>>& preShow,
                                              const std::string& nome, bool limpa)
{
    return form.GetInteractiveForm(preShow, nome, limpa).use_count();
}

__attribute__((noinline)) int FormInterativoB(api::CInteractiveFormBuilder& form,
                                              const std::shared_ptr<api::IPreShow<api::IScreen>>& preShow, int vezes)
{
    const auto interativo = form.GetInteractiveForm(preShow, std::string(), false);
    return vezes * interativo.use_count();
}

__attribute__((noinline)) int CampoA(api::CInteractiveFormBuilder& form)
{
    const auto controle = form.AddInputControl();
    const auto teclas = form.AddInputControl(6);
    return static_cast<int>(controle.use_count() + teclas.use_count());
}

__attribute__((noinline)) int CampoB(api::CInteractiveFormBuilder& form, int vezes)
{
    form.AddInputControl(5);
    form.AddInputControl();
    return vezes + 2;
}

__attribute__((noinline)) int ControleTeclas(int teclas)
{
    const auto campo = std::make_shared<api::CInputFieldControl<api::IScreen>>(teclas | 1);
    return static_cast<int>(campo.use_count()) + teclas;
}

__attribute__((noinline)) int SaiDoFormulario(api::IForm<api::IScreen>* form, int codigo)
{
    api::CFormStack<api::IScreen>::Remove(form);
    return codigo + 3;
}

__attribute__((noinline)) int TelaMT()
{
    const std::source_location local;
    api::IScreenMT& a = api::CPolySingleton<api::IScreenMT>::instance(api::g_polySingletonsInfo(), local);
    api::IScreenMT& b = api::CPolySingleton<api::IScreenMT>::instance(api::g_polySingletonsInfo(), local);
    return &a == &b ? 13 : 17;
}

void* volatile w120_sink;

struct SW120Roots {
    SW120Roots()
    {
        w120_sink = reinterpret_cast<void*>(&FormInterativoA);
        w120_sink = reinterpret_cast<void*>(&FormInterativoB);
        w120_sink = reinterpret_cast<void*>(&CampoA);
        w120_sink = reinterpret_cast<void*>(&CampoB);
        w120_sink = reinterpret_cast<void*>(&ControleTeclas);
        w120_sink = reinterpret_cast<void*>(&SaiDoFormulario);
        w120_sink = reinterpret_cast<void*>(&TelaMT);
    }
} w120_roots;

} // namespace
