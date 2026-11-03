#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

#include <format>
#include <string>
#include <utility>

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/estados/cconfirmafimregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/cgestordadomesario.h"
#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/ctitulomesarioinvalido.h"
#include "app/comum/comparecimentomesario/estados/ctitulomesariojaregistrado.h"
#include "app/comum/comparecimentomesario/estados/ctitulomesariovazio.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"

namespace comum {
namespace {

IControladorRegistraMesarios& GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace

IPedeTituloMesario::IPedeTituloMesario(std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> form,
                                       std::shared_ptr<api::IForm<api::IScreen>> formEleitor)
    : CAppState(EVENTO_ENTRADA), m_form(std::move(form)), m_formEleitor(std::move(formEleitor))
{
}

void IPedeTituloMesario::StartState()
{
    m_pNextState = this;
    m_formEleitor->Slot2();
    m_form->Slot2();
}

std::shared_ptr<api::IForm<api::IScreen>> IPedeTituloMesario::GetTelaEleitor()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_MODO |
                            api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("REGISTRO DE MESÁRIOS", api::SPoint(320, 150), FONTE_TITULO_REGISTRO_MESARIOS,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Siga as instruções no terminal do mesário.", api::SPoint(320, 250),
                         FONTE_TEXTO_REGISTRO_MESARIOS, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    return builder.GetForm("");
}

void IPedeTituloMesario::ProcessInput()
{
    const api::EInputResult resultado = m_form->Read();
    if (resultado != api::INPUT_CONFIRMA && resultado != api::INPUT_CORRIGE) {
        return;
    }
    const api::IInputField<api::IScreenMT>* entrada = m_form->GetEntradas().at(0);
    if (resultado == api::INPUT_CONFIRMA) {
        if (entrada->GetTexto().empty()) {
            m_pNextState = &CTituloMesarioVazio::GetInst();
            return;
        }
        const std::string titulo = std::format("{:0>{}}", entrada->GetTexto(), 12);
        const std::string zeros(12, '0');
        GetControlador().SetTituloMesario(titulo);
        CAppState* proximo;
        if (!md::CValidadorIdentidade::GetInst().EhValida(ecourna::app::dados::TipoIDInscricaoEleitoral, titulo) ||
            titulo == zeros) {
            proximo = &CTituloMesarioInvalido::GetInst();
        } else if (MesarioJaRegistrado(titulo)) {
            proximo = &CTituloMesarioJaRegistrado::GetInst();
        } else {
            const bool exterior = CLocal::GetInst().EhExterior();
            const bool biometria = CConfiguracaoEleicao::GetInst().HabilitaBiometria();
            if (exterior || !biometria) {
                proximo = &CGestorDadoMesario::GetInst();
            } else {
                proximo = &CPedeDigitalMesario::GetInst();
            }
        }
        m_pNextState = proximo;
    } else if (entrada->GetTexto().empty()) {
        m_pNextState = &CConfirmaFimRegistroMesarios::GetInst();
    }
}

bool IPedeTituloMesario::MesarioJaRegistrado(const std::string& titulo) const
{
    CRegistradorMesario& registrador = CRegistradorMesario::GetInst();
    const md::CComparecimentoMesarioPK chave(md::CEleitorIdentidade(titulo, ecourna::app::dados::TipoIDInscricaoEleitoral),
                                             Slot9());
    return registrador.Find(chave) != nullptr;
}

} // namespace comum
