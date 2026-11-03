// vota::CDigitalReconhecida (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cdigitalreconhecida.cpp).
// This comment is the reconstruction's. The file's one record is StartState's (line 47, column 22, the default
// argument of CPolySingleton's instance); every other line is a choice: the destructor before StartState, the order
// of the use band (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalreconhecida.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ifingermatcher.h"
#include "api/pattern/cpolysingleton.h"

namespace vota {

CDigitalReconhecida::~CDigitalReconhecida() = default;

// (original lines 17-43: content not recovered)
#line 44
void CDigitalReconhecida::StartState()
{
    m_pNextState = this;
    auto& digitais = api::CPolySingleton<api::IFingerMatcher>::instance();
    if (m_bMostraScore) {
        *m_score = std::format("Score: {}", digitais.Slot4());
    }
    m_form->Slot2();
}

} // namespace vota
