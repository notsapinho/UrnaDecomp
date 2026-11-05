// Roots: keep the unit's members in the skeleton link the way the target reaches them. Compiled with APP_CXXFLAGS, like
// the other stand-ins; it instantiates none of the unit's templates (the extern template below keeps CFormStack's copy
// out), so every body it reaches comes from the unit's objects.
//
//   FormInterativoA, FormInterativoB  the callers of 554, api::CInteractiveFormBuilder::GetInteractiveForm (1591, 1767,
//                     3063, 3064, 3067, 6616, 6626, 6639, 6681, 7787; 576 is linked): two call sites, or binaryen
//                     would inline it, with the name and the bool varied as theirs are
//   CampoA, CampoB    the callers of the control fields' adders, none reconstructed but 2376 (ctelasvota.cpp),
//                     11804 and 11809 (unit 217's, with ctelasvota.cpp's screens they hold) and 12055 (unit 37's,
//                     written): of 901, AddInputControl() (1591, 2376, 3063, 3064, 6626, 6639, 7787, 11804, 11809)
//                     and of 5530, AddInputControl(int) (7787 and 12055, which pass the keys 6 and 5). Each adder
//                     gets two call sites
//   RotulosA, RotulosB  the callers of 653, AddLabeledInputControl, none reconstructed but 2376 (ctelasvota.cpp), 2291
//                     (CRetirarMR::GetInst, two calls through ctelasvota.cpp's TelaLacreTampa and TelaMRModoDemo),
//                     11804 and 11809 (unit 217's), 11881 (unit 104's), 6599 (unit 110's, not matched) and 6569
//                     (unit 110's): 6592, 6595, 7787,
//                     11884, 11888, 11892 and 12040, which pass the same two constants as 2376 does: they stay while
//                     those callers wait. The target's 653 has neither of its last two parameters, folded by binaryen:
//                     it loads the area's corners from api::CApplication::s_areaTela (.data 1577200) and adds the keys'
//                     labels, so each passes s_areaTela and false (the flag's sense is cinteractiveformbuilder.cpp's
//                     choice). 653 is also 5565's (CInputFieldControlBase<IScreen>'s constructor) other caller beside
//                     5530
// api::CPolySingleton<api::IScreenMT>::instance (1714) needs no stand-in: every target caller the one here stood for,
// 10680 and 10690, is in the link.
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "api/gui/capplication.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/iscreen.h"

extern template void api::CFormStack<api::IScreen>::Remove(api::IForm<api::IScreen>*);

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

__attribute__((noinline)) int RotulosA(api::CInteractiveFormBuilder& form, const std::vector<std::pair<char, std::string>>& teclas)
{
    return static_cast<int>(form.AddLabeledInputControl(teclas, api::CApplication::s_areaTela, false).use_count());
}

__attribute__((noinline)) int RotulosB(api::CInteractiveFormBuilder& form, const std::vector<std::pair<char, std::string>>& teclas,
                                       int vezes)
{
    const auto campo = form.AddLabeledInputControl(teclas, api::CApplication::s_areaTela, false);
    return vezes * static_cast<int>(campo.use_count());
}

void* volatile w120_sink;

struct SW120Roots {
    SW120Roots()
    {
        w120_sink = reinterpret_cast<void*>(&FormInterativoA);
        w120_sink = reinterpret_cast<void*>(&FormInterativoB);
        w120_sink = reinterpret_cast<void*>(&CampoA);
        w120_sink = reinterpret_cast<void*>(&CampoB);
        w120_sink = reinterpret_cast<void*>(&RotulosA);
        w120_sink = reinterpret_cast<void*>(&RotulosB);
    }
} w120_roots;

} // namespace
