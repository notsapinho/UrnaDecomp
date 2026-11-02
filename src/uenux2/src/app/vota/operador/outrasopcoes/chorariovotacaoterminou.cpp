#include "app/vota/operador/outrasopcoes/chorariovotacaoterminou.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CHorarioVotacaoTerminou::~CHorarioVotacaoTerminou() = default;

CHorarioVotacaoTerminou::CHorarioVotacaoTerminou()
    : comum::CAppState(EVENTO_ENTRADA)
{
    api::CMTFormBuilder builder;
    builder.AddBeep(2);
    builder.AddTextField("Horario de votacao terminou!", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Favor encerrar a urna!", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    m_form = builder.GetInteractiveForm("", true);
}

CHorarioVotacaoTerminou& CHorarioVotacaoTerminou::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CHorarioVotacaoTerminou());
    }
    return *s_inst;
}

std::unique_ptr<CHorarioVotacaoTerminou> CHorarioVotacaoTerminou::s_inst;
std::mutex CHorarioVotacaoTerminou::s_mutex;

void CHorarioVotacaoTerminou::StartState()
{
    CLogVota::GetInst().LogaHorarioVotacaoTerminou();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
