#include "app/comum/util/cmonitoraalimentacao.h"

#include "app/comum/util/euecomumutilerror.h"

namespace comum::util {

// (original lines 7-25: content not recovered)
#line 26
void CMonitoraAlimentacao::CreateInst(ELogAplicativos aplicativo)
{
    if (s_inst) {
        throw CUeComumUtilError(EUE_COMUM_UTIL_INSTANCIA_JA_CRIADA, "Instância já criada");
    }
    s_inst.reset(new CMonitoraAlimentacao(aplicativo));
}

CMonitoraAlimentacao::CMonitoraAlimentacao(ELogAplicativos aplicativo)
    : m_aplicativo(aplicativo)
    , m_estado(0xFFFFFF)
{
}

std::unique_ptr<CMonitoraAlimentacao> CMonitoraAlimentacao::s_inst;

} // namespace comum::util
