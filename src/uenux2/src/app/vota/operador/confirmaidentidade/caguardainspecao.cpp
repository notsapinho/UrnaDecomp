// vota::CAguardaInspecao: no record names this file or any of its members. The reconstruction's notes are in the class
// header and in src/units/281-uenux2-cconfirmainspecionada.mk.

#include "app/vota/operador/confirmaidentidade/caguardainspecao.h"

#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "app/vota/operador/confirmaidentidade/cconfirmainspecionada.h"

namespace vota {

CAguardaInspecao::~CAguardaInspecao() = default;

namespace {

std::shared_ptr<api::IForm<api::IScreenMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Inspecione cabina e urna", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Instruções no terminal do eleitor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    return builder.GetForm("");
}

} // namespace

CAguardaInspecao::CAguardaInspecao()
    : comum::CAppState(EVENTO_TECLA)
    , m_form(MontaTela())
{
}

CAguardaInspecao& CAguardaInspecao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAguardaInspecao());
    }
    return *s_inst;
}

std::unique_ptr<CAguardaInspecao> CAguardaInspecao::s_inst;
std::mutex CAguardaInspecao::s_mutex;

void CAguardaInspecao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CAguardaInspecao::ProcessKey(uebyte tecla)
{
    if (tecla == 11) {
        m_pNextState = &CConfirmaInspecionada::GetInst();
    }
}

} // namespace vota
