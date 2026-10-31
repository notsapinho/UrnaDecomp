#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"

namespace comum {

CPedeDigitalMesario::~CPedeDigitalMesario() = default;

std::unique_ptr<CPedeDigitalMesario> CPedeDigitalMesario::s_inst;
std::mutex CPedeDigitalMesario::s_mutex;

// (original lines 14-114: content not recovered)
#line 115
void CPedeDigitalMesario::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

} // namespace comum
