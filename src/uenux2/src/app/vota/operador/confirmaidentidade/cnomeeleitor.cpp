// vota::CNomeEleitor (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cnomeeleitor.cpp). This comment
// is the reconstruction's. The file's records, lines 145 and 156, are NavegaBiometrica's and NavegaAnoNascimento's (in
// ProcessInput, fn 10500). The other lines are a choice: the statics' exit destructors (fns 10503 and 10502) sit above
// StartState (10501), and StartState above ProcessInput, in their use band, so they are defined in that order; the
// helpers ProcessInput holds come after it. HabilitaEleitor (5400) is in cnomeeleitorauxiliares.cpp.
// src/units/239-uenux2-cnomeeleitor.mk says which of this is evidence.
#include "app/vota/operador/confirmaidentidade/cnomeeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/fotoeleitor.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cinformaanodesabilitadodemo.h"
#include "app/vota/operador/confirmaidentidade/cinformabiodesabilitadademo.h"
#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CNomeEleitor::~CNomeEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("Seção:", api::SPoint{30, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSecao::Text, api::SPoint{40, 3}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField(&comum::CEleitorDadoTTE::Text, api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("telaNomeEleitor", false);
}

} // namespace

CNomeEleitor::CNomeEleitor()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CNomeEleitor& CNomeEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CNomeEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CNomeEleitor> CNomeEleitor::s_inst;
std::mutex CNomeEleitor::s_mutex;

void CNomeEleitor::StartState()
{
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        HabilitaEleitor();
        return;
    }
    ApresentaFotoEleitor();
    m_form->Slot2();
    m_pNextState = this;
}

// (original lines 81-90: content not recovered)
#line 91
void CNomeEleitor::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetPedeAnoNascimentoEleitor()) {
            ConfirmaComAnoNascimento();
        } else {
            ConfirmaSemAnoNascimento();
        }
        break;
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
        break;
    default:
        break;
    }
}

void CNomeEleitor::ConfirmaComAnoNascimento()
{
    bool temDedos = false;
    if (comum::CLocal::GetInst().UrnaBiometrica() && comum::CEleitores::GetInst().GetCurrent()->GetEleitor().TemBiometria()) {
        temDedos = comum::CEleitores::GetInst().GetCurrentBiometriaEleitor().TemDedos();
    }
    const bool treinamento = EhTreinamentoMesario();
    bool usaBiometria = temDedos && !treinamento;
    if (temDedos && treinamento) {
        usaBiometria = !EleitorNaFaixaSemBiometria();
    }
    const bool habilitaBiometria = comum::CConfiguracaoEleicao::GetInst().HabilitaBiometria();
    if (usaBiometria && habilitaBiometria) {
        NavegaBiometrica();
    } else {
        NavegaAnoNascimento();
    }
}

void CNomeEleitor::ConfirmaSemAnoNascimento()
{
    if (comum::CConfiguracaoEleicao::GetInst().HabilitaBiometria() && comum::CLocal::GetInst().UrnaBiometrica()) {
        NavegaBiometrica();
    } else {
        HabilitaEleitor();
    }
}

// (original lines 138-142: content not recovered)
#line 143
void CNomeEleitor::NavegaBiometrica()
{
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    if (ehDemo) {
        m_pNextState = &CInformaBioDesabilitadaDemo::GetInst();
    } else {
        m_pNextState = &CControlaReconhecimento::GetInst();
    }
}


void CNomeEleitor::NavegaAnoNascimento()
{
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    if (ehDemo) {
        m_pNextState = &CInformaAnoDesabilitadoDemo::GetInst();
    } else {
        LimpaBiometria();
        m_pNextState = &CPedeAnoNascimentoSemBiometria::GetInst();
    }
}

} // namespace vota
