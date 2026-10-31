// Reconstruction: comum::md::CEntidadeHashes::ValidaCriacao (target fn 5855). Its throws are records of the target (lines
// 59 and 62, column 15).

#include "app/comum/gravadores/md/centidadehashes.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-55: content not recovered)
#line 56
void CEntidadeHashes::ValidaCriacao() const
{
    if (m_fase == '0' || m_fase > FASE_TREINAMENTO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8672, "Fase inválida");
    }
    if (m_siglaUF.size() != 2) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8673, std::format("UF inválida: {}", m_siglaUF));
    }
}

} // namespace comum::md
