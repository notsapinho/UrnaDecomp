// vota::CEleitorEncontrado (/home/rubio/tse/uenux2/src/app/vota/operador/leidentidade/celeitorencontrado.cpp). The
// reconstruction's comment: the record is StartState's throw (fn 10635), line 102; every other line is a choice
// (src/units/104-uenux2-app-vota-estados.mk says which of this is evidence).
#include "app/vota/operador/leidentidade/celeitorencontrado.h"

#include <algorithm>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"
#include "app/vota/operador/justificativa/ciniciajustificativatemporario.h"
#include "app/vota/operador/justificativa/ciniciajustificativatransito.h"
#include "app/vota/operador/leidentidade/celeitorimpedidojustificar.h"
#include "app/vota/operador/leidentidade/celeitorimpedidojustificarvototransito.h"
#include "app/vota/operador/leidentidade/celeitorjavotou.h"
#include "app/vota/operador/leidentidade/celeitornaoencontrado.h"
#include "app/vota/operador/leidentidade/celeitornaopossuicargosparavotar.h"
#include "app/vota/operador/leidentidade/celeitornaotemidademinima.h"
#include "app/vota/operador/leidentidade/celeitoroptouporvotaremtransito.h"

namespace vota {

namespace {

bool AceitaJustificativaEmTransito()
{
    const auto tipos = comum::CConfiguracaoEleicao::GetInst().GetTipos();
    return std::ranges::find_if(tipos, [](auto tipo) { return tipo != 0; }) != tipos.end();
}

comum::md::ETipoImpedimento ImpedimentoNoTurno(const comum::CEleitorDetalhe& eleitor)
{
    const comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    return eleitor.GetImpedimentoTurno(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

bool PermiteJustificar(comum::md::ETipoImpedimento impedimento)
{
    return impedimento != comum::md::IMPEDIMENTO_SUSPENSO && impedimento != comum::md::IMPEDIMENTO_CANCELADO &&
           impedimento != comum::md::IMPEDIMENTO_NAO_LIBERADO;
}

comum::CAppState& EstadoEleitorImpedido(const comum::CEleitorDetalhe& eleitor)
{
    CLogVota::GetInst().LogaEleitorImpedido(eleitor.GetImpedimento());
    if (NaoAceitaJustificativa()) {
        if (eleitor.GetImpedimento() == comum::md::IMPEDIMENTO_SOLICITOU_VOTO_EM_TRANSITO) {
            return CEleitorOptouPorVotarEmTransito::GetInst();
        }
        return CEleitorNaoEncontrado::GetInst();
    }
    if (!PermiteJustificar(ImpedimentoNoTurno(eleitor))) {
        return CEleitorImpedidoJustificar::GetInst();
    }
    if (ImpedimentoNoTurno(eleitor) == comum::md::IMPEDIMENTO_SEM_IDADE_MINIMA) {
        return CEleitorNaoTemIdadeMinima::GetInst();
    }
    if (eleitor.GetImpedimento() == comum::md::IMPEDIMENTO_SOLICITOU_VOTO_EM_TRANSITO) {
        if (AceitaJustificativaEmTransito()) {
            return CIniciaJustificativaTransito::GetInst();
        }
        return CEleitorImpedidoJustificarVotoTransito::GetInst();
    }
    return CIniciaJustificativaTemporario::GetInst();
}

comum::CAppState& EstadoEleitorEncontrado(const comum::CEleitorDetalhe& eleitor)
{
    if (!eleitor.SemImpedimento()) {
        return EstadoEleitorImpedido(eleitor);
    }
    if (eleitor.GetDinamico().GetEstadoComparecimento() == 1) {
        return CEleitorNaoPossuiCargosParaVotar::GetInst();
    }
    if (eleitor.GetDinamico().GetEstadoComparecimento() == 3) {
        return CEleitorJaVotou::GetInst();
    }
    return CNomeEleitor::GetInst();
}

} // namespace

// (original lines 87-97: content not recovered)
#line 98
void CEleitorEncontrado::StartState()
{
    const comum::CEleitorDetalhe* eleitor = comum::CEleitores::GetInst().GetCurrent();
    if (eleitor == nullptr) {
        throw CUeVotaError(EUE_VOTA_ELEITOR_NAO_POSICIONADO, "Eleitor não posicionado");
    }
    m_pNextState = &EstadoEleitorEncontrado(*eleitor);
}

CEleitorEncontrado& CEleitorEncontrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorEncontrado());
    }
    return *s_inst;
}

CEleitorEncontrado::CEleitorEncontrado()
    : comum::CAppState(EVENTO_NENHUM)
{
}

std::unique_ptr<CEleitorEncontrado> CEleitorEncontrado::s_inst;
std::mutex CEleitorEncontrado::s_mutex;

} // namespace vota
