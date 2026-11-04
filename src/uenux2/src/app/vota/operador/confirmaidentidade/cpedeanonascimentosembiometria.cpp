#include "app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.h"

#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.h"
#include "app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CPedeAnoNascimentoSemBiometria::~CPedeAnoNascimentoSemBiometria() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("Digite o ANO de nascimento:", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    AdicionaCampoNumerico(builder, 4, true, api::SPoint{29, 3});
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: habilitar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaErro()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Seq:", api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&comum::CEleitorDadoSequencial::Text, api::SPoint{40, 2}, "{:04}", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("ANO DE NASCIMENTO INCORRETO", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: tentar novamente", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPedeAnoNascimentoSemBiometria::CPedeAnoNascimentoSemBiometria()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
    , m_formErro(MontaTelaErro())
    , m_tentativas(0)
    , m_bPrimeira(true)
{
}

CPedeAnoNascimentoSemBiometria& CPedeAnoNascimentoSemBiometria::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeAnoNascimentoSemBiometria());
    }
    return *s_inst;
}

std::unique_ptr<CPedeAnoNascimentoSemBiometria> CPedeAnoNascimentoSemBiometria::s_inst;
std::mutex CPedeAnoNascimentoSemBiometria::s_mutex;

void CPedeAnoNascimentoSemBiometria::StartState()
{
    SetNextState(this);
    m_tentativas = 0;
    m_bPrimeira = true;
    m_form->Slot2();
}

void CPedeAnoNascimentoSemBiometria::LeAnoDigitado()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA: {
        const std::string ano = m_form->GetEntradas().at(0)->GetTexto();
        if (ano.size() >= 4) {
            const unsigned long digitado = std::stoul(ano);
            if (comum::CEleitores::GetInst().GetCurrent()->GetEleitor().GetAnoNascimento() == digitado) {
                CLogVota::GetInst().LogaAnoNascimentoIgualCadastro();
                m_pNextState = &CInformaEleitorPodeVotar::GetInst();
            } else {
                CLogVota::GetInst().LogaAnoNascimentoDiferenteCadastro();
                if (++m_tentativas <= 1) {
                    m_bPrimeira = false;
                    m_formErro->Slot2();
                } else {
                    m_pNextState = &CInformaAnoNascimentoErrado::GetInst();
                }
            }
        }
        break;
    }
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
        break;
    default:
        break;
    }
}

void CPedeAnoNascimentoSemBiometria::ProcessInput()
{
    if (m_bPrimeira) {
        LeAnoDigitado();
    } else if (m_formErro->Read() == api::INPUT_CONFIRMA) {
        m_bPrimeira = true;
        m_form->Slot2();
    }
}

} // namespace vota
