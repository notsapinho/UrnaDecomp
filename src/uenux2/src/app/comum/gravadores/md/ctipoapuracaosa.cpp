// Reconstruction: comum::md::CTipoApuracaoSA's constructor, ValidaCriacao and ValidaMotivoApuracao, which
// comum::asn::CConversorTipoApuracaoSA::DoDesconverte (target fn 10282), their one caller, holds inlined. The throws
// are records of the target (lines 40 and 72, column 15); the constructor has none, so its line is a choice, above
// the member it calls. ValidaMotivoApuracao's cases are in the order 1, 3, 4, 2, measured: in the order 1, 2, 3, 4 the
// switch's br_table reads [0 1 2 3] where the target's reads [0 3 1 2].

#include "app/comum/gravadores/md/ctipoapuracaosa.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

CTipoApuracaoSA::CTipoApuracaoSA(ETipoApuracao tipoApuracao, uebyte motivoApuracao)
    : m_tipoApuracao(tipoApuracao), m_motivoApuracao(motivoApuracao)
{
    ValidaCriacao();
}

// (original lines 19-36: content not recovered)
#line 37
void CTipoApuracaoSA::ValidaCriacao() const
{
    if (m_tipoApuracao < TIPO_TOTALMENTE_MANUAL || m_tipoApuracao > TIPO_MISTA_MR) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8687, "Tipo de apuração inválido");
    }
    ValidaMotivoApuracao();
}

// (original lines 45-52: content not recovered)
#line 53
void CTipoApuracaoSA::ValidaMotivoApuracao() const
{
    bool motivoValido = false;
    switch (m_tipoApuracao) {
        case TIPO_TOTALMENTE_MANUAL:
            motivoValido = (m_motivoApuracao >= 1 && m_motivoApuracao <= 3) || m_motivoApuracao == 99;
            break;
        case TIPO_MISTA_BU:
            motivoValido = (m_motivoApuracao >= 1 && m_motivoApuracao <= 5) || m_motivoApuracao == 99;
            break;
        case TIPO_MISTA_MR:
            motivoValido = (m_motivoApuracao >= 1 && m_motivoApuracao <= 6) || m_motivoApuracao == 99;
            break;
        case TIPO_TOTALMENTE_ELETRONICA:
            motivoValido = (m_motivoApuracao >= 1 && m_motivoApuracao <= 3) || m_motivoApuracao == 99;
            break;
    }

    if (!motivoValido) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8688, "Motivo de apuração inválido");
    }
}

} // namespace comum::md
