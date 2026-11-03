#include "app/comum/comparecimentomesario/estados/ctitulomesarioinvalido.h"

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

std::unique_ptr<CTituloMesarioInvalido> CTituloMesarioInvalido::s_inst;
std::mutex CTituloMesarioInvalido::s_mutex;

// (original lines 19-21: content not recovered)
#line 22
namespace {

class CTituloMesarioInvalidoDS {
public:
    static std::string Text(const std::string& formato)
    {
        auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
        const std::string titulo = controladorMesario.GetTituloMesario();
        return std::vformat(formato, std::make_format_args(titulo));
    }
};

} // namespace

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaTituloMesarioInvalido()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Título inválido:", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&CTituloMesarioInvalidoDS::Text, api::SPoint{18, 1}, "{}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CTituloMesarioInvalido::CTituloMesarioInvalido()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaTituloMesarioInvalido();
}

CTituloMesarioInvalido::~CTituloMesarioInvalido() = default;

CTituloMesarioInvalido& CTituloMesarioInvalido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTituloMesarioInvalido());
    }
    return *s_inst;
}

// (original lines 64-72: content not recovered)
#line 73
const IControladorRegistraMesarios& CTituloMesarioInvalido::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

void CTituloMesarioInvalido::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaTituloInvalidoRegistroMesario();
}

void CTituloMesarioInvalido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

} // namespace comum
