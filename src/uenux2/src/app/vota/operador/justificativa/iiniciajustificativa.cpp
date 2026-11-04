#include "app/vota/operador/justificativa/iiniciajustificativa.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/justificativa/cjustificativaefetuada.h"
#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

namespace vota {

// (original lines 13-23: content not recovered)
#line 24
IIniciaJustificativa::IIniciaJustificativa(IConfirmaJustificativa* confirma) : m_confirma(confirma)
{
    if (!confirma) {
        throw CUeVotaError(EUE_VOTA_CONFIRMACAO_JUSTIFICATIVA_NULA, "Confirmação de justificativa nula");
    }
}

namespace {

bool Justificou(const std::string& titulo)
{
    return comum::CJustificador::GetInst().Find(ecourna::app::dados::CNumeroInscricaoEleitoral(titulo)) != nullptr;
}

} // namespace

void IIniciaJustificativa::StartState()
{
    const std::string titulo = GetIdentidadeEleitor().GetIdentificador();
    if (!Justificou(titulo)) {
        m_pNextState = m_confirma;
    } else {
        CJustificativaEfetuada::GetInst().SetRecebida(false);
        m_pNextState = &CJustificativaEfetuada::GetInst();
    }
}

void JustificaEleitor(ueint16 ano)
{
    comum::CJustificador& justificador = comum::CJustificador::GetInst();
    const std::string& titulo = GetIdentidadeEleitor().GetIdentificador();
    justificador.Justifica(titulo, ano);
    comum::CAppInfo::GetInst().GetVota().IncrementaQtdJustificativa();
    CSincronizaVota::SincronizaJustificativa();
    CJustificativaEfetuada::GetInst().SetRecebida(true);
}

} // namespace vota
