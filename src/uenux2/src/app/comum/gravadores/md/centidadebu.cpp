// comum::md::CEntidadeBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/md/centidadebu.cpp): the three getters
// that throw when their part of the BU is missing. Their records are records of the target, so their lines are fixed:
//   GetDadosVota                    record at line 186, column 15
//   GetDadosSA                      record at line 196, column 15
//   GetDetalhamentoComparecimento   record at line 206, column 15
// None has a target index of its own: binaryen inlines each into its one caller, CConversorEntidadeBU::DoConverte (fn
// 10273), where each opens a frame of its own. ValidaCriacao (records at lines 159 to 177, held by fn 11629, which is
// not written) is not written: its lines are left blank. Where each getter starts is a choice.

#include "app/comum/gravadores/md/centidadebu.h"

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 16-182: content not recovered)
#line 183
const CDadosBUVota& CEntidadeBU::GetDadosVota() const
{
    if (!m_dadosVota.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8670, "Dados específicos de BU do Vota não definidos");
    }
    return *m_dadosVota;
}

// (original lines 191-192: content not recovered)
#line 193
const CDadosBUSA& CEntidadeBU::GetDadosSA() const
{
    if (!m_dadosSA.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8671, "Dados específicos de BU do SA não definidos");
    }
    return *m_dadosSA;
}

// (original lines 201-202: content not recovered)
#line 203
const ecourna::app::dados::CDetalhamentoComparecimento& CEntidadeBU::GetDetalhamentoComparecimento() const
{
    if (!m_detalhamentoComparecimento.has_value()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8664, "Dados específicos de BU do SA não definidos");
    }
    return *m_detalhamentoComparecimento;
}

} // namespace comum::md
