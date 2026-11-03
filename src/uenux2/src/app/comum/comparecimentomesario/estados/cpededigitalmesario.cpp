#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/hwil/ifingerscanner.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/dados/celeitordetalhe.h"

namespace comum {

CPedeDigitalMesario::~CPedeDigitalMesario() = default;

std::unique_ptr<CPedeDigitalMesario> CPedeDigitalMesario::s_inst;
std::mutex CPedeDigitalMesario::s_mutex;

// (original lines 22-40: content not recovered)
#line 41
namespace {

class CNomeMesariosUrnaDS {
public:
    static std::string Text(const std::string& formato)
    {
        auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
        if (!controladorMesario.Slot13()) {
            return controladorMesario.GetTituloMesario();
        }
        std::string nome;
        const md::CEleitorDecorator eleitor = controladorMesario.Slot14()->GetEleitor();
        nome = (eleitor.GetNomeUrna().empty() ? eleitor.GetNome() : eleitor.GetNomeUrna()).substr(0, 40);
        return std::vformat(formato, std::make_format_args(nome));
    }
};

} // namespace

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaPedeDigitalMesario()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBuzz(52, 5);
    builder.AddTextField("Solicite que o(a) mesário(a)", api::SPoint{1, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(&CNomeMesariosUrnaDS::Text, api::SPoint{1, 2}, "{:2}", api::ALINHAMENTO_CENTRO);
    builder.AddTextField("posicione POLEGAR ou INDICADOR no sensor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaAguardeDigitalMesario()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Por favor, aguarde.", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

CPedeDigitalMesario::CPedeDigitalMesario()
    : CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickCaptura(GetControlador().AddTick(15000))
    , m_tickEspera(GetControlador().AddTick(50))
    , m_form(TelaPedeDigitalMesario())
    , m_formAguarde(TelaAguardeDigitalMesario())
{
}

CPedeDigitalMesario& CPedeDigitalMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeDigitalMesario());
    }
    return *s_inst;
}

// (original lines 99-101: content not recovered)
#line 102
void CPedeDigitalMesario::StartState()
{
    GetControlador().LogaPedidoBiometriaMesario();
    m_form->Slot2();
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(2);
    GetControlador().StartTick(m_tickCaptura);
    GetControlador().StartTick(m_tickEspera);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot3();
    m_pNextState = this;
}

// (original lines 113-114: content not recovered)
#line 115
void CPedeDigitalMesario::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

// (original lines 122-295: content not recovered)
#line 296
void CPedeDigitalMesario::FinishState()
{
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
}

const IControladorRegistraMesarios& CPedeDigitalMesario::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
