#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CVerificaDadoEleitor::~CVerificaDadoEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("Digite o ANO de nascimento:", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    AdicionaCampoNumerico(builder, 4, true, api::SPoint{29, 3});
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: habilitar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CVerificaDadoEleitor::CVerificaDadoEleitor() : comum::CAppState(EVENTO_ENTRADA), m_form(MontaTela()) {}

CVerificaDadoEleitor& CVerificaDadoEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CVerificaDadoEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CVerificaDadoEleitor> CVerificaDadoEleitor::s_inst;
std::mutex CVerificaDadoEleitor::s_mutex;

void CVerificaDadoEleitor::StartState()
{
    CLogVota::GetInst().LogaSolicitacaoDadoPessoalEleitor();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
