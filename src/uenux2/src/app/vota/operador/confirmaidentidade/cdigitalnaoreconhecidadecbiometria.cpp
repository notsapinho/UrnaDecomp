// vota::CDigitalNaoReconhecidaDecBiometria
// (app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.cpp, the class name in lower case). This
// comment is the reconstruction's: no record names this file or its functions, so every line is a choice
// (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CDigitalNaoReconhecidaDecBiometria::~CDigitalNaoReconhecidaDecBiometria() = default;

void CDigitalNaoReconhecidaDecBiometria::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CVerificaDadoEleitor::GetInst();
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
