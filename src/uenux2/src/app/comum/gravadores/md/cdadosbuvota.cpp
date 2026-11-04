// comum::md::CDadosBUVota (/home/rubio/tse/uenux2/src/app/comum/gravadores/md/cdadosbuvota.cpp): the getter of the
// optional date, whose record (line 37, column 15) is a record of the target, so its line is fixed. It has no target
// index of its own: binaryen inlines it into its one caller, held by CConversorEntidadeBU::DoConverte (fn 10273), where
// it opens a frame of its own. Where it starts is a choice.

#include "app/comum/gravadores/md/cdadosbuvota.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-33: content not recovered)
#line 34
api::CDateTime CDadosBUVota::GetDataHoraDesligamentoVotoImpresso() const
{
    if (!m_dataHoraDesligamentoVotoImpresso.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8661, "Data/hora de desligamento do voto impresso não definida");
    }
    return *m_dataHoraDesligamentoVotoImpresso;
}

} // namespace comum::md
