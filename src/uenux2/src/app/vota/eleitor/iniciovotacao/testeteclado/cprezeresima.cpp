#include "app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.h"

#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.h"
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"
#include "app/vota/log/clogvota.h"

namespace vota::testeteclado {

CPreZeresima::~CPreZeresima() = default;

CPreZeresima::CPreZeresima()
    : m_dataHora(0)
{
}

CPreZeresima& CPreZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPreZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CPreZeresima> CPreZeresima::s_inst;
std::mutex CPreZeresima::s_mutex;

// (original lines 33-44: content not recovered)
#line 45
comum::CAppState* CPreZeresima::GetEstadoPassouNoTeste()
{
    const comum::EEstadoVota estado = comum::CAppInfo::GetInst().GetVota().GetEstadoVota();
    switch (estado) {
        case comum::EAVINICIAL:
        case comum::EAVGERADADOSDINAMICOS:
            return &CGeraDadosDinamicos::GetInst();
        case comum::EAVAGUARDAHORAZERESIMA:
            return &CVerificaHorarioZeresima::GetInst();
        default:
            CLogVota::GetInst().LogaErroEstadoAplicativo();
            throw CUeVotaError(EUE_VOTA_PRE_ZERESIMA_ESTADO_NAO_ESPERADO,
                               "Estado nao esperado " + std::to_string(estado));
    }
}

} // namespace vota::testeteclado
