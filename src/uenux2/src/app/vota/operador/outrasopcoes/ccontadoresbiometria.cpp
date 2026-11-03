// vota::CContadoresBiometria (app/vota/operador/outrasopcoes/ccontadoresbiometria.cpp, the class name in lower case).
// This comment is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/ccontadoresbiometria.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/clocal.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CContadoresBiometria::~CContadoresBiometria() = default;

std::unique_ptr<CContadoresBiometria> CContadoresBiometria::s_inst;
std::mutex CContadoresBiometria::s_mutex;

std::string TextoHabilitacaoBiometrica()
{
    std::string quantidade = "n.a.";
    if (comum::CLocal::GetInst().UrnaBiometrica()) {
        quantidade = std::format("{:04}", comum::CEleitores::GetInst().QuantidadeHabilitacaoBiometrica());
    }
    return std::format("Habilitação biométrica: {}", quantidade);
}

std::string TextoHabilitacaoBiografica()
{
    std::string quantidade = "n.a.";
    if (comum::CLocal::GetInst().UrnaBiometrica()) {
        quantidade = std::format("{:04}", comum::CEleitores::GetInst().QuantidadeHabilitacaoBiografica());
    }
    return std::format("Habilitação biográfica: {}", quantidade);
}

std::string TextoHabilitacaoSemBiometria()
{
    std::string quantidade = "n.a.";
    if (comum::CLocal::GetInst().UrnaBiometrica()) {
        quantidade = std::format("{:04}", comum::CEleitores::GetInst().QuantidadeHabilitacaoSemBiometria());
    }
    return std::format("Habilitação sem biometria: {}", quantidade);
}

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&TextoHabilitacaoBiometrica, api::SPoint{35, 1}, api::ALINHAMENTO_DIREITA);
    builder.AddTextField(&TextoHabilitacaoBiografica, api::SPoint{35, 2}, api::ALINHAMENTO_DIREITA);
    builder.AddTextField(&TextoHabilitacaoSemBiometria, api::SPoint{35, 3}, api::ALINHAMENTO_DIREITA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CContadoresBiometria::CContadoresBiometria()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CContadoresBiometria& CContadoresBiometria::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CContadoresBiometria());
    }
    return *s_inst;
}

void CContadoresBiometria::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CContadoresBiometria::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CEscolheOpcao::GetInst();
    }
}

} // namespace vota
