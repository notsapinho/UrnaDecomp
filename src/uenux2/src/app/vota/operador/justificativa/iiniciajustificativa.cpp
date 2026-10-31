#include "app/vota/operador/justificativa/iiniciajustificativa.h"

#include "app/vota/euevotaerror.h"

namespace vota {

// (original lines 7-23: content not recovered)
#line 24
IIniciaJustificativa::IIniciaJustificativa(IConfirmaJustificativa* confirma) : m_confirma(confirma)
{
    if (!confirma) {
        throw CUeVotaError(EUE_VOTA_CONFIRMACAO_JUSTIFICATIVA_NULA, "Confirmação de justificativa nula");
    }
}

} // namespace vota
