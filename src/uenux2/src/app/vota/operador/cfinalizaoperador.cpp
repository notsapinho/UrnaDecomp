#include "app/vota/operador/cfinalizaoperador.h"

#include "api/gui/cmtformbuilder.h"

namespace vota {

namespace {

std::shared_ptr<api::IForm<api::IScreenMT>> MontaTelaEncerramento()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Procedimentos de Encerramento", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Siga as instruções na tela do eleitor", api::SPoint{20, 3}, api::ALINHAMENTO_CENTRO);
    return builder.GetForm("");
}

} // namespace

CFinalizaOperador::CFinalizaOperador()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFinalizaOperador& CFinalizaOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFinalizaOperador());
    }
    return *s_inst;
}

std::unique_ptr<CFinalizaOperador> CFinalizaOperador::s_inst;
std::mutex CFinalizaOperador::s_mutex;

void CFinalizaOperador::StartState()
{
    MontaTelaEncerramento()->Slot2();
    m_pNextState = nullptr;
}

} // namespace vota
