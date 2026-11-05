#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cinteractiveform.h"
#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/creport.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/relatorios/crelutil.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/cgeradorresumozeresima.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CGeraResumoZeresimaBase::CGeraResumoZeresimaBase()
    : comum::CAppState(EVENTO_NENHUM), m_form(CTelasVota::GetInst().GetTelaGeraResumoZeresima())
{
}

CGeraResumoZeresimaBase::~CGeraResumoZeresimaBase() = default;

void CGeraResumoZeresimaBase::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    GeraResumoZeresima();
    AposGeracao();
    m_pNextState = GetProximoEstado();
}

} // namespace vota
