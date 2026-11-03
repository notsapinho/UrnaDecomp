#include "app/comum/comparecimentomesario/estados/ctitulomesariovazio.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CTituloMesarioVazio::~CTituloMesarioVazio() = default;

std::unique_ptr<CTituloMesarioVazio> CTituloMesarioVazio::s_inst;
std::mutex CTituloMesarioVazio::s_mutex;

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaTituloMesarioVazio()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Título inválido: número vazio", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CTituloMesarioVazio::CTituloMesarioVazio()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaTituloMesarioVazio();
}

CTituloMesarioVazio& CTituloMesarioVazio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTituloMesarioVazio());
    }
    return *s_inst;
}

void CTituloMesarioVazio::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaTituloInvalidoRegistroMesario();
}

// (original lines 51-54: content not recovered)
#line 55
const IControladorRegistraMesarios& CTituloMesarioVazio::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

void CTituloMesarioVazio::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

} // namespace comum
