#include "app/comum/comparecimentomesario/estados/cdigitalmesarionaoreconhecida.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/dados/celeitordetalhe.h"

namespace comum {

CDigitalMesarioNaoReconhecida::~CDigitalMesarioNaoReconhecida() = default;

// (original lines 14-20: content not recovered)
#line 21
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
        if (!eleitor.GetNomeUrna().empty()) {
            nome = eleitor.GetNomeUrna().substr(0, 40);
        } else {
            nome = eleitor.GetNome().substr(0, 40);
        }
        return std::vformat(formato, std::make_format_args(nome));
    }
};

} // namespace

CDigitalMesarioNaoReconhecida::CDigitalMesarioNaoReconhecida()
    : CAppState(EVENTO_ENTRADA)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField(&CNomeMesariosUrnaDS::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Mesário(a) não reconhecido(a).", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CONFIRMA: Retornar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    m_form = builder.GetInteractiveForm("", true);
}

CDigitalMesarioNaoReconhecida& CDigitalMesarioNaoReconhecida::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalMesarioNaoReconhecida());
    }
    return *s_inst;
}

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
