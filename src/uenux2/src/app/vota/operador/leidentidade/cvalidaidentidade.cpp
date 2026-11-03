// vota::CValidaIdentidade (no record names its file). The reconstruction's notes are in cvalidaidentidade.h and
// src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/leidentidade/cvalidaidentidade.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cidentidadeinvalida.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/leidentidade/cprocuraeleitor.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

std::unique_ptr<CValidaIdentidade> CValidaIdentidade::s_inst;
std::mutex CValidaIdentidade::s_mutex;

CValidaIdentidade::~CValidaIdentidade() = default;

CValidaIdentidade& CValidaIdentidade::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CValidaIdentidade());
    }
    return *s_inst;
}

CValidaIdentidade::CValidaIdentidade() : comum::CAppState(EVENTO_ENTRADA) {}

TOpcoesIdentidade MontaOpcoesIdentidade(std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> tipos)
{
    TOpcoesIdentidade opcoes;
    int opcao = 1;
    for (const auto tipo : tipos) {
        switch (tipo) {
        case ecourna::app::dados::TipoIDInscricaoEleitoral:
            opcoes.emplace(opcao++, TOpcoesIdentidade::mapped_type("Título de eleitor", tipo));
            break;
        case ecourna::app::dados::TipoIDCPF:
            opcoes.emplace(opcao++, TOpcoesIdentidade::mapped_type("CPF", tipo));
            break;
        case ecourna::app::dados::TipoIDNumeroLivre:
            opcoes.emplace(opcao++, TOpcoesIdentidade::mapped_type("Identificador", tipo));
            break;
        }
    }
    return opcoes;
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaOpcoes(const TOpcoesIdentidade& opcoes)
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Tipo de identidade digitada", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    for (const auto& [opcao, identidade] : opcoes) {
        builder.AddTextField(std::format("{}-{}", opcao, identidade.first),
                             api::SPoint{1, static_cast<api::TPosition>(opcao + 1)}, api::ALINHAMENTO_ESQUERDA);
    }
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("ESCOLHA O TIPO:", api::SPoint{24, 4}, api::ALINHAMENTO_ESQUERDA);
    AdicionaCampoNumerico(builder, 1, false, api::SPoint{40, 4});
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    return builder.GetInteractiveForm("", true);
}

void CValidaIdentidade::StartState()
{
    const std::string identidade = GetIdentidadeDigitada();
    const std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> tipos =
        comum::md::CValidadorIdentidade::GetInst().TiposValidos(identidade);
    switch (tipos.size()) {
    case 0:
        m_pNextState = &CIdentidadeInvalida::GetInst();
        break;
    case 1:
        CLogVota::GetInst().loga(
            std::format("Identificador digitado pelo mesário foi: ({})", MontaOpcoesIdentidade(tipos)[1].first));
        SetTipoIdentidadeDigitada(tipos[0]);
        m_pNextState = &CProcuraEleitor::GetInst();
        break;
    default:
        m_pNextState = this;
        m_identidades = MontaOpcoesIdentidade(tipos);
        m_form = MontaTelaOpcoes(m_identidades);
        m_form->Slot2();
        break;
    }
}

void CValidaIdentidade::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        if (comum::CAppState* proximo = ProximoEstadoOpcaoDigitada()) {
            m_pNextState = proximo;
        }
        break;
    default:
        break;
    }
}

comum::CAppState* CValidaIdentidade::ProximoEstadoOpcaoDigitada()
{
    const std::string opcao = m_form->GetEntradas().at(0)->GetTexto();
    if (opcao.size() != 1) {
        return nullptr;
    }
    const auto identidade = m_identidades.find(std::stoi(opcao));
    if (identidade != m_identidades.end()) {
        CLogVota::GetInst().loga(
            std::format("Identificador digitado pelo mesário foi: ({})", identidade->second.first));
        SetTipoIdentidadeDigitada(identidade->second.second);
        return &CProcuraEleitor::GetInst();
    }
    CLogVota::GetInst().loga("Identificador inválido para o tipo informado");
    return nullptr;
}

} // namespace vota
