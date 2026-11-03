// comum's mesario registration: comum::CRegistrarMesarios, the state that asks whether to register the poll workers,
// with the operator's form it builds, and the voter's screen of the registration (target fn 1255) with its two fonts.
// The file is the one CRegistrarMesarios's records name (line 68, GetControlador, which fns 10391 and 10392 hold
// inlined). Every line here but the record's is a choice. That the voter's screen is in this file is a choice too: its
// fonts lie between CRegistrarMesarios's typeinfo name and CPedeTituloMesario's, an order that fits either file
// (src/units/247-uenux2-cregistrarmesarios.mk says why).
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/climitemesariosregistradosatingido.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CRegistrarMesarios::~CRegistrarMesarios() = default;

CRegistrarMesarios::CRegistrarMesarios()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaIndagaRegistroMesarios();
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaIndagaRegistroMesarios()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddTextField("Registrar mesário?", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Cancelar  CONFIRMA: Prosseguir", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CRegistrarMesarios& CRegistrarMesarios::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegistrarMesarios());
    }
    return *s_inst;
}

std::unique_ptr<CRegistrarMesarios> CRegistrarMesarios::s_inst;
std::mutex CRegistrarMesarios::s_mutex;

void CRegistrarMesarios::StartState()
{
    m_pNextState = this;
    GetControlador().LogaIndagaRegistroMesarios();
    GetControlador().Slot5();
    if (GetControlador().Slot7()) {
        m_pNextState = &CLimiteMesariosRegistradosAtingido::GetInst();
        return;
    }
    m_formEleitor->Slot2();
    m_form->Slot2();
}

// (original lines 64-65: content not recovered)
#line 66
const IControladorRegistraMesarios& CRegistrarMesarios::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

const api::SFont FONTE_TITULO_REGISTRO_MESARIOS{35, 0};
const api::SFont FONTE_TEXTO_REGISTRO_MESARIOS{25, 0};

std::shared_ptr<api::IForm<api::IScreen>> TelaRegistroMesarios()
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

} // namespace comum
