// vota::CDigitalNaoReconhecidaPorTempo (app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.cpp, the
// class name in lower case). This comment is the reconstruction's: no record names this file or its functions, so every
// line is a choice (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CDigitalNaoReconhecidaPorTempo::~CDigitalNaoReconhecidaPorTempo() = default;

void CDigitalNaoReconhecidaPorTempo::StartState()
{
    m_pNextState = this;
    *m_tentativa = std::format("Tentativa {} de {}", CControlaReconhecimento::GetInst().GetTentativa(),
                               CControlaReconhecimento::GetInst().GetLimiteTentativas());
    CLogVota::GetInst().LogaTimeoutReconhecimentoDedo(CControlaReconhecimento::GetTentativa(),
                                                      CControlaReconhecimento::GetLimiteTentativas());
    m_form->Slot2();
}

void CDigitalNaoReconhecidaPorTempo::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (CControlaReconhecimento::AtingiuLimiteTentativas()) {
            m_pNextState = &CVerificaDadoEleitor::GetInst();
        } else {
            CControlaReconhecimento::AvancaTentativa();
            m_pNextState = &CPedeDigital::GetInst();
        }
        break;
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaReconhecimentoBiometrico();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
