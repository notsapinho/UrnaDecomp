#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"

namespace vota::testeteclado {

CTesteTeclado::CTesteTeclado()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
    , m_indice(0)
    , m_pEstadoPassouNoTeste(nullptr)
{
}

CTesteTeclado& CTesteTeclado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTesteTeclado());
    }
    return *s_inst;
}

std::unique_ptr<CTesteTeclado> CTesteTeclado::s_inst;
std::mutex CTesteTeclado::s_mutex;

CTesteTeclado::~CTesteTeclado() = default;

} // namespace vota::testeteclado
