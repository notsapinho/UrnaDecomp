#include "app/comum/comparecimentomesario/estados/igestordadomesario.h"

#include <optional>

#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/estados/cmesarioregistrado.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace comum {

void IGestorDadoMesario::StartState()
{
    RegistraMesario();
    m_pNextState = &CMesarioRegistrado::GetInst();
}

void IGestorDadoMesario::RegistraMesario()
{
    CRegistradorMesario& registrador = CRegistradorMesario::GetInst();
    const CControladorReconhecimentoMesario& reconhecimento = CControladorReconhecimentoMesario::GetInst();
    const bool pertenceSecao = GetControlador().Slot13();
    const md::CComparecimentoMesario::EstadoReconhecimentoBiometrico estado = reconhecimento.GetEstadoBiometria();
    const md::CDedo::TipoDedo dedo = reconhecimento.GetDedo();
    const std::optional<int> idArquivo = reconhecimento.GetIdArquivo();
    const md::CEleitorIdentidade mesario(GetControlador().GetTituloMesario(),
                                         ecourna::app::dados::TipoIDInscricaoEleitoral);
    if (idArquivo.has_value()) {
        registrador.Registra(md::CComparecimentoMesario(mesario, Slot9(), pertenceSecao, estado, dedo,
                                                        api::CDateTime::Now(), *idArquivo));
    } else {
        registrador.Registra(
            md::CComparecimentoMesario(mesario, Slot9(), pertenceSecao, estado, dedo, api::CDateTime::Now()));
    }
    registrador.SaveCurrentInternal();
    GetControlador().Slot16();
}

// (original lines 43-62: content not recovered)
#line 63
const IControladorRegistraMesarios& IGestorDadoMesario::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
