// vota::CInicioVotacao: no record names this file, its path is chosen
// (src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk says why). The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/iniciovotacao/ciniciovotacao.h"

#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

CInicioVotacao::~CInicioVotacao() = default;

CInicioVotacao::CInicioVotacao()
    : comum::CAppState(EVENTO_TICK)
    , m_form(CTelasVota::GetInst().GetTelaInicioVotacao())
    , m_inicio(comum::CConfiguracaoEleicao::GetInst().GetDataHoraInicioVotacao())
    , m_tick(CThreadEleitor::GetInst().AddStoppedTick(1000))
{
    api::CMTFormBuilder builder;
    const std::string hora = m_inicio.GetHora().Format("h");
    const std::string minuto = m_inicio.GetHora().Format("mm");

    builder.AddTextField("Aguarde o horário de início da votação", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Votação a partir das ", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    if (minuto == "00") {
        builder.AddTextField(hora + "h", api::SPoint{22, 2}, api::ALINHAMENTO_ESQUERDA);
    } else {
        builder.AddTextField(hora + "h" + minuto + "min", api::SPoint{22, 2}, api::ALINHAMENTO_ESQUERDA);
    }
    builder.AddTextField("Hora atual: ", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddClock(api::SPoint{13, 3});

    m_formOperador = builder.GetInteractiveForm("", true);
}

CInicioVotacao& CInicioVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInicioVotacao());
    }
    return *s_inst;
}

std::unique_ptr<CInicioVotacao> CInicioVotacao::s_inst;
std::mutex CInicioVotacao::s_mutex;

} // namespace vota
