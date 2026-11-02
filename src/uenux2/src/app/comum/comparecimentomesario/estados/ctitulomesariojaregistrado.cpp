#include "app/comum/comparecimentomesario/estados/ctitulomesariojaregistrado.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

std::unique_ptr<CTituloMesarioJaRegistrado> CTituloMesarioJaRegistrado::s_inst;
std::mutex CTituloMesarioJaRegistrado::s_mutex;

// (original lines 19-22: content not recovered)
#line 23
namespace {

class CTituloMesarioJaRegistradoDS {
public:
    static std::string Text(const std::string& formato)
    {
        auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
        const std::string titulo = controladorMesario.GetTituloMesario();
        return std::vformat(formato, std::make_format_args(titulo));
    }
};

} // namespace

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaTituloMesarioJaRegistrado()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Título:", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&CTituloMesarioJaRegistradoDS::Text, api::SPoint{9, 1}, "{}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Já registrado", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

// (original lines 48-49: content not recovered)
#line 50
void CTituloMesarioJaRegistrado::StartState()
{
    m_pNextState = this;
    auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaMesarioJaRegistrado(controladorMesario.GetTituloMesario());
}

void CTituloMesarioJaRegistrado::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

CTituloMesarioJaRegistrado::CTituloMesarioJaRegistrado()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaTituloMesarioJaRegistrado();
}


const IControladorRegistraMesarios& CTituloMesarioJaRegistrado::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

CTituloMesarioJaRegistrado::~CTituloMesarioJaRegistrado() = default;

CTituloMesarioJaRegistrado& CTituloMesarioJaRegistrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTituloMesarioJaRegistrado());
    }
    return *s_inst;
}

} // namespace comum
