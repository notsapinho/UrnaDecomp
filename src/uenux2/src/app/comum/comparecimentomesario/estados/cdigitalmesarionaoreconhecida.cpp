#include "app/comum/comparecimentomesario/estados/cdigitalmesarionaoreconhecida.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"

namespace comum {

CDigitalMesarioNaoReconhecida::~CDigitalMesarioNaoReconhecida() = default;

std::unique_ptr<CDigitalMesarioNaoReconhecida> CDigitalMesarioNaoReconhecida::s_inst;
std::mutex CDigitalMesarioNaoReconhecida::s_mutex;




























void CDigitalMesarioNaoReconhecida::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CDigitalMesarioNaoReconhecida::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

} // namespace comum
