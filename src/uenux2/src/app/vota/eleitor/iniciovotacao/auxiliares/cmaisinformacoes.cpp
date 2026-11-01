#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <utility>

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

CMaisInformacoes::CMaisInformacoes()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_pRetorno(nullptr)
{
}

CMaisInformacoes::~CMaisInformacoes() = default;

CMaisInformacoes& CMaisInformacoes::GetInst(comum::CAppState* pRetorno)
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMaisInformacoes());
    }
    if (pRetorno != nullptr) {
        s_inst->m_pRetorno = pRetorno;
    }
    return *s_inst;
}

std::unique_ptr<CMaisInformacoes> CMaisInformacoes::s_inst;
std::mutex CMaisInformacoes::s_mutex;

void CMaisInformacoes::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        m_pNextState = std::exchange(m_pRetorno, nullptr);
        break;
    case api::INPUT_CONFIRMA: {
        const std::string opcao = m_form->GetEntradas().at(0)->GetTexto();
        if (opcao.empty() || !std::all_of(opcao.begin(), opcao.end(), ::isdigit)) {
            break;
        }
        switch (ecourna::api::util::CStringUtils::ToInt32(opcao)) {
        case 1:
            m_pNextState = &CImpressaoEstadoUrna::GetInst();
            break;
        case 2:
            m_pNextState = &CImpressaoListaEleitores::GetInst();
            break;
        case 3:
            m_pNextState = &CImpressaoVersaoPacotes::GetInst();
            break;
        case 4:
            m_pNextState = &CImpressaoPU::GetInst();
            break;
        case 5:
            m_pNextState = &CMenuVisualizarCandidatos::GetInst();
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

} // namespace vota
