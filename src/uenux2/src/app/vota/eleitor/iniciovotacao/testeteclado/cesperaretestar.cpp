#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"

namespace vota::testeteclado {

namespace {

api::CDateTime s_fimEspera(0);

std::string TextoEspera(const std::string& formato)
{
    unsigned int segundos = 0;
    if (const api::CDateTime agora = api::CDateTime::Now(); agora < s_fimEspera) {
        segundos = s_fimEspera - agora;
    }
    return std::vformat(formato, std::make_format_args(segundos));
}

} // namespace

CEsperaRetestar::CEsperaRetestar()
    : CEstadoComDesligamentoAutomatico(EVENTO_TICK)
    , m_form(TelaEsperaRepetirTesteTeclado(TextoEspera))
    , m_tickEspera(CThreadEleitor::GetInst().AddStoppedTick(100))
    , m_segundosEspera(0)
{
}

CEsperaRetestar& CEsperaRetestar::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEsperaRetestar());
    }
    return *s_inst;
}

std::unique_ptr<CEsperaRetestar> CEsperaRetestar::s_inst;
std::mutex CEsperaRetestar::s_mutex;

CEsperaRetestar::~CEsperaRetestar() = default;

void CEsperaRetestar::StartState()
{
    m_segundosEspera += 5;
    m_pNextState = this;
    s_fimEspera = api::CDateTime::Now() + m_segundosEspera;
    CThreadEleitor::GetInst().StartTick(m_tickEspera);
    m_form->Slot2();
}

void CEsperaRetestar::FinishState()
{
    CThreadEleitor::GetInst().StopTick(m_tickEspera);
    m_form->Hide();
}

void CEsperaRetestar::ProcessTickNaoDesligamento(uebyte tick)
{
    if (tick == m_tickEspera && api::CDateTime::Now() >= s_fimEspera) {
        m_pNextState = &CTesteTeclado::GetInst();
    }
}

} // namespace vota::testeteclado
