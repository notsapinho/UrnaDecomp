// comum's poll-worker registration, continued: comum::CMesarioRegistrado, the state after a poll worker is registered,
// with the operator's form it builds. The file is the one the class's record names (line 72, GetControlador, which fns
// 10338 and 10339 hold inlined); every line here but the record's is a choice. GetInst, the constructor and the form's
// builder are written from IGestorDadoMesario::StartState (fn 10337, not written), which holds them inlined; nothing
// in the link calls them yet.
#include "app/comum/comparecimentomesario/estados/cmesarioregistrado.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cconfirmafimregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/climitemesariosregistradosatingido.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CMesarioRegistrado::~CMesarioRegistrado() = default;

CMesarioRegistrado::CMesarioRegistrado()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaMesarioRegistrado();
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaMesarioRegistrado()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddTextField("Mesário registrado com sucesso.", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Continuar registrando mesários?", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Encerrar  CONFIRMA: Prosseguir", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CMesarioRegistrado& CMesarioRegistrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMesarioRegistrado());
    }
    return *s_inst;
}

std::unique_ptr<CMesarioRegistrado> CMesarioRegistrado::s_inst;
std::mutex CMesarioRegistrado::s_mutex;

void CMesarioRegistrado::StartState()
{
    SetNextState(this);
    GetControlador().LogaMesarioRegistrado(GetControlador().GetTituloMesario());
    if (GetControlador().Slot7()) {
        SetNextState(&CLimiteMesariosRegistradosAtingido::GetInst());
        return;
    }
    GetControlador().LogaIndagaContinuaRegistro();
    m_formEleitor->Slot2();
    m_form->Slot2();
}

// (original lines 66-69: content not recovered)
#line 70
const IControladorRegistraMesarios& CMesarioRegistrado::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

void CMesarioRegistrado::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        GetControlador().LogaConfirmouRegistroMesarios();
        SetNextState(&CPedeTituloMesario::GetInst());
        break;
    case api::INPUT_CORRIGE:
        GetControlador().LogaCancelouRegistroMesarios();
        SetNextState(&CConfirmaFimRegistroMesarios::GetInst());
        break;
    }
}

} // namespace comum
