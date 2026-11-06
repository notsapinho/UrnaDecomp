#include "app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.h"

#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"

using namespace comum;

namespace vota {

CGeraDadosDinamicos::CGeraDadosDinamicos()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CGeraDadosDinamicos& CGeraDadosDinamicos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraDadosDinamicos());
    }
    return *s_inst;
}

std::unique_ptr<CGeraDadosDinamicos> CGeraDadosDinamicos::s_inst;
std::mutex CGeraDadosDinamicos::s_mutex;

// (original lines 31-36: content not recovered)
#line 37
void CGeraDadosDinamicos::StartState()
{
    CEstadoAudio& estadoAudio = CEstadoAudio::GetInst();
    CAppInfo& appInfo = CAppInfo::GetInst();

    estadoAudio.GeraDadosDinamicos();
    estadoAudio.CarregaEleitores();

    md::estadoaplicacao::CEstadoGeralVota& vota = appInfo.GetVota();
    ASSERT(vota.GetEstadoVota() == EAVINICIAL || vota.GetEstadoVota() == EAVGERADADOSDINAMICOS,
        api::EUA_GERADADOSDINAMICOS_ESTADOINVALIDO);
    vota.SetEstadoVota(EAVAGUARDAHORAZERESIMA);
    CSincronizaVota::SincronizaEstadoGeralVota();

    m_pNextState = &CVerificaHorarioZeresima::GetInst();
}

} // namespace vota
