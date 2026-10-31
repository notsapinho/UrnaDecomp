#include "app/vota/eleitor/fimvotacao/climitecopiasbuatingido.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

namespace vota {

CLimiteCopiasBUAtingido::~CLimiteCopiasBUAtingido() = default;































void CLimiteCopiasBUAtingido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CMostraQRCodeBU::GetInst();
    }
}

} // namespace vota
