#include "app/vota/eleitor/fimvotacao/cgerabu.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CGeraBU::CGeraBU()
    : comum::CAppState(),
      m_telaVotacaoEncerrada(TelaVotacaoEncerrada()),
      m_telaPreparandoDados(TelaPreparandoDadosEncerramento())
{
}

CGeraBU::~CGeraBU() = default;

CGeraBU& CGeraBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraBU());
    }
    return *s_inst;
}

std::unique_ptr<CGeraBU> CGeraBU::s_inst;
std::mutex CGeraBU::s_mutex;

} // namespace vota
