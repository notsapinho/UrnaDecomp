#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"

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

} // namespace vota
