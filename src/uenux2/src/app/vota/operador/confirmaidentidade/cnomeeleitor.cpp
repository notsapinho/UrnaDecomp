// vota::CNomeEleitor (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cnomeeleitor.cpp). This comment
// is the reconstruction's. The file's records are ProcessInput's (fn 10500, pending), lines 145 and 156; they stay blank.
// Written here: the destructor (the shared fns 244 and 387), the helper that builds the form, the constructor and GetInst
// (fn 5401) and the statics, whose lines are a choice before the records; the statics' exit destructors (fns 10503 and
// 10502) sit above StartState (10501) in their use band, so they are defined before it. src/units/239-uenux2-cnomeeleitor.mk
// says which of this is evidence.
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CNomeEleitor::~CNomeEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("Seção:", api::SPoint{30, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSecao::Text, api::SPoint{40, 3}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField(&comum::CEleitorDadoTTE::Text, api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("telaNomeEleitor", false);
}

} // namespace

CNomeEleitor::CNomeEleitor()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CNomeEleitor& CNomeEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CNomeEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CNomeEleitor> CNomeEleitor::s_inst;
std::mutex CNomeEleitor::s_mutex;






































































































} // namespace vota
