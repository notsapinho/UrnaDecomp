#include "app/comum/util/cmonitoraalimentacao.h"

#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/log/clogcomum.h"
#include "app/comum/util/euecomumutilerror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum::util {

// (original lines 11-23: content not recovered)
#line 24
SINGLETON_IMPL_GET_INST(CMonitoraAlimentacao, s_mutex, s_instancia)

void CMonitoraAlimentacao::CreateInst(ELogAplicativos aplicativo)
{
    if (s_instancia) {
        throw CUeComumUtilError(EUE_COMUM_UTIL_INSTANCIA_JA_CRIADA, "Instância já criada");
    }
    s_instancia.reset(new CMonitoraAlimentacao(aplicativo));
}

CMonitoraAlimentacao::CMonitoraAlimentacao(ELogAplicativos aplicativo)
    : m_aplicativo(aplicativo)
    , m_fonte(0xFF)
    , m_statusBatInt(0xFF)
    , m_statusBatExt(0xFF)
    , m_eventos(0)
{
}

std::unique_ptr<CMonitoraAlimentacao> CMonitoraAlimentacao::s_instancia;
std::mutex CMonitoraAlimentacao::s_mutex;


void CMonitoraAlimentacao::VerificaAlimentacao()
{
    if (m_eventos >= 20) {
        return;
    }
    auto& ipower = api::CPolySingleton<api::IPower>::instance();
    CLogComum& logComum = CLogComum::GetInst();
    const uebyte fonte = ipower.Fonte();
    if (fonte != m_fonte) {
        logComum.LogaTipoBateria();
        m_fonte = fonte;
        m_statusBatInt = 0xFF;
        m_statusBatExt = 0xFF;
        ++m_eventos;
    }
    switch (fonte) {
    case 1:
        if (ipower.StatusBatInt() != m_statusBatInt) {
            logComum.LogaNivelBateria(fonte, ipower.StatusBatInt());
            m_statusBatInt = ipower.StatusBatInt();
        }
        break;
    case 2:
        if (ipower.StatusBatExt() != m_statusBatExt) {
            logComum.LogaNivelBateria(fonte, ipower.StatusBatExt());
            m_statusBatExt = ipower.StatusBatExt();
        }
        break;
    }
    if (m_eventos == 20) {
        logComum.LogaSuspensoMonitoramenteRepeticao(m_eventos);
    }
}

} // namespace comum::util
