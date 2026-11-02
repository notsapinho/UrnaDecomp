#include "app/vota/operador/leidentidade/cprocuraeleitor.h"

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/justificativa/ciniciajustificativa.h"
#include "app/vota/operador/leidentidade/celeitorencontrado.h"
#include "app/vota/operador/leidentidade/celeitornaoencontrado.h"

namespace vota {

CProcuraEleitor::CProcuraEleitor()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
{
}

CProcuraEleitor& CProcuraEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CProcuraEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CProcuraEleitor> CProcuraEleitor::s_inst;
std::mutex CProcuraEleitor::s_mutex;

comum::CAppState& EstadoAposProcura()
{
    const comum::md::CEleitorIdentidade identidade = GetIdentidadeEleitor();
    const comum::CEleitorDetalhe* detalhe = comum::CEleitores::GetInst().LocalizaEleitor(
        comum::md::FormataIdentidade(identidade.GetIdentificador(), identidade.GetTipo()), identidade.GetTipo());
    if (detalhe == nullptr) {
        if (!NaoAceitaJustificativa() && identidade.GetTipo() == ecourna::app::dados::TipoIDInscricaoEleitoral) {
            return CIniciaJustificativa::GetInst();
        }
        return CEleitorNaoEncontrado::GetInst();
    }
    return CEleitorEncontrado::GetInst();
}

void CProcuraEleitor::StartState()
{
    m_pNextState = &EstadoAposProcura();
}

} // namespace vota
