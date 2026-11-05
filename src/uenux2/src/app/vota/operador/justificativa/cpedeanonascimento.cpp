// vota::CPedeAnoNascimento: no record names this file or any of its members; the reconstruction's notes are in
// cpedeanonascimento.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/justificativa/canoinformadoinvalido.h"
#include "app/vota/operador/justificativa/celeitormenor16anos.h"
#include "app/vota/operador/justificativa/cjustificativaefetuada.h"
#include "app/vota/operador/justificativa/iiniciajustificativa.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "ecourna/api/util/cstringutils.hpp"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CPedeAnoNascimento::~CPedeAnoNascimento() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Digite o ANO de nascimento: ", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    AdicionaCampoNumerico(builder, 4, true, api::SPoint{29, 2});
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: justificar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPedeAnoNascimento::CPedeAnoNascimento()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CPedeAnoNascimento& CPedeAnoNascimento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeAnoNascimento());
    }
    return *s_inst;
}

std::unique_ptr<CPedeAnoNascimento> CPedeAnoNascimento::s_inst;
std::mutex CPedeAnoNascimento::s_mutex;

void CPedeAnoNascimento::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CPedeAnoNascimento::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA: {
        const std::string ano = m_form->GetEntradas().at(0)->GetTexto();
        if (ano.size() >= 4) {
            CThreadOperador::GetInst().SetAnoNascimentoDigitado(ano);
            const ueint16 anoNascimento = ecourna::api::util::CStringUtils::ToInt16(ano);
            const ueint16 idade = comum::CConfiguracaoEleicao::GetInst().GetPleito().GetData().GetAno() - anoNascimento;
            if (anoNascimento < 1900 || idade <= 0) {
                CLogVota::GetInst().LogaAnoNascimentoInvalido();
                m_pNextState = &CAnoInformadoInvalido::GetInst();
            } else if (idade < 16) {
                CLogVota::GetInst().LogaEleitorSemIdadeMinima();
                m_pNextState = &CEleitorMenor16Anos::GetInst();
            } else {
                JustificaEleitor(anoNascimento);
                m_pNextState = &CJustificativaEfetuada::GetInst();
            }
        }
        break;
    }
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaMesarioCancelouEntradaDados();
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
