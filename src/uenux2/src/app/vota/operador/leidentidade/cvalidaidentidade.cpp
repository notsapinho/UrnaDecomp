// vota::CValidaIdentidade (no record names its file). The reconstruction's notes are in cvalidaidentidade.h and
// src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/leidentidade/cvalidaidentidade.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/leidentidade/cprocuraeleitor.h"

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
            std::format("Identificador digitado pelo mesário foi: ({})", identidade->second.GetIdentificador()));
        SetTipoIdentidadeDigitada(identidade->second.GetTipo());
        return &CProcuraEleitor::GetInst();
    }
    CLogVota::GetInst().loga("Identificador inválido para o tipo informado");
    return nullptr;
}

} // namespace vota
