#include "app/vota/eleitor/fimvotacao/cgerarelatorios.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CGeraRelatorios::CGeraRelatorios()
    : comum::CAppState(),
      m_telaPreparandoDados(TelaPreparandoDadosEncerramento())
{
}

CGeraRelatorios::~CGeraRelatorios() = default;

CGeraRelatorios& CGeraRelatorios::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraRelatorios());
    }
    return *s_inst;
}

std::unique_ptr<CGeraRelatorios> CGeraRelatorios::s_inst;
std::mutex CGeraRelatorios::s_mutex;

} // namespace vota
