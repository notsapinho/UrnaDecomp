#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

namespace vota::testeteclado {

CRetomada::~CRetomada() = default;

comum::CAppState* CRetomada::GetEstadoSemTeste()
{
    if (m_retomada == 1) {
        return &CReinicioVotacao::GetInst();
    }
    return this;
}

} // namespace vota::testeteclado
